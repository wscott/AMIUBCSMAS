#include "starana-classes.h"

#include <string.h>
#include <ctype.h>


const int DISPLAY_RESOLUTION = 600;


// some terrible globals
int PARmin_mineral_move;
int PARmax_search_distance;
int PARmin_pop_for_scanner;

stars_map* game_map = NULL;
map_view* mapview = NULL;
graphics* display = NULL;
int infile_lineno;
myString infile_name;
myString infile_path;



bool initialize_map(const myString& smff)
{
  game_map = new stars_map();
  mapview = new map_view(game_map);

  // set the default path for all includes
  string::size_type i = string::npos, oi = string::npos;
  int j;

  while ( (i = smff.index('/', i+1)) != string::npos)
    oi = i;

  if (oi == string::npos) // no path
    infile_path = "";
  else
    infile_path = myString(smff)(0, oi+1);

  // open report log
  game_map->open_report_log(infile_path + "report-log");

  if (!game_map->read_smf_file(smff))
    return false;

  game_map->init_ownership();

  if (do_display)
    display->set_intro_loadingfile("Generating report-log....");

  game_map->log_all_messages();

  // initialize the default view
  if (do_display)
    display->set_intro_loadingfile("Initializing display....");

  mapview->initialize();

  // see if we have some planet view
  if (!mapview->get_num_planet_views()) {

    // load default planet views, select 1st
    if (!mapview->import_planet_views(infile_path + "default.pfl")) {
      // we have a problem - set up some crap display
      int params[16];
      for (j = 0; j < 16; j++)
	params[j] = 0;

      mapview->clone_planet_view(NULL);
      mapview->get_planet_view()->name = myString("PLEASE copy default.pfl into the directory containing the master file.");

      mapview->select_plamode(0);
      params[0] = 3;
      mapview->set_plamode("Set Marker", PF_STOMP,
			   PF_CIRCLES|PF_LINES|PF_DATA|PF_MARKER|PF_NAME|PF_FLAG,
			   params);
      mapview->select_plamode(1);
      params[0] = 0;
      mapview->set_plamode("Set Planet Name", PF_STOMP,
			   PF_CIRCLES|PF_LINES|PF_DATA|PF_MARKER|PF_NAME|PF_FLAG,
			   params);
    }
    mapview->select_planet_view(0);

  } else // select first planet view
    mapview->select_planet_view(0);

  // see if we have some fleet view
  if (!mapview->get_num_fleet_views()) {

    // load default fleet views, select 1st
    if (!mapview->import_fleet_views(infile_path + "default.ffl")) {
      // we have a problem - set up some crap display
      int params[16];
      for (j = 0; j < 16; j++)
	params[j] = 0;

      mapview->clone_fleet_view(NULL);
      mapview->get_fleet_view()->name = myString("PLEASE copy default.ffl into the directory containing the master file.");
    }
    mapview->select_fleet_view(0);

  } else // select first fleet view
    mapview->select_fleet_view(0);

  // select a random planet....
  mapview->set_active_planet(_xypoint(0,0), 0);
  mapview->set_active_planet(_xypoint(0,0), 1);

  return true;
}



#define GRANULARITY 32


void stars_map::build_valtab(void)
{
  // note: a request outside ranges will plainly SIGV
  int x, y;
  int d, v;

  valtab = new int*[wfrange + 2*GRANULARITY - 1];

  for (y = 0; y < wfrange + 2*GRANULARITY - 1; y++) {
    valtab[y] = new int[wfrange + 2*GRANULARITY - 1];

    for (x = 0; x < wfrange + 2*GRANULARITY - 1; x++) {
      d = (int)sqrt( (double)(x*x + y*y) );
       
      if (d > wfrange)
	v = 0;
      else
	v = wfunc(d);

      valtab[y][x] = v;
    }
  }
}



stars_map::stars_map(void) :
        game_name("unnamed"),
        xmin(100000), ymin(100000), xmax(-100000), ymax(-1000000), 
        total_planets(0), unexplored_planets(0), uninhabited_planets(0),
        unsorted_ptable(NULL), sorted_ptable(NULL), xregion_ptable(NULL),
	n_regions(0), valtab(NULL), 
	wfunc(wfunc_160), wfrange(160), wf_rspan(0),
	view_res(DISPLAY_RESOLUTION),
        row_lengths(NULL), row_owners(NULL), row_posits(NULL),
        number_races(0), cur_alliance(-1),
	ship_hulls(NULL),
	actual_sim_future(8), report_log(NULL)
{
  int i;

  for (i = 0; i < 16; i++) {
    race_planets[i] = 0;
    race_surface[i] = 0;
    race_list[i] = 0;
    race_alliances[i] = i;
  }
}


stars_map::~stars_map(void)
{
  //  int y;
  //  for (y = 0; y < wfrange; y++)
  //    delete[] valtab[y];

  //  delete[] valtab;

  // delete planets

  if (report_log)
    fclose(report_log);
}



void stars_map::open_report_log(const myString& rln)
{
  report_log = fopen(rln, "w");

  if (!report_log)
    yyerror("Cannot open report-log for writing");
}



void stars_map::log(const myString& m)
{
  if (report_log) {
    fprintf(report_log, "%s", (const char*)m);
    fflush(report_log);
  }
}



void stars_map::sort_universe(void)
{
  planet* p;
  planet* p2;
  planet* op2;
  int diff;
  int i, j;
  int region;

  if (do_display)
    display->set_intro_loadingfile("Planets: initial check....");

  for (p = unsorted_ptable; p; p = p->next) {
    if ( p->position() == _xypoint(0, 0) ) {
      log(p->_name + ": has undefined position?!? assuming 1200,1200\n");
      p->pos.x = 1200;
      p->pos.y = 1200;
    }

    if (p->pos.x < xmin)
      xmin = p->pos.x;
    if (p->pos.x > xmax)
      xmax = p->pos.x;

    if (p->pos.y < ymin)
      ymin = p->pos.y;
    if (p->pos.y > ymax)
      ymax = p->pos.y;
  }

  xmax++;
  ymax++;
  xmin = (xmin / 100) * 100;
  ymin = (ymin / 100) * 100;
  xmax = (xmax / 100 + 1) * 100;
  ymax = (ymax / 100 + 1) * 100;

  // adjust to square universe
  if ((xmax - xmin) != (ymax - ymin)) {
    diff = (xmax - xmin) - (ymax - ymin);

    if (diff > 0) // violence is the answer
      ymin -= diff;
    else
      xmin += diff;
  }

  // perform all checks
  check_planets_step1();

  if (do_display)
    display->set_intro_loadingfile("Fleets: processing....");

  // check fleets
  check_fleets();

  if (do_display)
    display->set_intro_loadingfile("Planets: simulation....");

  // count planets
  for (p = unsorted_ptable; p; p = p->next)
    if (p->trusted_source == -1)
      unexplored_planets++;
    else if (!p->_owner)
      uninhabited_planets++;
    else {
      race_planets[p->_owner->id]++;
      p->rnext = p->_owner->planet_table;
      p->_owner->planet_table = p;
    }

  for (i = 0; i < number_races; i++)
    race_list[i]->owned_planets = race_planets[i];

  evolve_planets();

  if (do_display)
    display->set_intro_loadingfile("Planets: final check....");

  check_planets_step2();
  empire_report();

  // generate regions and assign planets to them
  // regions are horizontal slices of the universe of height 1
  // within each subregion the planets are kept sorted along
  // their x-position
  n_regions = ymax / GRANULARITY + 1;

  wf_rspan = wfrange / GRANULARITY;

  build_valtab();

  sorted_ptable = new planet*[n_regions];
  xregion_ptable = new planet**[n_regions];
  for (i = 0; i < n_regions; i++) {
    sorted_ptable[i] = NULL;
    xregion_ptable[i] = new planet*[n_regions];

    for (j = 0; j < n_regions; j++)
      xregion_ptable[i][j] = NULL;
  }

  for (p = unsorted_ptable; p; p = p->next) {

    if (!p->_owner)
      continue; // skip uninhabited worlds

    region = p->pos.y / GRANULARITY;

    for (op2 = NULL, p2 = sorted_ptable[region];
	   p2 && p2->pos.x < p->pos.x; op2 = p2, p2 = p2->snext);

    if (op2 == NULL) { // head
      p->snext = sorted_ptable[region];
      sorted_ptable[region] = p;
    } else { // tail & insert
      p->snext = op2->snext;
      op2->snext = p;
    }
  }

  // now set xregion_ptable to point to the first to take into account when
  // computing region "region"

  for (i = 0; i < n_regions; i++)
    for (p = sorted_ptable[i]; p; p = p->snext) {
      region = p->pos.x / GRANULARITY;
      region -= wfrange;
      if (region < 0)
	region = 0;

      if (!xregion_ptable[i][region])
	xregion_ptable[i][region] = p;
    }

  // fix NULLed sregions by making them point to the next one
  for (i = 0; i < n_regions; i++)
    for (j = n_regions - 2; j >= 0; j--)
      if (!xregion_ptable[i][j])
	xregion_ptable[i][j] = xregion_ptable[i][j + 1];

  // debug- dump regions
  /*  for (region = (xmin / GRANULARITY); region < n_regions; region++) {
    fprintf(stderr, "Region: %d ->", region);
  
    for (i = 0, p = sorted_ptable[region]; p; p = p->snext, i++)
      fprintf(stderr, "  %s(%d,%d)", p->name().chars(), p->pos.x, 
	      p->pos.y);

    fprintf(stderr, "\n (region %d : %d planets)\n", region, i);
  } */
}



void stars_map::init_ownership(void)
{
  int i;

  if (actual_sim_future < 8)
    actual_sim_future = 7;
  else if (actual_sim_future > SIM_FUTURE)
    actual_sim_future = SIM_FUTURE;

  if (max_zoom < 1)
    max_zoom = 1;
  else if (max_zoom > 5)
    max_zoom = 5;

  sort_universe();

  base_res = view_res * (1 << (max_zoom-1));

  // surface of the universe
  surface = base_res * base_res;

  row_lengths = new short int[base_res];
  row_owners = new short int*[base_res];
  row_posits = new int*[base_res];

  for (i = 0; i < base_res; i++)
    row_lengths[i] = -1;

  gmscale = (xmax - xmin) * 1024 / base_res;
}




int stars_map::get_ownership(const int xm, const int ym, 
			     const int reg0, const int reg1, bool *discuss)
{
  int rw[16];
  int yr;
  register planet* p;
  register int xo;
  register int yo;
  register int i;
  int firstrace, firstval;
  int secondval;
  int curr_col;

  bzero((char*)rw, 16 * sizeof(int));

  for (yr = reg0; yr <= reg1; yr++)
    for (p = sorted_ptable[yr]; p; p = p->snext) {

      xo = p->pos.x - xm;

      if (xo > wfrange)
	break; // no need to continue

      xo = abs(xo);

      if (xo > wfrange)
	continue;

      yo = abs(p->pos.y - ym);

      rw[p->_owner->id] += p->power * valtab[yo][xo];
    }

  // use max value
  firstrace = -1;
  firstval = 1;
  secondval = 1;
  *discuss = false;
  for (i = 0; i < number_races; i++)
    if (rw[i] > firstval) {
      firstval = rw[i];
      firstrace = i;
    } else if (rw[i] > secondval)
      secondval = rw[i];
  
  if (firstrace >= 0) {
    race_surface[firstrace]++;

    curr_col = firstrace;

    if (secondval != 1 && 4 * (firstval - secondval) > firstval)
      *discuss = true;
  } else
    curr_col = -1;

  return curr_col;
}



void stars_map::line_ownership(const int yg)
{
  int xg;
  int xm, ym;
  int region, reg0, reg1;
  int xp_tab[128];
  short int col_tab[128];
  int xtab_ptr;
  short int curr_col, last_col;
  bool discuss;

  ym = yg * gmscale / 1024 + ymin;
  region = ym / GRANULARITY;

  reg0 = region - wf_rspan;
  reg1 = region + wf_rspan;
  if (reg0 < (xmin / GRANULARITY))
    reg0 = xmin / GRANULARITY;
  if (reg1 >= n_regions)
    reg1 = n_regions - 1;

  xtab_ptr = 0;
  last_col = -1;

  for (xg = 0; xg < base_res; xg++) {
    xm = xg * gmscale / 1024 + xmin;

    curr_col = get_ownership(xm, ym, reg0, reg1, &discuss);

    if (curr_col != last_col) {
      if (xg != 0 && xtab_ptr == 0) {  // first point was NOT owned
	xp_tab[xtab_ptr] = 0;
	col_tab[xtab_ptr] = -1;
	xtab_ptr++;
      }

      xp_tab[xtab_ptr] = xg;
      col_tab[xtab_ptr] = curr_col;
      last_col = curr_col;
      xtab_ptr++;
    }
  }

  xp_tab[xtab_ptr] = base_res - 1;
  xtab_ptr++;

  // store the array
  row_lengths[yg] = xtab_ptr - 1;
  row_owners[yg] = new short int[xtab_ptr];
  memcpy(row_owners[yg], col_tab, sizeof(short int) * xtab_ptr);
  row_posits[yg] = new int[xtab_ptr];
  memcpy(row_posits[yg], xp_tab, sizeof(int) * xtab_ptr);
}


// find planet closest to specified point

planet* stars_map::find_planet(const _xypoint& xy)
{
  // scan all planets
  planet* bestp = NULL;
  planet* p;
  int bestd = 100000000;
  int d;

  for (p = unsorted_ptable; p; p = p->next) {
    d = (p->pos.x - xy.x)*(p->pos.x - xy.x) +
      (p->pos.y - xy.y)*(p->pos.y - xy.y);

    if (d < bestd) {
      bestd = d;
      bestp = p;
    }
  }

  return bestp;
}


// find planet closest to movement vector

planet* stars_map::find_planet(const _xypoint& xy, const _xypoint& dir)
{
  // approx angular resolution is 1/128
  // assume this as error in target planet determination
  // closer planets are preferred (not a good idea, maybe?)

  // longitudinal vector
  double lx = dir.x, ly = dir.y;
  double lmod = sqrt(lx*lx + ly*ly);
  lx /= lmod;
  ly /= lmod;

  // transversal vector
  double tx = -ly, ty = lx;

  planet* p;
  double px, py;
  double ld, td, best_d = 1e10;
  planet* best_p = NULL;

  //  fprintf(stderr, "Trajectory is %d,%d --> %g,%g\n", 
  //	  xy.x, xy.y, lx, ly);

  for (p = game_map->unsorted_ptable; p; p = p->next) {
    px = p->pos.x - xy.x;
    py = p->pos.y - xy.y;

    //    fprintf(stderr, "  planet %s (%d,%d)", p->name().chars(),
    //	    p->pos.x, p->pos.y);

    ld = px*lx + py*ly;
    if (ld < 0.0) {
      //      fprintf(stderr, "  behind!!\n");
      continue; // planet is behind fleet
    }

    td = px*tx + py*ty;

    //    fprintf(stderr, "  L=%g T=%g", ld, td);    

    // note: I have artificially extended the cone by a factor of
    // two to include possible rounding errors, the real value
    // should be ld/128 and NOT ld/64

    if (fabs(td) < ld / 64.0) {
      // planet is inside cone, it's a possible destination

      //      fprintf(stderr, "  inside cone!\n");

      if (ld < best_d) {
	best_d = ld;
	best_p = p;
      }
    } else {
      //      fprintf(stderr, "\n");
    }
  }

  return best_p;
}


// find planet from name

planet* stars_map::find_planet(const myString& pn)
{
  planet* p;
  int rv;

  for (p = unsorted_ptable; p; p = p->next) {
    rv = strcmp((const char*)p->_name, (const char*)pn);

    if (rv == 0)
      return p;
    else if (rv > 0)
      return NULL;
  }

  return NULL;
}


planet* stars_map::find_planet(const int st_id)
{
  planet* p;

  for (p = unsorted_ptable; p; p = p->next)
    if (p->stars_id == st_id)
      return p;

  return NULL;
}


planet* stars_map::grab_planet(const myString& pn)
{
  planet* p;

  if ( (p = find_planet(pn)) )
    return p;

  p = new planet(pn);
  add_planet(p);

  return p;
}


void stars_map::add_planet(planet* p)
{
  planet* p2;
  planet* op2;

  total_planets++;

  for (op2 = NULL, p2 = unsorted_ptable;
       p2 && strcmp((const char*)p2->_name, (const char*)p->_name) < 0;
       op2 = p2, p2 = p2->next);

  if (op2 == NULL) { // head
    p->next = unsorted_ptable;
    unsorted_ptable = p;
  } else { // tail & insert
    p->next = op2->next;
    op2->next = p;
  }
}


race* stars_map::add_race(const myString& arg0)
{
  int i;

  if (number_races == 16) {
    char str[256];

    sprintf(str, "trying to add a 17th race?!?!");
    yyerror(str);
  }

  for (i = 0; i < number_races; i++)
    if (race_list[i]->_name == arg0) {
      char str[256];

      sprintf(str, "redefinition of race %s\n", (const char*)arg0);
      yyerror(str);
    }

  race* r = new race(arg0, number_races);

  race_list[number_races++] = r;

  return r;
}



void stars_map::add_message(const _msgtype mt, const myString& m)
{
  logmsgs.add(mt, m);
}



void stars_map::all_races_message(const _msgtype mt, const myString& m)
{
  int i;

  for (i = 0; i < number_races; i++)
    race_list[i]->add_message(mt, m);
}



void stars_map::log_all_messages(void)
{
  const message* msg = logmsgs.first();

  for (; msg; msg = msg->next)
    if (!msg->filtered())
      log(msg->msg + "\n");
}



hull* stars_map::create_hull(const myString& hn)
{
  hull* h = new hull(hn);

  h->next = ship_hulls;
  ship_hulls = h;

  return h;
}



hull* stars_map::find_hull(const myString& hn)
{
  hull* h;

  for (h = ship_hulls; h; h = h->next)
    if (h->name == hn)
      return h;

  return NULL;
}



engine* stars_map::create_engine(const myString& en)
{
  engine* e = new engine(en);

  e->next = ship_engines;
  ship_engines = e;

  return e;
}



engine* stars_map::find_engine(const myString& en)
{
  engine* e;

  for (e = ship_engines; e; e = e->next)
    if (e->name == en)
      return e;

  return NULL;
}



void stars_map::add_fleet(fleet* f, const int source)
{
  // parse the fleet name
  int ownerid;
  int owner = -1;
  unsigned int ownernlen = 0;
  fleet* df;
  fleet* of;
  myString msg;

  // try to guess the owner.....
  for (ownerid = 0; ownerid < number_races; ownerid++)
    if ( (0 == f->_starsname.index(race_list[ownerid]->_name))
	 && (race_list[ownerid]->_name.length() > ownernlen) ) {
      owner = ownerid;
      ownernlen = race_list[ownerid]->_name.length();
    }

  if (owner == -1) {
    char str[512];
    sprintf(str, "Can't understand owner of fleet '%s'", (const char*)f->_starsname);
    yyerror(str);
  }

  // we have owner, try to see if we have stars id number
  f->_owner = race_list[owner];

  myString fn = f->_starsname.after((int)ownernlen);

  // look for a #[0-9]+ at the end
  const char* p = (const char*)fn + fn.length() - 1;

  while (p > (const char*)fn && isdigit(*p))
    p--;

  if (p > (const char*)fn && *p == '#') {
    // ok, got the number
    sscanf(p+1, "%d", &f->stars_id);

    p--; // skip # and blanks before it
    while (p > (const char*)fn && isspace(*p))
      p--;

    f->_name = fn.before(p - (const char*)fn + 1);

    // if source == owner then it's not an enemy fleet...
    if (source == owner)
      f->enemy = false;

    // initial scan for duplicates, with owner & id we will get it
    for (of = NULL, df = f->_owner->fleet_table; df; of = df, df = df->rnext) {

      if (f->stars_id == df->stars_id) {
	// we have duplicate, if source == owner we prefer source
	msg = "Duplicate fleet " + f->_starsname + ", was " + df->_starsname;

	// check consistency
	if (f->_mass != df->_mass)
	  msg += " (mass is non-consistent)";
	if (f->numships[0] != df->numships[0])
	  msg += " (number of ships is non-consistent)";
	if (f->pos[0] != df->pos[0])
	  msg += " (position is non-consistent)";

	if (!f->enemy) {
	  // non-enemy fleets are given priority (if it's not
	  // enemy's than it's yours and you have more info)

	  msg += " old replaced";

	  // replace existing fleet
	  f->rnext = df->rnext;

	  if (of)
	    of->rnext = f;
	  else
	    f->_owner->fleet_table = f;

	  delete df;

	} else {
	  msg += " old kept";

	  // trash current fleet
	  delete f;
	}

	f->_owner->add_message(RLO_FLEETDUP, msg);

	break;
      }
    }

    if (!df) {
      // no duplicate, add to race list
      f->rnext = f->_owner->fleet_table;
      f->_owner->fleet_table = f;
    }

  } else {
    // unable to parse name, problems will arise?
    // we must check position/mass/ships, probably....
    log("Unable to parse fleet name " + f->_starsname + "\n");

    // add to race list
    f->rnext = f->_owner->fleet_table;
    f->_owner->fleet_table = f;
  }
}



race* stars_map::find_race(const myString& n)
{
  int i;

  if (!n.length())
    return NULL; // = uninhabited

  for (i = 0; i < number_races; i++)
    if (race_list[i]->_name == n)
      return race_list[i];

  if (fully_visual)
    display->error_dialog(myString("Request for non-existent race ") + n + " done");
  else
    fprintf(stderr, "Request for non-existent race %s done\n", (const char*)n);

  exit(-1);
  return NULL;
}



race* stars_map::find_race(const int id) const
{
  int rid = id;
  while (rid < 0)
    rid += number_races;
  while (rid >= number_races)
    rid -= number_races;

  race* r = race_list[rid];

  return r;
}



void stars_map::create_alliance(const myString& n)
{
  cur_alliance = -1;
  cur_alliance_name = n;
}


bool stars_map::add_to_alliance(const myString& rn)
{
  race* r;

  if ( !(r = find_race(rn)) )
    yyerror("Unknown race specified in alliance");

  if (cur_alliance == -1) {
    cur_alliance = r->id;
    alliance_names[cur_alliance] = cur_alliance_name;
  }

  race_alliances[r->id] = cur_alliance;
  return true;
}



bool stars_map::are_allies(const race* r1, const race* r2)
{
  if (race_alliances[r1->id] == race_alliances[r2->id])
    return true;
  else
    return false;
}



extern FILE* yyin;
extern myString infile_name;


bool stars_map::read_smf_file(const myString& name)
{
  if ( !(yyin = fopen((const char*)name, "r")) )
    return false;

  infile_name = name;

  fprintf(report_log, "************* Reading data from %s *************\n\n",
	  (const char*)name);
  if (do_display)
    display->set_intro_loadingfile("Loading file: " + name);

  yyparse();

  fclose(yyin);
  if (do_display)
    display->set_intro_loadingfile("Loading completed.");

  // set simulation parameters
  parameter* p;

  p = get_parameter(myString("min_mineral_move"));
  PARmin_mineral_move = (p)? (int)(*p) : 250;
  p = get_parameter(myString("max_search_distance"));
  PARmax_search_distance = (p)? (int)(*p) : 243;
  p = get_parameter(myString("min_pop_for_scanner"));
  PARmin_pop_for_scanner = (p)? (int)(*p) : 150000;

  fprintf(report_log, "\n\n");

  return true;
}

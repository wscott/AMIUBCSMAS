#include "starana-classes.h"



extern void restart_flex(FILE* f);

planet_view* planet_view::planet_view_table = NULL;
fleet_view* fleet_view::fleet_view_table = NULL;



map_view::map_view(stars_map* m) : 
                   xmap0(0), ymap0(0), _when(0), 
                   map(m), space_mode(MAP_BLACK), do_alliances(false),
		   pview(NULL), cur_pf(0), fview(NULL),
		   scanner_eff(100),
		   race_viewpoint(NULL), curr_planet(NULL),
                   x0(0), y0(0), xw(600), yw(600)
{
  // nothing to do right now
}



void map_view::initialize(void)
{
  _zoom = map->max_zoom;
  gmsc = (1024 * 1024 / map->gmscale) >> (_zoom - 1);
}



void map_view::reset(void)
{
  xmap0 = ymap0 = 0;
  _zoom = map->max_zoom;
  gmsc = (1024 * 1024 / map->gmscale) >> (_zoom - 1);
}



int map_view::when(const int w)
{
  if (w != MW_READ) {
    if (w == MW_NEXT)
      _when++;
    else if (w == MW_PREV)
      _when--;
    else _when = w;

    if (_when < 0)
      _when = 0;
    if (_when >= map->actual_sim_future)
      _when = map->actual_sim_future - 1;
  }

  return _when;
}


int map_view::zoom(const int z)
{
  if (z != MW_READ) {
    if (z == MW_NEXT)
      _zoom--;
    else if (z == MW_PREV)
      _zoom++;
    else
      _zoom = z;

    if (_zoom <= 0)
      _zoom = 1;
    if (_zoom > map->max_zoom)
      _zoom = map->max_zoom;

    gmsc = (1024 * 1024 / map->gmscale) >> (_zoom - 1);
  }

  // this will fix bounds for zoom-out
  xtranslate(0);
  ytranslate(0);

  return _zoom;
}


int map_view::good_move(void)
{
  return 256 / (1 << (map->max_zoom - _zoom));
}



int map_view::xtranslate(const int dx)
{
  xmap0 += dx;

  if (xmap0 < 0)
    xmap0 = 0;
  if (xmap0 > (xw * (1 << (map->max_zoom - _zoom)) - xw))
    xmap0 = xw * (1 << (map->max_zoom - _zoom)) - xw;

  return xmap0;
}



int map_view::ytranslate(const int dy)
{
  ymap0 += dy;

  if (ymap0 < 0)
    ymap0 = 0;
  if (ymap0 > (yw * (1 << (map->max_zoom - _zoom)) - yw))
    ymap0 = yw * (1 << (map->max_zoom - _zoom)) - yw;

  return ymap0;
}



const char* map_view::maptype_name(void) const
{
  switch(space_mode) {
  case MAP_BLACK:
    return "Black";

  case MAP_OWNERS:
    return "Controlled space";
  }

  return ""; // bah....
}



int map_view::set_maptype(const int mt)
{
  if (mt != MW_READ)
    if (mt >= MAP_BLACK && mt <= MAP_OWNERS)
      space_mode = mt;

  return space_mode;
}



planet* map_view::set_active_planet(const _xypoint& physpos)
{
  curr_planet = map->find_planet(display_to_map(physpos));

  if (!curr_planet)
    curr_planet = map->unsorted_ptable;

  return curr_planet;
}



bool map_view::import_planet_views(const String& fn)
{
  FILE* f;

  if ( (f = fopen((const char*)fn, "r")) ) {
    infile_name = fn;
    restart_flex(f);
    yyparse();
    fclose(f);
    return true;
  }

  return false;
}



bool map_view::save_planet_views(const String& fn)
{
  FILE* f;

  if ( (f = fopen((const char*)fn, "w")) ) {
    for (planet_view* pv = planet_view::planet_view_table; pv; pv = pv->next)
      pv->export(f);

    fclose(f);
    return true;
  }

  return false;
}



bool map_view::set_alliances(const int b)
{
  if (b != MW_READ)
    if (b == MW_PREV || b == MW_NEXT)
      do_alliances = !do_alliances;
    else
      do_alliances = (b == 1);

  return do_alliances;
}


int map_view::set_scanner_eff(const int e)
{
  if (e != MW_READ) {
    if (e == MW_PREV)
      scanner_eff -= 10;
    else if (e == MW_NEXT)
      scanner_eff += 10;
    else
      scanner_eff = e;

    if (scanner_eff < 2)
      scanner_eff = 2;
    if (scanner_eff > 100)
      scanner_eff = 100;
  }

  return scanner_eff;
}



int map_view::calc_radius(const double& v,
			   const double& vmin, const double& vmax)
{
  double t = v;

  if (t < vmin)
    t = vmin;
  if (t > vmax)
    t = vmax;

  t = (t - vmin) / (vmax - vmin);
  t = pow(t + 0.005, 0.5);

  int r = (int)(4 * MAX_RADIUS * t + 0.5);

  if (r <= 0)
    r = 1;
  if (r > MAX_RADIUS * 4)
    r = MAX_RADIUS * 4;

  return r;
}



void map_view::draw_object(object_display* pd, const int stage)
{
  int i, t;
  _xypoint ldir, tickdir, tp, tp1, tp2;
  int ldirmod, td, real_ft, real_ts;

  // stage indicates WHAT to draw, 16 are defined
  switch(stage) {
  case 0: // circle 0
  case 1: // circle 1
  case 2: // circle 2
  case 3: // circle 3
    if (pd->n_circles > stage) {
      // radius is given in map units, adjust
      i = map_to_display(pd->circles[stage].radius);

      display->draw_circle(pd->xy, i, pd->circles[stage].color, 
			   pd->circles[stage].fillcolor);
    }
    break;

  case 4: // lines
    for (i = 0; i < pd->n_lines; i++) {
      _lineto& ld = pd->linedest[i];

      display->draw_line(pd->xy, ld.dp, ld.color);

      // draw ticks
      if (ld.first_tick && ld.tick_sep) {
	ldir = ld.dp - pd->xy;
	ldirmod = (int)sqrt(ldir.x*ldir.x + ldir.y*ldir.y);

	if (ldirmod == 0)
	  continue; // idiots, they deserved a divide by 0, but I'm good

	// convert tick distances from map to display space (*1024)
	real_ft = ld.first_tick * gmsc;
	real_ts = ld.tick_sep * gmsc;

	tickdir = ldir * 4 / ldirmod;
	t = tickdir.x;
	tickdir.x = tickdir.y;
	tickdir.y = -t; // orthogonal to line

	for (td = real_ft; td <= ldirmod*1024; td += real_ts) {
	  tp = pd->xy + ldir * td / ldirmod / 1024; // tick position
	  tp1 = tp + tickdir;
	  tp2 = tp - tickdir;

	  display->draw_line(tp1, tp2, ld.color);
	}
      }
    }
    break;
  
  case 5: // data
    if (pd->n_values > 0) {
      int r = 0;

      if (pd->n_values == 1) { // single-value display
	r = calc_radius(pd->values[0].value, pd->vmin, pd->vmax);

	if (pd->pie_type == PIE_TRIANG)
	  display->draw_triangle_pie(pd->xy, pd->pie_dir, r, pd->values[0].color);
	else
	  display->draw_fat_circle_arc(pd->xy.x, pd->xy.y, r, pd->values[0].color);

      } else { // multi-valued pie chart
	double t, max, cv[16], total;
	double tnow;
	int thetanow, thetanext;

	for (i = 0, total = 0, max = -1; i < pd->n_values; i++) {
	  t = pd->values[i].value;

	  if (t < pd->vmin)
	    t = pd->vmin;
	  if (t > pd->vmax)
	    t = pd->vmax;

	  if (t > max)
	    max = t;

	  cv[i] = t;
	  total += t;
	}

	if (total == 0) // idiots...they deserve to get nothing, but I'm good
	  display->draw_marker(pd->xy.x, pd->xy.y, MT_TWODOTS, COL_GREY + 1);
      
	else {
	  // choose the max for radius
	  if (pd->value == -1e30)
	    r = calc_radius(max, pd->vmin, pd->vmax);
	  else
	    r = calc_radius(pd->value, pd->vmin, pd->vmax);

	  // now display the pie
	  for (i = 0, thetanow = 0, tnow = 0.0; i < pd->n_values; i++) {
	    tnow += cv[i];
	    thetanext = (int)(360 * 64 * tnow / total + 0.5);

	    if (pd->pie_type == PIE_TRIANG)
	      display->draw_triangle_pie(pd->xy, pd->pie_dir, r, pd->values[i].color,
					 thetanow, thetanext - thetanow);
	    else
	      display->draw_fat_circle_arc(pd->xy.x, pd->xy.y, r, pd->values[i].color,
					   thetanow, thetanext - thetanow);

	    thetanow = thetanext;
	  }
	}
      }

      // move "object" down to avoid clobbering marker with name
      pd->nameyshift = r / 4;
    }
    break;

  case 6: // marker
    if (pd->marker_type) {
      display->draw_marker(pd->xy.x, pd->xy.y, pd->marker_type, pd->marker_color);

      // shift down for markers?
      // pyshift = ??
    }
    break;

  case 7: // name
    // draw the planet name
    if (pd->name_color)
      display->draw_planetname(pd->xy.x, pd->xy.y + pd->nameyshift,
			       pd->name_color, pd->name);
  }
}



void map_view::set_viewpoint(race* r)
{
  if (r) {
    race_viewpoint = r;

  } else {
    int i = (race_viewpoint)? race_viewpoint->id : -1;
    i++;
    if (i == map->number_races)
      i = 0;

    race_viewpoint = map->race_list[i];
  }
}


_xypoint map_view::map_to_display(const _xypoint& xyin) const
{
  _xypoint xy;
  xy.x = (xyin.x - map->xmin) * gmsc / 1024 - xmap0 + x0;
  xy.y = (xyin.y - map->ymin) * gmsc / 1024 - ymap0 + y0;
  xy.y = yw - 1 - xy.y;

  return xy;
}



_xypoint map_view::display_to_map(const _xypoint& xyin) const
{
  _xypoint xy;
  xy.x = (xyin.x - x0 + xmap0) * 1024 / gmsc + map->xmin;
  xy.y = yw - 1 - xyin.y;
  xy.y = (xy.y - y0 + ymap0) * 1024 / gmsc + map->ymin;

  if (xy.x < map->xmin)
    xy.x = map->xmin;
  else if (xy.x > map->xmax)
    xy.x = map->xmax;

  if (xy.y < map->ymin)
    xy.y = map->ymin;
  else if (xy.y > map->ymax)
    xy.y = map->ymax;

  return xy;
}



int map_view::map_to_display(const int r) const
{
  return r * gmsc / 1024;
}



void map_view::set_window_title(void) const
{
  display->set_window_title(map->name() +
			    " (" + race_viewpoint->name() + ") " +
			    pview->name);
}



void map_view::display_space(void)
{
  int ym, yg;

  if (space_mode == MAP_BLACK) {
    // do nothing

  } else {
    for (ym = ymap0, yg = y0 + yw - 1; ym < map->base_res && yg >= y0; ym+=(1 <<(_zoom-1)), yg--)
    if (ym >= 0) {
      if (map->row_lengths[ym] == -1)
	map->line_ownership(ym);

      if (!do_alliances) // OWNERS
	display->draw_owners(yg, x0, xmap0, xw, _zoom,
			     map->row_lengths[ym], map->row_owners[ym], map->row_posits[ym], NULL);
      else // ALLIANCES
	display->draw_owners(yg, x0, xmap0, xw, _zoom,
			     map->row_lengths[ym], map->row_owners[ym], map->row_posits[ym],
			     map->race_alliances);

    }
  }

  display->done();
}



void map_view::set_planet_display(void)
{
  planet* p;
  int pfi;

  // now generate display part and draw markers
  for (p = map->unsorted_ptable; p; p = p->next) {
    // reset the planetary display
    object_display& pd = p->disp;

    pd.reset();
    // where will we draw it?
    pd.xy = map_to_display(p->position());

    // we can't do clipping since circles * lines are non-local
    //    if (pd.xy.x >= x0 && pd.xy.x < (x0+xw) && pd.xy.y >= y0 && pd.xy.y < (y0+yw))
    for (pfi = 0; pfi < MAX_PLA_MODES; pfi++) {
      pf_operation& po = pview->pla_modes[pfi];

      if (po.f) {
	if (po.mode == PF_STOMP ||
	    (po.mode == PF_AND &&
	     ( (po.modemask & PF_DATA && pd.data_defined()) ||
	       (po.modemask & PF_MARKER && pd.marker_defined()) ||
	       (po.modemask & PF_FLAG && pd.flag_defined()) ||
	       (po.modemask & PF_CIRCLES && pd.circles_defined()) ||
	       (po.modemask & PF_LINES && pd.lines_defined()) ||
	       (po.modemask & PF_NAME && pd.name_defined()) )) ||
	    (po.mode == PF_OR &&
	     ( (!(po.modemask & PF_DATA) || !pd.data_defined()) &&
	       (!(po.modemask & PF_MARKER) || !pd.marker_defined()) &&
	       (!(po.modemask & PF_FLAG) || !pd.flag_defined()) &&
	       (!(po.modemask & PF_CIRCLES) || !pd.circles_defined()) &&
	       (!(po.modemask & PF_LINES) || !pd.lines_defined()) &&
	       (!(po.modemask & PF_NAME) || !pd.name_defined()) )) )
	  po.f->function(*this, p, po.params, _when);
      }
    }
  }
}



void map_view::set_fleet_display(void)
{
  // for the moment use a hardwired display of triangle of player color + path
  fleet* f;
  race* vp;
  int i;

  for (i = 0; i < map->number_of_players(); i++) {
    vp = map->find_race(i);

    for (f = vp->fleet_table; f; f = f->rnext) {
      object_display& fd = f->disp;

      fd.reset();

      if (fview) {
	// where will we draw it?
	fd.xy = map_to_display(f->position(_when));

	// set triangle
	fd.pie_type = PIE_TRIANG;
	fd.values[0].value = 1.0;
	fd.vmin = 0.0;
	fd.vmax = 1.0;

	// color
	if ( vp == race_viewpoint || (do_alliances && map->are_allies(vp, race_viewpoint)) )
	  fd.values[0].color = COL_IRON;
	else
	  fd.values[0].color = COL_REDHAB;

	fd.n_values++;

	// direction vector
	if (_when <= f->eta && f->warp) {
	  fd.linedest[0].dp = map_to_display(f->position(map->sim_future()));

	  fd.pie_dir = f->position(map->sim_future()) - f->position(_when);

	  if (fd.pie_dir == _xypoint(0, 0)) // needed at sim limit
	    fd.pie_dir = f->position(_when) + _xypoint(100, 60);

	  if ( vp == race_viewpoint || (do_alliances && map->are_allies(vp, race_viewpoint)) )
	    fd.linedest[0].color = COL_IRON + 2;
	  else
	    fd.linedest[0].color = COL_GREY + 2;

	  if (f->warp <= 10)
	    fd.linedest[0].first_tick = fd.linedest[0].tick_sep = f->warp*f->warp;
	  else {
	    fd.linedest[0].first_tick = fd.linedest[0].tick_sep = 0;
	    // change color to indicate gating
	    fd.linedest[0].color = COL_YELLOWHAB + 1;
	  }

	  fd.n_lines++;
	} else
	  fd.pie_dir = f->position(_when) + _xypoint(100, 60);

	// scanning (for vpoint & allies)
	

	if ((do_alliances && map->are_allies(f->_owner, race_viewpoint)) ||
	    (race_viewpoint == f->_owner)) {
	  fd.circles[0].radius = set_scanner_eff(MW_READ) * f->scan_normal / 100;
	  fd.circles[0].color = -1;
	  fd.circles[0].fillcolor = COL_SCAN;
	  fd.circles[1].radius = set_scanner_eff(MW_READ) * f->scan_pen / 100;
	  fd.circles[1].color = -1;
	  fd.circles[1].fillcolor = COL_PENSCAN;
	  fd.n_circles = 2;
	}

	fd.name = f->_name;
	fd.name_color = COL_RACES + f->_owner->race_id() * 4;
      }
    }
  }
}



void map_view::display_objects(void)
{
  int s, i;
  planet* p;
  fleet* f;
  race* vp;

  // draw the objects
  for (s = 0; s < 8; s++) {
    for (p = map->unsorted_ptable; p; p = p->next)
      draw_object(&p->disp, s);

    for (i = 0; i < map->number_of_players(); i++) {
      vp = map->find_race(i);

      for (f = vp->fleet_table; f; f = f->rnext)
	  draw_object(&f->disp, s);
    }
  }

  display->done();
}



void map_view::display_racenames(const int xp, const int yp)
{
  int i;
  String rn;
  char str[256];

  for (i = 0; i < map->number_races; i++) {
    rn = map->race_list[i]->_name;

    if (do_alliances)
      display->draw_string(xp, yp + 26 * i, COL_RACES + 4 * map->race_alliances[i], (const char*)rn);
    else
      display->draw_string(xp, yp + 26 * i, COL_RACES + 4 * i, (const char*)rn);

    sprintf(str, "%3d (%2.2f) / %5d (%2.2f)", 
	    map->race_planets[i], 
	    100.0 * (float)(map->race_planets[i]) / map->total_planets,
	    map->race_surface[i], 
	    100.0 * (float)(map->race_surface[i]) / map->surface);
    display->draw_string(xp, yp + 26 * i + 10, COL_WHITE, str);
  }
}



void map_view::clone_planet_view(planet_view* orig)
{
  if (!orig)
    pview = new planet_view("Default planet display");
  else {
    pview = new planet_view(*pview); // clone
  }
}



int map_view::select_planet_view(const int i)
{
  int j;

  if (i == MW_READ) {

  } else if (i == MW_NEXT) {
    if (pview->next)
      pview = pview->next;

  } else {
    if (i == MW_PREV)
      j = get_planet_view_index() - 1;
    else
      j = i;
  
    planet_view* opv;
    for (opv = pview = planet_view::planet_view_table;
	 j > 0 && pview;
	 opv = pview, pview = pview->next, j--);

    if (!pview)
      pview = opv;
  }

  return get_planet_view_index();
}



void map_view::select_fleet_view(const int i)
{
  if (i == 0)
    fview = NULL;
  else
    fview = (fleet_view*)pview;
}



int map_view::get_planet_view_index(void) const
{
  planet_view* pv;
  int i;
  
  for (i = 0, pv = planet_view::planet_view_table; pv; pv = pv->next, i++)
    if (pv == pview)
      break;

  if (!pv)
    return -1;
  else
    return i;
}



planet_view* map_view::extract_pview(const int i)
{
  planet_view* pv = NULL;

  if (i == 0) {
    if ( (planet_view::planet_view_table->next) ) {
      pv = planet_view::planet_view_table;
      pview = planet_view::planet_view_table = pv->next;
      pv->next = NULL;
    }
  } else {
    int j = i - 1;
    planet_view* pvt;

    for (pvt = planet_view::planet_view_table; pvt && j; pvt = pvt->next, j--);

    if (pvt && pvt->next) {
      pv = pvt->next;
      pvt->next = pv->next;
      pview = ((pvt->next)? pvt->next : pvt);
      pv->next = NULL;
    }
  }

  return pv;
}


void map_view::delete_planet_view(const int i)
{
  planet_view* pv = extract_pview(i);

  delete pv;
}


void map_view::move_planet_view(const int i, const int dir)
{
  planet_view* pv;
  planet_view* pvt;
  int j;

  pv = extract_pview(i);

  if (pv) {
    pview = pv;

    j = i - 1 + dir;

    if (j < 0) {
      pv->next = planet_view::planet_view_table;
      planet_view::planet_view_table = pv;
    } else {
      for (pvt = planet_view::planet_view_table; pvt->next && j; pvt = pvt->next, j--);

      pv->next = pvt->next;
      pvt->next = pv;
    }
  }
}


// management of planet_view
planet_view::planet_view(const String& n) : name(n), next(NULL)
{
  link();
  clear();
}



void planet_view::link(void)
{
  if (planet_view_table) {
    planet_view* pv;
    for (pv = planet_view_table; pv->next; pv = pv->next);
    pv->next = this;
  } else
    planet_view_table = this;
}



planet_view::planet_view(const planet_view& pv) : name(pv.name)
{
  link();

  for (int i = 0; i < MAX_PLA_MODES; i++)
    pla_modes[i] = pv.pla_modes[i];
}



void planet_view::export(FILE* f)
{
  int i;

  fprintf(f, "planet_view \"%s\" {\n", name.chars());

  for (i = 0; i < MAX_PLA_MODES; i++) {
    const pf_operation& po = pla_modes[i];
    char modemask[16];

    if (po.f->name() == "- (nothing) -")
      continue;

    // build up the mask string
    modemask[0] = 0;
    if (po.modemask & PF_CIRCLES)
      strcat(modemask, "C");
    if (po.modemask & PF_LINES)
      strcat(modemask, "L");
    if (po.modemask & PF_DATA)
      strcat(modemask, "D");
    if (po.modemask & PF_MARKER)
      strcat(modemask, "M");
    if (po.modemask & PF_NAME)
      strcat(modemask, "N");
    if (po.modemask & PF_FLAG)
      strcat(modemask, "F");

    // write out the spec
    fprintf(f, "\t%d \"%s\" %d \"%s\" %d %d %d %d %d\n", i, (const char*)po.f->name(),
	    (int)po.mode, modemask, po.params[0], po.params[1], po.params[2],
	    po.params[3], po.params[4]);
  }

  fprintf(f, "}\n");
}



int map_view::select_plamode(const int pm)
{
  if (pm != MW_READ) {
    if (pm == MW_NEXT)
      cur_pf++;
   else if (pm == MW_PREV)
      cur_pf--;
    else
      cur_pf = pm;

    if (cur_pf < 0)
      cur_pf = 0;
    else if (cur_pf >= MAX_PLA_MODES)
      cur_pf = MAX_PLA_MODES - 1;
  }

  return cur_pf;
}



void map_view::insert_plamode(void)
{
  int i;

  // copy from MAX_PLA_MODES-1...cur_pf into cur_pf
  for (i = MAX_PLA_MODES-1; i > cur_pf; i--)
    pview->pla_modes[i] = pview->pla_modes[i-1];

  // clear current
  pview->pla_modes[cur_pf].clear();
}



void map_view::delete_plamode(void)
{
  int i;

  // copy from cur_pf+1...MAX_PLA_MODES into cur_pf
  for (i = cur_pf+1; i < MAX_PLA_MODES; i++)
    pview->pla_modes[i-1] = pview->pla_modes[i];

  // put a nothing at the end
  pview->pla_modes[MAX_PLA_MODES-1].clear();
}




const pf_operation& map_view::get_plamode(const int i = -1) const
{
  if (i >= 0 && i < MAX_PLA_MODES)
    return pview->pla_modes[i];
  else
    return pview->pla_modes[cur_pf];
}



void map_view::set_plamode(const String& pmn,
			   const _pfmode pfm, const int pfmsk,
			   const int* par)
{
  pf_operation& po = pview->pla_modes[cur_pf];

  // change of function type
  if (pmn.length())
    if (pmn == "+") {
      po.f = get_next_pfunction(po.f);
      
    } else if (pmn == "-") {
      po.f = get_prev_pfunction(po.f);
      
    } else
      po.f = find_pfunction(pmn);

  if (!po.f)
    po.f = find_pfunction("- (nothing) -");

  if (po.f) {
    // change of function mode
    if (pfm == PF_NEXT)
      po.mode = (_pfmode)((int)po.mode + 1);
    else if (pfm == PF_PREV)
      po.mode = (_pfmode)((int)po.mode - 1);
    else if (pfm != PF_NULL)
      po.mode = pfm;

    if (po.mode < PF_SKIP)
      po.mode = PF_OR;
    if (po.mode > PF_OR)
      po.mode = PF_SKIP;
  }

  // change of mode mask
  po.modemask = pfmsk;

  // setting of parameters
  if (par)
    memcpy(po.params, par, 16 * sizeof(int));
}



void planet_view::clear(void)
{
  int i;

  for (i = 0; i < MAX_PLA_MODES; i++)
    pla_modes[i].clear();
}

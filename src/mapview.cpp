#include "starana-classes.h"



extern void restart_flex(FILE* f);


map_view::map_view(stars_map* m) : 
                   xmap0(0), ymap0(0), _when(0), 
                   map(m), space_mode(MAP_BLACK), do_alliances(false),
		   planet_views(), pview(0), cur_pf(0),
		   fleet_views(), fview(0), cur_ff(0),
		   scanner_eff(100),
		   race_viewpoint(NULL),
                   x0(0), y0(0), xw(600), yw(600)
{
  for (int i = 0; i < 4; i++)
    curr_planet[i] = NULL;
}



void map_view::initialize(void)
{
  // get resolution from map object
  xw = yw = map->view_res;

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



planet* map_view::set_active_planet(const _xypoint& physpos, int pn = 0)
{
  if (pn < 0 || pn > 3)
    pn = 0;

  curr_planet[pn] = map->find_planet(display_to_map(physpos));

  if (!curr_planet[pn])
    curr_planet[pn] = map->unsorted_ptable;

  return curr_planet[pn];
}


planet* map_view::get_active_planet(const int pn = 0) const
{
  if (pn < 0 || pn > 3)
    return curr_planet[0];
  else
    return curr_planet[pn];
}



/* planet views */


void map_view::clone_planet_view(planet_view* orig)
{
  planet_view* pv;

  if (!orig)
    pv = new planet_view("Default planet display");
  else {
    pv = new planet_view(*orig); // clone
  }

  planet_views.push_back(pv);
  pview = planet_views.size() - 1;
}



int map_view::select_planet_view(const int i)
{
  if (i == MW_READ) {
    // do nothing
  } else if (i == MW_NEXT)
    pview++;
  else if (i == MW_PREV)
    pview--;
  else
    pview = i;

  if (pview > planet_views.size() - 1)
    pview = planet_views.size() - 1;
  if (pview < 0)
    pview = 0;

  return pview;
}



planet_view* map_view::get_planet_view(const int i = -1) const
{
  if (i < 0)
    return planet_views[pview];
  else if (i < (int)planet_views.size())
    return planet_views[i];
  
  return NULL;
}



void map_view::delete_planet_view(const int i)
{
  if (i > 0 && i < (int)planet_views.size()) {
     planet_views.erase(planet_views.begin() + i);
     if (pview > planet_views.size() - 1)
       pview = planet_views.size() - 1;
  }
}


void map_view::move_planet_view(const int i, const int dir)
{
  if (dir == 1 && i < (int)planet_views.size()-1) {
    planet_view* pv = planet_views[i];
    planet_views[i] = planet_views[i+1];
    planet_views[i+1] = pv;

  } else if (dir == -1 && i > 0) {
    planet_view* pv = planet_views[i];
    planet_views[i] = planet_views[i-1];
    planet_views[i-1] = pv;
  }
}


bool map_view::import_planet_views(const myString& fn)
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


bool map_view::save_planet_views(const myString& fn)
{
  FILE* f;
  int i;

  if ( (f = fopen((const char*)fn, "w")) ) {
    for (i = 0; i < (int)planet_views.size(); i++)
      planet_views[i]->export(f);

    fclose(f);
    return true;
  }

  return false;
}


/* modes within a view */

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
    else if (cur_pf >= MAX_DISP_MODES)
      cur_pf = MAX_DISP_MODES - 1;
  }

  return cur_pf;
}


void map_view::insert_plamode(void)
{
  int i;

  // copy from MAX_DISP_MODES-1...cur_pf into cur_pf
  for (i = MAX_DISP_MODES-1; i > cur_pf; i--)
    planet_views[pview]->pla_modes[i] = planet_views[pview]->pla_modes[i-1];

  // clear current
  planet_views[pview]->pla_modes[pview].clear();
}


void map_view::delete_plamode(void)
{
  int i;

  // copy from cur_pf+1...MAX_DISP_MODES into cur_pf
  for (i = cur_pf+1; i < MAX_DISP_MODES; i++)
    planet_views[pview]->pla_modes[i-1] = planet_views[pview]->pla_modes[i];

  // put a nothing at the end
  planet_views[pview]->pla_modes[MAX_DISP_MODES-1].clear();
}


const pf_operation& map_view::get_plamode(const int i = -1) const
{
  if (i >= 0 && i < MAX_DISP_MODES)
    return planet_views[pview]->pla_modes[i];
  else
    return planet_views[pview]->pla_modes[cur_pf];
}


void map_view::set_plamode(const myString& pmn,
			   const _dfmode pfm, const int pfmsk,
			   const int* par)
{
  pf_operation& po = planet_views[pview]->pla_modes[cur_pf];

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
      po.mode = (_dfmode)((int)po.mode + 1);
    else if (pfm == PF_PREV)
      po.mode = (_dfmode)((int)po.mode - 1);
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



/* fleet views */


void map_view::clone_fleet_view(fleet_view* orig)
{
  fleet_view* fv;

  if (!orig)
    fv = new fleet_view("Default fleet display");
  else {
    fv = new fleet_view(*orig); // clone
  }

  fleet_views.push_back(fv);
  fview = fleet_views.size() - 1;
}



int map_view::select_fleet_view(const int i)
{
  if (i == MW_READ) {
    // do nothing
  } else if (i == MW_NEXT)
    fview++;
  else if (i == MW_PREV)
    fview--;
  else
    fview = i;

  if (fview > fleet_views.size() - 1)
    fview = fleet_views.size() - 1;
  if (fview < 0)
    fview = 0;

  return fview;
}



void map_view::delete_fleet_view(const int i)
{
  if (i > 0 && i < (int)fleet_views.size()) {
    fleet_views.erase(fleet_views.begin() + i);
    if (fview > fleet_views.size() - 1)
      fview = fleet_views.size() - 1;
  }
}


void map_view::move_fleet_view(const int i, const int dir)
{
  if (dir == 1 && i < (int)fleet_views.size()-1) {
    fleet_view* fv = fleet_views[i];
    fleet_views[i] = fleet_views[i+1];
    fleet_views[i+1] = fv;

  } else if (dir == -1 && i > 0) {
    fleet_view* fv = fleet_views[i];
    fleet_views[i] = fleet_views[i-1];
    fleet_views[i-1] = fv;
  }
}



bool map_view::import_fleet_views(const myString& fn)
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



bool map_view::save_fleet_views(const myString& fn)
{
  FILE* f;
  int i;

  if ( (f = fopen((const char*)fn, "w")) ) {
    for (i = 0; i < (int)fleet_views.size(); i++)
      fleet_views[i]->export(f);

    fclose(f);
    return true;
  }

  return false;
}


fleet_view* map_view::get_fleet_view(const int i = -1) const
{
  if (i < 0)
    return fleet_views[fview];
  else if (i < (int)fleet_views.size())
    return fleet_views[i];

  return NULL;
}




int map_view::select_flemode(const int fm)
{
  if (fm != MW_READ) {
    if (fm == MW_NEXT)
      cur_ff++;
   else if (fm == MW_PREV)
      cur_ff--;
    else
      cur_ff = fm;

    if (cur_ff < 0)
      cur_ff = 0;
    else if (cur_ff >= MAX_DISP_MODES)
      cur_ff = MAX_DISP_MODES - 1;
  }

  return cur_ff;
}



void map_view::insert_flemode(void)
{
  int i;

  // copy from MAX_DISP_MODES-1...cur_pf into cur_pf
  for (i = MAX_DISP_MODES-1; i > cur_ff; i--)
    fleet_views[fview]->fle_modes[i] = fleet_views[fview]->fle_modes[i-1];

  // clear current
  fleet_views[fview]->fle_modes[fview].clear();
}


void map_view::delete_flemode(void)
{
  int i;

  // copy from cur_pf+1...MAX_DISP_MODES into cur_pf
  for (i = cur_ff+1; i < MAX_DISP_MODES; i++)
    fleet_views[fview]->fle_modes[i-1] = fleet_views[fview]->fle_modes[i];

  // put a nothing at the end
  fleet_views[fview]->fle_modes[MAX_DISP_MODES-1].clear();
}


const ff_operation& map_view::get_flemode(const int i = -1) const
{
  if (i >= 0 && i < MAX_DISP_MODES)
    return fleet_views[fview]->fle_modes[i];
  else
    return fleet_views[fview]->fle_modes[cur_ff];
}



void map_view::set_flemode(const myString& fmn,
			   const _dfmode ffm, const int ffmsk,
			   const int* par)
{
  ff_operation& fo = fleet_views[fview]->fle_modes[cur_ff];

  // change of function type
  if (fmn.length())
    if (fmn == "+") {
      fo.f = get_next_ffunction(fo.f);
      
    } else if (fmn == "-") {
      fo.f = get_prev_ffunction(fo.f);
      
    } else
      fo.f = find_ffunction(fmn);

  if (!fo.f)
    fo.f = find_ffunction("- (nothing) -");

  if (fo.f) {
    // change of function mode
    if (ffm == PF_NEXT)
      fo.mode = (_dfmode)((int)fo.mode + 1);
    else if (ffm == PF_PREV)
      fo.mode = (_dfmode)((int)fo.mode - 1);
    else if (ffm != PF_NULL)
      fo.mode = ffm;

    if (fo.mode < PF_SKIP)
      fo.mode = PF_OR;
    if (fo.mode > PF_OR)
      fo.mode = PF_SKIP;
  }

  // change of mode mask
  fo.modemask = ffmsk;

  // setting of parameters
  if (par)
    memcpy(fo.params, par, 16 * sizeof(int));
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
  _xypoint ldir, tickdirl, tickdirr, tp, tp1, tp2;
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

	tickdirl = ldir * 4 / ldirmod;
	t = tickdirl.x;
	tickdirl.x = tickdirl.y;
	tickdirl.y = -t; // orthogonal to line
	tickdirr = -tickdirl;
	tickdirl += ldir * (-ld.tickdev)/ ldirmod;
	tickdirr += ldir * (-ld.tickdev)/ ldirmod;

	for (td = real_ft; td <= ldirmod*1024; td += real_ts) {
	  tp = pd->xy + ldir * td / ldirmod / 1024; // tick position
	  tp1 = tp + tickdirl;
	  tp2 = tp + tickdirr;

	  display->draw_line(tp, tp1, ld.color);
	  display->draw_line(tp, tp2, ld.color);
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

      // for pie charts we move name DOWN (assuming a planet)
      // for triangle pies we move it UP (assuming a fleet)
      if (pd->pie_type == PIE_TRIANG)
	pd->nameyshift -= r / 4 - 2;
      else
	pd->nameyshift += r / 4;
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
			    planet_views[pview]->name);
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
    for (pfi = 0; pfi < MAX_DISP_MODES; pfi++) {
      pf_operation& po = planet_views[pview]->pla_modes[pfi];

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
  fleet* f;
  int i, ffi;
  race* vp;

  // now generate display part and draw markers
  for (i = 0; i < map->number_of_players(); i++) {
    vp = map->find_race(i);

    for (f = vp->fleet_table; f; f = f->rnext) {
      // reset the object display
      object_display& fd = f->disp;

      fd.reset();
      // where will we draw it?
      fd.xy = map_to_display(f->position(_when));
      // default direction is fleet movement
      fd.pie_dir = f->position(game_map->sim_future()) - f->position(_when);

      // shift name upwards
      fd.nameyshift = -13;

      for (ffi = 0; ffi < MAX_DISP_MODES; ffi++) {
	ff_operation& fo = fleet_views[fview]->fle_modes[ffi];

	if (fo.f) {
	  if (fo.mode == PF_STOMP ||
	      (fo.mode == PF_AND &&
	       ( (fo.modemask & PF_DATA && fd.data_defined()) ||
		 (fo.modemask & PF_MARKER && fd.marker_defined()) ||
		 (fo.modemask & PF_FLAG && fd.flag_defined()) ||
		 (fo.modemask & PF_CIRCLES && fd.circles_defined()) ||
		 (fo.modemask & PF_LINES && fd.lines_defined()) ||
		 (fo.modemask & PF_NAME && fd.name_defined()) )) ||
	      (fo.mode == PF_OR &&
	       ( (!(fo.modemask & PF_DATA) || !fd.data_defined()) &&
		 (!(fo.modemask & PF_MARKER) || !fd.marker_defined()) &&
		 (!(fo.modemask & PF_FLAG) || !fd.flag_defined()) &&
		 (!(fo.modemask & PF_CIRCLES) || !fd.circles_defined()) &&
		 (!(fo.modemask & PF_LINES) || !fd.lines_defined()) &&
		 (!(fo.modemask & PF_NAME) || !fd.name_defined()) )) )
	    fo.f->function(*this, f, fo.params, _when);
	}
      }
    }
  }
}


/*
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
*/


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
  myString rn;
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



// management of planet_view
planet_view::planet_view(const myString& n) : name(n)
{
  clear();
}



planet_view::planet_view(const planet_view& pv) : name(pv.name)
{
  for (int i = 0; i < MAX_DISP_MODES; i++)
    pla_modes[i] = pv.pla_modes[i];
}



void planet_view::export(FILE* f)
{
  int i, j;

  fprintf(f, "planet_view \"%s\" {\n", name.chars());

  for (i = 0; i < MAX_DISP_MODES; i++) {
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
    fprintf(f, "\t%d \"%s\" %d \"%s\"", i, (const char*)po.f->name(),
	    (int)po.mode, modemask);

    for (j = 0; j < 16; j++)
      fprintf(f, " %d", po.params[j]);

    fprintf(f, "\n");
  }

  fprintf(f, "}\n");
}



void planet_view::clear(void)
{
  int i;

  for (i = 0; i < MAX_DISP_MODES; i++)
    pla_modes[i].clear();
}



// management of fleet_view
fleet_view::fleet_view(const myString& n) : name(n)
{
  clear();
}



fleet_view::fleet_view(const fleet_view& fv) : name(fv.name)
{
  for (int i = 0; i < MAX_DISP_MODES; i++)
    fle_modes[i] = fv.fle_modes[i];
}



void fleet_view::export(FILE* f)
{
  int i, j;

  fprintf(f, "fleet_view \"%s\" {\n", name.chars());

  for (i = 0; i < MAX_DISP_MODES; i++) {
    const ff_operation& fo = fle_modes[i];
    char modemask[16];

    if (fo.f->name() == "- (nothing) -")
      continue;

    // build up the mask string
    modemask[0] = 0;
    if (fo.modemask & PF_CIRCLES)
      strcat(modemask, "C");
    if (fo.modemask & PF_LINES)
      strcat(modemask, "L");
    if (fo.modemask & PF_DATA)
      strcat(modemask, "D");
    if (fo.modemask & PF_MARKER)
      strcat(modemask, "M");
    if (fo.modemask & PF_NAME)
      strcat(modemask, "N");
    if (fo.modemask & PF_FLAG)
      strcat(modemask, "F");

    // write out the spec
    fprintf(f, "\t%d \"%s\" %d \"%s\"", i, (const char*)fo.f->name(),
	    (int)fo.mode, modemask);

    for (j = 0; j < 16; j++)
      fprintf(f, " %d", fo.params[j]);

    fprintf(f, "\n");
  }

  fprintf(f, "}\n");
}



void fleet_view::clear(void)
{
  int i;

  for (i = 0; i < MAX_DISP_MODES; i++)
    fle_modes[i].clear();
}

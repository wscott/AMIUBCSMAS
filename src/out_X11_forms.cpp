#include "starana-classes.h"


extern char* xfpp(const myString& s);

// scale for minerals, -1->log, -2->multilin, >0 linear, 0 end
int minscales[] = { -1, -2, 1000, 2500, 5000, 10000, 30000, 0};

// ticks to put on scale
int minticks[][50] = { { 10, 20, 30, 40, 50, 60, 70, 80, 90, -100,
			       200, 300, 400, 500, 600, 700, 800, 900, -1000,
			       1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, -10000,
			       20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, -100000,
			       -1},
			     { 0, 100, 200, 300, 400, 500, 600, 700, 800, 900, -1000,
			       2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, -10000,
			       20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, -100000,
			       -1},
			     { 0, 50, 100, 150, -200, 250, 300, 350, -400, 450, 
			       500, 550, -600, 650, 700, 750, -800, 850, 900, -1000,
			       -1},
			     { 0, 100, 200, 300, 400, -500, 600, 700, 800, 900,
			       -1000, 1100, 1200, 1300, 1400, -1500, 1600, 1700, 1800, 1900,
			       -2000, 2100, 2200, 2300, 2400, -2500,
			       -1},
			     { 0, 250, 500, 750, -1000, 1250, 1500, 1750, -2000, 2250, 
			       2500, 2750, -3000, 3250, 3500, 3750, -4000, 4250, 4500, 4750, -5000,
			       -1},
			     { 0, 500, 1000, 1500, -2000, 2500, 3000, 3500, -4000, 4500, 
			       5000, 5500, -6000, 6500, 7000, 7500, -8000, 8500, 9000, 9500, -10000,
			       -1},
			     { 0, 2500, 5000, 7500, -10000,
			       12500, 15000, 17500, -20000,
			       22500, 25000, 27500, -30000,
			       -1} };



void graphics::error_dialog(const myString& msg)
{
  // remove any title screen
  wait_title_form();

  fl_show_message("", msg, "");
}


void graphics::set_intro_loadingfile(const myString& s)
{
  fl_set_object_label(xf_titl->statusmsg, s.c_str());
  XFlush(fl_get_display());
}


myString graphics::ask_for_smf_file(void)
{
  const char* fname;
  fname = fl_show_fselector("Select master file", "./", "*.smf", "");

  if (fname && fname[0])
    return fname;
  else
    return "";
}



void graphics::show_planetstatus(void)
{
  if ( !fl_form_is_visible(curr_ps->PlanetStatus) ) {
    char tstr[256];
    sprintf(tstr, "Planet Status #%d", curr_ps->statusnumber+1);

    fl_show_form(curr_ps->PlanetStatus, FL_PLACE_SIZE, FL_FULLBORDER, tstr);
    XFlush(fl_get_display());
  }
}



void graphics::hide_planetstatus(void)
{
  if ( fl_form_is_visible(curr_ps->PlanetStatus) )
    fl_hide_form(curr_ps->PlanetStatus);
}



void graphics::show_planetsimulation(void)
{
  if ( !fl_form_is_visible(curr_pm->PlanetSimulation) ) {
    fl_show_form(curr_pm->PlanetSimulation, FL_PLACE_SIZE, FL_FULLBORDER, "Planet Simulation");
    XFlush(fl_get_display());
  } else
    XRaiseWindow(x_display, curr_pm->PlanetSimulation->window);
}



void graphics::hide_planetsimulation(void)
{
  if ( fl_form_is_visible(curr_pm->PlanetSimulation) )
    fl_hide_form(curr_pm->PlanetSimulation);
}



void graphics::select_planetstatus(int pn)
{
  if (pn < 0 || pn > 1)
    pn = 0;

  curr_ps = xf_ps[pn];
  curr_pm = xf_pm[pn];
}



void graphics::select_planetstatus(FL_FORM* form, const int type)
{
  int i;

  for (i = 0; i < 2; i++)
    if ( (type == 0 && xf_ps[i]->PlanetStatus == form) ||
	 (type == 1 && xf_pm[i]->PlanetSimulation == form) ) {
      select_planetstatus(i);
      return;
    }

  // something terrible has happened.....
  select_planetstatus(0);
}



void graphics::select_planet(const _xypoint& mousepos)
{
  int pn = 0;
  if ( sca_mask & CTRL_PRESSED )
    pn = 1;

  mapview->set_active_planet(mousepos, pn);
  select_planetstatus(pn);
  load_planetstatus();
  show_planetstatus();

  if ( !(sca_mask & SHIFT_PRESSED) )
    XRaiseWindow(x_display, curr_ps->PlanetStatus->window);
}


static
void load_habitability(const int h, FL_OBJECT* fo)
{
  myString n;
  n = int_to_str(h) + "%";
  fl_set_object_label(fo, n.chars());
  fl_set_object_lcol(fo, (h>=0)? FL_GREEN : FL_RED);
}



void graphics::load_planetstatus(void)
{
  planet* p = mapview->get_active_planet(curr_ps->statusnumber);
  int w = mapview->when(MW_READ);
  int d, y, i, c;
  int tt[3];
  const message* msg;

  fl_freeze_form(curr_ps->PlanetStatus);
  fl_freeze_form(curr_pm->PlanetSimulation);

  myString n(p->name() + ((p->is_homeworld())? " (HW)" : "") + " (#" + int_to_str(p->starsid()) + ")");
  fl_set_object_label(curr_ps->planetname, n.chars());
  // update also simulation
  fl_set_object_label(curr_pm->planetname, n.chars());

  if (p->owner()) {
    n = p->owner()->name();
    fl_set_object_lcol(curr_ps->owner, FL_FREE_COL1 + XFCOL_RACES + p->owner()->race_id());
  } else
    n = "";
  fl_set_object_label(curr_ps->owner, n.chars());

  if (p->trustedsource()) {
    n = p->trustedsource()->name();
    fl_set_object_lcol(curr_ps->trustedsource, FL_FREE_COL1 + XFCOL_RACES +
		                             p->trustedsource()->race_id());
  } else
    n = "";
  fl_set_object_label(curr_ps->trustedsource, n.chars());

  if (p->authsource()) {
    n = p->authsource()->name();
    fl_set_object_lcol(curr_ps->authsource, FL_FREE_COL1 + XFCOL_RACES + p->authsource()->race_id());
  } else
    n = "";
  fl_set_object_label(curr_ps->authsource, n.chars());

  n = int_to_str(p->report_age());
  fl_set_object_label(curr_ps->reportage, n.chars());

  n = "(" + int_to_str(p->position().x) + "," + 
      int_to_str(p->position().y) + ")";
  fl_set_object_label(curr_ps->position, n.chars());

  fl_set_object_label(curr_ps->type, p->type_name());

  fl_set_object_label(curr_ps->habvpoint, mapview->viewpoint()->name().chars());
  d = p->hab_now(mapview->viewpoint(), w);
  load_habitability(d, curr_ps->habnow);
  d = p->hab_when_max_terraformed(mapview->viewpoint(), w);
  load_habitability(d, curr_ps->habtformed);
  tt[0] = tt[1] = tt[2] = (mapview->viewpoint()->lrt(TT)? 30 : 15);
  d = p->hab_when_max_terraformed(mapview->viewpoint(), w, tt);
  n = int_to_str(d) + "%";
  load_habitability(d, curr_ps->habmaxtformed);

  if (p->owner()) {
    fl_set_object_label(curr_ps->habowner, p->owner()->name().chars());
    d = p->hab_now(p->owner(), w);
    load_habitability(d, curr_ps->ownhabnow);
    d = p->hab_when_max_terraformed(p->owner(), w);
    load_habitability(d, curr_ps->ownhabtformed);
    tt[0] = tt[1] = tt[2] = (p->owner()->lrt(TT)? 30 : 15);
    d = p->hab_when_max_terraformed(p->owner(), w, tt);
    n = int_to_str(d) + "%";
    load_habitability(d, curr_ps->ownhabmaxtformed);
  } else {
    fl_set_object_label(curr_ps->habowner, "");
    fl_set_object_label(curr_ps->ownhabnow, "");
    fl_set_object_label(curr_ps->ownhabtformed, "");
    fl_set_object_label(curr_ps->ownhabmaxtformed, "");
  }

  // set values in environment_dial (ALWAYS viewpoint)
  for (i = 0; i < 3; i++) {
    curr_ps->environment_dials[i].original = p->oristats()[i];
    curr_ps->environment_dials[i].current = p->stats(w)[i];
    curr_ps->environment_dials[i].tform = mapview->viewpoint()->terraform_tech()[i];
    curr_ps->environment_dials[i].maxtform = (mapview->viewpoint()->lrt(TT)? 30 : 15);
    curr_ps->environment_dials[i].habmin = mapview->viewpoint()->habmin()[i];
    curr_ps->environment_dials[i].habmax = mapview->viewpoint()->habmax()[i];
  }

  // force redraw of dials
  fl_redraw_object(curr_ps->gravitydial);
  fl_redraw_object(curr_ps->tempdial);
  fl_redraw_object(curr_ps->raddial);

  n = int_to_str(p->population(w));
  fl_set_object_label(curr_ps->population, n.chars());

  d = p->population(w+1) - p->population(w);
  n = myString("(") + ((d>0)? "+" : "") + int_to_str(d) + ")";
  fl_set_object_label(curr_ps->popgrowth, n.chars());

  d = (p->capacity(w)+5)/10;
  n = int_to_str(d) + "%";
  fl_set_object_label(curr_ps->popfill, n.chars());

  if (d <= 25)
    fl_set_object_color(curr_ps->popfilldial, FL_BOTTOM_BCOL, FL_PALEGREEN);
  else if (d <= 33)
    fl_set_object_color(curr_ps->popfilldial, FL_BOTTOM_BCOL, FL_YELLOW);
  else if (d <= 48)
    fl_set_object_color(curr_ps->popfilldial, FL_BOTTOM_BCOL, FL_INDIANRED);
  else
    fl_set_object_color(curr_ps->popfilldial, FL_BOTTOM_BCOL, FL_RED);
  fl_set_dial_value(curr_ps->popfilldial, (double)((d > 100)? 100 : d));

  if (!p->starbase_name().length()) {
    fl_set_object_label(curr_ps->starbasename, "-- no starbase --");
    fl_set_object_label(curr_ps->stbdamage, "");
    fl_set_object_label(curr_ps->gaterange, "");
    fl_set_object_label(curr_ps->massdriver, "");
  } else {
    fl_set_object_label(curr_ps->starbasename, p->starbase_name());
    if (p->starbase_damage() >= 0)
      n = int_to_str(p->starbase_damage()) + "%";
    else
      n = "??%";
    fl_set_object_label(curr_ps->stbdamage, n.chars());

    if (p->gate_range() != 0) {
      if (p->gate_range() == -1)
	n = "inf";
      else
	n = int_to_str(p->gate_range()) + "l.y.";
      if (p->gate_mass() == -1)
	n += "inf";
      else
	n += int_to_str(p->gate_mass()) + "kT";
    } else
      n = "-- no gate --";

    fl_set_object_label(curr_ps->gaterange, n.chars());

    if (p->driver_warp()) {
      n = int_to_str(p->driver_warp()) + " @ ";

      if (p->driver_destination())
	n += p->driver_destination()->name();
      else
	n += "none";
    } else
      n = "-- no driver --";

    fl_set_object_label(curr_ps->massdriver, n.chars());
  }

  d = p->factories(w) - p->maxcfactories(w);
  n = int_to_str(p->factories(w)) + "/" + ((d>0)? "+" : "") + 
      int_to_str(d) + "/" + int_to_str(p->maxfactories(w));
  fl_set_object_label(curr_ps->factories, n.chars());

  d = p->mines(w) - p->maxcmines(w);
  n = int_to_str(p->mines(w)) + "/" + ((d>0)? "+" : "") + 
      int_to_str(d) + "/" + int_to_str(p->maxmines(w));
  fl_set_object_label(curr_ps->mines, n.chars());

  n = int_to_str(p->defenses(w)) + "/" + int_to_str(p->maxdefenses(w)) +
      " (" + int_to_str(p->defense_coverage(w) / 100) + "%)";
  fl_set_object_label(curr_ps->defenses, n.chars());

  if (p->scanning() > 0)
    n = int_to_str(p->scanning()) + "/" + int_to_str(p->penscanning()) + " l.y.";
  else 
    n = "none";
  fl_set_object_label(curr_ps->scanning, n.chars());

  n = int_to_str(p->resources(w)) + " (" + int_to_str(p->research(w)) + ")";
  fl_set_object_label(curr_ps->resources, n.chars());

  if (p->routing_dest())
    n = p->routing_dest()->name();
  else
    n = "none";
  fl_set_object_label(curr_ps->routing, n.chars());

  _mintype mr;
  mr = p->mining_rate(w);
  n = int_to_str(p->minerals(w).iron) + "+" + int_to_str(mr.iron);
  fl_set_object_label(curr_ps->ironium, n.chars());
  n = int_to_str(p->minerals(w).bora) + "+" + int_to_str(mr.bora);
  fl_set_object_label(curr_ps->boranium, n.chars());
  n = int_to_str(p->minerals(w).germ) + "+" + int_to_str(mr.germ);
  fl_set_object_label(curr_ps->germanium, n.chars());
  mr = p->min_conc(w);
  n = int_to_str(mr.iron);
  fl_set_object_label(curr_ps->ironconc, n.chars());
  n = int_to_str(mr.bora);
  fl_set_object_label(curr_ps->boraconc, n.chars());
  n = int_to_str(mr.germ);
  fl_set_object_label(curr_ps->germconc, n.chars());

  mr = p->mining_rate(w);
  for (i = 0; i < 3; i++) {
    curr_ps->mineral_dials[i].now = p->minerals(w)[i];
    curr_ps->mineral_dials[i].mining = mr[i];
    curr_ps->mineral_dials[i].next = p->minerals(w+1)[i];
    curr_ps->mineral_dials[i].conc = p->min_conc(w)[i];
  }

  // force redraw of dials
  fl_redraw_object(curr_ps->ironiumdial);
  fl_redraw_object(curr_ps->boraniumdial);
  fl_redraw_object(curr_ps->germaniumdial);

  // update the object table and object mineral multipliers
  if (p->owner() && p->owner()->next_object(NULL)) {
    object* o;

    if (p->owner()->race_id() != curr_ps->mineralobjects_lastowner) {
      // reload table and select 1st
      fl_clear_choice(curr_ps->testobject);

      for (o = p->owner()->next_object(NULL); o; o = p->owner()->next_object(o))
	fl_addto_choice(curr_ps->testobject, o->name());
      fl_set_choice(curr_ps->testobject, 1);

      curr_ps->mineralobjects_lastowner = p->owner()->race_id();
    }

    load_mineralobject();
  } else {
    fl_clear_choice(curr_ps->testobject);
    // clear the boxes
    for (i = 0; i < 3; i++)
      fl_set_object_label(curr_ps->minobjects[i], "");
    fl_set_object_label(curr_ps->resobjects, "");    

    curr_ps->mineralobjects_lastowner = -1;
  }

  // update simulation window
  fl_clear_browser(curr_pm->messages);
  for (y = 0; y < game_map->sim_future(); y++)
    for (msg = p->next_message(NULL, y); msg; msg = p->next_message(msg, y))
      if ( (c = msg->color()) )
	fl_add_browser_line(curr_pm->messages,
			    ("@C" + int_to_str(c) + " " + int_to_str(y + game_map->year()) + ": " + msg->msg).chars());
      else
	fl_add_browser_line(curr_pm->messages,
			    (int_to_str(y + game_map->year()) + ": " + msg->msg).chars());

  for (msg = p->next_gmessage(NULL); msg; msg = p->next_gmessage(msg))
    if ( (c = msg->color()) )
      fl_add_browser_line(curr_pm->messages, "@C" + int_to_str(c) + " " + "Analysis: " + msg->msg);
    else
      fl_add_browser_line(curr_pm->messages, "Analysis: " + msg->msg);

  load_packetfiring();
  load_planetbombing();

  fl_unfreeze_form(curr_ps->PlanetStatus);
  fl_unfreeze_form(curr_pm->PlanetSimulation);
}



void graphics::load_packetfiring(void)
{

}


void graphics::show_packetfiring(void)
{
  if ( !fl_form_is_visible(xf_pak->PacketFiring) )
    fl_show_form(xf_pak->PacketFiring, FL_PLACE_SIZE, FL_FULLBORDER, "Packet Firing");
  else
    XRaiseWindow(x_display, xf_pak->PacketFiring->window);
  XFlush(fl_get_display());
}



void graphics::hide_packetfiring(void)
{
  if ( fl_form_is_visible(xf_pak->PacketFiring) )
    fl_hide_form(xf_pak->PacketFiring);
  XFlush(fl_get_display());
}



void graphics::load_planetbombing(void)
{
}



void graphics::show_racialreport(void)
{
  if ( !fl_form_is_visible(xf_rr->RacialReport) )
    fl_show_form(xf_rr->RacialReport, FL_PLACE_SIZE, FL_FULLBORDER, "Racial Report");
  else
    XRaiseWindow(x_display, xf_rr->RacialReport->window);
  XFlush(fl_get_display());
}



void graphics::hide_racialreport(void)
{
  if ( fl_form_is_visible(xf_rr->RacialReport) )
    fl_hide_form(xf_rr->RacialReport);
  XFlush(fl_get_display());
}



void graphics::load_racialreport(const int rid)
{
  race* r = game_map->find_race(rid);
  int c, i;
  object* o;

  fl_freeze_form(xf_rr->RacialReport);
  fl_freeze_form(xf_rrinfo->RR_RaceInfo);
  fl_freeze_form(xf_rrlog->RR_ReportLog);
  fl_freeze_form(xf_rrcmp->RR_Comparisons);
  fl_freeze_form(xf_rrdo->RR_DesignsObjects);

  // main form
  fl_set_object_label(xf_rr->race_names, r->name() + " (" + r->names() + ")");

  fl_set_object_label(xf_rr->race_isanalyzed, (r->do_analysis())? "A" : "");
  fl_set_object_label(xf_rr->race_issource, (r->gave_report())? "R" : "");

  // report-log form
  fl_clear_browser(xf_rrlog->messages);
  for (const message* msg = r->next_message(NULL); 
       msg; msg = r->next_message(msg))
    if ( (c = msg->color()) )
      fl_add_browser_line(xf_rrlog->messages, "@C" + int_to_str(c) + " " + msg->msg);
    else
      fl_add_browser_line(xf_rrlog->messages, msg->msg);

  // designs form
  for (i = 0, o = NULL; ; ) {
    do {
      o = r->next_object(o);
    } while (o && !(o->is_design() && !o->d()->is_starbase()));

    if (!o || i == 16)
      break;

    fl_set_object_label(xf_rrdo->design[i], o->name());
    fl_set_object_label(xf_rrdo->minerals[i][0], int_to_str(o->minerals().iron));
    fl_set_object_label(xf_rrdo->minerals[i][1], int_to_str(o->minerals().bora));
    fl_set_object_label(xf_rrdo->minerals[i][2], int_to_str(o->minerals().germ));
    fl_set_object_label(xf_rrdo->resources[i], int_to_str(o->resources()));
    fl_set_object_label(xf_rrdo->weight[i], int_to_str(o->d()->weight()));
    fl_set_object_label(xf_rrdo->basehull[i], o->d()->basehull()->name);
    i++;
  }

  for (; i < 16; i++) {
    fl_set_object_label(xf_rrdo->design[i], "-- empty slot --");
    fl_set_object_label(xf_rrdo->minerals[i][0], "--");
    fl_set_object_label(xf_rrdo->minerals[i][1], "--");
    fl_set_object_label(xf_rrdo->minerals[i][2], "--");
    fl_set_object_label(xf_rrdo->resources[i], "--");
    fl_set_object_label(xf_rrdo->weight[i], "--");
    fl_set_object_label(xf_rrdo->basehull[i], "- none -");
  }

  fl_unfreeze_form(xf_rr->RacialReport);
  fl_unfreeze_form(xf_rrinfo->RR_RaceInfo);
  fl_unfreeze_form(xf_rrlog->RR_ReportLog);
  fl_unfreeze_form(xf_rrcmp->RR_Comparisons);
  fl_unfreeze_form(xf_rrdo->RR_DesignsObjects);
}



void graphics::toggle_mapcontrol(void)
{
  if ( fl_form_is_visible(xf_mc->MapControl) )
    fl_hide_form(xf_mc->MapControl);
  else
    fl_show_form(xf_mc->MapControl, FL_PLACE_SIZE, FL_FULLBORDER, "Map Control");
  XFlush(fl_get_display());
}



void graphics::select_viewpoint(void)
{
  fl_freeze_form(xf_mc->MapControl);
  if (curr_vwp >= 0) {
    int i;

    fl_set_object_boxtype(xf_mc->race[curr_vwp], FL_NO_BOX);
    fl_redraw_object(xf_mc->racebox);
    fl_redraw_object(xf_mc->racetitle);

    for (i = 0 ; i < 16; i++)
      fl_redraw_object(xf_mc->race[i]);
  }

  curr_vwp = mapview->viewpoint()->race_id();
  fl_set_object_boxtype(xf_mc->race[curr_vwp], FL_FRAME_BOX);

  fl_unfreeze_form(xf_mc->MapControl);

  mapview->set_window_title();
  auto_redraw_map();
}



void graphics::toggle_pfunclist(void)
{
  if ( fl_form_is_visible(xf_pv->ObjectViews) )
    fl_hide_form(xf_pv->ObjectViews);
  else
    fl_show_form(xf_pv->ObjectViews, FL_PLACE_SIZE, FL_FULLBORDER, "Planetary Views");
  XFlush(fl_get_display());
}



void graphics::toggle_ffunclist(void)
{
  if ( fl_form_is_visible(xf_fv->ObjectViews) )
    fl_hide_form(xf_fv->ObjectViews);
  else
    fl_show_form(xf_fv->ObjectViews, FL_PLACE_SIZE, FL_FULLBORDER, "Fleet Views");
  XFlush(fl_get_display());
}



void graphics::load_pfunclist(void)
{
  int i;

  fl_freeze_form(xf_pv->ObjectViews);
  
  fl_clear_browser(xf_pv->pvlist);
  for (i = 0; i < mapview->get_num_planet_views(); i++)
    if (mapview->get_planet_view(i))
      fl_add_browser_line(xf_pv->pvlist, 
			  mapview->get_planet_view(i)->name.chars());
    else
      fl_add_browser_line(xf_pv->pvlist, "<NULL!?!?>");

  fl_unfreeze_form(xf_pv->ObjectViews);
}



void graphics::load_ffunclist(void)
{
  int i;

  fl_freeze_form(xf_fv->ObjectViews);
  
  fl_clear_browser(xf_fv->pvlist);
  for (i = 0; i < mapview->get_num_fleet_views(); i++)
    if (mapview->get_fleet_view(i))
      fl_add_browser_line(xf_fv->pvlist, 
			  mapview->get_fleet_view(i)->name.chars());
    else
      fl_add_browser_line(xf_fv->pvlist, "<NULL!?!?>");

  fl_unfreeze_form(xf_fv->ObjectViews);
}



void graphics::showselected_pfunclist(void)
{
  int i = mapview->get_planet_view_index();

  // select active
  fl_select_browser_line(xf_pv->pvlist, i+1);
}



void graphics::showselected_ffunclist(void)
{
  int i = mapview->get_fleet_view_index();

  // select active
  fl_select_browser_line(xf_fv->pvlist, i+1);
}



void graphics::toggle_pfuncedit(void)
{
  if ( fl_form_is_visible(xf_pfe->DisplayFunction) )
    fl_hide_form(xf_pfe->DisplayFunction);
  else
    fl_show_form(xf_pfe->DisplayFunction, FL_PLACE_SIZE, FL_FULLBORDER, "Planetary Function Editor");
  XFlush(fl_get_display());
}



void graphics::toggle_ffuncedit(void)
{
  if ( fl_form_is_visible(xf_ffe->DisplayFunction) )
    fl_hide_form(xf_ffe->DisplayFunction);
  else
    fl_show_form(xf_ffe->DisplayFunction, FL_PLACE_SIZE, FL_FULLBORDER, "Fleet Function Editor");
  XFlush(fl_get_display());
}


bool graphics::in_planet_windows(FL_OBJECT* ob)
{
  if (ob->form == xf_pfe->DisplayFunction ||
      ob->form == xf_pv->ObjectViews)
    return true;
  else
    return false;
}


void graphics::load_pfunction(void)
{
  int i;

  const pf_operation& po = mapview->get_plamode();
  char tstr[32];

  fl_freeze_form(xf_pfe->DisplayFunction);

  // set labels
  sprintf(tstr, "%d", 1 + mapview->select_plamode(MW_READ));
  fl_set_object_label(xf_pfe->number, tstr);
  write_pfunction(po.f);

  // set values
  fl_set_choice(xf_pfe->mode, (int)po.mode);

  fl_set_button(xf_pfe->mask_circles, po.modemask & PF_CIRCLES);
  fl_set_button(xf_pfe->mask_lines, po.modemask & PF_LINES);
  fl_set_button(xf_pfe->mask_data, po.modemask & PF_DATA);
  fl_set_button(xf_pfe->mask_marker, po.modemask & PF_MARKER);
  fl_set_button(xf_pfe->mask_name, po.modemask & PF_NAME);
  fl_set_button(xf_pfe->mask_flag, po.modemask & PF_FLAG);

  for (i = 0; i < 10; i++) {
    sprintf(tstr, "%d", po.params[i]);
    fl_set_input(xf_pfe->input_par[i], tstr);
  }

  fl_unfreeze_form(xf_pfe->DisplayFunction);
  pfe_menu_changed = false;
}



void graphics::load_ffunction(void)
{
  int i;

  const ff_operation& fo = mapview->get_flemode();
  char tstr[32];

  fl_freeze_form(xf_ffe->DisplayFunction);

  // set labels
  sprintf(tstr, "%d", 1 + mapview->select_flemode(MW_READ));
  fl_set_object_label(xf_ffe->number, tstr);
  write_ffunction(fo.f);

  // set values
  fl_set_choice(xf_ffe->mode, (int)fo.mode);

  fl_set_button(xf_ffe->mask_circles, fo.modemask & PF_CIRCLES);
  fl_set_button(xf_ffe->mask_lines, fo.modemask & PF_LINES);
  fl_set_button(xf_ffe->mask_data, fo.modemask & PF_DATA);
  fl_set_button(xf_ffe->mask_marker, fo.modemask & PF_MARKER);
  fl_set_button(xf_ffe->mask_name, fo.modemask & PF_NAME);
  fl_set_button(xf_ffe->mask_flag, fo.modemask & PF_FLAG);

  for (i = 0; i < 10; i++) {
    sprintf(tstr, "%d", fo.params[i]);
    fl_set_input(xf_ffe->input_par[i], tstr);
  }

  fl_unfreeze_form(xf_ffe->DisplayFunction);
  ffe_menu_changed = false;
}



void graphics::write_pfunction(planetary_function* pf)
{
  int i;

  fl_freeze_form(xf_pfe->DisplayFunction);
  // set menu selection
  fl_set_object_label(xf_pfe->selected, pf->name().chars());

  // set pfunction description
  fl_set_object_label(xf_pfe->description, pf->description().chars());

  // set parameter names
  for (i = 0; i < 10; i++)
    fl_set_object_label(xf_pfe->input_par[i], pf->parameter_desc(i).chars());

  fl_unfreeze_form(xf_pfe->DisplayFunction);
}



void graphics::write_ffunction(fleet_function* ff)
{
  int i;

  fl_freeze_form(xf_ffe->DisplayFunction);
  // set menu selection
  fl_set_object_label(xf_ffe->selected, ff->name().chars());

  // set pfunction description
  fl_set_object_label(xf_ffe->description, ff->description().chars());

  // set parameter names
  for (i = 0; i < 10; i++)
    fl_set_object_label(xf_ffe->input_par[i], ff->parameter_desc(i).chars());

  fl_unfreeze_form(xf_ffe->DisplayFunction);
}



void graphics::unload_pfunction(void)
{
  int i;

  // get menu selection
  int params[16];

  for (i = 0; i < 10; i++)
    sscanf(fl_get_input(xf_pfe->input_par[i]), "%d", &params[i]);

  for (; i < 16; i++)
    params[i] = 0;

  mapview->set_plamode((pfe_menu_changed? fl_get_menu_text(xf_pfe->selected) : ""),
		       (_dfmode)fl_get_choice(xf_pfe->mode),
		       (fl_get_button(xf_pfe->mask_circles)? PF_CIRCLES : 0) |
		         (fl_get_button(xf_pfe->mask_lines)? PF_LINES : 0) |
		         (fl_get_button(xf_pfe->mask_data)? PF_DATA : 0) |
		         (fl_get_button(xf_pfe->mask_marker)? PF_MARKER : 0) |
		         (fl_get_button(xf_pfe->mask_name)? PF_NAME : 0) |
		         (fl_get_button(xf_pfe->mask_flag)? PF_FLAG : 0),
		       params);

  // update the number_menu thingy
  if (pfe_menu_changed) {
    char menuitem[128];
  
    sprintf(menuitem, "%d- %s", mapview->select_plamode(MW_READ)+1, 
	                        fl_get_menu_text(xf_pfe->selected));
    fl_replace_menu_item(xf_pfe->number, mapview->select_plamode(MW_READ)+1,
			 xfpp(menuitem));
  }
}



void graphics::unload_ffunction(void)
{
  int i;

  // get menu selection
  int params[16];

  for (i = 0; i < 10; i++)
    sscanf(fl_get_input(xf_ffe->input_par[i]), "%d", &params[i]);

  for (; i < 16; i++)
    params[i] = 0;

  mapview->set_flemode((ffe_menu_changed? fl_get_menu_text(xf_ffe->selected) : ""),
		       (_dfmode)fl_get_choice(xf_ffe->mode),
		       (fl_get_button(xf_ffe->mask_circles)? PF_CIRCLES : 0) |
		         (fl_get_button(xf_ffe->mask_lines)? PF_LINES : 0) |
		         (fl_get_button(xf_ffe->mask_data)? PF_DATA : 0) |
		         (fl_get_button(xf_ffe->mask_marker)? PF_MARKER : 0) |
		         (fl_get_button(xf_ffe->mask_name)? PF_NAME : 0) |
		         (fl_get_button(xf_ffe->mask_flag)? PF_FLAG : 0),
		       params);

  // update the number_menu thingy
  if (ffe_menu_changed) {
    char menuitem[128];
  
    sprintf(menuitem, "%d- %s", mapview->select_flemode(MW_READ)+1, 
	                        fl_get_menu_text(xf_ffe->selected));
    fl_replace_menu_item(xf_ffe->number, mapview->select_flemode(MW_READ)+1,
			 xfpp(menuitem));
  }
}



void graphics::init_pla_number_menu(void)
{
  int i;
  char menuitem[128];

  fl_clear_menu(xf_pfe->number);
  for (i = 0; i < MAX_DISP_MODES; i++) {
    sprintf(menuitem, "%d- %s", i+1, xfpp(mapview->get_plamode(i).f->name().chars()));
    fl_addto_menu(xf_pfe->number, menuitem);
  }
}



void graphics::init_fle_number_menu(void)
{
  int i;
  char menuitem[128];

  fl_clear_menu(xf_ffe->number);
  for (i = 0; i < MAX_DISP_MODES; i++) {
    sprintf(menuitem, "%d- %s", i+1, xfpp(mapview->get_flemode(i).f->name().chars()));
    fl_addto_menu(xf_ffe->number, menuitem);
  }
}



void graphics::load_mineralobject(void)
{
  char tstr[512];
  planet* p = mapview->get_active_planet(0);
  int w = mapview->when(MW_READ);
  object* o;
  int i;

  if (!p->owner())
    return;

  if (!fl_get_choice_text(curr_ps->testobject) ||
      !(o = p->owner()->find_object(fl_get_choice_text(curr_ps->testobject))) ) {
    // clear the boxes
    for (i = 0; i < 3; i++)
      fl_set_object_label(curr_ps->minobjects[i], "");
    fl_set_object_label(curr_ps->resobjects, "");    

    return;
  }

  // for minerals we use now+mining (shipped is unavailable, in any case)
  _mintype mnow;
  mnow = p->minerals(w) + p->mining_rate(w);

  for (i = 0; i < 3; i++) {
    if (o->minerals()[i])
      sprintf(tstr, "%d", mnow[i] / o->minerals()[i]);
    else
      strcpy(tstr, "++++");
    fl_set_object_label(curr_ps->minobjects[i], tstr);
  }

  sprintf(tstr, "%.1f", (float)p->resources(w)/(float)o->resources());
  fl_set_object_label(curr_ps->resobjects, tstr);
}


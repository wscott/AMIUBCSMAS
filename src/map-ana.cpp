#include "starana-classes.h"


#include <string.h>




void stars_map::check_planets_step1(void)
{
  int i;
  planet* p;
  race* r;

  add_message(RLO_ERROR, "");
  add_message(RLO_ERROR, "************* Initial planetary analysis *************");
  add_message(RLO_ERROR, "");

  for (p = unsorted_ptable; p; p = p->next) {

    if (p->auth_source != -1 && race_list[p->auth_source]->can_analyze) {
      // we have authoritative source & is a friend -> use data
      p->trusted_source = p->auth_source;

      p->add_message(RLO_DATASRC, p->name() + ": authoritative source " + 
		     race_list[p->auth_source]->name() + " assumed trusted for simulation");
    } else {
      for (p->rep_age = 20000, i = 0; i < number_races; i++) {
	// add to race explored total (if explored, of course)
	if (p->r_age[i] < 10000) {
	  race_list[i]->explored_planets++;

	  if (p->r_age[i] < p->rep_age) {
	    p->rep_age = p->r_age[i];
	    p->trusted_source = i;
	  } else if (p->r_age[i] == p->rep_age) {
	    if ( (race_list[i]->reliab + 10*(i == p->auth_source)) >
		 (race_list[p->trusted_source]->reliab + 10*(p->trusted_source == p->auth_source))) {

	      p->add_message(RLO_DATASRC, p->name() + ": " + race_list[i]->name() +
			     " data preferred over " + race_list[p->trusted_source]->name());

	      p->trusted_source = i;
	    } else
	      p->add_message(RLO_DATASRC, p->name() + ": " + race_list[p->trusted_source]->name() + 
			     " data preferred over " + race_list[i]->name() + " data");
	  }
	}
      }
    }

    if (p->trusted_source == -1) {
      //      fprintf(of, "%s: no data available on planet", p->_name.chars());

    } else {
      p->add_message(RLO_DATASRC, p->name() + ": data from " + 
		     race_list[p->trusted_source]->name() + " used as trusted source");
      if (p->trusted_source != p->auth_source && p->_owner &&
	  p->_owner->can_analyze)
	add_message(RLO_ERROR, p->name() + ": TRUSTED != AUTHORITATIVE AND YOU WANT SIMULATION!!!!");

      // set actual values
      p->_owner = p->r_owner[p->trusted_source];
      p->starbase = p->r_starbase[p->trusted_source];
      if ( (p->stb_type = p->get_starbase_power(p->starbase)) == ErrorInName)
	p->add_message(RLO_ERROR, p->name() + " (" + p->starbase + 
		       "): unable to understand starbase hull type!!");

      p->_pop[0] = p->r_pop[p->trusted_source];
      p->_stats[0][0] = p->r_stats[p->trusted_source][0];
      p->_stats[0][1] = p->r_stats[p->trusted_source][1];
      p->_stats[0][2] = p->r_stats[p->trusted_source][2];
      p->ori_stats[0] = p->r_oristats[p->trusted_source][0];
      p->ori_stats[1] = p->r_oristats[p->trusted_source][1];
      p->ori_stats[2] = p->r_oristats[p->trusted_source][2];
      p->_min_conc[0] = p->r_minconc[p->trusted_source];
      p->def_coverage[0] = p->r_def_coverage[p->trusted_source];

      if (p->_owner)
	p->_habitab[0] = p->r_hab[p->_owner->id];

      p->check_data();
    }

    p->set_power();
  }

  // report planet habitability for all viewpoints
  // header (we assume at least 1 race to analyze)
  add_message(RLO_HABTABLE, "");
  add_message(RLO_HABTABLE, "************* Planet Habitability Report *************");
  add_message(RLO_HABTABLE, "");

  char tstr[256];
  myString msg = "Planet            ";

  for (i = 0; i < number_races; i++)
    if (race_list[i]->can_analyze) {
      sprintf(tstr, "%18s", race_list[i]->_names.c_str());
      msg += tstr;
    }

  add_message(RLO_HABTABLE, msg);

  for (p = unsorted_ptable; p; p = p->next)
    if (p->trusted_source != -1) {
      sprintf(tstr, "%-18s ", p->name().c_str());
      msg = tstr;

      if (p->ori_stats[Grav] != -10) {
	for (i = 0; i < number_races; i++) {
	  r = race_list[i];

	  if (r->can_analyze) {
	    // output reported habitability
	    if (p->r_age[i] != 10000)
	      sprintf(tstr, " %3d%% ", p->r_hab[i]);
	    else
	      sprintf(tstr, "      ");

	    msg += tstr;

	    // output estimated habitability
	    sprintf(tstr, " %3d%%(%3d%%) ", p->hab_now(r), p->hab_when_max_terraformed(r));
	    msg += tstr;
	  }
	}
      } else
	msg += "....reported, but no planetary info.....";
      
      add_message(RLO_HABTABLE, msg);
    }
  
  add_message(RLO_HABTABLE, "");
}



void stars_map::check_fleets(void)
{
  fleet* f;
  int i;

  add_message(RLO_ERROR, "");
  add_message(RLO_ERROR, "****************** Fleet Analysis ******************");
  add_message(RLO_ERROR, "");

  for (i = 0; i < number_races; i++)
    for (f = race_list[i]->fleet_table; f; f = f->rnext)
      f->check_data();

  add_message(RLO_ERROR, "");
}



void stars_map::find_breeders(planet* p)
{
  planet* source;
  planet* s_list = NULL;
  int dist;
  planet* op2;
  planet* p2;
  myString msg;
  char tstr[256];

  //  if (p->p_type == planet::BREEDER)
  //    return;

  for (source = p->_owner->planet_table; source; source = source->rnext) {
    if (source == p || source->p_type == planet::PRODUCTION ||
	                source->p_type == planet::NEWCOLONY)
      continue;

    dist = p->distance(source);

    for (op2 = NULL, p2 = s_list; p2 && p->distance(p2) < dist; op2 = p2, p2 = p2->tnext);

    if (op2 == NULL) { // head
      source->tnext = s_list;
      s_list = source;
    } else { // tail & insert
      source->tnext = op2->tnext;
      op2->tnext = source;
    }
  }

  // write out names
  if (s_list) {
    msg = p->header + " pop sources:";

    for (source = s_list; source && source->distance(p) <= PARmax_search_distance;
	 source = source->tnext) {
      if (source->p_type == planet::BREEDER)
	sprintf(tstr, "  %s (%.1f/%d)", source->name().c_str(), 
		(float)source->capacity(0)/10.0, source->distance(p) / 81 + 1);
      else
	sprintf(tstr, "  [%s (%.1f @ %d)]", source->name().c_str(), 
		(float)source->capacity(0)/10.0, source->distance(p) / 81 + 1);

      msg += tstr;
    }

    p->add_message(RLO_PLAPOPSTAT, msg);
  }
}



void stars_map::find_minerals(planet* p, const int mt)
{
  planet* source;
  planet* s_list = NULL;
  int dist;
  planet* op2;
  planet* p2;
  myString msg;
  char tstr[256];

  //  if (p->p_type == planet::MINING || p->p_type == planet::BREEDER)
  //    return;

  for (source = p->_owner->planet_table; source; source = source->rnext) {
    if (source == p || source->need_min[mt] > 0 ||
	source->_mineral[0][mt] <= PARmin_mineral_move)
      continue;

    dist = p->distance(source);

    for (op2 = NULL, p2 = s_list; p2 && p->distance(p2) < dist; op2 = p2, p2 = p2->tnext);

    if (op2 == NULL) { // head
      source->tnext = s_list;
      s_list = source;
    } else { // tail & insert
      source->tnext = op2->tnext;
      op2->tnext = source;
    }
  }

  // write out names
  if (s_list) {
    msg = p->header + " " + ((mt)? ((mt==1)? "boranium" : "germanium") : "ironium") + " sources:";

    for (source = s_list; source && source->distance(p) < PARmax_search_distance;
	 source = source->tnext) {
      sprintf(tstr, "  %s (%d/%d @ %d)", (const char*)source->_name,
	      -source->need_min[mt], source->_mineral[0][mt],
	      source->distance(p) / 81 + 1);

      msg += tstr;
    }

    p->add_message(RLO_PLAMINSTAT, msg);
  }
}



void stars_map::check_planets_step2(void)
{
  planet* p;
  int i;

  // check growth/germanium/min shortages, etc.
  add_message(RLO_ERROR, "");
  add_message(RLO_ERROR, "************* Planetary simulation/analysis *************");
  add_message(RLO_ERROR, "");

  // select planet types
  for (p = unsorted_ptable; p; p = p->next) {
    if (!p->_owner || !p->_owner->can_analyze)
      continue;

    if (p->p_type == planet::UNKNOWN) {
      add_message(RLO_ERROR, p->header + " planet type undefined!!!");
      continue;
    }

    p->pop_needs();
    p->min_needs();
  }

  for (p = unsorted_ptable; p; p = p->next) {
    if (!p->_owner || !p->_owner->can_analyze)
      continue;

    add_message((RLO_PLAREPORTS | RLO_PLAMINSTAT | RLO_PLAPOPSTAT), p->title());

    // do evolution
    for (i = 0; i <= sim_future(); i++)
      for (const message* m = p->next_message(NULL, i); m; m = p->next_message(m, i))
	add_message(m->type, p->header + " " + m->msg);

    // check pop/mineral offer/demand
    p->report_growth(); 
    p->report_mining();

    add_message((RLO_PLAMINSTAT | RLO_PLAPOPSTAT), p->header + "xcng matrix: " +
		int_to_str(p->need_pop) + " - " +
		int_to_str(p->need_min.iron) + "/" +
		int_to_str(p->need_min.bora) + "/" +
		int_to_str(p->need_min.germ));

    // report global messages
    for (const message* m = p->next_gmessage(NULL); m; m = p->next_gmessage(m))
      add_message(m->type, p->header + " " + m->msg);

    // report sources of pop/min
    if (p->need_pop > 0)
      find_breeders(p);

    for (i = 0; i < 3; i++)
      if (p->need_min[i] > 0)
	find_minerals(p, i);
  }

  add_message(RLO_ERROR, "");
}




void stars_map::empire_report(void)
{
  int i, y;
  race* r;
  planet* p;
  fleet* f;
  double t;
  myString msg;
  char tstr[256];

  add_message(RLO_EMPIRETOT, "");
  add_message(RLO_EMPIRETOT, "****************** Empire evolution *******************");
  add_message(RLO_EMPIRETOT, "");

  for (i = 0; i < number_races; i++) {
    r = race_list[i];

    // reports possible for all races
    // total number of fleets
    for (f = r->fleet_table; f; f = f->rnext) {
      r->number_fleets++;

      for (y = 0; y < 6; y++)
	r->total_fleets[y] += f->n_ships(y);
    }

    // if can't analyze spread year 0 pop
    if (!r->can_analyze) {
      for (p = race_list[i]->planet_table; p; p = p->rnext)
	r->total_pop[0] += p->population(0)/ 100;

      continue;
    }

    if (race_planets[i] == 0) // why bother?
      continue;

    msg = "************** Report of " + r->name() + " empire";
    r->add_message(RLO_EMPIRETOT, msg);
    add_message(RLO_EMPIRETOT, r->name() + ": " + msg);

    for (y = 0; y < actual_sim_future; y++) {
      // calc total populations (land+orbit)

      for (p = race_list[i]->planet_table; p; p = p->rnext) {
	if (!p->evolving())
	  continue;

	r->total_pop[y] += p->population(y) / 100;
	r->total_hab[y] += p->habitability(y);
	r->total_res[y] += p->resources(y);
	r->total_rsrch[y] += p->research(y);
	r->total_min[y] += p->minerals(y);
	r->total_mg[y] += p->mining_rate(y);

	r->total_fact[y] += p->factories(y);
	r->total_mine[y] += p->mines(y);
	r->total_maxfact[y] += p->maxcfactories(y);
	r->total_maxmine[y] += p->maxcmines(y);
	r->total_unufact[y] += p->unused_factories(y);
	r->total_unumine[y] += p->unused_mines(y);
      }

      // add in people in fleets
      for (f = r->fleet_table; f; f = f->rnext) {
	// problem here: how do we deal with "colonization" fleets?
	// just assume they sit in orbit like idiots
	if (y < f->eta || !f->_destin || f->_destin->owner() != f->_owner) {
	  r->total_opop[y] += f->_pop;
	  r->total_min[y] += f->_min;
	}
      }

      // take into account IS growth by pumping the opop total
      if (r->prt() == IS && y)
	r->total_opop[y] = (int)((double)r->total_opop[y] * pow(1.0 + (double)r->col_grow/200.0, y));
    }

    for (y = 0; y < actual_sim_future-1; y++) {
      r->total_growth[y] = (r->total_pop[y+1] + r->total_opop[y+1]) - 
                           (r->total_pop[y] + r->total_opop[y]);
      t = 10000.0 * (double)r->total_growth[y] / ((double)(r->total_pop[y] + r->total_opop[y]));
      r->total_gpctg[y] = (int)(t + 0.5);
      r->total_geff[y] = (int)((100.0 * t)/ r->col_grow + 0.5);
    }

    sprintf(tstr, "Population  (  orbit )     Growth    Grow%%     Geff%%");
    r->add_message(RLO_EMPIRETOT, tstr);
    add_message(RLO_EMPIRETOT, r->name() + ": " + tstr);
 
    for (y = 0; y < actual_sim_future-1; y++) {
      sprintf(tstr, "%8d00  (%6d00)    %5d00   %5.2f%%   %6.2f%%",
	      r->total_pop[y], r->total_opop[y], r->total_growth[y], 
	      (float)r->total_gpctg[y]/100.0, (float)r->total_geff[y]/100.0);
      r->add_message(RLO_EMPIRETOT, tstr);
      add_message(RLO_EMPIRETOT, r->name() + ": " + tstr);
    }

    sprintf(tstr, "-----------");
    r->add_message(RLO_EMPIRETOT, tstr);
    add_message(RLO_EMPIRETOT, r->name() + ": " + tstr);

    sprintf(tstr, "       Minerals (tot)              Mining (tot)          Mining / planet");
    r->add_message(RLO_EMPIRETOT, tstr);
    add_message(RLO_EMPIRETOT, r->name() + ": " + tstr);

    for (y = 0; y < actual_sim_future-1; y++) {
      sprintf(tstr, "%7di %7db %7dg   %6di %6db %6dg   %4di %4db %4dg",
		r->total_min[y][0], r->total_min[y][1], r->total_min[y][2],
		r->total_mg[y][0], r->total_mg[y][1], r->total_mg[y][2],
		r->total_mg[y][0]/race_planets[i], r->total_mg[y][1]/race_planets[i],
		r->total_mg[y][2]/race_planets[i]);
      r->add_message(RLO_EMPIRETOT, tstr);
      add_message(RLO_EMPIRETOT, r->name() + ": " + tstr);
    }

    sprintf(tstr, "-----------");
    r->add_message(RLO_EMPIRETOT, tstr);
    add_message(RLO_EMPIRETOT, r->name() + ": " + tstr);

    sprintf(tstr, "   factories  (unus)        mines    (unus)  resources  resource growth");
    r->add_message(RLO_EMPIRETOT, tstr);
    add_message(RLO_EMPIRETOT, r->name() + ": " + tstr);

    for (y = 0; y < actual_sim_future-1; y++) {
      sprintf(tstr, "%6d/%6d (%4d)   %6d/%6d (%4d)    %7d (%7d - %2.2f%%)",
	      r->total_fact[y], r->total_maxfact[y], r->total_unufact[y],
	      r->total_mine[y], r->total_maxmine[y], r->total_unumine[y],
	      r->total_res[y], r->total_res[y+1] - r->total_res[y],
	      (float)(r->total_res[y+1] - r->total_res[y]) / r->total_res[y] * 100.0);
      r->add_message(RLO_EMPIRETOT, tstr);
      add_message(RLO_EMPIRETOT, r->name() + ": " + tstr);
    }

    /*      fprintf(of, "%s: ----\n", r->_name.chars());
	    fprintf(of, "%s: Res %%  Research      En  We  Pr  Co  El  Bi  (gT tT rT)\n", r->_name.chars());

	    for (y = 0; y < actual_sim_future-1; y++)
	    fprintf(of, "%s: %2.2f%% %8d      %2d  %2d  %2d  %2d  %2d  %2d  (%2d %2d %2d)\n",
	    r->_name.chars(),
	    100.0*(float)r->total_rsrch[y]/(float)r->total_res[y], r->total_rsrch[y], 
	    r->tech[y][0], r->tech[y][1], r->tech[y][2], 
	    r->tech[y][3], r->tech[y][4], r->tech[y][5],
	    r->tform_tech[y][Grav], r->tform_tech[y][Temp], r->tform_tech[y][Rad]); */
  }
}


void stars_map::evolve_planets(void)
{
  int y;
  int i;
  planet* p;

  for (y = 1; y < actual_sim_future; y++) {

    for (i = 0; i < number_races; i++)
      if (race_list[i]->can_analyze) {
	for (p = race_list[i]->planet_table; p; p = p->rnext)
	  if (p->evolving()) {
	    p->init_turn();
	    p->do_turn();
	    p->advance_year();
	  }
	
	// we must now advance year for the race (tech, etc)
	race_list[i]->advance_year();
      }
  }

  // spread year 0 data on non-analyzed/non-owned planets
  for (p = unsorted_ptable; p; p = p->next)
    if (!p->owner() || !p->owner()->can_analyze)
      p->spread_year0_data();

  // perform final report
  for (i = 0; i < number_races; i++)
    if (race_list[i]->can_analyze)
      for (p = race_list[i]->planet_table; p; p = p->rnext)
	if (p->evolving())
	  p->report(Full);
}

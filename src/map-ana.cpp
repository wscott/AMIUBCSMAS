#include "starana-classes.h"


#include <string.h>




void stars_map::check_planets_step1(FILE* of)
{
  int i;
  planet* p;
  race* r;

  fprintf(of, "************* Planetary analysis (step 1) *************\n\n");

  for (p = unsorted_ptable; p; p = p->next) {

    if (p->auth_source != -1 && race_list[p->auth_source]->can_analyze) {
      // we have authoritative source & is a friend -> use data
      p->trusted_source = p->auth_source;

      fprintf(of, "%s: authoritative source %s assumed trusted for simulation\n", 
	      (const char*)p->_name, (const char*)race_list[p->auth_source]->_name);

    } else {
      for (p->rep_age = 20000, i = 0; i < number_races; i++)
	if (p->r_age[i] < 10000 && p->r_age[i] < p->rep_age) {
	  p->rep_age = p->r_age[i];
	  p->trusted_source = i;
	} else if (p->r_age[i] == p->rep_age) {
	  if ( (race_list[i]->reliab + 10*(i == p->auth_source)) >
	       (race_list[p->trusted_source]->reliab + 10*(p->trusted_source == p->auth_source))) {
	    fprintf(of, "%s: %s data preferred over %s data\n", 
		    (const char*)p->_name, (const char*)race_list[i]->_name, 
		    (const char*)race_list[p->trusted_source]->_name);

	    p->trusted_source = i;
	  } else
	    fprintf(of, "%s: %s data preferred over %s data\n", 
		    (const char*)p->_name, (const char*)race_list[p->trusted_source]->_name,
		    (const char*)race_list[i]->_name);
	}
    }

    if (p->trusted_source == -1) {
      //      fprintf(of, "%s: no data available on planet\n", p->_name.chars());

    } else {
      fprintf(of, "%s: data from %s used as trusted source\n", 
	      (const char*)p->_name, (const char*)race_list[p->trusted_source]->_name);

      if (p->trusted_source != p->auth_source && p->_owner &&
	  p->_owner->can_analyze)
	fprintf(of, "%s: TRUSTED != AUTHORITATIVE AND YOU WANT SIMULATION!!!!\n",
	      (const char*)p->_name);
      
      // set actual values
      p->_owner = p->r_owner[p->trusted_source];
      p->starbase = p->r_starbase[p->trusted_source];
      p->_pop[0] = p->r_pop[p->trusted_source];
      p->_stats[0][0] = p->r_stats[p->trusted_source][0];
      p->_stats[0][1] = p->r_stats[p->trusted_source][1];
      p->_stats[0][2] = p->r_stats[p->trusted_source][2];
      p->ori_stats[0] = p->r_oristats[p->trusted_source][0];
      p->ori_stats[1] = p->r_oristats[p->trusted_source][1];
      p->ori_stats[2] = p->r_oristats[p->trusted_source][2];
      p->_min_conc[0] = p->r_minconc[p->trusted_source];

      if (p->_owner)
	p->_habitab[0] = p->r_hab[p->_owner->id];

      p->check_data(of);
    }

    p->set_power();
  }

  // report planet habitability for all viewpoints

  // header (we assume at least 1 race to analyze)
  fprintf(of, "\n----- Planet Habitability Report -----\n\nPlanet            ");

  for (i = 0; i < number_races; i++)
    if (race_list[i]->can_analyze)
      fprintf(of, "%18s", (const char*)race_list[i]->_names);

  fprintf(of, "\n");

  for (p = unsorted_ptable; p; p = p->next)
    if (p->trusted_source != -1) {
      if (p->ori_stats[Grav] != -10) {
	fprintf(of, "%-18s ", (const char*)p->_name);

	for (i = 0; i < number_races; i++) {
	  r = race_list[i];

	  if (r->can_analyze) {
	    // output reported habitability
	    if (p->r_age[i] != 10000)
	      fprintf(of, " %3d%% ", p->r_hab[i]);
	    else
	      fprintf(of, "      ");

	    // output estimated habitability
	    fprintf(of, " %3d%%(%3d%%) ", p->hab_now(r), p->hab_when_max_terraformed(r));
	  }
	}

	fprintf(of, "\n");

      } else
	fprintf(of, "%-18s ....reported, but no planetary info.....\n", 
		(const char*)p->_name);
    }

  fprintf(of, "\n\n");
  fflush(of);
}



void stars_map::check_fleets(FILE* of)
{
  fleet* f;
  int i;

  fprintf(of, "****************** Fleet Analysis ******************\n\n");

  for (i = 0; i < number_races; i++)
    for (f = race_list[i]->fleet_table; f; f = f->rnext)
      f->check_data(game_map->report_log);

  fprintf(of, "\n\n");
  fflush(of);
}



void stars_map::find_breeders(planet* p, FILE* of)
{
  planet* source;
  planet* s_list = NULL;
  int dist;
  planet* op2;
  planet* p2;

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
    fprintf(of, "%s pop sources:", (const char*)p->header);

    for (source = s_list; source && source->distance(p) <= PARmax_search_distance;
	 source = source->tnext)
      if (source->p_type == planet::BREEDER)
	fprintf(of, "  %s (%.1f/%d)", (const char*)source->_name, 
		(float)source->capacity(0)/10.0, source->distance(p) / 81 + 1);
      else
	fprintf(of, "  [%s (%.1f @ %d)]", (const char*)source->_name, 
		(float)source->capacity(0)/10.0, source->distance(p) / 81 + 1);

    fprintf(of, "\n");
  }
}



void stars_map::find_minerals(planet* p, FILE* of, const int mt)
{
  planet* source;
  planet* s_list = NULL;
  int dist;
  planet* op2;
  planet* p2;

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
    fprintf(of, "%s %s sources:", (const char*)p->header,
	    (mt)? ((mt==1)? "boranium" : "germanium") : "ironium");

    for (source = s_list; source && source->distance(p) < PARmax_search_distance;
	 source = source->tnext)
      fprintf(of, "  %s (%d/%d @ %d)", (const char*)source->_name,
	      -source->need_min[mt], source->_mineral[0][mt],
	      source->distance(p) / 81 + 1);

    fprintf(of, "\n");
  }
}



void stars_map::check_planets_step2(FILE* of)
{
  planet* p;
  int i;

  // check growth/germanium/min shortages, etc.
  fprintf(of, "************* Planetary analysis (step 2) *************\n\n");

  // select planet types
  for (p = unsorted_ptable; p; p = p->next) {
    if (!p->_owner || !p->_owner->can_analyze)
      continue;

    if (p->p_type == planet::UNKNOWN) {
      fprintf(of, "%s planet type undefined!!!\n", (const char*)p->header);
      continue;
    }

    p->pop_needs();
    p->min_needs();
  }

  for (p = unsorted_ptable; p; p = p->next) {
    if (!p->_owner || !p->_owner->can_analyze)
      continue;

    p->title(of);

    // do evolution
    for (i = 0; i <= sim_future(); i++)
      p->print_messages(of, i);

    p->report_growth();
    p->report_mining();

    fprintf(of, "%s xcng matrix: %d - %d/%d/%d\n", (const char*)p->header, 
	    p->need_pop, p->need_min.iron, p->need_min.bora, p->need_min.germ);

    // check pop/mineral offer/demand
    p->print_gmessages(of);

    // report sources of pop/min
    if (p->need_pop > 0)
      find_breeders(p, of);

    for (i = 0; i < 3; i++)
      if (p->need_min[i] > 0)
	find_minerals(p, of, i);
  }

  fprintf(of, "\n\n");
  fflush(of);
}




void stars_map::empire_report(FILE* of)
{
  int i, y;
  race* r;
  planet* p;
  fleet* f;
  double t;

  fprintf(of, "****************** Empire evolution *******************\n\n");

  for (i = 0; i < number_races; i++) {

    r = race_list[i];

    if (!r->can_analyze || race_planets[i] == 0)
      continue;

    fprintf(of, "%s: ************** Report of %s empire\n", (const char*)r->_name, (const char*)r->_name);

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
	if (y < f->eta || !f->destin || f->destin->owner() != f->_owner) {
	  r->total_opop[y] += f->pop;
	  r->total_min[y] += f->min;
	}
      }

      // take into account IS growth by pumping the opop total
      if (r->prt() == IS && y)
	r->total_opop[y] = (int)((double)r->total_opop[y] * pow(1.0 + (double)r->col_grow/100.0, y));
    }

    for (y = 0; y < actual_sim_future-1; y++) {
      r->total_growth[y] = (r->total_pop[y+1] + r->total_opop[y+1]) - 
                           (r->total_pop[y] + r->total_opop[y]);
      t = 10000.0 * (double)r->total_growth[y] / ((double)(r->total_pop[y] + r->total_opop[y]));
      r->total_gpctg[y] = (int)(t + 0.5);
      r->total_geff[y] = (int)((100.0 * t)/ r->col_grow + 0.5);
    }

    fprintf(of, "%s: Population  (  orbit )     Growth    Grow%%     Geff%%\n", (const char*)r->_name);
 
    for (y = 0; y < actual_sim_future-1; y++)
      fprintf(of, "%s: %8d00  (%6d00)    %5d00   %5.2f%%   %6.2f%%\n", (const char*)r->_name, 
	      r->total_pop[y], r->total_opop[y], r->total_growth[y], 
	      (float)r->total_gpctg[y]/100.0, (float)r->total_geff[y]/100.0);

    fprintf(of, "%s: ----\n", (const char*)r->_name);
    fprintf(of, "%s:        Minerals (tot)              Mining (tot)          Mining / planet\n",
	    (const char*)r->_name);

    for (y = 0; y < actual_sim_future-1; y++)
      fprintf(of, "%s: %7di %7db %7dg   %6di %6db %6dg   %4di %4db %4dg\n", (const char*)r->_name,
	      r->total_min[y][0], r->total_min[y][1], r->total_min[y][2],
	      r->total_mg[y][0], r->total_mg[y][1], r->total_mg[y][2],
	      r->total_mg[y][0]/race_planets[i], r->total_mg[y][1]/race_planets[i],
	      r->total_mg[y][2]/race_planets[i]);

    fprintf(of, "%s: ----\n", (const char*)r->_name);
    fprintf(of,
	    "%s:    factories  (unus)        mines    (unus)  resources  resource growth\n",
	    (const char*)r->_name);

    for (y = 0; y < actual_sim_future-1; y++)
      fprintf(of, "%s: %6d/%6d (%4d)   %6d/%6d (%4d)    %7d (%7d - %2.2f%%)\n",
	      (const char*)r->_name,
	      r->total_fact[y], r->total_maxfact[y], r->total_unufact[y],
	      r->total_mine[y], r->total_maxmine[y], r->total_unumine[y],
	      r->total_res[y], r->total_res[y+1] - r->total_res[y],
	      (float)(r->total_res[y+1] - r->total_res[y]) / r->total_res[y] * 100.0);

    /*    fprintf(of, "%s: ----\n", r->_name.chars());
    fprintf(of, "%s: Res %%  Research      En  We  Pr  Co  El  Bi  (gT tT rT)\n", r->_name.chars());

    for (y = 0; y < actual_sim_future-1; y++)
      fprintf(of, "%s: %2.2f%% %8d      %2d  %2d  %2d  %2d  %2d  %2d  (%2d %2d %2d)\n",
	      r->_name.chars(),
	      100.0*(float)r->total_rsrch[y]/(float)r->total_res[y], r->total_rsrch[y], 
	      r->tech[y][0], r->tech[y][1], r->tech[y][2], 
	      r->tech[y][3], r->tech[y][4], r->tech[y][5],
	      r->tform_tech[y][Grav], r->tform_tech[y][Temp], r->tform_tech[y][Rad]); */
  }

  fflush(of);
}



void stars_map::evolve_planets(FILE* of)
{
  int y;
  int i;
  planet* p;

  //  fprintf(of, "************* Planetary evolution *************\n\n");  

  for (y = 1; y < actual_sim_future; y++) {
    //    fprintf(of, "----- YEAR %d -----------------------------------------\n", 
    //	    game_year + y);

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

  // spread year 0 data on non-analyzed planets
  for (i = 0; i < number_races; i++)
    if (!race_list[i]->can_analyze)
      for (p = race_list[i]->planet_table; p; p = p->rnext)
	p->spread_year0_data();

  // perform final report
  for (i = 0; i < number_races; i++)
    if (race_list[i]->can_analyze)
      for (p = race_list[i]->planet_table; p; p = p->rnext)
	if (p->evolving())
	  p->report(Full);

  fprintf(of, "\n\n");
  fflush(of);
}

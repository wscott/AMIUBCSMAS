#include "starana-classes.h"



// idiotic inline function returning the pointer to the end of a char[]
// (useful in sprintfs)
inline
char* e(char* s)
{
  return s + strlen(s);
}


// data is % limit * 10, breeder, production, newcolony, generic, mining

int planet::planet_pop_needs[][6] = {
      {  50,  1,  1,  1,  1,  1 },
      { 250,  0,  1,  0,  0,  1 },
      { 330, -1,  1,  0,  0,  1 },
      { 480, -1,  1, -1, -1,  0 },
      { 600, -1,  0, -1, -1,  0 },
      { 800, -1,  0, -1, -1, -1 },
      {1000, -1,  1, -1, -1,  1 }
};



void planet::check_data(void)
{
  int i;

  // see if we have some kind of stats
  if (_stats[0][Grav] == -10 && ori_stats[Grav] != -10) {
    _stats[0][Grav] = ori_stats[Grav];
    _stats[0][Temp] = ori_stats[Temp];
    _stats[0][Rad] = ori_stats[Rad];

    game_map->add_message(RLO_PLASTATS, 
			  header + "currents stats assumed equal to original stats");

  } else if (_stats[0][Grav] != -10 && ori_stats[Grav] == -10) {
    ori_stats[Grav] = _stats[0][Grav];
    ori_stats[Temp] = _stats[0][Temp];
    ori_stats[Rad] = _stats[0][Rad];

    game_map->add_message(RLO_PLASTATS, 
			  header + " original stats assumed equal to CURRENT stats - beware!!");
  }

  if (homeworld) {
    if (_min_conc[0].iron < 30)
      _min_conc[0].iron = 30;
    if (_min_conc[0].bora < 30)
      _min_conc[0].bora = 30;
    if (_min_conc[0].germ < 30)
      _min_conc[0].germ = 30;
  }

  if (_owner)
    header = _owner->_name + "-" + _name + ":";
  else {
    header = "<unowned>-" + _name + ":";
    return;
  }

  if (_pop[0] == -1) {
    _pop[0] = (get_parameter(myString("acceleratedBBS")))? (100000 + (_owner->col_grow - 15) * 5000) : 25000;

    if (_owner->lrt(LSP))
      _pop[0] = (int)(0.7 * _pop[0]);
  }

  // fix defense coverage
  if (_defenses[0] < 0) {
    if (def_coverage[0] < 0) {
      // uh?
      _defenses[0] = def_coverage[0] = 0;

    } else {
      // guess number from def%
      _defenses[0] = _owner->compute_def_from_percent(def_coverage[0]);

      if (_defenses[0] > 100) {
	_defenses[0] = 100;
	_owner->add_message(RLO_PLANETINI, 
			    header + " weird def coverage %....check energy tech level!");
	game_map->add_message(RLO_PLANETINI, 
			      header + " weird def coverage %....check energy tech level!");
      }
    }

  } else if (def_coverage[0] < 0) {
    def_coverage[0] = _owner->compute_percent_from_def(_defenses[0]);
  }

  // choose if we have scanners or not on the planet
  if (scan_normal == -1)
    if (auth_source == -1 && _owner) {
      // guess
      if (_pop[0] >= PARmin_pop_for_scanner) {
	scan_pen = _owner->pla_penscan_radius(0);
        scan_normal =  _owner->pla_scan_radius(0);
      } else {
	scan_normal = 0;
	scan_pen = 0;
      }	
    } else {
      // no scanner
      scan_normal = 0;
      scan_pen = 0;
    }

  // decide if we do sim or not
  if (!_owner->can_analyze)
    return;

  // check if we have planetary stats
  if (_stats[0][Grav] != -10) {
    if (_owner->prt() == CA) {
      // do instaforming
      game_map->add_message(RLO_PLANETINI,
			    header + " unbelievable CA powers instaform the world to " +
			    int_to_str(hab_when_max_terraformed()) + "%!");
      instaform();
    }

    calc_habitability();
  } else {
    if (_habitab[0] == -100)
      game_map->add_message(RLO_ERROR, 
			    header + " no planetary data and no hab% info! - sim will be pure crap");
    else
      game_map->add_message(RLO_ERROR, 
			    header + " no planetary data - terraforming sim will be wrong");
  }

  // sanity check on mineral concentrations
  if (_min_conc[0].iron <= 0 || _min_conc[0].bora <= 0 || _min_conc[0].germ <= 0) {
    game_map->add_message(RLO_ERROR,
			  header + " ZERO mineral concentrations!?!?!? Assuming 1, but check....");

    for (i = 0; i < 3; i++)
      if (_min_conc[0][i] <= 0)
	_min_conc[0][i] = 1;
  }

  if (p_type == planet::UNKNOWN)
    guess_type();

  if (mine_year[0].iron <= 0) {
    for (i = 0; i < 3; i++)
      if (_min_conc[0][i] >= 30)
	mine_year[0][i] = 12500 / _min_conc[0][i];
      else if (_min_conc[0][i] >= 3)
	mine_year[0][i] = 456;
      else
	mine_year[0][i] = 456 * 2;
  }

  if (!queue) {
    // use race's default queue
    if (_owner->default_queue) {
      // copy queue
      game_map->add_message(RLO_PLANETINI,
			    header + " default production queue used");

      for (queue_obj* qo = _owner->default_queue; qo; qo = qo->next)
	add_to_queue(new queue_obj(*qo));

    } else {
      game_map->add_message(RLO_PLANETINI,
			    header + " no production queue - assuming default 500f/500m/5t");
      add_to_queue(true, myString("factory"), 500);
      add_to_queue(true, myString("mine"), 500);
      add_to_queue(true, myString("terraform"), 5);
    }
  }
}



myString planet::title(void) const
{
  return header + "--------- " + type_name()+ "-----------";
}



void planet::guess_type(void)
{
  if (p_type == UNKNOWN) {
    // try to guess planet type

    if (_habitab[0] < -10 && capacity(0) < 500) {
      game_map->add_message(RLO_PLANETINI, 
			    header + " type unknown, but looks like a looting area...");
      p_type = LOOTING;

    } else if (_habitab[0] < 0 || resources(0) < 350 ||
	_pop[0] < 200000) {
      game_map->add_message(RLO_PLANETINI, 
			    header + " type unknown, but looks like a new colony");
      p_type = NEWCOLONY;

    } else if (_habitab[0] >= 70 && capacity(0) > 400 &&
	       (100 * _factories[0] / maxcfactories(0)) > 80 &&
	       _mineral[0].total() > 6000) {
      game_map->add_message(RLO_PLANETINI,
			    header + " type unknown, but looks like a production center");
      p_type = PRODUCTION;
    } else if (_habitab[0] >= 80 && capacity(0) < 480 &&
	       _min_conc[0].total() < 55) {
      game_map->add_message(RLO_PLANETINI,
			    header + " type unknown, but looks like a population breeder");
      p_type = BREEDER;
    } else if (0) {
      // MINING
    } else {
      game_map->add_message(RLO_PLANETINI,
			    header + " type unknown, no clear guess, marked as generic");
      p_type = GENERIC;
    }
  }
}



void planet::pop_needs(void)
{
  int oldf, newf;
  int i;

  need_pop = 0;

  if (p_type == LOOTING || p_type == UNKNOWN)
    return; // don't care

  oldf = capacity(0);

  // red/yellow world ignores type (except looting) and assumes newcolony
  if (_habitab[0] < 0) {
    if (oldf < 1000)
      need_pop = 1;
    else if (oldf > 3000)
      need_pop = -1;
    else
      for (i = 1; i < 6; i++) {
	oldf = capacity(i - 1);
	newf = capacity(i);

	if (oldf >= 1000 && newf < 1000)
	  need_pop = 1;
      }
  } else if (oldf > 1000)
    need_pop = -1;
  else {
    i = -1;
    do {
      i++;
      if (oldf < planet_pop_needs[i][0])
	need_pop = planet_pop_needs[i][(int)p_type - 1];
    } while (planet_pop_needs[i][0] != 1000);
  }
}



void planet::report_growth(void)
{
  int oldf, newf;
  int i;
  int need_pop = 0;
  char tmsg[512];

  if (p_type == LOOTING)
    return; // don't care

  oldf = capacity(0);

  // red/yellow world ignores type (except looting) and assumes newcolony
  if (_habitab[0] < 0) {
    if (oldf < 1000)
      add_gmessage(RLO_PLAPOPSTAT, "red-yellow: population below 100%!");

    if (oldf > 3000)
      add_gmessage(RLO_PLAPOPSTAT, 
		   "red-yellow planet filling beyond 300% - USELESS overpopulation!!");

    for (i = 1; i < game_map->sim_future(); i++) {
      oldf = capacity(i - 1);
      newf = capacity(i);

      if (oldf >= 1000 && newf < 1000) {
	sprintf(tmsg, "red-yellow: pop will drop below filling 100%% in %d years", i);
	add_message(RLO_PLAPOPSTAT, tmsg);
	need_pop = true;
      }
    }
  } else {
    if (oldf < 250)
      add_gmessage(RLO_PLAPOPSTAT, "planet filling is below 25%");
    else if (oldf < 330)
      add_gmessage(RLO_PLAPOPSTAT, "planet filling is in 25%-33% range");
    else if (oldf < 480)
      add_gmessage(RLO_PLAPOPSTAT, "planet filling is in 33%-48% range");
    else if (oldf < 800)	   
      add_gmessage(RLO_PLAPOPSTAT, "planet filling is in 48%-80% range - suboptimal");
    else if (oldf < 1000)	   
      add_gmessage(RLO_PLAPOPSTAT, "planet filling is above 80% - max pop!");
    else if (oldf == 1000)	   
      add_gmessage(RLO_PLAPOPSTAT, "planet is filled");
    else if (oldf < 3000)
      add_gmessage(RLO_PLAPOPSTAT, "planet filling is beyond 100% - overpopulated");
    else
      add_gmessage(RLO_PLAPOPSTAT, "planet filling is beyond 300% - USELESS overpopulation!");

    for (i = 1; i < game_map->sim_future(); i++) {
      oldf = capacity(i-1);
      newf = capacity(i);

      if (oldf < 250 && newf >= 250) {
	sprintf(tmsg, "25%% filling boundary crossed in %d years", i - 1);
	add_gmessage(RLO_PLAPOPSTAT, tmsg);
      }
      if (oldf < 330 && newf >= 330) { 
	sprintf(tmsg, "33%% filling boundary crossed in %d years", i - 1);
	add_gmessage(RLO_PLAPOPSTAT, tmsg);
      }	
      if (oldf < 480 && newf >= 480) {
	sprintf(tmsg, "48%% filling boundary crossed in %d years", i - 1);
	add_gmessage(RLO_PLAPOPSTAT, tmsg);
      }
      if (oldf < 800 && newf >= 800) {
	sprintf(tmsg, "80%% filling boundary crossed in %d years", i - 1);
	add_gmessage(RLO_PLAPOPSTAT, tmsg);
      }
    }
  }
}



void planet::min_needs(void)
{
  _mintype still_needed;
  _mintype avg_mining;
  int i;

  avg_mining = mining_rate(0);

  if (p_type == UNKNOWN)
    return;

  else if (p_type == LOOTING) {
    need_min.iron = -_mineral[0].iron;
    need_min.bora = -_mineral[0].bora;
    need_min.germ = -_mineral[0].germ;

  } else if (p_type == PRODUCTION) {
    if (_mineral[0].iron < 3500)
      need_min.iron = 20000;
    else if (_mineral[0].iron > 25000)
      need_min.iron = 25000 - _mineral[0].iron;
    if (_mineral[0].bora < 2500)
      need_min.bora = 10000;
    else if (_mineral[0].bora > 12000)
      need_min.iron = 12000 - _mineral[0].bora;
    if (_mineral[0].germ < 2000)
      need_min.germ = 2000;
    else if (_mineral[0].germ > 4000)
      need_min.germ = 4000 - _mineral[0].germ;
 
  } else {
    if (p_type != NEWCOLONY && !starbase) {
      still_needed.iron += 400;
      still_needed.bora += 250;
      still_needed.germ += 250;
    }

    int exp_fact = _factories[0];
    int y;

    for (y = 0; y < 5; y++)
      exp_fact += (exp_fact * _owner->fact_res / 10 + pop(y) / _owner->col_res)
	          / _owner->fact_cost;

    exp_fact = min(exp_fact, maxcfactories(5)) - _factories[0];
    exp_fact = max(0, exp_fact);

    still_needed.germ += exp_fact * _owner->fact_germ - avg_mining.germ * 3;
    still_needed -= avg_mining * 2;
    still_needed -= _mineral[0];

    if (p_type == BREEDER) {
      for (i = 0; i < 3; i++)
	if (still_needed[i] > 0)
	  need_min[i] = still_needed[i];
	else if (still_needed[i] <= -250)
	  need_min[i] = still_needed[i];

    } else if (p_type == NEWCOLONY) {
      for (i = 0; i < 3; i++)
	if (still_needed[i] >= 0)
	  need_min[i] = still_needed[i];
	else if (still_needed[i] <= -500)
	  need_min[i] = still_needed[i] + 300;
    } else if (p_type == GENERIC) {
      for (i = 0; i < 3; i++)
	if (still_needed[i] > 0)
	  need_min[i] = still_needed[i];
	else if (still_needed[i] <= -1000)
	  need_min[i] = still_needed[i] + 750;
    }
  }
}



void planet::report_mining(void)
{
  int i;
  char tmsg[512];
  _mintype shortage;
  char* minname;

  if (need_min.total()) {
    strcpy(tmsg, "minerals:");

    if (need_min.iron > 0)
      sprintf(e(tmsg), "  need ironium (%d)", need_min.iron);
    else if (need_min.iron < 0)
      sprintf(e(tmsg), "  offer ironium (%d)", -need_min.iron);

    if (need_min.bora > 0)
      sprintf(e(tmsg), "  need boranium (%d)", need_min.bora);
    else if (need_min.bora < 0)
      sprintf(e(tmsg), "  offer boranium (%d)", -need_min.bora);

    if (need_min.germ > 0)
      sprintf(e(tmsg), "  need GERMANIUM (%d)", need_min.germ);
    else if (need_min.germ < 0)
      sprintf(e(tmsg), "  offer GERMANIUM (%d)", -need_min.germ);

    add_message(RLO_PLAMINSTAT, tmsg);
  }

  // if shortage is detected then comment on concentration
  for (i = 0; i < game_map->sim_future(); i++)
    shortage += _minshortage[i];

  for (i = 0; i < 3; i++)
    if (shortage[i]) {
      minname = ( (i == 0)? "ironium" : ( (i == 1)? "boranium" : "germanium" ) );

      if (_min_conc[0][i] < 25)
	sprintf(tmsg, "ridiculous %s concentration (%d) - ship some",
		minname, _min_conc[0][i]);
      else if (_min_conc[0].germ < 60)
	sprintf(tmsg, "medium %s concentration (%d) - production slowed",
		minname, _min_conc[0][i]);
      else
	sprintf(tmsg, "%s concentration (%d) is good - slight production slowdown",
		minname, _min_conc[0][i]);
    
      add_gmessage(RLO_PLAMINSTAT, tmsg);
    }

/*
  // analyze germanium usage
  // basically: if germanium is low and production is non-maxed
  // factories but mines this means that we needed germanium
  for (i = 1; i < game_map->sim_future(); i++)
    if (factories(i) != maxcfactories(i) && _mineral[i].germ < 10 &&
	mines(i-1) != mines(i)) {

      // compute resources devoted to something else
      pfact = resources(i-1) / _owner->fact_cost;
      if (factories(i-1) + pfact > maxcfactories(i))
	pfact = maxcfactories(i) - factories(i-1); // "potential factories"

      // missed factories
      mfact = pfact - (factories(i) - factories(i-1));

      // since "half-factories" can be built this year, leading to MORE factories
      // than expected, a paranoia check is done
      if (mfact > 0) {
	sprintf(tmsg, "lack of %dkT of germ (missed %d/%d fact, but %d mines) in %d years",
		mfact * _owner->fact_germ, mfact, pfact,
		mines(i)-mines(i-1), i - 1);
	add_gmessage(PLA_MINSTATE, myString(tmsg));
	germ_status = true;
      }
    }

  if (germ_status) {
    if (_min_conc[0].germ < 25)
      sprintf(tmsg, "ridiculous germanium concentration (%d) - ship some",
	      _min_conc[0].germ);
    else if (_min_conc[0].germ < 60)
      sprintf(tmsg, "medium germanium concentration (%d) - developement slowed",
	      _min_conc[0].germ);
    else
      sprintf(tmsg, "germanium concentration (%d) is good - slight developement slowdown",
	      _min_conc[0].germ);
    
    add_gmessage(PLA_MINSTATE, tmsg);
  }
*/
}

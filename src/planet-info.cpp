#include "starana-classes.h"



race* planet::trustedsource(void) const
{
  if (trusted_source != -1)
    return game_map->find_race(trusted_source);
  else
    return NULL;
}



race* planet::authsource(void) const
{
  if (auth_source != -1)
    return game_map->find_race(auth_source);
  else
    return NULL;
}



int planet::hab_now(race* owner, int when) const
{
  int hab;

  when = fix_year(when);

  if (!owner)
    owner = _owner;

  // if we have the reported hab from that player we use it
  // COMMENT out to test planet formula
  /*  if (report_age[owner->id] != 10000)
    return r_hab[owner->id]; */

  if (owner->hab_min[Grav] == -100) // no racial hab info
    return -100;

  if (ori_stats[Grav] == -10) // no planetary info
    return -100;

  if (owner->prt() == CA)
    return hab_when_max_terraformed(owner, when);

  hab = habitability(_stats[when], owner);
  if (hab >= 0)
    hab = hab + 50;

  return hab / 100;
}



int planet::hab_when_max_terraformed(const race* owner, int when,
				     const int* tf_tech) const
{
  int hab;
  int d, i;
  int st[3];

  when = fix_year(when);

  if (!owner)
    owner = _owner;

  if (owner->hab_min[Grav] == -100) // no racial hab info
    return -100;

  if (ori_stats[Grav] == -10) // no planetary info
    return -100;

  // if no tform tech given then use the one from the race
  if (!tf_tech)
    tf_tech = owner->tform_tech[when];

  for (i = 0; i < 3; i++) {
    st[i] = ori_stats[i];

    d = st[i] - (owner->hab_min[i] + owner->hab_max[i]) / 2;
    if (abs(d) > tf_tech[i])
      d = sign(d) * tf_tech[i];

    st[i] -= d;
  }

  hab = habitability(st, owner);
  if (hab >= 0)
    hab = hab + 50;

  return hab / 100;
}



int planet::tform_left(int when) const
{
  int tfl = 0;
  int i, d, od;

  when = fix_year(when);

  if (_stats[when][Grav] == -10)
    return 0; // no tform info available

  for (i = 0; i < 3; i++)
    if (_owner->hab_min[i] != -1) {
      if (_stats[when][i] != (_owner->hab_min[i] + _owner->hab_max[i]) / 2) {
	od = abs(ori_stats[i] - (_owner->hab_min[i] + _owner->hab_max[i]) / 2);
	d = abs(_stats[when][i] - (_owner->hab_min[i] + _owner->hab_max[i]) / 2);

	if (od - d < _owner->tform_tech[when][i])
	  tfl += _owner->tform_tech[when][i] - (od - d);
      }
    }

  return tfl;
}



_mintype planet::mining_rate(int when) const
{
  _mintype mined;

  if (!evolving())
    return mined;

  when = fix_year(when);

  int i, my;

  for (i = 0; i < 3; i++) {
    my = min(_mines[when], _pop[when] * _owner->mine_ctrl / 10000);

    mined[i] = (_min_conc[when][i] * _owner->mine_eff * my + 50) / 1000;
  }

  return mined;
}



void planet::dump_queue(void)
{
  char tmsg[512];

  add_message(PLA_INTERNAL, String("  Active queue:"));
  for (queue_obj* qo = queue; qo; qo = qo->next) {
    if (qo->active) {
      sprintf(tmsg, "    %s%s (%d)", 
	      (qo->autob != queue_obj::Normal)? "autobuild " : "",
	      (const char*)qo->proto->_name, qo->count);
      add_message(PLA_INTERNAL, String(tmsg));
    }
  }
}



const int* planet::stats(int when) const
{
  when = fix_year(when);
  return _stats[when];
}



int planet::habitability(int when) const
{
  when = fix_year(when);
  return _habitab[when];
}


const char* planet::type_name(void) const
{
  if (!_owner)
    return "uninhabited";

  switch(p_type) {
  case UNKNOWN:
    return "undefined type??";
  case NEWCOLONY:
    return "new colony";
  case GENERIC:
    return "generic planet";
  case BREEDER:
    return "population breeder";
  case LOOTING:
    return "useless enemy planet to loot";
  case PRODUCTION:
    return "main production center";
  case MINING:
    return "main mining center";
  }

  return "<no type?>";
}





int planet::population(int when) const
{
  if (!_owner)
    return 0;

  when = fix_year(when);
  return _pop[when] / 100 * 100;
}



int planet::capacity(int when) const
{
  if (!_owner)
    return 0;

  when = fix_year(when);
  return _pop[when] * 1000 / maxpop(when);
}



int planet::maxpop(int when) const
{
  if (!_owner)
    return 0;

  when = fix_year(when);
  int eff_hab;
  
  // if we have auth source we can play with habitability
  // else we try to use hab_now for the requested race
  // if anything fails we just assume 100%....
  if (auth_source != -1)
    eff_hab = _habitab[when];
  else {
    eff_hab = hab_now();

    if (eff_hab == -100)
      eff_hab = 100;
  }

  // never below 5%
  if (eff_hab < 5)
    eff_hab = 5;

  return _owner->maxpop * eff_hab / 100;
}



int planet::pop(int when) const
{
  if (!_owner)
    return 0;

  when = fix_year(when);
  return _pop[when];
}



int planet::factories(int when) const
{
  if (!_owner)
    return 0;

  when = fix_year(when);
  return _factories[when];
}



int planet::defenses(int when) const
{
  if (!_owner)
    return 0;

  when = fix_year(when);
  return _defenses[when];
}



int planet::defense_coverage(int when) const
{
  if (!_owner)
    return 0;

  when = fix_year(when);
  return def_coverage[when];
}



const _mintype& planet::minerals(int when) const
{
  if (!_owner)
    return _mineral[0];

  when = fix_year(when);
  return _mineral[when];
}



const _mintype& planet::minshortage(int when) const
{
  if (!_owner)
    return _minshortage[0];

  when = fix_year(when);
  return _minshortage[when];
}



const _mintype& planet::min_conc(int when) const
{
  when = fix_year(when);
  return _min_conc[when];
}



int planet::maxfactories(int when) const
{
  if (!_owner)
    return 0;

  when = fix_year(when);
  return maxpop(when) * _owner->fact_ctrl / 10000;
}


int planet::maxdefenses(int when) const
{
  if (!_owner)
    return 0;

  when = fix_year(when);
  return 100; /* NEED THE FORMULA */
}


int planet::maxcfactories(int when) const
{
  if (!_owner)
    return 0;

  when = fix_year(when);
  return min(_pop[when], maxpop(when)) * _owner->fact_ctrl / 10000;
}



int planet::mines(int when) const
{
  if (!_owner)
    return 0;

  when = fix_year(when);
  return _mines[when];
}



int planet::maxmines(int when) const
{
  if (!_owner)
    return 0;

  when = fix_year(when);
  return maxpop(when) * _owner->mine_ctrl / 10000;
}



int planet::maxcmines(int when) const
{
  if (!_owner)
    return 0;

  when = fix_year(when);
  return min(_pop[when], maxpop(when)) * _owner->mine_ctrl / 10000;
}



int planet::maxcdefenses(int when) const
{
  if (!_owner)
    return 0;

  when = fix_year(when);
  return 100; /* NEED THE FORMULA */
}



int planet::unused_factories(int when) const
{
  if (!_owner)
    return 0;

  when = fix_year(when);
  int u = _factories[when] - maxcfactories(when);
  return (u > 0)? u : 0;
}



int planet::unused_mines(int when) const
{
  if (!_owner)
    return 0;

  when = fix_year(when);
  int u = _mines[when] - maxcmines(when);
  return (u > 0)? u : 0;
}



bool planet::need_more_mines(int when) const
{
  if (!_owner)
    return 0;

  when = fix_year(when);
  if (_mines[when] >= (_pop[when] * _owner->mine_ctrl / 10000))
    return false;
  else
    return true;
}



bool planet::need_more_factories(int when) const
{
  if (!_owner)
    return 0;

  when = fix_year(when);
  if (_factories[when] >= (_pop[when] * _owner->fact_ctrl / 10000))
    return false;
  else
    return true;
}



int planet::resources(int when)
{
  if (!_owner)
    return 0;

  when = fix_year(when);

  if (res[when] == -1) {
    // calculate the value
    int popres = 0;

    if (pop(when) <= maxpop(when))
      popres = pop(when) / _owner->col_res;
    else {
      popres = maxpop(when) / _owner->col_res;

      if (pop(when) <= 3 * maxpop(when))
	popres += (pop(when) - maxpop(when)) / 2 / _owner->col_res;
      else
	popres += maxpop(when) / _owner->col_res;
    }

    res[when] = popres + _owner->fact_res * 
                min(factories(when), pop(when) * _owner->fact_ctrl / 10000) / 10;
  }

  return res[when];
}



int planet::tot_resources(int when) const
{
  if (!_owner)
    return 0;

  when = fix_year(when);

  return _tot_resources[when];
}



int planet::research(int when) const
{
  if (!_owner)
    return 0;

  when = fix_year(when);

  return _research[when];
}


void planet::output(FILE* of, int when) const
{
  when = fix_year(when);

  fprintf(of, "planet \"%s\" {\n", (const char*)_name);
  if (_owner)
    fprintf(of, "\t_owner \"%s\"\n", (const char*)_owner->_name);
  fprintf(of, "\toriginal_stats %d %d %d\n", ori_stats[0], ori_stats[1], ori_stats[2]);
  fprintf(of, "\tstats %d %d %d\n", _stats[when][0], _stats[when][1], _stats[when][2]);
  fprintf(of, "\tmineral_conc %d %d %d\n", _min_conc[when][0], _min_conc[when][1], _min_conc[when][2]);
  fprintf(of, "\tmine_years %d %d %d\n", mine_year[when][0], mine_year[when][1], mine_year[when][2]);
  fprintf(of, "\tminerals %d %d %d\n", _mineral[when][0], _mineral[when][1], _mineral[when][2]);
  fprintf(of, "\tpopulation %d\n", _pop[when]);
  fprintf(of, "\tinstallations %d %d\n", _factories[when], _mines[when]);
  fprintf(of, "\tposition %d %d\n}\n", pos.x, pos.y);
}



void planet::report(const report_type rt)
{
  char tmsg[512];

  if (rt == Graph)
    sprintf(tmsg, " %d %d %d %d %d ", pop(), habitability(), capacity()/10, resources(), tot_resources());

  else {
    sprintf(tmsg, "%7d (%3d%%) %3d%% %4df %4dm %4dres %4di %4db %4dg %2diC %2dbC %2dgC",
	    population(), capacity()/10, habitability(),
	    factories(), mines(), resources(),
	    minerals().iron, minerals().bora, minerals().germ,
	    min_conc().iron, min_conc().bora, min_conc().germ);

    if (rt == Total) {
      add_message(PLA_REPORTS, String(tmsg));
      sprintf(tmsg, "%2d[%2d] (%2d-%2d)-> %2d%% / %2d[%2d] (%2d-%2d)-> %2d%% / %2d[%2d] (%2d-%2d)-> %2d%%",
	      stats()[Grav], ori_stats[Grav], _owner->hab_min[Grav], _owner->hab_max[Grav], 
	      (_owner->hab_min[Grav] + _owner->hab_max[Grav]) / 2 - stats()[Grav],
	      stats()[Temp], ori_stats[Temp], _owner->hab_min[Temp], _owner->hab_max[Temp], 
	      (_owner->hab_min[Temp] + _owner->hab_max[Temp]) / 2 - stats()[Temp],
	      stats()[Rad], ori_stats[Rad], _owner->hab_min[Rad], _owner->hab_max[Rad], 
	      (_owner->hab_min[Rad] + _owner->hab_max[Rad]) / 2 - stats()[Rad]);
    }
  }

  add_message(PLA_REPORTS, String(tmsg));
}



message* planet::next_message(message* m, int when) const
{
  message* nm;

  if (m)
    nm = m->next;
  else
    nm = msg_table[when];

  while (nm && nm->filtered())
    nm = nm->next;

  return nm;
}



message* planet::next_gmessage(message* m) const
{
  message* nm;

  if (m)
    nm = m->next;
  else
    nm = global_msgs;

  while (nm && nm->filtered())
    nm = nm->next;

  return nm;
}



void planet::print_messages(FILE* of, int when) const
{
  when = fix_year(when);

  for (message* m = next_message(NULL, when); m; m = next_message(m, when)) {
    fprintf(of, "%s ", (const char*)header);
    m->print(of);
  }
}


void planet::print_gmessages(FILE* of) const
{
  for (message* m = next_gmessage(NULL); m; m = next_gmessage(m)) {
    fprintf(of, "%s ", (const char*)header);
    m->print(of);
  }
}

#include "starana-classes.h"

#include <string.h>


const double SQR3 = 1.73205080756887729;


starbase_type planet::get_starbase_power(const myString& name)
{
  if (!name.length())
    return NoStarbase;

  myString checkname = name;

  // determine base hull
  // step 1: check in race design table
  design* d;

  // if we have a design we just turn the name into the hull name
  if ( (d = _owner->find_design(name, true)) )
    checkname = d->basehull()->name;

  // step 2: check default hull names
  // BE CAREFUL WITH THIS (an enemy calling a base "Orbital Fort" will trick you
  if (checkname.index("Orbital Fort") == 0)
    return OrbitalFort;
  if (checkname.index("Space Dock") == 0)
    return SpaceDock;
  if (checkname.index("Space Station") == 0 || checkname.index("Starbase") == 0)
    return SpaceStation;
  if (checkname.index("Ultra Station") == 0)
    return UltraStation;
  if (checkname.index("Death Star") == 0)
    return DeathStar;

  return ErrorInName;
}



planet::planet(const myString& n) : 
        next(NULL), rnext(NULL), snext(NULL),
	_name(n), stars_id(-1), header("<unknown>"+n), p_type(UNKNOWN),
	homeworld(false),
        auth_source(-1), trusted_source(-1),
	scan_normal(-1), scan_pen(-1), 
	starbase(""), stb_type(NoStarbase), stb_design(NULL), stb_damage(-1), 
	gatemass(0), gaterange(0), 
	driverdest(NULL), driverwarp(0),
	routing(NULL), power(0),
	_owner(NULL), queue(NULL), avail_res(0), need_pop(0),
	incoming(NULL), curr_year(0), 
        tnext(NULL)
{
  int i;
  
  for (i = 0; i < 16; i++) {
    r_starbase[i] = "";
    r_owner[i] = NULL;
    r_hab[i] = 0;
    r_mxhab[i] = 0;
    r_pop[i] = 0;
    r_age[i] = 10000;
    r_stats[i][Grav] = r_stats[i][Temp] = r_stats[i][Rad] = -10;
    r_oristats[i][Grav] = r_oristats[i][Temp] = r_oristats[i][Rad] = -10;
    r_minconc[i].clear();
    r_def_coverage[i] = 0;
  }

  for (i = 0; i < SIM_FUTURE; i++) {
    _pop_lsd[i] = 0;
    _pop[i] = 0;
    _factories[i] = 0;
    _mines[i] = 0;
    _defenses[i] = -1;
    def_coverage[i] = -1;
    _stats[i][Grav] = _stats[i][Temp] = _stats[i][Rad] = -10;
    _min_conc[i].clear();
    mine_year[i].clear();
    _mineral[i].clear();
    _minshortage[i].clear();
    _habitab[i] = -100;
    res[i] = -1;
    _research[i] = 0;
    _tot_resources[i] = 0;
    _tot_research[i] = 0;
  }
}


planet::~planet(void)
{
  clear_queue();
}



planet::planet(const planet& p)
{
  memcpy(this, &p, sizeof(planet)); // ok, this is criminal, so what?

  queue = NULL;
  snext = tnext = rnext = NULL;

  for (queue_obj* qo = p.queue; qo; qo = qo->next)
    add_to_queue(new queue_obj(*qo));
}


void planet::add_message(const _msgtype mt, const myString& m)
{
  msg_table[curr_year].add(mt, m);
}



void planet::add_gmessage(const _msgtype mt, const myString& m)
{
  global_msgs.add(mt, m);
}



void planet::evolve(const int from, const int len)
{
  int y;

  if (!evolving())
    return;

  curr_year = from;

  for (y = 0; y < len; y++) {
    init_turn();
    do_turn();
    advance_year();
  }

  // report final status
  report(Full);
}



bool planet::set_planet_stats(int* st, double g, const double& t, const double& r) 
{
  int i;
  int g_third;

  if (g < gravity_table[0] || g > gravity_table[100] ||
      t < -200 || t > 200 || r < 0 || r > 100)
    yyerror("planetary stats out of range");

  // these are easy....
  st[1] = (int)(t + 200) / 4;
  st[2] = (int)r;

  // use the 3rd digit on grav to resolve ambiguity
  g_third = (int)(g * 1000 + 0.5) - (int)(g * 100 + 0.5) * 10;
  g -= (double) g_third / 1000;

  st[0] = -100;
  for (i = 0; i < 101; i++)
    if (g == gravity_table[i])
      break;

  if (i == 101)
    yyerror("invalid grav value");

  st[0] = i;

  // check and (maybe) resolve ambiguity
  if (g == 0.12 || g == 0.13 || g == 0.14 || g == 0.15 || g == 0.17) {
    // overestimate
    st[0]++;

    if (g_third == 0)
      return false;
    else if (g_third == 1)
      st[0]--; // was the low one
    else if (g_third != 2)
      yyerror("invalid 3rd grav digit");
  }

  return true;
}



bool planet::set_ori_stats(const double& g, const double& t, const double& r) 
{
  return set_planet_stats(ori_stats, g, t, r);
}


bool planet::set_stats(const double& g, const double& t, const double& r)
{
  return set_planet_stats(_stats[0], g, t, r);
}



bool planet::set_reported_stats(const int src, const double& g, const double& t, const double& r)
{
  return set_planet_stats(r_stats[src], g, t, r);
}



bool planet::set_reported_oristats(const int src,
	                           const double& g, const double& t, const double& r)
{
  return set_planet_stats(r_oristats[src], g, t, r);
}



void planet::set_power(void)
{
  if (trusted_source == -1) // no info at all on world
    return;

  power = 200 + 200 * _pop[0] / 1000000;
  if (stb_type != 0)
    if (stb_type < 3) {
      power = power * 3 / 2;
      power += 100;
    } else {
      power = power * 2;
      power += 200;
    }
}

/*
void planet::set_power(void)
{
  double dbp = (double)pxop[trusted_source] / 1000000.0;

  if (dbp > 1.0)
    dbp = 1.0;

  power = (int)(400.0 * (1.0 - pow(1.0-dbp, 5)));

  if (starbase[trusted_source] != 0)
    if (starbase[trusted_source] < 3) {
      power = power * 3 / 2;
      power += 100;
    } else {
      power = power * 2;
      power += 200;
    }
}
*/


const double deftable[] = {0.0099, 0.0199, 0.0239, 0.0299, 0.0379};

 
int planet::compute_percent_from_def(const int d)
{
  return (int)(10000 * (1.0 - pow(1-deftable[_owner->defense_level(0)], d)));
}
 
 
int planet::compute_def_from_percent(const int dp)
{
  return (int)(log(1 - dp / 10000.0)/log(1 - deftable[_owner->defense_level(0)]));
}


// hab formula from Loren Webster

int planet::habitability(const int* st, const race* owner) const
{
  int h;
  double f1 = 0.0;
  double f2 = 1.0;
  double nd, nd1;
  int hwidth, hwidth2;
  int i, deviat[3];

  if (!owner)
    owner = _owner;

  for (i = 0; i < 3; i++)
    if (owner->hab_min[i] == -1)
      deviat[i] = 0;
    else if (st[i] < owner->hab_min[i])
      deviat[i] = st[i] - owner->hab_min[i];
    else if (st[i] > owner->hab_max[i])
      deviat[i] = owner->hab_max[i] - st[i];
    else
      deviat[i] = abs(st[i] - (owner->hab_max[i] + owner->hab_min[i]) / 2);

  h = 0;

  for (i = 0; i < 3; i++)
    if (deviat[i] < 0)
      h += (deviat[i] < -15)? -15 : deviat[i];
  
  if (h < 0) // red
    return h * 100;

  for (i = 0; i < 3; i++) {
    if (owner->hab_min[i] == -1) {
      nd = 0.0;
      nd1 = 0.0;
    } else {
      hwidth = abs((owner->hab_max[i] - owner->hab_min[i]) / 2);
      hwidth2 = hwidth / 2;

      nd = (double)deviat[i] / (double)hwidth;
      nd1 = (nd > 0.5)? (nd - 0.5) : 0.0;
    }

    f1 += (1.0 - nd) * (1.0 - nd);
    f2 *= (1.0 - nd1);
  }

  h = (int)(sqrt(f1)/SQR3 * f2 * 10000.0);

  return h;
}



void planet::calc_habitability(void)
{
  if (_stats[curr_year][Grav] == -10) { // no planetary info
      // if no planetary stats are available then just copy year 0 data
      _habitab[curr_year+1] = _habitab[0];

  } else {
    _habitab[curr_year] = habitability(_stats[curr_year]);

    _habitab[curr_year] /= 100;

    _habitab[curr_year+1] = _habitab[curr_year];
  }
}


void planet::instaform(void)
{
  int d, i;

  // instaform planet according to owner's tech
  if (!_owner || !_owner->can_analyze || ori_stats[Grav] == -10)
    return;

  for (i = 0; i < 3; i++) {
    _stats[0][i] = ori_stats[i];

    d = _stats[0][i] - (_owner->hab_min[i] + _owner->hab_max[i]) / 2;
    if (abs(d) > _owner->tform_tech[0][i])
      d = sign(d) * _owner->tform_tech[0][i];

    _stats[0][i] -= d;
  }
}


void planet::terraform(race* owner)
{
  int hab_best = -10000;
  int new_hab;
  int which, i, dir;
  int try_stat[3];

  if (!owner)
    owner = _owner;

  if (_stats[curr_year][Grav] == -10)
    return; // no tform info available

  try_stat[Grav] = _stats[curr_year+1][Grav];
  try_stat[Temp] = _stats[curr_year+1][Temp];
  try_stat[Rad] = _stats[curr_year+1][Rad];

  // try terraforming (if possible)
  for (i = 0; i < 3; i++)
    if (owner->hab_min[i] != -1)
      if (abs(ori_stats[i] - _stats[curr_year+1][i]) < owner->tform_tech[curr_year][i]) {
	dir = - sign(_stats[curr_year+1][i] - (owner->hab_max[i] + owner->hab_min[i]) / 2);

	try_stat[i] += dir;
	new_hab = habitability(try_stat);
	try_stat[i] = _stats[curr_year+1][i];

	if (new_hab > hab_best) {
	  hab_best = new_hab;
	  which = i;
	}
      }

  if (hab_best == -10000) {
    add_message(RLO_ERROR, "Attempted terraform beyond limits?!?");
    return;
  }

  dir = - sign(_stats[curr_year+1][which] - (owner->hab_max[which] + owner->hab_min[which]) / 2);
  _stats[curr_year+1][which] = _stats[curr_year][which] + dir;
}



void planet::unterraform(race* owner)
{
  exit(-1);
}



void planet::grow_pop(void)
{
  if (_pop[curr_year] < 100) {
    _pop[curr_year + 1] = 0;
    return;
  }

  double grow = (double)_owner->col_grow / 100.0;
  double hab = (double)_habitab[curr_year] / 100.0;
  double mp = maxpop(curr_year);
  double popnow = _pop[curr_year];
  double gpop, ff;

  if (hab < 0.0)
    gpop = popnow * hab / 10.0;

  else if (popnow < mp) {
    if (popnow <= (mp / 4.0))
      gpop = popnow * grow * hab;
    else {
      ff = (1.0 - popnow / mp) / 0.75;

      gpop = popnow * grow * hab * ff * ff;
    }
  } else
    gpop = (mp - popnow) / 10;

  _pop[curr_year+1] = _pop[curr_year] + (int)gpop / 10 * 10;
}



// mineral depletion formula from Jason Cawley

void planet::do_mining(_mintype* mined)
{
  if (!evolving())
    return;

  int i, my;

  mine_year[curr_year+1] = mine_year[curr_year];
  _min_conc[curr_year+1] = _min_conc[curr_year];

  for (i = 0; i < 3; i++) {
    my = min(mines(), pop() * _owner->mine_ctrl / 10000);

    (*mined)[i] = (_min_conc[curr_year][i] * _owner->mine_eff * my + 50) / 1000;

    my = (*mined)[i];
    // use Jason's formula (which gives minerals/conc step)
    while (my) {
      if (my > mine_year[curr_year+1][i]) {
	my -= mine_year[curr_year+1][i];
	_min_conc[curr_year+1][i]--;

	if (_min_conc[curr_year+1][i] == 0)
	  _min_conc[curr_year+1][i] = 1;

	if (_min_conc[curr_year+1][i] >= 30)
	  mine_year[curr_year+1][i] = 12500 / _min_conc[curr_year+1][i];
	else if (_min_conc[curr_year+1][i] >= 3)
	  mine_year[curr_year+1][i] = 456;
	else
	  mine_year[curr_year+1][i] = 456 * 2;
      } else {
	mine_year[curr_year+1][i] -= my;
	my = 0;
      }
    }

    if (homeworld && _min_conc[curr_year+1][i] < 30)
      _min_conc[curr_year+1][i] = 30;
  }
}



void planet::clear_queue(void)
{
  queue_obj* qo;
  queue_obj* qon;

  for (qo = queue; qo; qo = qon) {
    qon = qo->next;

    delete qo;
  }
}



void planet::add_to_queue(queue_obj* nqo)
{
  if (!_owner)
    return;

  if (!queue)
    queue = nqo;
  else {
    queue_obj* qo;

    for (qo = queue; qo->next; qo = qo->next);

    qo->next = nqo;
  }
}



bool planet::add_to_queue(const bool a, const myString& n, const int c,
			  const int act, const int deact)
{
  object* o;

  if (c <= 0)
    return false;

  if (!_owner) // no explicit owner, check auth source (this is needed for load-time queues)
    if (auth_source == -1)
      return false;
    else 
      o = game_map->find_race(auth_source)->find_object(n);
  else
    o = _owner->find_object(n);

  if (!o)
    return false;

  // create queue_obj
  queue_obj* nqo = new queue_obj(a, c, o, act, deact);

  if (!queue)
    queue = nqo;
  else {
    queue_obj* qo;

    for (qo = queue; qo->next; qo = qo->next);

    qo->next = nqo;
  }

  return true;
}



bool planet::insert_in_queue(int pos, const bool a, const myString& n, const int c,
			     const int act, const int deact)
{
  if (!_owner || c <= 0)
    return false;

  object* o = _owner->find_object(n);

  if (!o)
    return false;

  // create queue_obj
  queue_obj* nqo = new queue_obj(a, c, o, act, deact);

  // insert in required position
  queue_obj* qo;
  queue_obj* pqo;

  for (pqo = NULL, qo = queue; qo && pos > 0; pqo = qo, qo = qo->next, pos--);

  if (!pqo) { // list head
    nqo->next = queue;
    queue = nqo;
  } else {
    pqo->next = nqo;
    nqo->next = qo;
  }

  return true;
}




void planet::build_queue(void)
{
  queue_obj* co;
  queue_obj* pco;
  queue_obj* aco;
  int original_count;
  char tmsg[512];
  int required_res, n_objects;
  _mintype required_min;
  _mintype shortage;

  // update queue
  for (pco = NULL, co = queue; co; ) {
    // add new objects
    if (!co->active && co->add_to_queue == curr_year)
      co->active = true;
    // remove old objects
    else if (co->active)
      if (co->rem_from_queue == curr_year) {
	// plainly kill it
	if (pco) {
	  pco->next = co->next;
	  delete co;
	  co = pco;
	} else {
	  delete co;
	  co = NULL;
	}
      } else // unset autobuild bit
	if (co->autob == queue_obj::AutoDone)
	  co->autob = queue_obj::Autobuild;

    pco = co;
    if (co)
      co = co->next;
    else
      co = queue;
  }

  dump_queue();

  // scan queue and build objects
  for (pco = NULL, co = queue; co && avail_res;) {
    if (co->active && co->autob != queue_obj::AutoDone) {
      if (co->autob == queue_obj::Autobuild) {
	// convert from auto to "real" stuff
	if ( (aco = create_nonauto(co)) ) {
	  // note that object is placed at HEAD of list
	  aco->next = queue;
	  queue = aco;
	  co = NULL;
	}
      } else {
	// paranoia check for fact/mine/tform
	// object must not be created if max are reached
	if (co->proto->_name == "factory")
	  if (factories() + co->count > maxfactories()) {
	    add_message(RLO_ERROR, "Excess factories trimmed");
	    co->count = maxfactories() - factories();
	  }

	if (co->proto->_name == "mine")
	  if (mines() + co->count > maxmines()) {
	    add_message(RLO_ERROR, "Excess mines trimmed");
	    co->count = maxmines() - mines();
	  }

	if (co->proto->_name == "defense")
	  if (defenses() + co->count > maxdefenses()) {
	    add_message(RLO_ERROR, "Excess defenses trimmed");
	    co->count = maxdefenses() - defenses();
	  }

	if (co->proto->_name == "terraform") {
	  int tl = tform_left();

	  if (co->count > tl) {
	    add_message(RLO_ERROR, "Excess terraform trimmed");
	    co->count = tl;
	  }
	}

	original_count = co->count;

	required_res = co->res; // current (partial) object
	required_res += co->proto->res * (co->count - 1); // rest
	required_min = co->min;
	required_min += co->proto->min * (co->count - 1);

	// if we have enough stuff then just build
	if (required_res <= avail_res && _mineral[curr_year+1].enough(required_min)) {
	  // create the objects
	  avail_res -= required_res;
	  _mineral[curr_year+1] -= required_min;
	  create_object(co->proto, co->count);

	  sprintf(tmsg, "production: %d %s", original_count, (const char*)co->proto->_name);
	  add_message(RLO_PLABUILD, tmsg);

	  // ran out of objects, delete and move to next
	  if (pco) {
	    pco->next = co->next;
	    delete co;
	    co = pco;
	  } else {
	    queue = co->next;
	    delete co;
	    co = NULL;
	  }

	} else { // we have a problem
	  // we may have run out of resources, minerals or both

	  // save the mineral shortage value (if any)
	  if (!_mineral[curr_year+1].enough(required_min))
	    shortage = required_min - _mineral[curr_year+1];
	  
	  // 1st object may be partial
	  if (co->res <= avail_res && _mineral[curr_year+1].enough(co->min)) {
	    // build first object
	    co->count--;
	    avail_res -= co->res;
	    _mineral[curr_year+1] -= co->min;
	    create_object(co->proto);
	    co->res = co->proto->res; // restore original costs
	    co->min = co->proto->min;

	    // keep going until last object
	    if (co->count) {
	      n_objects = avail_res / co->proto->res;
	      // note: we know that n_objects < co->count!
	      avail_res -= n_objects * co->proto->res;
	      _mineral[curr_year+1] -= co->proto->min * n_objects;
	      create_object(co->proto, n_objects);
	      co->count -= n_objects;
	    }
	  }

	  // partially build last object (we know co->count != 0)
	  if (avail_res) {
	    // (use resources as step)
	    int ar;
	    _mintype mu;

	    for (ar = 1; ar <= avail_res; ar++) {
	      mu = co->min * ar / co->res;

	      if (!_mineral[curr_year+1].enough(mu)) {
		ar--;
		mu = co->min * ar / co->res;
		ar++;
		break;
	      }
	    }

	    ar--;
	    avail_res -= ar;
	    co->res -= ar;
	    co->min -= mu;

	    _mineral[curr_year+1] -= mu;

	    sprintf(tmsg, "production: %d %s (and next at %d%%)", original_count - co->count,
		    (const char*)co->proto->_name, 
		    100 * (co->proto->res - co->res) / co->proto->res);
	    add_message(RLO_PLABUILD, tmsg);

	    // now we either have no resources (stop)
	    // or no minerals (again stop, since auto-build doesn't queue
	    //                 stuff which can't be completed by mins)
	    if (avail_res) {
	      sprintf(tmsg, "Mineral shortage %d/%d/%d limits %s production to %d/%d",
		      shortage.iron, shortage.bora, shortage.germ, (const char*)co->proto->_name,
		      original_count - co->count, original_count);

	      add_message(RLO_PLAMINSTAT, tmsg);

	      _minshortage[curr_year] += shortage;
	    }

	    break; // leave for co loop
	  }
	}
      }
    }

    pco = co;
    if (co)
      co = co->next;
    else
      co = queue;
  }
}


// convert auto-orders to real orders, taking care not to exceed
// fact/mine/tform limits and mineral limits
queue_obj* planet::create_nonauto(queue_obj* qo)
{
  queue_obj* nqo = NULL;
  int n = qo->count;
  _mintype shortage;
  int n_possible;
  char tmsg[512];

  // compute "theoretically possible" objects based on resource output
  n_possible = avail_res / qo->proto->res;

  // object-specific limits, note that they act on 'n', objects to
  // create, and NOT just on n_possible
  if (qo->proto->_name == "mine") {
    if ((mines() + n) > maxcmines(curr_year+1))
      n = maxcmines(curr_year+1) - mines();
    if ((mines() + n_possible) > maxcmines(curr_year+1))
      n_possible = maxcmines(curr_year+1) - mines();

  } else if (qo->proto->_name == "factory") {
    if ((factories() + n) > maxcfactories(curr_year+1))
      n = maxcfactories(curr_year+1) - factories();
    if ((factories() + n_possible) > maxcfactories(curr_year+1))
      n_possible = maxcfactories(curr_year+1) - factories();

  } else if (qo->proto->_name == "defense") {
    if ((defenses() + n_possible) > maxcdefenses(curr_year+1))
      n = n_possible = maxcdefenses(curr_year+1) - defenses();

  } else if (qo->proto->_name == "terraform") {
    int tl = tform_left();

    if (n_possible > tl)
      n_possible = n = tl;
  }

  // see if minerals allow the construction of n_possible objects
  if (!_mineral[curr_year+1].enough(qo->proto->min * n_possible)) {
    int was_possible = n_possible;
    n_possible = _mineral[curr_year+1] / qo->proto->min;

    shortage = qo->proto->min * (was_possible - n_possible);
    _minshortage[curr_year] += shortage;

    sprintf(tmsg, "Mineral shortage %d/%d/%d limits autobuild %s to %d/%d",
	    shortage.iron, shortage.bora, shortage.germ, (const char*)qo->proto->_name,
	    n_possible, was_possible);
    add_message(RLO_PLAMINSTAT, tmsg);

  } else {
    // if enough minerals are available for one more object BUT
    // only partial resources are available then we add it to the
    // queue, in order to "halt" on its partial creation
    if (_mineral[curr_year+1].enough(qo->proto->min * (n_possible+1))
	&& avail_res > (qo->proto->res * n_possible) )
      n_possible++;
  }

  // specific object might be hard-limited to n value (mines, factories, etc.)
  if (n_possible < n)
    n = n_possible;

  qo->autob = queue_obj::AutoDone;
  if (n > 0) {
    nqo = new queue_obj(false, n, qo->proto);
    nqo->active = true;

    sprintf(tmsg, "Autobuild %d %s --> %d placed into queue",
	    qo->count, (const char*)qo->proto->_name, n);
    add_message(RLO_PLAABUILD, tmsg);
  }

  return nqo;
}


int planet::max_can_build(const myString& on, int when) const
{
  if (!_owner)
    return 0;

  object* o;

  when = fix_year(when);

  for (o = _owner->object_table; o; o = o->next)
    if (o->_name == on)
      break;

  if (!o)
    return 0;

  int n = res[when] / o->res;

  _mintype willbemin;
  _mintype mined;

  mined = mining_rate(when);
  willbemin = _mineral[when] + mined;

  if (!willbemin.enough(o->min * n))
    n = willbemin / o->min;

  // additional paranoia checks for mines/fact/tform
  if (on == "factory")
    n = min(maxfactories(when) - factories(when), n);
  else if (on == "defense")
    n = min(maxdefenses(when) - defenses(when), n);
  else if (on == "mine")
    n = min(maxmines(when) - mines(when), n);
  else if (on == "terraform")
    n = min(tform_left(_owner, when), n);

  return n;
}



void planet::create_object(const object* o, const int n = 1)
{
  if (o->_name == "factory")
    _factories[curr_year+1] += n;
  else if (o->_name == "mine")
    _mines[curr_year+1] += n;
  else if (o->_name == "defense")
    _defenses[curr_year+1] += n;
  else if (o->_name == "terraform")
    for (int i = 0; i < n; i++)
      terraform();
  else {
    // create the objects?!?
  }
}



void planet::init_turn(void)
{
  if (!evolving())
    return;

  // compute (or propagate) habitability - this is done to take into
  // account last year's terraforming
  calc_habitability();

  // update defense coverage (done here to take into account the tech
  // level of the year AFTER the construction has been done)
  def_coverage[curr_year] = compute_percent_from_def(_defenses[curr_year]);

  // compute resources available this year
  avail_res = resources();

  // report status
  report(Full);
}



void planet::do_turn(void)
{
  _mintype mined;
  char tmsg[512];

  if (!evolving())
    return;

  grow_pop();

  do_mining(&mined);
  _mineral[curr_year+1] = (_mineral[curr_year]).operator+(mined);
  _stats[curr_year+1][Grav] = _stats[curr_year][Grav];
  _stats[curr_year+1][Temp] = _stats[curr_year][Temp];
  _stats[curr_year+1][Rad] = _stats[curr_year][Rad];
  _factories[curr_year+1] = _factories[curr_year];
  _mines[curr_year+1] = _mines[curr_year];
  _defenses[curr_year+1] = _defenses[curr_year];

  build_queue();

  // leftover resources
  if (avail_res != 0) {
    sprintf(tmsg, "planet contributes %d to research", avail_res);
    add_message(RLO_PLABUILD, myString(tmsg));
  }
  _research[curr_year] = avail_res;

  // integrals
  _tot_resources[curr_year+1] = _tot_resources[curr_year] + resources();
  _tot_research[curr_year+1] = _tot_research[curr_year] + _research[curr_year];

  // check incoming fleets
  for (fleet* f = incoming; f; f = f->pnext)
    if (f->eta == curr_year+1) {// fleet arrives now!
      if (f->_owner == _owner) { 
	int ip = f->unload_pop();
	_mintype im = f->unload_min();

	// take into account IS growth by pumping the opop total
	if (_owner->prt() == IS) {
	  int isgwt = (int)(1000.0 * pow(1.0 + (double)_owner->col_grow/200.0, f->eta));
	  ip = ip * isgwt / 1000;
	}

	ip *= 100;

	if (ip || im.total()) {
	  sprintf(tmsg, "fleet %s unloads %d/%d/%d minerals and %d colonists",
		  (const char*)f->_name, im.iron, im.bora, im.germ, ip);
	  add_message(RLO_PLAFLEETS, myString(tmsg));

	  _pop[curr_year+1] += ip;
	  _mineral[curr_year+1] += im;
	}

      } else if (game_map->are_allies(f->_owner, _owner)) {
	  sprintf(tmsg, "allied fleet %s arrives at planet", (const char*)f->_name);
	  add_message(RLO_PLAFLEETS, myString(tmsg));

      } else {
	sprintf(tmsg, "ENEMY fleet %s arrives at planet!!!", (const char*)f->_name);
	add_message(RLO_PLAFLEETS, myString(tmsg));
      }

      if (game_map->are_allies(f->_owner, _owner) && stb_type >= SpaceDock) {
	f->refuel();
	sprintf(tmsg, "fleet %s is refuelled by station", (const char*)f->_name);
	add_message(RLO_PLAFLEETS, myString(tmsg));
      }
    }

  // check die-off
  if (_pop[curr_year+1] == 0) {
    clear_queue();
  }
}



void planet::advance_year(void)
{
  // advance to next year
  curr_year++;
}



// used to copy all data into future for non-evolving planets
void planet::spread_year0_data(void)
{
  int y;

  for (y = 1; y <= game_map->sim_future(); y++) {
    _stats[y][0] = _stats[0][0];
    _stats[y][1] = _stats[0][1];
    _stats[y][2] = _stats[0][2];
    _min_conc[y] = _min_conc[0];
    _pop[y] = _pop[0];
    _factories[y] = _factories[0];
    _mines[y] = _mines[0];
    _defenses[y] = _defenses[0];
    def_coverage[y] = def_coverage[0];
    _mineral[y] = _mineral[0];
    _habitab[y] = _habitab[0];
    res[y] = res[0];
  }
}


void planet::add_fleet(fleet* f)
{
  f->pnext = incoming;
  incoming = f;
}

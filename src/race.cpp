#include "starana-classes.h"



/*
Level	    Normal Cost	
-----	------------------
 1	     50 + 10/level
 2	     80 + 10/level
 3	    130 + 10/level	T1  + T2
 4	    210 + 10/level	T2  + T3
 5	    340 + 10/level	T3  + T4
 6	    550 + 10/level	T4  + T5
 7	    890 + 10/level	T5  + T6
 8	   1440 + 10/level	T6  + T7
 9	   2330 + 10/level	T7  + T8
10	   3770 + 10/level	T8  + T9
11	   6100 + 10/level	T9  + T10
12	   9870 + 10/level	T10 + T11
13	  13850 + 10/level	T12 + 3980 (T10 + 210)
14	  18040 + 10/level	T13 + 4190 (T10 + 210*2)
15	  22440 + 10/level	T14 + 4400 (T10 + 210*3)
16	  27050 + 10/level	T15 + 4610 (T10 + 210*4)
17	  31870 + 10/level	T16 + 4820 (T10 + 210*5)
18	  36900 + 10/level	T17 + 5030 (T10 + 210*6)
19	  42140 + 10/level	T18 + 5240 (T10 + 210*7)
20	  47590 + 10/level	T19 + 5450 (T10 + 210*8)
21	  53250 + 10/level	T20 + 5660 (T10 + 210*9)
22	  59120 + 10/level	T21 + 5870 (T10 + 210*10)
23	  65200 + 10/level	T22 + 6080 (T10 + 210*11)
24	  71490 + 10/level	T23 + 6290 (T10 + 210*12)
25	  77990 + 10/level	T24 + 6500 (T10 + 210*13)
26	  84700 + 10/level	T25 + 6710 (T10 + 210*14)
*/
int race::fibonacci[26] = { 50, 80, 130, 210, 340,
			    550, 890, 1440, 2330, 3770,
			    6100, 9870, 15970, 25840, 41810,
			    67650, 109460, 177110, 286570, 463680,
			    750250, 1213930, 1964180, 3178110, 5142290,
			    8320400 };

myString race::prt_names[10] = {"HE", "SS", "WM", "CA", "IS",
			      "SD", "PP", "IT", "AR", "JoaT"};

myString race::lrt_names[14] = {"IFE", "TT", "ARM", "ISB", "GR", "UR", "MA",
			      "NRSE", "CE", "OBRM", "NAS", "LSP", "BET", "RS"};


race::race(const myString& n, const int i) :   
            _name(n), _names(n+"s"), id(i), reliab(1),
	    can_analyze(false), has_report(false), 
	    col_res(1000), col_grow(15),
	    fact_res(10), fact_cost(10), fact_ctrl(10), fact_germ(4),
	    mine_eff(10), mine_cost(5), mine_ctrl(10),
	    _prt(SD), min_pop_move(100), maxpop(1000000),
	    default_queue(NULL), object_table(NULL), last_object(NULL),
	    fleet_table(NULL), last_fleet(NULL), planet_table(NULL), 
	    number_fleets(0), explored_planets(0), owned_planets(0),
	    curr_year(0)
{
  hab_min[Grav] = hab_min[Temp] = hab_min[Rad] = -100;
  hab_max[Grav] = hab_max[Temp] = hab_max[Rad] = -100;

  strcpy(techcost, "000000");

  for (int j = 0; j < 16; j++)
    lrt_tab[j] = false;

  for (int k = 0; k < SIM_FUTURE; k++) {
    for (int j = 0; j < 6; j++) {
      tech[k][j] = -1;
      tech_tonext[k][j] = -1;
    }

    tech_research[k] = -1;
    tform_tech[k][Grav] = tform_tech[k][Temp] = tform_tech[k][Rad] = -1;

    total_pop[k] = 0;
    total_opop[k] = 0;
    total_hab[k] = 0;
    total_growth[k] = 0;
    total_gpctg[k] = 0;
    total_geff[k] = 0;
    total_min[k][0] = total_min[k][1] = total_min[k][2] = 0;
    total_mg[k][0] = total_mg[k][1] = total_mg[k][2] = 0;
    total_fact[k] = 0;
    total_mine[k] = 0;  
    total_maxfact[k] = 0;
    total_maxmine[k] = 0;  
    total_unufact[k] = 0;
    total_unumine[k] = 0;
    total_res[k] = 0;
    total_rsrch[k] = 0;
  }

  for (int k = 0; k < 6; k++)
    total_fleets[k] = 0;
  // %%%%%%%%%%%% missing stuff
}


myString race::lrt_name(void) const
{
  myString s;
  int i;

  for (i = 0; i < 14; i++)
    if (lrt((lrt_type)i)) {
      if (s.length())
	s += ' ';
      s += lrt_names[i];
    }

  return s;
}


myString race::factory_stats(void) const
{
  return int_to_str(fact_res) + "/" +
    int_to_str(fact_cost) + "/" +
    int_to_str(fact_ctrl) + " (" +
    int_to_str(fact_germ) + " germ)";
}


myString race::mine_stats(void) const
{
  return int_to_str(mine_eff) + "/" +
    int_to_str(mine_cost) + "/" +
    int_to_str(mine_ctrl);
}


object* race::find_object(const myString& n) const
{
  object* o;
  for (o = object_table; o; o = o->next)
    if (o->_name == n)
      return o;

  return NULL;
}


design* race::find_design(const myString& n, const bool starbase = false) const
{
  object* o;

  for (o = object_table; o; o = o->next)
    if ( o->des &&
	 ((starbase && !o->des->h->n_engines) ||
	  (!starbase && o->des->h->n_engines)) &&
	 o->des->alias == n )
      return o->des;

  // not found as alias: try as full name
  for (o = object_table; o; o = o->next)
    if ( o->des &&
	 ((starbase && !o->des->h->n_engines) ||
	  (!starbase && o->des->h->n_engines)) &&
	 o->_name == n )
      return o->des;

  return NULL;
}


// find a design whose alias starts with n
// NULL if not found OR if ambiguous

design* race::find_design_alias(const myString& n, const bool starbase = false) const
{
  object* o;
  design* d = NULL;

  for (o = object_table; o; o = o->next)
    if ( o->des &&
	 ((starbase && !o->des->h->n_engines) ||
	  (!starbase && o->des->h->n_engines)) &&
	 o->des->alias.matches(n, 0) )
      if (d)
	return NULL;
      else
	d = o->des;

  return d;
}


object* race::next_object(const object* o) const
{
  if (o == NULL)
    return object_table;
  else
    return o->next;
}



void race::set_minimal_objects(void)
{
  object *o;

  if ( !(o = find_object(myString("factory"))) ) {
    add_object(myString("factory"), fact_cost, 0, 0, fact_germ);
    add_object(myString("mine"), mine_cost, 0, 0, 0);
    add_object(myString("terraform"), lrt(TT)? 70 : 100, 0, 0, 0);

    if (prt() == IS)
      add_object(myString("defense"), 9, 3, 3, 3);
    else
      add_object(myString("defense"), 15, 5, 5, 5);
  }
}



void race::add_fleet(fleet* f)
{
  f->rnext = NULL;

  if (!fleet_table)
    fleet_table = last_fleet = f;
  else {
    last_fleet->rnext = f;
    last_fleet = f;
  }
}



void race::replace_fleet(fleet* pof, fleet* of, fleet* nf)
{
  nf->rnext = of->rnext;

  if (pof)
    pof->rnext = nf;
  else
    fleet_table = nf;

  if (of == last_fleet)
    last_fleet = nf;

  delete of;
}



bool race::add_to_default_queue(const bool a, const myString& n, const int c,
				const int act, const int deact)
{
  if (c <= 0)
    return false;

  object* o = find_object(n);

  if (!o)
    return false;

  queue_obj* nqo = new queue_obj(a, c, o, act, deact);

  if (!default_queue)
    default_queue = nqo;
  else {
    queue_obj* qo;

    for (qo = default_queue; qo->next; qo = qo->next);

    qo->next = nqo;
  }

  return true;
}



int race::defense_level(int when) const
{
  int el = tech[when][Elec];
  int dl = 0;

  if (el >= 23) {
    dl = 4;
  } else if (el >= 16) {
    dl = 3;
  } else if (el >= 10) {
    dl = 2;
  } else if (el >= 5) {
    dl = 1;
  }

  if (prt() == WM)
    dl = min(1, dl);

  return dl;
}



int race::pla_penscan_radius(int when) const
{
  if (lrt(NAS))
    return 0;

  int r = 0;

  if (tech[when][Ener] >= 3 && 
      tech[when][Ener] >= 10 && 
      tech[when][Bio] >= 3)
    r = 160;

  if (tech[when][Ener] >= 4 && 
      tech[when][Ener] >= 13 && 
      tech[when][Bio] >= 6)
    r = 200;

  if (tech[when][Ener] >= 5 && 
      tech[when][Ener] >= 16 && 
      tech[when][Bio] >= 7)
    r = 250;

  if (tech[when][Ener] >= 7 && 
      tech[when][Ener] >= 23 && 
      tech[when][Bio] >= 9)
    r = 310;

  return r;
}



int race::pla_scan_radius(int when) const
{
  int el = tech[when][Elec];
  int r = 50;

  if (el >= 1)
    r = 90;
  if (el >= 3)
    r = 150;
  if (el >= 6)
    r = 220;
  if (el >= 8)
    r = 260;
  
  if (lrt(NAS))
    return r * 2;

  if (tech[when][Ener] >= 3 && 
      el >= 10 && 
      tech[when][Bio] >= 3)
    r = 320;

  if (tech[when][Ener] >= 4 && 
      el >= 13 && 
      tech[when][Bio] >= 6)
    r = 400;

  if (tech[when][Ener] >= 5 && 
      el >= 16 && 
      tech[when][Bio] >= 7)
    r = 500;

  if (tech[when][Ener] >= 7 && 
      el >= 23 && 
      tech[when][Bio] >= 9)
    r = 620;

  return r;
}



object* race::create_object(const myString& n)
{
  object* o = new object(n);
  o->next = NULL;

  if (!object_table)
    object_table = last_object = o;
  else {
    last_object->next = o;
    last_object = o;
  }

  return o;
}



design* race::create_design(const myString& n)
{
  object* o = create_object(n);
  o->des = new design(o);
  return o->des;
}



object* race::add_object(const myString& n, const int r, const int i, const int b, const int g)
{
  object* o = new object(n, r, i, b, g);

  o->next = object_table;
  object_table = o;

  return o;
}



int race::get_normal_tform(const int bio, const int ewp)
{
  int t = 0;

  if (bio >= 1 && ewp >= 1)
    t = 3;
  if (bio >= 2 && ewp >= 5)
    t = 7;
  if (bio >= 3 && ewp >= 10)
    t = 11;
  if (bio >= 4 && ewp >= 16)
    t = 15;

  return t;
}



void race::set_terraform_tech(int when)
{
  // do we have tech info?
  if (tech[0][0] == -1) {
    tform_tech[when][Grav] = 0;
    tform_tech[when][Temp] = 0;
    tform_tech[when][Rad] = 0;

    return;
  }

  // normal terraforming
  tform_tech[when][Grav] = get_normal_tform(tech[when][Bio], tech[when][Prop]);
  tform_tech[when][Temp] = get_normal_tform(tech[when][Bio], tech[when][Ener]);
  tform_tech[when][Rad] = get_normal_tform(tech[when][Bio], tech[when][Weap]);

  // total terraforming
  if (lrt(TT)) {
    int tt;

    if (tech[when][Bio] >= 25)
      tt = 30;
    else if (tech[when][Bio] >= 22)
      tt = 25;
    else if (tech[when][Bio] >= 17)
      tt = 20;
    else if (tech[when][Bio] >= 13)
      tt = 15;
    else if (tech[when][Bio] >= 9)
      tt = 10;
    else if (tech[when][Bio] >= 6)
      tt = 7;
    else if (tech[when][Bio] >= 3)
      tt = 5;
    else
      tt = 3;

    tform_tech[when][Grav] = max(tt, tform_tech[when][Grav]);
    tform_tech[when][Temp] = max(tt, tform_tech[when][Temp]);
    tform_tech[when][Rad] = max(tt, tform_tech[when][Rad]);
  }
}



void race::advance_year(void)
{
  // we have the _research stuff to use for research.....
  // do nothing for the moment
  tech[curr_year+1][Ener] = tech[curr_year][Ener];
  tech[curr_year+1][Weap] = tech[curr_year][Weap];
  tech[curr_year+1][Prop] = tech[curr_year][Prop];
  tech[curr_year+1][Con] = tech[curr_year][Con];
  tech[curr_year+1][Elec] = tech[curr_year][Elec];
  tech[curr_year+1][Bio] = tech[curr_year][Bio];

  curr_year++;

  set_terraform_tech(curr_year);
}



void race::check_data(void)
{
  set_terraform_tech();

  if (can_analyze) {
    add_message(RLO_ERROR, "The " + _name + " race is flagged for analysis");

    // make sure that factory/mine/stuff are available for planet queues
    set_minimal_objects();
  }

  if (_prt == HE)
    col_grow *= 2;

  maxpop = (_prt == JoaT)? 1200000 : 1000000;

  if (lrt(OBRM))
    maxpop = maxpop * 11 / 10;

  if (_prt == HE)
    maxpop /= 2;

  // some check should be done, probably

  // compute max res,fact,mine/planet
  maxfact = maxpop * fact_ctrl / 10000;
  maxmine = maxpop * mine_ctrl / 10000;
  maxres = maxpop / col_res + maxfact * fact_res / 10;
}



void race::add_message(const int mt, const myString& m)
{
  logmsgs.add(mt, m);
}



const message* race::next_message(const message* m) const
{
  const message* nm;

  if (m)
    nm = m->next;
  else
    nm = logmsgs.first();

  while (nm && nm->filtered())
    nm = nm->next;

  return nm;
}

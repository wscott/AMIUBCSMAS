#include "starana-classes.h"



// null function, do nothing at all

class pla_nullfunction : public planetary_function {
public:
  pla_nullfunction(void)
  {
    _name = "- (nothing) -";
    _type = "General";
    _desc = "This function does nothing at all.";
  }

  virtual void function(map_view& mw, planet* p, const int* par, const int when)
  {
    return;
  }
};

pla_nullfunction pla_nullfunction_proto;


// associate a marker to a planet

class pla_setmarker : public planetary_function {
public:
  pla_setmarker(void)
  {
    _name = "Set Marker";
    _type = "General";
    _desc = "This function associates a marker to a planet:\n1=dot, 2=cross, 3=box, 4=square, 5=circle, 6=flag.";
    _pardesc[0] = "Marker type";
  }
  
  virtual void function(map_view& mw, planet* p, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = p->disp;

    if (par[0] >= 0 && par[0] <= MAX_MARKER) {
      d.marker_type = (_marktype)par[0];
      d.marker_color = COL_WHITE;
    }

    d.flag = true;
  }
};

pla_setmarker pla_setmarker_proto;



// associate fixed data to a planet

class pla_setdata : public planetary_function {
public:
  pla_setdata(void)
  {
    _name = "Set Data";
    _type = "General";
    _desc = "This function associates single value data to a planet.\nData is assumed to be in the range [0,100].";
    _pardesc[0] = "Data value";
  }
  
  virtual void function(map_view& mw, planet* p, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = p->disp;

    // range
    d.vmin = 0;
    d.vmax = 100;
    d.values[0].value = par[0];
    d.values[0].color = COL_GREY;

    d.n_values = 1;
    d.flag = true;
  }
};

pla_setdata pla_setdata_proto;



// the default planet name functions

class pla_all_names : public planetary_function {
public:
  pla_all_names(void)
  {
    _name = "Set Planet Name";
    _type = "Names";
    _desc = "This function associates a name to a planet, '??' if unexplored,\ngrey if uninhabited white if inhabited.";
  }
  
  virtual void function(map_view& mw, planet* p, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = p->disp;

    // is planet unexplored?
    if (!p->data_available()) {
      d.name = "??";
      d.name_color = COL_GREY + 1;

    } else if (!p->owner()) {
      d.name = p->name();
      d.name_color = COL_GREY;

    } else {
      d.name = p->name();
      d.name_color = COL_WHITE;
    }

    d.flag = true;
  }
};

pla_all_names pla_all_names_proto;



class pla_all_starids : public planetary_function {
public:
  pla_all_starids(void)
  {
    _name = "Set Planet Name+Id";
    _type = "Names";
    _desc = "This function associates to a planet a name consisting of the actual\nplanet name followed by the Stars! id#.";
  }
  
  virtual void function(map_view& mw, planet* p, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = p->disp;

    d.name = p->name() + "(" + int_to_str(p->starsid()) + ")";

    if (!p->data_available())
      d.name_color = COL_GREY + 1;
    else if (!p->owner())
      d.name_color = COL_GREY;
    else
      d.name_color = COL_WHITE;

    d.flag = true;
  }
};

pla_all_starids pla_all_starids_proto;



class pla_all_starsids : public planetary_function {
public:
  pla_all_starsids(void)
  {
    _name = "Set Planet Id";
    _type = "Names";
    _desc = "This function associates to a planet a name consisting of its Stars! id#.";
  }
  
  virtual void function(map_view& mw, planet* p, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = p->disp;

    d.name = "(" + int_to_str(p->starsid()) + ")";

    if (!p->data_available())
      d.name_color = COL_GREY + 1;
    else if (!p->owner())
      d.name_color = COL_GREY;
    else
      d.name_color = COL_WHITE;

    d.flag = true;
  }
};

pla_all_starsids pla_all_starsids_proto;



// set name color

class pla_owncolor_names : public planetary_function {
public:
  pla_owncolor_names(void)
  {
    _name = "Color: name";
    _type = "Names";
    _desc = "This function sets the color of the name of the planet.";
    _pardesc[0] = "Color (0=owner's)";
  }
  
  virtual void function(map_view& mw, planet* p, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = p->disp;

    // do we have name?
    if (d.name_color) {
      if (par[0] > 0 && par[0] <= 16)
	d.name_color = COL_RACES + 4 * (par[0] - 1);
      else if (p->data_available() && p->owner())
	d.name_color = COL_RACES + 4 * p->owner()->race_id();
    }
  }
};

pla_owncolor_names pla_owncolor_names_proto;



// set marker color

class pla_owner : public planetary_function {
public:
  pla_owner(void)
  {
    _name = "Color: marker";
    _type = "General";
    _desc = "This function sets the color of the marker of the planet.";
    _pardesc[0] = "Color (0=owner's)";
  }

  virtual void function(map_view& mw, planet* p, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = p->disp;

    // do we have a marker?
    if (d.marker_type != MT_NONE) {
      if (par[0] > 0 && par[0] <= 16)
	d.marker_color = COL_RACES + 4 * (par[0] - 1);
      else if (p->data_available() && p->owner())
	d.marker_color = COL_RACES + 4 * p->owner()->race_id();
    }
  }
};

pla_owner pla_owner_proto;



// turn single pieslice data (if any) to owner color

class pla_singlevalueowner : public planetary_function {
public:
  pla_singlevalueowner(void)
  {
    _name = "Color: data";
    _type = "General";
    _desc = "This function sets the color of the data associated to a planet\n(only if it's single-valued).";
    _pardesc[0] = "Color (0=owner's)";
  }

  virtual void function(map_view& mw, planet* p, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = p->disp;

    // make sure we have single data
    if (d.n_values == 1) {
      if (par[0] > 0 && par[0] <= 16)
	d.values[0].color = COL_RACES + 4 * (par[0] - 1);
      else if (p->data_available() && p->owner())
	d.values[0].color = COL_RACES + 4 * p->owner()->race_id();
    }
  }
};

pla_singlevalueowner pla_singlevalueowner_proto;



// random % chance of killing

class pla_F_randomkill : public planetary_function {
public:
  pla_F_randomkill(void)
  {
    _name = "Filter: random";
    _type = "General";
    _desc = "Randomly kills the data/marker/name for the planet. Use parameter 1\nto select which field to affect (111 = all, 000 = none,\n101 = data & name).";
    _pardesc[1] = "Fields affect mask";
    _pardesc[2] = "Kill %";
    _pardesc[3] = "Random seed";
    _pardesc[4] = "Negate filter";
  }
  
  virtual void function(map_view& mw, planet* p, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = p->disp;

    srand((unsigned int)p + par[3]);

    bool f = ((rand() % 100) < par[2]);

    if (par[4])
      f = !f;

    if (par[1]) {
      if (f)
	d.reset_something(par[1]);
    } else
      d.flag = f;
  }
};

pla_F_randomkill pla_F_randomkill_proto;



// unconditional kill

class pla_F_kill : public planetary_function {
public:
  pla_F_kill(void)
  {
    _name = "Filter: unconditional";
    _type = "General";
    _desc = "Filters out all planets.";
    _pardesc[1] = "Fields affect mask";
    _pardesc[4] = "Negate filter";
  }
  
  virtual void function(map_view& mw, planet* p, const int* par, const int when)
  {
    if (par[1])
      p->disp.reset_something(par[1]);
    else
      p->disp.flag = (par[4]? false : true);
  }
};

pla_F_kill pla_F_kill_proto;



// kill if unexplored

class pla_F_unexplored : public planetary_function {
public:
  pla_F_unexplored(void)
  {
    _name = "Filter: unexplored";
    _type = "General";
    _desc = "Filters unexplored planets.";
    _pardesc[1] = "Fields affect mask";
    _pardesc[4] = "Negate filter";
  }
  
  virtual void function(map_view& mw, planet* p, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = p->disp;

    bool f = !(p->data_available());

    if (par[4])
      f = !f;

    if (par[1]) {
      if (f)
	d.reset_something(par[1]);
    } else
      d.flag = f;
  }
};

pla_F_unexplored pla_F_unexplored_proto;



// kill if planet has a starbase

class pla_F_starbase : public planetary_function {
public:
  pla_F_starbase(void)
  {
    _name = "Filter: starbase";
    _type = "General";
    _desc = "Filters planets equipped with a starbase.";
    _pardesc[1] = "Fields affect mask";
    _pardesc[4] = "Negate filter";
  }
  
  virtual void function(map_view& mw, planet* p, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = p->disp;

    bool f = false;

    if (p->data_available() && p->owner() && p->starbase_name().length())
      f = true;

    if (par[4])
      f = !f;

    if (par[1]) {
      if (f)
	d.reset_something(par[1]);
    } else
      d.flag = f;
  }
};

pla_F_starbase pla_F_starbase_proto;



// kill if owned

class pla_F_ownerkill : public planetary_function {
public:
  pla_F_ownerkill(void)
  {
    _name = "Filter: owner";
    _type = "General";
    _desc = "Filters planets depending on their owner.";
    _pardesc[0] = "Race (0=viewpoint, -1=any)";
    _pardesc[1] = "Fields affect mask";
    _pardesc[4] = "Negate filter";
  }
  
  virtual void function(map_view& mw, planet* p, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = p->disp;

    bool f = false;

    if (p->owner()) {
      if (par[0] == -1) // just kill
	f = true;
      else {
	race* r = (par[0])? mw.get_map()->find_race(par[0] - 1) : mw.viewpoint();

	if (mw.set_alliances(MW_READ))
	  f = mw.get_map()->are_allies(p->owner(), r);
	else
	  f = (r == p->owner());
      }
    }

    if (par[4])
      f = !f;

    if (par[1]) {
      if (f)
	d.reset_something(par[1]);
    } else
      d.flag = f;
  }
};

pla_F_ownerkill pla_F_ownerkill_proto;


// kill on distance

class pla_F_distancekill : public planetary_function {
  int sel_pla_id;
  planet* sel_pla;

public:
  pla_F_distancekill(void) : sel_pla_id(-1), sel_pla(NULL)
  {
    _name = "Filter: distance";
    _type = "General";
    _desc = "Filter planets depending on their distance from the given one.\nSet min.=max.=0 to filter the given planet.";
    _pardesc[0] = "Planet id (0 = selected)";
    _pardesc[1] = "Fields affect mask";
    _pardesc[2] = "Min. distance";
    _pardesc[3] = "Max. distance";
    _pardesc[4] = "Negate filter";
  }
  
  virtual void function(map_view& mw, planet* p, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = p->disp;

    bool f = false;

    // find planet
    int pid = ((par[0]>0)? par[0] : mw.get_active_planet()->starsid());

    if (pid != sel_pla_id) {
      if (par[0] > 0)
	sel_pla = mw.get_map()->find_planet(par[0]);
      else
	sel_pla = mw.get_active_planet();

      if (!sel_pla)
	return;

      sel_pla_id = pid;
    }

    if (par[2] == 0 && par[3] == 0) {
      // just sel_pla
      f = (p == sel_pla);

    } else {
      int val = (int)(0.99+ sqrt((sel_pla->position().x - p->position().x)*
				 (sel_pla->position().x - p->position().x) +
				 (sel_pla->position().y - p->position().y)*
				 (sel_pla->position().y - p->position().y)));

      f = (par[2] <= par[3] && val >= par[2] && val <= par[3]) ||
	(par[2] > par[3] && (val >= par[2] || val <= par[3]));
    }

    if (par[4])
      f = !f;

    if (par[1]) {
      if (f)
	d.reset_something(par[1]);
    } else
      d.flag = f;
  }
};

pla_F_distancekill pla_F_distancekill_proto;





// show report age

class pla_reportage : public planetary_function {
public:
  pla_reportage(void)
  {
    _name = "Report age";
    _type = "General";
    _desc = "Create a circle whose radius depends on the report age.\nGreen if 0-1, yellow 2-9, red beyond.";
  }
  
  virtual void function(map_view& mw, planet* p, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = p->disp;

    if (!p->data_available())
      return;

    if (p->report_age() < 2) {
      d.vmin = 0;
      d.vmax = 50;
      d.values[0].value = 30 - 5*p->report_age();
      d.values[0].color = COL_GREENHAB;
    } else if (p->report_age() < 10) {
      d.vmin = 0;
      d.vmax = 50;
      d.values[0].value = 25 - 2 * (p->report_age() - 2) ;
      d.values[0].color = COL_YELLOWHAB;
    } else {
      d.vmin = 0;
      d.vmax = 50;
      d.values[0].value = 11 + 2 * (p->report_age() - 10);
      d.values[0].color = COL_REDHAB;
    }

    d.n_values = 1;
    d.flag = true;
  }
};

pla_reportage pla_reportage_proto;



// filter on report age

class pla_F_reportage : public planetary_function {
public:
  pla_F_reportage(void)
  {
    _name = "Filter: report age";
    _type = "General";
    _desc = "Filters planets depending on report age of the information.";
    _pardesc[1] = "Fields affect mask";
    _pardesc[2] = "Min. age";
    _pardesc[3] = "Max. age";
    _pardesc[4] = "Negate filter";
  }
  
  virtual void function(map_view& mw, planet* p, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = p->disp;

    bool f = false;

    if (p->data_available()) {
      int val = p->report_age();

      f = (par[2] <= par[3] && val >= par[2] && val <= par[3]) ||
	(par[2] > par[3] && (val >= par[2] || val <= par[3]));
    }

    if (par[4])
      f = !f;

    if (par[1]) {
      if (f)
	d.reset_something(par[1]);
    } else
      d.flag = f;
  }
};

pla_F_reportage pla_F_reportage_proto;

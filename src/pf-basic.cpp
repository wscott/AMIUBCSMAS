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
    _desc = "This function associates a marker to a planet:\n[3] use 1=dot, 2=cross, 3=box, 4=square, 5=circle, 6=flag.";
    _pardesc[3] = "Marker type";
  }
  
  virtual void function(map_view& mw, planet* p, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = p->disp;

    if (par[3] >= 0 && par[3] <= MAX_MARKER) {
      d.marker_type = (_marktype)par[3];
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
    _desc = "This function associates single value data to a planet.\n[3] data is assumed to be in the range [0,100].";
    _pardesc[3] = "Data value";
  }
  
  virtual void function(map_view& mw, planet* p, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = p->disp;

    // range
    d.vmin = 0;
    d.vmax = 100;
    d.values[0].value = par[3];
    d.values[0].color = COL_GREY;

    d.n_values = 1;
    d.flag = true;
  }
};

pla_setdata pla_setdata_proto;




// associate circles to a planet

class pla_setcircles : public planetary_function {
public:
  pla_setcircles(void)
  {
    _name = "Set Circles";
    _type = "General";
    _desc = "This function associates a series of circles to a planet.\n[0] use 0 to specify the owner's color.";
    _pardesc[0] = "Color";
    _pardesc[3] = "Circle radius";
    _pardesc[4] = "N. of circles";
  }
  
  virtual void function(map_view& mw, planet* p, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = p->disp;

    int i, r;
    int col = COL_YELLOWHAB;

    if (par[0] > 0 && par[0] <= 24)
      col = COL_WHITE + 4 * (par[0] - 1);
    else if (p->data_available() && p->owner())
      col = COL_RACES + 4 * p->owner()->race_id();

    for (r = par[3], i = 0; i < par[4]; r += par[3], i++) {
      d.circles[i].radius = r;
      d.circles[i].fillcolor = -1;
      d.circles[i].color = col + min(i, 3);
    }

    d.flag = true;
  }
};

pla_setcircles pla_setcircles_proto;



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
    _desc = "This function sets the color of the name of the planet.\n[0] use 0 to specify the owner's color.";
    _pardesc[0] = "Color";
  }
  
  virtual void function(map_view& mw, planet* p, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = p->disp;

    // do we have name?
    if (d.name_color) {
      if (par[0] > 0 && par[0] <= 24)
	d.name_color = COL_WHITE + 4 * (par[0] - 1);
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
    _desc = "This function sets the color of the marker of the planet.\n[0] use 0 to specify the owner's color.";
    _pardesc[0] = "Color";
  }

  virtual void function(map_view& mw, planet* p, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = p->disp;

    // do we have a marker?
    if (d.marker_type != MT_NONE) {
      if (par[0] > 0 && par[0] <= 24)
	d.marker_color = COL_WHITE + 4 * (par[0] - 1);
      else if (p->data_available() && p->owner())
	d.marker_color = COL_RACES + 4 * p->owner()->race_id();
    }
  }
};

pla_owner pla_owner_proto;



// set color of single pieslice data

class pla_datacolor : public planetary_function {
public:
  pla_datacolor(void)
  {
    _name = "Color: data";
    _type = "General";
    _desc = "This function sets the color of the data associated to a planet\n(only if it's single-valued).\n[0] use 0 to specify the owner's color.";
    _pardesc[0] = "Color";
  }

  virtual void function(map_view& mw, planet* p, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = p->disp;

    // make sure we have single data
    if (d.n_values == 1) {
      if (par[0] > 0 && par[0] <= 24)
	d.values[0].color = COL_WHITE + 4 * (par[0] - 1);
      else if (p->data_available() && p->owner())
	d.values[0].color = COL_RACES + 4 * p->owner()->race_id();
    }
  }
};

pla_datacolor pla_datacolor_proto;



// random % chance of killing

class pla_F_randomkill : public planetary_function {
public:
  pla_F_randomkill(void)
  {
    _name = "Filter: random";
    _type = "General";
    _desc = "Randomly filters the planet out.";
    _pardesc[1] = "Fields affect mask";
    _pardesc[2] = "Negate filter";
    _pardesc[3] = "Chance %";
    _pardesc[4] = "Random seed";
  }

  virtual void function(map_view& mw, planet* p, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = p->disp;

    srand((unsigned int)p + par[4]);

    bool filt = ((rand() % 100) < par[3]);

    if (par[2])
      filt = !filt;

    if (par[1]) {
      if (filt)
	d.reset_something(par[1]);
    } else
      d.flag = filt;
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
    _pardesc[2] = "Negate filter";
  }
  
  virtual void function(map_view& mw, planet* p, const int* par, const int when)
  {
    if (par[1])
      p->disp.reset_something(par[1]);
    else
      p->disp.flag = (par[2]? false : true);
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
    _pardesc[2] = "Negate filter";
  }
  
  virtual void function(map_view& mw, planet* p, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = p->disp;

    bool f = !(p->data_available());

    if (par[2])
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
    _desc = "Filters planets equipped with a starbase.\n [3,4] they types are 0=none, 1=Fort 2=Dock 3=Station 4=Ultra 5=Death Star.";
    _pardesc[1] = "Fields affect mask";
    _pardesc[2] = "Negate filter";
    _pardesc[3] = "Min. type";
    _pardesc[4] = "Max. type";
  }
  
  virtual void function(map_view& mw, planet* p, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = p->disp;

    bool f = false;

    if (p->data_available() && p->owner()) {
      int val = (int)p->starbase_power();
      
      f = (par[3] <= par[4] && val >= par[3] && val <= par[4]) ||
	(par[3] > par[4] && (val >= par[3] || val <= par[4]));
    }

    if (par[2])
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
    _desc = "Filters planets depending on their owner.\n[0] use race number or 0 for current viewpoint, -1 for any.";
    _pardesc[0] = "Race";
    _pardesc[1] = "Fields affect mask";
    _pardesc[2] = "Negate filter";
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

    if (par[2])
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
    _desc = "Filter planets depending on their distance from the given one.\nSet min.=max.=0 to filter the given planet.\n[0] use -1 or -2 to specify the first or second selected planet.";
    _pardesc[0] = "Planet id";
    _pardesc[1] = "Fields affect mask";
    _pardesc[2] = "Negate filter";
    _pardesc[3] = "Min. distance";
    _pardesc[4] = "Max. distance";
  }
  
  virtual void function(map_view& mw, planet* p, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = p->disp;

    bool f = false;

    // find planet
    int pid = ((par[0]>0)? par[0] : mw.get_active_planet(-par[0]-1)->starsid());

    if (pid != sel_pla_id) {
      if (par[0] > 0)
	sel_pla = mw.get_map()->find_planet(par[0]);
      else
	sel_pla = mw.get_active_planet(-par[0]-1);

      if (!sel_pla)
	return;

      sel_pla_id = pid;
    }

    if (par[3] == 0 && par[4] == 0) {
      // just sel_pla
      f = (p == sel_pla);

    } else {
      int val = (int)(0.99+ sqrt((sel_pla->position().x - p->position().x)*
				 (sel_pla->position().x - p->position().x) +
				 (sel_pla->position().y - p->position().y)*
				 (sel_pla->position().y - p->position().y)));

      f = (par[3] <= par[4] && val >= par[3] && val <= par[4]) ||
	(par[3] > par[4] && (val >= par[3] || val <= par[4]));
    }

    if (par[2])
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
    _desc = "Create a circle whose radius depends on the report age.\nGreen if <= [3], yellow if <= [4], red beyond.";
    _pardesc[3] = "Green";
    _pardesc[4] = "Yellow";
  }
  
  virtual void function(map_view& mw, planet* p, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = p->disp;

    if (!p->data_available())
      return;

    if (p->report_age() <= par[3]) {
      d.vmin = 0;
      d.vmax = 100;
      d.values[0].value = 60 - 20*p->report_age()/par[3];
      d.values[0].color = COL_GREENHAB;
    } else if (p->report_age() < par[4]) {
      d.vmin = 0;
      d.vmax = 100;
      d.values[0].value = 50 - 40*(p->report_age() - par[3])/par[4];
      d.values[0].color = COL_YELLOWHAB;
    } else {
      d.vmin = 0;
      d.vmax = 100;
      d.values[0].value = 22 + 4 * (p->report_age() - par[4]);
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
    _pardesc[2] = "Negate filter";
    _pardesc[3] = "Min. age";
    _pardesc[4] = "Max. age";
  }
  
  virtual void function(map_view& mw, planet* p, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = p->disp;

    bool f = false;

    if (p->data_available()) {
      int val = p->report_age();

      f = (par[3] <= par[4] && val >= par[3] && val <= par[4]) ||
	(par[3] > par[4] && (val >= par[3] || val <= par[4]));
    }

    if (par[2])
      f = !f;

    if (par[1]) {
      if (f)
	d.reset_something(par[1]);
    } else
      d.flag = f;
  }
};

pla_F_reportage pla_F_reportage_proto;

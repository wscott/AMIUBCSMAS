#include "starana-classes.h"



// null function, do nothing at all

class fle_nullfunction : public fleet_function {
public:
  fle_nullfunction(void)
  {
    _name = "- (nothing) -";
    _type = "General";
    _desc = "This function does nothing at all.";
  }

  virtual void function(map_view& mw, fleet* p, const int* par, const int when)
  {
    return;
  }
};

fle_nullfunction fle_nullfunction_proto;



// associate a marker to a fleet

class fle_setmarker : public fleet_function {
public:
  fle_setmarker(void)
  {
    _name = "Set Marker";
    _type = "General";
    _desc = "This function associates a marker to a fleet:\n[3]1=dot, 2=cross, 3=box, 4=square, 5=circle, 6=flag.";
    _pardesc[3] = "Marker type";
  }
  
  virtual void function(map_view& mw, fleet* f, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = f->disp;

    if (par[3] >= 0 && par[3] <= MAX_MARKER) {
      d.marker_type = (_marktype)par[3];
      d.marker_color = COL_WHITE;
    }

    d.flag = true;
  }
};

fle_setmarker fle_setmarker_proto;



// associate fixed data to a fleet

class fle_setdata : public fleet_function {
public:
  fle_setdata(void)
  {
    _name = "Set Data";
    _type = "General";
    _desc = "This function associates single value data to a fleet.\n[3] Data is assumed to be in the range [0,100].";
    _pardesc[3] = "Data value";
  }
  
  virtual void function(map_view& mw, fleet* f, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = f->disp;

    // range
    d.pie_type = PIE_TRIANG;
    d.vmin = 0;
    d.vmax = 100;
    d.values[0].value = par[3];
    d.values[0].color = COL_GREY;

    d.n_values = 1;
    d.flag = true;
  }
};

fle_setdata fle_setdata_proto;



// set marker color

class fle_owner : public fleet_function {
public:
  fle_owner(void)
  {
    _name = "Color: marker";
    _type = "General";
    _desc = "This function sets the color of the marker of the fleet.\n[0] specify the color number or 0 to indicate the color of the owner.";
    _pardesc[0] = "Color";
  }

  virtual void function(map_view& mw, fleet* f, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = f->disp;

    // do we have a marker?
    if (d.marker_type != MT_NONE) {
      if (par[0] > 0 && par[0] <= 24)
	d.marker_color = COL_WHITE + 4 * (par[0] - 1);
      else
	d.marker_color = COL_RACES + 4 * f->owner()->race_id();
    }
  }
};

fle_owner fle_owner_proto;



// set color of single pieslice data

class fle_colordata : public fleet_function {
public:
  fle_colordata(void)
  {
    _name = "Color: data";
    _type = "General";
    _desc = "This function sets the color of the data associated to a fleet\n(only if it's single-valued).\n[0] specify the color number or 0 to indicate the color of the owner.";
    _pardesc[0] = "Color";
  }

  virtual void function(map_view& mw, fleet* f, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = f->disp;

    // make sure we have single data
    if (d.n_values == 1) {
      if (par[0] > 0 && par[0] <= 24)
	d.values[0].color = COL_WHITE + 4 * (par[0] - 1);
      else
	d.values[0].color = COL_RACES + 4 * f->owner()->race_id();
    }
  }
};

fle_colordata fle_colordata_proto;



// associate circles to a fleet

class fle_setcircles : public fleet_function {
public:
  fle_setcircles(void)
  {
    _name = "Set Circles";
    _type = "Movement";
    _desc = "This function associates a series of circles to a fleet.\n[0] use 0 to specify the owner's color.";
    _pardesc[0] = "Color";
    _pardesc[3] = "Circle radius";
    _pardesc[4] = "N. of circles";  }
  
  virtual void function(map_view& mw, fleet* f, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = f->disp;

    int i, r;
    int col = COL_YELLOWHAB;

    if (par[0] > 0 && par[0] <= 24)
      col = COL_WHITE + 4 * (par[0] - 1);
    else
      col = COL_RACES + 4 * f->owner()->race_id();

    for (r = par[3], i = 0; i < par[4]; r += par[3], i++) {
      d.circles[i].radius = r;
      d.circles[i].fillcolor = -1;
      d.circles[i].color = col + min(i, 3);
    }

    d.n_circles = i;
    d.flag = true;
  }
};

fle_setcircles fle_setcircles_proto;



// the default fleet name functions

class fle_all_names : public fleet_function {
public:
  fle_all_names(void)
  {
    _name = "Set Fleet Name";
    _type = "Names";
    _desc = "This function associates a name (but no ID) to a fleet.";
  }
  
  virtual void function(map_view& mw, fleet* f, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = f->disp;

    d.name = f->name();
    d.name_color = COL_WHITE;
    d.flag = true;
  }
};

fle_all_names fle_all_names_proto;



class fle_all_starids : public fleet_function {
public:
  fle_all_starids(void)
  {
    _name = "Set Fleet Name+Id";
    _type = "Names";
    _desc = "This function associates to a fleet a name identical to that used in Stars!.";
  }
  
  virtual void function(map_view& mw, fleet* f, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = f->disp;

    d.name = f->starsname();
    d.name_color = COL_WHITE;
    d.flag = true;
  }
};

fle_all_starids fle_all_starids_proto;



class fle_numships : public fleet_function {
public:
  fle_numships(void)
  {
    _name = "Set # of ships";
    _type = "Names";
    _desc = "This function associates to a fleet a name which is the number of ships\nin the fleet.\nNOTE: contrary to Stars! superimposed fleets are NOT summed.";
  }

  virtual void function(map_view& mw, fleet* f, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = f->disp;

    d.name = int_to_str(f->n_ships(F_TOTAL));
    d.name_color = COL_WHITE;

    d.flag = true;
  }
};

fle_numships fle_numships_proto;



// set name color

class fle_owncolor_names : public fleet_function {
public:
  fle_owncolor_names(void)
  {
    _name = "Color: name";
    _type = "Names";
    _desc = "This function sets the color of the name of the fleet.\n[0] use 0 to specify the owner's color.";
    _pardesc[0] = "Color";
  }
  
  virtual void function(map_view& mw, fleet* f, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = f->disp;

    // do we have name?
    if (d.name_color) {
      if (par[0] > 0 && par[0] <= 24)
	d.name_color = COL_WHITE + 4 * (par[0] - 1);
      else
	d.name_color = COL_RACES + 4 * f->owner()->race_id();
    }
  }
};

fle_owncolor_names fle_owncolor_names_proto;



// random % chance of killing

class fle_F_randomkill : public fleet_function {
public:
  fle_F_randomkill(void)
  {
    _name = "Filter: random";
    _type = "General";
    _desc = "Randomly filters the fleet out.";
    _pardesc[1] = "Fields affect mask";
    _pardesc[2] = "Negate filter";
    _pardesc[3] = "Chance %";
    _pardesc[4] = "Random seed";
  }
  
  virtual void function(map_view& mw, fleet* f, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = f->disp;

    srand((unsigned int) + par[4]);

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

fle_F_randomkill fle_F_randomkill_proto;



// unconditional kill

class fle_F_kill : public fleet_function {
public:
  fle_F_kill(void)
  {
    _name = "Filter: unconditional";
    _type = "General";
    _desc = "Filters out all fleets.";
    _pardesc[1] = "Fields affect mask";
    _pardesc[2] = "Negate filter";
  }
  
  virtual void function(map_view& mw, fleet* f, const int* par, const int when)
  {
    if (par[1])
      f->disp.reset_something(par[1]);
    else
      f->disp.flag = (par[2]? false : true);
  }
};

fle_F_kill fle_F_kill_proto;



// kill if owned

class fle_F_ownerkill : public fleet_function {
public:
  fle_F_ownerkill(void)
  {
    _name = "Filter: owner";
    _type = "General";
    _desc = "Filters fleets depending on their owner.\n[0] use race number or 0 for current viewpoint.";
    _pardesc[0] = "Race";
    _pardesc[1] = "Fields affect mask";
    _pardesc[2] = "Negate filter";
  }
  
  virtual void function(map_view& mw, fleet* f, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = f->disp;

    bool filt = false;

    race* r = (par[0])? mw.get_map()->find_race(par[0] - 1) : mw.viewpoint();

    if (mw.set_alliances(MW_READ))
      filt = mw.get_map()->are_allies(f->owner(), r);
    else
      filt = (r == f->owner());

    if (par[2])
      filt = !filt;

    if (par[1]) {
      if (filt)
	d.reset_something(par[1]);
    } else
      d.flag = filt;
  }
};

fle_F_ownerkill fle_F_ownerkill_proto;



// kill if orbiting a world

class fle_F_orbitkill : public fleet_function {
public:
  fle_F_orbitkill(void)
  {
    _name = "Filter: orbiting";
    _type = "General";
    _desc = "Filters fleets which are orbiting around a planet.";
    _pardesc[1] = "Fields affect mask";
    _pardesc[2] = "Negate filter";
  }
  
  virtual void function(map_view& mw, fleet* f, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = f->disp;

    bool filt = (f->orbiting(when) == NULL);

    if (par[2])
      filt = !filt;

    if (par[1]) {
      if (filt)
	d.reset_something(par[1]);
    } else
      d.flag = filt;
  }
};

fle_F_orbitkill fle_F_orbitkill_proto;



// kill on distance

class fle_F_distancekill : public fleet_function {
  int sel_pla_id;
  planet* sel_pla;

public:
  fle_F_distancekill(void) : sel_pla_id(-1), sel_pla(NULL)
  {
    _name = "Filter: distance";
    _type = "General";
    _desc = "Filter fleets depending on their distance from a planet.[0] use -1 or -2 to specify the first or second selected planet.";
    _pardesc[0] = "Planet id";
    _pardesc[1] = "Fields affect mask";
    _pardesc[2] = "Negate filter";
    _pardesc[3] = "Min. distance";
    _pardesc[4] = "Max. distance";
  }
  
  virtual void function(map_view& mw, fleet* f, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = f->disp;

    bool filt = false;

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

    int val = (int)(0.99+ sqrt((sel_pla->position().x - f->position(when).x)*
			       (sel_pla->position().x - f->position(when).x) +
			       (sel_pla->position().y - f->position(when).y)*
			       (sel_pla->position().y - f->position(when).y)));

    filt = (par[3] <= par[4] && val >= par[3] && val <= par[4]) ||
      (par[3] > par[4] && (val >= par[3] || val <= par[4]));

    if (par[2])
      filt = !filt;
    
    if (par[1]) {
      if (filt)
	d.reset_something(par[1]);
    } else
      d.flag = filt;
  }
};

fle_F_distancekill fle_F_distancekill_proto;

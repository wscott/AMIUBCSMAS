#include "starana-classes.h"


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


// use the # of ships in a fleet to set the name

class fle_numships : public fleet_function {
public:
  fle_numships(void)
  {
    _name = "Set # of ships";
    _type = "Names";
    _desc = "This function associates to a fleet a name which is the number of ships\nin the fleet.\nNOTE: contrary to Stars! superimposed fleets are NOT summed.\n[5..9] select what classes NOT to include in the count.";
    _pardesc[5] = "Exclude scouts";
    _pardesc[6] = "Exclude unarmed";
    _pardesc[7] = "Exclude warship";
    _pardesc[8] = "Exclude utility";
    _pardesc[9] = "Exclude bomber";
  }

  virtual void function(map_view& mw, fleet* f, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = f->disp;

    int num = f->n_ships(F_TOTAL);

    if (par[5])
      num -= f->n_ships(F_SCOUT);
    if (par[6])
      num -= f->n_ships(F_UNARMED);
    if (par[7])
      num -= f->n_ships(F_WARSHIP);
    if (par[8])
      num -= f->n_ships(F_UTILITY);
    if (par[9])
      num -= f->n_ships(F_BOMBER);

    if (num) {
      d.name = int_to_str(num);
      d.name_color = COL_WHITE;

      d.flag = true;
    }
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

#include "starana-classes.h"


// associate pie with size depending on mass

class fle_mass : public fleet_function {
public:
  fle_mass(void)
  {
    _name = "Mass";
    _type = "Composition";
    _desc = "This function associates data to a fleet depending on the total fleet mass.";
    _pardesc[4] = "Full triangle at";
  }
  
  virtual void function(map_view& mw, fleet* f, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = f->disp;

    d.pie_type = PIE_TRIANG;
    d.vmin = 0;
    d.vmax = (par[4])? par[4] : 1000;

    d.values[d.n_values].value = f->mass();
    d.values[d.n_values++].color = COL_WHITE;

    d.flag = true;
  }
};

fle_mass fle_mass_proto;


// associate pie with size depending on generic composition

class fle_gcomposition : public fleet_function {
public:
  fle_gcomposition(void)
  {
    _name = "Composition";
    _type = "Composition";
    _desc = "This function associates data to a fleet depending on the number of\nships in the fleet. You can exclude certain classes from the count.\n[5..9] select what classes NOT to include in the count.";
    _pardesc[4] = "Full triangle at";
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

    d.pie_type = PIE_TRIANG;
    d.vmin = 0;
    d.vmax = (par[4])? par[4] : 30;

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
      d.values[d.n_values].value = num;
      d.values[d.n_values++].color = COL_WHITE;

      d.flag = true;
    }
  }
};

fle_gcomposition fle_gcomposition_proto;

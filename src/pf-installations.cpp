#include "starana-classes.h"


// defense coverage display

class pla_defcoverage : public planetary_function {
public:
  pla_defcoverage(void)
  {
    _name = "Def. coverage %";
    _type = "Installations";
    _desc = "This function generates a disk with a size based on the planet's\ndefense coverage %.";
  }

  virtual void function(map_view& mw, planet* p, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = p->disp;

    // we can do something if we have the data
    if (!p->data_available() || !p->owner())
      return;

    if ( (d.values[0].value = p->defense_coverage(when)) ) {
      // range
      d.vmin = 0;
      d.vmax = 10000;

      d.values[0].color = COL_GREY;
      d.n_values = 1;
      d.flag = true;
    }
  }
};

pla_defcoverage pla_defcoverage_proto;


// factories display

class pla_factories : public planetary_function {
public:
  pla_factories(void)
  {
    _name = "Factories";
    _type = "Installations";
    _desc = "This function generates a pie whose radius depends on the maximum number\nof factories on the planet, with a green section for operated,\nred for built but not operated, yellow for operable but not built and\nwhite for the remaining to maximum.";
  }

  virtual void function(map_view& mw, planet* p, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = p->disp;

    // we can do something if we have the data
    if (!p->data_available() || !p->owner())
      return;

    // range
    d.vmin = 0;
    d.vmax = p->owner()->max_fact_per_planet();
    // override default range
    d.value = p->maxfactories(when);

    d.values[0].color = COL_GREENHAB;
    d.values[2].color = COL_GREY;

    if (p->unused_factories()) {
      // slice 1 is unoperated ones
      d.values[1].color = COL_REDHAB;

      d.values[0].value = p->maxcfactories(when);
      d.values[1].value = p->unused_factories(when);
      d.values[2].value = d.vmax - p->factories();

    } else {
      // slice 1 is "potential" ones
      d.values[1].color = COL_YELLOWHAB;

      d.values[0].value = p->factories(when);
      d.values[1].value = p->maxcfactories(when) - p->factories(when);
      d.values[2].value = d.vmax - p->maxcfactories();
    }

    d.n_values = 3;
    d.flag = true;
  }
};

pla_factories pla_factories_proto;


// mines display

class pla_mines : public planetary_function {
public:
  pla_mines(void)
  {
    _name = "Mines";
    _type = "Installations";
    _desc = "This function generates a pie whose radius depends on the maximum number\nof mines on the planet, with a green section for operated,\nred for built but not operated, yellow for operable but not built and\nwhite for the remaining to maximum.";
  }

  virtual void function(map_view& mw, planet* p, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = p->disp;

    // we can do something if we have the data
    if (!p->data_available() || !p->owner())
      return;

    // range
    d.vmin = 0;
    d.vmax = p->owner()->max_mine_per_planet();
    // override default range
    d.value = p->maxmines(when);

    d.values[0].color = COL_GREENHAB;
    d.values[2].color = COL_GREY;

    if (p->unused_mines()) {
      // slice 1 is unoperated ones
      d.values[1].color = COL_REDHAB;

      d.values[0].value = p->maxcmines(when);
      d.values[1].value = p->unused_mines(when);
      d.values[2].value = d.vmax - p->mines();

    } else {
      // slice 1 is "potential" ones
      d.values[1].color = COL_YELLOWHAB;

      d.values[0].value = p->mines(when);
      d.values[1].value = p->maxcmines(when) - p->mines(when);
      d.values[2].value = d.vmax - p->maxcmines();
    }

    d.n_values = 3;
    d.flag = true;
  }
};

pla_mines pla_mines_proto;


// scanner coverage

class pla_scancoverage : public planetary_function {
public:
  pla_scancoverage(void)
  {
    _name = "Scanning";
    _type = "Installations";
    _desc = "This function generates a circle with a size based on the planet's\nscanning ranges.";
  }

  virtual void function(map_view& mw, planet* p, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = p->disp;

    // we can do something if we have the data
    if (!p->data_available() || !p->owner() || !p->scanning())
      return;

    d.circles[0].radius = mw.set_scanner_eff(MW_READ) * p->scanning() / 100;
    d.circles[0].color = -1;
    d.circles[0].fillcolor = COL_SCAN;
    d.circles[1].radius = mw.set_scanner_eff(MW_READ) * p->penscanning() / 100;
    d.circles[1].color = -1;
    d.circles[1].fillcolor = COL_PENSCAN;

    d.n_circles = 2;
    d.flag = true;
  }
};

pla_scancoverage pla_scancoverage_proto;


// gate coverage

class pla_gatecoverage : public planetary_function {
public:
  pla_gatecoverage(void)
  {
    _name = "Gate coverage";
    _type = "Installations";
    _desc = "This function generates a circle with a size based on the planet's\ngate ranges.";
  }

  virtual void function(map_view& mw, planet* p, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = p->disp;

    // we can do something if we have the data
    if (!p->data_available() || !p->owner() || p->gate_range() <= 0)
      return;

    d.circles[0].radius = p->gate_range();
    d.circles[0].fillcolor = -1;
    d.circles[0].color = COL_YELLOWHAB;
    d.circles[1].radius = p->gate_range() * 2;
    d.circles[1].fillcolor = -1;
    d.circles[1].color = COL_YELLOWHAB + 1;
    d.circles[2].radius = p->gate_range() * 3;
    d.circles[2].fillcolor = -1;
    d.circles[2].color = COL_YELLOWHAB + 2;

    d.n_circles = 3;
    d.flag = true;
  }
};

pla_gatecoverage pla_gatecoverage_proto;


// filter on gate presence

class pla_F_gate : public planetary_function {
public:
  pla_F_gate(void)
  {
    _name = "Filter: stargate";
    _type = "Installations";
    _desc = "This function filters planet based on their gate statistics.\nA planet will be filtered if its range and mass are superior or equal to the required ones.";
    _pardesc[1] = "Fields affect mask";
    _pardesc[2] = "Negate filter";
    _pardesc[3] = "Minimum range";
    _pardesc[4] = "Minimum mass";
  }

  virtual void function(map_view& mw, planet* p, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = p->disp;

    bool f = false;

    // we can do something if we have the data
    if (p->data_available() && p->owner())
      f = ((p->gate_range() == -1)? 1 : (p->gate_range() >= par[3])) &&
	  ((p->gate_mass() == -1)? 1 : (p->gate_mass() >= par[4]));

    if (par[2])
      f = !f;

    if (par[1]) {
      if (f)
	d.reset_something(par[1]);
    } else
      d.flag = f;
  }
};

pla_F_gate pla_F_gate_proto;

#include "starana-classes.h"


// population display

class pla_population : public planetary_function {
public:
  pla_population(void)
  {
    _name = "Population";
    _type = "Population";
    _desc = "This function generates a white disk with a size proportional to\nthe total population. The disk turns yellow if beyond 100%\ncapacity and red beyond 300%";
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
    d.vmax = p->owner()->max_pop_per_planet();

    d.values[0].value = p->population(when);

    if (p->capacity() <= 1000)
      d.values[0].color = COL_GREY;
    else if (p->capacity() <= 3000)
      d.values[0].color = COL_YELLOWHAB;
    else
      d.values[0].color = COL_REDHAB;

    d.n_values = 1;
    d.flag = true;
  }
};

pla_population pla_population_proto;



// population growth display

class pla_pop_growth : public planetary_function {
public:
  pla_pop_growth(void)
  {
    _name = "Population growth";
    _type = "Population";
    _desc = "This function generates a disk with a size based on the population\ngrowth on the planet.";
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
    d.vmax = 50000;

    d.values[0].value = p->population(when+1) - p->population(when);
    d.values[0].color = COL_GREY;

    d.n_values = 1;
    d.flag = true;
  }
};

pla_pop_growth pla_pop_growth_proto;



// population filling display

class pla_popfilling : public planetary_function {
public:
  pla_popfilling(void)
  {
    _name = "Population Filling";
    _type = "Population";
    _desc = "This function generates a disk with a size based on the current\npopulation filling. The disk is green for filling below 25%, yellow\nfor 25%-33% and red beyond 33%";
  }
  
  virtual void function(map_view& mw, planet* p, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = p->disp;

    // we can do something if we have the data
    if (!p->data_available() || !p->owner())
      return;

    int ff = p->capacity(when);

    d.values[0].value = ff;
    if (ff <= 250) {
      d.vmin = 0;
      d.vmax = 250;
      d.values[0].color = COL_GREENHAB;
    } else if (ff <= 330) {
      d.vmin = 200;
      d.vmax = 330;
      d.values[0].color = COL_YELLOWHAB;
    } else if (ff <= 480) {
      d.vmin = 330;
      d.vmax = 480;
      d.values[0].color = COL_YELLOWHAB+2;
    } else {
      d.vmin = 250;
      d.vmax = 1000;
      d.values[0].color = COL_REDHAB;
    }

    d.n_values = 1;
    d.flag = true;
  }
};

pla_popfilling pla_popfilling_proto;



// resources display (ok, not EXACTLY population... :)

class pla_resources : public planetary_function {
public:
  pla_resources(void)
  {
    _name = "Resources";
    _type = "Population";
    _desc = "This function generates a white disk with a size based on the\nplanet's total resource output";
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
    d.vmax = p->owner()->max_res_per_planet();

    d.values[0].value = p->resources(when);
    d.values[0].color = COL_GREY;

    d.n_values = 1;
    d.flag = true;
  }
};

pla_resources pla_resources_proto;



// filter on population value

class pla_F_population : public planetary_function {
public:
  pla_F_population(void)
  {
    _name = "Filter: population";
    _type = "Population";
    _desc = "This function filters planets depending on their population.";
    _pardesc[1] = "Fields affect mask";
    _pardesc[2] = "Min value";
    _pardesc[3] = "Max value";
    _pardesc[4] = "Negate filter";
  }
  
  virtual void function(map_view& mw, planet* p, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = p->disp;

    bool f = false;

    // we can do something if we have the data
    if (p->data_available() && !p->owner()) {
      int val = p->population(when);
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

pla_F_population pla_F_population_proto;



// filter on resources

class pla_F_resources : public planetary_function {
public:
  pla_F_resources(void)
  {
    _name = "Filter: resources";
    _type = "Population";
    _desc = "This function filters planets depending on their total resource output.";
    _pardesc[1] = "Fields affect mask";
    _pardesc[2] = "Min value";
    _pardesc[3] = "Max value";
    _pardesc[4] = "Negate filter";
  }
  
  virtual void function(map_view& mw, planet* p, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = p->disp;

    bool f = false;

    // we can do something if we have the data
    if (p->data_available() && !p->owner()) {
      int val = p->resources(when);
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

pla_F_resources pla_F_resources_proto;

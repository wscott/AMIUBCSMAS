#include "starana-classes.h"


// surface minerals display

class pla_surf_minerals : public planetary_function {
public:
  pla_surf_minerals(void)
  {
    _name = "Surface Minerals";
    _type = "Minerals";
    _desc = "This function generates a pie chart with a radius proportional to\nthe maximum of a single surface mineral, but with every slice with\nan angle proportional to every surface mineral.";
    _pardesc[1] = "Mineral mask";
    _pardesc[3] = "Full circle at kT";
  }
  
  virtual void function(map_view& mw, planet* p, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = p->disp;

    // we can do something if we have the data
    if (!p->data_available() && p->owner())
      return;

    _mintype m;

    // range
    d.vmin = 0;
    d.vmax = (par[3])? par[3] : 6000;

    m = p->minerals(when);
    d.n_values = 0;

    if ( !((par[1]/100) & 1) ) {
      d.values[d.n_values].value = m.iron;
      d.values[d.n_values++].color = COL_IRON;
    }

    if ( !((par[1]/10) & 1) ) {
      d.values[d.n_values].value = m.bora;
      d.values[d.n_values++].color = COL_BORA;
    }

    if ( !(par[1] & 1) ) {
      d.values[d.n_values].value = m.germ;
      d.values[d.n_values++].color = COL_GERM;
    }

    d.flag = true;
  }
};

pla_surf_minerals pla_surf_minerals_proto;



// mining display

class pla_mining : public planetary_function {
public:
  pla_mining(void)
  {
    _name = "Mining";
    _type = "Minerals";
    _desc = "This function generates a pie chart with a radius proportional to\nthe maximum of a single mining rate, but with every slice with an\nangle proportional to every mineral mining rate.";
    _pardesc[1] = "Mineral mask";
    _pardesc[3] = "Full circle at kT";
  }
  
  virtual void function(map_view& mw, planet* p, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = p->disp;

    // we can do something if we have the data
    if (!p->data_available() && p->owner())
      return;

    _mintype m;

    // range
    d.vmin = 0;
    d.vmax = (par[3])? par[3] : 1000;

    m = p->mining_rate(when);
    d.n_values = 0;

    if ( !((par[1]/100) & 1) ) {
      d.values[d.n_values].value = m.iron;
      d.values[d.n_values++].color = COL_IRON;
    }

    if ( !((par[1]/10) & 1) ) {
      d.values[d.n_values].value = m.bora;
      d.values[d.n_values++].color = COL_BORA;
    }

    if ( !(par[1] & 1) ) {
      d.values[d.n_values].value = m.germ;
      d.values[d.n_values++].color = COL_GERM;
    }

    d.flag = true;
  }
};

pla_mining pla_mining_proto;



// mineral concentrations

class pla_mineral_conc : public planetary_function {
public:
  pla_mineral_conc(void)
  {
    _name = "Mineral concentrations";
    _type = "Minerals";
    _desc = "This function generates a pie chart with a radius proportional to\nthe maximum of a single mineral concentration, but with every\nslice with an angle proportional to every mineral concentration.";
    _pardesc[1] = "Mineral mask";
    _pardesc[3] = "Full circle at conc.";
  }
  
  virtual void function(map_view& mw, planet* p, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = p->disp;

    // we can do something if we have the data
    if (!p->data_available())
      return;

    _mintype m;

    // range
    d.vmin = 0;
    d.vmax = (par[3])? par[3] : 150;

    m = p->min_conc(when);
    d.n_values = 0;

    if ( !((par[1]/100) & 1) ) {
      d.values[d.n_values].value = m.iron;
      d.values[d.n_values++].color = COL_IRON;
    }

    if ( !((par[1]/10) & 1) ) {
      d.values[d.n_values].value = m.bora;
      d.values[d.n_values++].color = COL_BORA;
    }

    if ( !(par[1] & 1) ) {
      d.values[d.n_values].value = m.germ;
      d.values[d.n_values++].color = COL_GERM;
    }

    d.flag = true;
  }
};

pla_mineral_conc pla_mineral_conc_proto;

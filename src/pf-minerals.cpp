#include "starana-classes.h"


// surface minerals display

class pla_surf_minerals : public planetary_function {
public:
  pla_surf_minerals(void)
  {
    _name = "Surface Minerals";
    _type = "Minerals";
    _desc = "This function generates a pie chart with a radius proportional to\nthe maximum of a single surface mineral, but with every slice with\nan angle proportional to every surface mineral.[4] amount for which the maximum radius is reached (0 -> 6000 kT)\n[5,6,7] use a non-zero value to hide the mineral.";
    _pardesc[4] = "Full circle at";
    _pardesc[5] = "Hide ironium";
    _pardesc[6] = "Hide boranium";
    _pardesc[7] = "Hide germanium";
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
    d.vmax = (par[4])? par[4] : 6000;

    m = p->minerals(when);
    d.n_values = 0;

    if (!par[5]) {
      d.values[d.n_values].value = m.iron;
      d.values[d.n_values++].color = COL_IRON;
    }

    if (!par[6]) {
      d.values[d.n_values].value = m.bora;
      d.values[d.n_values++].color = COL_BORA;
    }

    if (!par[7]) {
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
    _desc = "This function generates a pie chart with a radius proportional to\nthe maximum of a single mining rate, but with every slice with an\nangle proportional to every mineral mining rate.[4] amount for which the maximum radius is reached (0 -> 1000 kT)\n[5,6,7] use a non-zero value to hide the mineral.";
    _pardesc[4] = "Full circle at";
    _pardesc[5] = "Hide ironium";
    _pardesc[6] = "Hide boranium";
    _pardesc[7] = "Hide germanium";
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
    d.vmax = (par[4])? par[4] : 1000;

    m = p->mining_rate(when);
    d.n_values = 0;

    if (!par[5]) {
      d.values[d.n_values].value = m.iron;
      d.values[d.n_values++].color = COL_IRON;
    }

    if (!par[6]) {
      d.values[d.n_values].value = m.bora;
      d.values[d.n_values++].color = COL_BORA;
    }

    if (!par[7]) {
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
    _desc = "This function generates a pie chart with a radius proportional to\nthe maximum of a single mineral concentration, but with every\nslice with an angle proportional to every mineral concentration.[4] amount for which the maximum radius is reached (0 -> 120 kT)\n[5,6,7] use a non-zero value to hide the mineral.";
    _pardesc[4] = "Full circle at";
    _pardesc[5] = "Hide ironium";
    _pardesc[6] = "Hide boranium";
    _pardesc[7] = "Hide germanium";
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
    d.vmax = (par[4])? par[4] : 150;

    m = p->min_conc(when);
    d.n_values = 0;

    if (!par[5]) {
      d.values[d.n_values].value = m.iron;
      d.values[d.n_values++].color = COL_IRON;
    }

    if (!par[6]) {
      d.values[d.n_values].value = m.bora;
      d.values[d.n_values++].color = COL_BORA;
    }

    if (!par[7]) {
      d.values[d.n_values].value = m.germ;
      d.values[d.n_values++].color = COL_GERM;
    }

    d.flag = true;
  }
};

pla_mineral_conc pla_mineral_conc_proto;


// mineral shortage display

class pla_min_shortage : public planetary_function {
public:
  pla_min_shortage(void)
  {
    _name = "Mineral Shortage";
    _type = "Minerals";
    _desc = "This function generates a pie chart similat to that of surface,\nbut indicating the mineral shortages for the current year (as obtained\nfrom the production queue requirements).\n[4] amount for which the maximum radius is reached (0 -> 200 kT)\n[5,6,7] use a non-zero value to hide the mineral.";
    _pardesc[4] = "Full circle at";
    _pardesc[5] = "Hide ironium";
    _pardesc[6] = "Hide boranium";
    _pardesc[7] = "Hide germanium";
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
    d.vmax = (par[4])? par[4] : 200;

    m = p->minshortage(when);
    d.n_values = 0;

    if (!par[5]) {
      d.values[d.n_values].value = m.iron;
      d.values[d.n_values++].color = COL_IRON;
    }

    if (!par[6]) {
      d.values[d.n_values].value = m.bora;
      d.values[d.n_values++].color = COL_BORA;
    }

    if (!par[7]) {
      d.values[d.n_values].value = m.germ;
      d.values[d.n_values++].color = COL_GERM;
    }

    d.flag = true;
  }
};

pla_min_shortage pla_min_shortage_proto;


// filter on surface minerals

class pla_F_surfminkill : public planetary_function {
public:
  pla_F_surfminkill(void)
  {
    _name = "Filter: germanium";
    _type = "Minerals";
    _desc = "Filters planets depending on their surface mineral availability.\n[3..8] use min=0 max=0 to ignore the mineral.";
    _pardesc[1] = "Fields affect mask";
    _pardesc[2] = "Negate filter";
    _pardesc[3] = "Min ironium";
    _pardesc[4] = "Max ironium";
    _pardesc[5] = "Min boranium";
    _pardesc[6] = "Max boranium";
    _pardesc[7] = "Min germanium";
    _pardesc[8] = "Max germanium";
  }

  virtual void function(map_view& mw, planet* p, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = p->disp;

    int nf = 0;

    // we can do something if we have the data
    if (p->data_available()) {
      int i;

      for (i = 0; i < 3; i++)
	if (par[3+i*2] != 0 && par[4+i*2] != 0) {
	  int val = p->minerals(when)[i];

          if ( (par[3+i*2] <= par[4+i*2] && val >= par[3+i*2] && val <= par[4+i*2]) ||
	    (par[3+i*2] > par[4+i*2] && (val >= par[3+i*2] || val <= par[4+i*2])) )
	    nf++;
	  else
            nf++;
	}
    }

    bool f = (nf == 3);

    if (par[2])
      f = !f;

    if (par[1]) {
      if (f)
	d.reset_something(par[1]);
    } else
      d.flag = f;
  }
};

pla_F_surfminkill pla_F_surfminkill_proto;

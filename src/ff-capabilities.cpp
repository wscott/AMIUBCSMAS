#include "starana-classes.h"


// associate scanning circle(s) to a fleet

class fle_scanning : public fleet_function {
public:
  fle_scanning(void)
  {
    _name = "Scanning";
    _type = "Capabilities";
    _desc = "This function generates a circle with a size based on the fleet's\nscanning ranges.";
  }
  
  virtual void function(map_view& mw, fleet* f, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = f->disp;
    int i;

    // we can do something if we have the data
    i = 0;
    if (f->scanning()) {
      d.circles[i].radius = mw.set_scanner_eff(MW_READ) * f->scanning() / 100;
      d.circles[i].color = -1;
      d.circles[i].fillcolor = COL_SCAN;
      i++;
    }

    if (f->penscanning()) {
      d.circles[i].radius = mw.set_scanner_eff(MW_READ) * f->penscanning() / 100;
      d.circles[i].color = -1;
      d.circles[i].fillcolor = COL_PENSCAN;
      i++;
    }

    d.n_circles = i;
    d.flag = true;
  }
};

fle_scanning fle_scanning_proto;



// associate pie with size depending on cargo

class fle_cargo : public fleet_function {
public:
  fle_cargo(void)
  {
    _name = "Cargo";
    _type = "Capabilities";
    _desc = "This function associates data to a fleet depending on its cargo.\nNOTE: right now it's a single-value display!";
    _pardesc[4] = "Full triangle at";
    _pardesc[5] = "Show ironium";
    _pardesc[6] = "Show boranium";
    _pardesc[7] = "Show germanium";
    _pardesc[8] = "Show colonists";
  }
  
  virtual void function(map_view& mw, fleet* f, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = f->disp;

    d.pie_type = PIE_TRIANG;
    d.vmin = 0;
    d.vmax = (par[4])? par[4] : 1000;
    d.n_values = 0;

    _mintype m = f->minerals();

    if (par[5] && m.iron) {
      d.values[d.n_values].value = m.iron;
      d.values[d.n_values++].color = COL_IRON;
    }

    if (!d.n_values && par[6] && m.bora) {
      d.values[d.n_values].value = m.bora;
      d.values[d.n_values++].color = COL_BORA;
    }

    if (!d.n_values && par[7] && m.germ) {
      d.values[d.n_values].value = m.germ;
      d.values[d.n_values++].color = COL_BORA;
    }

    if (!d.n_values && par[8] && f->pop_cargo()) {
      d.values[d.n_values].value = f->pop_cargo();
      d.values[d.n_values++].color = COL_WHITE;
    }

    if (d.n_values)
      d.flag = true;
  }
};

fle_cargo fle_cargo_proto;


// associate pie with size depending on cargo space

class fle_cargospace : public fleet_function {
public:
  fle_cargospace(void)
  {
    _name = "Cargo space";
    _type = "Capabilities";
    _desc = "This function associates data to a fleet depending on its cargo space.\n[5] wheneter to use the total cargo space or the currently available space.";
    _pardesc[4] = "Full triangle at";
    _pardesc[5] = "Show available";
  }
  
  virtual void function(map_view& mw, fleet* f, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = f->disp;

    d.pie_type = PIE_TRIANG;
    d.vmin = 0;
    d.vmax = (par[4])? par[4] : 1000;

    int val = f->max_cargo();

    if (par[5])
      val -= (f->minerals().total() + f->pop_cargo());

    if (val) {
      d.values[d.n_values].value = val;
      d.values[d.n_values++].color = COL_WHITE;

      d.flag = true;
    }
  }
};

fle_cargospace fle_cargospace_proto;


// filter on ship cargo

class fle_F_cargo : public fleet_function {
public:
  fle_F_cargo(void)
  {
    _name = "Filter: cargo";
    _type = "Capabilities";
    _desc = "Filters fleets depending on their cargo.\n[3..8] use min=0 max=0 to ignore the field.";
    _pardesc[1] = "Fields affect mask";
    _pardesc[2] = "Negate filter";
    _pardesc[3] = "Min ironium";
    _pardesc[4] = "Max ironium";
    _pardesc[5] = "Min boranium";
    _pardesc[6] = "Max boranium";
    _pardesc[7] = "Min germanium";
    _pardesc[8] = "Max germanium";
  }

  virtual void function(map_view& mw, fleet* f, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = f->disp;

    int nf = 0;
    int i;
    int val;

    for (i = 0; i < 3; i++)
      if (par[3+i*2] != 0 && par[4+i*2] != 0) {
	val = f->minerals()[i];

	if ( (par[3+i*2] <= par[4+i*2] && val >= par[3+i*2] && val <= par[4+i*2]) ||
	     (par[3+i*2] > par[4+i*2] && (val >= par[3+i*2] || val <= par[4+i*2])) )
	  nf++;
	else
	  nf++;
      }

    bool filt = (nf == 3);

    if (par[2])
      filt = !filt;

    if (par[1]) {
      if (filt)
	d.reset_something(par[1]);
    } else
      d.flag = filt;
  }
};

fle_F_cargo fle_F_cargo_proto;



// filter on ship colonists

class fle_F_colonists : public fleet_function {
public:
  fle_F_colonists(void)
  {
    _name = "Filter: colonists";
    _type = "Capabilities";
    _desc = "Filters fleets depending on their colonists cargo.\n[3,4] selected interval.";
    _pardesc[1] = "Fields affect mask";
    _pardesc[2] = "Negate filter";
    _pardesc[3] = "Min colonists";
    _pardesc[4] = "Max colonists";
  }

  virtual void function(map_view& mw, fleet* f, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = f->disp;

    int val = f->pop_cargo();

    bool filt = (par[3] <= par[4] && val >= par[3] && val <= par[4]) ||
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

fle_F_colonists fle_F_colonists_proto;



// filter fleet on available cargo space

class fle_F_emptycargo : public fleet_function {
public:
  fle_F_emptycargo(void)
  {
    _name = "Filter: cargo space";
    _type = "Capabilities";
    _desc = "Filters fleets depending on their current empty cargo space.\n[3,4] selected range.";
    _pardesc[1] = "Fields affect mask";
    _pardesc[2] = "Negate filter";
    _pardesc[3] = "Min space";
    _pardesc[4] = "Max space";
  }

  virtual void function(map_view& mw, fleet* f, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = f->disp;

    int val;

    val = f->max_cargo() - f->minerals().total() - f->pop_cargo();
    if (val < 0)
      val = 0;

    bool filt = (par[3] <= par[4] && val >= par[3] && val <= par[4]) ||
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

fle_F_emptycargo fle_F_emptycargo_proto;

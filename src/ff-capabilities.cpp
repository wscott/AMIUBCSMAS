#include "starana-classes.h"


// associate a marker to a fleet

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

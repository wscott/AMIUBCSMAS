#include "starana-classes.h"



// origin function: add a line from fleet to its origin

class fle_lineorigin : public fleet_function {
public:
  fle_lineorigin(void)
  {
    _name = "Destination";
    _type = "Movement";
    _desc = "This function adds a line which indicates where the fleet is going.";
  }

  virtual void function(map_view& mw, fleet* f, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = f->disp;

    // direction vector
    if (when <= f->ETA() && f->warp()) {
      d.linedest[d.n_lines].dp = mw.map_to_display(f->position(mw.get_map()->sim_future()));
      d.linedest[d.n_lines].color = COL_GREY + 1;

      if (f->warp() <= 10) {
	d.linedest[d.n_lines].first_tick = d.linedest[d.n_lines].tick_sep = f->warp()*f->warp();
	d.linedest[d.n_lines].tickdev = 3;
      } else {
	d.linedest[d.n_lines].first_tick = d.linedest[d.n_lines].tick_sep = 0;
	// change default color to indicate gating
	d.linedest[d.n_lines].color = COL_YELLOWHAB + 1;
      }
      
      d.flag = true;
      d.n_lines++;
    }
  }
};

fle_lineorigin fle_lineorigin_proto;


// destination function: add a line from fleet to its destination

class fle_linedestination : public fleet_function {
public:
  fle_linedestination(void)
  {
    _name = "Origin";
    _type = "Movement";
    _desc = "This function adds a line which indicates where the fleet is coming from.";
  }

  virtual void function(map_view& mw, fleet* f, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = f->disp;

    // inverse direction vector
    if (f->position(1) != f->position(0)) {
      // it is really moving, draw 300 ly in the past (should use _origin????)
      _xypoint rp = f->position(0) + f->position(0) - f->position(mw.get_map()->sim_future());
      d.linedest[d.n_lines].dp = mw.map_to_display(rp);
      d.linedest[d.n_lines].color = COL_GREY + 1;

      if (f->warp() <= 10) {
	d.linedest[d.n_lines].first_tick = d.linedest[d.n_lines].tick_sep = f->warp()*f->warp();
	d.linedest[d.n_lines].tickdev = -3;
      } else {
	d.linedest[d.n_lines].first_tick = d.linedest[d.n_lines].tick_sep = 0;
	// change default color to indicate gating
	d.linedest[d.n_lines].color = COL_YELLOWHAB + 1;
      }

      d.flag = true;
      d.n_lines++;
    }
  }
};

fle_linedestination fle_linedestination_proto;


// this function sets the color of the line

class fle_linecolor : public fleet_function {
public:
  fle_linecolor(void)
  {
    _name = "Line: color";
    _type = "Movement";
    _desc = "This function sets the color of a line associated to a fleet.\n[0] specify the color number or 0 to indicate the color of the owner.";
    _pardesc[0] = "Color";
  }

  virtual void function(map_view& mw, fleet* f, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = f->disp;

    // do we have a line?
    if (d.n_lines) {
      if (par[0] > 0 && par[0] <= 24)
	d.linedest[d.n_lines-1].color = COL_WHITE + 4 * (par[0] - 1);
      else
	d.linedest[d.n_lines-1].color = COL_RACES + 4 * f->owner()->race_id();
    }
  }
};

fle_linecolor fle_linecolor_proto;


// kill on destination planet

class fle_F_destinkill : public fleet_function {
  int sel_pla_id;
  planet* sel_pla;

public:
  fle_F_destinkill(void) : sel_pla_id(-1), sel_pla(NULL)
  {
    _name = "Filter: destination";
    _type = "Movement";
    _desc = "Filter fleets whose destination is the specified planet.\n[0] specify id 0 for any planet or -1/-2 to indicate the 1st or 2nd selected.\n[3] specify 0 to ignore, 1 to filter only friendly fleets, 2 for enemy fleets\n";
    _pardesc[0] = "Planet ID";
    _pardesc[1] = "Fields affect mask";
    _pardesc[2] = "Negate filter";
    _pardesc[3] = "Friend";
  }
  
  virtual void function(map_view& mw, fleet* f, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = f->disp;

    bool filt = false;

    // any planet or one in particular?
    if (par[0] == 0)
      filt = (f->destination() != NULL);

    else {
      // find planet
      int pid = ((par[0]>0)? par[0] : mw.get_active_planet(-par[0]-1)->starsid());

      if (pid != sel_pla_id) {
	if (par[0] > 0)
	  sel_pla = mw.get_map()->find_planet(par[0]);
	else
	  sel_pla = mw.get_active_planet(-par[0]-1);

	if (!sel_pla)
	  return; // abort without doing anything

	sel_pla_id = pid;
      }

      filt = (f->destination() == sel_pla);
    }

    // handle the "friend" field:
    // if planet has no owner we ALWAYS filter out
    if (par[3] && filt) // only care if we are filtering
      if (f->destination()->owner()) {
	if (par[3] == 1 && !mw.get_map()->are_allies(f->owner(), f->destination()->owner()))
	  filt = false;
	else if (mw.get_map()->are_allies(f->owner(), f->destination()->owner()))
	  filt = false;
      } else
	filt = false;

    if (par[2])
      filt = !filt;
    
    if (par[1]) {
      if (filt)
	d.reset_something(par[1]);
    } else
      d.flag = filt;
  }
};

fle_F_destinkill fle_F_destinkill_proto;


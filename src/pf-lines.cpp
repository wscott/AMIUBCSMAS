#include "starana-classes.h"


// associate a line corresponding to the routing

class pla_routing : public planetary_function {
public:
  pla_routing(void)
  {
    _name = "Routing";
    _type = "Lines";
    _desc = "This function adds a line from the planet to its routing destination.";
  }
  
  virtual void function(map_view& mw, planet* p, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = p->disp;

    if (p->owner() && p->routing_dest()) {
      d.linedest[d.n_lines].color = COL_GREY;
      d.linedest[d.n_lines].dp = mw.map_to_display(p->routing_dest()->position());
      d.linedest[d.n_lines].first_tick = 10;
      d.linedest[d.n_lines].tick_sep = 100;
      d.linedest[d.n_lines].tickdev = 3;

      d.n_lines++;
      d.flag = true;
    }
  }
};

pla_routing pla_routing_proto;



// associate a line corresponding to the packet driver destination

class pla_packets : public planetary_function {
public:
  pla_packets(void)
  {
    _name = "Mass Driver";
    _type = "Lines";
    _desc = "This function adds a line from the planet to its mass driver destination.\nBy default the line will turn red if the destination planet is unable to safely catch the packet.";
  }
  
  virtual void function(map_view& mw, planet* p, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = p->disp;

    if (p->owner()) {
      int warp = p->driver_warp();

      if (warp && p->driver_destination()) {
	d.linedest[d.n_lines].dp = mw.map_to_display(p->driver_destination()->position());

	if (warp > p->driver_destination()->driver_warp())
	  d.linedest[d.n_lines].color = COL_REDHAB;
	else
	  d.linedest[d.n_lines].color = COL_RACES + 5 * 4 + 1;

	d.linedest[d.n_lines].first_tick = warp*warp / 2;
	d.linedest[d.n_lines].tick_sep = warp*warp;
	d.linedest[d.n_lines].tickdev = 3;

	d.n_lines++;
	d.flag = true;
      }
    }
  }
};

pla_packets pla_packets_proto;



// this function sets the color of the line

class pla_linecolor : public planetary_function {
public:
  pla_linecolor(void)
  {
    _name = "Line: color";
    _type = "Lines";
    _desc = "This function sets the color of a line associated to a planet.\n[0] specify the color number or 0 to indicate the color of the owner.";
    _pardesc[0] = "Color";
  }

  virtual void function(map_view& mw, planet* p, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = p->disp;

    // do we have a line?
    if (d.n_lines) {
      if (par[0] > 0 && par[0] <= 24)
	d.linedest[d.n_lines-1].color = COL_WHITE + 4 * (par[0] - 1);
      else if (p->data_available() && p->owner())
	d.linedest[d.n_lines-1].color = COL_RACES + 4 * p->owner()->race_id();
    }
  }
};

pla_linecolor pla_linecolor_proto;

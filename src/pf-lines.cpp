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
    _desc = "This function adds a line from the planet to its mass driver destination. By default line will turn red if the destination planet is unable to safely catch the packet.";
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

	d.n_lines++;
	d.flag = true;
      }
    }
  }
};

pla_packets pla_packets_proto;

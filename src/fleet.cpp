#include "starana-classes.h"

#include <ctype.h>



fleet::fleet(const myString& n) : _starsname(n),
         _name(), _owner(NULL), enemy(true), stars_id(-1),
         _destin(NULL), _warp(0), eta(-1), starsETA(-1),
         _mass(-1), _pop(0), _fuel(0), _maxfuel(0),
         scan_normal(0), scan_pen(0), _cloaking(0), _minelaying(0), _minesweeping(0),
         _terraforming(0), _remote_mining(0)

{
  int i;

  for (i = 0; i < SIM_FUTURE; i++) {
    pos[i].x = 0;
    pos[i].y = 0;
    _orbit[i] = NULL;
  }

  // mark as "unknown"
  pos[1].x = -1000;
  pos[1].y = -1000;

  for (i = 0; i < 6; i++)
    numships[i] = 0;

  for (i = 0; i < 16; i++) {
    des[i] = NULL;
    ndes[i] = 0;
  }
}


fleet::~fleet(void)
{

}


int fleet::unload_pop(void)
{
  int up = _pop;
  //  pop = 0;  // we don't really clear this to allow totals to work

  return up;
}


_mintype fleet::unload_min(void)
{
  _mintype um(_min);
  //  min.clear(); // same as pop

  return um;
}


void fleet::check_data(void)
{
  // we have in pos[0] the current position and in pos[1] the
  // waypoint 1 position, or -1000,-1000 (if dest unknown), or (dx, dy)
  // destin will be pointing to the destination planet (if any)

  // for "orbiting" we use the source position given in gram.y
  // spread on all years if fleet is not moving. Otherwise we
  // leave NULLs until we hit the destination

  char destmsg[256];
  _xypoint xydest;
  _xypoint dxy;
  bool deltas = false;
  int y;
  myString msg;

  // parse fleet name, carefully looking for composition
  // we have several cases:
  //   a single design (this is easy :)
  //   multiple designs in enemy fleet (no way to find composition)
  //   multiple designs in friendly fleet
  //     try to parse the name and find the composition, check against ship # and mass

  // for simplicity we DON'T parse enemy fleets in any case, to prevent filters
  // from misleading user by working correctly on single-ship fleets but not on
  // others

  if (!enemy) {
    int designs = 0;
    design* d;
    myString cname;

    // check for fleet aliasing
    cname = find_fleet_alias(_starsname);

    if (cname == _starsname) {
      cname = _name;
      _owner->add_message(RLO_FLEETPARSE, "Trying to parse: '" + _starsname + "'");
    } else    
      _owner->add_message(RLO_FLEETPARSE, "Trying to parse: '" + cname +
			   "' (alias of " + _starsname + ")");

    // check for single design
    if ( (d = _owner->find_design(cname)) ) {
      des[designs] = d;
      ndes[designs] = numships[F_TOTAL];
      designs++;

      _owner->add_message(RLO_FLEETPARSE, "  found single design " + d->o()->name());

    } else {
      // try to parse
      char dnam[64], quan[64];
      char* np;
      int q;
      char* qp;
      char* qep;
      const char* p = cname.chars();

      while (*p) {
        np = dnam;
	qp = quan;

	// skip whitespace
	while (*p && isspace(*p))
	  p++;
	if (!*p)
	  break; // over

	// name.....
	while (*p && !isdigit(*p))
	  *np++ = *p++;
	*np = 0;

	// ....and quantity
	while (*p && isdigit(*p))
	  *qp++ = *p++;
	*qp = 0;

	if (!dnam[0] || !quan[0]) {
	  _owner->add_message(RLO_FLEETPARSE, _starsname + ": unable to determine design/quantity!");
	  break;
	}

	q = strtol(quan, &qep, 10);
	_owner->add_message(RLO_FLEETPARSE, "  found " + int_to_str(q) + " of " + dnam);

	if ( !(d = _owner->find_design_alias(dnam)) ) {
	  _owner->add_message(RLO_ERROR, cname + ": '" + dnam + 
			     "' is a either unknown or ambiguous design!");
	  break;
	}

	if (q == 0 || qep == quan) {
	  _owner->add_message(RLO_FLEETPARSE, cname + ": unable to decode quantity '" + quan + "'!");
	  break;
	}
	_owner->add_message(RLO_FLEETPARSE, "  adding " + int_to_str(q) + " of " + d->o()->name());

	// add a design to the fleet
	des[designs] = d;
	ndes[designs] = q;
	designs++;
      }
    }

    if (designs) {
      // check ship # / mass consistency
      int nship = 0, emass = 0;

      for (y = 0; y < designs; y++) {
	nship += ndes[y];
	emass += ndes[y] * des[y]->mass;
      }

      // don't forget cargo!
      emass += _pop;
      emass += _min.total();

      if (nship != numships[F_TOTAL]) {
	if (cname == _name)
	  msg = _starsname + ": total number of ships inconsistent with fleet name!";
	else
	  msg = _starsname + "(" + cname + "): total number of ships inconsistent with fleet name!";

	_owner->add_message(RLO_FLEETCONS, msg);
      }

      if (emass != _mass) {
	if (cname == _name)
	  msg = _starsname + ": fleet mass inconsistent with fleet composition!";
	else
	  msg = _starsname + "(" + cname + "): fleet mass inconsistent with fleet composition!";

	_owner->add_message(RLO_FLEETCONS, msg);
      }

    } else
      _owner->add_message(RLO_ERROR, _starsname + ": unable to decode fleet composition!");
  }
  // analyze destination, movement, etc.

  if (_destin)
    xydest = _destin->position();
  else if (pos[1] == _xypoint(-1000,-1000)) {
    xydest = pos[0]; // assume stationary fleet

    if (_warp != 0)
      _owner->add_message(RLO_FLEETDEST, _starsname + ": fleet has no destination but warp != 0!!!!");

  } else if (pos[1].x < 300) { // this means we have deltas (maybe)
    deltas = true;

    // stars paranoia! if warp == 0 then deltas must be ignored
    if (!_warp)
      xydest = pos[0];
    else {
      xydest = pos[0] + pos[1];

      // try to guess fleet's destination planet
      if (find_possible_destination()) {
	_owner->add_message(RLO_FLEETDEST, 
			    _starsname + ": guessed destination is " + _destin->name());

	xydest = _destin->position(); // override xydest
	deltas = false; // no deltas
      }
    }

  } else
    xydest = pos[1];

  // we have pos & xydest set, if we are not orbiting a world we can try to
  // determine where the fleet comes from
  if (!_origin)
    if (find_possible_origin(xydest))
      _owner->add_message(RLO_FLEETDEST, _starsname +" guessed origin is " + _origin->name());

  // estimate eta (if we are moving)
  if ( xydest != pos[0] ) {
    if (!_warp) {
	//      fprintf(of, "%s fleet is stopped (from %d,%d to %d,%d)\n", (const char*)_starsname, pos[0].x, pos[0].y, xydest.x, xydest.y);

      _owner->add_message(RLO_FLEETDEST, _starsname + " fleet is stopped (with a destination)!!");

      eta = SIM_FUTURE+1;
      
    } else if (deltas) {
      // we have deltas, set ETA to infinite
      eta = SIM_FUTURE + 1;

    } else {
      // eta calculation is meaningful if we have a REAL destination
      
      // are we jumping through a gate?
      if (_warp == 11) {
	// check gate limits/cargo/etc.
	eta = 1;

      } else {
	dxy = xydest - pos[0];
	eta = (1 + (int)sqrt(dxy.x*dxy.x + dxy.y*dxy.y)) / (_warp * _warp) + 1;

	// consistency check with Stars! ETA
	if (starsETA != -1 && eta != starsETA)
	  _owner->add_message(RLO_ERROR, "Fleet " + _starsname + " ETA inconsistency! Starana " +
			      int_to_str(eta) + ", Stars! " + int_to_str(starsETA) + "....");
      }

      if (_destin)
	sprintf(destmsg, "Fleet %s will arrive at %s in %d years", 
		(const char*)_starsname, (const char*)_destin->name(), eta);
    }

    // if destination is a planet some more checks are needed
    if (_destin) {
      if (_destin->owner()) {
	if (_destin->owner() == _owner) {
	  if (_min.total() != 0 || _pop != 0) {
	    _owner->add_message(RLO_FLEETTROK, myString(destmsg) + " and unload all cargo");

	    // add fleet to planet's array
	    _destin->add_fleet(this);
	  } else if (_maxcargo != 0)
	    _owner->add_message(RLO_FLEETTROK, myString(destmsg) + ", ready to pick up stuff");

	} else {
	  if (game_map->are_allies(_owner, _destin->owner()))
	    _owner->add_message(RLO_FLEETTROK, myString(destmsg) + " (allied world)");

	  else
	    _owner->add_message(RLO_FLEETATTK, myString(destmsg) + " (ENEMY world)");
	}
      } else {
	if (_maxcargo != 0)
	  msg = myString(destmsg) + " (unihnabited, colonize?)";
	else
	  msg = myString(destmsg) + " (unihnabited)";
	
	_owner->add_message(RLO_FLEETCOLON, msg);
      }
    } else if (!deltas) {
      // fleet aims for deep space
      if (_min.total() != 0 || _pop != 0)
	_owner->add_message(RLO_FLEETTRBAD, "Fleet " + _starsname +
			    " is going to deep space (but it has cargo!!)");
    }

    // fun part: calculate the fleet position at all years
    // vector of motion, renormalized
    dxy = xydest - pos[0];
    dxy = dxy * (_warp*_warp) / (int)sqrt(dxy.x*dxy.x + dxy.y*dxy.y);

    //    fprintf(of, "Fleet %s going from %d,%d to %d,%d at warp %d, deltas %d,%d\n", 
    //	    (const char*)_starsname, pos[0].x, pos[0].y, xydest.x, xydest.y, _warp,
    //	    dxy.x, dxy.y);

    for (y = 1; y <= game_map->sim_future(); y++)
      if (y >= eta) { // arrived at destination
	pos[y] = xydest;
	if (_destin) // if destination is a world then set _orbit
	  _orbit[y] = _destin;
      } else
	// flying fleet: calculate position
	pos[y] = pos[0] + dxy * y;

  } else {
    // fleet is standing still
    if (_min.total() != 0 || _pop != 0) {
      // standing still/going to non-planet with load
      if (_warp == 0)
	msg = "Fleet " + _starsname + " is standing still (but it has cargo)!!";
      else
	msg = "Fleet " + _starsname + " is NOT going to a planet (but it has cargo)!!";

      _owner->add_message(RLO_FLEETTRBAD, msg);
    }

    for (y = 1; y <= game_map->sim_future(); y++) {
      pos[y] = pos[0];
      _orbit[y] = _orbit[0];
    }
  }

  // do a report
  /* if (_destin)
    fprintf(of, "Fleet %s: destination is %s\n", _starsname.chars(), _destin->name().chars());

  if (scan_normal)
    fprintf(of, "Fleet %s has a scanning of %d %d\n", _starsname.chars(),
	    scan_normal, scan_pen);  

  for (y = 1; y < game_map->sim_future(); y++)
    fprintf(of, "Fleet %s: position in year %d is (%d,%d)\n", _starsname.chars(),
	    y, pos[y].x, pos[y].y); */
}


// for a fleet with pos & deltas, try to find a destination planet

bool fleet::find_possible_destination(void)
{
  // check for movement vector or destination
  if (_destin || (pos[1].x == 0 && pos[1].y == 0) )
    return false;

  planet* p = game_map->find_planet(pos[0], pos[1]);

  if (!p)
    return false;

  // do a sanity check on TIME required to get there
  _xypoint dxy = p->position() - pos[0];
  int eta = (1 + (int)sqrt(dxy.x*dxy.x + dxy.y*dxy.y)) / (_warp * _warp) + 1;
	
  if (eta > game_map->sim_future())
    return false;

  _destin = p;
  return true;
}


// for a fleet with pos & destination, try to find a source planet

bool fleet::find_possible_origin(const _xypoint& dest)
{
  // the idea is to use find_planet(_xypoint, _xypoint) by generating
  // a fake "destination" which is symmetrical to the fleet
  if (!_origin) {
    _xypoint fakedest(pos[0] - (dest - pos[0]));

    planet* p = game_map->find_planet(pos[0], fakedest);

    if (p)
      _origin = p;

    return (p != NULL);
  }

  return false;
}


// fleet name aliasing management

struct fleetalias {
  fleetalias* next;
  myString fleetname;
  myString alias;
};

fleetalias* fleet_alias_table = NULL;

bool add_fleet_alias(const myString& n, const myString& a)
{
  if (n == a) // paranoia check
    return false;

  if (n == find_fleet_alias(n)) {
    fleetalias* fa = new fleetalias;
    fa->fleetname = n;
    fa->alias = a;
    fa->next = fleet_alias_table;
    fleet_alias_table = fa;

    return true;

  } else
    return false;
}



// find alias: if not found returns n

const myString& find_fleet_alias(const myString& n)
{
  fleetalias* fa;

  for (fa = fleet_alias_table; fa; fa = fa->next)
    if (fa->fleetname == n)
      return fa->alias;

  return n;
}

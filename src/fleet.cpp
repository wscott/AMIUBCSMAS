#include "starana-classes.h"



fleet::fleet(const String& n) : _starsname(n), _name(), _owner(NULL), stars_id(-1),
         destin(NULL), warp(0), eta(-1), starsETA(-1),
         n_ships(0), n_unarmed(0), n_scout(0), n_warship(0), n_utility(0), n_bomber(0),
	 mass(-1), pop(0), fuel(0),
         scan_normal(0), scan_pen(0), cloaking(0), minelaying(0), minesweeping(0),
         terraforming(0), remote_mining(0)

{
  int i;

  for (i = 0; i < SIM_FUTURE; i++) {
    pos[i].x = 0;
    pos[i].y = 0;
  }

  // mark as "unknown"
  pos[1].x = -1000;
  pos[1].y = -1000;
}


fleet::~fleet(void)
{

}


int fleet::unload_pop(void)
{
  int up = pop;
  //  pop = 0;  // we don't really clear this to allow totals to work

  return up;
}


_mintype fleet::unload_min(void)
{
  _mintype um(min);
  //  min.clear(); // same as pop

  return um;
}


void fleet::check_data(FILE* of)
{
  // we have in pos[0] the current position and in pos[1] the
  // waypoint 1 position, or -1000,-1000 (if dest unknown), or (dx, dy)
  // destin will be pointing to the destination planet (if any)

  _xypoint xydest;
  _xypoint dxy;
  bool deltas = false;
  int y;
  
  if (destin)
    xydest = destin->position();
  else if (pos[1] == _xypoint(-1000,-1000)) {
    xydest = pos[0]; // assume stationary fleet

    if (warp != 0)
      fprintf(of, "%s fleet has no destination but warp != 0!!!!\n", (const char*)_starsname);

  } else if (pos[1].x < 300) { // this means we have deltas (maybe)
    deltas = true;

    // stars paranoia! if warp == 0 then deltas must be ignored
    if (!warp)
      xydest = pos[0];
    else
      xydest = pos[0] + pos[1];

  } else
    xydest = pos[1];

  // estimate eta (if we are moving)
  if ( xydest != pos[0] ) {
    if (!warp) {
      fprintf(of, "%s fleet is stopped (with a destination)!!!!\n", (const char*)_starsname);
      //      fprintf(of, "%s fleet is stopped (from %d,%d to %d,%d)\n", (const char*)_starsname, pos[0].x, pos[0].y, xydest.x, xydest.y);
      eta = SIM_FUTURE+1;

    } else if (deltas) {
      // we have deltas, set ETA to infinite
      eta = SIM_FUTURE + 1;

    } else {
      // eta calculation is meaningful if we have a REAL destination
      
      // are we jumping through a gate?
      if (warp == 11) {
	// check gate limits/cargo/etc.
	eta = 1;

      } else {
	dxy = xydest - pos[0];
	eta = (1 + (int)sqrt(dxy.x*dxy.x + dxy.y*dxy.y)) / (warp * warp) + 1;

	// consistency check with Stars! ETA
	if (starsETA != -1 && eta != starsETA)
	  fprintf(of, "Fleet %s ETA inconsistency! Starana %d, Stars! %d....\n", 
		  (const char*)_starsname, eta, starsETA);
      }

      if (destin)
	fprintf(of, "Fleet %s will arrive at %s in %d years", 
		(const char*)_starsname, (const char*)destin->name(), eta);
    }

    // if destination is a planet some more checks are needed
    if (destin) {
      if (destin->owner()) {
	if (destin->owner() == _owner)
	  if (min.total() != 0 || pop != 0) {
	    fprintf(of, " and unload all cargo\n");

	    // add fleet to planet's array
	    destin->add_fleet(this);
	  } else
	    fprintf(of, ", ready to pick up stuff\n");
	else
	  fprintf(of, ", is he a friend?\n");
      } else
	fprintf(of, " and wait (colonize?)\n");

    } else if (!deltas) {
      // fleet aims for deep space
      if (min.total() != 0 || pop != 0)
	fprintf(of, "Fleet %s is going to deep space (but it has cargo)\n", 
		(const char*)_starsname);
    }

    // fun part: calculate the fleet position at all years
    // vector of motion, renormalized
    dxy = xydest - pos[0];
    dxy = dxy * (warp*warp) / (int)sqrt(dxy.x*dxy.x + dxy.y*dxy.y);

    fprintf(of, "Fleet %s going from %d,%d to %d,%d at warp %d, deltas %d,%d\n", 
	    (const char*)_starsname, pos[0].x, pos[0].y, xydest.x, xydest.y, warp,
	    dxy.x, dxy.y);

    for (y = 1; y <= game_map->sim_future(); y++)
      if (y >= eta) // arrived at destination
	pos[y] = xydest;
      else
	// flying fleet: calculate position
	pos[y] = pos[0] + dxy * y;

  } else {
    // fleet is standing still
    if (min.total() != 0 || pop != 0) // standing still with load
      fprintf(of, "Fleet %s is standing still (but it has cargo)\n", 
	      (const char*)_starsname);

    for (y = 1; y <= game_map->sim_future(); y++)
      pos[y] = pos[0];
  }

  // do a report
  /* if (destin)
    fprintf(of, "Fleet %s: destination is %s\n", _starsname.chars(), destin->name().chars());

  if (scan_normal)
    fprintf(of, "Fleet %s has a scanning of %d %d\n", _starsname.chars(),
	    scan_normal, scan_pen);  

  for (y = 1; y < game_map->sim_future(); y++)
    fprintf(of, "Fleet %s: position in year %d is (%d,%d)\n", _starsname.chars(),
	    y, pos[y].x, pos[y].y); */
}

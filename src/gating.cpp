void graphics::gatestarships(void)
{
  // fetch values from form
  
  if (distance > 5*maxSrange || mass > 5*maxSmass || mass > 5*maxDmass) {
    // all ships destroyed
    damage = -1;
    shiplost = nships;
  
  } else {
    damage = 0;
    if (distance > maxSrange)
      damage += 100 * (distance - maxSrange) / (4 * maxSrange);

    if (mass > maxSmass || mass > maxDmass)
      damage += 100 * (1.0 - (5*maxSmass - mass) / (4 * maxSmass) *
		       (5*maxDmass - mass) / (4 * maxDmass));
  }
}

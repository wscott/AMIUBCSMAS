#include "starana-classes.h"



int wfunc_160(const int r)
{
  if (r > 160)
    return 0;

  if (r == 0)
    return 100000;

  int v = 99383 / (r + 1) - 617;

  if (v < 0)
    return 0;
  
  return v;
}


int wfunc_200(const int r)
{
  if (r > 200)
    return 0;

  if (r == 0)
    return 100000;

  int v = 198039 / (r + 2) - 980;

  if (v < 0)
    return 0;
  
  return v;
}


int wfunc_250(const int r)
{
  if (r > 250)
    return 0;

  if (r == 0)
    return 100000;

  int v = 296484 / (r + 3) - 1171;

  if (v < 0)
    return 0;

  return v;
}

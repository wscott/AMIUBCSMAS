#include "myString.h"


int main(void)
{
  myString dest = "Space (1234, 1235)";
  vector<myString> dt;
  if (dest.matches(myRegexp("Space \\([0-9]+, [0-9]+\\)")))
    puts("MATCH!");
  else
    puts("no match");

  /*
    dt = dest.at(8).split(myString("."), 2);
    t = int_to_str(atoi(dt[0])) + " " + int_to_str(atoi(dt[1]));
    PRINT("destination", t);
  }
  */




}

#include "myString.h"

#include <stdio.h>


vector<TmyString> myString::split(const myString& sep, int max = 0)
{
  size_type pos = 0;
  size_type p;
  vector<TmyString> res;

  while (1) {
    p = s.find(sep, pos);

    if (p == string::npos) {
      res.push_back(s.substr(pos, string::npos));
      break;

    } else if (p == pos) {
      // we add a null
      res.push_back("");

    } else {
      // we add the string from pos to p-1
      res.push_back(s.substr(pos, p-1-pos));
    }

    // move pos forward (to end of match)
    pos = p + sep.length();
    if (max)
      if ( !(--max) )
	break; // we reached limit
  }

  return res;
}


vector<TmyString> myString::split(const myRegexp& sep, int max = 0)
{
  size_type pos = 0;
  vector<TmyString> res;
  int b, e;

  while (1) {
    if (sep.match(*this, pos)) {
      // we had match, so reg0 will be good
      sep.match_pos(0, &b, &e);

      if (pos == (size_type)b) {
	// we add a null
	res.push_back("");

      } else {
	// we add the string from pos to b-1
	res.push_back(s.substr(pos, b-pos));
      }

      pos = e;

    } else {
      res.push_back(s.substr(pos, string::npos));
      break;
    }

    if (max)
      if ( !(--max) )
	break; // we reached limit
  }

  return res;
}



myRegexp::myRegexp(const char* s) : nmatches(-1)
{
  int e;

  if ( (e = regcomp(&rxbuffer, s, REG_EXTENDED)) ) {
    char err[256];
    regerror(e, &rxbuffer, err, 256);
    fprintf(stderr, "REGEX ERROR: %s\n", err);
    exit(-1);
  }
}


myRegexp::~myRegexp(void)
{
  regfree(&rxbuffer);
}


bool myRegexp::match(const char* s, myString::size_type pos = 0) const
{
  int state;
  nmatches = -1;
  matched_string = s;

  if (pos)
    if (pos < strlen(s)) {
      state = regexec(&rxbuffer, s+pos, MAX_REGEXP_MATCHES, rxmatchpos, 0);

      if (!state) {
	// adjust positions
	for (nmatches = 0; 
	     nmatches < MAX_REGEXP_MATCHES && rxmatchpos[nmatches].rm_so != -1; 
	     nmatches++) {
	  rxmatchpos[nmatches].rm_so += pos;
	  rxmatchpos[nmatches].rm_eo += pos;
	}
      }
    } else
      return false;
  
  else {
    state = regexec(&rxbuffer, s, MAX_REGEXP_MATCHES, rxmatchpos, 0);

    // count matches
    for (nmatches = 0; 
	 nmatches < MAX_REGEXP_MATCHES && rxmatchpos[nmatches].rm_so != -1; 
	 nmatches++);
  }

  if (state == REG_NOMATCH)
    return false;
   
  return true;
}


bool myRegexp::match_pos(const int i, int* begin, int* end) const
{
  if (i < nmatches && rxmatchpos[i].rm_so != -1) {
    *begin = rxmatchpos[i].rm_so;
    *end = rxmatchpos[i].rm_eo;
    return true;

  } else
    return false;
}



const myRegexp myRegexp::RXwhite("[ \n\t\r\v\f]+");
const myRegexp myRegexp::RXint("-?[0-9]+");
const myRegexp myRegexp::RXdouble("-?\\(\\([0-9]+\\.[0-9]*\\)\\|\\([0-9]+\\)\\|\\(\\.[0-9]+\\)\\)\\([eE][---+]?[0-9]+\\)?");
const myRegexp myRegexp::RXalpha("[A-Za-z]+");
const myRegexp myRegexp::RXlowercase("[a-z]+");
const myRegexp myRegexp::RXuppercase("[A-Z]+");
const myRegexp myRegexp::RXalphanum("[0-9A-Za-z]+");
const myRegexp myRegexp::RXidentifier("[A-Za-z_][A-Za-z0-9_]*");

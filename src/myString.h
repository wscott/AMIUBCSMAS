// my crappy string interface built on top of <string>
// it also includes a wonderful support for regular expressions based
// on POSIX's standard regex.h

#ifndef _MYSTRING_INCLUDED
#define _MYSTRING_INCLUDED

#include <string>
#include <vector>
#include <sys/types.h>
extern "C" {
#include <regex.h>
}

class myRegexp;

class myString {
  typedef string::size_type size_type;

  string s;

public:
  myString(void) : s("")
    { }
  myString(const myString& s2) : s(s2.s)
    { }
  myString(const string& s2) : s(s2)
    { }
  myString(const char* c) : s(c)
    { }
  ~myString(void)
    { }

  myString& operator=(const myString& s2)
    { s = s2.s;
      return *this; }
  const myString operator+(const myString& s2) const
    { return s + s2.s; }
  myString& operator+=(const myString& s2)
    { s += s2.s;
      return *this; }
  const myString operator+(const char* s2) const
    { return s + s2; }
  myString& operator+=(const char* s2)
    { s += s2;
      return *this; }
  const myString operator+(const char c2) const
    { return s + c2; }
  myString& operator+=(const char c2)
    { s += c2;
      return *this; }
  int compare(const myString& s2) const
    { return s.compare(s2.s); }
  int compare(const char* s2) const
    { return s.compare(s2); }
  int index(const char c, size_type i = string::npos) const
    { return s.find(c, i); }
  int index(const myString& s2, size_type i = string::npos) const
    { return s.find(s2.s, i); }
  myString before(size_type i) const
    { return s.substr(0, i); }
  myString after(size_type i) const
    { return s.substr(i+1, string::npos); }
  myString at(size_type i, size_type len = string::npos) const
    { return s.substr(i, len); }
  vector<myString> split(const myString& sep, int max = 0);
  vector<myString> split(const myRegexp& sep, int max = 0);
  bool matches(const myString& s2, size_type pos = 0) const
    { return !s.compare(s2.s, pos, string::npos); }
  bool matches(const myRegexp& rx, size_type pos = 0) const;
  const myString operator()(size_type i1, size_type i2 = string::npos) const
    { return s.substr(i1, (i2 == string::npos)? string::npos : (i2-i1+1)); }
  unsigned int length(void) const
    { return s.length(); }
  operator const char*(void) const
    { return s.c_str(); }
  const char* chars(void) const
    { return s.c_str(); }
  const char* c_str(void) const
    { return s.c_str(); }
};


const int MAX_REGEXP_MATCHES = 32;

class myRegexp {
  regex_t rxbuffer;
  mutable regmatch_t rxmatchpos[MAX_REGEXP_MATCHES];
  mutable int nmatches;
  mutable string matched_string;

  myRegexp& operator=(const myRegexp&);
  myRegexp(const myRegexp&);

public:
  myRegexp(const char* s);
  ~myRegexp(void);
  bool match(const char* s, myString::size_type pos = 0) const;
  bool match_pos(const int i, int* begin, int* end) const;
  myString match_text(const int i) const;
  myString substitute(const char* s) const;

  // some commonly used ones
static const myRegexp RXwhite;          // = "[ \n\t\r\v\f]+"
static const myRegexp RXint;            // = "-?[0-9]+"
static const myRegexp RXdouble;         // = "-?\\(\\([0-9]+\\.[0-9]*\\)\\|
                                        //    \\([0-9]+\\)\\|\\(\\.[0-9]+\\)\\)
                                        //    \\([eE][---+]?[0-9]+\\)?"
static const myRegexp RXalpha;          // = "[A-Za-z]+"
static const myRegexp RXlowercase;      // = "[a-z]+"
static const myRegexp RXuppercase;      // = "[A-Z]+"
static const myRegexp RXalphanum;       // = "[0-9A-Za-z]+"
static const myRegexp RXidentifier;     // = "[A-Za-z_][A-Za-z0-9_]*"
};



inline
myString operator+(const char* c, const myString& s)
{
  return myString(c) + s;
}

inline
bool myString::matches(const myRegexp& rx, size_type pos = 0) const
{
  return rx.match(s.c_str(), pos);
}

inline
bool operator==(const myString& s1, const myString& s2)
{
  return !s1.compare(s2);
}

inline
bool operator==(const myString s1, const char* s2)
{
  return !s1.compare(s2);
}

inline
bool operator==(const char* s1, const myString& s2)
{
  return !s2.compare(s1);
}

inline
bool operator!=(const myString& s1, const myString& s2)
{
  return s1.compare(s2);
}

inline
bool operator!=(const myString s1, const char* s2)
{
  return s1.compare(s2);
}

inline
bool operator!=(const char* s1, const myString& s2)
{
  return s2.compare(s1);
}

#endif

#include "starana-classes.h"



parameter* parameter::param_table = NULL;


void default_parameter_handler(const par_errors pe)
{
  switch(pe) {
  case PE_NOTADOUBLE:
    fprintf(stderr, "Tried to fetch a double from a non-double parameter\n");
    break;
  case PE_NOTASTRING:
    fprintf(stderr, "Tried to fetch a myString from a non-myString parameter\n");
    break;
  }
}

void (*parameter::parameter_handler)(const par_errors) = default_parameter_handler;


parameter::parameter(const myString& n, const myString& v) : name(n)
{
  if (get_parameter(n))
    name += "_redefined";

  _type = PString;
  _value.s = new myString(v);
  next = param_table;
  param_table = this;
}


parameter::parameter(const myString& n, const double& v) : name(n)
{
  if (get_parameter(n))
    name += "_redefined";

  _type = PDouble;
  _value.d = v;
  next = param_table;
  param_table = this;
}


parameter::operator double(void) const
{
  if (_type != PDouble) {
    parameter_handler(PE_NOTADOUBLE);
    return 0.0;
  }

  return _value.d;
}


parameter::operator myString(void) const
{
  if (_type != PString) {
    parameter_handler(PE_NOTASTRING);
    return myString("");
  }

  return *(_value.s);
}


parameter::operator int(void) const
{
  if (_type != PDouble) {
    parameter_handler(PE_NOTADOUBLE);
    return 0;
  }

  return (int)_value.d;
}


parameter* get_parameter(const myString& n)
{
  for (parameter* p = parameter::param_table; p; p = p->next)
    if (p->name == n)
      return p;

  return NULL;
}

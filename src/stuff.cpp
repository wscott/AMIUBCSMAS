#include "starana-classes.h"


// mineral type operations
_mintype _mintype::operator+(const _mintype& m2) const
{
  _mintype r;
  r.iron = iron + m2.iron;
  r.bora = bora + m2.bora;
  r.germ = germ + m2.germ;
  return r;
}

_mintype _mintype::operator-(const _mintype& m2) const
{
  _mintype r;
  r.iron = iron - m2.iron;
  r.bora = bora - m2.bora;
  r.germ = germ - m2.germ;
  return r;
}

_mintype& _mintype::operator-=(const _mintype& m2)
{
  iron -= m2.iron;
  bora -= m2.bora;
  germ -= m2.germ;
  return *this;
}

_mintype& _mintype::operator+=(const _mintype& m2)
{
  iron += m2.iron;
  bora += m2.bora;
  germ += m2.germ;
  return *this;
}

bool _mintype::enough(const _mintype& m2)
{
  return m2.iron <= iron && m2.bora <= bora && m2.germ <= germ;
}

_mintype _mintype::operator*(const int m) const
{
  _mintype r;
  r.iron = iron * m;
  r.bora = bora * m;
  r.germ = germ * m;
  return r;
}

_mintype _mintype::operator/(const int m) const
{ 
  _mintype r;
  r.iron = iron / m;
  r.bora = bora / m;
  r.germ = germ / m;
  return r;
}

int _mintype::operator/(const _mintype& m) const
{
  int n = 10000;
  if (m.iron)
    n = min(n, iron / m.iron);
  if (m.bora)
    n = min(n, bora/m.bora);
  if (m.germ)
    n = min(n, germ/m.germ);
  return n;
}



planetary_function* planetary_function::function_table = NULL;


pf_operation::pf_operation(void) : f(NULL), mode(PF_SKIP), modemask(0)
{
  for (int i = 0; i < 16; i++)
    params[i] = 0;
}



void pf_operation::clear(void)
{
  f = find_pfunction("- (nothing) -");
  mode = PF_STOMP;
  modemask = PF_CIRCLES|PF_LINES|PF_DATA|PF_NAME|PF_MARKER|PF_FLAG;
  
  for (int i = 0; i < 16; i++)
    params[i] = 0;
}



planetary_function::planetary_function(void)
{
  _name = _type = _desc = "<undefined>";
  for (int i = 0; i < 16; i++)
    _pardesc[i] = "<unused>";

  next = function_table;
  function_table = this;
}


planetary_function* find_pfunction(const String& pfn)
{
  planetary_function* pf;

  for (pf = planetary_function::function_table; pf; pf = pf->next)
    if (pf->_name == pfn)
      return pf;

  return NULL;
}



planetary_function* get_next_pfunction(planetary_function* pf)
{
  if (!pf || !pf->next)
    return planetary_function::function_table;

  return pf->next;
}


// got to use container classes or make it doubly-linked.....

planetary_function* get_prev_pfunction(planetary_function* pf)
{
  planetary_function* ppf;

  if (!pf)
    return planetary_function::function_table;
  
  if (pf == planetary_function::function_table)
    for (ppf = planetary_function::function_table; ppf->next; ppf = ppf->next);

  else
    for (ppf = planetary_function::function_table; ppf->next != pf; ppf = ppf->next);

  return ppf;
}



void object_display::reset_something(const int what)
{
  if (what & 1)
    flag = false;
  if ((what/10) & 1)
    name_color = 0;
  if ((what/100) & 1)
    marker_type = MT_NONE;
  if ((what/1000) & 1)
    n_values = 0;
  if ((what/10000) & 1)
    n_lines = 0;
  if ((what/100000) & 1)
    n_circles = 0;
}



int message::msg_mask = 0;


message::message(const String& m, const _msgtype mt, message** tab) :
                   next(NULL), type(mt), msg(m)
{
  if (*tab) {
    message* tmsg;

    for (tmsg = *tab; tmsg->next; tmsg = tmsg->next);
    tmsg->next = this;
  } else
    *tab = this;
}



void filter_out_messages(const _msgtype mt)
{
  message::msg_mask |= mt;
}



int grav_value(const double& v)
{
  int i;

  for (i = 0; i < 101; i++)
    if (v == gravity_table[i])
      break;

  if (i == 101)
    return -100;
  
  return i;
}



bool guess_gravity(int* r1, int* r2, const double& v1, const double& v2)
{
  if (v1 < gravity_table[0] || v1 > gravity_table[100] ||
      v2 < gravity_table[0] || v2 > gravity_table[100])
    return false;

  if ((*r1 = grav_value(v1)) == -100)
    return false;

  if ((*r2 = grav_value(v2)) == -100)
    return false;

  if (*r2 - *r1 < 0)
    return false;

  // check for ambiguous values but verifying that the interval width is even
  if ((*r2 - *r1) % 2)
    (*r1)++; // left limit was underestimated

  return true;
}



String int_to_str(const int i)
{
  char c[16];
  sprintf(c, "%d", i);
  return String(c);
}



queue_obj::queue_obj(const bool a, const int c, object* p, const int act,
		     const int deact) :
                       add_to_queue(act), rem_from_queue(deact), active(false),
		       autob((a)? Autobuild : Normal), count(c),
		       proto(p), res(p->res), min(p->min),
		       next(NULL)
                       
{ 
  // do nothing
}


queue_obj::queue_obj(const queue_obj& qo) :
                       add_to_queue(qo.add_to_queue), rem_from_queue(qo.rem_from_queue),
		       active(false), autob(qo.autob), count(qo.count), proto(qo.proto),
		       res(qo.proto->res), min(qo.proto->min),
		       next(NULL)
                       
{ 
  // do nothing
}

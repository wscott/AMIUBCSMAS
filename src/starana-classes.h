// #define DISABLE_BACKINGSTORE
// #define DEFAULT_FULLYVISUAL

#include "myString.h"
// must be first

#include <vector>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "starana-const.h"


class planet;
class graphics;
class race;
class object;
class design;
class queue_obj;
class minerals;
class fleet;
class planetary_function;
class fleet_function;
class stars_map;
class map_view;


// starstat structure for Stars! binary file info
struct _starstat {
  int verMajor, verMinor, verInc;
  bool InUse;
  int idGame;
  int dt;
  int turn, endturn;
  bool GameOver;
  int Player;
  bool Shareware;
  bool Done;
};


struct _xypoint {
  int x;
  int y;

  _xypoint(void) : x(0), y(0)
    { }
  _xypoint(const int i, const int j) : x(i), y(j)
    { }
  bool operator==(const _xypoint& xy) const
    { return (x == xy.x && y == xy.y); }
  bool operator!=(const _xypoint& xy) const
    { return !(*this == xy); }
  _xypoint operator+(const _xypoint& xy) const
    { return _xypoint(x+xy.x, y+xy.y); }
  _xypoint operator-(const _xypoint& xy) const
    { return _xypoint(x-xy.x, y-xy.y); }
  _xypoint operator+=(const _xypoint& xy)
    { x += xy.x; y += xy.y;
      return *this; }
  _xypoint operator-=(const _xypoint& xy)
    {  x -= xy.x; y -= xy.y;
       return *this; }
  _xypoint operator-(void) const
    { return _xypoint(-x, -y); }
  _xypoint operator*(const int s) const
    { return _xypoint(x*s, y*s); }
  _xypoint operator/(const int s) const
    { return _xypoint(x/s, y/s); }
};

struct _pieslice {
  double value;
  int color;
};


struct _lineto {
  _xypoint dp;
  int color;
  short int first_tick;   // where to draw first tick (0 for none)
  short int tick_sep;     // distance between ticks (0 for none)
  int tickdev;            // tick deviation (for arrows)
};


struct _circle {
  int radius;
  int color;
  int fillcolor;
};


#include "out_X11.h"


struct object_display {
  _xypoint xy;            // position on screen
  int nameyshift;         // to avoid overwriting data with name

  int n_values;           // n_values != 0 means use pie chart and override marker
  _pieslice values[32];
  double value;           // value for pie radius (-1e30 = use max of values[])
  double vmin, vmax;      // ranges for pie chart values
  int pie_type;           // select circular/arrow for planets/fleets
  _xypoint pie_dir;       // used for fleets to turn triangle

  int marker_color;
  _marktype marker_type;  // marker_type == 0 means NO marker at all
  int marker_size;        // set by draw routine and used to align name, don't touch it

  int name_color;         // name_color == 0 means NO name at all
  myString name;            // string (which might be != from actual name)

  int n_lines;            // number of vectors originating from object
  _lineto linedest[32];    // vector destinations

  int n_circles;
  _circle circles[4];      // circles (filled or not) centered on object

  bool flag;              // just a simple bool flag

  object_display(void)
    { reset(); }
  void reset(void);
  void reset_something(const int what);
  bool anything_defined(void) const
    { return (n_values != 0 || marker_type != MT_NONE || name_color != 0 || n_lines != 0 || flag || n_circles != 0); }
  bool data_defined(void) const
    { return (n_values != 0); }
  bool marker_defined(void) const
    { return (marker_type != MT_NONE); }
  bool name_defined(void) const
    { return (name_color != 0); }
  bool lines_defined(void) const
    { return (n_lines != 0); }
  bool circles_defined(void) const
    { return (n_circles != 0); }
  bool flag_defined(void) const
    { return flag; }
};



struct pf_operation {
  planetary_function* f;
  int params[16];
  _dfmode mode;
  int modemask;

  pf_operation(void);
  // default copy constructor
  // default destructor

  void clear(void);
};


class planetary_function {
  friend planetary_function* get_next_pfunction(planetary_function* pf);
  friend planetary_function* get_prev_pfunction(planetary_function* pf);
  friend planetary_function* find_pfunction(const myString& pfn);

static planetary_function* function_table;
  planetary_function* next;

protected:
  myString _name;
  myString _type;
  myString _desc;
  myString _pardesc[16];

  planetary_function(void);
  virtual ~planetary_function(void)
    { }

public:
  const myString& name(void)
    { return _name; }
  const myString& type(void)
    { return _type; }
  const myString& description(void)
    { return _desc; }
  const myString& parameter_desc(const int i)
    { return _pardesc[i]; }
  virtual void function(map_view& mw, planet* p, const int* par, const int when) = 0;
};


struct ff_operation {
  fleet_function* f;
  int params[16];
  _dfmode mode;
  int modemask;

  ff_operation(void);
  // default copy constructor
  // default destructor

  void clear(void);
};


class fleet_function {
  friend fleet_function* get_next_ffunction(fleet_function* ff);
  friend fleet_function* get_prev_ffunction(fleet_function* ff);
  friend fleet_function* find_ffunction(const myString& pfn);

static fleet_function* function_table;
  fleet_function* next;

protected:
  myString _name;
  myString _type;
  myString _desc;
  myString _pardesc[16];

  fleet_function(void);
  virtual ~fleet_function(void)
    { }

public:
  const myString& name(void)
    { return _name; }
  const myString& type(void)
    { return _type; }
  const myString& description(void)
    { return _desc; }
  const myString& parameter_desc(const int i)
    { return _pardesc[i]; }
  virtual void function(map_view& mw, fleet* f, const int* par, const int when) = 0;
};



struct message {
  friend void filter_out_messages(const int mt);
  friend void filter_in_messages(const int mt);
  friend bool messages_are_filtered(const int mt);

static int color_table[31];
static int msg_mask;

  message* next;
  int type;
  myString msg;

  message(const int mt, const myString& m) : next(NULL), type(mt), msg(m)
    { }
  void print(FILE* of) const
    { fprintf(of, "%s\n", (const char*)msg); }
  bool filtered(void) const
    { return (bool)(type & msg_mask); }
  int color(void) const;
};



class message_table {
  message* head;
  message* tail;

public:
  message_table(void) : head(NULL), tail(NULL)
    { }
  ~message_table(void);
  void add(const int mt, const myString& m);
  const message* first(void) const
    { return head; }
};



struct _mintype {
  int iron;
  int bora;
  int germ;

  _mintype(void)
    { iron = bora = germ = 0; }
  _mintype operator+(const _mintype& m2) const;
  _mintype operator-(const _mintype& m2) const;
  _mintype& operator-=(const _mintype& m2);
  _mintype& operator+=(const _mintype& m2);
  bool enough(const _mintype& m2);
  _mintype operator*(const int m) const;
  _mintype operator/(const int m) const;
  int operator/(const _mintype& m) const;
  int total(void) const
    { return iron + bora + germ; }
  void clear(void)
    { iron = bora = germ = 0; }
  int& operator[](const int i) 
    { if (!i) return iron;
      if (i==1) return bora;
      return germ; }
  const int& operator[](const int i) const
    { if (!i) return iron;
      if (i==1) return bora;
      return germ; }
};



enum par_type { PDouble, PString };
enum par_errors { PE_NOTADOUBLE, PE_NOTASTRING };

class parameter {
  friend parameter* get_parameter(const myString& n);

static parameter* param_table;
static void (*parameter_handler)(const par_errors);

  parameter* next;
  myString name;
  par_type _type;
  union {
    myString* s;
    double d;
  } _value;

  parameter(const parameter&);
  parameter& operator=(const parameter&);
  ~parameter(void);

public:
  parameter(const myString& n, const myString& v);
  parameter(const myString& n, const double& d);
  par_type type(void) const
    { return _type; }
  operator double(void) const;
  operator int(void) const;
  operator myString(void) const;
};



class race {
  // allow access - this will need to be changed, splitting the "struct"-type
  // attributes (public) from the "class"-type attributes (private)
  friend class planet;
  friend class fleet;
  friend class stars_map;
  friend class map_view;
  friend void check_auth_source(const char* item);
  friend int yyparse(void);
  friend void graphics::load_racialreport(const int rid);
  friend void graphics::load_rrcomparisons(const int rid);

static int fibonacci[26];
static myString lrt_names[14];
static myString prt_names[10];

  myString _name;
  myString _names;
  int id;
  int reliab;
  bool can_analyze;
  bool has_report;

  int hab_min[3];
  int hab_max[3];
  int col_res;
  int col_grow;
  int fact_res;
  int fact_cost;
  int fact_ctrl;
  int fact_germ;
  int mine_eff;
  int mine_cost;
  int mine_ctrl;
  int tech[SIM_FUTURE][6];
  int tech_tonext[SIM_FUTURE][6];
  char techcost[7];
  int tech_research[SIM_FUTURE];
  int tform_tech[SIM_FUTURE][3];
  prt_type _prt;
  bool lrt_tab[14];
  int min_pop_move;
  int maxpop;
  int maxfact;
  int maxmine;
  int maxres;

  queue_obj* default_queue;
  object* object_table;
  object* last_object;
  fleet* fleet_table;
  fleet* last_fleet;
  planet* planet_table;

  // totals
  int total_pop[SIM_FUTURE];
  int total_opop[SIM_FUTURE];
  int total_hab[SIM_FUTURE];
  int total_growth[SIM_FUTURE];
  int total_gpctg[SIM_FUTURE];
  int total_geff[SIM_FUTURE];
  _mintype total_min[SIM_FUTURE];
  _mintype total_mg[SIM_FUTURE];
  int total_fact[SIM_FUTURE];
  int total_mine[SIM_FUTURE];  
  int total_maxfact[SIM_FUTURE];
  int total_maxmine[SIM_FUTURE];  
  int total_unufact[SIM_FUTURE];
  int total_unumine[SIM_FUTURE];
  int total_res[SIM_FUTURE];
  int total_rsrch[SIM_FUTURE];

  // this is year-independent
  int total_fleets[6];
  int number_fleets;

  int explored_planets;
  int owned_planets;

  int curr_year;

  // report-log messages to put in window
  message_table logmsgs;

  race(const race&);
  race& operator=(const race&);

  int get_normal_tform(const int bio, const int ewp);

public:
  race(const myString& n, const int i);
  ~race(void);

  const myString& name(void) const
    { return _name; }
  const myString& names(void) const
    { return _names; }
  bool do_analysis(void) const
    { return can_analyze; }
  bool gave_report(void) const
    { return has_report; }
  int reliability(void) const
    { return reliab; }
  void output(FILE* of) const;
  //  void report(const report_type rt, FILE* of) const;
  bool lrt(lrt_type lt) const
    { return lrt_tab[lt]; }
  prt_type prt(void) const
    { return _prt; }
  myString lrt_name(void) const;
  myString prt_name(void) const
    { return prt_names[(int)_prt]; }
  int race_id(void) const
    { return id; }
  int col_resource(void) const
    { return col_res; }
  int max_res_per_planet(void) const
    { return maxres; }
  int max_pop_per_planet(void) const
    { return maxpop; }
  int max_fact_per_planet(void) const
    { return maxfact; }
  int max_mine_per_planet(void) const
    { return maxmine; }
  myString factory_stats(void) const;
  myString mine_stats(void) const;  
  object* add_object(const myString& n, const int r, const int i, const int b, const int g);
  object* create_object(const myString& n);
  design* create_design(const myString& n);
  object* find_object(const myString& n) const;
  design* find_design(const myString& n, const bool starbase = false) const;
  design* find_design_alias(const myString& n, const bool starbase = false) const;
  object* next_object(const object* o) const;
  void add_fleet(fleet* f);
  void replace_fleet(fleet* pof, fleet* of, fleet* nf);
  bool add_to_default_queue(const bool a, const myString& n, const int c, const int act = 0, const int deact = SIM_FUTURE);
  void advance_year(void);
  void choose_next_tech_field(void);
  void perform_research(void);
  int defense_level(int when = 0) const;
  int pla_penscan_radius(int when = 0) const;
  int pla_scan_radius(int when = 0) const;
  int compute_percent_from_def(const int d);
  int compute_def_from_percent(const int dp);
  void set_terraform_tech(int when = 0);
  const char* tech_cost(void) const
    { return techcost; }
  const int* tech_level(int when = 0)
    { return tech[when]; }
  const int* terraform_tech(int when = 0)
    { return tform_tech[when]; }
  void set_minimal_objects(void);
  void check_data(void);
  const int* habmin(void) const
    { return hab_min; }
  const int* habmax(void) const
    { return hab_max; }
  void add_message(const int mt, const myString& m);
  const message* next_message(const message* m) const;
};



class planet {
  friend class stars_map;
  friend class map_view;
  friend int yyparse(void);
  friend void check_defined_source(const char* item);
  friend void check_auth_source(const char* item);

public:
  enum _platype { UNKNOWN=0, LOOTING=1, BREEDER=2, PRODUCTION=3,
		  NEWCOLONY=4, GENERIC=5, MINING=6 };

private:
  planet* next;
  planet* rnext;
  planet* snext;

  myString _name;
  int stars_id;
  myString header;
  _platype p_type;
  bool homeworld;
  _xypoint pos;

  myString r_starbase[16];
  race* r_owner[16];
  int r_hab[16];
  int r_mxhab[16];
  int r_pop[16];
  int r_stats[16][3];
  int r_oristats[16][3];
  _mintype r_minconc[16];
  int r_def_coverage[16];
  int r_age[16];
  int auth_source;
  int trusted_source;
  int rep_age;

  int scan_normal;
  int scan_pen;
  myString starbase;
  starbase_type stb_type;
  design* stb_design;
  int stb_damage;
  int gatemass;
  int gaterange;
  planet* driverdest;
  int driverwarp;
  planet* routing;

  int power;

  race* _owner;
  queue_obj* queue;
  int ori_stats[3];
  int _stats[SIM_FUTURE][3];
  _mintype _min_conc[SIM_FUTURE];
  _mintype mine_year[SIM_FUTURE];
  int _pop[SIM_FUTURE];
  int _pop_lsd[SIM_FUTURE];
  int _factories[SIM_FUTURE];
  int _mines[SIM_FUTURE];
  int _defenses[SIM_FUTURE];
  int def_coverage[SIM_FUTURE];
  _mintype _mineral[SIM_FUTURE];
  _mintype _minshortage[SIM_FUTURE];
  int _habitab[SIM_FUTURE];
  int res[SIM_FUTURE];
  int _research[SIM_FUTURE];
  int _tot_resources[SIM_FUTURE];
  int _tot_research[SIM_FUTURE];
  int avail_res;

static int planet_pop_needs[][6];

  int need_pop;
  _mintype need_min;

  fleet* incoming;

  int curr_year;
  message_table msg_table[SIM_FUTURE];
  message_table global_msgs;

  void add_message(const int mt, const myString& m);
  void add_gmessage(const int mt, const myString& m);
  queue_obj* create_nonauto(queue_obj* qo);
  void create_object(const object* o, const int n = 1);
  void calc_habitability(void);
  int tform_left(race* owner = NULL, int when = -1) const;
  void instaform(void);
  int habitability(const int* st, const race* owner = NULL) const;
  bool set_planet_stats(int *st, double g, const double& t, const double& r);
  void add_to_queue(queue_obj* qo);
  starbase_type get_starbase_power(const myString& sn);

  int fix_year(const int when) const
    { return (when == -1)? curr_year : when; }

  planet(const planet&);
  planet& operator=(const planet&);

public:
  planet* tnext;
  object_display disp;

  planet(const myString& n);
  ~planet(void);
  void grow_pop(void);
  void check_data(void);
  bool evolving(int when = -1) const
    { when = fix_year(when);
      return _owner && _owner->can_analyze && _pop[when]; }
  const myString& name(void) const
    { return _name; }
  const _xypoint& position(void) const
    { return pos; }
  const int& starsid(void) const
    { return stars_id; }
  race* owner(void) const
    { return _owner; }
  bool is_homeworld(void) const
    { return homeworld; }
  bool data_available(void) const
    { return trusted_source != -1; }
  race* trustedsource(void) const;
  race* authsource(void) const;
  int report_age(void) const
    { return rep_age; }
  const char* type_name(void) const;
  void output(FILE* of, int when = -1) const;
  void clear_queue(void);
  void dump_queue(void);
  void report(const report_type rt);
  myString title(void) const;
  void pop_needs(void);
  void report_growth(void);
  void min_needs(void);
  void report_mining(void);
  planet* routing_dest(void) const
    { return routing; }
  planet* driver_destination(void) const
    { return driverdest; }
  int driver_warp(void) const
    { return driverwarp; }
  myString starbase_name(void) const
    { return starbase; }
  int starbase_damage(void) const
    { return stb_damage; }
  starbase_type starbase_power(void) const
    { return stb_type; }
  int gate_range(void) const
    { return gaterange; }
  int gate_mass(void) const
    { return gatemass; }
  int resources(int when = -1);
  int research(int when = -1) const;
  int tot_resources(int when = -1) const;
  int population(int when = -1) const;
  int defense_coverage(int when = -1) const;
  int capacity(int when = -1) const;
  int maxpop(int when = -1) const;
  int factories(int when = -1) const;
  int maxfactories(int when = -1) const;
  int maxcfactories(int when = -1) const;
  int unused_factories(int when = -1) const;
  int mines(int when = -1) const;
  int maxmines(int when = -1) const;
  int maxcmines(int when = -1) const;
  int unused_mines(int when = -1) const;
  int defenses(int when = -1) const;
  int maxdefenses(int when = -1) const;
  int maxcdefenses(int when = -1) const;
  int scanning(void) const
    { return scan_normal; }
  int penscanning(void) const
    { return scan_pen; }
  const _mintype& minerals(int when = -1) const;
  const _mintype& minshortage(int when = -1) const;
  const _mintype& min_conc(int when = -1) const;
  int pop(int when = -1) const;
  const int* oristats(void) const
    { return ori_stats; }
  const int* stats(int when = -1) const;
  int habitability(int when = -1) const;
  bool need_more_factories(int when = -1) const;
  bool need_more_mines(int when = -1) const;
  bool empty_queue(void) const
    { return (queue == NULL); }
  void terraform(race* owner = NULL);
  void unterraform(race* owner);
  _mintype mining_rate(int when = -1) const;
  void do_mining(_mintype* mined);
  void init_turn(void);
  void do_turn(void);
  void spread_year0_data(void);
  void evolve(const int from, const int len);
  void advance_year(void);
  void build_queue(void);
  int max_can_build(const myString& on, int when = -1) const;
  bool add_to_queue(const bool a, const myString& n, const int c, const int act = 0, const int deact = SIM_FUTURE);
  bool insert_in_queue(int pos, const bool a, const myString& n, const int c, const int act = 0, const int deact = SIM_FUTURE);
  const message* next_message(const message* m, int when) const;
  const message* next_gmessage(const message* m) const;
  void set_power(void);
  bool set_ori_stats(const double& g, const double& t, const double& r);
  bool set_stats(const double& g, const double& t, const double& r);
  bool set_reported_stats(const int src, const double& g, const double& t, const double& r);
  bool set_reported_oristats(const int src, const double& g, const double& t, const double& r);
  int hab_now(race* owner = NULL, int when = -1) const;
  int hab_when_max_terraformed(const race* owner = NULL, int when = -1, const int* tf_tech = NULL) const;
  void guess_type(void);
  int distance(const _xypoint dest)
    { return (int)sqrt((dest.x-pos.x)*(dest.x-pos.x)+(dest.y-pos.y)*(dest.y-pos.y)); }
  int distance(planet* p)
    { return (int)sqrt((p->pos.x-pos.x)*(p->pos.x-pos.x)+(p->pos.y-pos.y)*(p->pos.y-pos.y)); }
  void add_fleet(fleet* f);
};


struct engine {
  engine* next;

  myString name;
  int fuel_usage[11];

  engine(const myString n) : name(n)
    { for (int i = 0; i < 11; i++)
        fuel_usage[i] = 0; }
};


struct hull {
  hull* next;

  myString name;
  int def_fuel;
  int def_cargo;
  int n_engines;
  int base_mass;

  hull(const myString& n) : name(n), def_fuel(0), def_cargo(0), n_engines(0), base_mass(0)
    { }
};


class object {
  friend class queue_obj;
  friend class planet;
  friend class race;
  friend int yyparse(void);

  myString _name;
  int res;
  _mintype min;
  design* des;

public:
  object* next;

  object(const myString& n, const int r = 10000,
	 const int i = 10000, const int b = 10000, const int g = 10000) :
           _name(n), res(r), des(NULL)
    { min[0] = i; min[1] = b; min[2] = g; }
  const myString& name(void) const
    { return _name; }
  const _mintype& minerals(void) const
    { return min; }
  int resources(void) const
    { return res; }
  bool is_design(void) const
    { return des != NULL; }
  design* d(void) const
    { return des; }
};



class queue_obj {
  friend class planet;

  int add_to_queue;
  int rem_from_queue;
  bool active;
  enum {Normal, Autobuild, AutoDone} autob;
  int count;
  object* proto;
  int res;
  _mintype min;

  queue_obj& operator=(const queue_obj&);

public:
  queue_obj* next;

  queue_obj(const bool a, const int c, object* p, const int act = 0,
	    const int deact = SIM_FUTURE);
  queue_obj(const queue_obj& qo);
  // ~queue_obj(void); // default destructor
};


class design {
  friend class race;
  friend class fleet;
  friend int yyparse(void);

  object* obj;
  hull* h;
  int maxcargo;
  int maxfuel;
  engine* eng;
  int mass;
  myString alias;

  design(const design&);
  design& operator=(const design&);

public:
  design(object* o) : obj(o), h(NULL), eng(NULL)
    { maxcargo = maxfuel = mass = 0; }
  ~design(void);

  object* o(void) const
    { return obj; }
  bool is_starbase(void) const
    { return (h->n_engines == 0); }
  hull* basehull(void) const
    { return h; }
  int weight(void) const
    { return mass; }
};



class fleet {
  friend class planet;
  friend class stars_map;
  friend class map_view;
  friend int yyparse(void);  
  friend void race::add_fleet(fleet* f);
  friend void race::replace_fleet(fleet* pof, fleet* of, fleet* nf);

  fleet* rnext;
  fleet* pnext;

  myString _starsname;
  myString _name;
  race* _owner;
  bool enemy;
  int stars_id;
  _xypoint pos[SIM_FUTURE];
  planet* _destin;
  planet* _origin;
  planet* _orbit[SIM_FUTURE];
  int _warp;
  int eta;
  int starsETA;
  myString wptask_name;
  myString battleplan_name;
  int numships[6];
  int _mass;
  _mintype _min;
  int _pop;
  int _maxcargo;
  int _fuel, _maxfuel;
  int scan_normal;
  int scan_pen;
  int _cloaking;
  int _minelaying;
  int _minesweeping;
  int _terraforming;
  int _remote_mining;
  design* des[16];
  int ndes[16];

public:
  object_display disp;

  fleet(const myString& n);
  ~fleet(void);
  void check_data(void);
  void output(FILE* of) const;
  const _xypoint& position(const int w) const
    { return pos[w]; }
  race* owner(void) const
    { return _owner; }
  const myString& name(void) const
    { return _name; }
  const myString& starsname(void) const
    { return _starsname; }
  int unload_pop(void);
  _mintype unload_min(void);
  void refuel(void)
    { _fuel = _maxfuel; }
  planet* destination(void) const
    { return _destin; }
  planet* orbiting(const int w) const
    { return _orbit[w]; }
  planet* origin(void) const
    { return _origin; }
  int warp(void) const
    { return _warp; }
  int ETA(void) const
    { return eta; }
  int n_ships(const int type) const
    { return numships[type]; }
  int mass(void) const
    { return _mass; }
  const _mintype& minerals(void) const
    { return _min; }
  int pop_cargo(void) const
    { return _pop; }
  int max_cargo(void) const
    { return _maxcargo; }
  int fuel(void) const
    { return _fuel; }
  int scanning(void) const
    { return scan_normal; }
  int penscanning(void) const
    { return scan_pen; }

  bool find_possible_destination(void);
  bool find_possible_origin(const _xypoint& dest);
};



const int MAX_DISP_MODES = 16;

struct planet_view {
  myString name;
  pf_operation pla_modes[MAX_DISP_MODES];

  planet_view(const myString& n);
  planet_view(const planet_view& pv);
  void export(FILE* f);
  void clear(void);
  void link(void);
};
  

struct fleet_view {
  myString name;
  ff_operation fle_modes[MAX_DISP_MODES];

  fleet_view(const myString& n);
  fleet_view(const fleet_view& fv);
  void export(FILE* f);
  void clear(void);
  void link(void);
};
  


// a simple class to keep the map display info in one place

typedef vector<planet_view*> pview_v;
typedef vector<fleet_view*> fview_v;

class map_view {
  int xmap0, ymap0;
  int _zoom;
  int gmsc;
  int _when;
  stars_map* map;
  int space_mode;
  bool do_alliances;
  pview_v planet_views;
  unsigned int pview;
  int cur_pf;
  fview_v fleet_views;
  unsigned int fview;
  int cur_ff;
  int scanner_eff;
  race* race_viewpoint;
  planet* curr_planet[4];

  map_view(const map_view&);
  map_view& operator=(const map_view&);

  int calc_radius(const double& v, const double& vmin, const double& vmax);
  void draw_object(object_display* pd, const int stage);
  void display_normal_scanning(const race* vp);
  void display_pen_scanning(const race* vp);

public:
  // position in real screen (set as you prefer)
  int x0, y0, xw, yw;

public:

  map_view(stars_map* m);
  // default destructor
  void initialize(void);

  int zoom(const int z);
  int xtranslate(const int dx);
  int ytranslate(const int dy);
  int when(const int w);
  int good_move(void);
  void reset(void);
  void set_viewpoint(race* r);
  race* viewpoint(void) const
   { return race_viewpoint; }
  const char* maptype_name(void) const;
  int set_maptype(const int mt);

  planet* set_active_planet(const _xypoint& physpos, int pn = 0);
  planet* get_active_planet(const int pn = 0) const;

  int select_plamode(const int pm);
  void delete_plamode(void);
  void insert_plamode(void);
  const pf_operation& get_plamode(const int i = -1) const;
  void set_plamode(const myString& pmn, const _dfmode pfm = PF_STOMP, const int pfmsk = PF_CIRCLES|PF_LINES|PF_DATA|PF_MARKER|PF_NAME|PF_FLAG, const int* par = NULL);
  int get_num_planet_views(void) const
    { return planet_views.size(); }
  int get_planet_view_index(void) const
    { return pview; }
  planet_view* get_planet_view(const int i = -1) const;
  void clone_planet_view(planet_view* orig);
  int select_planet_view(const int i);
  void delete_planet_view(const int i);
  void move_planet_view(const int i, const int dir);
  bool save_planet_views(const myString& fn);
  bool import_planet_views(const myString& fn);

  int select_flemode(const int fm);
  void delete_flemode(void);
  void insert_flemode(void);
  const ff_operation& get_flemode(const int i = -1) const;
  void set_flemode(const myString& fmn, const _dfmode ffm = PF_STOMP, const int ffmsk = PF_CIRCLES|PF_LINES|PF_DATA|PF_MARKER|PF_NAME|PF_FLAG, const int* par = NULL);
  int get_num_fleet_views(void) const
    { return fleet_views.size(); }
  int get_fleet_view_index(void) const
    { return fview; }
  fleet_view* get_fleet_view(const int i = -1) const;
  void clone_fleet_view(fleet_view* orig);
  int select_fleet_view(const int i);
  void delete_fleet_view(const int i);
  void move_fleet_view(const int i, const int dir);
  bool save_fleet_views(const myString& fn);
  bool import_fleet_views(const myString& fn);

  bool set_alliances(const int b);
  int set_scanner_eff(const int e);
  stars_map* get_map(void) const
    { return map; }
  _xypoint map_to_display(const _xypoint& xyin) const;
  _xypoint display_to_map(const _xypoint& xyin) const;
  int map_to_display(const int r) const;
  void display_space(void);
  void set_planet_display(void);
  void set_fleet_display(void);
  void set_window_title(void) const;
  void display_objects(void);
  void display_racenames(const int xp, const int yp);
};



class stars_map {
  friend int yyparse(void);
  friend class map_view;

  myString game_name;
  int game_year;

  int xmin, ymin;
  int xmax, ymax;
  int surface;

  int total_planets;
  int unexplored_planets;
  int uninhabited_planets;

  int race_planets[16];
  int race_surface[16];

  planet* unsorted_ptable;
  planet** sorted_ptable;
  planet*** xregion_ptable;
  int n_regions;

  int** valtab;
  int (*wfunc)(const int r);
  int wfrange;
  int wf_rspan;

  int view_res;
  int base_res;
  int max_zoom;
  int gmscale;
  short int* row_lengths;
  short int** row_owners;
  int** row_posits;

  race* race_list[16];
  int number_races;
  int cur_alliance;
  myString cur_alliance_name;
  myString alliance_names[16];
  int race_alliances[16];

  hull* ship_hulls;
  engine* ship_engines;

  int actual_sim_future;
  message_table logmsgs;
  FILE* report_log;

  void build_valtab(void);

public:
  stars_map(void);
  ~stars_map(void);
  void open_report_log(const myString& rln);
  FILE* logfile(void) const
    { return report_log; }
  void log(const myString& m);
  void log_all_messages(void);
  bool read_smf_file(const myString& name);
  race* find_race(const myString& n);
  race* find_race(const int id) const;
  const myString& name(void) const
    { return game_name; }
  const int year(void) const
    { return game_year; }
  const int sim_future(void) const
    { return actual_sim_future - 1; }
  const int displayres(void) const
    { return view_res; }
  const int maxmapzoom(void) const
    { return max_zoom; }
  void sort_universe(void);  
  void init_ownership(void);
  int get_ownership(const int xm, const int ym, const int reg0, const int reg1, bool *discuss);
  void line_ownership(const int ym);
  void add_planet(planet* p);
  planet* grab_planet(const myString& pn);
  planet* find_planet(const myString& pn);
  planet* find_planet(const int st_id);
  planet* find_planet(const _xypoint& xy);
  planet* find_planet(const _xypoint& xy, const _xypoint& dir);
  void evolve_planets(void);
  void find_breeders(planet* p);
  void find_minerals(planet* p, const int mt);
  void check_planets_step1(void);
  void check_fleets(void);
  void check_planets_step2(void);
  void empire_report(void);
  race* add_race(const myString& rn);
  hull* create_hull(const myString& hn);
  hull* find_hull(const myString& hn);
  engine* create_engine(const myString& en);
  engine* find_engine(const myString& en);
  void add_fleet(fleet* f, const int source);
  void create_alliance(const myString& an);
  bool add_to_alliance(const myString& rn);
  bool are_allies(const race* r1, const race* r2);
  int number_of_players(void)
    { return number_races; }
  int number_of_planets(void)
    { return total_planets; }
  int number_of_unexplored_planets(void)
    { return unexplored_planets; }
  void add_message(const int mt, const myString& m);
  void all_races_message(const int mt, const myString& m);
};



extern bool fully_visual;
extern bool do_display;
extern stars_map* game_map;
extern map_view* mapview;
extern graphics* display;
extern int infile_lineno;
extern myString infile_name;
extern myString infile_path;

extern int PARmin_mineral_move;
extern int PARmax_search_distance;
extern int PARmin_pop_for_scanner;

bool initialize_map(const myString& smff);
myString int_to_str(const int);
bool guess_gravity(int* r1, int* r2, const double& v1, const double& v2);
int wfunc_160(const int);
int wfunc_200(const int);
int wfunc_250(const int);
int yyparse(void);
int yyerror(char* m);
bool convert(const myString& infile, const myString& outfile);
bool starstat(const char* fn, _starstat* sfi);
bool add_fleet_alias(const myString& n, const myString& a);
const myString& find_fleet_alias(const myString& n);
int message_type_number(int mt);
int message_get_mask(const int i);

#define CONFIG_LINUX
// #define DISABLE_BACKINGSTORE
// #define DEFAULT_FULLYVISUAL


#ifdef CONFIG_LINUX
#include <String.h>
#endif

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// I don't want this
#undef abs


#define SIM_FUTURE 51


class planet;
class graphics;
class race;
class object;
class queue_obj;
class minerals;
class fleet;
class planetary_function;
class stars_map;
class map_view;



inline int sign(const int i)
{
  return (i > 0)? 1 : ( (i < 0)? -1 : 0 );
}


inline int abs(const int i)
{
  return (i > 0)? i : -i;
}


inline int min(const int i, const int j)
{
  return (i < j)? i : j;
}


inline int max(const int i, const int j)
{
  return (i > j)? i : j;
}


enum report_type { Total, Full, Graph };

enum prt_type { HE = 0, SS = 1, WM = 2, CA = 3, IS = 4, 
		SD = 5, PP = 6, IT = 7, AR = 8, JoaT = 9 };
enum lrt_type { IFE = 0, TT = 1, ARM = 2, ISB = 3, GR = 4, UR = 5, MA = 6, 
		NRSE = 7, CE = 8, OBRM = 9, NAS = 10, LSP = 11, BET = 12, RS = 13 };
enum tech_type { Ener=0, Weap=1, Prop=2, Con=3, Elec=4, Bio=5 };
enum stat_type { Grav=0, Temp=1, Rad=2 };

const double gravity_table[101] = { 0.12, 0.12, 0.13, 0.13, 0.14, 0.14, 0.15, 0.15,
   0.16, 0.17, 0.17, 0.18, 0.19, 0.20, 0.21, 0.22, 0.24, 0.25, 0.27, 0.29, 0.31,
   0.33, 0.36, 0.40, 0.44, 0.50, 0.51, 0.52, 0.53, 0.54, 0.55, 0.56, 0.58, 0.59,
   0.60, 0.62, 0.64, 0.65, 0.67, 0.69, 0.71, 0.73, 0.75, 0.78, 0.80, 0.83, 0.86,
   0.89, 0.92, 0.96, 1.00, 1.04, 1.08, 1.12, 1.16, 1.20, 1.24, 1.28, 1.32, 1.36,
   1.40, 1.44, 1.48, 1.52, 1.56, 1.60, 1.64, 1.68, 1.72, 1.76, 1.80, 1.84, 1.88,
   1.92, 1.96, 2.00, 2.24, 2.48, 2.72, 2.96, 3.20, 3.44, 3.68, 3.92, 4.16, 4.40,
   4.64, 4.88, 5.12, 5.36, 5.60, 5.84, 6.08, 6.32, 6.56, 6.80, 7.04, 7.28, 7.52,
   7.76, 8.00 };


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
};


struct _circle {
  int radius;
  int color;
  int fillcolor;
};


#include "out.h"


const int PIE_CIRCLE = 0;
const int PIE_TRIANG = 1;


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
  String name;            // string (which might be != from actual name)

  int n_lines;            // number of vectors originating from object
  _lineto linedest[32];    // vector destinations

  int n_circles;
  _circle circles[4];      // circles (filled or not) centered on object

  bool flag;              // just a simple bool flag

  object_display(void)
    { reset(); }
  void reset(void)
    { nameyshift = n_circles = n_lines = n_values = name_color = 0; marker_type = MT_NONE; flag = false; vmin = 0.0; vmax = 1.0; value = -1e30; }
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

// modes
enum _pfmode {
  PF_SKIP     = 1,      // do nothing if anything is defined
  PF_STOMP    = 2,      // always call the function
  PF_AND      = 3,      // act only if ??? is already defined
  PF_OR       = 4,      // act only if ??? is NOT defined
  PF_NEXT     = 20,     // move to next pfmode
  PF_PREV     = 21,     // move to previous pfmode
  PF_NULL     = 22,     // do nothing
};

// mode masks
const int PF_DATA     = 0x01;  // ??? = planetary data
const int PF_MARKER   = 0x02;  // ??? = planetary marker
const int PF_NAME     = 0x04;  // ??? = planet name
const int PF_LINES    = 0x08;  // ??? = planet lines
const int PF_FLAG     = 0x10;  // ??? = planet flag
const int PF_CIRCLES  = 0x20;  // ??? = planet circles


struct pf_operation {
  planetary_function* f;
  int params[16];
  _pfmode mode;
  int modemask;

  pf_operation(void);
  // default copy constructor
  // default destructor

  void clear(void);
};


class planetary_function {
  friend planetary_function* get_next_pfunction(planetary_function* pf);
  friend planetary_function* get_prev_pfunction(planetary_function* pf);
  friend planetary_function* find_pfunction(const String& pfn);

static planetary_function* function_table;
  planetary_function* next;

protected:
  String _name;
  String _type;
  String _desc;
  String _pardesc[16];

  planetary_function(void);
  virtual ~planetary_function(void)
    { }

public:
  const String& name(void)
    { return _name; }
  const String& type(void)
    { return _type; }
  const String& description(void)
    { return _desc; }
  const String& parameter_desc(const int i)
    { return _pardesc[i]; }
  virtual void function(map_view& mw, planet* p, const int* par, const int when) = 0;
};



enum _msgtype { NONMASKABLE = 0,
		PLA_BUILD = 0x02, PLA_FLEETS = 0x04, PLA_REPORTS = 0x08, PLA_MINSTATE = 0x10,
                PLA_POPSTATE = 0x20, PLA_INTERNAL = 0x40 };

struct message {
  friend void filter_out_messages(const _msgtype mt);

  message* next;
  _msgtype type;
  String msg;

static int msg_mask;

  message(const String& m, const _msgtype mt, message** tab);
  void print(FILE* of) const
    { fprintf(of, "%s\n", (const char*)msg); }
  bool filtered(void) const
    { return (bool)(type & msg_mask); }
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
  friend parameter* get_parameter(const String& n);

static parameter* param_table;
static void (*parameter_handler)(const par_errors);

  parameter* next;
  String name;
  par_type _type;
  union {
    String* s;
    double d;
  } _value;

  parameter(const parameter&);
  parameter& operator=(const parameter&);
  ~parameter(void);

public:
  parameter(const String& n, const String& v);
  parameter(const String& n, const double& d);
  par_type type(void) const
    { return _type; }
  operator double(void) const;
  operator int(void) const;
  operator String(void) const;
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

static int fibonacci[26];
static String lrt_names[14];
static String prt_names[10];

  String _name;
  String _names;
  int id;
  int reliab;
  bool can_analyze;

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
  char tech_cost[7];
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
  fleet* fleet_table;
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

  int curr_year;

  race(const race&);
  race& operator=(const race&);

  int get_normal_tform(const int bio, const int ewp);

public:
  race(const String& n, const int i);
  ~race(void);

  const String& name(void) const
    { return _name; }
  void output(FILE* of) const;
  //  void report(const report_type rt, FILE* of) const;
  bool lrt(lrt_type lt) const
    { return lrt_tab[lt]; }
  prt_type prt(void) const
    { return _prt; }
  int race_id(void) const
    { return id; }
  int max_res_per_planet(void) const
    { return maxres; }
  int max_pop_per_planet(void) const
    { return maxpop; }
  int max_fact_per_planet(void) const
    { return maxfact; }
  int max_mine_per_planet(void) const
    { return maxmine; }
  void add_object(const String& n, const int r, const int i, const int b, const int g);
  object* find_object(const String& n);
  object* next_object(const object* o) const;
  bool add_to_default_queue(const bool a, const String& n, const int c, const int act = 0, const int deact = SIM_FUTURE);
  void advance_year(void);
  void choose_next_tech_field(void);
  void perform_research(void);
  int pla_penscan_radius(int when = 0) const;
  int pla_scan_radius(int when = 0) const;
  void set_terraform_tech(int when = 0);
  const int* terraform_tech(int when = 0)
    { return tform_tech[when]; }
  void set_minimal_objects(void);
  void check_data(FILE* of);
  const int* habmin(void) const
    { return hab_min; }
  const int* habmax(void) const
    { return hab_max; }
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

  String _name;
  int stars_id;
  String header;
  _platype p_type;
  bool homeworld;
  _xypoint pos;

  String r_starbase[16];
  race* r_owner[16];
  int r_hab[16];
  int r_mxhab[16];
  int r_pop[16];
  int r_stats[16][3];
  int r_oristats[16][3];
  _mintype r_minconc[16];
  int r_age[16];
  int auth_source;
  int trusted_source;
  int rep_age;

  int scan_normal;
  int scan_pen;
  String starbase;
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
  message* msg_table[SIM_FUTURE];
  message* global_msgs;

  void add_message(const _msgtype mt, const String& m);
  void add_gmessage(const _msgtype mt, const String& m);
  queue_obj* create_nonauto(queue_obj* qo);
  void create_object(const object* o, const int n = 1);
  void calc_habitability(void);
  int tform_left(int when = -1) const;
  void instaform(void);
  int compute_percent_from_def(const int d);
  int compute_def_from_percent(const int dp);
  int habitability(const int* st, const race* owner = NULL) const;
  bool set_planet_stats(int *st, double g, const double& t, const double& r);
  void add_to_queue(queue_obj* qo);

  int fix_year(const int when) const
    { return (when == -1)? curr_year : when; }

  planet(const planet&);
  planet& operator=(const planet&);

public:
  planet* tnext;
  object_display disp;

  planet(const String& n);
  ~planet(void);
  void grow_pop(void);
  void check_data(FILE* of);
  bool evolving(int when = -1) const
    { when = fix_year(when);
      return _owner && _owner->can_analyze && _pop[when]; }
  const String& name(void) const
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
  void print_messages(FILE* of, int when = -1) const;
  void print_gmessages(FILE* of) const;
  void title(FILE* of) const;
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
  String starbase_name(void) const
    { return starbase; }
  int starbase_damage(void) const
    { return stb_damage; }
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
  void terraform(void);
  _mintype mining_rate(int when = -1) const;
  void do_mining(_mintype* mined);
  void init_turn(void);
  void do_turn(void);
  void spread_year0_data(void);
  void evolve(const int from, const int len);
  void advance_year(void);
  void build_queue(void);
  int max_can_build(const String& on, int when = -1) const;
  bool add_to_queue(const bool a, const String& n, const int c, const int act = 0, const int deact = SIM_FUTURE);
  bool insert_in_queue(int pos, const bool a, const String& n, const int c, const int act = 0, const int deact = SIM_FUTURE);
  message* next_message(message* m, int when) const;
  message* next_gmessage(message* m) const;
  void set_power(void);
  bool set_ori_stats(const double& g, const double& t, const double& r);
  bool set_stats(const double& g, const double& t, const double& r);
  bool set_reported_stats(const int src, const double& g, const double& t, const double& r);
  bool set_reported_oristats(const int src, const double& g, const double& t, const double& r);
  int hab_now(race* owner = NULL, int when = -1) const;
  int hab_when_max_terraformed(const race* owner = NULL, int when = -1, const int* tf_tech = NULL) const;
  int get_starbase_power(const String& sn);
  void guess_type(FILE* of);
  int distance(const _xypoint dest)
    { return (int)sqrt((dest.x-pos.x)*(dest.x-pos.x)+(dest.y-pos.y)*(dest.y-pos.y)); }
  int distance(planet* p)
    { return (int)sqrt((p->pos.x-pos.x)*(p->pos.x-pos.x)+(p->pos.y-pos.y)*(p->pos.y-pos.y)); }
  void add_fleet(fleet* f);
};



class object {
  friend class queue_obj;
  friend class planet;
  friend class race;
  friend int yyparse(void);

  String _name;
  int res;
  _mintype min;

public:
  object* next;

  object(const String& n, const int r = 10000,
	 const int i = 10000, const int b = 10000, const int g = 10000) :
           _name(n), res(r)
    { min[0] = i; min[1] = b; min[2] = g; }
  const String& name(void) const
    { return _name; }
  const _mintype& minerals(void) const
    { return min; }
  int resources(void) const
    { return res; }
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



class fleet {
  friend class planet;
  friend class stars_map;
  friend class map_view;
  friend int yyparse(void);  

  fleet* rnext;
  fleet* pnext;

  String _starsname;
  String _name;
  race* _owner;
  int stars_id;
  _xypoint pos[SIM_FUTURE];
  planet* destin;
  int warp;
  int eta;
  int starsETA;
  String wptask_name;
  String battleplan_name;
  int n_ships;
  int n_unarmed;
  int n_scout;
  int n_warship;
  int n_utility;
  int n_bomber;
  int mass;
  _mintype min;
  int pop;
  int fuel;
  int scan_normal;
  int scan_pen;
  int cloaking;
  int minelaying;
  int minesweeping;
  int terraforming;
  int remote_mining;

public:
  object_display disp;

  fleet(const String& n);
  ~fleet(void);
  void check_data(FILE* of);
  void output(FILE* of) const;
  const _xypoint& position(const int w) const
    { return pos[w]; }
  int unload_pop(void);
  _mintype unload_min(void);
  void refuel(void)
    { fuel = 1200; }
};



const int MAX_PLA_MODES = 16;

struct planet_view {
static planet_view* planet_view_table;

  String name;
  pf_operation pla_modes[MAX_PLA_MODES];
  planet_view* next;

  planet_view(const String& n);
  planet_view(const planet_view& pv);
  void export(FILE* f);
  void clear(void);
  void link(void);
};
  

struct fleet_view {
static fleet_view* fleet_view_table;

  String name;
  //  ff_operation fle_modes[16];

  fleet_view(void);
  void export(FILE* f);
};
  


// a simple class to keep the map display info in one place

const int MW_READ     = -1;
const int MW_NEXT     = -2;
const int MW_PREV     = -3;

const int MAP_BLACK     = 0;
const int MAP_OWNERS    = 1;


class map_view {
  int xmap0, ymap0;
  int _zoom;
  int gmsc;
  int _when;
  stars_map* map;
  int space_mode;
  bool do_alliances;
  planet_view* pview;
  int cur_pf;
  fleet_view* fview;
  int scanner_eff;
  race* race_viewpoint;
  planet* curr_planet;

  map_view(const map_view&);
  map_view& operator=(const map_view&);

  planet_view* map_view::extract_pview(const int i);
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
  planet* set_active_planet(const _xypoint& physpos);
  planet* get_active_planet(void) const
    { return curr_planet; }
  int select_plamode(const int pm);
  void delete_plamode(void);
  void insert_plamode(void);
  const pf_operation& get_plamode(const int i = -1) const;
  void set_plamode(const String& pmn, const _pfmode pfm = PF_STOMP, const int pfmsk = PF_CIRCLES|PF_LINES|PF_DATA|PF_MARKER|PF_NAME|PF_FLAG, const int* par = NULL);
  int get_planet_view_index(void) const;
  planet_view* get_planet_view(void) const
    { return pview; }
  void clone_planet_view(planet_view* orig);
  int select_planet_view(const int i);
  void select_fleet_view(const int i);
  void delete_planet_view(const int i);
  void move_planet_view(const int i, const int dir);
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
  bool save_planet_views(const String& fn);
  bool import_planet_views(const String& fn);
};



class stars_map {
  friend int yyparse(void);
  friend class map_view;

  String game_name;
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

  int base_res;
  int max_zoom;
  int gmscale;
  short int* row_lengths;
  short int** row_owners;
  int** row_posits;

  race* race_list[16];
  int number_races;
  int number_alliances;
  String alliance_names[16];
  int race_alliances[16];

  int actual_sim_future;
  FILE* report_log;

  void build_valtab(void);

public:
  stars_map(void);
  ~stars_map(void);
  void open_report_log(const String& rln);
  FILE* logfile(void) const
    { return report_log; }
  void log(const String& m);
  bool read_smf_file(const String& name);
  race* find_race(const String& n);
  race* find_race(const int id) const;
  const String& name(void) const
    { return game_name; }
  const int year(void) const
    { return game_year; }
  const int sim_future(void) const
    { return actual_sim_future - 1; }
  const int maxmapzoom(void) const
    { return max_zoom; }
  void sort_universe(void);  
  void init_ownership(const int bres);
  int get_ownership(const int xm, const int ym, const int reg0, const int reg1, bool *discuss);
  void line_ownership(const int ym);
  void add_planet(planet* p);
  planet* grab_planet(const String& pn);
  planet* find_planet(const String& pn);
  planet* find_planet(const int st_id);
  planet* find_planet(const _xypoint& xy);
  void evolve_planets(FILE* of);
  void find_breeders(planet* p, FILE* of);
  void find_minerals(planet* p, FILE* of, const int mt);
  void check_planets_step1(FILE* of);
  void check_fleets(FILE* of);
  void check_planets_step2(FILE* of);
  void empire_report(FILE* of);
  race* add_race(const String& rn);
  void add_fleet(fleet* f, const int source);
  void create_alliance(const String& an);
  bool add_to_alliance(const String& rn);
  bool are_allies(const race* r1, const race* r2);
  int number_of_players(void)
    { return number_races; }
  race* player_race(int i)
    { return race_list[i]; }
};



extern bool fully_visual;
extern stars_map* game_map;
extern map_view* mapview;
extern graphics* display;
extern int infile_lineno;
extern String infile_name;
extern String infile_path;

extern int PARmin_mineral_move;
extern int PARmax_search_distance;
extern int PARmin_pop_for_scanner;

bool initialize_map(const String& smff, const int mapres);
String int_to_str(const int);
bool guess_gravity(int* r1, int* r2, const double& v1, const double& v2);
int wfunc_160(const int);
int wfunc_200(const int);
int wfunc_250(const int);
int yyparse(void);
int yyerror(char* m);
bool convert(const String& infile, const String& outfile);
bool starstat(const char* fn, _starstat* sfi);

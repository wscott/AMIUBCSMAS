#define SIM_FUTURE 52

// planet report type

enum report_type { Total, Full, Graph };

// report log message types
// * marks the user-selectables in the filtering window

const int RLO_ERROR      = 0x000001; //    0
const int RLO_HABTABLE   = 0x000002;
const int RLO_DATASRC    = 0x000004; // *
const int RLO_EMPIRETOT  = 0x000008; // *
const int RLO_FLEETDUP   = 0x000010; // *
const int RLO_PLAREPORTS = 0x000020; //    5
const int RLO_PLABUILD   = 0x000040; // *
const int RLO_PLASTATS   = 0x000080;
const int RLO_PLAFLEETS  = 0x000100; // *
const int RLO_PLAMINSTAT = 0x000200; // *
const int RLO_PLAPOPSTAT = 0x000400; // * 10
const int RLO_PLANETINI  = 0x000800; // *
const int RLO_FLEETDEST  = 0x001000; // *
const int RLO_FLEETTROK  = 0x002000; // *
const int RLO_FLEETCOLON = 0x004000; // *
const int RLO_FLEETATTK  = 0x008000; // * 15
const int RLO_FLEETPARSE = 0x010000; // *
const int RLO_FLEETCONS  = 0x020000; // *
const int RLO_PLAQUEUE   = 0x040000; // *
const int RLO_PLAABUILD  = 0x080000; // *
const int RLO_FLEETTRBAD = 0x100000; // * 20

const int RLO_MAXMESSAGE = 21;

// racial characteristics / starbase hull types

enum prt_type { HE = 0, SS = 1, WM = 2, CA = 3, IS = 4, 
		SD = 5, PP = 6, IT = 7, AR = 8, JoaT = 9 };
enum lrt_type { IFE = 0, TT = 1, ARM = 2, ISB = 3, GR = 4, UR = 5, MA = 6, 
		NRSE = 7, CE = 8, OBRM = 9, NAS = 10, LSP = 11, BET = 12, RS = 13 };
enum tech_type { Ener=0, Weap=1, Prop=2, Con=3, Elec=4, Bio=5 };
enum stat_type { Grav=0, Temp=1, Rad=2 };
enum starbase_type { NoStarbase=0, OrbitalFort=1, SpaceDock=2, SpaceStation=3,
		     UltraStation=4, DeathStar=5, ErrorInName=6 };


// gravity conversion table

const double gravity_table[101] = { 0.12, 0.12, 0.13, 0.13, 0.14, 0.14, 0.15, 0.15,
   0.16, 0.17, 0.17, 0.18, 0.19, 0.20, 0.21, 0.22, 0.24, 0.25, 0.27, 0.29, 0.31,
   0.33, 0.36, 0.40, 0.44, 0.50, 0.51, 0.52, 0.53, 0.54, 0.55, 0.56, 0.58, 0.59,
   0.60, 0.62, 0.64, 0.65, 0.67, 0.69, 0.71, 0.73, 0.75, 0.78, 0.80, 0.83, 0.86,
   0.89, 0.92, 0.96, 1.00, 1.04, 1.08, 1.12, 1.16, 1.20, 1.24, 1.28, 1.32, 1.36,
   1.40, 1.44, 1.48, 1.52, 1.56, 1.60, 1.64, 1.68, 1.72, 1.76, 1.80, 1.84, 1.88,
   1.92, 1.96, 2.00, 2.24, 2.48, 2.72, 2.96, 3.20, 3.44, 3.68, 3.92, 4.16, 4.40,
   4.64, 4.88, 5.12, 5.36, 5.60, 5.84, 6.08, 6.32, 6.56, 6.80, 7.04, 7.28, 7.52,
   7.76, 8.00 };


// "pie chart" types

const int PIE_CIRCLE = 0;
const int PIE_TRIANG = 1;

// planetary/fleet functions:
// modes

enum _dfmode {
  PF_SKIP     = 1,      // do nothing if anything is defined
  PF_STOMP    = 2,      // always call the function
  PF_AND      = 3,      // act only if ??? is already defined
  PF_OR       = 4,      // act only if ??? is NOT defined
  PF_NEXT     = 20,     // move to next dfmode
  PF_PREV     = 21,     // move to previous dfmode
  PF_NULL     = 22,     // do nothing
};

// mode masks

const int PF_DATA     = 0x01;  // ??? = planetary data
const int PF_MARKER   = 0x02;  // ??? = planetary marker
const int PF_NAME     = 0x04;  // ??? = planet name
const int PF_LINES    = 0x08;  // ??? = planet lines
const int PF_FLAG     = 0x10;  // ??? = planet flag
const int PF_CIRCLES  = 0x20;  // ??? = planet circles


// graph type in race comparion window
// NOTE: it must match sequence in pfunc.c: fdchoice_displaywhat
const int RC_RESOURCES = 1;
const int RC_POPTOTAL  = 2;
const int RC_POPORBIT  = 3;
const int RC_POPPLANET = 4;
const int RC_POPGROWTH = 5;
const int RC_MINERALS  = 6;
const int RC_IRONIUM   = 7;
const int RC_BORANIUM  = 8;
const int RC_GERMANIUM = 9;
const int RC_MINING    = 10;


// fleet ship types

const int F_TOTAL   = 0;
const int F_UNARMED = 1;
const int F_SCOUT   = 2;
const int F_WARSHIP = 3;
const int F_UTILITY = 4;
const int F_BOMBER  = 5;

// mapview constants

const int MW_READ     = -1;
const int MW_NEXT     = -2;
const int MW_PREV     = -3;

const int MAP_BLACK     = 0;
const int MAP_OWNERS    = 1;


// I don't want this
#undef abs


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

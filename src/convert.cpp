#include "starana-classes.h"

#include <ctype.h>
#include <sys/stat.h>

// this function is meant to replace the functionality of
// the perl script 'stars2smf.pl', but no support for old-stle

// perl is muuuch more versatile, but this one is getting better

const int MAP_STARSID = 0;
const int MAP_PLANETNAME = 3;
const int MAP_PLANETX = 1;
const int MAP_PLANETY = 2;

const int NP_PLANETNAME = 0;
const int NP_OWNER = 1;
const int NP_STARBASE = 2;
const int NP_REPORTAGE = 3;
const int NP_POPULATION = 4;
const int NP_VALUE = 5;
const int NP_PRODQUEUE = 6;
const int NP_MINES = 7;
const int NP_FACTORIES = 8;
const int NP_DEFCOVERAGE = 9;
const int NP_SURFIRON = 10;
const int NP_SURFBORA = 11;
const int NP_SURFGERM = 12;
const int NP_IronMR = 13;
const int NP_BoraMR = 14;
const int NP_GermMR = 15;
const int NP_CONCIRON = 16;
const int NP_CONCBORA = 17;
const int NP_CONCGERM = 18;
const int NP_Resources = 19;
const int NP_GRAV = 20;
const int NP_TEMP = 21;
const int NP_RAD = 22;
const int NP_GRAVORIG = 23;
const int NP_TEMPORIG = 24;
const int NP_RADORIG = 25;
const int NP_TERRA = 26;
const int NP_Cap = 27;
const int NP_SCAN = 28;
const int NP_PENSCAN = 29;
const int NP_DRIVER = 30;
const int NP_WARP = 31;
const int NP_ROUTING = 32;
const int NP_GATERANGE = 33;
const int NP_GATEMASS = 34;
const int NP_PCTDMG = 35;

const int NF_FNAME = 0;
const int NF_X = 1;
const int NF_Y = 2;
const int NF_PLANET = 3;
const int NF_DESTINATION = 4;
const int NF_BATTLEPLAN = 5;
const int NF_SHIPCNT = 6;
const int NF_IRON = 7;
const int NF_BORA = 8;
const int NF_GERM = 9;
const int NF_COL = 10;
const int NF_FUEL = 11;
const int NF_OWNER = 12;
const int NF_ETA = 13;
const int NF_WARP = 14;
const int NF_MASS = 15;
const int NF_CLOAK = 16;
const int NF_SCAN = 17;
const int NF_PEN = 18;
const int NF_TASK = 19;
const int NF_MINING = 20;
const int NF_SWEEP = 21;
const int NF_LAYING = 22;
const int NF_TERRA = 23;
const int NF_UNARMED = 24;
const int NF_SCOUT = 25;
const int NF_WARSHIP = 26;
const int NF_UTILITY = 27;
const int NF_BOMBER = 28;


#define PRINT(a, b) _print(outf, (a), (b))
#define is_defined(x) (fields[x][0] && strcmp(fields[x], "0"))

void chomp(char* i)
{
  while (isspace(i[strlen(i)-1]))
    i[strlen(i)-1] = 0;
}


inline
void _print(FILE* outf, const char* a, const char* b)
{
  fprintf(outf, "\t%s %s\n", a, b);
}



void split_on_tabs(const char* in, char out[48][128])
{
  int i = 0;
  const char* p = in;
  char* o = out[0];

  while (*p)
    if (*p == '\t') {
      *o = 0;
      i++;
      o = out[i];
      p++;
    } else
      *o++ = *p++;

  *o = 0;
  i++;

  for (; i < 48; i++)
    out[i][0] = 0;
}


void munge_dquotes(char* t)
{
  for (; *t; t++)
    if (*t == '"')
      *t = '\'';
}


bool convert(const myString& infile, const myString& outfile)
{
  FILE* inf;
  FILE* outf;
  char inlin[1024];
  char fields[48][128];
  myString t;
  struct stat ifstats, ofstats;

  // check if we need to perform the conversion
  if (!stat(outfile, &ofstats)) {
    // file exists, check date
    if (stat(infile, &ifstats))
      return false;

    // if infile is older than outfile then no conversion is done
    if (ifstats.st_mtime < ofstats.st_mtime) {
      game_map->log(infile + " unchanged, no auto-conversion done\n");
      return true;
    }
  }

  if ( !(inf = fopen(infile, "r")) )
    return false;

  if ( !(outf = fopen(outfile, "w")) ) {
    fclose(inf);
    return false;
  }

  // write messages
  display->set_intro_loadingfile("Converting: " + infile + " ==> " + outfile);
  game_map->log("Performing conversion: " + infile + " ==> " + outfile + "\n");

  fgets(inlin, 1024, inf);
  chomp(inlin);

  split_on_tabs(inlin, fields);

  if (!strcmp(fields[0], "#")) {
    // universe report
    if (fields[4][0]) {
      // screwed-style report, handle 1st line (which is buggy :(
      split_on_tabs(inlin+11, fields);
    } else {
      fgets(inlin, 1024, inf);
      chomp(inlin);
      split_on_tabs(inlin, fields);
    }

    while (1) {
      fprintf(outf, "planet \"%s\" {\n", fields[MAP_PLANETNAME]);

      PRINT("starsid", fields[MAP_STARSID]);

      t = myString(fields[MAP_PLANETX]) + " " + fields[MAP_PLANETY];
      PRINT("position", t);

      fprintf(outf, "}\n\n");

      fgets(inlin, 1024, inf);      
      if (feof(inf))
	break;

      chomp(inlin);
      split_on_tabs(inlin, fields);     
    }
  } else if (!strcmp(fields[0], "Planet Name") && fields[NP_ROUTING][0]) {
    // new style planetary report
    while (1) {
      fgets(inlin, 1024, inf);

      if (feof(inf))
	break;

      chomp(inlin);
      split_on_tabs(inlin, fields);

      // paranoia check for " in race name
      munge_dquotes(fields[NF_OWNER]);

      fprintf(outf, "planet \"%s\" {\n", fields[NP_PLANETNAME]);

      if (is_defined(NP_OWNER)) {
	t = myString("\"") + fields[NP_OWNER] + "\"";
	PRINT("owner", t);
      }

      if (is_defined(NP_STARBASE)) {
	munge_dquotes(fields[NP_STARBASE]);

	if (is_defined(NP_PCTDMG)) {
	  t = myString("\"") + fields[NP_STARBASE] + "\" " + fields[NP_PCTDMG] +"%";
	} else {
	  t = myString("\"") + fields[NP_STARBASE] + "\" 0%";
	}

	if (is_defined(NP_GATERANGE)) {
	  t += myString(" ") + fields[NP_GATERANGE] + " " + fields[NP_GATEMASS];
	} else {
	  t += " 0 0";
	}

	if (is_defined(NP_DRIVER)) {
	  t += myString(" \"") + fields[NP_DRIVER] + "\" " + fields[NP_WARP];
	} else {
	  t += " \"\" 0";
	}

	PRINT("starbase", t);
      }

      if (is_defined(NP_REPORTAGE)) {
	PRINT("report_age", fields[NP_REPORTAGE]);
      }

      if (is_defined(NP_POPULATION)) {
	PRINT("population", fields[NP_POPULATION]);
      }

      if (is_defined(NP_VALUE)) {
	PRINT("habitability", myString(fields[NP_VALUE]) + "/" + fields[NP_TERRA]);
      }

      if (is_defined(NP_MINES)) {
	PRINT("installations", myString(fields[NP_MINES]) + " " + fields[NP_FACTORIES] + " -1");
      }

      if (is_defined(NP_DEFCOVERAGE)) {
	PRINT("def_coverage", fields[NP_DEFCOVERAGE]);
      }

      if (is_defined(NP_SURFIRON) || is_defined(NP_SURFBORA) || is_defined(NP_SURFGERM)) {
	t = myString(fields[NP_SURFIRON]) + " " + myString(fields[NP_SURFBORA]) +
	    " " + myString(fields[NP_SURFGERM]);
	PRINT("minerals", t);
      }

      if (is_defined(NP_CONCIRON)) {
	t = myString(fields[NP_CONCIRON]) + " " + myString(fields[NP_CONCBORA]) +
	    " " + myString(fields[NP_CONCGERM]);
	PRINT("mineral_conc", t);
      }

      if (is_defined(NP_GRAV)) {
	// clean them up
	fields[NP_GRAV][strlen(fields[NP_GRAV])-1] = 0;
	fields[NP_TEMP][strlen(fields[NP_TEMP])-2] = 0;
	fields[NP_RAD][strlen(fields[NP_RAD])-2] = 0;

	t = myString(fields[NP_GRAV]) + " " + myString(fields[NP_TEMP]) +
	    " " + myString(fields[NP_RAD]);
	PRINT("stats", t);
      }

      if (is_defined(NP_GRAVORIG)) {
	// clean them up
	fields[NP_GRAVORIG][strlen(fields[NP_GRAVORIG])-1] = 0;
	fields[NP_TEMPORIG][strlen(fields[NP_TEMPORIG])-2] = 0;
	fields[NP_RADORIG][strlen(fields[NP_RADORIG])-2] = 0;

	t = myString(fields[NP_GRAVORIG]) + " " + myString(fields[NP_TEMPORIG]) +
	    " " + myString(fields[NP_RADORIG]);
	PRINT("original_stats", t);
      }

      if (is_defined(NP_SCAN)) {
	t = myString(fields[NP_SCAN]) + " " + myString(fields[NP_PENSCAN]);
	PRINT("scanning", t);
      }

      if (is_defined(NP_ROUTING)) {
	t = "\"" + myString(fields[NP_ROUTING]) + "\"";
	PRINT("routing", t);
      }

      fprintf(outf, "}\n\n");
    }

  } else if (!strcmp(fields[0], "Fleet Name") && fields[NF_TERRA][0]) {
    // new style fleet report
    while (1) {
      fgets(inlin, 1024, inf);

      if (feof(inf))
	break;

      chomp(inlin);
      split_on_tabs(inlin, fields);

      // paranoia check for " in race name
      munge_dquotes(fields[NF_FNAME]);

      fprintf(outf, "fleet \"%s\" {\n", fields[NF_FNAME]);

      // put in all the stuff which is ALWAYS present
      if (is_defined(NF_PLANET)) {
	// planet overrides X/Y position
	t = myString("\"") + fields[NF_PLANET] + "\"";
	PRINT("position", t);
      } else {
	t = myString(fields[NF_X]) + " " + fields[NF_Y];
	PRINT("position", t);
      }

      // destination (if ship is not halted)
      myString dest(fields[NF_DESTINATION]);
      if (dest.length()) {
	vector<myString> dt;

	if (dest.matches(myRegexp("[0-9]+\\.[0-9]+"))) {
	  dt = dest.split(myString("."), 2);
	  t = int_to_str(atoi(dt[0])-127) + " " + int_to_str(atoi(dt[1])-127);
	  PRINT("destination", t);
	} else if (!dest.matches(myRegexp(" *-- *")) && dest != "(Delayed)") {
	  if (dest.matches(myRegexp("Space \\([0-9]+, [0-9]+\\)"))) {
	    dt = dest.at(8).split(myString(", "), 2);
	    t = int_to_str(atoi(dt[0])) + " " + int_to_str(atoi(dt[1]));
	    PRINT("destination", t);
	  } else {
	    t = "\"" + dest + "\"";
	    PRINT("destination", t);
	  }
	}
      }

      t = myString(fields[NF_SHIPCNT]) + " " + fields[NF_MASS];
      PRINT("ships", t);

      // fleet composition
      t = myString(fields[NF_UNARMED]) + " " + myString(fields[NF_SCOUT]) + " " +
	myString(fields[NF_WARSHIP]) + " " + myString(fields[NF_UTILITY]) + " " +
	myString(fields[NF_BOMBER]);

      // now check (and add) any additional info
      if (is_defined(NF_IRON) || is_defined(NF_BORA) || 
	  is_defined(NF_GERM) || is_defined(NF_COL)) {
	t = myString(fields[NF_IRON]) + " " + myString(fields[NF_BORA]) + " " +
	  myString(fields[NF_GERM]) + " " + myString(fields[NF_COL]);
	PRINT("cargo", t);
      }
      
      if (is_defined(NF_FUEL)) {
	PRINT("fuel", fields[NF_FUEL]);
      }

      if (is_defined(NF_WARP)) {
	PRINT("warp", fields[NF_WARP]);
      }

      // this is only included for cross-checks
      if (is_defined(NF_ETA)) {
	if (fields[NF_ETA][strlen(fields[NF_ETA] - 1)] == 'y') {
	  fields[NF_ETA][strlen(fields[NF_ETA] - 1)] = 0;
	  PRINT("starsETA", fields[NF_ETA]);
	}
      }

      if (is_defined(NF_CLOAK)) {
	PRINT("cloaking", fields[NF_CLOAK]);
      }

      if (is_defined(NF_SCAN)) {
	t = myString(fields[NF_SCAN]) + " " + fields[NF_PEN];
	PRINT("scanning", t);
      }

      // not clear if I'll ever use these
      if (is_defined(NF_BATTLEPLAN)) {
	t = myString("\"") + fields[NF_BATTLEPLAN] + "\"";
	PRINT("battleplan", t);
      }

      if (is_defined(NF_TASK)) {
	t = myString("\"") + fields[NF_TASK] + "\"";
	PRINT("wp_task", t);
      }

      if (is_defined(NF_MINING)) {
	PRINT("mining", fields[NF_MINING]);
      }

      if (is_defined(NF_MINING)) {
	PRINT("mining", fields[NF_MINING]);
      }

      if (is_defined(NF_SWEEP) || is_defined(NF_LAYING)) {
	t = myString(fields[NF_LAYING]) + " " + fields[NF_SWEEP];
	PRINT("minefield_ls", t);
      }

      if (is_defined(NF_TERRA)) {
	PRINT("terraforming", fields[NF_TERRA]);
      }

      fprintf(outf, "}\n\n");
    }
  } else {
    fclose(inf);
    fclose(outf);
    return false;
  }

  fclose(inf);
  fclose(outf);
  return true;
}



// a "c++" conversion of starstat.c to automatically take the info from files
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define dtXY   0
#define dtLog  1
#define dtHost 2
#define dtTurn 3
#define dtHist 4
#define dtRace 5
#define dtMax  6

#define rtBOF  8  // Begining Of File Record Type

typedef struct _rtbof
{
  char rgid[4];       // Magic number: "J3J3"
  long lidGame;        // Game ID
	
  unsigned short verInc   : 5,    // 1.04c
                 verMinor : 7,    // 1.04
                 verMajor : 4;    // 1.00

  unsigned short turn;
  short iPlayer:5,
        lSaltTime:11;  // Encryption salt

    unsigned short dt         : 8, // File type dtXY, dtHost, dtLog, dtHist etc.
                   fDone      : 1, // Player has submitted this turn (dtLog only).
                   fInUse     : 1, // Host instance is using this file (dtHost, dtTurn).
                   fMulti     : 1, // Multiple turns in this file (dtTurn only).
                   fGameOver  : 1, // A winner has been declared
                   fShareware : 1, // The shareware version
                   unused     : 3;
} RTBOF;

typedef struct _hdr
{
  unsigned short cb : 10,  // Size of the record in bytes not counting this header.
                 rt :  6;  // Record Type (rtBOF etc)
} HDR;

char *szMagic = "J3J3";

char *rgszdt[7] = { "Universe Definition File", 
		    "Player Log File",
		    "Host File",
		    "Player Turn File",
                    "Player History File",
		    "Race Definition File",
		    "Unknown File" };
                    

bool starstat(const char* fn, _starstat* sfi)
{
  FILE *in;
  short w;
  HDR hdr;
  RTBOF rtbof;

  in = fopen(fn, "rb");
  if (!in)
    return false;

  if (fread(&hdr, 1, sizeof(HDR), in) != sizeof(HDR) || hdr.rt != rtBOF
      || hdr.cb < sizeof(RTBOF) || fread(&rtbof, 1, sizeof(RTBOF), in) != sizeof(RTBOF)
      || strncmp(szMagic, &rtbof.rgid[0], 4) || rtbof.dt >= dtMax) {
    fclose(in);
    return false;
  }

  sfi->verMajor = rtbof.verMajor;
  sfi->verMinor = rtbof.verMinor;
  sfi->verInc = rtbof.verInc;
  sfi->InUse = rtbof.fInUse;
  sfi->idGame = rtbof.lidGame;
  sfi->dt = rtbof.dt;

  switch (rtbof.dt) {
  case dtLog:
  case dtHost:
  case dtTurn:
    sfi->turn = rtbof.turn + 2400;
    if (rtbof.dt == dtTurn && rtbof.fMulti) {
      fseek(in, -2, SEEK_END);
      fread(&w, 1, 2, in);
      sfi->endturn = w + 2400;
    } else
      sfi->endturn = sfi->turn;

    sfi->GameOver = rtbof.fGameOver;

    if (rtbof.iPlayer != -1) {
      sfi->Player = rtbof.iPlayer+1;
      sfi->Shareware = rtbof.fShareware;
      if (rtbof.dt == dtLog && rtbof.fDone)
	sfi->Done = rtbof.fDone;
    }
    break;
  }
  
  fclose(in);
  return true;
}

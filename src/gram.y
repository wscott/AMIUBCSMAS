%{
#include "starana-classes.h"
#include <string.h>
#include <malloc.h>

extern int yylex(void);
int yyerror(char* s);
void check_auth_source(const char* item);
void check_defined_source(const char* item);
void add_to_someones_queue(const bool a, const String& n, const int c, const int act = 0, const int deact = SIM_FUTURE);

int r_source, r_age;
planet* curr_planet = NULL;
race* curr_race = NULL;
fleet* curr_fleet = NULL;
object* curr_object = NULL;

%}

%union{
  char* y_str;
  int y_int;
  double y_dbl;
  bool y_boo;
  int y_col[3];
};

%type  <y_col> colorspec
%type  <y_dbl> expr
%type  <y_boo> opt_autobuild

%token <y_int> INTEGER
%token <y_dbl> NUMBER
%token <y_str> STRING

%token LBRACE RBRACE LPARE RPARE COMMA CAT ASSIGN SOURCE PLURAL
%token RACE PLANET OWNER ORIGINAL_STATS STATS MINERAL_CONC MINERALS
%token POPULATION INSTALLATIONS POSITION RT HIMMUNE DEFCOVERAGE
%token HABITABILITY COL_RES GROWTH FACTORIES MINES TECH_COST
%token TECH MIN_POP_MOVE MINE_YEARS HOMEWORLD ALLIANCE SCAN
%token AUTOBUILD QUEUE CLONE DOLLAR SIMFUTURE MAXZOOM STARSID
%token UNIVERSE YEAR WFUNCTION RELIABILITY PERCENT STARBASE REPORTAGE
%token ANALYZE PNEWCOLONY PBREEDER PPRODUCTION PLOOT PGENERIC PMINING
%token SHIPS FLEET FUEL CARGO DESTINATION OBJECT RESOURCES
%token WAYPOINTTASK STARSETA BATTLEPLAN WARP MINELAYSWEEP CLOAKING
%token TFORMING PLANETVIEW ROUTING COMPOSITION FLEETVIEW COLOR
%token MAXPIERADIUS

%left  PLUS MINUS
%left  MULTIPLY DIVIDE
%right RAISE
%left  UMINUS

%%

input: /* NULL */
    {
      /* yydebug = 1; */
      infile_lineno = 1;
      r_source = -1;
      r_age = 0;
    }
    | input SOURCE STRING
    {
      r_source = game_map->find_race(String($3))->id;
      r_age = 0;

      free($3);
    }
    | input SOURCE STRING expr
    {
      r_source = game_map->find_race(String($3))->id;
      r_age = (int)$4;

      free($3);
    }
    | input STRING ASSIGN STRING
    {
      new parameter(String($2), String($4));
      free($2);
      free($4);
    }
    | input STRING ASSIGN expr
    {
      new parameter(String($2), $4);
      free($2);
    }
    | input PLANET STRING
         {
	   curr_planet = game_map->grab_planet(String($3));
	 }
           LBRACE planetspec RBRACE
    {
      free($3);
      curr_planet = NULL;
    }
    | input UNIVERSE STRING
         {
	   game_map->game_name = String($3);
	 }
           LBRACE universespec RBRACE
    {
      free($3);
    }
    | input RACE STRING 
         {
	   curr_race = game_map->add_race(String($3));
	 }
           LBRACE racespec RBRACE
    {
      curr_race->check_data(game_map->report_log);
      free($3);
      curr_race = NULL;
    }
    | input FLEET STRING 
         {
	   curr_fleet = new fleet(String($3));
	 }
           LBRACE fleetspec RBRACE
    {
      game_map->add_fleet(curr_fleet, r_source);
      free($3);
      curr_fleet = NULL;
    }
    | input ALLIANCE STRING 
         {
	   game_map->create_alliance(String($3));
	 }
           LBRACE alliancespec RBRACE
    {
      free($3);
    }
    | input PLANETVIEW STRING
         {
	   mapview->clone_planet_view(NULL);
	   mapview->get_planet_view()->name = String($3);
	 } 
           LBRACE pfunclist RBRACE
    {
      free($3);
    }
    | input FLEETVIEW STRING
         {
	 } 
           LBRACE ffunclist RBRACE
    {
    }
    ;

universespec: /* NULL */
    | universespec SIMFUTURE expr
    {
      game_map->actual_sim_future = (int)$3;
    }
    | universespec MAXZOOM expr
    {
      game_map->max_zoom = (int)$3;
    }
    | universespec MAXPIERADIUS expr
    {
      set_max_pie_radius((int)$3);
    }
    | universespec YEAR expr
    {
      game_map->game_year = (int)$3;
    }
    | universespec YEAR STRING
    {
      _starstat sfi;

      String sfn($3);
      sfn = infile_path + sfn;

      // use starstat to get year
      if (starstat(sfn, &sfi)) {
	game_map->game_year = sfi.endturn;
      } else
	yyerror("Unable to ready year from file");

      free($3);
    }
    | universespec WFUNCTION expr
    {
      switch ((int)$3) {
      case 160:
	game_map->wfunc = wfunc_160;
	game_map->wfrange = 160;
	break;

      case 200:
	game_map->wfunc = wfunc_200;
	game_map->wfrange = 200;
	break;

      case 250:
	game_map->wfunc = wfunc_250;
	game_map->wfrange = 250;
	break;

      default:
	game_map->wfunc = wfunc_160;
	game_map->wfrange = 160;
	break;
      }
    }
    | universespec COLOR univcolorspec
    ;

univcolorspec:
      MINERALS colorspec colorspec colorspec
    {
      set_colormap_color(COL_IRON, $2[0], $2[1], $2[2]);
      set_colormap_color(COL_BORA, $3[0], $3[1], $3[2]);
      set_colormap_color(COL_GERM, $4[0], $4[1], $4[2]);
    }
    | SCAN colorspec colorspec
    {
      set_colormap_color(COL_SCAN, $2[0], $2[1], $2[2]);
      set_colormap_color(COL_PENSCAN, $3[0], $3[1], $3[2]);
    }
    ;

planetspec: /* NULL */
    | planetspec HOMEWORLD
    {
      curr_planet->homeworld = true;
    }
    | planetspec PNEWCOLONY
    {
      curr_planet->p_type = planet::NEWCOLONY;
    }
    | planetspec PBREEDER
    {
      curr_planet->p_type = planet::BREEDER;
    }
    | planetspec PPRODUCTION
    {
      curr_planet->p_type = planet::PRODUCTION;
    }
    | planetspec PLOOT
    {
      curr_planet->p_type = planet::LOOTING;
    }
    | planetspec PGENERIC
    {
      curr_planet->p_type = planet::GENERIC;
    }
    | planetspec PMINING
    {
      curr_planet->p_type = planet::MINING;
    }
    | planetspec OWNER STRING
    {
      check_defined_source("planet owner");

      race* r = game_map->find_race(String($3));

      if (r->race_id() == r_source) {
	if (curr_planet->auth_source != -1) /* we have multiple auth sources */
	  game_map->log(curr_planet->name() +
			String(": MULTIPLE AUTH SOURCES?? (old=") +
			game_map->find_race(curr_planet->auth_source)->name() +
			String(" / new=") +
			r->name() +
			String(") new will be used\n"));

	curr_planet->auth_source = r->race_id();
      }

      curr_planet->r_owner[r_source] = r;

      free($3);
    }
    | planetspec STARSID expr
    {
      curr_planet->stars_id = (int)$3;
    }
    | planetspec HABITABILITY expr PERCENT DIVIDE expr PERCENT
    {
      check_defined_source("habitability");

      curr_planet->r_hab[r_source] = (int)$3;
      curr_planet->r_mxhab[r_source] = (int)$6;
    }
    | planetspec REPORTAGE expr
    {
      check_defined_source("report_age");

      curr_planet->r_age[r_source] = (int)$3 + r_age;
    }
    | planetspec STARBASE STRING expr PERCENT expr expr STRING expr
    {
      check_defined_source("starbase");

      curr_planet->r_starbase[r_source] = String($3);

      /* these can only come from auth source.... */
      if (curr_planet->r_owner[r_source] &&
	  curr_planet->r_owner[r_source]->id == r_source) {
	curr_planet->stb_damage = (int)$4;
	curr_planet->gaterange = (int)$6;
	curr_planet->gatemass = (int)$7;
	curr_planet->driverdest = game_map->find_planet(String($8));
	curr_planet->driverwarp = (int)$9;
      }

      free($3);
    }
    | planetspec SCAN expr expr
    {
      check_auth_source("scanning");

      curr_planet->scan_normal = (int)$3;
      curr_planet->scan_pen = (int)$4;
    }
    | planetspec ORIGINAL_STATS expr expr expr
    {
      check_defined_source("planet ori_stats");

      if (!curr_planet->set_reported_oristats(r_source, $3, $4, $5))
	game_map->log(curr_planet->name() + ": ambiguous grav value resolved as maximum\n");
    }
    | planetspec STATS expr expr expr
    {
      check_defined_source("planet stats");

      if (!curr_planet->set_reported_stats(r_source, $3, $4, $5))
	game_map->log(curr_planet->name() + ": ambiguous grav value resolved as maximum\n");
    }
    | planetspec MINERAL_CONC expr expr expr
    {
      check_defined_source("planet mineral_conc");

      curr_planet->r_minconc[r_source].iron = (int)$3;
      curr_planet->r_minconc[r_source].bora = (int)$4;
      curr_planet->r_minconc[r_source].germ = (int)$5;
    }
    | planetspec MINE_YEARS expr expr expr
    {
      check_auth_source("planet mine_years");

      curr_planet->mine_year[0].iron = (int)$3;
      curr_planet->mine_year[0].bora = (int)$4;
      curr_planet->mine_year[0].germ = (int)$5;
    }
    | planetspec MINERALS expr expr expr
    {
      check_defined_source("planet minerals");
      // not authoritative because of remote mining sites

      curr_planet->_mineral[0].iron = (int)$3;
      curr_planet->_mineral[0].bora = (int)$4;
      curr_planet->_mineral[0].germ = (int)$5;
    }
    | planetspec POPULATION expr
    {
      check_defined_source("planet pop");

      curr_planet->r_pop[r_source] = (int)$3;
    }
    | planetspec INSTALLATIONS expr expr expr
    {
      check_auth_source("planet installations");

      curr_planet->_mines[0] = (int)$3;
      curr_planet->_factories[0] = (int)$4;
      curr_planet->_defenses[0] = (int)$5;
    }
    | planetspec DEFCOVERAGE expr PERCENT
    {
      check_defined_source("def coverage%");

      curr_planet->def_coverage[0] = (int)(100 * $3);
    }
    | planetspec POSITION expr expr
    {
      curr_planet->pos.x = (int)$3;
      curr_planet->pos.y = (int)$4;
    }
    | planetspec QUEUE 
                   {
		     check_auth_source("queue");
		   } 
                     LBRACE queuespec RBRACE
    {
      // do nothing
    }
    | planetspec ROUTING STRING
    {
      curr_planet->routing = game_map->find_planet(String($3));
    }
    ;

queuespec: /* NULL */
    | queuespec opt_autobuild STRING expr
    {
      add_to_someones_queue($2, String($3), (int)$4);
      free($3);
    }
    | queuespec PLUS INTEGER opt_autobuild STRING expr
    {
      add_to_someones_queue($4, String($5), (int)$6, $3);
      free($5);
    }
    | queuespec MINUS INTEGER opt_autobuild STRING expr
    {
      add_to_someones_queue($4, String($5), (int)$6, 0, $3);
      free($5);
    }
    | queuespec PLUS INTEGER MINUS INTEGER opt_autobuild STRING expr
    {
      add_to_someones_queue($6, String($7), (int)$8, $3, $5);
      free($7);
    }
    ;

opt_autobuild: /* NULL */
    {
      $$ = false;
    }
    | AUTOBUILD
    {
      $$ = true;
    }
    ;    

racespec: /* NULL */
    | racespec RT prtspec LPARE lrtspec RPARE
    {
      // do nothing
    }
    | racespec CLONE STRING
    {
      race* r = game_map->find_race(String($3));

      if (!r)
	yyerror("unknown race");

      /* dup significant values (i.e. all) */
      curr_race->_names = r->_names;
      curr_race->_prt = r->_prt;
      memcpy(curr_race->lrt_tab, r->lrt_tab, sizeof(r->lrt_tab));
      memcpy(curr_race->hab_min, r->hab_min, sizeof(r->hab_min));
      memcpy(curr_race->hab_max, r->hab_max, sizeof(r->hab_max));
      curr_race->col_res = r->col_res;
      curr_race->col_grow = r->col_grow;
      curr_race->fact_res  = r->fact_res;
      curr_race->fact_cost = r->fact_cost;
      curr_race->fact_ctrl = r->fact_ctrl;
      curr_race->fact_germ = r->fact_germ;
      curr_race->mine_eff = r->mine_eff;
      curr_race->mine_cost = r->mine_cost;
      curr_race->mine_ctrl = r->mine_ctrl;
      strcpy(curr_race->tech_cost, r->tech_cost);
      memcpy(curr_race->tech, r->tech, sizeof(r->tech));
      curr_race->min_pop_move = r->min_pop_move;
    }
    | racespec PLURAL STRING
    {
      curr_race->_names = String($3);
      free($3);
    } 
    | racespec COLOR colorspec
    {
      set_colormap_color(COL_RACES + curr_race->race_id()*4,
			 $3[0], $3[1], $3[2]);
    }
    | racespec ANALYZE
    {
      curr_race->can_analyze = true;
    }
    | racespec HABITABILITY gravhabspec temphabspec radhabspec
    {
      // do nothing
    }
    | racespec COL_RES expr
    {
      curr_race->col_res = (int)$3;
    }
    | racespec GROWTH expr
    {
      curr_race->col_grow = (int)$3;
    }
    | racespec FACTORIES expr expr expr expr
    {
      curr_race->fact_res = (int)$3;
      curr_race->fact_cost = (int)$4;
      curr_race->fact_ctrl = (int)$5;
      curr_race->fact_germ = (int)$6;
    }
    | racespec MINES expr expr expr
    {
      curr_race->mine_eff = (int)$3;
      curr_race->mine_cost = (int)$4;
      curr_race->mine_ctrl = (int)$5;
    }
    | racespec TECH_COST STRING
    {
      strncpy(curr_race->tech_cost, $3, 6);
      free($3);
    }
    | racespec TECH expr expr expr expr expr expr
    {
      curr_race->tech[0][0] = (int)$3;
      curr_race->tech[0][1] = (int)$4;
      curr_race->tech[0][2] = (int)$5;
      curr_race->tech[0][3] = (int)$6;
      curr_race->tech[0][4] = (int)$7;
      curr_race->tech[0][5] = (int)$8;
    }
    | racespec MIN_POP_MOVE expr
    {
      curr_race->min_pop_move = (int)$3;
    }
    | racespec RELIABILITY expr
    {
      curr_race->reliab = (int)$3;
    }
    | racespec OBJECT STRING
                {
		  curr_object = new object(String($3));
	        }
               LBRACE objectspec RBRACE
    {
      curr_object->next = curr_race->object_table;
      curr_race->object_table = curr_object; 
      free($3);
    }
    | racespec QUEUE
                 {
		   // make sure that factory/mine/stuff are available
		   curr_race->set_minimal_objects();
		 }
			LBRACE queuespec RBRACE
    {
      /* do nothing */
    }
    ;

objectspec: /* NULL */
    | objectspec RESOURCES expr
    {
      curr_object->res = (int)$3;
    }
    | objectspec MINERALS expr expr expr
    {
      curr_object->min.iron = (int)$3;
      curr_object->min.bora = (int)$4;
      curr_object->min.germ = (int)$5;
    }
    ;

gravhabspec: expr DIVIDE expr 
    {
      if (!guess_gravity(&curr_race->hab_min[Grav], &curr_race->hab_max[Grav], $1, $3))
	yyerror("invalid gravity range");
    }
    | HIMMUNE
    {
      curr_race->hab_min[Grav] = -1;
      curr_race->hab_max[Grav] = -1;
    }
    ;

temphabspec: expr DIVIDE expr 
    {
      if ($1 < -200 || $1 > 200 || $3 < -200 || $3 > 200 ||
	  $3 < $1 || ((int)(($3 - $1) / 4) % 2) )
	yyerror("invalid temperature range");

      curr_race->hab_min[Temp] = ((int)$1 + 200) / 4;
      curr_race->hab_max[Temp] = ((int)$3 + 200) / 4;
    }
    | HIMMUNE
    {
      curr_race->hab_min[Temp] = -1;
      curr_race->hab_max[Temp] = -1;
    }
    ;

radhabspec: expr DIVIDE expr 
    {
      if ($1 < 0 || $1 > 100 || $3 < 0 || $3 > 100 ||
	  $3 < $1 || ((int)($3 - $1) % 2) )
	yyerror("invalid radiation range");

      curr_race->hab_min[Rad] = (int)$1;
      curr_race->hab_max[Rad] = (int)$3;
    }
    | HIMMUNE
    {
      curr_race->hab_min[Rad] = -1;
      curr_race->hab_max[Rad] = -1;
    }
    ;

fleetspec: /* NULL */
    | fleetspec POSITION expr expr
    {
      curr_fleet->pos[0].x = (int)$3;
      curr_fleet->pos[0].y = (int)$4;
    }
    | fleetspec POSITION expr
    {
      /* positioning from planet id # */
      planet* p = game_map->find_planet((int)$3);

      if (!p)
	game_map->log(curr_fleet->_name + ": fleet stationed at unknown planet?!?\n");
      else
	curr_fleet->pos[0] = p->position();
    }
    | fleetspec POSITION STRING
    {
      planet* p = game_map->find_planet(String($3));

      if (!p)
	game_map->log(curr_fleet->_name + ": fleet stationed at unknown planet?!?\n");
      else
	curr_fleet->pos[0] = p->position();

      free($3);
    }
    | fleetspec SHIPS expr expr
    {
      curr_fleet->n_ships = (int)$3;
      curr_fleet->mass = (int)$4;
    }
    | fleetspec COMPOSITION expr expr expr expr expr
    {
      curr_fleet->n_unarmed = (int)$3;
      curr_fleet->n_scout = (int)$4;
      curr_fleet->n_warship = (int)$5;
      curr_fleet->n_utility = (int)$6;
      curr_fleet->n_bomber = (int)$7;
    }
    | fleetspec FUEL expr
    {
      curr_fleet->fuel = (int)$3;
    }
    | fleetspec CARGO expr expr expr expr
    {
      curr_fleet->min.iron = (int)$3;
      curr_fleet->min.bora = (int)$4;
      curr_fleet->min.germ = (int)$5;
      curr_fleet->pop = (int)$6;
    }
    | fleetspec DESTINATION expr expr
    {
      curr_fleet->pos[1].x = (int)$3;
      curr_fleet->pos[1].y = (int)$4;
    }
    | fleetspec DESTINATION STRING
    {
      planet* p = game_map->find_planet(String($3));

      if (!p) {
	game_map->log(curr_fleet->_starsname + ": fleet travelling to " + $3 + " - no idea what to do...\n");

      } else {
	curr_fleet->pos[1] = p->position();

	/* set the destination */
	curr_fleet->destin = p;
      }

      free($3);
    }
    | fleetspec WAYPOINTTASK STRING
    {
      curr_fleet->wptask_name = *$3;
      free($3);
    }
    | fleetspec BATTLEPLAN STRING
    {
      curr_fleet->battleplan_name = *$3;
      free($3);
    }
    | fleetspec STARSETA expr
    {
      curr_fleet->starsETA = (int)$3;
    }
    | fleetspec WARP expr
    {
      curr_fleet->warp = (int)$3;
    }
    | fleetspec SCAN expr expr
    {
      curr_fleet->scan_normal = (int)$3;
      curr_fleet->scan_pen = (int)$4;
    }
    | fleetspec CLOAKING expr
    {
      curr_fleet->cloaking = (int)$3;
    }
    | fleetspec TFORMING expr
    {
      curr_fleet->terraforming = (int)$3;
    }
    | fleetspec PMINING expr
    {
      curr_fleet->remote_mining = (int)$3;
    }
    | fleetspec MINELAYSWEEP expr expr
    {
      curr_fleet->minelaying = (int)$3;
      curr_fleet->minesweeping = -(int)$4;
    }
    ;

alliancespec: /* NULL */
    | alliancespec RACE STRING
    {
      game_map->add_to_alliance(String($3));
      free($3);
    }


prtspec: STRING
    {
      String p($1);
      int i;

      for (i = 0; i < 10; i++)
	if (p == race::prt_names[i]) {
	  curr_race->_prt = (prt_type)i;
	  break;
	}

      if (i == 10)
	yyerror("unknown prt");

      free($1);
    }
    ;

lrtspec: /* NULL */
    | lrtspec STRING
    {
      String p($2);
      int i;

      for (i = 0; i < 14; i++)
	if (p == race::lrt_names[i]) {
	  curr_race->lrt_tab[i] = true;
	  break;
	}

      if (i == 14)
	yyerror("unknown lrt");

      free($2);
    }
    ;


ffunclist: /* NULL */
    ;

pfunclist: /* NULL */
    | pfunclist INTEGER STRING INTEGER STRING INTEGER INTEGER INTEGER INTEGER INTEGER
    {
      if (mapview) {
	int params[16];
	int i, mask;

	params[0] = $6;
	params[1] = $7;
	params[2] = $8;
	params[3] = $9;
	params[4] = $10;
	for (i = 5; i < 16; i++)
	  params[i] = 0;

	// generate mask
	     mask = 0;
	mask |= strchr($5, 'C')? PF_CIRCLES : 0;
	mask |= strchr($5, 'L')? PF_LINES : 0;
	mask |= strchr($5, 'D')? PF_DATA : 0;
	mask |= strchr($5, 'M')? PF_MARKER : 0;
	mask |= strchr($5, 'N')? PF_NAME : 0;
	mask |= strchr($5, 'F')? PF_FLAG : 0;

	mapview->select_plamode($2);
	mapview->set_plamode($3, (_pfmode)$4, mask, params);

	free($3);
	free($5);
      }
    }
    ;

colorspec: LPARE expr COMMA expr COMMA expr RPARE
    {
      $$[0] = (int)$2;
      $$[1] = (int)$4;
      $$[2] = (int)$6;
    }
    ;

expr: INTEGER
    {
      $$ = (double)$1;
    }
    | NUMBER
    {
         $$ = $1;
    }
/*    | LPARE mathexpr RPARE
    {
         $$ = $2;
    } */
    | DOLLAR STRING
    {
      parameter* p = get_parameter(String($2));

      if (!p)
	yyerror("undefined parameter");

      $$ = (double)*p;
      free($2);
    }
    ;

%%


void check_defined_source(const char* item)
{
  if (r_source == -1) {
    char str[512];
    
    sprintf(str, "%s definition requires a data source", item);
    yyerror(str);
  }

  if (curr_planet->r_age[r_source] == 10000)
    curr_planet->r_age[r_source] = 0;
}


void check_auth_source(const char* item)
{
  if (r_source == -1 || curr_planet->auth_source == -1) {
    char str[512];
    
    sprintf(str, "%s definition can only come from planet owner", item);
    yyerror(str);
  }
}



void add_to_someones_queue(const bool a, const String& n, const int c,
			   const int act, const int deact)
{
  bool success;

  if (curr_planet)
    success = curr_planet->add_to_queue(a, n, c, act, deact);
  else if (curr_race)
    success = curr_race->add_to_default_queue(a, n, c, act, deact);
  else
    yyerror("queue defined outside planet or race?!?");

  if (!success) {
    char tmsg[512];

    sprintf(tmsg, "trying to build unknown object %s", (const char*)n);
    yyerror(tmsg);
  }
}



int yyerror(char* s)
{
  char str[256];

  sprintf(str, "yacc: %s:%d: %s\n", (const char*)infile_name, infile_lineno, s);
  game_map->log(String(str));

  if (fully_visual)
    display->error_dialog(str);
  else
    fprintf(stderr, str);

  delete game_map;

  exit(-1);
  return -1;
}

%{

#include "starana-classes.h"

#include "gram.h"

#include <ctype.h>

#define yywrap() 1
#define MAX_INCLUDE_DEPTH 10
YY_BUFFER_STATE include_stack[MAX_INCLUDE_DEPTH];
int include_stack_line[MAX_INCLUDE_DEPTH];
myString include_stack_infile[MAX_INCLUDE_DEPTH];
int include_stack_ptr = 0;

void begin_include_file(const char* fname);
%}

%%

[ \t]               ;

"\n"                infile_lineno++;

"{"                 return (LBRACE);

"}"                 return (RBRACE);

"="                 return (ASSIGN);

"@"                 return (CAT);

"$"                 return (DOLLAR);

","                 return (COMMA);

"\""                {
                         char c, *t, tstr[512];
                         t = tstr;

                         while ( '"' != (c = yyinput()) ) {
                              if (c == '\n') {
                                   infile_lineno++;

                                   while (isspace(c))
                                        c = yyinput();

                                   if (c == '"')
                                        break;

                                   *(t++) = ' ';
                              }

                              if (c == EOF)
				yyerror("EOF in quoted string");

                              *(t++) = c;
                         }

                         *t = 0;
                         yylval.y_str = (char *)malloc(strlen(tstr) + 1);
                         strcpy(yylval.y_str, tstr);

                         return (STRING);
                    }

"/*"                {
                         char c, oc;

                         oc = yyinput();
                         c = yyinput();

                         while (oc != '*' || c != '/') {

                              if (oc == '\n')
                                   infile_lineno++;

                              if (oc == EOF)
                                   yyerror("EOF in comment");

                              oc = c;
                              c = yyinput();
                         }
                    }

universe	    return (UNIVERSE);

year		    return (YEAR);

max_zoom	    return (MAXZOOM);

color		    return (COLOR);

maxpieradius	    return (MAXPIERADIUS);

displayresolution   return (DISPLAYRESOLUTION);

sim_future	    return (SIMFUTURE);

weight_function	    return (WFUNCTION);

source		    return (SOURCE);

race		    return (RACE);

do_analysis	    return (ANALYZE);

plural		    return (PLURAL);

reliability	    return (RELIABILITY);

alliance	    return (ALLIANCE);

planet		    return (PLANET);

starsid		    return (STARSID);

owner               return (OWNER);

report_age	    return (REPORTAGE);

new_colony	    return (PNEWCOLONY);

breeder		    return (PBREEDER);

production	    return (PPRODUCTION);

loot		    return (PLOOT);

generic	            return (PGENERIC);

mining              return (PMINING);

starbase            return (STARBASE);

scanning	    return (SCAN);

homeworld	    return (HOMEWORLD);

original_stats      return (ORIGINAL_STATS);

stats               return (STATS);

mineral_conc        return (MINERAL_CONC);

mine_years          return (MINE_YEARS);

minerals            return (MINERALS);

resources	    return (RESOURCES);

population          return (POPULATION);

installations       return (INSTALLATIONS);

def_coverage        return (DEFCOVERAGE);

position            return (POSITION);

clone               return (CLONE);

rt                  return (RT);

habitability        return (HABITABILITY);

immune	  	    return (HIMMUNE);

col_res             return (COL_RES);

growth              return (GROWTH);

factories           return (FACTORIES);

mines               return (MINES);

tech_cost           return (TECH_COST);

tech                return (TECH);

min_pop_move        return (MIN_POP_MOVE);

queue		    return (QUEUE);

routing		    return (ROUTING);

object		    return (OBJECT);

autobuild	    return (AUTOBUILD);

fleet		    return (FLEET);

ships		    return (SHIPS);

composition	    return (COMPOSITION);

fuel		    return (FUEL);

cargo		    return (CARGO);

destination         return (DESTINATION);

wp_task		    return (WAYPOINTTASK);

starsETA	    return (STARSETA);

warp		    return (WARP);

battleplan	    return (BATTLEPLAN);

minefield_ls	    return (MINELAYSWEEP);

cloaking	    return (CLOAKING);

terraforming	    return (TFORMING);

design		    return (DESIGN);

hull		    return (HULL);

mass		    return (MASS);

engine		    return (ENGINE);

planet_view	    return (PLANETVIEW);

fleet_view	    return (FLEETVIEW);

"%"                 return (PERCENT);

"("                 return (LPARE);

")"                 return (RPARE);

"+"                 return (PLUS);

"-"                 return (MINUS);

"*"                 return (MULTIPLY);

"/"                 return (DIVIDE);

"^"                 return (RAISE);

include\ .+         {
                      if ( include_stack_ptr >= MAX_INCLUDE_DEPTH )
			yyerror("Includes nested too deeply");

		      myString incl(yytext);
		      vector<myString> fns;

		      fns = incl.split(myRegexp::RXwhite, 2);

		      /* check path */
		      if (fns[1][0] != '/')
			fns[1] = infile_path + fns[1];

		      begin_include_file(fns[1]);
                    }

starsinclude\ .+    {
                      if ( include_stack_ptr >= MAX_INCLUDE_DEPTH )
			yyerror("Includes nested too deeply");

		      /* separate the two names (3?) */
		      myString incl(yytext);
		      vector<myString> fns;

		      fns = incl.split(myRegexp::RXwhite, 4);

		      /* check path */
		      if (fns[1][0] != '/')
			fns[1] = infile_path + fns[1];
		      if (fns[2][0] != '/')
			fns[2] = infile_path + fns[2];

		      // perform the conversion on the fly
		      if (!convert(fns[2], fns[1]))
			yyerror("Error performing conversion");

		      begin_include_file(fns[1]);
                    }

<<EOF>>             {
                      if (--include_stack_ptr < 0) {
			yyterminate();

		      } else {
			yy_delete_buffer(YY_CURRENT_BUFFER);
			yy_switch_to_buffer(include_stack[include_stack_ptr]);

			infile_name = include_stack_infile[include_stack_ptr];
			infile_lineno = include_stack_line[include_stack_ptr];

			// notify user
		        if (do_display)
			  display->set_intro_loadingfile("Loading file: " + infile_name);
		      }
                    }

-?[0-9]+            {
                      yylval.y_int = atoi(yytext);

                      return (INTEGER);
                    }

[0-9]*(\.[0-9]*)?((e|E)[+-]?[0-9]+)?  {
                      yylval.y_dbl = atof(yytext);

		      return (NUMBER);
                    }

[A-Za-z][A-Za-z0-9_.]* {
                      yylval.y_str = (char *)malloc(strlen(yytext) + 1);
                      strcpy(yylval.y_str, yytext);

                      return (STRING);
                    }

%%


void restart_flex(FILE* f)
{	
  yyrestart(f);
}

void begin_include_file(const char* fname)
{
  include_stack[include_stack_ptr] = YY_CURRENT_BUFFER;
  include_stack_line[include_stack_ptr] = infile_lineno;
  include_stack_infile[include_stack_ptr] = infile_name;
  include_stack_ptr++;
  infile_lineno = 1;
  infile_name = fname;

  yyin = fopen(fname, "r" );

  if (!yyin)
    yyerror("Include file not found");

  // notify user
  if (do_display)
    display->set_intro_loadingfile("Loading file: " + infile_name);

  yy_switch_to_buffer(yy_create_buffer(yyin, YY_BUF_SIZE));
}

#include "starana-classes.h"



#ifdef DEFAULT_FULLYVISUAL
bool fully_visual = true;
#else
bool fully_visual = false;
#endif
bool do_display = true;


int report_log_filter = 0
//    RLO_ERROR
//  | RLO_HABTABLE
//  | RLO_DATASRC
//  | RLO_EMPIRETOT
  | RLO_FLEETDUP
//  | RLO_PLAREPORTS
//  | RLO_PLABUILD
//  | RLO_PLASTATS
//  | RLO_PLAFLEETS
//  | RLO_PLAMINSTAT
//  | RLO_PLAPOPSTAT
//  | RLO_PLANETINI
  | RLO_FLEETDEST
//  | RLO_FLEETTRANS
//  | RLO_FLEETCOLON
//  | RLO_FLEETATTK
  | RLO_FLEETPARSE
//  | RLO_FLEETCONS
//  | RLO_PLAQUEUE
//  | RLO_PLAABUILD
    ;



void usage(void)
{
  puts("StarAna "+STARANA_VERSION+" -- "+STARANA_RELDATE+" -- usage:\n");
  puts("starana [-a] [-v] [master .smf file]\n");
  puts("-a    just generate report-log and quit\n");
  puts("-v    open a window to ask for the master file\n");
  exit(-1);
}



int main(int argc, char** argv)
{
  myString starsmf_file;
  int i;

  // simplify life to windog users
  if (!getenv("DISPLAY"))
    setenv("DISPLAY", "localhost:0.0", 0);

  for (i = 1; i < argc; i++)
    if (argv[i][0] == '-') {
      if (!strcmp(argv[i], "-a"))
	do_display = false;
      if (!strcmp(argv[i], "-v"))
	fully_visual = true;
    } else
      starsmf_file = argv[i];

  if (!fully_visual) {
    if (!starsmf_file.length())
      usage();

    if (do_display) {
      display = new graphics(100, "Starana");

      if (display->didntstart()) {
	delete display;
	fprintf(stderr, "Can't start graphics\n");
	exit(-1);
      }

      display->show_title_form();
    }

    if (!initialize_map(starsmf_file)) {
      fprintf(stderr, "Unable to read starsmf file %s\n", starsmf_file.chars());
      exit(-1);
    }

    filter_out_messages(report_log_filter);

    if (do_display) {
      myString title = game_map->name() + " - year " + int_to_str(game_map->year());
      display->wait_title_form();
      display->create_palette();
      display->form_initial_update();
      display->resize_map_window(game_map->displayres());
      display->set_window_title(title);
      display->redraw_map();
      //      display->toggle_mapcontrol();

      display->interact();

      delete display;
    } else
      fprintf(stderr, "Analysis done.\n");

  } else { // fully visual enabled
    // ignore do_display
    do_display = true;
    display = new graphics(100, "Starana");
    if (display->didntstart()) {
      delete display;
      fprintf(stderr, "Can't start graphics\n");
      exit(-1);
    }

    // ask for smf file (if not given)
    if (!starsmf_file.length())
      starsmf_file = display->ask_for_smf_file();

    display->show_title_form();
    if (!initialize_map(starsmf_file)) {
      display->wait_title_form();
      display->error_dialog(myString("Unable to read starsmf file " + starsmf_file));

    } else {
      myString title = game_map->name() + " - year " + int_to_str(game_map->year());
      filter_out_messages(report_log_filter);
      display->create_palette();
      display->form_initial_update();
      display->wait_title_form();
      display->resize_map_window(game_map->displayres());
      display->set_window_title(title);
      display->redraw_map();
      //      display->toggle_mapcontrol();

      display->interact();

      delete display;
    }
  }

  delete game_map;

  return 0;
}

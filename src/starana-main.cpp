#include "starana-classes.h"


#ifdef DEFAULT_FULLYVISUAL
bool fully_visual = true;
#else
bool fully_visual = false;
#endif



void usage(void)
{
  puts("StarAna 0.2e -- 2 Jul 1998 -- usage:\n");
  puts("starana [-a] [-v] [master .smf file]\n");
  puts("-a    just generate report-log and quit\n");
  puts("-v    open a window to ask for the master file\n");
  exit(-1);
}



int main(int argc, char** argv)
{
  String starsmf_file;
  int i;
  bool OPTdisplay = true;

  // simplify life to windog users
  setenv("DISPLAY", "localhost:0.0", 0);

  for (i = 1; i < argc; i++)
    if (argv[i][0] == '-') {
      if (!strcmp(argv[i], "-a"))
	OPTdisplay = false;
      if (!strcmp(argv[i], "-v"))
	fully_visual = true;
    } else
      starsmf_file = argv[i];

  if (!fully_visual) {
    if (!starsmf_file.length())
      usage();

    if (!initialize_map(starsmf_file, 600)) {
      fprintf(stderr, "Unable to read starsmf file %s\n", starsmf_file.chars());
      exit(-1);
    }

    if (OPTdisplay) {
      String title = game_map->name() + " - year " + int_to_str(game_map->year());
      display = new graphics(600, 600, (const char*)title);

      if (display->didntstart()) {
	delete display;
	fprintf(stderr, "Can't start graphics\n");
	exit(-1);
      }

      display->create_palette();
      display->form_initial_update();
      display->redraw_map();
      //      display->toggle_mapcontrol();

      display->interact();

      delete display;
    } else
      fprintf(stderr, "Analysis done.\n");

  } else { // fully visual enabled
    // ignore optdisplay
    display = new graphics(600, 600, "Starana");
    if (display->didntstart()) {
      delete display;
      fprintf(stderr, "Can't start graphics\n");
      exit(-1);
    }

    // ask for smf file (if not given)
    if (!starsmf_file.length())
      starsmf_file = display->ask_for_smf_file();

    if (!initialize_map(starsmf_file, 600))
      display->error_dialog(String("Unable to read starsmf file " + starsmf_file));

    else {
      String title = game_map->name() + " - year " + int_to_str(game_map->year());
      display->set_window_title(title);
      display->create_palette();

      display->form_initial_update();
      display->redraw_map();
      //      display->toggle_mapcontrol();

      display->interact();

      delete display;
    }
  }

  delete game_map;

  return 1;
}

extern "C" {
#include "forms.h"
}
#include "pfunc.h"
#include "../src/starana-classes.h"

/* callbacks and freeobj handles for form PlanetaryFunction */
void pfecb_selected(FL_OBJECT *ob, long data)
{
  if(fl_get_menu(ob) >= 0) {
    planetary_function* pf = find_pfunction(fl_get_menu_text(ob));

    display->write_pfunction(pf);
    display->pfunction_changed();
  }
}


void pfecb_number(FL_OBJECT *ob, long data)
{
  display->unload_pfunction();  
  mapview->select_plamode(fl_get_menu(ob) - 1);
  display->load_pfunction();
}


void pfecb_accept_and_prev(FL_OBJECT *ob, long data)
{
  display->unload_pfunction();
  mapview->select_plamode(MW_PREV);
  display->load_pfunction();
}

void pfecb_accept_and_next(FL_OBJECT *ob, long data)
{
  display->unload_pfunction();
  mapview->select_plamode(MW_NEXT);
  display->load_pfunction();
}

void pfecb_apply(FL_OBJECT *ob, long data)
{
  display->unload_pfunction();
  display->auto_redraw_map();
}

void pfecb_cancel(FL_OBJECT *ob, long data)
{
  display->load_pfunction();
}

void pfecb_close(FL_OBJECT *ob, long data)
{
  display->toggle_pfuncedit();
}

void pfecb_delete(FL_OBJECT *ob, long data)
{
  mapview->delete_plamode();
  display->load_pfunction();
  display->init_number_menu();
  display->auto_redraw_map();
}

void pfecb_insert(FL_OBJECT *ob, long data)
{
  mapview->insert_plamode();
  display->load_pfunction();
  display->init_number_menu();
  display->auto_redraw_map();
}


/* callbacks and freeobj handles for form MapControl */
void mccb_pfeditorwindow(FL_OBJECT *ob, long data)
{
  display->toggle_pfuncedit();
}

void mccb_pflistwindow(FL_OBJECT *ob, long data)
{
  display->toggle_pfunclist();
}

void mccb_scrollmap(FL_OBJECT *ob, long data)
{
  display->cbobj = ob;

  display->scroll_map(data);
}

void mccb_setfuture(FL_OBJECT *ob, long data)
{
  display->set_map_future(data);
}


void mccb_setraceviewpoint(FL_OBJECT *ob, long data)
{
  data--;
  if (data < game_map->number_of_players()) {
    mapview->set_viewpoint(game_map->find_race(data));
    display->select_viewpoint();
   
  } // else is an internal error
    
}

void mccb_setbkgmode(FL_OBJECT *ob, long data)
{
  display->cbobj = ob;

  mapview->set_maptype(fl_get_choice(ob) - 1);
  display->auto_redraw_map();
}



void mccb_alliances(FL_OBJECT *ob, long data)
{
  mapview->set_alliances(MW_NEXT);
  display->auto_redraw_map();
}



void mccb_setscaneff(FL_OBJECT* ob, long data)
{
  int eff;
  char tstr[32];

  sscanf(fl_get_input(ob), "%d", &eff);
  eff = mapview->set_scanner_eff(eff);

  sprintf(tstr, "%d", eff);
  fl_set_input(ob, tstr);

  display->auto_redraw_map();
}



int cb_mywin_handler(XEvent* xev, void* data)
{
  display->display_handle_event(xev);
}


/* callbacks and freeobj handles for form PlanetStatus */
int freeobj_ironiumdial_handle(FL_OBJECT *ob, int ev, FL_Coord mx, FL_Coord my,
			int key, void *xev)
{
  display->draw_mineral_handler(ob, 0);
  return 0;
}
int freeobj_boraniumdial_handle(FL_OBJECT *ob, int ev, FL_Coord mx, FL_Coord my,
			int key, void *xev)
{
  display->draw_mineral_handler(ob, 1);
  return 0;
}

int freeobj_germaniumdial_handle(FL_OBJECT *ob, int ev, FL_Coord mx, FL_Coord my,
			int key, void *xev)
{
  display->draw_mineral_handler(ob, 2);
  return 0;
}

int freeobj_gravitydial_handle(FL_OBJECT *ob, int ev, FL_Coord mx, FL_Coord my,
			int key, void *xev)
{
  display->draw_environment_handler(ob, 0);
  return 0;
}

int freeobj_termpdial_handle(FL_OBJECT *ob, int ev, FL_Coord mx, FL_Coord my,
			int key, void *xev)
{
  display->draw_environment_handler(ob, 1);
  return 0;
}

int freeobj_raddial_handle(FL_OBJECT *ob, int ev, FL_Coord mx, FL_Coord my,
			int key, void *xev)
{
  display->draw_environment_handler(ob, 2);
  return 0;
}

void pscb_closewindow(FL_OBJECT *ob, long data)
{
  display->hide_planetstatus();
}


/* callbacks and freeobj handles for form PlanetViews */
void pvcb_close(FL_OBJECT *ob, long data)
{
  display->toggle_pfunclist();
}

void pvcb_load(FL_OBJECT *ob, long data)
{
  const char* fname;

  fname = fl_show_fselector("Import from file", infile_path, "*.pfl", "");
  if (fname && fname[0]) {
    mapview->import_planet_views(fname);
    display->load_pfunclist();
    display->showselected_pfunclist();
    display->init_number_menu();
    display->load_pfunction();
    display->auto_redraw_map();
  }
}

void pvcb_export(FL_OBJECT *ob, long data)
{
  const char* fname;
  FILE* f;

  fname = fl_show_fselector("Export (append) to file", infile_path, "*.pfl", "");
  if (fname && fname[0])
    if ( (f = fopen(fname, "a")) ) {
      mapview->get_planet_view()->export(f);
      fclose(f);
    }
}

void pvcb_save(FL_OBJECT *ob, long data)
{
  const char* fname;

  fname = fl_show_fselector("Save to file", infile_path, "*.pfl", "");
  if (fname && fname[0])
    mapview->save_planet_views(fname);
}

void pvcb_delete(FL_OBJECT *ob, long data)
{
  mapview->delete_planet_view(mapview->get_planet_view_index());
  display->load_pfunclist();
  display->showselected_pfunclist();
  mapview->set_window_title();
  display->init_number_menu();
  display->load_pfunction();
  display->auto_redraw_map();
}

void pvcb_clone(FL_OBJECT *ob, long data)
{
  mapview->clone_planet_view(mapview->get_planet_view());
  display->load_pfunclist();
  display->showselected_pfunclist();
}

void pvcb_rename(FL_OBJECT *ob, long data)
{
  const char* nm;

  nm = fl_show_input("Enter new name for planet view:",
		     mapview->get_planet_view()->name.chars());

  if (nm && nm[0])
    mapview->get_planet_view()->name = String(nm);

  display->load_pfunclist();
  display->showselected_pfunclist();
  mapview->set_window_title();
}

void pvcb_pfeditor(FL_OBJECT *ob, long data)
{
  display->toggle_pfuncedit();
}

void pvcb_move(FL_OBJECT *ob, long data)
{
  mapview->move_planet_view(mapview->get_planet_view_index(), data);
  display->load_pfunclist();
  display->showselected_pfunclist();
}

void pvcb_select(FL_OBJECT *ob, long data)
{
  if (mapview->get_planet_view_index() != fl_get_browser(ob) - 1) {
    mapview->select_planet_view(fl_get_browser(ob) - 1);
    mapview->set_window_title();
    display->showselected_pfunclist();
    display->init_number_menu();
    display->load_pfunction();
    display->redraw_map();
  }
}

void pscb_setminscale(FL_OBJECT *ob, long)
{
  display->set_mineraldial_scale(fl_get_choice(ob) - 1);
}

void pscb_settestobject(FL_OBJECT *ob, long)
{
  display->load_mineralobject();
}

void pscb_viewsimulation(FL_OBJECT *ob, long)
{
  display->show_planetsimulation();
}


/* callbacks and freeobj handles for form PlanetSimulation */
void pmcb_close(FL_OBJECT *ob, long data)
{
  display->hide_planetsimulation();
}


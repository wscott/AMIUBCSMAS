extern "C" {
#include "forms.h"
}
#include "pfunc.h"
#include "../src/starana-classes.h"

/* callbacks and freeobj handles for form PlanetaryFunction */
void pfecb_selected(FL_OBJECT *ob, long data)
{
  if (display->in_planet_windows(ob)) {
    if(fl_get_menu(ob) >= 0) {
      planetary_function* pf = find_pfunction(fl_get_menu_text(ob));

      display->write_pfunction(pf);
      display->pfunction_changed();
    }
  } else {
    if(fl_get_menu(ob) >= 0) {
      fleet_function* ff = find_ffunction(fl_get_menu_text(ob));

      display->write_ffunction(ff);
      display->ffunction_changed();
    }
  }
}


void pfecb_number(FL_OBJECT *ob, long data)
{
  if (display->in_planet_windows(ob)) {
    display->unload_pfunction();  
    mapview->select_plamode(fl_get_menu(ob) - 1);
    display->load_pfunction();
  } else {
    display->unload_ffunction();  
    mapview->select_flemode(fl_get_menu(ob) - 1);
    display->load_ffunction();
  }
}


void pfecb_accept_and_prev(FL_OBJECT *ob, long data)
{
  if (display->in_planet_windows(ob)) {
    display->unload_pfunction();
    mapview->select_plamode(MW_PREV);
    display->load_pfunction();
  } else {
    display->unload_ffunction();
    mapview->select_flemode(MW_PREV);
    display->load_ffunction();
  }
}

void pfecb_accept_and_next(FL_OBJECT *ob, long data)
{
  if (display->in_planet_windows(ob)) {
    display->unload_pfunction();
    mapview->select_plamode(MW_NEXT);
    display->load_pfunction();
  } else {
    display->unload_ffunction();
    mapview->select_flemode(MW_NEXT);
    display->load_ffunction();
  }
}

void pfecb_apply(FL_OBJECT *ob, long data)
{
  if (display->in_planet_windows(ob))
    display->unload_pfunction();
  else
    display->unload_ffunction();

  display->auto_redraw_map();
}

void pfecb_cancel(FL_OBJECT *ob, long data)
{
  if (display->in_planet_windows(ob))
    display->load_pfunction();
  else
    display->load_ffunction();
}

void pfecb_close(FL_OBJECT *ob, long data)
{
  if (display->in_planet_windows(ob))
    display->toggle_pfuncedit();
  else
    display->toggle_ffuncedit();
}

void pfecb_delete(FL_OBJECT *ob, long data)
{
  if (display->in_planet_windows(ob)) {
    mapview->delete_plamode();
    display->load_pfunction();
    display->init_pla_number_menu();
  } else {
    mapview->delete_flemode();
    display->load_ffunction();
    display->init_fle_number_menu();
  }

  display->auto_redraw_map();
}

void pfecb_insert(FL_OBJECT *ob, long data)
{
  if (display->in_planet_windows(ob)) {
    mapview->insert_plamode();
    display->load_pfunction();
    display->init_pla_number_menu();
  } else {
    mapview->insert_flemode();
    display->load_ffunction();
    display->init_fle_number_menu();
  }

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

void mccb_ffeditorwindow(FL_OBJECT *ob, long data)
{
  display->toggle_ffuncedit();
}

void mccb_fflistwindow(FL_OBJECT *ob, long data)
{
  display->toggle_ffunclist();
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
    if (fl_get_button_numb(ob) == 3) {
      // right = open info window (or reload/raise it)
      display->load_racialreport(data);
      display->show_racialreport();

    } else {
      // left = select viewpoint
      mapview->set_viewpoint(game_map->find_race(data));
      display->select_viewpoint();
    }
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
  return 0;
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

void pscb_closewindow(FL_OBJECT *ob, long data)
{
  display->select_planetstatus(ob->form, 0);
  display->hide_planetstatus();
}


/* callbacks and freeobj handles for form PlanetViews */
void pvcb_close(FL_OBJECT *ob, long data)
{
  if (display->in_planet_windows(ob))
    display->toggle_pfunclist();
  else
    display->toggle_ffunclist();
}

void pvcb_load(FL_OBJECT *ob, long data)
{
  const char* fname;

  if (display->in_planet_windows(ob)) {
    fname = fl_show_fselector("Import from file", infile_path, "*.pfl", "");
    if (fname && fname[0]) {
      mapview->import_planet_views(fname);
      display->load_pfunclist();
      display->showselected_pfunclist();
      display->init_pla_number_menu();
      display->load_pfunction();
    }
  } else {
    fname = fl_show_fselector("Import from file", infile_path, "*.ffl", "");
    if (fname && fname[0]) {
      mapview->import_fleet_views(fname);
      display->load_ffunclist();
      display->showselected_ffunclist();
      display->init_fle_number_menu();
      display->load_ffunction();
    }

    display->auto_redraw_map();
  }
}

void pvcb_export(FL_OBJECT *ob, long data)
{
  const char* fname;
  FILE* f;

  if (display->in_planet_windows(ob)) {
    fname = fl_show_fselector("Export (append) to file", infile_path, "*.pfl", "");
    if (fname && fname[0])
      if ( (f = fopen(fname, "a")) )
	mapview->get_planet_view()->export(f);
    fclose(f);

  } else {
    fname = fl_show_fselector("Export (append) to file", infile_path, "*.ffl", "");
    if (fname && fname[0])
      if ( (f = fopen(fname, "a")) )
	mapview->get_fleet_view()->export(f);
    fclose(f);
  }
}

void pvcb_save(FL_OBJECT *ob, long data)
{
  const char* fname;

  if (display->in_planet_windows(ob)) {
    fname = fl_show_fselector("Save to file", infile_path, "*.pfl", "");
    if (fname && fname[0])
      mapview->save_planet_views(fname);
  } else {
    fname = fl_show_fselector("Save to file", infile_path, "*.ffl", "");
    if (fname && fname[0])
      mapview->save_fleet_views(fname);
  }
}

void pvcb_delete(FL_OBJECT *ob, long data)
{
  if (display->in_planet_windows(ob)) {
    mapview->delete_planet_view(mapview->get_planet_view_index());
    display->load_pfunclist();
    display->showselected_pfunclist();
    mapview->set_window_title();
    display->init_pla_number_menu();
    display->load_pfunction();
  } else {
    mapview->delete_fleet_view(mapview->get_fleet_view_index());
    display->load_ffunclist();
    display->showselected_ffunclist();
    display->init_fle_number_menu();
    display->load_ffunction();
  }

  display->auto_redraw_map();
}

void pvcb_clone(FL_OBJECT *ob, long data)
{
  if (display->in_planet_windows(ob)) {
    mapview->clone_planet_view(mapview->get_planet_view());
    display->load_pfunclist();
    display->showselected_pfunclist();
  } else {
    mapview->clone_fleet_view(mapview->get_fleet_view());
    display->load_ffunclist();
    display->showselected_ffunclist();
  }
}

void pvcb_rename(FL_OBJECT *ob, long data)
{
  const char* nm;

  if (display->in_planet_windows(ob)) {
    nm = fl_show_input("Enter new name for planet view:",
		       mapview->get_planet_view()->name.chars());

    if (nm && nm[0])
      mapview->get_planet_view()->name = myString(nm);

    display->load_pfunclist();
    display->showselected_pfunclist();
    mapview->set_window_title();
  } else {
    nm = fl_show_input("Enter new name for fleet view:",
		       mapview->get_fleet_view()->name.chars());

    if (nm && nm[0])
      mapview->get_fleet_view()->name = myString(nm);

    display->load_ffunclist();
    display->showselected_ffunclist();
  }
}

void pvcb_pfeditor(FL_OBJECT *ob, long data)
{
  if (display->in_planet_windows(ob))
    display->toggle_pfuncedit();
  else
    display->toggle_ffuncedit();
}

void pvcb_move(FL_OBJECT *ob, long data)
{
  if (display->in_planet_windows(ob)) {
    mapview->move_planet_view(mapview->get_planet_view_index(), data);
    display->load_pfunclist();
    display->showselected_pfunclist();
  } else {
    mapview->move_fleet_view(mapview->get_fleet_view_index(), data);
    display->load_ffunclist();
    display->showselected_ffunclist();
  }
}

void pvcb_select(FL_OBJECT *ob, long data)
{
  if (display->in_planet_windows(ob)) {
    if (mapview->get_planet_view_index() != fl_get_browser(ob) - 1) {
      mapview->select_planet_view(fl_get_browser(ob) - 1);
      mapview->set_window_title();
      display->showselected_pfunclist();
      display->init_pla_number_menu();
      display->load_pfunction();
      display->redraw_map();
    }
  } else {
    if (mapview->get_fleet_view_index() != fl_get_browser(ob) - 1) {
      mapview->select_fleet_view(fl_get_browser(ob) - 1);
      display->showselected_ffunclist();
      display->init_fle_number_menu();
      display->load_ffunction();
      display->redraw_map();
    }
  }
}

void pscb_setminscale(FL_OBJECT *ob, long)
{
  display->select_planetstatus(ob->form, 0);
  display->set_mineraldial_scale(fl_get_choice(ob) - 1);
}

void pscb_settestobject(FL_OBJECT *ob, long)
{
  display->select_planetstatus(ob->form, 0);
  display->load_mineralobject();
}

void pscb_viewsimulation(FL_OBJECT *ob, long)
{
  display->select_planetstatus(ob->form, 0);
  display->show_planetsimulation();
}

void pscb_firepacket(FL_OBJECT *ob, long)
{
  display->load_packetfiring();
  display->show_packetfiring();
}

void pscb_bombplanet(FL_OBJECT *ob, long)
{

}

void pscb_gateships(FL_OBJECT *ob, long)
{

}


/* callbacks and freeobj handles for form PlanetSimulation */
void pmcb_close(FL_OBJECT *ob, long data)
{
  display->select_planetstatus(ob->form, 1);
  display->hide_planetsimulation();
}


/* callbacks and freeobj handles for form PacketFiring */
void pfcb_close(FL_OBJECT *ob, long data)
{
  display->hide_packetfiring();
}


void pfcb_computepacket(FL_OBJECT *ob, long data)
{

}


void pfcb_increasewarp(FL_OBJECT *ob, long data)
{

}


void pfcb_decreasewarp(FL_OBJECT *ob, long data)
{

}


void pfcb_switchdirection(FL_OBJECT *ob, long data)
{

}


/* callbacks and freeobj handles for form RacialReport */
void rrcb_close(FL_OBJECT *ob, long data)
{
  display->hide_racialreport();
}


void rrccb_selectgraph(FL_OBJECT *ob, long data)
{
  if (data > 0)
    display->load_rrcomparisons(fl_get_choice(ob));
  else
    display->load_rrcomparisons();
}


void rrfcb_setfiltering(FL_OBJECT *ob, long data)
{
  if (fl_get_button(ob))
    filter_in_messages(data);
  else
    filter_out_messages(data);
}

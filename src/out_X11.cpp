#include "starana-classes.h"

extern int minscales[];
extern int minticks[][50];


int MAX_RADIUS = 8;  // max physical radius of pie charts


#include <ctype.h>


inline
char* e(char* s)
{
  return s + strlen(s);
}


// xforms percent paranoia: returns a pointer to an internal
// static buffer where the string gets the % doubled

char* xfpp(const myString& s)
{
  static char outbuf[512];
  const char* sp = s;
  char* op = outbuf;

  for (; (*op = *sp); op++, sp++)
    if (*sp == '%')
      *++op = '%';

  *op = 0;

  return outbuf;
}



void graphics::display_handle_event(XEvent* ev)
{
  char* symstring, keystring[8];
  KeySym key;
  int c;
  int view;
  race* r;

  switch(ev->type) {
  case KeyPress:
    XLookupString(&ev->xkey, keystring, 7, &key, 0);
    symstring = XKeysymToString(key);

    sca_mask = ev->xkey.state;
    if (symstring && strlen(symstring) == 1) {
      c = keystring[0];  /* "normal key" pressed :) */

      if (!c)
	c = symstring[0]; // handle case of ctrl-number

    } else
      c = key;

    // act on keypress
    switch(c) {
    case XK_KP_Add:
      scroll_map(-2);
      break;
    case XK_KP_Subtract:
      scroll_map(-3);
      break;
    case XK_KP_1:
    case XK_KP_End:
      scroll_map(1);
      break;
    case XK_KP_2:
    case XK_KP_Down:
    case XK_Down:
      scroll_map(2);
      break;
    case XK_KP_3:
    case XK_KP_Next:
      scroll_map(3);
      break;
    case XK_KP_4:
    case XK_KP_Left:
    case XK_Left:
      scroll_map(4);
      break;
    case XK_KP_6:
    case XK_KP_Right:
    case XK_Right:
      scroll_map(6);
      break;
    case XK_KP_7:
    case XK_KP_Home:
      scroll_map(7);
      break;
    case XK_KP_8:
    case XK_KP_Up:
    case XK_Up:
      scroll_map(8);
      break;
    case XK_KP_9:
    case XK_KP_Prior:
      scroll_map(9);
      break;
    case XK_KP_Enter: // redraw
      scroll_map(0);
      break;

    case 'r':
      if ( (r = game_map->find_race(mapview->viewpoint()->race_id() + 1)) ) {
	mapview->set_viewpoint(r);
	select_viewpoint();
      }
      break;
    case 'R':
      if ( (r = game_map->find_race(mapview->viewpoint()->race_id() - 1)) ) {
	mapview->set_viewpoint(r);
	select_viewpoint();
      }
      break;
    case 'v':
      mapview->select_planet_view(MW_NEXT);
      goto setview_p;
    case 'V':
      mapview->select_planet_view(MW_PREV);
      goto setview_p;
    case 'c':
      mapview->select_fleet_view(MW_NEXT);
      goto setview_f;
    case 'C':
      mapview->select_fleet_view(MW_PREV);
      goto setview_f;
    case 'f':
      mapview->when(MW_NEXT);
      auto_redraw_map();
      break;
    case 'F':
      mapview->when(MW_PREV);
      auto_redraw_map();
      break;
    case 's':
      mapview->set_scanner_eff(MW_NEXT);
      auto_redraw_map();
      break;
    case 'S':
      mapview->set_scanner_eff(MW_PREV);
      auto_redraw_map();
      break;
    case 'p':
      toggle_pfunclist();
      break;
    case 'e':
      toggle_pfuncedit();
      break;
    case 'o':
      toggle_ffunclist();
      break;
    case 'w':
      toggle_ffuncedit();
      break;
    case 'm':
      toggle_mapcontrol();
      break;
    case 'a':
      mapview->set_alliances(MW_NEXT);
      auto_redraw_map();
      break;
    case XK_F1:
      view = 0;
      goto setview;
    case XK_F2:
      view = 1;
      goto setview;
    case XK_F3:
      view = 2;
      goto setview;
    case XK_F4:
      view = 3;
      goto setview;
    case XK_F5:
      view = 4;
      goto setview;
    case XK_F6:
      view = 5;
      goto setview;
    case XK_F7:
      view = 6;
      goto setview;
    case XK_F8:
      view = 7;
      goto setview;
    case XK_F9:
      view = 8;
      goto setview;
    case XK_F10:
      view = 9;
      goto setview;
    case XK_F11:
      view = 10;
      goto setview;
    case XK_F12:
      view = 11;

setview:
      if (sca_mask && CTRL_PRESSED) {
	mapview->select_fleet_view(view);
	goto setview_p;
      } else {
	mapview->select_planet_view(view);
	goto setview_f;
      }

setview_p:
      mapview->set_window_title();
      showselected_pfunclist();
      init_pla_number_menu();
      load_pfunction();
      redraw_map();
      break;

setview_f:
      showselected_ffunclist();
      init_fle_number_menu();
      load_ffunction();
      redraw_map();
      break;
    }
    break;

#ifdef DISABLE_BACKINGSTORE
  case Expose:
    if (ev->xexpose.count == 0)
      auto_redraw_map();
    break;
#endif

  case KeyRelease:
    break;

  case ButtonPress:
    sca_mask = ev->xbutton.state;

    if (ev->xbutton.button == Button3)
      toggle_mapcontrol();
    else if (ev->xbutton.button == Button1) {
      select_planet(_xypoint(ev->xbutton.x, ev->xbutton.y));
      auto_redraw_map();
    }
    break;

  case ButtonRelease:
    break;

  case LeaveNotify:
    inwindow = 0;
    break;

  case EnterNotify:
    inwindow = 1;
    break;
  }
}


// colors required for MAP display
// white, grey, redhab, yellowhab+germ, greenhab+bora, iron, 16x races
unsigned int my_basecolors[][3] = { { 255, 255, 255}, // white
				    { 216, 216, 216}, // grey        
				    {   0, 220,   0}, // green habitab
				    { 220, 220,   0}, // yellow habitab
				    { 220,   0,   0}, // red habitab
				    {   0,   0, 255}, // ironium     
				    {   0, 220,   0}, // bora
				    { 220, 220,   0}, // germanium
				    { 204, 159,  59}, // races
				    { 240,   0,   0},       
				    {   0, 220,   0},       
				    {   0,   0, 255},       
				    { 214, 214,   0},       
				    { 214,   0, 214},       
				    {   0, 214, 214},       
				    { 140,  40,  46},       
				    { 133, 126,   0},       
				    { 138,  41, 186},       
				    { 242, 179, 148},       
				    { 150, 150, 255},       
				    { 189,  87,  87},       
				    { 242, 174, 242},       
				    { 255, 139,  97},       
				    {  46, 153,  51},       
				    {   0,   0,   0} }; // end marker

// colors required in XForms displays
// iron+mining, bora+mining, germ+mining, 16x races

unsigned int xforms_colors[][3] = { {   0,   0, 255}, // ironium     
				    {   0,   0, 190},
				    {   0, 220,   0}, // boranium
				    {   0, 163,   0},
				    { 220, 220,   0}, // germanium
				    { 163, 163,   0},
				    { 204, 159,  59}, // races
				    { 240,   0,   0},    
				    {   0, 220,   0},                
				    {   0,   0, 255},                
				    { 214, 214,   0},                
				    { 214,   0, 214},                
				    {   0, 214, 214},                
				    { 140,  40,  46},                
				    { 133, 126,   0},                
				    { 138,  41, 186},                
				    { 242, 179, 148},                
				    { 150, 150, 255},                
				    { 189,  87,  87},                
				    { 242, 174, 242},                
				    { 255, 139,  97},                
				    {  46, 153,  51},                
				    {   0,   0,   0} }; // end marker

const int PALETTE_LEN = 100;

unsigned long my_to_x[PALETTE_LEN];
unsigned char my_palette[PALETTE_LEN][3] = { {   0,   0,   0}, // black
					     { 124, 124,   0}, // penscan
					     { 124,   0,   0}, // scan
					     {   0,   0,   0} }; // unused


void set_max_pie_radius(int r)
{
  if (r < 4)
    r = 4;
  if (r > 32)
    r = 64;

  MAX_RADIUS = r;
}



void set_colormap_color(const int c, int r, int g, int b)
{
  r &= 0xFF;
  g &= 0xFF;
  b &= 0xFF;

  if (c < 4) { // default colors
    my_palette[c][0] = r;
    my_palette[c][1] = g;
    my_palette[c][2] = b;
  } else if (c >= COL_WHITE && c < (COL_RACES+4*16)) {
    int bc  = c / 4 - 1;

    my_basecolors[bc][0] = r;
    my_basecolors[bc][1] = g;
    my_basecolors[bc][2] = b;
  }
}



void graphics::create_palette(void)
{
  int i, j;
  XColor c;

  // create shades
  for (j = 4, i = 0; (my_basecolors[i][0] || my_basecolors[i][1] || my_basecolors[i][2]); i++) {
    my_palette[j][0] = my_basecolors[i][0];
    my_palette[j][1] = my_basecolors[i][1];
    my_palette[j++][2] = my_basecolors[i][2];

    my_palette[j][0] = (int)my_basecolors[i][0] * 220 / 255;
    my_palette[j][1] = (int)my_basecolors[i][1] * 220 / 255;
    my_palette[j++][2] = (int)my_basecolors[i][2] * 220 / 255;

    my_palette[j][0] = (int)my_basecolors[i][0] * 190 / 255;
    my_palette[j][1] = (int)my_basecolors[i][1] * 190 / 255;
    my_palette[j++][2] = (int)my_basecolors[i][2] * 190 / 255;

    my_palette[j][0] = (int)my_basecolors[i][0] * 144 / 255;
    my_palette[j][1] = (int)my_basecolors[i][1] * 144 / 255;
    my_palette[j++][2] = (int)my_basecolors[i][2] * 144 / 255;
  }

  // release old colormap (if any)
  XFreeColormap(x_display, x_cmap);

  // try with default, otherwise
  x_cmap = DefaultColormap(x_display, x_screen);

  for (i = 0; i < PALETTE_LEN; i++) {
    c.red   = (int)my_palette[i][0] << 8;
    c.green = (int)my_palette[i][1] << 8;
    c.blue  = (int)my_palette[i][2] << 8;
    c.flags = DoRed | DoGreen | DoBlue;

    if (!XAllocColor(x_display, x_cmap, &c))
      break;

    my_to_x[i] = c.pixel;
  }

  if (i != PALETTE_LEN) {
    x_cmap = XCreateColormap(x_display, rootw, visual, AllocAll);

    for (i = 0; i < PALETTE_LEN; i++) {
      c.pixel = i + 1;
      c.red   = (int)my_palette[i][0] << 8;
      c.green = (int)my_palette[i][1] << 8;
      c.blue  = (int)my_palette[i][2] << 8;
      c.flags = DoRed | DoGreen | DoBlue;    
      
      XStoreColor(x_display, x_cmap, &c);

      my_to_x[i] = c.pixel;
    }
  }

  XSetWindowColormap(x_display, my_win, x_cmap);
  XInstallColormap(x_display, x_cmap);
}



static
int close_null(FL_FORM* frm, void* data)
{
  return FL_OK;
}


graphics::graphics(const int resol, const char* title) : 
          sca_mask(0), gra_xres(resol),
	  gra_yres(resol), curr_vwp(-1),
	  curr_rep(-1), curr_comparison_graph(1), 
	  cbobj(NULL)
{
  int depth;
  XVisualInfo visualinfo;
  unsigned int bw;
  XSizeHints sizehints;
  unsigned int mask;
  int xpos, ypos;
  unsigned int wid, hi;
  XSetWindowAttributes wattr;
  unsigned int wattrmask;
  XWMHints wmhints;
  XGCValues gcvals;

  running_fine = true;

  // initialize the xforms stuff
  int one = 1;
  char* crapargv[] = {"starana", NULL};

  fl_initialize(&one, (char**)&crapargv, "StarAna", 0, 0);
  xf_mc = create_form_MapControl();
  xf_pfe = create_form_DisplayFunction();
  xf_ffe = create_form_DisplayFunction();
  xf_ps[0] = create_form_PlanetStatus();
  xf_ps[1] = create_form_PlanetStatus();
  xf_pm[0] = create_form_PlanetSimulation();
  xf_pm[1] = create_form_PlanetSimulation();
  xf_pv = create_form_ObjectViews();
  xf_fv = create_form_ObjectViews();
  xf_pak = create_form_PacketFiring();
  xf_sg = create_form_ShipGating();
  xf_titl = create_form_IntroTitle();
  xf_rrinfo = create_form_RR_RaceInfo();
  xf_rrlog = create_form_RR_ReportLog();
  xf_rrcmp = create_form_RR_Comparisons();
  xf_rrdes = create_form_RR_Designs();
  xf_rrobj = create_form_RR_Objects();
  xf_rrfilt = create_form_RR_Filtering();
  xf_rr = create_form_RacialReport(xf_rrinfo, xf_rrlog, xf_rrcmp, xf_rrdes, xf_rrobj, xf_rrfilt);

  // prevent closeform to kill application
  fl_set_form_atclose(xf_mc->MapControl, close_null, NULL);
  fl_set_form_atclose(xf_pfe->DisplayFunction, close_null, NULL);
  fl_set_form_atclose(xf_ffe->DisplayFunction, close_null, NULL);
  fl_set_form_atclose(xf_ps[0]->PlanetStatus, close_null, NULL);
  fl_set_form_atclose(xf_ps[1]->PlanetStatus, close_null, NULL);
  fl_set_form_atclose(xf_pm[0]->PlanetSimulation, close_null, NULL);
  fl_set_form_atclose(xf_pm[1]->PlanetSimulation, close_null, NULL);
  fl_set_form_atclose(xf_pv->ObjectViews, close_null, NULL);
  fl_set_form_atclose(xf_fv->ObjectViews, close_null, NULL);
  fl_set_form_atclose(xf_pak->PacketFiring, close_null, NULL);
  fl_set_form_atclose(xf_rr->RacialReport, close_null, NULL);

  x_display = fl_get_display();
  if (!x_display) {
    running_fine = false;
    return;
  }

  geomstring = XGetDefault(x_display, "StarAna", "Geometry");

  x_screen = DefaultScreen(x_display);

  depth = XDisplayPlanes(x_display, x_screen);

  if (depth < 8) {
    running_fine = false;
    return;
  }

  // require TrueColor or PseudoColor visual
  if (!XMatchVisualInfo(x_display, x_screen, depth, PseudoColor, &visualinfo))
    if (!XMatchVisualInfo(x_display, x_screen, depth, TrueColor, &visualinfo)) {
      running_fine = false;
      return;
    }

  visual = visualinfo.visual;

  rootw = RootWindow(x_display, x_screen);

  useGC = DefaultGC(x_display, x_screen);

  //  my_font = XLoadFont(x_display, "-misc-fixed-bold-r-normal--16-140-75-75-c-90-iso8859-1");
  my_font = XLoadFont(x_display, "-adobe-courier-bold-r-normal--10-100-75-75-m-60-iso8859-1");
  small_font = XLoadFont(x_display, "-schumacher-clean-medium-r-normal--6-60-75-75-c-40-iso8859-1");

  if (my_font == BadName || small_font == BadName) {
    running_fine = false;
    return;
  }

  busy_cursor = XCreateFontCursor(x_display, XC_clock);
  norm_cursor = XCreateFontCursor(x_display, XC_arrow);

  /* Create Window */
  bw = 1;

  sizehints.flags = PMinSize | PMaxSize;

  sizehints.x = (DisplayWidth(x_display, x_screen) - resol) / 2;
  sizehints.y = (DisplayHeight(x_display, x_screen) - resol) / 2;

  sizehints.width = resol;
  sizehints.height = resol;

  sizehints.max_width = sizehints.min_width = sizehints.width;
  sizehints.max_height = sizehints.min_height = sizehints.height;

  if (geomstring) {
    mask = XParseGeometry(geomstring, &xpos, &ypos, &wid, &hi);

    if (mask & XValue) {
      sizehints.flags |= USPosition;
      sizehints.x = xpos;
    }

    if (mask & YValue) {
      sizehints.flags |= USPosition;
      sizehints.y = ypos;
    }

    if (mask & XNegative)
      sizehints.x = DisplayWidth(x_display, x_screen) - sizehints.width + xpos;

    if (mask & YNegative)
      sizehints.y = DisplayHeight(x_display, x_screen) - sizehints.height + ypos;

  } else
    sizehints.flags |= PPosition | PSize;

  x_cmap = DefaultColormap(x_display, x_screen);

  wattr.background_pixel = BlackPixel(x_display, x_screen);
  wattr.border_pixel = WhitePixel(x_display, x_screen);
  wattr.colormap = x_cmap;
#ifdef DISABLE_BACKINGSTORE
  wattr.backing_store = NotUseful;
#else
  wattr.backing_store = Always;
#endif
  wattrmask = CWBackPixel | CWBorderPixel | CWColormap | CWBackingStore;

  my_win = XCreateWindow(x_display, rootw, sizehints.x, sizehints.y, 
			 sizehints.width, sizehints.height, bw,
			 depth, CopyFromParent, visual, wattrmask, &wattr);

  XSetStandardProperties(x_display, my_win, title, "StarAna", None,
			 (char **)NULL, 0, &sizehints);

  wmhints.initial_state = NormalState;
  wmhints.input = True;
  wmhints.flags = StateHint | InputHint;

  XSetWMHints(x_display, my_win, &wmhints);

  XSelectInput(x_display, my_win, EVENT_MASK);

  XDefineCursor(x_display, my_win, norm_cursor);

  // generate needed GCs
  gcvals.graphics_exposures = 0;
  XChangeGC(x_display, useGC, GCGraphicsExposures, &gcvals);
  XSetFont(x_display, useGC, my_font);

  mask = 0;
  fillGC = XCreateGC(x_display, my_win, mask, &gcvals);
  smallGC = XCreateGC(x_display, my_win, mask, &gcvals);

  mask = GCFunction | GCForeground | GCLineWidth | GCLineStyle | 
         GCGraphicsExposures;
  XCopyGC(x_display, useGC, mask, fillGC);
  XSetFillStyle(x_display, fillGC, FillSolid);

  XCopyGC(x_display, useGC, mask, smallGC);
  XSetFont(x_display, smallGC, small_font);

  // set idle callback to handle display window events
  fl_add_event_callback(my_win, 0, cb_mywin_handler, NULL);

  XMapWindow(x_display, my_win);
}



graphics::~graphics(void)
{
  if (running_fine) {
    XUnloadFont(x_display, my_font);
    
    XUndefineCursor(x_display, my_win);
  
    XFreeColormap(x_display, x_cmap);

    XUnmapWindow(x_display, my_win);

    XCloseDisplay(x_display);
  }
}



void graphics::set_window_title(const myString& title)
{
  // no idea if it's correct
  XSetStandardProperties(x_display, my_win, title, "StarAna", None,
			 (char **)NULL, 0, NULL);
}



void graphics::resize_map_window(const int resol)
{
  XSizeHints sizehints;

  sizehints.flags = PMinSize | PMaxSize;

  gra_xres = gra_yres = resol;
  sizehints.max_width = sizehints.min_width = resol;
  sizehints.max_height = sizehints.min_height = resol;

  XSetStandardProperties(x_display, my_win, NULL, NULL, None,
			 (char **)NULL, 0, &sizehints);
  XResizeWindow(x_display, my_win, resol, resol);
}



void graphics::show_title_form(void)
{
  fl_show_form(xf_titl->IntroTitle, FL_PLACE_CENTER, FL_NOBORDER, "Welcome to Starana!");
  XRaiseWindow(x_display, xf_titl->IntroTitle->window);
  XFlush(fl_get_display());
  
  // set up timer
  elapsed_title = time(0L) + 2;
}



void graphics::wait_title_form(void)
{
  // make sure it's shown
  if ( !fl_form_is_visible(xf_titl->IntroTitle) )
    return;

  // wait for timer
  int dt = time(0L) - elapsed_title - 2;
  if (dt < 0)
    sleep(-dt);

  fl_hide_form(xf_titl->IntroTitle);
  XFlush(fl_get_display());
}



void graphics::form_initial_update(void)
{
  char mainmenu[512];
  int i, j, mt;
  const char* c;
  myString msg;

  // put all the appropriate stuff in the forms (race names/colors/pfuncs)
  
  mainmenu[0] = 0;
  // map background types
  
  for (i = 0; ; i++) {
    if (i != mapview->set_maptype(i))
      break;

    c = mapview->maptype_name();
    if (i)
      strcat(mainmenu, " |");
    
    strcat(mainmenu, c);
  }

  fl_addto_choice(xf_mc->mapmode, mainmenu);
  mapview->set_maptype(MAP_BLACK);
  fl_set_choice(xf_mc->mapmode, 1);

  // planetary functions menu
  char submenus[8][2][256];
  int subids[8];
  int mm, subcount;
  int nsubs = 0;
  planetary_function* pf0 = get_next_pfunction(NULL);
  planetary_function* pf = pf0;

  mainmenu[0] = 0;
  mm = fl_newpup(fl_default_win());
  subcount = 8;

  do {
    // do we have type?
    for (i = 0; i < nsubs; i++)
      if (!strcmp((const char*)pf->type(), submenus[i][0]))
	break;

    if (i == nsubs) {

      // we need to add a submenu
      strcpy(submenus[nsubs][0], (const char*)pf->type());
      strcpy(submenus[nsubs][1], xfpp(pf->name()));
      sprintf(e(submenus[nsubs][1]), "%%x%d", subcount++);
      subids[nsubs] = fl_newpup(0);

      if (nsubs)
	strcat(mainmenu, "|");
      strcat(mainmenu, xfpp(pf->type()));
      strcat(mainmenu, "%m");

      nsubs++;

    } else {
      // add to an existing one
      strcat(submenus[i][1], "|");
      strcat(submenus[i][1], xfpp(pf->name()));
      sprintf(e(submenus[i][1]), "%%x%d", subcount++);
    }
  } while ( (pf = get_next_pfunction(pf)) != pf0 && nsubs < 8);

  // attach all menus
  for (i = 0; i < nsubs; i++)
    fl_addtopup(subids[i], submenus[i][1]);

  fl_addtopup(mm, mainmenu, subids[0], subids[1], subids[2], subids[3], subids[4], subids[5], subids[6], subids[7]);
  fl_set_menu_popup(xf_pfe->selected, mm);

  // fleet functions menu (same as above, but with fleets)
  nsubs = 0;
  fleet_function* ff0 = get_next_ffunction(NULL);
  fleet_function* ff = ff0;

  mainmenu[0] = 0;
  mm = fl_newpup(fl_default_win());
  subcount = 8;

  do {
    // do we have type?
    for (i = 0; i < nsubs; i++)
      if (!strcmp((const char*)ff->type(), submenus[i][0]))
	break;

    if (i == nsubs) {

      // we need to add a submenu
      strcpy(submenus[nsubs][0], (const char*)ff->type());
      strcpy(submenus[nsubs][1], xfpp(ff->name()));
      sprintf(e(submenus[nsubs][1]), "%%x%d", subcount++);
      subids[nsubs] = fl_newpup(0);

      if (nsubs)
	strcat(mainmenu, "|");
      strcat(mainmenu, xfpp(ff->type()));
      strcat(mainmenu, "%m");

      nsubs++;

    } else {
      // add to an existing one
      strcat(submenus[i][1], "|");
      strcat(submenus[i][1], xfpp(ff->name()));
      sprintf(e(submenus[i][1]), "%%x%d", subcount++);
    }
  } while ( (ff = get_next_ffunction(ff)) != ff0 && nsubs < 8);

  // attach all menus
  for (i = 0; i < nsubs; i++)
    fl_addtopup(subids[i], submenus[i][1]);

  fl_addtopup(mm, mainmenu, subids[0], subids[1], subids[2], subids[3], subids[4], subids[5], subids[6], subids[7]);
  fl_set_menu_popup(xf_ffe->selected, mm);

  // set up the initial menu for the number
  init_pla_number_menu();
  init_fle_number_menu();

  // set some kind of default crap into pfe window
  mapview->select_plamode(0);
  load_pfunction();
  mapview->select_flemode(0);
  load_ffunction();

  // propagate colors to xforms table
  // minerals
  for (i = 0; i < 3; i++) {
    xforms_colors[XFCOL_IRON+2*i][0] = my_basecolors[COL_IRON/4-1+i][0];
    xforms_colors[XFCOL_IRON+2*i][1] = my_basecolors[COL_IRON/4-1+i][1];
    xforms_colors[XFCOL_IRON+2*i][2] = my_basecolors[COL_IRON/4-1+i][2];
    xforms_colors[XFCOL_IRON+2*i+1][0] = my_basecolors[COL_IRON/4-1+i][0] * 199/255;
    xforms_colors[XFCOL_IRON+2*i+1][1] = my_basecolors[COL_IRON/4-1+i][1] * 199/255;
    xforms_colors[XFCOL_IRON+2*i+1][2] = my_basecolors[COL_IRON/4-1+i][2] * 199/255;
  }

  // races
  for (i = 0; i < 16; i++) {
    xforms_colors[XFCOL_RACES+i][0] = my_basecolors[COL_RACES/4-1+i][0];
    xforms_colors[XFCOL_RACES+i][1] = my_basecolors[COL_RACES/4-1+i][1];
    xforms_colors[XFCOL_RACES+i][2] = my_basecolors[COL_RACES/4-1+i][2];
  }

  for (i = 0; xforms_colors[i][0] || xforms_colors[i][1] || xforms_colors[i][2]; i++)
    fl_mapcolor(FL_FREE_COL1 + i, xforms_colors[i][0],
		xforms_colors[i][1], xforms_colors[i][2]);

  for (i = 0; i < game_map->number_of_players(); i++) {
    fl_set_object_lcol(xf_mc->race[i], FL_FREE_COL1 + XFCOL_RACES + i);
    fl_set_object_label(xf_mc->race[i], game_map->find_race(i)->name());
  }

  // mineral objects labels colors, minscales menu
  for (i = 0; i < 2; i++) {
    fl_set_object_lcol(xf_ps[i]->minobjects[0], FL_FREE_COL1 + XFCOL_IRON+1);
    fl_set_object_lcol(xf_ps[i]->minobjects[1], FL_FREE_COL1 + XFCOL_BORA);
    fl_set_object_lcol(xf_ps[i]->minobjects[2], FL_FREE_COL1 + XFCOL_GERM);

    // default minscale
    xf_ps[i]->mineraldial_scale = 4; // offset in minscales (=5000)

    for (j = 0; minscales[j]; j++) {
      if (minscales[j] == -1)
	strcpy(mainmenu, "Logarithmic");
      else if (minscales[j] == -2)
	strcpy(mainmenu, "Multi-Linear");
      else
	sprintf(mainmenu, "%d", minscales[j]);

      fl_addto_choice(xf_ps[i]->minscale, mainmenu);
    }
    fl_set_choice(xf_ps[i]->minscale, 5);

    // when there's a planet owner modification in the status window
    // we must reload the object table
    xf_ps[i]->mineralobjects_lastowner = -1;
    xf_ps[i]->statusnumber = i;
    xf_pm[i]->statusnumber = i;
  }
  select_planetstatus(0);

  // mineral colors: race ship designs
  for (i = 0; i < 16; i++) {
    fl_set_object_lcol(xf_rrdes->minerals[i][0], FL_FREE_COL1 + XFCOL_IRON+1);
    fl_set_object_lcol(xf_rrdes->minerals[i][1], FL_FREE_COL1 + XFCOL_BORA);
    fl_set_object_lcol(xf_rrdes->minerals[i][2], FL_FREE_COL1 + XFCOL_GERM);
  }

  for (i = 0; i < 12; i++) {
    fl_set_object_lcol(xf_rrobj->minerals[i][0], FL_FREE_COL1 + XFCOL_IRON+1);
    fl_set_object_lcol(xf_rrobj->minerals[i][1], FL_FREE_COL1 + XFCOL_BORA);
    fl_set_object_lcol(xf_rrobj->minerals[i][2], FL_FREE_COL1 + XFCOL_GERM);
  }

  // set message filtering buttons
  for (i = 0; ; i++)
    if ( (mt = message_get_mask(i)) ) {
      if (xf_rrfilt->buttons[i])
	if (messages_are_filtered(mt))
	  fl_set_button(xf_rrfilt->buttons[i], 0);
	else
	  fl_set_button(xf_rrfilt->buttons[i], 1);
    } else
      break;

  // ship gating gate statistics
  msg = "Planet's";
  fl_addto_choice(xf_sg->gatetouse[0], msg);
  fl_addto_choice(xf_sg->gatetouse[1], msg);

  for (i = 0; i < 7; i++) {
    msg = ( (gate_mass[i] > 0)? int_to_str(gate_mass[i]) : myString("oo") ) 
          + " / " +
          ( (gate_distance[i] > 0)? int_to_str(gate_distance[i]) : myString("oo") );
    fl_addto_choice(xf_sg->gatetouse[0], msg);
    fl_addto_choice(xf_sg->gatetouse[1], msg);
  }

  for (i = 0; i < 4; i++)
    fl_set_input(xf_sg->amount[i], "0");

  fl_set_input(xf_mc->future, "0");
  fl_set_input(xf_mc->scaneff, "100");

  mapview->set_viewpoint(NULL);
  select_viewpoint();

  // autoredraw on
  fl_set_button(xf_mc->autoredraw, 1);

  // prepare planetary/fleet view browser
  load_pfunclist();
  showselected_pfunclist();
  load_ffunclist();
  showselected_ffunclist();
}



void graphics::redraw_map(void)
{
  clear();

  mapview->display_space();
  mapview->set_planet_display();
  mapview->set_fleet_display();

  mapview->display_objects();

  for (int i = 0; i < 2; i++)
    if (fl_form_is_visible(xf_ps[i]->PlanetStatus)) {
      select_planetstatus(i);
      load_planetstatus();
    }

  //  mapview->display_addinfo(620, 20);

  done();
}



void graphics::auto_redraw_map(void)
{
  if (fl_get_button(xf_mc->autoredraw))
    redraw_map();
}



void graphics::scroll_map(const int dir)
{
  int mv = mapview->good_move();
  if ((cbobj && fl_get_button_numb(cbobj) == 3) || (sca_mask & SHIFT_PRESSED) )
    mv *= 2;

  switch(dir) {
  case -1:
    mapview->reset();
    break;
  case -2:
    mapview->zoom(MW_NEXT);
    break;
  case -3:
    mapview->zoom(MW_PREV);
    break;
  case 1:
    mapview->ytranslate(-mv);
    mapview->xtranslate(-mv);
    break;
  case 2:
    mapview->ytranslate(-mv);
    break;
  case 3:
    mapview->ytranslate(-mv);
    mapview->xtranslate(mv);
    break;
  case 4:
    mapview->xtranslate(-mv);
    break;
  case 5:
    break;
  case 6:
    mapview->xtranslate(mv);
    break;
  case 7:
    mapview->xtranslate(-mv);
    mapview->ytranslate(mv);
    break;
  case 8:
    mapview->ytranslate(mv);
    break;
  case 9:
    mapview->xtranslate(mv);
    mapview->ytranslate(mv);
    break;
  case 0:
    redraw_map();
    return;
  }

  auto_redraw_map();
}



void graphics::set_map_future(int data)
{
  int w;
  char t[16];

  if (data == 1)
    w = mapview->when(MW_NEXT);

  else if (data == -1)
    w = mapview->when(MW_PREV);

  else {
    sscanf(fl_get_input(xf_mc->future), "%d", &w);
    w = mapview->when(w);
  }

  sprintf(t, "%d", w);
  fl_set_input(xf_mc->future, t);

  auto_redraw_map();
}



void graphics::interact(void)
{
  FL_OBJECT* fo;

  do {
    do {
      fo = fl_do_forms();
    } while (fo != xf_mc->quit);
    
    // display some dialog
  } while (!fl_show_question("Do you really want to quit?", 0));
}



void graphics::draw_string(const int xp, const int yp, const int color, 
			   const char* str)
{
  XSetForeground(x_display, useGC, my_to_x[color]);
  XDrawString(x_display, my_win, useGC, xp, yp, str, strlen(str));
}



void graphics::draw_smallstring(const int xp, const int yp, const int color, 
				const char* str)
{
  XSetForeground(x_display, smallGC, my_to_x[color]);
  XDrawString(x_display, my_win, smallGC, xp, yp, str, strlen(str));
}



void graphics::set_mineraldial_scale(const int i)
{
  curr_ps->mineraldial_scale = i;

  fl_redraw_object(curr_ps->ironiumdial);
  fl_redraw_object(curr_ps->boraniumdial);
  fl_redraw_object(curr_ps->germaniumdial);
}



int graphics::minerals_to_display(const int v, const int w)
{
  int x;
  const int& scale = minscales[curr_ps->mineraldial_scale];

  if (scale == -1) { // logarithmic
    x = (int)(1000.0 * (log10(v) - 0.99));
    if (x < 0)
      x = 1;
    x = x * w / 4100;

  } else if (scale == -2) { // multilinear
    // 3 sections: 0->1000->10000->100000
    if (v <= 1000)
      x = v * w / 3033;
    else if (v <= 10000)
      x = 1000 * w / 3033 + ( (v-1000) * w / 30330);
    else
      x = 2000 * w / 3033 + ( (v-10000) * w / 303300);

  } else { // normal linear
    x = v * w / (scale * 41 / 40);
  }

  if (x > w)
    x = w;

  return x;
}
 


void graphics::draw_mineral_handler(FL_OBJECT* ob, const int i)
{
  GC gc = fl_state[fl_get_vclass()].gc[0];
  Window win = fl_winget();
  int hahe = ob->h / 2;
  int xmin, xmax, step;
  const _mindial& mineral = curr_ps->mineral_dials[i];
  const int& scale = curr_ps->mineraldial_scale;

  // clear old object
  XSetForeground(x_display, gc, fl_get_flcolor(FL_COL1));
  XFillRectangle(x_display, win, gc, ob->x, ob->y, ob->w, ob->h);
  
  // use a logarithmic scale for minerals 10/1000/10000/100000
  // minerals now
  if (mineral.now > 0) {
    xmin = minerals_to_display(mineral.now, ob->w);
    XSetForeground(x_display, gc, fl_get_flcolor(FL_FREE_COL1 + XFCOL_IRON + 2*i));
    XFillRectangle(x_display, win, gc, ob->x, ob->y+hahe-6, xmin, 12);
  } else
    xmin = 0;

  // mining
  if ( (mineral.now+mineral.mining) > 0) {
    xmax = minerals_to_display(mineral.now+mineral.mining, ob->w);
    XSetForeground(x_display, gc, fl_get_flcolor(FL_FREE_COL1 + XFCOL_IRON + 2*i + 1));
    XFillRectangle(x_display, win, gc, ob->x+xmin, ob->y+hahe-6, xmax-xmin, 12);
  } else
    xmax = 0;


  // draw bar for minerals next year
  if ( (mineral.next > 0) ) {
    xmax = minerals_to_display(mineral.next, ob->w);
    XSetForeground(x_display, gc, fl_get_flcolor(FL_FREE_COL1 + XFCOL_IRON + 2*i));
    XDrawLine(x_display, win, gc, ob->x+xmax, ob->y+hahe-9, ob->x+xmax, ob->y+hahe+9);
  }

  // draw scale
  XSetForeground(x_display, gc, fl_get_flcolor(FL_BLACK));  

  for (step = 0; minticks[scale][step] != -1; step++) {
    xmax = minerals_to_display(abs(minticks[scale][step]), ob->w);

    if ( minticks[scale][step] < 0 ) {
      XDrawLine(x_display, win, gc, ob->x+xmax, ob->y, ob->x+xmax, ob->y+4);
      XDrawLine(x_display, win, gc, ob->x+xmax, ob->y+ob->h-1, ob->x+xmax, ob->y+ob->h-5);
    } else {
      XDrawLine(x_display, win, gc, ob->x+xmax, ob->y, ob->x+xmax, ob->y+2);
      XDrawLine(x_display, win, gc, ob->x+xmax, ob->y+ob->h-1, ob->x+xmax, ob->y+ob->h-3);
    }
  }

  // black diamod for concentration (adjusted to prevent clipping)
  xmin = 5 + mineral.conc * (ob->w -10) / 120;
  if (xmin > ob->w)
    xmin = ob->w;

  XDrawLine(x_display, win, gc, ob->x+xmin+4, ob->y+hahe, ob->x+xmin, ob->y+hahe+4);
  XDrawLine(x_display, win, gc, ob->x+xmin, ob->y+hahe+4, ob->x+xmin-4, ob->y+hahe);
  XDrawLine(x_display, win, gc, ob->x+xmin-4, ob->y+hahe, ob->x+xmin, ob->y+hahe-4);
  XDrawLine(x_display, win, gc, ob->x+xmin, ob->y+hahe-4, ob->x+xmin+4, ob->y+hahe);

  // restore grey
  XSetForeground(x_display, gc, fl_get_flcolor(FL_COL1));
}



void graphics::draw_fat_circle_arc(const int xp, const int yp, const int r,
				   const int c1,
				   const int thetamin = 0, const int thetaspan = 360*64)
{
  // don't forget that we are getting 4* radius and are supposed
  // to use the last 2 bits for some cute shading trick

  // real radius, we'll use this +1 at maximum
  int rr = r / 4;

  // shading effect: 0=nothing 1,2,3=draw outer ring of darker shade (1 to 3)
  int se = r % 4;

  if (se != 0) {
    XSetForeground(x_display, fillGC, my_to_x[c1 + (4 - se)]);
    XFillArc(x_display, my_win, fillGC, xp - rr - 1, yp - rr - 1, 3 + rr * 2, 3 + rr * 2, thetamin, thetaspan);
  }

  XSetForeground(x_display, fillGC, my_to_x[c1]);
  XFillArc(x_display, my_win, fillGC, xp - rr, yp - rr, 1 + rr * 2, 1 + rr * 2, thetamin, thetaspan);
}



void graphics::draw_triangle_pie(const _xypoint& p, const _xypoint& dir,
				 const int r, const int c1,
				 const int thetamin = 0, const int thetaspan = 360*64)
{
  XPoint xpoints[3];
  _xypoint rdir;

  // don't forget that we are getting 4* radius and are supposed
  // to use the last 2 bits for some cute shading trick

  // real radius, we'll use this +1 at maximum
  int rr = r / 4;

  // shading effect: 0=nothing 1,2,3=draw outer ring of darker shade (1 to 3)
  // int se = r % 4;

  // for the moment plainly ignore the theta stuff

  // check for valid direction, assume 100,60 if none given
  rdir = dir;
  if (rdir == _xypoint(0, 0))
    rdir = _xypoint(-50, -50);

  // renormalize direction vector to real radius
  rdir = rdir * rr / (int)sqrt(rdir.x*rdir.x + rdir.y*rdir.y);

  xpoints[0].x = p.x + rdir.x - rdir.x / 2;
  xpoints[0].y = p.y - rdir.y + rdir.y / 2;
  xpoints[1].x = p.x - rdir.y - rdir.x / 2;
  xpoints[1].y = p.y - rdir.x + rdir.y / 2;
  xpoints[2].x = p.x + rdir.y - rdir.x / 2;
  xpoints[2].y = p.y + rdir.x + rdir.y / 2;

  //  if (se != 0) {
  //    XSetForeground(x_display, fillGC, my_to_x[c1 + (4 - se)]);
  //    XFillPolygon(x_display, my_win, fillGC, xpoints, 3, Convex, CoordModeOrigin);
  //  }

  XSetForeground(x_display, fillGC, my_to_x[c1]);
  XFillPolygon(x_display, my_win, fillGC, xpoints, 3, Convex, CoordModeOrigin);
}



void graphics::draw_circle(const _xypoint& p, const int r,
			   const int col, const int colfill)
{
  if (colfill != -1) {
    XSetForeground(x_display, fillGC, my_to_x[colfill]);
    XFillArc(x_display, my_win, fillGC, p.x - r, p.y - r, 1 + r * 2, 1 + r * 2, 0, 360*64);
  }

  if (col != -1) {
    XSetForeground(x_display, fillGC, my_to_x[col]);
    XDrawArc(x_display, my_win, fillGC, p.x - r, p.y - r, 1 + r * 2, 1 + r * 2, 0, 360*64);
  }
}



void graphics::draw_planetname(const int xp, const int yp, const int color, const myString& name)
{
  // correction for font should go here
  display->draw_smallstring(xp - 4*name.length()/2 + 1,
			    yp + 9, color, name);
}



void graphics::draw_marker(const int xp, const int yp, 
			   const _marktype marktype, const int markcolor)
{
  XSetForeground(x_display, useGC, my_to_x[markcolor]);

  switch(marktype) {
  case MT_NONE:
    break;

  case MT_TWODOTS: // two dots (one is just invisible)
    XDrawLine(x_display, my_win, useGC, xp - 1, yp, xp + 1, yp);
    break;

  case MT_CROSS: // the cross
    XDrawLine(x_display, my_win, useGC, xp - 1, yp, xp + 1, yp);
    XDrawLine(x_display, my_win, useGC, xp, yp - 1, xp, yp + 1);
    break;

  case MT_EMPTYBOX: // the empty box
    XDrawLine(x_display, my_win, useGC, xp - 1, yp - 1, xp + 1, yp - 1);
    XDrawLine(x_display, my_win, useGC, xp + 1, yp - 1, xp + 1, yp + 1);
    XDrawLine(x_display, my_win, useGC, xp + 1, yp + 1, xp - 1, yp + 1);
    XDrawLine(x_display, my_win, useGC, xp - 1, yp + 1, xp - 1, yp);
    break;

  case MT_SQUARE: // the square
    XFillRectangle(x_display, my_win, useGC, xp - 1, yp - 1, 3, 3);
    break;

  case MT_CIRCLE: // a circle, useful for fleets orbiting planets
    XDrawArc(x_display, my_win, useGC, xp - 3, yp - 3, 7, 7, 0, 360*64);
    break;

  case MT_FLAG: // a flag
    XDrawLine(x_display, my_win, useGC, xp, yp, xp, yp - 11);
    XFillRectangle(x_display, my_win, useGC, xp, yp - 11, 7, 5);
    break;
  }
}



void graphics::draw_line(const _xypoint& f, const _xypoint& t, const int col)
{
  XSetForeground(x_display, useGC, my_to_x[col]);
  XDrawLine(x_display, my_win, useGC, f.x, f.y, t.x, t.y);  
}



void graphics::draw_owners(const int y, const int x, 
			   const int x0, int xspan, const int zoom,
			   const short int xlen, const short int color[],
			   const int xpos[], const int color_filter[])
{
  if (xlen == 0)
    return;

  int i;

  // find starting span
  for (i = 0; i < xlen; i++)
    if (xpos[i + 1] > x0)
      break;

  if (i == xlen)
    return;

  int shift = zoom - 1;

  int xoff = x - x0;
  xspan += x0;
  int nx = 0;
  int curr_x;

  for (curr_x = (x0 >> shift); i < xlen && nx != xspan; i++, curr_x = nx) {
    nx = xpos[i + 1] >> shift;
    if (nx > xspan)
      nx = xspan;

    if (color[i] != -1) {
      if (color_filter)
	XSetForeground(x_display, useGC, my_to_x[COL_RACES + 4 * color_filter[color[i]]]);
      else
	XSetForeground(x_display, useGC, my_to_x[COL_RACES + 4 * color[i]]);

      XDrawLine(x_display, my_win, useGC, curr_x + xoff, y, nx + xoff - 1, y);
    }
  }

  done();
}


void graphics::clear(void)
{
  XSetForeground(x_display, fillGC, my_to_x[0]);
  XFillRectangle(x_display, my_win, fillGC, 0, 0, gra_xres, gra_yres);
}


void graphics::done(void)
{
  XFlush(x_display);
}

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#define XK_MISCELLANY
#include <X11/keysymdef.h>

#include <X11/cursorfont.h>
#include <X11/Xatom.h>

extern "C" {
#include <forms.h>
}
#include "../xforms/pfunc.h"


#define EVENT_MASK   KeyPressMask|KeyReleaseMask|ButtonReleaseMask|\
                     ExposureMask|ButtonPressMask|LeaveWindowMask|\
                     EnterWindowMask

#define SHIFT_PRESSED 0x0001
#define CTRL_PRESSED  0x0002
#define ALT_PRESSED   0x0004

extern int MAX_RADIUS;  // now user-selectable

const int COL_BLACK     = 0;
const int COL_PENSCAN   = 1;
const int COL_SCAN      = 2;
const int COL_WHITE     = 1 * 4;
const int COL_GREY      = 2 * 4;
const int COL_GREENHAB  = 3 * 4;
const int COL_YELLOWHAB = 4 * 4;
const int COL_REDHAB    = 5 * 4;
const int COL_IRON      = 6 * 4;
const int COL_BORA      = 7 * 4;
const int COL_GERM      = 8 * 4;
const int COL_RACES     = 9 * 4;

const int XFCOL_IRON    = 0;
const int XFCOL_BORA    = 2;
const int XFCOL_GERM    = 4;
const int XFCOL_RACES   = 6;


// marker types for planets
enum _marktype {
  MT_NONE = 0,
  MT_TWODOTS = 1,
  MT_CROSS = 2,
  MT_EMPTYBOX = 3,
  MT_SQUARE = 4,
  MT_CIRCLE = 5,
  MT_FLAG = 6
};

const int MAX_MARKER = 6;


struct _mindial {
  int now;
  int next;
  int conc;
  int mining;
};



struct _envdial {
  int current;
  int original;
  int tform;
  int maxtform;
  int habmin;
  int habmax;
};



class graphics {
  char* geomstring;
  Visual* visual;
  Window rootw;
  GC useGC, fillGC, smallGC;
  Cursor busy_cursor, norm_cursor;
  Colormap x_cmap;
  Window my_win;
  bool inwindow;
  Display* x_display;
  int x_screen;
  Font my_font;
  Font small_font;
  int sca_mask;
  bool running_fine;

  int gra_xres;
  int gra_yres;

  FD_MapControl* xf_mc;
  FD_PlanetaryFunction* xf_pfe;
  FD_PlanetStatus* xf_ps;
  FD_PlanetSimulation* xf_pm;
  FD_PlanetViews* xf_pv;
  
  int curr_vwp;
  bool pfe_menu_changed; // workaround

  int mineraldial_scale;
  int mineralobjects_lastowner;
  _mindial mineral_dials[3];
  _envdial environment_dials[3];

  int update_mask(KeySym k, int type);
  graphics& operator=(const graphics&);
  graphics(const graphics&);

  int minerals_to_display(const int v, const int w);

public:
  FL_OBJECT* cbobj;

public:
  void display_handle_event(XEvent* ev);
  graphics(const int xresol, const int yresol, const char* title);
  ~graphics(void);
  void create_palette(void);
  void set_window_title(const String& title);
  void error_dialog(const String& msg);
  String ask_for_smf_file(void);
  void draw_string(const int xp, const int yp, const int color, const char* str);
  void draw_smallstring(const int xp, const int yp, const int color, const char* str);
  void set_mineraldial_scale(const int i);
  void load_mineralobject(void);
  void draw_mineral_handler(FL_OBJECT* ob, const int i);
  void draw_environment_handler(FL_OBJECT* ob, const int i);
  void draw_fat_circle_arc(const int xp, const int yp, const int r, const int c1, const int thetamin = 0, const int thetaspan = 360*64); 
  void draw_triangle_pie(const _xypoint& p, const _xypoint& dir, const int r, const int c1, const int thetamin = 0, const int thetaspan = 360*64);
  void draw_circle(const _xypoint& p, const int r, const int col, const int colfill);
  void draw_planetname(const int xp, const int yp, const int color, const String& name);
  void draw_marker(const int xp, const int yp, const _marktype marktype, const int markcolor);
  void draw_line(const _xypoint& f, const _xypoint& t, const int col);
  void draw_owners(const int y, const int x, const int x0, int xspan, const int zoom, const short int xlen, const short int color[], const int xpos[], const int col_filter[]);
  void done(void);
  void clear(void);
  bool didntstart(void)
    { return !running_fine; }
  void form_initial_update(void);
  void show_planetstatus(void);
  void hide_planetstatus(void);
  void show_planetsimulation(void);
  void hide_planetsimulation(void);
  void select_planet(const _xypoint& mousepos);
  void load_planetstatus(void);
  void toggle_mapcontrol(void);
  void toggle_pfuncedit(void);
  void toggle_pfunclist(void);
  void load_pfunclist(void);
  void showselected_pfunclist(void);
  void load_pfunction(void);
  void write_pfunction(planetary_function* pf);
  void unload_pfunction(void);
  void init_number_menu(void);
  void redraw_map(void);
  void interact(void);
  void auto_redraw_map(void);
  void scroll_map(const int dir);
  void set_map_future(int data);
  void select_viewpoint(void);
  void pfunction_changed(void)
    { pfe_menu_changed = true; }
};

// outside, since it can be called before creation of graphics window
void set_colormap_color(const int c, int r, int g, int b);
void set_max_pie_radius(int r);

#ifndef FD_PlanetaryFunction_h_
#define FD_PlanetaryFunction_h_
/* Header file generated with fdesign. */

/** Callback routines and free object handlers **/

extern void pfecb_apply(FL_OBJECT *, long);
extern void pfecb_cancel(FL_OBJECT *, long);
extern void pfecb_selected(FL_OBJECT *, long);
extern void pfecb_close(FL_OBJECT *, long);
extern void pfecb_accept_and_next(FL_OBJECT *, long);
extern void pfecb_accept_and_prev(FL_OBJECT *, long);
extern void pfecb_delete(FL_OBJECT *, long);
extern void pfecb_insert(FL_OBJECT *, long);

extern void mccb_scrollmap(FL_OBJECT *, long);
extern void mccb_setfuture(FL_OBJECT *, long);
extern void mccb_setraceviewpoint(FL_OBJECT *, long);
extern void mccb_setbkgmode(FL_OBJECT *, long);
extern void mccb_pflistio(FL_OBJECT *, long);
extern void mccb_pfeditorwindow(FL_OBJECT *, long);
extern void mccb_setscaneff(FL_OBJECT *, long);
extern void mccb_alliances(FL_OBJECT *, long);

extern int freeobj_ps_ironiumdial_handle(FL_OBJECT *, int, FL_Coord, FL_Coord,
			int, void *);
extern int freeobj_ps_boraniumdial_handle(FL_OBJECT *, int, FL_Coord, FL_Coord,
			int, void *);
extern int freeobj_ps_germaniumdial_handle(FL_OBJECT *, int, FL_Coord, FL_Coord,
			int, void *);
extern int freeobj_ps_gravitydial_handle(FL_OBJECT *, int, FL_Coord, FL_Coord,
			int, void *);
extern int freeobj_ps_termpdial_handle(FL_OBJECT *, int, FL_Coord, FL_Coord,
			int, void *);
extern int freeobj_ps_raddial_handle(FL_OBJECT *, int, FL_Coord, FL_Coord,
			int, void *);
extern void pscb_closewindow(FL_OBJECT *, long);
extern void pscb_setminscale(FL_OBJECT *, long);
extern void pscb_settestobject(FL_OBJECT *, long);
extern void pscb_viewsimulation(FL_OBJECT *, long);


extern void pmcb_close(FL_OBJECT *, long);


/**** Forms and Objects ****/

typedef struct {
	FL_FORM *PlanetaryFunction;
	void *vdata;
	char *cdata;
	long  ldata;
	FL_OBJECT *pfe_description;
	FL_OBJECT *pfe_mask_circles;
	FL_OBJECT *pfe_input_par1;
	FL_OBJECT *pfe_input_par2;
	FL_OBJECT *pfe_input_par3;
	FL_OBJECT *pfe_input_par4;
	FL_OBJECT *pfe_mask_marker;
	FL_OBJECT *pfe_mask_flag;
	FL_OBJECT *pfe_mode;
	FL_OBJECT *pfe_number;
	FL_OBJECT *pfe_apply;
	FL_OBJECT *pfe_cancel;
	FL_OBJECT *pfe_selected;
	FL_OBJECT *pfe_mask_lines;
	FL_OBJECT *pfe_mask_name;
	FL_OBJECT *pfe_mask_data;
	FL_OBJECT *accept_and_next;
	FL_OBJECT *accept_and_prev;
	FL_OBJECT *delete;
	FL_OBJECT *insert;
} FD_PlanetaryFunction;

extern FD_PlanetaryFunction * create_form_PlanetaryFunction(void);
typedef struct {
	FL_FORM *MapControl;
	void *vdata;
	char *cdata;
	long  ldata;
	FL_OBJECT *mc_resetmap;
	FL_OBJECT *mc_upleft;
	FL_OBJECT *mc_up;
	FL_OBJECT *mc_upright;
	FL_OBJECT *mc_left;
	FL_OBJECT *mc_right;
	FL_OBJECT *mc_downleft;
	FL_OBJECT *mc_down;
	FL_OBJECT *mc_downright;
	FL_OBJECT *mc_future;
	FL_OBJECT *mc_decfuture;
	FL_OBJECT *mc_incfuture;
	FL_OBJECT *mc_race1;
	FL_OBJECT *mc_redraw;
	FL_OBJECT *mc_autoredraw;
	FL_OBJECT *mc_race3;
	FL_OBJECT *mc_race2;
	FL_OBJECT *mc_race4;
	FL_OBJECT *mc_race5;
	FL_OBJECT *mc_race7;
	FL_OBJECT *mc_race6;
	FL_OBJECT *mc_race8;
	FL_OBJECT *mc_race9;
	FL_OBJECT *mc_race11;
	FL_OBJECT *mc_race10;
	FL_OBJECT *mc_race12;
	FL_OBJECT *mc_race13;
	FL_OBJECT *mc_race15;
	FL_OBJECT *mc_race14;
	FL_OBJECT *mc_race16;
	FL_OBJECT *mc_mapmode;
	FL_OBJECT *mc_quit;
	FL_OBJECT *mc_center;
	FL_OBJECT *mc_zoomout;
	FL_OBJECT *mc_zoomin;
	FL_OBJECT *mc_pfload;
	FL_OBJECT *mc_pfsave;
	FL_OBJECT *mc_pfeditor;
	FL_OBJECT *mc_scaneff;
	FL_OBJECT *mc_alliances;
} FD_MapControl;

extern FD_MapControl * create_form_MapControl(void);
typedef struct {
	FL_FORM *PlanetStatus;
	void *vdata;
	char *cdata;
	long  ldata;
	FL_OBJECT *ps_popfilldial;
	FL_OBJECT *ps_popfill;
	FL_OBJECT *ps_popgrowth;
	FL_OBJECT *ps_population;
	FL_OBJECT *ps_ironium;
	FL_OBJECT *ps_boranium;
	FL_OBJECT *ps_germanium;
	FL_OBJECT *ps_mines;
	FL_OBJECT *ps_factories;
	FL_OBJECT *ps_defenses;
	FL_OBJECT *ps_scanning;
	FL_OBJECT *ps_stbdamage;
	FL_OBJECT *ps_starbasename;
	FL_OBJECT *ps_gaterange;
	FL_OBJECT *ps_massdriver;
	FL_OBJECT *ps_planetname;
	FL_OBJECT *ps_position;
	FL_OBJECT *ps_type;
	FL_OBJECT *ps_authsource;
	FL_OBJECT *ps_trustedsource;
	FL_OBJECT *ps_owner;
	FL_OBJECT *ps_reportage;
	FL_OBJECT *routing;
	FL_OBJECT *ps_ownhabnow;
	FL_OBJECT *resources;
	FL_OBJECT *ps_ironiumdial;
	FL_OBJECT *ps_boraniumdial;
	FL_OBJECT *ps_germaniumdial;
	FL_OBJECT *ps_gravitydial;
	FL_OBJECT *ps_termpdial;
	FL_OBJECT *ps_raddial;
	FL_OBJECT *ps_close;
	FL_OBJECT *ownhabtformed;
	FL_OBJECT *ownhabmaxtformed;
	FL_OBJECT *habnow;
	FL_OBJECT *habtformed;
	FL_OBJECT *habmaxtformed;
	FL_OBJECT *ironconc;
	FL_OBJECT *boraconc;
	FL_OBJECT *germconc;
	FL_OBJECT *minscale;
	FL_OBJECT *testobject;
	FL_OBJECT *ironobjects;
	FL_OBJECT *boraobjects;
	FL_OBJECT *germobjects;
	FL_OBJECT *resobjects;
} FD_PlanetStatus;

extern FD_PlanetStatus * create_form_PlanetStatus(void);
typedef struct {
	FL_FORM *PlanetViews;
	void *vdata;
	char *cdata;
	long  ldata;
	FL_OBJECT *close;
	FL_OBJECT *import;
	FL_OBJECT *save;
	FL_OBJECT *delete;
	FL_OBJECT *clone;
	FL_OBJECT *export;
	FL_OBJECT *movedown;
	FL_OBJECT *moveup;
} FD_PlanetViews;

extern FD_PlanetViews * create_form_PlanetViews(void);
typedef struct {
	FL_FORM *PlanetSimulation;
	void *vdata;
	char *cdata;
	long  ldata;
	FL_OBJECT *planetname;
	FL_OBJECT *messages;
} FD_PlanetSimulation;

extern FD_PlanetSimulation * create_form_PlanetSimulation(void);

#endif /* FD_PlanetaryFunction_h_ */

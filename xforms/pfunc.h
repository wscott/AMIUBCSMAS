#ifndef FD_PlanetaryFunction_h_
#define FD_PlanetaryFunction_h_
/* Header file generated with fdesign. */

/** Callback routines and free object handlers **/

extern void pfecb_number(FL_OBJECT *ob, long data);
extern void pfecb_accept_and_prev(FL_OBJECT *, long);
extern void pfecb_accept_and_next(FL_OBJECT *, long);
extern void pfecb_apply(FL_OBJECT *, long);
extern void pfecb_cancel(FL_OBJECT *, long);
extern void pfecb_selected(FL_OBJECT *, long);
extern void pfecb_close(FL_OBJECT *, long);
extern void pfecb_insert(FL_OBJECT *, long);
extern void pfecb_delete(FL_OBJECT *, long);

extern void mccb_pflistwindow(FL_OBJECT *, long);
extern void mccb_pfeditorwindow(FL_OBJECT *, long);
extern void mccb_scrollmap(FL_OBJECT *, long);
extern void mccb_setfuture(FL_OBJECT *, long);
extern void mccb_setraceviewpoint(FL_OBJECT *, long);
extern void mccb_setbkgmode(FL_OBJECT *, long);
extern void mccb_setscaneff(FL_OBJECT *, long);
extern void mccb_alliances(FL_OBJECT *, long);

extern void pvcb_close(FL_OBJECT *, long);
extern void pvcb_load(FL_OBJECT *, long);
extern void pvcb_save(FL_OBJECT *, long);
extern void pvcb_delete(FL_OBJECT *, long);
extern void pvcb_clone(FL_OBJECT *, long);
extern void pvcb_rename(FL_OBJECT *, long);
extern void pvcb_pfeditor(FL_OBJECT *, long);
extern void pvcb_export(FL_OBJECT *, long);
extern void pvcb_move(FL_OBJECT *, long);
extern void pvcb_select(FL_OBJECT *, long);

extern int cb_mywin_handler(XEvent* xev, void* data);

extern int freeobj_ironiumdial_handle(FL_OBJECT *, int, FL_Coord, FL_Coord,
		   	int, void *);
extern int freeobj_boraniumdial_handle(FL_OBJECT *, int, FL_Coord, FL_Coord,
		   	int, void *);
extern int freeobj_germaniumdial_handle(FL_OBJECT *, int, FL_Coord, FL_Coord,
		   	int, void *);
extern int freeobj_gravitydial_handle(FL_OBJECT *, int, FL_Coord, FL_Coord,
		   	int, void *);
extern int freeobj_termpdial_handle(FL_OBJECT *, int, FL_Coord, FL_Coord,
		   	int, void *);
extern int freeobj_raddial_handle(FL_OBJECT *, int, FL_Coord, FL_Coord,
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
	FL_OBJECT *description;
	FL_OBJECT *input_par[5];
	FL_OBJECT *mask_circles;
	FL_OBJECT *mask_lines;
	FL_OBJECT *mask_data;
	FL_OBJECT *mask_marker;
	FL_OBJECT *mask_name;
	FL_OBJECT *mask_flag;
	FL_OBJECT *mode;
	FL_OBJECT *number;
	FL_OBJECT *selected;
} FD_PlanetaryFunction;

extern FD_PlanetaryFunction * create_form_PlanetaryFunction(void);
typedef struct {
	FL_FORM *MapControl;
	void *vdata;
	char *cdata;
	long  ldata;
	FL_OBJECT *pflist;
	FL_OBJECT *pfeditor;
	FL_OBJECT *ffeditor;
	FL_OBJECT *resetmap;
	FL_OBJECT *upleft;
	FL_OBJECT *up;
	FL_OBJECT *upright;
	FL_OBJECT *left;
	FL_OBJECT *right;
	FL_OBJECT *downleft;
	FL_OBJECT *down;
	FL_OBJECT *downright;
	FL_OBJECT *future;
	FL_OBJECT *decfuture;
	FL_OBJECT *incfuture;
	FL_OBJECT *racebox;
	FL_OBJECT *racetitle;
	FL_OBJECT *race[16];
	FL_OBJECT *redraw;
	FL_OBJECT *autoredraw;
	FL_OBJECT *mapmode;
	FL_OBJECT *quit;
	FL_OBJECT *center;
	FL_OBJECT *zoomout;
	FL_OBJECT *zoomin;
        FL_OBJECT *scaneff;
        FL_OBJECT *alliances;
} FD_MapControl;

extern FD_MapControl * create_form_MapControl(void);

typedef struct {
	FL_FORM *PlanetStatus;
	void *vdata;
	char *cdata;
	long  ldata;
	FL_OBJECT *ironium;
	FL_OBJECT *boranium;
	FL_OBJECT *germanium;
	FL_OBJECT *mines;
	FL_OBJECT *factories;
	FL_OBJECT *defenses;
	FL_OBJECT *scanning;
	FL_OBJECT *stbdamage;
	FL_OBJECT *starbasename;
	FL_OBJECT *gaterange;
	FL_OBJECT *massdriver;
	FL_OBJECT *popgrowth;
	FL_OBJECT *population;
	FL_OBJECT *popfilldial;
	FL_OBJECT *popfill;
	FL_OBJECT *planetname;
	FL_OBJECT *position;
	FL_OBJECT *type;
	FL_OBJECT *authsource;
	FL_OBJECT *trustedsource;
	FL_OBJECT *owner;
	FL_OBJECT *reportage;
	FL_OBJECT *routing;
	FL_OBJECT *habowner;
        FL_OBJECT *habvpoint;
	FL_OBJECT *ownhabnow;
	FL_OBJECT *ownhabmaxtformed;
	FL_OBJECT *ownhabtformed;
	FL_OBJECT *habnow;
	FL_OBJECT *habmaxtformed;
	FL_OBJECT *habtformed;
	FL_OBJECT *resources;
	FL_OBJECT *ironconc;
	FL_OBJECT *boraconc;
	FL_OBJECT *germconc;
	FL_OBJECT *ironiumdial;
	FL_OBJECT *boraniumdial;
	FL_OBJECT *germaniumdial;
	FL_OBJECT *gravitydial;
	FL_OBJECT *tempdial;
	FL_OBJECT *raddial;
	FL_OBJECT *close;
	FL_OBJECT *minscale;
	FL_OBJECT *testobject;
	FL_OBJECT *minobjects[3];
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
	FL_OBJECT *del;
	FL_OBJECT *clone;
	FL_OBJECT *rename;
	FL_OBJECT *pfeditor;
	FL_OBJECT *export;
	FL_OBJECT *movedown;
	FL_OBJECT *moveup;
	FL_OBJECT *pvlist;
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

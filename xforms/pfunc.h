#ifndef FD_DisplayFunction_h_
#define FD_DisplayFunction_h_

/* freeobject support structures */

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
extern void mccb_fflistwindow(FL_OBJECT *, long);
extern void mccb_ffeditorwindow(FL_OBJECT *, long);
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
extern void pscb_firepacket(FL_OBJECT *, long);
extern void pscb_bombplanet(FL_OBJECT *, long);
extern void pscb_setminscale(FL_OBJECT *, long);
extern void pscb_settestobject(FL_OBJECT *, long);
extern void pscb_viewsimulation(FL_OBJECT *, long);

extern void pmcb_close(FL_OBJECT *, long);

extern void pfcb_fastkiller(FL_OBJECT *, long);
extern void pfcb_cheapkiller(FL_OBJECT *, long);
extern void pfcb_close(FL_OBJECT *, long);

extern void rrcb_close(FL_OBJECT *, long);

/**** Forms and Objects ****/

typedef struct {
	FL_FORM *DisplayFunction;
	void *vdata;
	char *cdata;
	long  ldata;
	FL_OBJECT *description;
	FL_OBJECT *input_par[10];
	FL_OBJECT *mask_circles;
	FL_OBJECT *mask_lines;
	FL_OBJECT *mask_data;
	FL_OBJECT *mask_marker;
	FL_OBJECT *mask_name;
	FL_OBJECT *mask_flag;
	FL_OBJECT *mode;
	FL_OBJECT *number;
	FL_OBJECT *selected;
} FD_DisplayFunction;

extern FD_DisplayFunction * create_form_DisplayFunction(void);
typedef struct {
	FL_FORM *MapControl;
	void *vdata;
	char *cdata;
	long  ldata;
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

  /* non xforms data for freeobject handlers */
        int statusnumber;
        int mineraldial_scale;
        int mineralobjects_lastowner;
        _mindial mineral_dials[3];
        _envdial environment_dials[3];
} FD_PlanetStatus;

extern FD_PlanetStatus * create_form_PlanetStatus(void);

typedef struct {
	FL_FORM *ObjectViews;
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
} FD_ObjectViews;

extern FD_ObjectViews * create_form_ObjectViews(void);

typedef struct {
	FL_FORM *PlanetSimulation;
	void *vdata;
	char *cdata;
	long  ldata;
	FL_OBJECT *planetname;
	FL_OBJECT *messages;

  /* non xforms data */
        int statusnumber;
} FD_PlanetSimulation;

extern FD_PlanetSimulation * create_form_PlanetSimulation(void);

typedef struct {
	FL_FORM *PacketFiring;
	void *vdata;
	char *cdata;
	long  ldata;
	FL_OBJECT *frameuno;
	FL_OBJECT *planetname[2];
	FL_OBJECT *planetdistance;
	FL_OBJECT *close;
	FL_OBJECT *mineralspent;
	FL_OBJECT *twindriver[2];
	FL_OBJECT *racenotes[2];
	FL_OBJECT *cheapkiller;
	FL_OBJECT *packetdirection;
	FL_OBJECT *fastkiller;
	FL_OBJECT *population[2];
	FL_OBJECT *ndefenses[2];
	FL_OBJECT *defcoverage[2];
	FL_OBJECT *colkill[8];
	FL_OBJECT *mineral[8];
	FL_OBJECT *travel[8];
	FL_OBJECT *warp[8];
	FL_OBJECT *defdestroy[8];
	FL_OBJECT *terraform[8];
	FL_OBJECT *framedue;
	FL_OBJECT *driverwarp[2];
	FL_OBJECT *increasewarp1;
	FL_OBJECT *lowerwarp1;
	FL_OBJECT *increasewarp2;
	FL_OBJECT *lowerwarp2;
} FD_PacketFiring;

extern FD_PacketFiring * create_form_PacketFiring(void);

typedef struct {
	FL_FORM *IntroTitle;
	void *vdata;
	char *cdata;
	long  ldata;
	FL_OBJECT *statusmsg;
} FD_IntroTitle;

extern FD_IntroTitle * create_form_IntroTitle(void);

typedef struct {
	FL_FORM *RR_RaceInfo;
	void *vdata;
	char *cdata;
	long  ldata;
	FL_OBJECT *techterra[3];
	FL_OBJECT *habgraph;
	FL_OBJECT *prt_lrt;
	FL_OBJECT *col_res;
	FL_OBJECT *factories;
	FL_OBJECT *mines;
	FL_OBJECT *res100pct;
	FL_OBJECT *techcost[6];
	FL_OBJECT *techlevel[6];
	FL_OBJECT *totalplanets;
	FL_OBJECT *totalpop;
	FL_OBJECT *totalfleets;
	FL_OBJECT *shiptypes;
	FL_OBJECT *habdial[3];
	FL_OBJECT *explored;
	FL_OBJECT *playern;
	FL_OBJECT *reliability;
} FD_RR_RaceInfo;

extern FD_RR_RaceInfo * create_form_RR_RaceInfo(void);

typedef struct {
	FL_FORM *RR_ReportLog;
	void *vdata;
	char *cdata;
	long  ldata;
        FL_OBJECT* messages;
} FD_RR_ReportLog;

extern FD_RR_ReportLog * create_form_RR_ReportLog(void);

typedef struct {
	FL_FORM *RR_Comparisons;
	void *vdata;
	char *cdata;
	long  ldata;
	FL_OBJECT *racegraph;
	FL_OBJECT *displaywhat;
	FL_OBJECT *compare;
} FD_RR_Comparisons;

extern FD_RR_Comparisons * create_form_RR_Comparisons(void);

typedef struct {
	FL_FORM *RR_DesignsObjects;
	void *vdata;
	char *cdata;
	long  ldata;
        FL_OBJECT *design[16];
        FL_OBJECT *minerals[16][3];
        FL_OBJECT *resources[16];
        FL_OBJECT *weight[16];
        FL_OBJECT *basehull[16];
} FD_RR_DesignsObjects;

extern FD_RR_DesignsObjects * create_form_RR_DesignsObjects(void);

typedef struct {
	FL_FORM *RacialReport;
	void *vdata;
	char *cdata;
	long  ldata;
	FL_OBJECT *race_isanalyzed;
	FL_OBJECT *race_issource;
	FL_OBJECT *race_names;
} FD_RacialReport;

extern FD_RacialReport * create_form_RacialReport(FD_RR_RaceInfo* tf1, FD_RR_ReportLog* tf2, FD_RR_Comparisons* tf3, FD_RR_DesignsObjects* tf4);

#endif /* FD_DisplayFunction_h_ */

/** Header file generated with fdesign on Fri Nov 13 22:33:00 1998.**/

#ifndef FD_PlanetaryFunction_h_
#define FD_PlanetaryFunction_h_

/** Callbacks, globals and object handlers **/
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
extern void pscb_firepacket(FL_OBJECT *, long);
extern void pscb_bombplanet(FL_OBJECT *, long);


extern void pmcb_close(FL_OBJECT *, long);

extern void pfcb_close(FL_OBJECT *, long);
extern void pfcb_cheapkiller(FL_OBJECT *, long);
extern void pfcb_fastkiller(FL_OBJECT *, long);



extern int freeobj_gravdial_handle(FL_OBJECT *, int, FL_Coord, FL_Coord,
			int, void *);
extern int freeobj_tempdial_handle(FL_OBJECT *, int, FL_Coord, FL_Coord,
			int, void *);
extern int freeobj_raddial_handle(FL_OBJECT *, int, FL_Coord, FL_Coord,
			int, void *);







/**** Forms and Objects ****/
typedef struct {
	FL_FORM *PlanetaryFunction;
	void *vdata;
	char *cdata;
	long  ldata;
	FL_OBJECT *description;
	FL_OBJECT *mask_circles;
	FL_OBJECT *input_par1;
	FL_OBJECT *input_par2;
	FL_OBJECT *input_par3;
	FL_OBJECT *input_par4;
	FL_OBJECT *mask_marker;
	FL_OBJECT *mask_flag;
	FL_OBJECT *mode;
	FL_OBJECT *number;
	FL_OBJECT *apply;
	FL_OBJECT *cancel;
	FL_OBJECT *input_par5;
	FL_OBJECT *selected;
	FL_OBJECT *mask_lines;
	FL_OBJECT *mask_name;
	FL_OBJECT *mask_data;
	FL_OBJECT *accept_and_next;
	FL_OBJECT *accept_and_prev;
	FL_OBJECT *delete;
	FL_OBJECT *insert;
	FL_OBJECT *input_par6;
	FL_OBJECT *input_par7;
	FL_OBJECT *input_par8;
	FL_OBJECT *input_par9;
	FL_OBJECT *input_par10;
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
	FL_OBJECT *popfilldial;
	FL_OBJECT *popfill;
	FL_OBJECT *popgrowth;
	FL_OBJECT *population;
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
	FL_OBJECT *planetname;
	FL_OBJECT *position;
	FL_OBJECT *type;
	FL_OBJECT *authsource;
	FL_OBJECT *trustedsource;
	FL_OBJECT *owner;
	FL_OBJECT *reportage;
	FL_OBJECT *routing;
	FL_OBJECT *ownhabnow;
	FL_OBJECT *resources;
	FL_OBJECT *ironiumdial;
	FL_OBJECT *boraniumdial;
	FL_OBJECT *germaniumdial;
	FL_OBJECT *gravitydial;
	FL_OBJECT *termpdial;
	FL_OBJECT *raddial;
	FL_OBJECT *close;
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
typedef struct {
	FL_FORM *PacketFiring;
	void *vdata;
	char *cdata;
	long  ldata;
	FL_OBJECT *frameuno;
	FL_OBJECT *planetname1;
	FL_OBJECT *planetdistance;
	FL_OBJECT *close;
	FL_OBJECT *mineralspent;
	FL_OBJECT *twindriver1;
	FL_OBJECT *racenotes1;
	FL_OBJECT *cheapkiller;
	FL_OBJECT *packetdirection;
	FL_OBJECT *fastkiller;
	FL_OBJECT *population1;
	FL_OBJECT *ndefenses1;
	FL_OBJECT *defcoverage1;
	FL_OBJECT *colkill1;
	FL_OBJECT *mineral1;
	FL_OBJECT *travel1;
	FL_OBJECT *warp1;
	FL_OBJECT *defdestroy1;
	FL_OBJECT *terraform1;
	FL_OBJECT *colkill2;
	FL_OBJECT *travel2;
	FL_OBJECT *warp2;
	FL_OBJECT *defdestroy2;
	FL_OBJECT *terraform2;
	FL_OBJECT *colkill3;
	FL_OBJECT *travel3;
	FL_OBJECT *warp3;
	FL_OBJECT *defdestroy3;
	FL_OBJECT *terraform3;
	FL_OBJECT *colkill4;
	FL_OBJECT *travel4;
	FL_OBJECT *warp4;
	FL_OBJECT *defdestroy4;
	FL_OBJECT *terraform4;
	FL_OBJECT *colkill5;
	FL_OBJECT *travel5;
	FL_OBJECT *warp5;
	FL_OBJECT *defdestroy5;
	FL_OBJECT *terraform5;
	FL_OBJECT *colkill6;
	FL_OBJECT *travel6;
	FL_OBJECT *warp6;
	FL_OBJECT *defdestroy6;
	FL_OBJECT *terraform6;
	FL_OBJECT *colkill7;
	FL_OBJECT *travel7;
	FL_OBJECT *warp7;
	FL_OBJECT *defdestroy7;
	FL_OBJECT *terraform7;
	FL_OBJECT *framedue;
	FL_OBJECT *planetname2;
	FL_OBJECT *twindriver2;
	FL_OBJECT *racenotes2;
	FL_OBJECT *population2;
	FL_OBJECT *ndefenses2;
	FL_OBJECT *defcoverage2;
	FL_OBJECT *driverwarp1;
	FL_OBJECT *increasewarp1;
	FL_OBJECT *lowerwarp1;
	FL_OBJECT *driverwarp2;
	FL_OBJECT *increasewarp2;
	FL_OBJECT *lowerwarp2;
	FL_OBJECT *mineral2;
	FL_OBJECT *mineral3;
	FL_OBJECT *mineral4;
	FL_OBJECT *mineral5;
	FL_OBJECT *mineral6;
	FL_OBJECT *mineral7;
} FD_PacketFiring;

extern FD_PacketFiring * create_form_PacketFiring(void);
typedef struct {
	FL_FORM *IntroTitle;
	void *vdata;
	char *cdata;
	long  ldata;
} FD_IntroTitle;

extern FD_IntroTitle * create_form_IntroTitle(void);
typedef struct {
	FL_FORM *RacialReport;
	void *vdata;
	char *cdata;
	long  ldata;
	FL_OBJECT *race_isanalyzed;
	FL_OBJECT *race_issource;
	FL_OBJECT *tabfolder;
	FL_OBJECT *race_names;
} FD_RacialReport;

extern FD_RacialReport * create_form_RacialReport(void);
typedef struct {
	FL_FORM *RR_RaceInfo;
	void *vdata;
	char *cdata;
	long  ldata;
	FL_OBJECT *terrarad;
	FL_OBJECT *habgraph;
	FL_OBJECT *prt_lrt;
	FL_OBJECT *col_res;
	FL_OBJECT *factories;
	FL_OBJECT *mines;
	FL_OBJECT *res100pct;
	FL_OBJECT *costen;
	FL_OBJECT *techen;
	FL_OBJECT *totalplanets;
	FL_OBJECT *totalpop;
	FL_OBJECT *totalfleets;
	FL_OBJECT *shiptypes;
	FL_OBJECT *terratemp;
	FL_OBJECT *gravdial;
	FL_OBJECT *tempdial;
	FL_OBJECT *raddial;
	FL_OBJECT *explored;
	FL_OBJECT *playern;
	FL_OBJECT *reliability;
	FL_OBJECT *costwp;
	FL_OBJECT *techwe;
	FL_OBJECT *costpr;
	FL_OBJECT *techpr;
	FL_OBJECT *terragrav;
	FL_OBJECT *costco;
	FL_OBJECT *techco;
	FL_OBJECT *costel;
	FL_OBJECT *techel;
	FL_OBJECT *costbi;
	FL_OBJECT *techbi;
} FD_RR_RaceInfo;

extern FD_RR_RaceInfo * create_form_RR_RaceInfo(void);
typedef struct {
	FL_FORM *RR_ReportLog;
	void *vdata;
	char *cdata;
	long  ldata;
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
	FL_FORM *RR_Designs;
	void *vdata;
	char *cdata;
	long  ldata;
} FD_RR_Designs;

extern FD_RR_Designs * create_form_RR_Designs(void);
typedef struct {
	FL_FORM *RR_Filtering;
	void *vdata;
	char *cdata;
	long  ldata;
} FD_RR_Filtering;

extern FD_RR_Filtering * create_form_RR_Filtering(void);
typedef struct {
	FL_FORM *RR_Objects;
	void *vdata;
	char *cdata;
	long  ldata;
} FD_RR_Objects;

extern FD_RR_Objects * create_form_RR_Objects(void);

#endif /* FD_PlanetaryFunction_h_ */

/* Form definition file generated with fdesign. */

#include "forms.h"
#include <stdlib.h>
#include "o-pfunc.h"

static FL_PUP_ENTRY fdchoice_0[] =
{ 
    /*  itemtext   callback  shortcut   mode */
    { "stomp",	0,	"",	 FL_PUP_NONE},
    { "skip",	0,	"",	 FL_PUP_NONE},
    { "and",	0,	"",	 FL_PUP_NONE},
    { "or",	0,	"",	 FL_PUP_NONE},
    {0}
};

FD_PlanetaryFunction *create_form_PlanetaryFunction(void)
{
  FL_OBJECT *obj;
  FD_PlanetaryFunction *fdui = (FD_PlanetaryFunction *) fl_calloc(1, sizeof(*fdui));

  fdui->PlanetaryFunction = fl_bgn_form(FL_NO_BOX, 320, 260);
  obj = fl_add_box(FL_UP_BOX,0,0,320,260,"");
  fdui->pfe_description = obj = fl_add_text(FL_NORMAL_TEXT,10,40,300,40,"Text");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->pfe_mask_circles = obj = fl_add_button(FL_PUSH_BUTTON,120,80,30,20,"C");
  fdui->pfe_input_par1 = obj = fl_add_input(FL_NORMAL_INPUT,160,110,70,20,"Input");
  fdui->pfe_input_par2 = obj = fl_add_input(FL_NORMAL_INPUT,160,130,70,20,"Input");
  fdui->pfe_input_par3 = obj = fl_add_input(FL_NORMAL_INPUT,160,150,70,20,"Input");
  fdui->pfe_input_par4 = obj = fl_add_input(FL_NORMAL_INPUT,160,170,70,20,"Input");
  fdui->pfe_mask_marker = obj = fl_add_button(FL_PUSH_BUTTON,180,80,30,20,"M");
  fdui->pfe_mask_flag = obj = fl_add_button(FL_PUSH_BUTTON,270,80,30,20,"F");
  fdui->pfe_mode = obj = fl_add_choice(FL_NORMAL_CHOICE2,10,80,90,20,"");
    fl_set_object_boxtype(obj,FL_FRAME_BOX);
   fl_set_choice_entries(obj, fdchoice_0);
   fl_set_choice(obj,1);
  fdui->pfe_number = obj = fl_add_text(FL_NORMAL_TEXT,10,10,30,30,"1");
    fl_set_object_boxtype(obj,FL_FRAME_BOX);
    fl_set_object_lsize(obj,FL_MEDIUM_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->pfe_apply = obj = fl_add_button(FL_NORMAL_BUTTON,100,220,80,30,"Apply");
    fl_set_object_callback(obj,pfecb_apply,0);
  fdui->pfe_cancel = obj = fl_add_button(FL_NORMAL_BUTTON,10,220,80,30,"Cancel");
    fl_set_object_callback(obj,pfecb_cancel,0);
  obj = fl_add_input(FL_NORMAL_INPUT,160,190,70,20,"Input");
  fdui->pfe_selected = obj = fl_add_menu(FL_PULLDOWN_MENU,40,10,270,30,"Select a PFunction");
    fl_set_object_boxtype(obj,FL_FRAME_BOX);
    fl_set_object_lsize(obj,FL_MEDIUM_SIZE);
    fl_set_object_callback(obj,pfecb_selected,0);
  fdui->pfe_mask_lines = obj = fl_add_button(FL_PUSH_BUTTON,150,80,30,20,"L");
  fdui->pfe_mask_name = obj = fl_add_button(FL_PUSH_BUTTON,240,80,30,20,"N");
  fdui->pfe_mask_data = obj = fl_add_button(FL_PUSH_BUTTON,210,80,30,20,"D");
  obj = fl_add_button(FL_NORMAL_BUTTON,230,220,80,30,"Close");
    fl_set_object_callback(obj,pfecb_close,0);
  fdui->accept_and_next = obj = fl_add_button(FL_NORMAL_BUTTON,280,180,30,30,"@2");
    fl_set_object_callback(obj,pfecb_accept_and_next,0);
  fdui->accept_and_prev = obj = fl_add_button(FL_NORMAL_BUTTON,240,180,30,30,"@8");
    fl_set_object_callback(obj,pfecb_accept_and_prev,0);
  fdui->delete = obj = fl_add_button(FL_NORMAL_BUTTON,240,150,70,20,"Delete");
    fl_set_object_callback(obj,pfecb_delete,0);
  fdui->insert = obj = fl_add_button(FL_NORMAL_BUTTON,240,120,70,20,"Insert");
    fl_set_object_callback(obj,pfecb_insert,0);
  fl_end_form();

  fdui->PlanetaryFunction->fdui = fdui;

  return fdui;
}
/*---------------------------------------*/

FD_MapControl *create_form_MapControl(void)
{
  FL_OBJECT *obj;
  FD_MapControl *fdui = (FD_MapControl *) fl_calloc(1, sizeof(*fdui));

  fdui->MapControl = fl_bgn_form(FL_NO_BOX, 470, 370);
  obj = fl_add_box(FL_UP_BOX,0,0,470,370,"");
  obj = fl_add_text(FL_NORMAL_TEXT,320,10,60,30,"Planetary\nFunctions");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  obj = fl_add_frame(FL_ENGRAVED_FRAME,10,10,300,150,"");
  obj = fl_add_frame(FL_ENGRAVED_FRAME,310,10,80,150,"");
  obj = fl_add_box(FL_DOWN_BOX,10,170,450,200,"");
    fl_set_object_color(obj,FL_BLACK,FL_COL1);
  fdui->mc_resetmap = obj = fl_add_button(FL_NORMAL_BUTTON,130,130,50,30,"Reset");
    fl_set_object_callback(obj,mccb_scrollmap,-1);
  fdui->mc_upleft = obj = fl_add_button(FL_NORMAL_BUTTON,10,10,30,30,"@7");
    fl_set_object_callback(obj,mccb_scrollmap,7);
  fdui->mc_up = obj = fl_add_button(FL_NORMAL_BUTTON,50,10,30,30,"@8");
    fl_set_object_callback(obj,mccb_scrollmap,8);
  fdui->mc_upright = obj = fl_add_button(FL_NORMAL_BUTTON,90,10,30,30,"@9");
    fl_set_object_callback(obj,mccb_scrollmap,9);
  fdui->mc_left = obj = fl_add_button(FL_NORMAL_BUTTON,10,50,30,30,"@4");
    fl_set_object_callback(obj,mccb_scrollmap,4);
  fdui->mc_right = obj = fl_add_button(FL_NORMAL_BUTTON,90,50,30,30,"@6");
    fl_set_object_callback(obj,mccb_scrollmap,6);
  fdui->mc_downleft = obj = fl_add_button(FL_NORMAL_BUTTON,10,90,30,30,"@1");
    fl_set_object_callback(obj,mccb_scrollmap,1);
  fdui->mc_down = obj = fl_add_button(FL_NORMAL_BUTTON,50,90,30,30,"@2");
    fl_set_object_callback(obj,mccb_scrollmap,2);
  fdui->mc_downright = obj = fl_add_button(FL_NORMAL_BUTTON,90,90,30,30,"@3");
    fl_set_object_callback(obj,mccb_scrollmap,3);
  fdui->mc_future = obj = fl_add_input(FL_NORMAL_INPUT,150,100,40,20,"Future");
    fl_set_object_lalign(obj,FL_ALIGN_TOP);
    fl_set_object_callback(obj,mccb_setfuture,0);
  fdui->mc_decfuture = obj = fl_add_button(FL_NORMAL_BUTTON,130,100,20,20,"@4");
    fl_set_object_callback(obj,mccb_setfuture,-1);
  fdui->mc_incfuture = obj = fl_add_button(FL_NORMAL_BUTTON,190,100,20,20,"@6");
    fl_set_object_callback(obj,mccb_setfuture,1);
  fdui->mc_race1 = obj = fl_add_button(FL_NORMAL_BUTTON,40,200,180,20,"<no race 1>");
    fl_set_object_boxtype(obj,FL_NO_BOX);
    fl_set_object_color(obj,FL_BLACK,FL_COL1);
    fl_set_object_lcolor(obj,FL_COL1);
    fl_set_object_callback(obj,mccb_setraceviewpoint,1);
  obj = fl_add_text(FL_NORMAL_TEXT,160,170,150,30,"RACES");
    fl_set_object_boxtype(obj,FL_NO_BOX);
    fl_set_object_color(obj,FL_BLACK,FL_BLACK);
    fl_set_object_lcolor(obj,FL_WHITE);
    fl_set_object_lsize(obj,FL_MEDIUM_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
    fl_set_object_lstyle(obj,FL_BOLD_STYLE);
  fdui->mc_redraw = obj = fl_add_button(FL_NORMAL_BUTTON,250,130,50,30,"Redraw");
    fl_set_object_callback(obj,mccb_scrollmap,0);
  fdui->mc_autoredraw = obj = fl_add_button(FL_PUSH_BUTTON,190,130,50,30,"Auto\nRedraw");
  fdui->mc_race3 = obj = fl_add_button(FL_NORMAL_BUTTON,40,220,180,20,"<no race 3>");
    fl_set_object_boxtype(obj,FL_NO_BOX);
    fl_set_object_color(obj,FL_BLACK,FL_COL1);
    fl_set_object_lcolor(obj,FL_COL1);
    fl_set_object_callback(obj,mccb_setraceviewpoint,3);
  fdui->mc_race2 = obj = fl_add_button(FL_NORMAL_BUTTON,250,200,180,20,"<no race 2>");
    fl_set_object_boxtype(obj,FL_NO_BOX);
    fl_set_object_color(obj,FL_BLACK,FL_COL1);
    fl_set_object_lcolor(obj,FL_COL1);
    fl_set_object_callback(obj,mccb_setraceviewpoint,2);
  fdui->mc_race4 = obj = fl_add_button(FL_NORMAL_BUTTON,250,220,180,20,"<no race 4>");
    fl_set_object_boxtype(obj,FL_NO_BOX);
    fl_set_object_color(obj,FL_BLACK,FL_COL1);
    fl_set_object_lcolor(obj,FL_COL1);
    fl_set_object_callback(obj,mccb_setraceviewpoint,4);
  fdui->mc_race5 = obj = fl_add_button(FL_NORMAL_BUTTON,40,240,180,20,"<no race 5>");
    fl_set_object_boxtype(obj,FL_NO_BOX);
    fl_set_object_color(obj,FL_BLACK,FL_COL1);
    fl_set_object_lcolor(obj,FL_COL1);
    fl_set_object_callback(obj,mccb_setraceviewpoint,5);
  fdui->mc_race7 = obj = fl_add_button(FL_NORMAL_BUTTON,40,260,180,20,"<no race 7>");
    fl_set_object_boxtype(obj,FL_NO_BOX);
    fl_set_object_color(obj,FL_BLACK,FL_COL1);
    fl_set_object_lcolor(obj,FL_COL1);
    fl_set_object_callback(obj,mccb_setraceviewpoint,7);
  fdui->mc_race6 = obj = fl_add_button(FL_NORMAL_BUTTON,250,240,180,20,"<no race 6>");
    fl_set_object_boxtype(obj,FL_NO_BOX);
    fl_set_object_color(obj,FL_BLACK,FL_COL1);
    fl_set_object_lcolor(obj,FL_COL1);
    fl_set_object_callback(obj,mccb_setraceviewpoint,6);
  fdui->mc_race8 = obj = fl_add_button(FL_NORMAL_BUTTON,250,260,180,20,"<no race 8>");
    fl_set_object_boxtype(obj,FL_NO_BOX);
    fl_set_object_color(obj,FL_BLACK,FL_COL1);
    fl_set_object_lcolor(obj,FL_COL1);
    fl_set_object_callback(obj,mccb_setraceviewpoint,8);
  fdui->mc_race9 = obj = fl_add_button(FL_NORMAL_BUTTON,40,280,180,20,"<no race 9>");
    fl_set_object_boxtype(obj,FL_NO_BOX);
    fl_set_object_color(obj,FL_BLACK,FL_COL1);
    fl_set_object_lcolor(obj,FL_COL1);
    fl_set_object_callback(obj,mccb_setraceviewpoint,9);
  fdui->mc_race11 = obj = fl_add_button(FL_NORMAL_BUTTON,40,300,180,20,"<no race 11>");
    fl_set_object_boxtype(obj,FL_NO_BOX);
    fl_set_object_color(obj,FL_BLACK,FL_COL1);
    fl_set_object_lcolor(obj,FL_COL1);
    fl_set_object_callback(obj,mccb_setraceviewpoint,11);
  fdui->mc_race10 = obj = fl_add_button(FL_NORMAL_BUTTON,250,280,180,20,"<no race 10>");
    fl_set_object_boxtype(obj,FL_NO_BOX);
    fl_set_object_color(obj,FL_BLACK,FL_COL1);
    fl_set_object_lcolor(obj,FL_COL1);
    fl_set_object_callback(obj,mccb_setraceviewpoint,10);
  fdui->mc_race12 = obj = fl_add_button(FL_NORMAL_BUTTON,250,300,180,20,"<no race 12>");
    fl_set_object_boxtype(obj,FL_NO_BOX);
    fl_set_object_color(obj,FL_BLACK,FL_COL1);
    fl_set_object_lcolor(obj,FL_COL1);
    fl_set_object_callback(obj,mccb_setraceviewpoint,12);
  fdui->mc_race13 = obj = fl_add_button(FL_NORMAL_BUTTON,40,320,180,20,"<no race 13>");
    fl_set_object_boxtype(obj,FL_NO_BOX);
    fl_set_object_color(obj,FL_BLACK,FL_COL1);
    fl_set_object_lcolor(obj,FL_COL1);
    fl_set_object_callback(obj,mccb_setraceviewpoint,13);
  fdui->mc_race15 = obj = fl_add_button(FL_NORMAL_BUTTON,40,340,180,20,"<no race 15>");
    fl_set_object_boxtype(obj,FL_NO_BOX);
    fl_set_object_color(obj,FL_BLACK,FL_COL1);
    fl_set_object_lcolor(obj,FL_COL1);
    fl_set_object_callback(obj,mccb_setraceviewpoint,15);
  fdui->mc_race14 = obj = fl_add_button(FL_NORMAL_BUTTON,250,320,180,20,"<no race 14>");
    fl_set_object_boxtype(obj,FL_NO_BOX);
    fl_set_object_color(obj,FL_BLACK,FL_COL1);
    fl_set_object_lcolor(obj,FL_COL1);
    fl_set_object_callback(obj,mccb_setraceviewpoint,14);
  fdui->mc_race16 = obj = fl_add_button(FL_NORMAL_BUTTON,250,340,180,20,"<no race 16>");
    fl_set_object_boxtype(obj,FL_NO_BOX);
    fl_set_object_color(obj,FL_BLACK,FL_COL1);
    fl_set_object_lcolor(obj,FL_COL1);
    fl_set_object_callback(obj,mccb_setraceviewpoint,16);
  fdui->mc_mapmode = obj = fl_add_choice(FL_NORMAL_CHOICE2,130,20,170,30,"Background mode");
    fl_set_object_boxtype(obj,FL_FRAME_BOX);
    fl_set_object_lalign(obj,FL_ALIGN_TOP);
    fl_set_object_callback(obj,mccb_setbkgmode,0);
  fdui->mc_quit = obj = fl_add_button(FL_NORMAL_BUTTON,400,130,60,30,"Quit");
  fdui->mc_center = obj = fl_add_button(FL_NORMAL_BUTTON,50,50,30,30,"@-2circle");
    fl_set_object_callback(obj,mccb_scrollmap,5);
  fdui->mc_zoomout = obj = fl_add_button(FL_NORMAL_BUTTON,10,130,50,30,"Zoom out");
    fl_set_object_callback(obj,mccb_scrollmap,-3);
  fdui->mc_zoomin = obj = fl_add_button(FL_NORMAL_BUTTON,70,130,50,30,"Zoom in");
    fl_set_object_callback(obj,mccb_scrollmap,-2);
  obj = fl_add_button(FL_NORMAL_BUTTON,400,10,60,50,"<future>");
  obj = fl_add_button(FL_NORMAL_BUTTON,400,70,60,50,"<future>");
  fdui->mc_pfload = obj = fl_add_button(FL_PUSH_BUTTON,320,90,60,30,"Load");
    fl_set_object_callback(obj,mccb_pflistio,0);
  fdui->mc_pfsave = obj = fl_add_button(FL_PUSH_BUTTON,320,130,60,30,"Save");
    fl_set_object_callback(obj,mccb_pflistio,1);
  fdui->mc_pfeditor = obj = fl_add_button(FL_PUSH_BUTTON,320,50,60,30,"Editor");
    fl_set_object_callback(obj,mccb_pfeditorwindow,0);
  fdui->mc_scaneff = obj = fl_add_input(FL_NORMAL_INPUT,230,100,60,20,"Scanner\nEfficiency");
    fl_set_object_lalign(obj,FL_ALIGN_TOP);
    fl_set_object_callback(obj,mccb_setscaneff,0);
  fdui->mc_alliances = obj = fl_add_button(FL_NORMAL_BUTTON,130,60,80,20,"Alliances");
    fl_set_object_callback(obj,mccb_alliances,0);
  fl_end_form();

  fdui->MapControl->fdui = fdui;

  return fdui;
}
/*---------------------------------------*/

static FL_PUP_ENTRY fdchoice_1[] =
{ 
    /*  itemtext   callback  shortcut   mode */
    { "Logarithmic",	0,	"",	 FL_PUP_NONE},
    { "Multi-Linear",	0,	"",	 FL_PUP_NONE},
    { "1000",	0,	"",	 FL_PUP_NONE},
    { "2500",	0,	"",	 FL_PUP_NONE},
    { "10000",	0,	"",	 FL_PUP_NONE},
    { "100000",	0,	"",	 FL_PUP_NONE},
    {0}
};

FD_PlanetStatus *create_form_PlanetStatus(void)
{
  FL_OBJECT *obj;
  FD_PlanetStatus *fdui = (FD_PlanetStatus *) fl_calloc(1, sizeof(*fdui));

  fdui->PlanetStatus = fl_bgn_form(FL_NO_BOX, 440, 490);
  obj = fl_add_box(FL_UP_BOX,0,0,440,490,"");
  obj = fl_add_labelframe(FL_EMBOSSED_FRAME,10,230,420,100,"Minerals");
    fl_set_object_boxtype(obj,FL_FLAT_BOX);
    fl_set_object_color(obj,FL_COL1,FL_COL1);
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_labelframe(FL_EMBOSSED_FRAME,10,340,420,100,"Environment");
    fl_set_object_boxtype(obj,FL_FLAT_BOX);
    fl_set_object_color(obj,FL_COL1,FL_COL1);
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->ps_popfilldial = obj = fl_add_dial(FL_FILL_DIAL,120,80,30,40,"");
    fl_set_object_color(obj,FL_COL1,FL_GREEN);
    fl_set_dial_bounds(obj, 0, 100);
    fl_set_dial_value(obj, 25);
  fdui->ps_popfill = obj = fl_add_text(FL_NORMAL_TEXT,90,100,30,20,"Htf");
    fl_set_object_lalign(obj,FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
  fdui->ps_popgrowth = obj = fl_add_text(FL_NORMAL_TEXT,10,100,80,20,"(+ growth)");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->ps_population = obj = fl_add_text(FL_NORMAL_TEXT,10,80,110,20,"Pop now");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->ps_ironium = obj = fl_add_text(FL_NORMAL_TEXT,20,270,80,20,"XXXXX+YYYY");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->ps_boranium = obj = fl_add_text(FL_NORMAL_TEXT,20,290,80,20,"XXXXX+YYYY");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->ps_germanium = obj = fl_add_text(FL_NORMAL_TEXT,20,310,80,20,"XXXXX+YYYY");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,250,170,70,20,"Scanner");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->ps_mines = obj = fl_add_text(FL_NORMAL_TEXT,80,150,100,20,"XXX/YYY/ZZZ");
    fl_set_object_lalign(obj,FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
  fdui->ps_factories = obj = fl_add_text(FL_NORMAL_TEXT,80,170,100,20,"XXX/YYY/ZZZ");
    fl_set_object_lalign(obj,FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
  fdui->ps_defenses = obj = fl_add_text(FL_NORMAL_TEXT,320,150,100,20,"XXX/YYY (zz%)");
    fl_set_object_lalign(obj,FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,250,150,50,20,"Defenses");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,20,170,50,20,"Factories");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,20,150,50,20,"Mines");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->ps_scanning = obj = fl_add_text(FL_NORMAL_TEXT,350,170,70,20,"XXX/YYY");
    fl_set_object_lalign(obj,FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
  fdui->ps_stbdamage = obj = fl_add_text(FL_NORMAL_TEXT,390,80,40,20,"DMG%");
    fl_set_object_lcolor(obj,FL_RED);
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->ps_starbasename = obj = fl_add_text(FL_NORMAL_TEXT,160,80,230,20,"Starbase design name");
    fl_set_object_lsize(obj,FL_NORMAL_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->ps_gaterange = obj = fl_add_text(FL_NORMAL_TEXT,160,100,100,20,"Gate x/y");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->ps_massdriver = obj = fl_add_text(FL_NORMAL_TEXT,260,100,170,20,"MD-x @ Planet Name");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->ps_planetname = obj = fl_add_text(FL_NORMAL_TEXT,10,10,290,20,"Planet Name (HW) (#id)");
    fl_set_object_lsize(obj,FL_LARGE_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->ps_position = obj = fl_add_text(FL_NORMAL_TEXT,350,30,80,20,"(pos,pos)");
    fl_set_object_lalign(obj,FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
  fdui->ps_type = obj = fl_add_text(FL_NORMAL_TEXT,340,10,90,20,"-type-");
    fl_set_object_lalign(obj,FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
  fdui->ps_authsource = obj = fl_add_text(FL_NORMAL_TEXT,150,50,120,20,"Authoritative");
    fl_set_object_boxtype(obj,FL_DOWN_BOX);
    fl_set_object_color(obj,FL_BLACK,FL_WHITE);
    fl_set_object_lcolor(obj,FL_LEFT_BCOL);
    fl_set_object_lsize(obj,FL_NORMAL_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->ps_trustedsource = obj = fl_add_text(FL_NORMAL_TEXT,270,50,120,20,"Trusted");
    fl_set_object_boxtype(obj,FL_DOWN_BOX);
    fl_set_object_color(obj,FL_BLACK,FL_WHITE);
    fl_set_object_lcolor(obj,FL_LEFT_BCOL);
    fl_set_object_lsize(obj,FL_NORMAL_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->ps_owner = obj = fl_add_text(FL_NORMAL_TEXT,10,50,120,20,"Owner");
    fl_set_object_boxtype(obj,FL_DOWN_BOX);
    fl_set_object_color(obj,FL_BLACK,FL_WHITE);
    fl_set_object_lcolor(obj,FL_LEFT_BCOL);
    fl_set_object_lsize(obj,FL_NORMAL_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,260,200,40,20,"Route");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->ps_reportage = obj = fl_add_text(FL_NORMAL_TEXT,390,50,40,20,"AGE");
    fl_set_object_lsize(obj,FL_NORMAL_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->routing = obj = fl_add_text(FL_NORMAL_TEXT,300,200,130,20,"XXX/YYY");
    fl_set_object_lalign(obj,FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
  fdui->ps_ownhabnow = obj = fl_add_text(FL_NORMAL_TEXT,90,350,40,20,"Hnow");
    fl_set_object_lalign(obj,FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
  fdui->resources = obj = fl_add_text(FL_NORMAL_TEXT,110,200,110,20,"XXXX (YYYY)");
    fl_set_object_lsize(obj,FL_MEDIUM_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,10,200,100,20,"Resources");
    fl_set_object_lsize(obj,FL_MEDIUM_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->ps_ironiumdial = obj = fl_add_free(FL_INACTIVE_FREE,110,270,270,20,"",
			freeobj_ps_ironiumdial_handle);
  fdui->ps_boraniumdial = obj = fl_add_free(FL_INACTIVE_FREE,110,290,270,20,"",
			freeobj_ps_boraniumdial_handle);
  fdui->ps_germaniumdial = obj = fl_add_free(FL_INACTIVE_FREE,110,310,270,20,"",
			freeobj_ps_germaniumdial_handle);
  fdui->ps_gravitydial = obj = fl_add_free(FL_INACTIVE_FREE,20,380,400,20,"",
			freeobj_ps_gravitydial_handle);
  fdui->ps_termpdial = obj = fl_add_free(FL_INACTIVE_FREE,20,400,400,20,"",
			freeobj_ps_termpdial_handle);
  fdui->ps_raddial = obj = fl_add_free(FL_INACTIVE_FREE,20,420,400,20,"",
			freeobj_ps_raddial_handle);
  fdui->ps_close = obj = fl_add_button(FL_NORMAL_BUTTON,360,450,70,30,"Close");
    fl_set_object_callback(obj,pscb_closewindow,0);
  obj = fl_add_labelframe(FL_EMBOSSED_FRAME,160,80,270,50,"Starbase");
  obj = fl_add_labelframe(FL_EMBOSSED_FRAME,10,80,140,50,"Population");
    fl_set_object_boxtype(obj,FL_FLAT_BOX);
    fl_set_object_color(obj,FL_COL1,FL_COL1);
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_labelframe(FL_EMBOSSED_FRAME,10,140,420,50,"Installations");
    fl_set_object_boxtype(obj,FL_FLAT_BOX);
    fl_set_object_color(obj,FL_COL1,FL_COL1);
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,10,30,60,20,"Owner:");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,150,30,110,20,"Authoritative:");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,270,30,60,20,"Trusted:");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->ownhabtformed = obj = fl_add_text(FL_NORMAL_TEXT,130,350,40,20,"Htf");
    fl_set_object_lalign(obj,FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
  fdui->ownhabmaxtformed = obj = fl_add_text(FL_NORMAL_TEXT,170,350,40,20,"Hmaxt");
    fl_set_object_lalign(obj,FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
  fdui->habnow = obj = fl_add_text(FL_NORMAL_TEXT,300,350,40,20,"Hnow");
    fl_set_object_lalign(obj,FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
  fdui->habtformed = obj = fl_add_text(FL_NORMAL_TEXT,340,350,40,20,"Htf");
    fl_set_object_lalign(obj,FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
  fdui->habmaxtformed = obj = fl_add_text(FL_NORMAL_TEXT,380,350,40,20,"Hmaxt");
    fl_set_object_lalign(obj,FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,230,350,70,20,"Viewpoint:");
    fl_set_object_lalign(obj,FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,20,350,70,20,"Owner:");
    fl_set_object_lalign(obj,FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
  fdui->ironconc = obj = fl_add_text(FL_NORMAL_TEXT,380,270,40,20,"iC");
    fl_set_object_lsize(obj,FL_NORMAL_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->boraconc = obj = fl_add_text(FL_NORMAL_TEXT,380,290,40,20,"bC");
    fl_set_object_lsize(obj,FL_NORMAL_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->germconc = obj = fl_add_text(FL_NORMAL_TEXT,380,310,40,20,"gC");
    fl_set_object_lsize(obj,FL_NORMAL_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->minscale = obj = fl_add_choice(FL_NORMAL_CHOICE2,20,240,110,20,"");
    fl_set_object_boxtype(obj,FL_FRAME_BOX);
    fl_set_object_callback(obj,pscb_setminscale,0);
   fl_set_choice_entries(obj, fdchoice_1);
   fl_set_choice(obj,1);
  fdui->testobject = obj = fl_add_choice(FL_NORMAL_CHOICE2,140,240,110,20,"");
    fl_set_object_boxtype(obj,FL_FRAME_BOX);
    fl_set_object_callback(obj,pscb_settestobject,0);
  fdui->ironobjects = obj = fl_add_text(FL_NORMAL_TEXT,260,240,40,20,"Imul");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->boraobjects = obj = fl_add_text(FL_NORMAL_TEXT,300,240,40,20,"Bmul");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->germobjects = obj = fl_add_text(FL_NORMAL_TEXT,340,240,40,20,"Gmul");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->resobjects = obj = fl_add_text(FL_NORMAL_TEXT,380,240,40,20,"Rmul");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_button(FL_NORMAL_BUTTON,10,450,110,30,"View Simulation");
    fl_set_object_callback(obj,pscb_viewsimulation,0);
  fl_end_form();

  fdui->PlanetStatus->fdui = fdui;

  return fdui;
}
/*---------------------------------------*/

FD_PlanetViews *create_form_PlanetViews(void)
{
  FL_OBJECT *obj;
  FD_PlanetViews *fdui = (FD_PlanetViews *) fl_calloc(1, sizeof(*fdui));

  fdui->PlanetViews = fl_bgn_form(FL_NO_BOX, 380, 390);
  obj = fl_add_box(FL_UP_BOX,0,0,380,390,"");
  fdui->close = obj = fl_add_button(FL_NORMAL_BUTTON,300,350,70,30,"Close");
  fdui->import = obj = fl_add_button(FL_NORMAL_BUTTON,10,350,70,30,"Import");
  fdui->save = obj = fl_add_button(FL_NORMAL_BUTTON,90,350,70,30,"Save");
  fdui->delete = obj = fl_add_button(FL_NORMAL_BUTTON,10,310,70,30,"Delete");
  fdui->clone = obj = fl_add_button(FL_NORMAL_BUTTON,90,310,70,30,"Clone");
  fdui->export = obj = fl_add_button(FL_NORMAL_BUTTON,170,350,70,30,"Export");
  fdui->movedown = obj = fl_add_button(FL_NORMAL_BUTTON,210,310,30,30,"@2");
  fdui->moveup = obj = fl_add_button(FL_NORMAL_BUTTON,170,310,30,30,"@8");
  obj = fl_add_browser(FL_NORMAL_BROWSER,10,10,360,290,"");
  fl_end_form();

  fdui->PlanetViews->fdui = fdui;

  return fdui;
}
/*---------------------------------------*/

FD_PlanetSimulation *create_form_PlanetSimulation(void)
{
  FL_OBJECT *obj;
  FD_PlanetSimulation *fdui = (FD_PlanetSimulation *) fl_calloc(1, sizeof(*fdui));

  fdui->PlanetSimulation = fl_bgn_form(FL_NO_BOX, 490, 360);
  obj = fl_add_box(FL_UP_BOX,0,0,490,360,"");
  obj = fl_add_button(FL_NORMAL_BUTTON,410,320,70,30,"Close");
    fl_set_object_callback(obj,pmcb_close,0);
  fdui->planetname = obj = fl_add_text(FL_NORMAL_TEXT,10,10,290,20,"Planet Name (HW) (#id)");
    fl_set_object_lsize(obj,FL_LARGE_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->messages = obj = fl_add_browser(FL_NORMAL_BROWSER,10,40,470,270,"");
  fl_end_form();

  fdui->PlanetSimulation->fdui = fdui;

  return fdui;
}
/*---------------------------------------*/


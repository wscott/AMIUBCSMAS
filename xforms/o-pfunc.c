/* Form definition file generated with fdesign. */

#include "forms.h"
#include <stdlib.h>
#include "o-pfunc.h"

static FL_PUP_ENTRY fdchoice_mode_0[] =
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

  fdui->PlanetaryFunction = fl_bgn_form(FL_NO_BOX, 370, 330);
  obj = fl_add_box(FL_UP_BOX,0,0,370,330,"");
  fdui->description = obj = fl_add_text(FL_NORMAL_TEXT,10,40,350,60,"pf description");
    fl_set_object_boxtype(obj,FL_FRAME_BOX);
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->mask_circles = obj = fl_add_button(FL_PUSH_BUTTON,160,110,30,20,"C");
  fdui->input_par1 = obj = fl_add_input(FL_NORMAL_INPUT,120,140,70,20,"Input");
  fdui->input_par2 = obj = fl_add_input(FL_NORMAL_INPUT,120,160,70,20,"Input");
  fdui->input_par3 = obj = fl_add_input(FL_NORMAL_INPUT,120,180,70,20,"Input");
  fdui->input_par4 = obj = fl_add_input(FL_NORMAL_INPUT,120,200,70,20,"Input");
  fdui->mask_marker = obj = fl_add_button(FL_PUSH_BUTTON,220,110,30,20,"M");
  fdui->mask_flag = obj = fl_add_button(FL_PUSH_BUTTON,310,110,30,20,"F");
  fdui->mode = obj = fl_add_choice(FL_NORMAL_CHOICE2,60,110,90,20,"");
    fl_set_object_boxtype(obj,FL_FRAME_BOX);
   fl_set_choice_entries(obj, fdchoice_mode_0);
   fl_set_choice(obj,1);
  fdui->number = obj = fl_add_text(FL_NORMAL_TEXT,10,5,40,30,"1");
    fl_set_object_boxtype(obj,FL_UP_BOX);
    fl_set_object_lsize(obj,FL_MEDIUM_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->apply = obj = fl_add_button(FL_NORMAL_BUTTON,10,290,80,30,"Apply");
    fl_set_object_callback(obj,pfecb_apply,0);
  fdui->cancel = obj = fl_add_button(FL_NORMAL_BUTTON,190,290,80,30,"Cancel");
    fl_set_object_callback(obj,pfecb_cancel,0);
  fdui->input_par5 = obj = fl_add_input(FL_NORMAL_INPUT,120,220,70,20,"Input");
  fdui->selected = obj = fl_add_menu(FL_PULLDOWN_MENU,50,5,310,30,"Select a PFunction");
    fl_set_object_boxtype(obj,FL_UP_BOX);
    fl_set_object_lsize(obj,FL_MEDIUM_SIZE);
    fl_set_object_callback(obj,pfecb_selected,0);
  fdui->mask_lines = obj = fl_add_button(FL_PUSH_BUTTON,190,110,30,20,"L");
  fdui->mask_name = obj = fl_add_button(FL_PUSH_BUTTON,280,110,30,20,"N");
  fdui->mask_data = obj = fl_add_button(FL_PUSH_BUTTON,250,110,30,20,"D");
  obj = fl_add_button(FL_NORMAL_BUTTON,280,290,80,30,"Close");
    fl_set_object_callback(obj,pfecb_close,0);
  fdui->accept_and_next = obj = fl_add_button(FL_NORMAL_BUTTON,50,250,30,30,"@2");
    fl_set_object_callback(obj,pfecb_accept_and_next,0);
  fdui->accept_and_prev = obj = fl_add_button(FL_NORMAL_BUTTON,10,250,30,30,"@8");
    fl_set_object_callback(obj,pfecb_accept_and_prev,0);
  fdui->delete = obj = fl_add_button(FL_NORMAL_BUTTON,170,250,70,30,"Delete");
    fl_set_object_callback(obj,pfecb_delete,0);
  fdui->insert = obj = fl_add_button(FL_NORMAL_BUTTON,90,250,70,30,"Insert");
    fl_set_object_callback(obj,pfecb_insert,0);
  fdui->input_par6 = obj = fl_add_input(FL_NORMAL_INPUT,290,140,70,20,"Input");
  fdui->input_par7 = obj = fl_add_input(FL_NORMAL_INPUT,290,160,70,20,"Input");
  fdui->input_par8 = obj = fl_add_input(FL_NORMAL_INPUT,290,180,70,20,"Input");
  fdui->input_par9 = obj = fl_add_input(FL_NORMAL_INPUT,290,200,70,20,"Input");
  fdui->input_par10 = obj = fl_add_input(FL_NORMAL_INPUT,290,220,70,20,"Input");
  obj = fl_add_text(FL_NORMAL_TEXT,10,110,50,20,"Mode:");
    fl_set_object_boxtype(obj,FL_NO_BOX);
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
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
  obj = fl_add_text(FL_NORMAL_TEXT,330,10,60,30,"Planetary\nViews");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  obj = fl_add_frame(FL_ENGRAVED_FRAME,10,10,300,150,"");
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
  fdui->mc_quit = obj = fl_add_button(FL_NORMAL_BUTTON,390,130,60,30,"Quit");
  fdui->mc_center = obj = fl_add_button(FL_NORMAL_BUTTON,50,50,30,30,"@-2circle");
    fl_set_object_callback(obj,mccb_scrollmap,5);
  fdui->mc_zoomout = obj = fl_add_button(FL_NORMAL_BUTTON,10,130,50,30,"Zoom out");
    fl_set_object_callback(obj,mccb_scrollmap,-3);
  fdui->mc_zoomin = obj = fl_add_button(FL_NORMAL_BUTTON,70,130,50,30,"Zoom in");
    fl_set_object_callback(obj,mccb_scrollmap,-2);
  fdui->mc_pfload = obj = fl_add_button(FL_PUSH_BUTTON,330,50,60,30,"List");
    fl_set_object_callback(obj,mccb_pflistio,0);
  fdui->mc_pfeditor = obj = fl_add_button(FL_PUSH_BUTTON,330,90,60,30,"Editor");
    fl_set_object_callback(obj,mccb_pfeditorwindow,0);
  fdui->mc_scaneff = obj = fl_add_input(FL_NORMAL_INPUT,230,100,60,20,"Scanner\nEfficiency");
    fl_set_object_lalign(obj,FL_ALIGN_TOP);
    fl_set_object_callback(obj,mccb_setscaneff,0);
  fdui->mc_alliances = obj = fl_add_button(FL_NORMAL_BUTTON,130,60,80,20,"Alliances");
    fl_set_object_callback(obj,mccb_alliances,0);
  obj = fl_add_text(FL_NORMAL_TEXT,400,10,60,30,"Fleet\nViews");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  obj = fl_add_button(FL_PUSH_BUTTON,400,50,60,30,"List");
    fl_set_object_callback(obj,mccb_pflistio,0);
  obj = fl_add_button(FL_PUSH_BUTTON,400,90,60,30,"Editor");
    fl_set_object_callback(obj,mccb_pfeditorwindow,0);
  obj = fl_add_frame(FL_ENGRAVED_FRAME,390,10,80,120,"");
  obj = fl_add_frame(FL_ENGRAVED_FRAME,320,10,70,120,"");
  fl_end_form();

  fdui->MapControl->fdui = fdui;

  return fdui;
}
/*---------------------------------------*/

static FL_PUP_ENTRY fdchoice_minscale_1[] =
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
  obj = fl_add_labelframe(FL_EMBOSSED_FRAME,10,80,140,50,"Population");
    fl_set_object_boxtype(obj,FL_FLAT_BOX);
    fl_set_object_color(obj,FL_COL1,FL_COL1);
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_labelframe(FL_EMBOSSED_FRAME,10,230,420,100,"Minerals");
    fl_set_object_boxtype(obj,FL_FLAT_BOX);
    fl_set_object_color(obj,FL_COL1,FL_COL1);
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_labelframe(FL_EMBOSSED_FRAME,10,340,420,100,"Environment");
    fl_set_object_boxtype(obj,FL_FLAT_BOX);
    fl_set_object_color(obj,FL_COL1,FL_COL1);
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->popfilldial = obj = fl_add_dial(FL_FILL_DIAL,120,80,30,40,"");
    fl_set_object_color(obj,FL_COL1,FL_GREEN);
    fl_set_dial_bounds(obj, 0, 100);
    fl_set_dial_value(obj, 25);
  fdui->popfill = obj = fl_add_text(FL_NORMAL_TEXT,90,100,30,20,"Htf");
    fl_set_object_lalign(obj,FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
  fdui->popgrowth = obj = fl_add_text(FL_NORMAL_TEXT,10,100,80,20,"(+ growth)");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->population = obj = fl_add_text(FL_NORMAL_TEXT,10,80,110,20,"Pop now");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->ironium = obj = fl_add_text(FL_NORMAL_TEXT,20,265,80,20,"XXXXX+YYYY");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->boranium = obj = fl_add_text(FL_NORMAL_TEXT,20,285,80,20,"XXXXX+YYYY");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->germanium = obj = fl_add_text(FL_NORMAL_TEXT,20,305,80,20,"XXXXX+YYYY");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,250,170,70,20,"Scanner");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->mines = obj = fl_add_text(FL_NORMAL_TEXT,80,150,100,20,"XXX/YYY/ZZZ");
    fl_set_object_lalign(obj,FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
  fdui->factories = obj = fl_add_text(FL_NORMAL_TEXT,80,170,100,20,"XXX/YYY/ZZZ");
    fl_set_object_lalign(obj,FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
  fdui->defenses = obj = fl_add_text(FL_NORMAL_TEXT,320,150,100,20,"XXX/YYY (zz%)");
    fl_set_object_lalign(obj,FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,250,150,50,20,"Defenses");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,20,170,50,20,"Factories");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,20,150,50,20,"Mines");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->scanning = obj = fl_add_text(FL_NORMAL_TEXT,350,170,70,20,"XXX/YYY");
    fl_set_object_lalign(obj,FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
  fdui->stbdamage = obj = fl_add_text(FL_NORMAL_TEXT,390,80,40,20,"DMG%");
    fl_set_object_lcolor(obj,FL_RED);
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->starbasename = obj = fl_add_text(FL_NORMAL_TEXT,160,80,230,20,"Starbase design name");
    fl_set_object_lsize(obj,FL_NORMAL_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->gaterange = obj = fl_add_text(FL_NORMAL_TEXT,160,100,100,20,"Gate x/y");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->massdriver = obj = fl_add_text(FL_NORMAL_TEXT,260,100,170,20,"MD-x @ Planet Name");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->planetname = obj = fl_add_text(FL_NORMAL_TEXT,10,10,290,20,"Planet Name (HW) (#id)");
    fl_set_object_lsize(obj,FL_LARGE_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->position = obj = fl_add_text(FL_NORMAL_TEXT,350,30,80,20,"(pos,pos)");
    fl_set_object_lalign(obj,FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
  fdui->type = obj = fl_add_text(FL_NORMAL_TEXT,340,10,90,20,"-type-");
    fl_set_object_lalign(obj,FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
  fdui->authsource = obj = fl_add_text(FL_NORMAL_TEXT,150,50,120,20,"Authoritative");
    fl_set_object_boxtype(obj,FL_DOWN_BOX);
    fl_set_object_color(obj,FL_BLACK,FL_WHITE);
    fl_set_object_lcolor(obj,FL_LEFT_BCOL);
    fl_set_object_lsize(obj,FL_NORMAL_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->trustedsource = obj = fl_add_text(FL_NORMAL_TEXT,270,50,120,20,"Trusted");
    fl_set_object_boxtype(obj,FL_DOWN_BOX);
    fl_set_object_color(obj,FL_BLACK,FL_WHITE);
    fl_set_object_lcolor(obj,FL_LEFT_BCOL);
    fl_set_object_lsize(obj,FL_NORMAL_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->owner = obj = fl_add_text(FL_NORMAL_TEXT,10,50,120,20,"Owner");
    fl_set_object_boxtype(obj,FL_DOWN_BOX);
    fl_set_object_color(obj,FL_BLACK,FL_WHITE);
    fl_set_object_lcolor(obj,FL_LEFT_BCOL);
    fl_set_object_lsize(obj,FL_NORMAL_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,260,200,40,20,"Route");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->reportage = obj = fl_add_text(FL_NORMAL_TEXT,390,50,40,20,"AGE");
    fl_set_object_lsize(obj,FL_NORMAL_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->routing = obj = fl_add_text(FL_NORMAL_TEXT,300,200,130,20,"XXX/YYY");
    fl_set_object_lalign(obj,FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
  fdui->ownhabnow = obj = fl_add_text(FL_NORMAL_TEXT,90,350,40,20,"Hnow");
    fl_set_object_lalign(obj,FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
  fdui->resources = obj = fl_add_text(FL_NORMAL_TEXT,110,200,110,20,"XXXX (YYYY)");
    fl_set_object_lsize(obj,FL_MEDIUM_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,10,200,100,20,"Resources");
    fl_set_object_lsize(obj,FL_MEDIUM_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->ironiumdial = obj = fl_add_free(FL_INACTIVE_FREE,110,265,270,20,"",
			freeobj_ironiumdial_handle);
  fdui->boraniumdial = obj = fl_add_free(FL_INACTIVE_FREE,110,285,270,20,"",
			freeobj_boraniumdial_handle);
  fdui->germaniumdial = obj = fl_add_free(FL_INACTIVE_FREE,110,305,270,20,"",
			freeobj_germaniumdial_handle);
  fdui->gravitydial = obj = fl_add_free(FL_INACTIVE_FREE,20,375,400,20,"",
			freeobj_gravitydial_handle);
  fdui->termpdial = obj = fl_add_free(FL_INACTIVE_FREE,20,395,400,20,"",
			freeobj_termpdial_handle);
  fdui->raddial = obj = fl_add_free(FL_INACTIVE_FREE,20,415,400,20,"",
			freeobj_raddial_handle);
  fdui->close = obj = fl_add_button(FL_NORMAL_BUTTON,360,450,70,30,"Close");
    fl_set_object_callback(obj,pscb_closewindow,0);
  obj = fl_add_labelframe(FL_EMBOSSED_FRAME,160,80,270,50,"Starbase");
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
  fdui->ironconc = obj = fl_add_text(FL_NORMAL_TEXT,380,265,40,20,"iC");
    fl_set_object_lsize(obj,FL_NORMAL_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->boraconc = obj = fl_add_text(FL_NORMAL_TEXT,380,285,40,20,"bC");
    fl_set_object_lsize(obj,FL_NORMAL_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->germconc = obj = fl_add_text(FL_NORMAL_TEXT,380,305,40,20,"gC");
    fl_set_object_lsize(obj,FL_NORMAL_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->minscale = obj = fl_add_choice(FL_NORMAL_CHOICE2,20,240,110,20,"");
    fl_set_object_boxtype(obj,FL_FRAME_BOX);
    fl_set_object_callback(obj,pscb_setminscale,0);
   fl_set_choice_entries(obj, fdchoice_minscale_1);
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
  obj = fl_add_button(FL_NORMAL_BUTTON,130,450,80,30,"Fire Packet");
    fl_set_object_callback(obj,pscb_firepacket,0);
  obj = fl_add_button(FL_NORMAL_BUTTON,220,450,80,30,"Bomb Planet");
    fl_set_object_callback(obj,pscb_bombplanet,0);
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

FD_PacketFiring *create_form_PacketFiring(void)
{
  FL_OBJECT *obj;
  FD_PacketFiring *fdui = (FD_PacketFiring *) fl_calloc(1, sizeof(*fdui));

  fdui->PacketFiring = fl_bgn_form(FL_NO_BOX, 480, 460);
  obj = fl_add_box(FL_UP_BOX,0,0,480,460,"");
  obj = fl_add_frame(FL_ENGRAVED_FRAME,20,235,440,180,"");
  fdui->frameuno = obj = fl_add_labelframe(FL_ENGRAVED_FRAME,5,10,200,180,"Planet #1");
  fdui->planetname1 = obj = fl_add_text(FL_NORMAL_TEXT,10,20,190,30,"Wammalammadingdong");
    fl_set_object_lsize(obj,FL_MEDIUM_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
    fl_set_object_lstyle(obj,FL_BOLD_STYLE);
  obj = fl_add_text(FL_NORMAL_TEXT,210,90,60,20,"Distance:");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->planetdistance = obj = fl_add_text(FL_NORMAL_TEXT,210,110,60,20,"9999 l.y.");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->close = obj = fl_add_button(FL_NORMAL_BUTTON,400,420,70,30,"Close");
    fl_set_object_callback(obj,pfcb_close,0);
  fdui->mineralspent = obj = fl_add_counter(FL_NORMAL_COUNTER,110,200,180,20,"Minerals spent: ");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT);
  obj = fl_add_text(FL_NORMAL_TEXT,70,240,40,30,"Travel\ntime");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,110,240,90,30,"Minerals\narrived / recov.");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,200,240,100,30,"Colonists\nkilled / left");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,30,240,40,30,"Warp");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->twindriver1 = obj = fl_add_lightbutton(FL_PUSH_BUTTON,130,60,60,30,"Twin");
    fl_set_object_boxtype(obj,FL_NO_BOX);
  fdui->racenotes1 = obj = fl_add_text(FL_NORMAL_TEXT,10,150,190,30,"Racial notes");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->cheapkiller = obj = fl_add_button(FL_NORMAL_BUTTON,300,200,70,30,"Cheapest\nkiller");
    fl_set_object_callback(obj,pfcb_cheapkiller,0);
  fdui->packetdirection = obj = fl_add_button(FL_NORMAL_BUTTON,210,40,60,30,"@5");
  obj = fl_add_text(FL_NORMAL_TEXT,300,240,80,30,"Defenses\ndestroyed / left");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,390,240,60,30,"Tforming\nstd / perm");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->fastkiller = obj = fl_add_button(FL_NORMAL_BUTTON,380,200,70,30,"Fastest\nkiller");
    fl_set_object_callback(obj,pfcb_fastkiller,0);
  fdui->population1 = obj = fl_add_input(FL_NORMAL_INPUT,70,100,120,20,"Population:");
  fdui->ndefenses1 = obj = fl_add_input(FL_NORMAL_INPUT,70,120,50,20,"Defenses:");
  fdui->defcoverage1 = obj = fl_add_text(FL_NORMAL_TEXT,130,120,60,20,"(99.45%)");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->colkill1 = obj = fl_add_text(FL_NORMAL_TEXT,200,270,100,20,"769500 / 175900");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->mineral1 = obj = fl_add_text(FL_NORMAL_TEXT,110,270,90,20,"22700 / 22700");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->travel1 = obj = fl_add_text(FL_NORMAL_TEXT,70,270,40,20,"3");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->warp1 = obj = fl_add_text(FL_NORMAL_TEXT,30,270,40,20,"7");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->defdestroy1 = obj = fl_add_text(FL_NORMAL_TEXT,300,270,80,20,"27 / 56");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->terraform1 = obj = fl_add_text(FL_NORMAL_TEXT,390,270,60,20,"12 / 1");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->colkill2 = obj = fl_add_text(FL_NORMAL_TEXT,200,290,100,20,"769500 / 175900");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->travel2 = obj = fl_add_text(FL_NORMAL_TEXT,70,290,40,20,"3");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->warp2 = obj = fl_add_text(FL_NORMAL_TEXT,30,290,40,20,"8");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->defdestroy2 = obj = fl_add_text(FL_NORMAL_TEXT,300,290,80,20,"27 / 56");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->terraform2 = obj = fl_add_text(FL_NORMAL_TEXT,390,290,60,20,"12 / 1");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->colkill3 = obj = fl_add_text(FL_NORMAL_TEXT,200,310,100,20,"769500 / 175900");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->travel3 = obj = fl_add_text(FL_NORMAL_TEXT,70,310,40,20,"3");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->warp3 = obj = fl_add_text(FL_NORMAL_TEXT,30,310,40,20,"9");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->defdestroy3 = obj = fl_add_text(FL_NORMAL_TEXT,300,310,80,20,"27 / 56");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->terraform3 = obj = fl_add_text(FL_NORMAL_TEXT,390,310,60,20,"12 / 1");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->colkill4 = obj = fl_add_text(FL_NORMAL_TEXT,200,330,100,20,"769500 / 175900");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->travel4 = obj = fl_add_text(FL_NORMAL_TEXT,70,330,40,20,"3");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->warp4 = obj = fl_add_text(FL_NORMAL_TEXT,30,330,40,20,"10");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->defdestroy4 = obj = fl_add_text(FL_NORMAL_TEXT,300,330,80,20,"27 / 56");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->terraform4 = obj = fl_add_text(FL_NORMAL_TEXT,390,330,60,20,"12 / 1");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->colkill5 = obj = fl_add_text(FL_NORMAL_TEXT,200,350,100,20,"769500 / 175900");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->travel5 = obj = fl_add_text(FL_NORMAL_TEXT,70,350,40,20,"3");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->warp5 = obj = fl_add_text(FL_NORMAL_TEXT,30,350,40,20,"11");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->defdestroy5 = obj = fl_add_text(FL_NORMAL_TEXT,300,350,80,20,"27 / 56");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->terraform5 = obj = fl_add_text(FL_NORMAL_TEXT,390,350,60,20,"12 / 1");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->colkill6 = obj = fl_add_text(FL_NORMAL_TEXT,200,370,100,20,"769500 / 175900");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->travel6 = obj = fl_add_text(FL_NORMAL_TEXT,70,370,40,20,"3");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->warp6 = obj = fl_add_text(FL_NORMAL_TEXT,30,370,40,20,"12");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->defdestroy6 = obj = fl_add_text(FL_NORMAL_TEXT,300,370,80,20,"27 / 56");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->terraform6 = obj = fl_add_text(FL_NORMAL_TEXT,390,370,60,20,"12 / 1");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->colkill7 = obj = fl_add_text(FL_NORMAL_TEXT,200,390,100,20,"769500 / 175900");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->travel7 = obj = fl_add_text(FL_NORMAL_TEXT,70,390,40,20,"3");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->warp7 = obj = fl_add_text(FL_NORMAL_TEXT,30,390,40,20,"13");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->defdestroy7 = obj = fl_add_text(FL_NORMAL_TEXT,300,390,80,20,"27 / 56");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->terraform7 = obj = fl_add_text(FL_NORMAL_TEXT,390,390,60,20,"12 / 1");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->framedue = obj = fl_add_labelframe(FL_ENGRAVED_FRAME,275,10,200,180,"Planet #2");
  fdui->planetname2 = obj = fl_add_text(FL_NORMAL_TEXT,280,20,190,30,"Wammalammadingdong");
    fl_set_object_lsize(obj,FL_MEDIUM_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
    fl_set_object_lstyle(obj,FL_BOLD_STYLE);
  fdui->twindriver2 = obj = fl_add_lightbutton(FL_PUSH_BUTTON,400,60,60,30,"Twin");
    fl_set_object_boxtype(obj,FL_NO_BOX);
  fdui->racenotes2 = obj = fl_add_text(FL_NORMAL_TEXT,280,150,190,30,"Racial notes");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->population2 = obj = fl_add_input(FL_NORMAL_INPUT,340,100,120,20,"Population:");
  fdui->ndefenses2 = obj = fl_add_input(FL_NORMAL_INPUT,340,120,50,20,"Defenses:");
  fdui->defcoverage2 = obj = fl_add_text(FL_NORMAL_TEXT,400,120,60,20,"(99.45%)");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->driverwarp1 = obj = fl_add_text(FL_NORMAL_TEXT,50,60,40,30,"W");
    fl_set_object_boxtype(obj,FL_BORDER_BOX);
    fl_set_object_lsize(obj,FL_MEDIUM_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
    fl_set_object_lstyle(obj,FL_BOLD_STYLE);
  fdui->increasewarp1 = obj = fl_add_scrollbutton(FL_TOUCH_BUTTON,90,60,30,30,"6");
    fl_set_object_boxtype(obj,FL_BORDER_BOX);
  fdui->lowerwarp1 = obj = fl_add_scrollbutton(FL_TOUCH_BUTTON,20,60,30,30,"4");
    fl_set_object_boxtype(obj,FL_BORDER_BOX);
  fdui->driverwarp2 = obj = fl_add_text(FL_NORMAL_TEXT,320,60,40,30,"W");
    fl_set_object_boxtype(obj,FL_BORDER_BOX);
    fl_set_object_lsize(obj,FL_MEDIUM_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
    fl_set_object_lstyle(obj,FL_BOLD_STYLE);
  fdui->increasewarp2 = obj = fl_add_scrollbutton(FL_TOUCH_BUTTON,360,60,30,30,"6");
    fl_set_object_boxtype(obj,FL_BORDER_BOX);
  fdui->lowerwarp2 = obj = fl_add_scrollbutton(FL_TOUCH_BUTTON,290,60,30,30,"4");
    fl_set_object_boxtype(obj,FL_BORDER_BOX);
  fdui->mineral2 = obj = fl_add_text(FL_NORMAL_TEXT,110,290,90,20,"22700 / 22700");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->mineral3 = obj = fl_add_text(FL_NORMAL_TEXT,110,310,90,20,"22700 / 22700");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->mineral4 = obj = fl_add_text(FL_NORMAL_TEXT,110,330,90,20,"22700 / 22700");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->mineral5 = obj = fl_add_text(FL_NORMAL_TEXT,110,350,90,20,"22700 / 22700");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->mineral6 = obj = fl_add_text(FL_NORMAL_TEXT,110,370,90,20,"22700 / 22700");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->mineral7 = obj = fl_add_text(FL_NORMAL_TEXT,110,390,90,20,"22700 / 22700");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fl_end_form();

  fdui->PacketFiring->fdui = fdui;

  return fdui;
}
/*---------------------------------------*/

FD_IntroTitle *create_form_IntroTitle(void)
{
  FL_OBJECT *obj;
  FD_IntroTitle *fdui = (FD_IntroTitle *) fl_calloc(1, sizeof(*fdui));

  fdui->IntroTitle = fl_bgn_form(FL_NO_BOX, 410, 320);
  obj = fl_add_box(FL_UP_BOX,0,0,410,320,"");
    fl_set_object_color(obj,FL_BOTTOM_BCOL,FL_MCOL);
  obj = fl_add_box(FL_SHADOW_BOX,10,150,390,130,"");
    fl_set_object_color(obj,FL_INACTIVE,FL_COL1);
  obj = fl_add_box(FL_SHADOW_BOX,10,10,390,70,"");
    fl_set_object_color(obj,FL_INACTIVE,FL_COL1);
  obj = fl_add_text(FL_NORMAL_TEXT,20,20,140,50,"STARANA");
    fl_set_object_color(obj,FL_INACTIVE,FL_MCOL);
    fl_set_object_lcolor(obj,FL_YELLOW);
    fl_set_object_lsize(obj,FL_HUGE_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
    fl_set_object_lstyle(obj,FL_BOLDITALIC_STYLE);
  obj = fl_add_text(FL_NORMAL_TEXT,20,280,370,30,"Loading report files.........");
    fl_set_object_color(obj,FL_BOTTOM_BCOL,FL_MCOL);
    fl_set_object_lcolor(obj,FL_YELLOW);
    fl_set_object_lsize(obj,FL_MEDIUM_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,160,40,120,30,"version 0.2f");
    fl_set_object_color(obj,FL_INACTIVE,FL_MCOL);
    fl_set_object_lcolor(obj,FL_TOMATO);
    fl_set_object_lsize(obj,FL_MEDIUM_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
    fl_set_object_lstyle(obj,FL_FIXEDBOLDITALIC_STYLE);
  obj = fl_add_text(FL_NORMAL_TEXT,280,40,110,30,"(27 Sep 1998)");
    fl_set_object_color(obj,FL_INACTIVE,FL_MCOL);
    fl_set_object_lcolor(obj,FL_TOMATO);
    fl_set_object_lsize(obj,FL_NORMAL_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
    fl_set_object_lstyle(obj,FL_FIXED_STYLE);
  obj = fl_add_text(FL_NORMAL_TEXT,20,80,370,60,"actually named AMIUBCSMAS\n(as in Alberto's Most Incomplete, Undocumented and\nBadly Coded Stars! Mapper, Analyzer and Simulator)");
    fl_set_object_color(obj,FL_BOTTOM_BCOL,FL_MCOL);
    fl_set_object_lcolor(obj,FL_GREEN);
    fl_set_object_lsize(obj,FL_NORMAL_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,20,200,70,30,"Credits:   ");
    fl_set_object_color(obj,FL_INACTIVE,FL_MCOL);
    fl_set_object_lcolor(obj,FL_LEFT_BCOL);
    fl_set_object_lsize(obj,FL_NORMAL_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,20,170,70,20,"Written by:");
    fl_set_object_color(obj,FL_INACTIVE,FL_MCOL);
    fl_set_object_lcolor(obj,FL_LEFT_BCOL);
    fl_set_object_lsize(obj,FL_NORMAL_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,100,170,290,20,"Alberto Barsella");
    fl_set_object_color(obj,FL_INACTIVE,FL_MCOL);
    fl_set_object_lcolor(obj,FL_WHITE);
    fl_set_object_lsize(obj,FL_NORMAL_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,90,200,70,70,"(patches)\n(formulae)\n(Stars! :)\n(ideas)");
    fl_set_object_color(obj,FL_INACTIVE,FL_MCOL);
    fl_set_object_lcolor(obj,FL_LEFT_BCOL);
    fl_set_object_lsize(obj,FL_NORMAL_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,160,200,230,70,"Wayne Smith\nLoren Webster, Jason Cawley\nJeff^2\nall the rec.games.computer.stars people");
    fl_set_object_color(obj,FL_INACTIVE,FL_MCOL);
    fl_set_object_lcolor(obj,FL_WHITE);
    fl_set_object_lsize(obj,FL_NORMAL_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fl_end_form();

  fdui->IntroTitle->fdui = fdui;

  return fdui;
}
/*---------------------------------------*/

FD_RacialReport *create_form_RacialReport(void)
{
  FL_OBJECT *obj;
  FD_RacialReport *fdui = (FD_RacialReport *) fl_calloc(1, sizeof(*fdui));

  fdui->RacialReport = fl_bgn_form(FL_NO_BOX, 630, 360);
  obj = fl_add_box(FL_UP_BOX,0,0,630,360,"");
  obj = fl_add_text(FL_NORMAL_TEXT,30,10,110,30,"Racial Report:");
    fl_set_object_lsize(obj,FL_MEDIUM_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
    fl_set_object_lstyle(obj,FL_BOLD_STYLE);
  fdui->race_isanalyzed = obj = fl_add_text(FL_NORMAL_TEXT,580,10,30,30,"A");
    fl_set_object_lsize(obj,FL_HUGE_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
    fl_set_object_lstyle(obj,FL_BOLD_STYLE);
  fdui->race_issource = obj = fl_add_text(FL_NORMAL_TEXT,550,10,30,30,"R");
    fl_set_object_lsize(obj,FL_HUGE_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
    fl_set_object_lstyle(obj,FL_BOLD_STYLE);
  fdui->tabfolder = obj = fl_add_tabfolder(FL_TOP_TABFOLDER,10,60,610,290,"Tabbed folder");
    fl_set_object_boxtype(obj,FL_NO_BOX);
  fdui->race_names = obj = fl_add_text(FL_NORMAL_TEXT,140,10,340,30,"??????????????? (?????????????????s)");
    fl_set_object_lsize(obj,FL_MEDIUM_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
    fl_set_object_lstyle(obj,FL_BOLD_STYLE);
  fl_end_form();

  fdui->RacialReport->fdui = fdui;

  return fdui;
}
/*---------------------------------------*/

FD_RR_RaceInfo *create_form_RR_RaceInfo(void)
{
  FL_OBJECT *obj;
  FD_RR_RaceInfo *fdui = (FD_RR_RaceInfo *) fl_calloc(1, sizeof(*fdui));

  fdui->RR_RaceInfo = fl_bgn_form(FL_NO_BOX, 610, 290);
  obj = fl_add_box(FL_UP_BOX,0,0,610,290,"");
  obj = fl_add_text(FL_NORMAL_TEXT,490,10,80,20,"Player number:");
    fl_set_object_lalign(obj,FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,10,10,70,20,"Racial traits:");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,10,130,100,20,"Technology levels:");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,10,210,100,20,"Terraforming tech:");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,10,40,100,20,"Colonist efficiency:");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,10,60,100,20,"Factories:");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,10,80,100,20,"Mines:");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,10,160,100,20,"Controlled planets:");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,510,30,60,20,"Reliability:");
    fl_set_object_lalign(obj,FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,10,110,100,20,"Research cost:");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_xyplot(FL_NORMAL_XYPLOT,390,80,210,200,"");
    fl_set_object_boxtype(obj,FL_DOWN_BOX);
    fl_set_object_color(obj,FL_BLACK,FL_WHITE);
  obj = fl_add_text(FL_NORMAL_TEXT,170,80,140,20,"Max resources/100% world:");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,390,60,120,20,"Habitability distribution:");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,170,160,100,20,"Total Population:");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,10,180,100,20,"Total Fleets:");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,170,180,100,20,"Total ships::");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fl_end_form();

  fdui->RR_RaceInfo->fdui = fdui;

  return fdui;
}
/*---------------------------------------*/

FD_RR_ReportLog *create_form_RR_ReportLog(void)
{
  FL_OBJECT *obj;
  FD_RR_ReportLog *fdui = (FD_RR_ReportLog *) fl_calloc(1, sizeof(*fdui));

  fdui->RR_ReportLog = fl_bgn_form(FL_NO_BOX, 610, 290);
  obj = fl_add_box(FL_UP_BOX,0,0,610,290,"");
  obj = fl_add_browser(FL_NORMAL_BROWSER,10,10,590,270,"");
    fl_set_object_color(obj,FL_BOTTOM_BCOL,FL_YELLOW);
  fl_end_form();

  fdui->RR_ReportLog->fdui = fdui;

  return fdui;
}
/*---------------------------------------*/

static FL_PUP_ENTRY fdchoice_displaywhat_2[] =
{ 
    /*  itemtext   callback  shortcut   mode */
    { "Resources",	0,	"",	 FL_PUP_NONE},
    { "Population (total)",	0,	"",	 FL_PUP_NONE},
    { "Population (orbit)",	0,	"",	 FL_PUP_NONE},
    { "Population (planet)",	0,	"",	 FL_PUP_NONE},
    { "Minerals",	0,	"",	 FL_PUP_NONE},
    { "Ironium",	0,	"",	 FL_PUP_NONE},
    { "Boranium",	0,	"",	 FL_PUP_NONE},
    { "Germanium",	0,	"",	 FL_PUP_NONE},
    { "Population growth",	0,	"",	 FL_PUP_NONE},
    { "Mining Rates",	0,	"",	 FL_PUP_NONE},
    {0}
};

FD_RR_Comparisons *create_form_RR_Comparisons(void)
{
  FL_OBJECT *obj;
  FD_RR_Comparisons *fdui = (FD_RR_Comparisons *) fl_calloc(1, sizeof(*fdui));

  fdui->RR_Comparisons = fl_bgn_form(FL_NO_BOX, 610, 290);
  obj = fl_add_box(FL_UP_BOX,0,0,610,290,"");
  fdui->racegraph = obj = fl_add_xyplot(FL_NORMAL_XYPLOT,10,10,360,270,"");
    fl_set_object_boxtype(obj,FL_DOWN_BOX);
    fl_set_object_color(obj,FL_BLACK,FL_WHITE);
    fl_set_object_lcolor(obj,FL_GREEN);
  fdui->displaywhat = obj = fl_add_choice(FL_NORMAL_CHOICE2,390,20,200,30,"");
   fl_set_choice_align(obj, FL_ALIGN_LEFT);
   fl_set_choice_entries(obj, fdchoice_displaywhat_2);
   fl_set_choice(obj,1);
  obj = fl_add_text(FL_NORMAL_TEXT,390,60,200,40,"NOTE: comparison is available only in\nthe case of single-value displays.");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->compare = obj = fl_add_lightbutton(FL_PUSH_BUTTON,390,110,120,30,"Comparison");
  fl_end_form();

  fdui->RR_Comparisons->fdui = fdui;

  return fdui;
}
/*---------------------------------------*/

FD_RR_DesignsObjects *create_form_RR_DesignsObjects(void)
{
  FL_OBJECT *obj;
  FD_RR_DesignsObjects *fdui = (FD_RR_DesignsObjects *) fl_calloc(1, sizeof(*fdui));

  fdui->RR_DesignsObjects = fl_bgn_form(FL_NO_BOX, 610, 290);
  obj = fl_add_box(FL_UP_BOX,0,0,610,290,"");
  obj = fl_add_text(FL_NORMAL_TEXT,30,10,140,16,"Design name 1");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,170,10,40,16,"Iron");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,210,10,40,16,"Bora");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,250,10,40,16,"Germ");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,290,10,40,16,"Res");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,380,10,100,20,"(base hull)");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,30,30,140,20,"Design name 1");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,170,30,40,20,"Iron");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,210,30,40,20,"Bora");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,250,30,40,20,"Germ");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,290,30,40,20,"Res");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,380,30,100,20,"(base hull)");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,30,50,140,20,"Design name 1");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,170,50,40,20,"Iron");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,210,50,40,20,"Bora");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,250,50,40,20,"Germ");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,290,50,40,20,"Res");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,380,50,100,20,"(base hull)");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,30,70,140,20,"Design name 1");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,170,70,40,20,"Iron");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,210,70,40,20,"Bora");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,250,70,40,20,"Germ");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,290,70,40,20,"Res");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,380,70,100,20,"(base hull)");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,30,90,140,20,"Design name 1");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,170,90,40,20,"Iron");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,210,90,40,20,"Bora");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,250,90,40,20,"Germ");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,290,90,40,20,"Res");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,380,90,100,20,"(base hull)");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,30,110,140,20,"Design name 1");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,170,110,40,20,"Iron");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,210,110,40,20,"Bora");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,250,110,40,20,"Germ");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,290,110,40,20,"Res");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,380,110,100,20,"(base hull)");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,30,130,140,20,"Design name 1");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,170,130,40,20,"Iron");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,210,130,40,20,"Bora");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,250,130,40,20,"Germ");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,290,130,40,20,"Res");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,380,130,100,20,"(base hull)");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,30,150,140,20,"Design name 1");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,170,150,40,20,"Iron");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,210,150,40,20,"Bora");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,250,150,40,20,"Germ");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,290,150,40,20,"Res");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,380,150,100,20,"(base hull)");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,30,170,140,20,"Design name 1");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,170,170,40,20,"Iron");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,210,170,40,20,"Bora");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,250,170,40,20,"Germ");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,290,170,40,20,"Res");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,380,170,100,20,"(base hull)");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,30,190,140,20,"Design name 1");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,170,190,40,20,"Iron");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,210,190,40,20,"Bora");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,250,190,40,20,"Germ");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,290,190,40,20,"Res");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,380,190,100,20,"(base hull)");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,30,210,140,20,"Design name 1");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,170,210,40,20,"Iron");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,210,210,40,20,"Bora");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,250,210,40,20,"Germ");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,290,210,40,20,"Res");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,380,210,100,20,"(base hull)");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,30,230,140,20,"Design name 1");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,170,230,40,20,"Iron");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,210,230,40,20,"Bora");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,250,230,40,20,"Germ");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,290,230,40,20,"Res");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,380,230,100,20,"(base hull)");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,30,250,140,20,"Design name 1");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,170,250,40,20,"Iron");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,210,250,40,20,"Bora");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,250,250,40,20,"Germ");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,290,250,40,20,"Res");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,380,250,100,20,"(base hull)");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,30,270,140,20,"Design name 1");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,170,270,40,20,"Iron");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,210,270,40,20,"Bora");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,250,270,40,20,"Germ");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,290,270,40,20,"Res");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,380,270,100,20,"(base hull)");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,330,10,50,20,"weight");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,330,30,50,20,"weight");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,330,50,50,20,"weight");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,330,70,50,20,"weight");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,330,90,50,20,"weight");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,330,110,50,20,"weight");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,330,130,50,20,"weight");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,330,150,50,20,"weight");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,330,170,50,20,"weight");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,330,190,50,20,"weight");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,330,210,50,20,"weight");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,330,230,50,20,"weight");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,330,250,50,20,"weight");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,330,270,50,20,"weight");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,10,10,20,20,"1");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,10,30,20,20,"2");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,10,50,20,20,"3");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,10,70,20,20,"4");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,10,90,20,20,"5");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,10,110,20,20,"6");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,10,130,20,20,"7");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,10,150,20,20,"8");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,10,170,20,20,"9");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,10,190,20,20,"10");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,10,210,20,20,"11");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,10,230,20,20,"12");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,10,250,20,20,"13");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,10,270,20,20,"14");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fl_end_form();

  fdui->RR_DesignsObjects->fdui = fdui;

  return fdui;
}
/*---------------------------------------*/


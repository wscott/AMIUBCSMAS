/* Form definition file generated with fdesign. */

extern "C" {
#include "forms.h"
}
#include <stdlib.h>
#include "pfunc.h"
#include "../src/starana-const.h"

static FL_PUP_ENTRY fdchoice_0[] =
{ 
    /*  itemtext   callback  shortcut   mode */
    { "skip",	0,	"",	 FL_PUP_NONE},
    { "stomp",	0,	"",	 FL_PUP_NONE},
    { "and",	0,	"",	 FL_PUP_NONE},
    { "or",	0,	"",	 FL_PUP_NONE},
    {0}
};

FD_DisplayFunction *create_form_DisplayFunction(void)
{
  FL_OBJECT *obj;
  FD_DisplayFunction *fdui = (FD_DisplayFunction *) fl_calloc(1, sizeof(*fdui));

  fdui->DisplayFunction = fl_bgn_form(FL_NO_BOX, 370, 330);
  obj = fl_add_box(FL_UP_BOX,0,0,370,330,"");
  fdui->description = obj = fl_add_text(FL_NORMAL_TEXT,10,40,350,60,"description");
    fl_set_object_boxtype(obj,FL_FRAME_BOX);
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->mask_circles = obj = fl_add_button(FL_PUSH_BUTTON,160,110,30,20,"C");
  fdui->input_par[0] = obj = fl_add_input(FL_NORMAL_INPUT,120,140,70,20,"Input");
  fdui->input_par[1] = obj = fl_add_input(FL_NORMAL_INPUT,120,160,70,20,"Input");
  fdui->input_par[2] = obj = fl_add_input(FL_NORMAL_INPUT,120,180,70,20,"Input");
  fdui->input_par[3] = obj = fl_add_input(FL_NORMAL_INPUT,120,200,70,20,"Input");
  fdui->input_par[4] = obj = fl_add_input(FL_NORMAL_INPUT,120,220,70,20,"Input");
  fdui->input_par[5] = obj = fl_add_input(FL_NORMAL_INPUT,290,140,70,20,"Input");
  fdui->input_par[6] = obj = fl_add_input(FL_NORMAL_INPUT,290,160,70,20,"Input");
  fdui->input_par[7] = obj = fl_add_input(FL_NORMAL_INPUT,290,180,70,20,"Input");
  fdui->input_par[8] = obj = fl_add_input(FL_NORMAL_INPUT,290,200,70,20,"Input");
  fdui->input_par[9] = obj = fl_add_input(FL_NORMAL_INPUT,290,220,70,20,"Input");
  fdui->mask_marker = obj = fl_add_button(FL_PUSH_BUTTON,220,110,30,20,"M");
  fdui->mask_flag = obj = fl_add_button(FL_PUSH_BUTTON,310,110,30,20,"F");
  fdui->mode = obj = fl_add_choice(FL_NORMAL_CHOICE2,60,110,90,20,"");
    fl_set_object_boxtype(obj,FL_FRAME_BOX);
   fl_set_choice_entries(obj, fdchoice_0);
   fl_set_choice(obj,1);
  fdui->number = obj = fl_add_menu(FL_PULLDOWN_MENU,10,5,40,30,"1");
    fl_set_object_boxtype(obj,FL_UP_BOX);
    fl_set_object_lsize(obj,FL_MEDIUM_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
    fl_set_object_callback(obj,pfecb_number,0);
  obj = fl_add_button(FL_NORMAL_BUTTON,10,290,80,30,"Apply");
    fl_set_object_callback(obj,pfecb_apply,0);
  obj = fl_add_button(FL_NORMAL_BUTTON,190,290,80,30,"Cancel");
    fl_set_object_callback(obj,pfecb_cancel,0);
  fdui->selected = obj = fl_add_menu(FL_PULLDOWN_MENU,50,5,310,30,"Select a Function");
    fl_set_object_boxtype(obj,FL_UP_BOX);
    fl_set_object_lsize(obj,FL_MEDIUM_SIZE);
    fl_set_object_callback(obj,pfecb_selected,0);
  fdui->mask_lines = obj = fl_add_button(FL_PUSH_BUTTON,190,110,30,20,"L");
  fdui->mask_name = obj = fl_add_button(FL_PUSH_BUTTON,280,110,30,20,"N");
  fdui->mask_data = obj = fl_add_button(FL_PUSH_BUTTON,250,110,30,20,"D");
  obj = fl_add_button(FL_NORMAL_BUTTON,280,290,80,30,"Close");
    fl_set_object_callback(obj,pfecb_close,0);
  obj = fl_add_button(FL_NORMAL_BUTTON,50,250,30,30,"@2");
    fl_set_object_callback(obj,pfecb_accept_and_next,0);
  obj = fl_add_button(FL_NORMAL_BUTTON,10,250,30,30,"@8");
    fl_set_object_callback(obj,pfecb_accept_and_prev,0);
  obj = fl_add_button(FL_NORMAL_BUTTON,170,250,70,30,"Delete");
    fl_set_object_callback(obj,pfecb_delete,0);
  obj = fl_add_button(FL_NORMAL_BUTTON,90,250,70,30,"Insert");
    fl_set_object_callback(obj,pfecb_insert,0);
  obj = fl_add_text(FL_NORMAL_TEXT,10,110,50,20,"Mode:");
    fl_set_object_boxtype(obj,FL_NO_BOX);
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fl_end_form();

  fdui->DisplayFunction->fdui = fdui;

  return fdui;
}
/*---------------------------------------*/

FD_MapControl *create_form_MapControl(void)
{
  FL_OBJECT *obj;
  FD_MapControl *fdui = (FD_MapControl *) fl_calloc(1, sizeof(*fdui));

  int oldbw = fl_get_border_width();
  fl_set_border_width(2);

  fdui->MapControl = fl_bgn_form(FL_NO_BOX, 470, 370);
  obj = fl_add_box(FL_UP_BOX,0,0,470,370,"");

  obj = fl_add_text(FL_NORMAL_TEXT,330,10,60,30,"Planetary\nViews");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  obj = fl_add_button(FL_NORMAL_BUTTON,330,90,60,30,"Editor");
    fl_set_object_callback(obj,mccb_pfeditorwindow,0);
  obj = fl_add_button(FL_NORMAL_BUTTON,330,50,60,30,"List");
    fl_set_object_callback(obj,mccb_pflistwindow,0);
  obj = fl_add_text(FL_NORMAL_TEXT,400,10,60,30,"Fleet\nViews");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  obj = fl_add_button(FL_NORMAL_BUTTON,400,50,60,30,"List");
    fl_set_object_callback(obj,mccb_fflistwindow,0);
  obj = fl_add_button(FL_NORMAL_BUTTON,400,90,60,30,"Editor");
    fl_set_object_callback(obj,mccb_ffeditorwindow,0);
  obj = fl_add_frame(FL_ENGRAVED_FRAME,395,10,70,115,"");
  obj = fl_add_frame(FL_ENGRAVED_FRAME,325,10,70,115,"");

  obj = fl_add_frame(FL_ENGRAVED_FRAME,5,5,305,160,"");
  fdui->racebox = obj = fl_add_box(FL_DOWN_BOX,10,170,450,200,"");
    fl_set_object_color(obj,FL_BLACK,FL_COL1);
  fdui->resetmap = obj = fl_add_button(FL_NORMAL_BUTTON,130,130,50,30,"Reset");
    fl_set_object_callback(obj,mccb_scrollmap,-1);
  fdui->upleft = obj = fl_add_button(FL_NORMAL_BUTTON,10,10,30,30,"@7");
    fl_set_object_callback(obj,mccb_scrollmap,7);
  fdui->up = obj = fl_add_button(FL_NORMAL_BUTTON,50,10,30,30,"@8");
    fl_set_object_callback(obj,mccb_scrollmap,8);
  fdui->upright = obj = fl_add_button(FL_NORMAL_BUTTON,90,10,30,30,"@9");
    fl_set_object_callback(obj,mccb_scrollmap,9);
  fdui->left = obj = fl_add_button(FL_NORMAL_BUTTON,10,50,30,30,"@4");
    fl_set_object_callback(obj,mccb_scrollmap,4);
  fdui->right = obj = fl_add_button(FL_NORMAL_BUTTON,90,50,30,30,"@6");
    fl_set_object_callback(obj,mccb_scrollmap,6);
  fdui->downleft = obj = fl_add_button(FL_NORMAL_BUTTON,10,90,30,30,"@1");
    fl_set_object_callback(obj,mccb_scrollmap,1);
  fdui->down = obj = fl_add_button(FL_NORMAL_BUTTON,50,90,30,30,"@2");
    fl_set_object_callback(obj,mccb_scrollmap,2);
  fdui->downright = obj = fl_add_button(FL_NORMAL_BUTTON,90,90,30,30,"@3");
    fl_set_object_callback(obj,mccb_scrollmap,3);
  fdui->future = obj = fl_add_input(FL_NORMAL_INPUT,150,100,40,20,"Future");
    fl_set_input(obj, "0");
    fl_set_object_lalign(obj,FL_ALIGN_TOP);
    fl_set_object_callback(obj,mccb_setfuture,0);
  fdui->decfuture = obj = fl_add_button(FL_NORMAL_BUTTON,130,100,20,20,"@4");
    fl_set_object_callback(obj,mccb_setfuture,-1);
  fdui->incfuture = obj = fl_add_button(FL_NORMAL_BUTTON,190,100,20,20,"@6");
    fl_set_object_callback(obj,mccb_setfuture,1);
  fdui->redraw = obj = fl_add_button(FL_NORMAL_BUTTON,250,130,50,30,"Redraw");
    fl_set_object_callback(obj,mccb_scrollmap,0);
  fdui->autoredraw = obj = fl_add_button(FL_PUSH_BUTTON,190,130,50,30,"Auto\nRedraw");
  fdui->racetitle = obj = fl_add_text(FL_NORMAL_TEXT,160,170,150,30,"RACES");
    fl_set_object_boxtype(obj,FL_NO_BOX);
    fl_set_object_color(obj,FL_BLACK,FL_BLACK);
    fl_set_object_lcolor(obj,FL_WHITE);
    fl_set_object_lsize(obj,FL_MEDIUM_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
    fl_set_object_lstyle(obj,FL_BOLD_STYLE);
  fdui->race[0] = obj = fl_add_button(FL_NORMAL_BUTTON,40,200,180,20,"<no race 1>");
    fl_set_object_boxtype(obj,FL_NO_BOX);
    fl_set_object_color(obj,FL_BLACK,FL_COL1);
    fl_set_object_lcolor(obj,FL_COL1);
    fl_set_object_callback(obj,mccb_setraceviewpoint,1);
  fdui->race[2] = obj = fl_add_button(FL_NORMAL_BUTTON,40,220,180,20,"<no race 3>");
    fl_set_object_boxtype(obj,FL_NO_BOX);
    fl_set_object_color(obj,FL_BLACK,FL_COL1);
    fl_set_object_lcolor(obj,FL_COL1);
    fl_set_object_callback(obj,mccb_setraceviewpoint,3);
  fdui->race[1] = obj = fl_add_button(FL_NORMAL_BUTTON,250,200,180,20,"<no race 2>");
    fl_set_object_boxtype(obj,FL_NO_BOX);
    fl_set_object_color(obj,FL_BLACK,FL_COL1);
    fl_set_object_lcolor(obj,FL_COL1);
    fl_set_object_callback(obj,mccb_setraceviewpoint,2);
  fdui->race[3] = obj = fl_add_button(FL_NORMAL_BUTTON,250,220,180,20,"<no race 4>");
    fl_set_object_boxtype(obj,FL_NO_BOX);
    fl_set_object_color(obj,FL_BLACK,FL_COL1);
    fl_set_object_lcolor(obj,FL_COL1);
    fl_set_object_callback(obj,mccb_setraceviewpoint,4);
  fdui->race[4] = obj = fl_add_button(FL_NORMAL_BUTTON,40,240,180,20,"<no race 5>");
    fl_set_object_boxtype(obj,FL_NO_BOX);
    fl_set_object_color(obj,FL_BLACK,FL_COL1);
    fl_set_object_lcolor(obj,FL_COL1);
    fl_set_object_callback(obj,mccb_setraceviewpoint,5);
  fdui->race[6] = obj = fl_add_button(FL_NORMAL_BUTTON,40,260,180,20,"<no race 7>");
    fl_set_object_boxtype(obj,FL_NO_BOX);
    fl_set_object_color(obj,FL_BLACK,FL_COL1);
    fl_set_object_lcolor(obj,FL_COL1);
    fl_set_object_callback(obj,mccb_setraceviewpoint,7);
  fdui->race[5] = obj = fl_add_button(FL_NORMAL_BUTTON,250,240,180,20,"<no race 6>");
    fl_set_object_boxtype(obj,FL_NO_BOX);
    fl_set_object_color(obj,FL_BLACK,FL_COL1);
    fl_set_object_lcolor(obj,FL_COL1);
    fl_set_object_callback(obj,mccb_setraceviewpoint,6);
  fdui->race[7] = obj = fl_add_button(FL_NORMAL_BUTTON,250,260,180,20,"<no race 8>");
    fl_set_object_boxtype(obj,FL_NO_BOX);
    fl_set_object_color(obj,FL_BLACK,FL_COL1);
    fl_set_object_lcolor(obj,FL_COL1);
    fl_set_object_callback(obj,mccb_setraceviewpoint,8);
  fdui->race[8] = obj = fl_add_button(FL_NORMAL_BUTTON,40,280,180,20,"<no race 9>");
    fl_set_object_boxtype(obj,FL_NO_BOX);
    fl_set_object_color(obj,FL_BLACK,FL_COL1);
    fl_set_object_lcolor(obj,FL_COL1);
    fl_set_object_callback(obj,mccb_setraceviewpoint,9);
  fdui->race[10] = obj = fl_add_button(FL_NORMAL_BUTTON,40,300,180,20,"<no race 11>");
    fl_set_object_boxtype(obj,FL_NO_BOX);
    fl_set_object_color(obj,FL_BLACK,FL_COL1);
    fl_set_object_lcolor(obj,FL_COL1);
    fl_set_object_callback(obj,mccb_setraceviewpoint,11);
  fdui->race[9] = obj = fl_add_button(FL_NORMAL_BUTTON,250,280,180,20,"<no race 10>");
    fl_set_object_boxtype(obj,FL_NO_BOX);
    fl_set_object_color(obj,FL_BLACK,FL_COL1);
    fl_set_object_lcolor(obj,FL_COL1);
    fl_set_object_callback(obj,mccb_setraceviewpoint,10);
  fdui->race[11] = obj = fl_add_button(FL_NORMAL_BUTTON,250,300,180,20,"<no race 12>");
    fl_set_object_boxtype(obj,FL_NO_BOX);
    fl_set_object_color(obj,FL_BLACK,FL_COL1);
    fl_set_object_lcolor(obj,FL_COL1);
    fl_set_object_callback(obj,mccb_setraceviewpoint,12);
  fdui->race[12] = obj = fl_add_button(FL_NORMAL_BUTTON,40,320,180,20,"<no race 13>");
    fl_set_object_boxtype(obj,FL_NO_BOX);
    fl_set_object_color(obj,FL_BLACK,FL_COL1);
    fl_set_object_lcolor(obj,FL_COL1);
    fl_set_object_callback(obj,mccb_setraceviewpoint,13);
  fdui->race[14] = obj = fl_add_button(FL_NORMAL_BUTTON,40,340,180,20,"<no race 15>");
    fl_set_object_boxtype(obj,FL_NO_BOX);
    fl_set_object_color(obj,FL_BLACK,FL_COL1);
    fl_set_object_lcolor(obj,FL_COL1);
    fl_set_object_callback(obj,mccb_setraceviewpoint,15);
  fdui->race[13] = obj = fl_add_button(FL_NORMAL_BUTTON,250,320,180,20,"<no race 14>");
    fl_set_object_boxtype(obj,FL_NO_BOX);
    fl_set_object_color(obj,FL_BLACK,FL_COL1);
    fl_set_object_lcolor(obj,FL_COL1);
    fl_set_object_callback(obj,mccb_setraceviewpoint,14);
  fdui->race[15] = obj = fl_add_button(FL_NORMAL_BUTTON,250,340,180,20,"<no race 16>");
    fl_set_object_boxtype(obj,FL_NO_BOX);
    fl_set_object_color(obj,FL_BLACK,FL_COL1);
    fl_set_object_lcolor(obj,FL_COL1);
    fl_set_object_callback(obj,mccb_setraceviewpoint,16);
  fdui->mapmode = obj = fl_add_choice(FL_NORMAL_CHOICE2,130,25,170,30,"Background mode");
    fl_set_object_boxtype(obj,FL_FRAME_BOX);
    fl_set_object_lalign(obj,FL_ALIGN_TOP);
    fl_set_object_callback(obj,mccb_setbkgmode,0);
  fdui->quit = obj = fl_add_button(FL_NORMAL_BUTTON,400,130,60,30,"Quit");
  fdui->center = obj = fl_add_button(FL_NORMAL_BUTTON,50,50,30,30,"@-2circle");
    fl_set_object_callback(obj,mccb_scrollmap,5);
  fdui->zoomout = obj = fl_add_button(FL_NORMAL_BUTTON,10,130,50,30,"Zoom out");
    fl_set_object_callback(obj,mccb_scrollmap,-3);
  fdui->zoomin = obj = fl_add_button(FL_NORMAL_BUTTON,70,130,50,30,"Zoom in");
    fl_set_object_callback(obj,mccb_scrollmap,-2);
  fdui->scaneff = obj = fl_add_input(FL_NORMAL_INPUT,230,100,60,20,"Scanner\nEfficiency");
    fl_set_object_lalign(obj,FL_ALIGN_TOP);
    fl_set_object_callback(obj,mccb_setscaneff,0);
  fdui->alliances = obj = fl_add_button(FL_PUSH_BUTTON,130,60,80,20,"Alliances");
    fl_set_object_callback(obj,mccb_alliances,0);
  fl_end_form();
  fl_set_border_width(oldbw);

  fdui->MapControl->fdui = fdui;

  return fdui;
}
/*---------------------------------------*/

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
  fdui->popfilldial = obj = fl_add_dial(FL_FILL_DIAL,120,85,30,40,"");
    fl_set_object_color(obj,FL_COL1,FL_GREEN);
    fl_set_dial_bounds(obj, 0, 100);
    fl_set_dial_value(obj, 25);
  fdui->popfill = obj = fl_add_text(FL_NORMAL_TEXT,80,100,40,20,"ppf");
    fl_set_object_lalign(obj,FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
  fdui->popgrowth = obj = fl_add_text(FL_NORMAL_TEXT,10,105,70,20,"(+ growth)");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->population = obj = fl_add_text(FL_NORMAL_TEXT,10,85,110,20,"Pop now");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->ironium = obj = fl_add_text(FL_NORMAL_TEXT,20,265,80,20,"XXXXX+YYYY");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->boranium = obj = fl_add_text(FL_NORMAL_TEXT,20,285,80,20,"XXXXX+YYYY");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->germanium = obj = fl_add_text(FL_NORMAL_TEXT,20,305,80,20,"XXXXX+YYYY");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,250,165,70,20,"Scanner");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->mines = obj = fl_add_text(FL_NORMAL_TEXT,80,145,100,20,"XXX/YYY/ZZZ");
    fl_set_object_lalign(obj,FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
  fdui->factories = obj = fl_add_text(FL_NORMAL_TEXT,80,165,100,20,"XXX/YYY/ZZZ");
    fl_set_object_lalign(obj,FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
  fdui->defenses = obj = fl_add_text(FL_NORMAL_TEXT,320,145,100,20,"XXX/YYY (zz%)");
    fl_set_object_lalign(obj,FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,250,145,50,20,"Defenses");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,20,165,50,20,"Factories");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,20,145,50,20,"Mines");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->scanning = obj = fl_add_text(FL_NORMAL_TEXT,350,165,70,20,"XXX/YYY");
    fl_set_object_lalign(obj,FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
  fdui->stbdamage = obj = fl_add_text(FL_NORMAL_TEXT,390,85,40,20,"DMG%");
    fl_set_object_lcolor(obj,FL_RED);
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->starbasename = obj = fl_add_text(FL_NORMAL_TEXT,165,85,230,20,"Starbase design name");
    fl_set_object_lsize(obj,FL_NORMAL_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->gaterange = obj = fl_add_text(FL_NORMAL_TEXT,165,105,100,20,"Gate x/y");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->massdriver = obj = fl_add_text(FL_NORMAL_TEXT,265,105,160,20,"MD-x @ Planet Name");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->planetname = obj = fl_add_text(FL_NORMAL_TEXT,10,8,290,25,"Planet Name (HW) (#id)");
    fl_set_object_lsize(obj,FL_LARGE_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->position = obj = fl_add_text(FL_NORMAL_TEXT,350,25,80,20,"(pos,pos)");
    fl_set_object_lalign(obj,FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
  fdui->type = obj = fl_add_text(FL_NORMAL_TEXT,340,5,90,20,"-type-");
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
  fdui->ironiumdial = obj = fl_add_free(FL_INACTIVE_FREE,110,265,280,20,"",
			freeobj_ironiumdial_handle);
  fdui->boraniumdial = obj = fl_add_free(FL_INACTIVE_FREE,110,285,280,20,"",
			freeobj_boraniumdial_handle);
  fdui->germaniumdial = obj = fl_add_free(FL_INACTIVE_FREE,110,305,280,20,"",
			freeobj_germaniumdial_handle);
  fdui->ironconc = obj = fl_add_text(FL_NORMAL_TEXT,390,265,30,20,"iC");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->boraconc = obj = fl_add_text(FL_NORMAL_TEXT,390,285,30,20,"bC");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->germconc = obj = fl_add_text(FL_NORMAL_TEXT,390,305,30,20,"gC");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->envdial[0] = obj = fl_add_habdial(FL_HABNORMAL,20,375,400,20,"");
  fdui->envdial[1] = obj = fl_add_habdial(FL_HABNORMAL,20,395,400,20,"");
  fdui->envdial[2] = obj = fl_add_habdial(FL_HABNORMAL,20,415,400,20,"");
  fdui->close = obj = fl_add_button(FL_NORMAL_BUTTON,360,450,70,30,"Close");
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
  fdui->habvpoint = obj = fl_add_text(FL_NORMAL_TEXT,230,350,70,20,"Viewpoint:");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->habowner = obj = fl_add_text(FL_NORMAL_TEXT,20,350,70,20,"Owner:");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);

  fdui->minscale = obj = fl_add_choice(FL_NORMAL_CHOICE2,20,240,100,20,"");
    fl_set_object_boxtype(obj,FL_FRAME_BOX);
    fl_set_object_callback(obj,pscb_setminscale,0);
  fdui->testobject = obj = fl_add_choice(FL_NORMAL_CHOICE2,130,240,120,20,"");
    fl_set_object_boxtype(obj,FL_FRAME_BOX);
    fl_set_object_callback(obj,pscb_settestobject,0);
  fdui->minobjects[0] = obj = fl_add_text(FL_NORMAL_TEXT,260,240,40,20,"Imul");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->minobjects[1] = obj = fl_add_text(FL_NORMAL_TEXT,300,240,40,20,"Bmul");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->minobjects[2] = obj = fl_add_text(FL_NORMAL_TEXT,340,240,40,20,"Gmul");
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


FD_ObjectViews *create_form_ObjectViews(void)
{
  FL_OBJECT *obj;
  FD_ObjectViews *fdui = (FD_ObjectViews *) fl_calloc(1, sizeof(*fdui));

  fdui->ObjectViews = fl_bgn_form(FL_NO_BOX, 380, 390);
  obj = fl_add_box(FL_UP_BOX,0,0,380,390,"");

  fdui->pvlist = obj = fl_add_browser(FL_HOLD_BROWSER,10,10,360,290,"");
    fl_set_object_callback(obj,pvcb_select,0);
  fdui->del = obj = fl_add_button(FL_NORMAL_BUTTON,10,310,60,30,"Delete");
    fl_set_object_callback(obj,pvcb_delete,0);
  fdui->clone = obj = fl_add_button(FL_NORMAL_BUTTON,80,310,60,30,"Clone");
    fl_set_object_callback(obj,pvcb_clone,0);
  fdui->rename = obj = fl_add_button(FL_NORMAL_BUTTON,150,310,60,30,"Rename");
    fl_set_object_callback(obj,pvcb_rename,0);
  fdui->pfeditor = obj = fl_add_button(FL_NORMAL_BUTTON,220,310,60,30,"Edit");
    fl_set_object_callback(obj,pvcb_pfeditor,0);
  fdui->moveup = obj = fl_add_button(FL_NORMAL_BUTTON,300,310,30,30,"@8");
    fl_set_object_callback(obj,pvcb_move,-1);
  fdui->movedown = obj = fl_add_button(FL_NORMAL_BUTTON,340,310,30,30,"@2");
    fl_set_object_callback(obj,pvcb_move,1);
  fdui->import = obj = fl_add_button(FL_NORMAL_BUTTON,10,350,60,30,"Import");
    fl_set_object_callback(obj,pvcb_load,0);
  fdui->save = obj = fl_add_button(FL_NORMAL_BUTTON,80,350,60,30,"Save");
    fl_set_object_callback(obj,pvcb_save,0);
  fdui->export = obj = fl_add_button(FL_NORMAL_BUTTON,150,350,60,30,"Export");
    fl_set_object_callback(obj,pvcb_export,0);
  fdui->close = obj = fl_add_button(FL_NORMAL_BUTTON,310,350,60,30,"Close");
    fl_set_object_callback(obj,pvcb_close,0);
  fl_end_form();

  fdui->ObjectViews->fdui = fdui;

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
    fl_set_object_color(obj,FL_BOTTOM_BCOL,FL_YELLOW);
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
  fdui->planetname[0] = obj = fl_add_text(FL_NORMAL_TEXT,10,20,190,30,"Wammalammadingdong");
    fl_set_object_lsize(obj,FL_MEDIUM_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
    fl_set_object_lstyle(obj,FL_BOLD_STYLE);
  fdui->twindriver[0] = obj = fl_add_lightbutton(FL_PUSH_BUTTON,130,60,60,30,"Twin");
    fl_set_object_boxtype(obj,FL_NO_BOX);
  fdui->racenotes[0] = obj = fl_add_text(FL_NORMAL_TEXT,10,150,190,30,"Racial notes");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_button(FL_NORMAL_BUTTON,380,200,70,30,"Fastest\nkiller");
    fl_set_object_callback(obj,pfcb_fastkiller,0);
  fdui->population[0] = obj = fl_add_input(FL_NORMAL_INPUT,70,100,120,20,"Population:");
  fdui->ndefenses[0] = obj = fl_add_input(FL_NORMAL_INPUT,70,120,50,20,"Defenses:");
  fdui->defcoverage[0] = obj = fl_add_text(FL_NORMAL_TEXT,130,120,60,20,"(99.45%)");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->framedue = obj = fl_add_labelframe(FL_ENGRAVED_FRAME,275,10,200,180,"Planet #2");
  fdui->planetname[1] = obj = fl_add_text(FL_NORMAL_TEXT,280,20,190,30,"Wammalammadingdong");
    fl_set_object_lsize(obj,FL_MEDIUM_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
    fl_set_object_lstyle(obj,FL_BOLD_STYLE);
  fdui->twindriver[1] = obj = fl_add_lightbutton(FL_PUSH_BUTTON,400,60,60,30,"Twin");
    fl_set_object_boxtype(obj,FL_NO_BOX);
  fdui->racenotes[1] = obj = fl_add_text(FL_NORMAL_TEXT,280,150,190,30,"Racial notes");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->population[1] = obj = fl_add_input(FL_NORMAL_INPUT,340,100,120,20,"Population:");
  fdui->ndefenses[1] = obj = fl_add_input(FL_NORMAL_INPUT,340,120,50,20,"Defenses:");
  fdui->defcoverage[1] = obj = fl_add_text(FL_NORMAL_TEXT,400,120,60,20,"(99.45%)");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->driverwarp[0] = obj = fl_add_text(FL_NORMAL_TEXT,50,60,40,30,"W");
    fl_set_object_boxtype(obj,FL_BORDER_BOX);
    fl_set_object_lsize(obj,FL_MEDIUM_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
    fl_set_object_lstyle(obj,FL_BOLD_STYLE);
  fdui->increasewarp1 = obj = fl_add_scrollbutton(FL_TOUCH_BUTTON,90,60,30,30,"6");
    fl_set_object_boxtype(obj,FL_BORDER_BOX);
  fdui->lowerwarp1 = obj = fl_add_scrollbutton(FL_TOUCH_BUTTON,20,60,30,30,"4");
    fl_set_object_boxtype(obj,FL_BORDER_BOX);
  fdui->driverwarp[1] = obj = fl_add_text(FL_NORMAL_TEXT,320,60,40,30,"W");
    fl_set_object_boxtype(obj,FL_BORDER_BOX);
    fl_set_object_lsize(obj,FL_MEDIUM_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
    fl_set_object_lstyle(obj,FL_BOLD_STYLE);
  fdui->increasewarp2 = obj = fl_add_scrollbutton(FL_TOUCH_BUTTON,360,60,30,30,"6");
    fl_set_object_boxtype(obj,FL_BORDER_BOX);
  fdui->lowerwarp2 = obj = fl_add_scrollbutton(FL_TOUCH_BUTTON,290,60,30,30,"4");
    fl_set_object_boxtype(obj,FL_BORDER_BOX);

  obj = fl_add_text(FL_NORMAL_TEXT,210,90,60,20,"Distance:");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->packetdirection = obj = fl_add_button(FL_NORMAL_BUTTON,210,40,60,30,"@5");
  fdui->planetdistance = obj = fl_add_text(FL_NORMAL_TEXT,210,110,60,20,"9999 l.y.");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->close = obj = fl_add_button(FL_NORMAL_BUTTON,400,420,70,30,"Close");
    fl_set_object_callback(obj,pfcb_close,0);
  fdui->mineralspent = obj = fl_add_counter(FL_NORMAL_COUNTER,110,200,180,20,"Minerals spent: ");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT);
  fdui->cheapkiller = obj = fl_add_button(FL_NORMAL_BUTTON,300,200,70,30,"Cheapest\nkiller");
    fl_set_object_callback(obj,pfcb_cheapkiller,0);

  obj = fl_add_text(FL_NORMAL_TEXT,70,240,40,30,"Travel\ntime");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,110,240,90,30,"Minerals\narrived / recov.");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,200,240,100,30,"Colonists\nkilled / left");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,30,240,40,30,"Warp");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,300,240,80,30,"Defenses\ndestroyed / left");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,390,240,60,30,"Tforming\nstd / perm");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->colkill[0] = obj = fl_add_text(FL_NORMAL_TEXT,200,270,100,20,"769500 / 175900");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->mineral[0] = obj = fl_add_text(FL_NORMAL_TEXT,110,270,90,20,"22700 / 22700");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->travel[0] = obj = fl_add_text(FL_NORMAL_TEXT,70,270,40,20,"3");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->warp[0] = obj = fl_add_text(FL_NORMAL_TEXT,30,270,40,20,"7");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->defdestroy[0] = obj = fl_add_text(FL_NORMAL_TEXT,300,270,80,20,"27 / 56");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->terraform[0] = obj = fl_add_text(FL_NORMAL_TEXT,390,270,60,20,"12 / 1");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->colkill[1] = obj = fl_add_text(FL_NORMAL_TEXT,200,290,100,20,"769500 / 175900");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->travel[1] = obj = fl_add_text(FL_NORMAL_TEXT,70,290,40,20,"3");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->warp[1] = obj = fl_add_text(FL_NORMAL_TEXT,30,290,40,20,"8");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->defdestroy[1] = obj = fl_add_text(FL_NORMAL_TEXT,300,290,80,20,"27 / 56");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->terraform[1] = obj = fl_add_text(FL_NORMAL_TEXT,390,290,60,20,"12 / 1");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->colkill[2] = obj = fl_add_text(FL_NORMAL_TEXT,200,310,100,20,"769500 / 175900");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->travel[2] = obj = fl_add_text(FL_NORMAL_TEXT,70,310,40,20,"3");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->warp[2] = obj = fl_add_text(FL_NORMAL_TEXT,30,310,40,20,"9");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->defdestroy[2] = obj = fl_add_text(FL_NORMAL_TEXT,300,310,80,20,"27 / 56");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->terraform[2] = obj = fl_add_text(FL_NORMAL_TEXT,390,310,60,20,"12 / 1");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->colkill[3] = obj = fl_add_text(FL_NORMAL_TEXT,200,330,100,20,"769500 / 175900");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->travel[3] = obj = fl_add_text(FL_NORMAL_TEXT,70,330,40,20,"3");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->warp[3] = obj = fl_add_text(FL_NORMAL_TEXT,30,330,40,20,"10");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->defdestroy[3] = obj = fl_add_text(FL_NORMAL_TEXT,300,330,80,20,"27 / 56");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->terraform[3] = obj = fl_add_text(FL_NORMAL_TEXT,390,330,60,20,"12 / 1");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->colkill[4] = obj = fl_add_text(FL_NORMAL_TEXT,200,350,100,20,"769500 / 175900");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->travel[4] = obj = fl_add_text(FL_NORMAL_TEXT,70,350,40,20,"3");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->warp[4] = obj = fl_add_text(FL_NORMAL_TEXT,30,350,40,20,"11");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->defdestroy[4] = obj = fl_add_text(FL_NORMAL_TEXT,300,350,80,20,"27 / 56");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->terraform[4] = obj = fl_add_text(FL_NORMAL_TEXT,390,350,60,20,"12 / 1");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->colkill[5] = obj = fl_add_text(FL_NORMAL_TEXT,200,370,100,20,"769500 / 175900");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->travel[5] = obj = fl_add_text(FL_NORMAL_TEXT,70,370,40,20,"3");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->warp[5] = obj = fl_add_text(FL_NORMAL_TEXT,30,370,40,20,"12");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->defdestroy[5] = obj = fl_add_text(FL_NORMAL_TEXT,300,370,80,20,"27 / 56");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->terraform[5] = obj = fl_add_text(FL_NORMAL_TEXT,390,370,60,20,"12 / 1");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->colkill[6] = obj = fl_add_text(FL_NORMAL_TEXT,200,390,100,20,"769500 / 175900");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->travel[6] = obj = fl_add_text(FL_NORMAL_TEXT,70,390,40,20,"3");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->warp[6] = obj = fl_add_text(FL_NORMAL_TEXT,30,390,40,20,"13");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->defdestroy[6] = obj = fl_add_text(FL_NORMAL_TEXT,300,390,80,20,"27 / 56");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->terraform[6] = obj = fl_add_text(FL_NORMAL_TEXT,390,390,60,20,"12 / 1");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->mineral[1] = obj = fl_add_text(FL_NORMAL_TEXT,110,290,90,20,"22700 / 22700");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->mineral[2] = obj = fl_add_text(FL_NORMAL_TEXT,110,310,90,20,"22700 / 22700");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->mineral[3] = obj = fl_add_text(FL_NORMAL_TEXT,110,330,90,20,"22700 / 22700");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->mineral[4] = obj = fl_add_text(FL_NORMAL_TEXT,110,350,90,20,"22700 / 22700");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->mineral[5] = obj = fl_add_text(FL_NORMAL_TEXT,110,370,90,20,"22700 / 22700");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fdui->mineral[6] = obj = fl_add_text(FL_NORMAL_TEXT,110,390,90,20,"22700 / 22700");
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
  fdui->statusmsg = obj = fl_add_text(FL_NORMAL_TEXT,20,280,370,30,"Loading report files: initialize");
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
  obj = fl_add_text(FL_NORMAL_TEXT,280,40,110,30,"(8 Nov 1998)");
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
  obj = fl_add_text(FL_NORMAL_TEXT,20,190,60,20,"Credits: ");
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
  obj = fl_add_text(FL_NORMAL_TEXT,80,190,70,80,"(patches)\n(testing)\n(formulae)\n(Stars! :)\n(ideas)");
    fl_set_object_color(obj,FL_INACTIVE,FL_MCOL);
    fl_set_object_lcolor(obj,FL_LEFT_BCOL);
    fl_set_object_lsize(obj,FL_NORMAL_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,150,190,240,80,"Wayne Smith\nJ. Ballantyne, J. Andersen, A. Controzzi\nLoren Webster, Jason Cawley\nJeff^2\nall the rec.games.computer.stars people");
    fl_set_object_color(obj,FL_INACTIVE,FL_MCOL);
    fl_set_object_lcolor(obj,FL_WHITE);
    fl_set_object_lsize(obj,FL_NORMAL_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fl_end_form();

  fdui->IntroTitle->fdui = fdui;

  return fdui;
}
/*---------------------------------------*/

FD_RacialReport *create_form_RacialReport(FD_RR_RaceInfo* tf1,
					  FD_RR_ReportLog* tf2,
					  FD_RR_Comparisons* tf3,
					  FD_RR_Designs* tf4,
					  FD_RR_Objects* tf5,
					  FD_RR_Filtering* tf6)
{
  FL_OBJECT *obj;
  FD_RacialReport *fdui = (FD_RacialReport *) fl_calloc(1, sizeof(*fdui));

  fdui->RacialReport = fl_bgn_form(FL_NO_BOX, 640, 410);
  obj = fl_add_box(FL_UP_BOX,0,0,640,410,"");
  obj = fl_add_tabfolder(FL_TOP_TABFOLDER,10,40,620,320,"");
    fl_set_object_boxtype(obj,FL_NO_BOX);
    fl_addto_tabfolder(obj, "Race design", tf1->RR_RaceInfo);
    fl_addto_tabfolder(obj, "Report-log", tf2->RR_ReportLog);
    fl_addto_tabfolder(obj, "Simulation", tf3->RR_Comparisons);
    fl_addto_tabfolder(obj, "Ship designs", tf4->RR_Designs);
    fl_addto_tabfolder(obj, "Ship designs", tf5->RR_Objects);
    fl_addto_tabfolder(obj, "Ship designs", tf6->RR_Filtering);
  obj = fl_add_text(FL_NORMAL_TEXT,30,5,110,30,"Racial Report:");
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
  fdui->race_names = obj = fl_add_text(FL_NORMAL_TEXT,140,5,340,30,"??????????????? (?????????????????s)");
    fl_set_object_lsize(obj,FL_MEDIUM_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
    fl_set_object_lstyle(obj,FL_BOLD_STYLE);
  obj = fl_add_button(FL_NORMAL_BUTTON,550,370,80,30,"Close");
    fl_set_object_callback(obj,rrcb_close,0);
  fl_end_form();

  fdui->RacialReport->fdui = fdui;

  return fdui;
}
/*---------------------------------------*/

FD_RR_RaceInfo *create_form_RR_RaceInfo(void)
{
  FL_OBJECT *obj;
  FD_RR_RaceInfo *fdui = (FD_RR_RaceInfo *) fl_calloc(1, sizeof(*fdui));
  int i;

  fdui->RR_RaceInfo = fl_bgn_form(FL_NO_BOX, 610, 290);
  obj = fl_add_box(FL_FLAT_BOX,0,0,610,290,"");
  obj = fl_add_text(FL_NORMAL_TEXT,490,10,80,20,"Player number:");
    fl_set_object_lalign(obj,FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,10,10,70,20,"Racial traits:");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,10,130,100,20,"Technology levels:");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,10,150,100,20,"Terraforming tech:");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,10,40,70,20,"Colonist eff.:");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,10,60,70,20,"Factories:");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,10,80,70,20,"Mines:");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,10,240,100,20,"Controlled planets:");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,510,30,60,20,"Reliability:");
    fl_set_object_lalign(obj,FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,10,110,100,20,"Research cost:");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->habgraph = obj = fl_add_xyplot(FL_NORMAL_XYPLOT,390,80,210,200,"");
    fl_set_object_boxtype(obj,FL_DOWN_BOX);
    fl_set_object_color(obj,FL_BLACK,FL_WHITE);
  obj = fl_add_text(FL_NORMAL_TEXT,170,80,140,20,"Max resources/100% world:");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,390,60,120,20,"Habitability distribution:");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,170,240,100,20,"Total Population:");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,10,260,100,20,"Total Fleets:");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);

  fdui->prt_lrt = obj = fl_add_text(FL_NORMAL_TEXT,80,10,180,20,"");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
    fl_set_object_lstyle(obj,FL_BOLD_STYLE);
  fdui->col_res = obj = fl_add_text(FL_NORMAL_TEXT,80,40,80,20,"");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
    fl_set_object_lstyle(obj,FL_BOLD_STYLE);
  fdui->factories = obj = fl_add_text(FL_NORMAL_TEXT,80,60,120,20,"");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
    fl_set_object_lstyle(obj,FL_BOLD_STYLE);
  fdui->mines = obj = fl_add_text(FL_NORMAL_TEXT,80,80,80,20,"");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
    fl_set_object_lstyle(obj,FL_BOLD_STYLE);
  fdui->res100pct = obj = fl_add_text(FL_NORMAL_TEXT,310,80,70,20,"");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
    fl_set_object_lstyle(obj,FL_BOLD_STYLE);
  fdui->totalplanets = obj = fl_add_text(FL_NORMAL_TEXT,110,240,50,20,"");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
    fl_set_object_lstyle(obj,FL_BOLD_STYLE);
  fdui->totalpop = obj = fl_add_text(FL_NORMAL_TEXT,260,240,110,20,"");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
    fl_set_object_lstyle(obj,FL_BOLD_STYLE);
  fdui->totalfleets = obj = fl_add_text(FL_NORMAL_TEXT,80,260,30,20,"");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
    fl_set_object_lstyle(obj,FL_BOLD_STYLE);
  fdui->shiptypes = obj = fl_add_text(FL_NORMAL_TEXT,110,260,270,20,"");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
    fl_set_object_lstyle(obj,FL_ITALIC_STYLE);
  fdui->explored = obj = fl_add_text(FL_NORMAL_TEXT,510,60,90,20,"");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->playern = obj = fl_add_text(FL_NORMAL_TEXT,570,10,30,20,"");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
    fl_set_object_lstyle(obj,FL_BOLD_STYLE);
  fdui->reliability = obj = fl_add_text(FL_NORMAL_TEXT,570,30,30,20,"");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
    fl_set_object_lstyle(obj,FL_BOLD_STYLE);

  for (i = 0; i < 6; i++) {
    fdui->techcost[i] = obj = fl_add_text(FL_NORMAL_TEXT,110 + i*40,110,40,20,"");
      fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
      fl_set_object_lstyle(obj,FL_BOLD_STYLE);
    fdui->techlevel[i] = obj = fl_add_text(FL_NORMAL_TEXT,110 + i*40,130,40,20,"");
      fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
      fl_set_object_lstyle(obj,FL_BOLD_STYLE);
  }

  fdui->techterra[0] = obj = fl_add_text(FL_NORMAL_TEXT,110,150,40,20,"");
    fl_set_object_lcolor(obj,FL_RED);
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
    fl_set_object_lstyle(obj,FL_BOLD_STYLE);
  fdui->techterra[1] = obj = fl_add_text(FL_NORMAL_TEXT,150,150,40,20,"");
    fl_set_object_lcolor(obj,FL_GREEN);
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
    fl_set_object_lstyle(obj,FL_BOLD_STYLE);
  fdui->techterra[2] = obj = fl_add_text(FL_NORMAL_TEXT,190,150,40,20,"");
    fl_set_object_lcolor(obj,FL_BLUE);
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
    fl_set_object_lstyle(obj,FL_BOLD_STYLE);

  fdui->habdial[0] = obj = fl_add_habdial(FL_HABNORMAL,20,170,360,20,"");
  fdui->habdial[1] = obj = fl_add_habdial(FL_HABNORMAL,20,170,360,20,"");
  fdui->habdial[2] = obj = fl_add_habdial(FL_HABNORMAL,20,170,360,20,"");
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
  obj = fl_add_box(FL_FLAT_BOX,0,0,610,290,"");
  fdui->messages = obj = fl_add_browser(FL_NORMAL_BROWSER,10,10,590,270,"");
    fl_set_object_color(obj,FL_BOTTOM_BCOL,FL_YELLOW);
  
  // workaround
  obj = fl_add_box(FL_FLAT_BOX,1,1,1,1,"");

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
    { "Population growth",	0,	"",	 FL_PUP_NONE},
    { "Minerals",	0,	"",	 FL_PUP_NONE},
    { "Ironium",	0,	"",	 FL_PUP_NONE},
    { "Boranium",	0,	"",	 FL_PUP_NONE},
    { "Germanium",	0,	"",	 FL_PUP_NONE},
    { "Mining Rates",	0,	"",	 FL_PUP_NONE},
    {0}
};

FD_RR_Comparisons *create_form_RR_Comparisons(void)
{
  FL_OBJECT *obj;
  FD_RR_Comparisons *fdui = (FD_RR_Comparisons *) fl_calloc(1, sizeof(*fdui));

  fdui->RR_Comparisons = fl_bgn_form(FL_NO_BOX, 610, 290);
  obj = fl_add_box(FL_FLAT_BOX,0,0,610,290,"");
  fdui->racegraph = obj = fl_add_xyplot(FL_NORMAL_XYPLOT,10,10,360,270,"");
    fl_set_object_boxtype(obj,FL_DOWN_BOX);
    fl_set_object_color(obj,FL_BLACK,FL_WHITE);
    fl_set_object_lcolor(obj,FL_GREEN);
  fdui->displaywhat = obj = fl_add_choice(FL_NORMAL_CHOICE2,390,20,200,30,"");
    fl_set_choice_align(obj, FL_ALIGN_LEFT);
    fl_set_choice_entries(obj, fdchoice_displaywhat_2);
    fl_set_choice(obj,1);
    fl_set_object_callback(obj,rrccb_selectgraph,1);
  obj = fl_add_text(FL_NORMAL_TEXT,390,60,200,40,"NOTE: comparison is available only in\nthe case of single-value displays.");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->compare = obj = fl_add_lightbutton(FL_PUSH_BUTTON,390,110,120,30,"Comparison");
    fl_set_object_callback(obj,rrccb_selectgraph,-1);
  fl_end_form();

  fdui->RR_Comparisons->fdui = fdui;

  return fdui;
}
/*---------------------------------------*/

FD_RR_Designs *create_form_RR_Designs(void)
{
  FL_OBJECT *obj;
  int i;
  char val[64];

  FD_RR_Designs *fdui = (FD_RR_Designs *) fl_calloc(1, sizeof(*fdui));

  fdui->RR_Designs = fl_bgn_form(FL_NO_BOX, 610, 290);
  obj = fl_add_box(FL_FLAT_BOX,0,0,610,290,"");

  obj = fl_add_text(FL_NORMAL_TEXT,10,8,20,16,"#");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,30,8,140,16,"Design name");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,170,8,40,16,"Iron");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,210,8,40,16,"Bora");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,250,8,40,16,"Germ");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,290,8,40,16,"Res");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,330,8,50,16,"Mass");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,380,8,100,16,"Base hull");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);

  for (i = 0; i < 16; i++) {
    sprintf(val, "%d", i+1);
    obj = fl_add_text(FL_NORMAL_TEXT,10,26 + 16*i,20,16,val);
      fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
    sprintf(val, "Design name %d", i+1);
    fdui->design[i] = obj = fl_add_text(FL_NORMAL_TEXT,30,26 + 16*i,140,16,val);
      fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
    fdui->minerals[i][0] = obj = fl_add_text(FL_NORMAL_TEXT,170,26 + 16*i,40,16,"Iron");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
    fdui->minerals[i][1] = obj = fl_add_text(FL_NORMAL_TEXT,210,26 + 16*i,40,16,"Bora");
      fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
    fdui->minerals[i][2] = obj = fl_add_text(FL_NORMAL_TEXT,250,26 + 16*i,40,16,"Germ");
      fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
    fdui->resources[i] = obj = fl_add_text(FL_NORMAL_TEXT,290,26 + 16*i,40,16,"Res");
      fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
    fdui->weight[i] = obj = fl_add_text(FL_NORMAL_TEXT,330,26 + 16*i,50,16,"Mass");
      fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
    fdui->basehull[i] = obj = fl_add_text(FL_NORMAL_TEXT,380,26 + 16*i,100,16,"(base hull)");
      fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  }
  fl_end_form();

  fdui->RR_Designs->fdui = fdui;

  return fdui;
}
/*---------------------------------------*/

FD_RR_Filtering *create_form_RR_Filtering(void)
{
  FL_OBJECT *obj;
  FD_RR_Filtering *fdui = (FD_RR_Filtering *) fl_calloc(1, sizeof(*fdui));

  fdui->RR_Filtering = fl_bgn_form(FL_NO_BOX, 610, 290);
  obj = fl_add_box(FL_UP_BOX,0,0,610,290,"");
    fl_set_object_color(obj,FL_BOTTOM_BCOL,FL_COL1);
  fdui->buttons[0] = NULL;
  fdui->buttons[1] = NULL;
  fdui->buttons[2] = obj = fl_add_lightbutton(FL_PUSH_BUTTON,10,10,180,40,"Data source determination\nfor planets.");
    fl_set_object_boxtype(obj,FL_NO_BOX);
    fl_set_object_color(obj,FL_BOTTOM_BCOL,FL_WHITE);
    fl_set_object_lcolor(obj,FL_MAGENTA);
    fl_set_object_callback(obj,rrfcb_setfiltering,RLO_DATASRC);
  fdui->buttons[3] = obj = fl_add_lightbutton(FL_PUSH_BUTTON,210,150,180,40,"Numerical values for empire\ntotals simulation.");
    fl_set_object_boxtype(obj,FL_NO_BOX);
    fl_set_object_color(obj,FL_BOTTOM_BCOL,FL_WHITE);
    fl_set_object_lcolor(obj,FL_WHITE);
    fl_set_object_callback(obj,rrfcb_setfiltering,RLO_EMPIRETOT);
  fdui->buttons[4] = obj = fl_add_lightbutton(FL_PUSH_BUTTON,420,250,180,40,"Fleet duplicates resolution.");
    fl_set_object_boxtype(obj,FL_NO_BOX);
    fl_set_object_color(obj,FL_BOTTOM_BCOL,FL_WHITE);
    fl_set_object_lcolor(obj,FL_MCOL);
    fl_set_object_callback(obj,rrfcb_setfiltering,RLO_FLEETDUP);
  fdui->buttons[5] = NULL;
  fdui->buttons[6] = obj = fl_add_lightbutton(FL_PUSH_BUTTON,10,90,180,40,"Planetary queue production.");
    fl_set_object_boxtype(obj,FL_NO_BOX);
    fl_set_object_color(obj,FL_BOTTOM_BCOL,FL_WHITE);
    fl_set_object_lcolor(obj,FL_GREEN);
    fl_set_object_callback(obj,rrfcb_setfiltering,RLO_PLAQUEUE);
  fdui->buttons[7] = NULL;
  fdui->buttons[8] = obj = fl_add_lightbutton(FL_PUSH_BUTTON,210,250,180,40,"Cargo/population unloading for\nfleets reaching a planet.");
    fl_set_object_boxtype(obj,FL_NO_BOX);
    fl_set_object_color(obj,FL_BOTTOM_BCOL,FL_WHITE);
    fl_set_object_lcolor(obj,FL_LEFT_BCOL);
    fl_set_object_callback(obj,rrfcb_setfiltering,RLO_PLAFLEETS);
  fdui->buttons[9] = obj = fl_add_lightbutton(FL_PUSH_BUTTON,10,210,180,40,"Mineral shortage/analysis\nfor planet.");
    fl_set_object_boxtype(obj,FL_NO_BOX);
    fl_set_object_color(obj,FL_BOTTOM_BCOL,FL_WHITE);
    fl_set_object_lcolor(obj,FL_DARKORANGE);
    fl_set_object_callback(obj,rrfcb_setfiltering,RLO_PLAMINSTAT);
  fdui->buttons[10] = obj = fl_add_lightbutton(FL_PUSH_BUTTON,10,250,180,40,"Population analysis (growth,\nfilling, suggestions) for planet.");
    fl_set_object_boxtype(obj,FL_NO_BOX);
    fl_set_object_color(obj,FL_BOTTOM_BCOL,FL_WHITE);
    fl_set_object_lcolor(obj,FL_CYAN);
    fl_set_object_callback(obj,rrfcb_setfiltering,RLO_PLAPOPSTAT);
  fdui->buttons[11] = obj = fl_add_lightbutton(FL_PUSH_BUTTON,10,50,180,40,"Planetary initial analysis & check.");
    fl_set_object_boxtype(obj,FL_NO_BOX);
    fl_set_object_color(obj,FL_BOTTOM_BCOL,FL_WHITE);
    fl_set_object_lcolor(obj,FL_WHEAT);
    fl_set_object_callback(obj,rrfcb_setfiltering,RLO_PLANETINI);
  fdui->buttons[12] = obj = fl_add_lightbutton(FL_PUSH_BUTTON,420,10,180,40,"Guessing of fleet origin and\ndestination.");
    fl_set_object_boxtype(obj,FL_NO_BOX);
    fl_set_object_color(obj,FL_BOTTOM_BCOL,FL_WHITE);
    fl_set_object_lcolor(obj,FL_WHITE);
    fl_set_object_callback(obj,rrfcb_setfiltering,RLO_FLEETDEST);
  fdui->buttons[13] = obj = fl_add_lightbutton(FL_PUSH_BUTTON,420,50,180,40,"Fleet 'normal' transport orders\n(i.e. to owned or friendly planets).");
    fl_set_object_boxtype(obj,FL_NO_BOX);
    fl_set_object_color(obj,FL_BOTTOM_BCOL,FL_WHITE);
    fl_set_object_lcolor(obj,FL_GREEN);
    fl_set_object_callback(obj,rrfcb_setfiltering,RLO_FLEETTROK);
  fdui->buttons[14] = obj = fl_add_lightbutton(FL_PUSH_BUTTON,420,90,180,40,"Fleet 'colonization' orders\n(i.e. to uninhabited planets).");
    fl_set_object_boxtype(obj,FL_NO_BOX);
    fl_set_object_color(obj,FL_BOTTOM_BCOL,FL_WHITE);
    fl_set_object_lcolor(obj,FL_PALEGREEN);
    fl_set_object_callback(obj,rrfcb_setfiltering,RLO_FLEETCOLON);
  fdui->buttons[15] = obj = fl_add_lightbutton(FL_PUSH_BUTTON,420,130,180,40,"Fleet 'attack' orders\n(i.e. to enemy planets).");
    fl_set_object_boxtype(obj,FL_NO_BOX);
    fl_set_object_color(obj,FL_BOTTOM_BCOL,FL_WHITE);
    fl_set_object_lcolor(obj,FL_YELLOW);
    fl_set_object_callback(obj,rrfcb_setfiltering,RLO_FLEETATTK);
  fdui->buttons[16] = obj = fl_add_lightbutton(FL_PUSH_BUTTON,420,210,180,40,"Fleet name parsing internals.");
    fl_set_object_boxtype(obj,FL_NO_BOX);
    fl_set_object_color(obj,FL_BOTTOM_BCOL,FL_WHITE);
    fl_set_object_lcolor(obj,FL_DARKORANGE);
    fl_set_object_callback(obj,rrfcb_setfiltering,RLO_FLEETPARSE);
  fdui->buttons[17] = obj = fl_add_lightbutton(FL_PUSH_BUTTON,210,210,180,40,"Fleet consistency checks and\nfailed name parsing.");
    fl_set_object_boxtype(obj,FL_NO_BOX);
    fl_set_object_color(obj,FL_BOTTOM_BCOL,FL_WHITE);
    fl_set_object_lcolor(obj,FL_RED);
    fl_set_object_callback(obj,rrfcb_setfiltering,RLO_FLEETCONS);
  fdui->buttons[18] = obj = fl_add_lightbutton(FL_PUSH_BUTTON,10,170,180,40,"Current planetary production\nqueue.");
    fl_set_object_boxtype(obj,FL_NO_BOX);
    fl_set_object_color(obj,FL_BOTTOM_BCOL,FL_WHITE);
    fl_set_object_lcolor(obj,FL_TOP_BCOL);
    fl_set_object_callback(obj,rrfcb_setfiltering,RLO_PLAQUEUE);
  fdui->buttons[19] = obj = fl_add_lightbutton(FL_PUSH_BUTTON,10,130,180,40,"Autobuild objects conversions\nin planet queue.");
    fl_set_object_boxtype(obj,FL_NO_BOX);
    fl_set_object_color(obj,FL_BOTTOM_BCOL,FL_WHITE);
    fl_set_object_lcolor(obj,FL_YELLOW);
    fl_set_object_callback(obj,rrfcb_setfiltering,RLO_PLAABUILD);
  fdui->buttons[20] = obj = fl_add_lightbutton(FL_PUSH_BUTTON,420,170,180,40,"Fleet 'suspicious' orders\n(e.g. stationary freighters).");
    fl_set_object_boxtype(obj,FL_NO_BOX);
    fl_set_object_color(obj,FL_BOTTOM_BCOL,FL_WHITE);
    fl_set_object_lcolor(obj,FL_WHEAT);
    fl_set_object_callback(obj,rrfcb_setfiltering,RLO_FLEETTRBAD);
  obj = fl_add_text(FL_NORMAL_TEXT,210,10,200,90,"** NOTE **\nThe new message filtering selections\nwill apply only when windows are\nregenerated (i.e. by re-selecting\n a race or a planet).");
    fl_set_object_boxtype(obj,FL_SHADOW_BOX);
    fl_set_object_color(obj,FL_BOTTOM_BCOL,FL_TOP_BCOL);
    fl_set_object_lcolor(obj,FL_WHITE);
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  fl_end_form();

  fdui->RR_Filtering->fdui = fdui;

  return fdui;
}
/*---------------------------------------*/

FD_RR_Objects *create_form_RR_Objects(void)
{
  FL_OBJECT *obj;
  FD_RR_Objects *fdui = (FD_RR_Objects *) fl_calloc(1, sizeof(*fdui));

  fdui->RR_Objects = fl_bgn_form(FL_NO_BOX, 610, 290);
  obj = fl_add_box(FL_UP_BOX,0,0,610,290,"");
  obj = fl_add_text(FL_NORMAL_TEXT,40,250,140,20,"Terraforming");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,40,10,140,20,"Starbase design 1");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,180,10,40,20,"Iron");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,220,10,40,20,"Bora");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,260,10,40,20,"Germ");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,300,10,40,20,"Res");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,340,10,100,20,"(base hull)");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,20,10,20,20,"1");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,40,30,140,20,"Starbase design 1");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,180,30,40,20,"Iron");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,220,30,40,20,"Bora");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,260,30,40,20,"Germ");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,300,30,40,20,"Res");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,340,30,100,20,"(base hull)");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,20,30,20,20,"1");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,40,50,140,20,"Starbase design 1");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,180,50,40,20,"Iron");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,220,50,40,20,"Bora");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,260,50,40,20,"Germ");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,300,50,40,20,"Res");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,340,50,100,20,"(base hull)");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,20,50,20,20,"1");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,40,70,140,20,"Starbase design 1");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,180,70,40,20,"Iron");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,220,70,40,20,"Bora");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,260,70,40,20,"Germ");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,300,70,40,20,"Res");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,340,70,100,20,"(base hull)");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,20,70,20,20,"1");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,40,90,140,20,"Starbase design 1");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,180,90,40,20,"Iron");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,220,90,40,20,"Bora");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,260,90,40,20,"Germ");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,300,90,40,20,"Res");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,340,90,100,20,"(base hull)");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,20,90,20,20,"1");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,40,110,140,20,"Starbase design 1");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,180,110,40,20,"Iron");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,220,110,40,20,"Bora");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,260,110,40,20,"Germ");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,300,110,40,20,"Res");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,340,110,100,20,"(base hull)");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,20,110,20,20,"1");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,40,130,140,20,"Starbase design 1");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,180,130,40,20,"Iron");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,220,130,40,20,"Bora");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,260,130,40,20,"Germ");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,300,130,40,20,"Res");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,340,130,100,20,"(base hull)");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,20,130,20,20,"1");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,40,150,140,20,"Starbase design 1");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,180,150,40,20,"Iron");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,220,150,40,20,"Bora");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,260,150,40,20,"Germ");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,300,150,40,20,"Res");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,340,150,100,20,"(base hull)");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,20,150,20,20,"1");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,40,190,140,20,"Factory");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,180,190,40,20,"Iron");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,220,190,40,20,"Bora");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,260,190,40,20,"Germ");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,300,190,40,20,"Res");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,40,210,140,20,"Mine");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,180,210,40,20,"Iron");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,220,210,40,20,"Bora");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,260,210,40,20,"Germ");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,300,210,40,20,"Res");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,40,230,140,20,"Defense");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,180,230,40,20,"Iron");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,220,230,40,20,"Bora");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,260,230,40,20,"Germ");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,300,230,40,20,"Res");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,180,250,40,20,"Iron");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,220,250,40,20,"Bora");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,260,250,40,20,"Germ");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  obj = fl_add_text(FL_NORMAL_TEXT,300,250,40,20,"Res");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fl_end_form();

  fdui->RR_Objects->fdui = fdui;

  return fdui;
}
/*---------------------------------------*/


/* Form definition file generated with fdesign. */

extern "C" {
#include "forms.h"
}
#include <stdlib.h>
#include "pfunc.h"

static FL_PUP_ENTRY fdchoice_0[] =
{ 
    /*  itemtext   callback  shortcut   mode */
    { "skip",	0,	"",	 FL_PUP_NONE},
    { "stomp",	0,	"",	 FL_PUP_NONE},
    { "and",	0,	"",	 FL_PUP_NONE},
    { "or",	0,	"",	 FL_PUP_NONE},
    {0}
};

FD_PlanetaryFunction *create_form_PlanetaryFunction(void)
{
  FL_OBJECT *obj;
  FD_PlanetaryFunction *fdui = (FD_PlanetaryFunction *) fl_calloc(1, sizeof(*fdui));

  int oldbw = fl_get_border_width();
  fl_set_border_width(2);

  fdui->PlanetaryFunction = fl_bgn_form(FL_NO_BOX, 320, 290);
  obj = fl_add_box(FL_UP_BOX,0,0,320,290,"");
  fdui->description = obj = fl_add_text(FL_NORMAL_TEXT,10,40,300,70,"Text");
    fl_set_object_lalign(obj,FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
  fdui->input_par[0] = obj = fl_add_input(FL_INT_INPUT,160,140,70,20,"Input");
  fdui->input_par[1] = obj = fl_add_input(FL_INT_INPUT,160,160,70,20,"Input");
  fdui->input_par[2] = obj = fl_add_input(FL_INT_INPUT,160,180,70,20,"Input");
  fdui->input_par[3] = obj = fl_add_input(FL_INT_INPUT,160,200,70,20,"Input");
  fdui->input_par[4] = obj = fl_add_input(FL_INT_INPUT,160,220,70,20,"Input");
  fdui->mask_circles = obj = fl_add_button(FL_PUSH_BUTTON,120,110,30,20,"C");
  fdui->mask_lines = obj = fl_add_button(FL_PUSH_BUTTON,150,110,30,20,"L");
  fdui->mask_data = obj = fl_add_button(FL_PUSH_BUTTON,180,110,30,20,"D");
  fdui->mask_marker = obj = fl_add_button(FL_PUSH_BUTTON,210,110,30,20,"M");
  fdui->mask_name = obj = fl_add_button(FL_PUSH_BUTTON,240,110,30,20,"N");
  fdui->mask_flag = obj = fl_add_button(FL_PUSH_BUTTON,270,110,30,20,"F");

  fdui->mode = obj = fl_add_choice(FL_NORMAL_CHOICE2,10,110,90,20,"");
    fl_set_object_boxtype(obj,FL_FRAME_BOX);
    fl_set_choice_entries(obj, fdchoice_0);
    fl_set_choice(obj,1);
  fdui->number = obj = fl_add_menu(FL_PUSH_MENU,10,10,30,30,"1");
    fl_set_object_boxtype(obj,FL_FRAME_BOX);
    fl_set_object_lsize(obj,FL_MEDIUM_SIZE);
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
    fl_set_object_callback(obj,pfecb_number,0);
  obj = fl_add_button(FL_NORMAL_BUTTON,280,210,30,30,"@2");
    fl_set_object_callback(obj,pfecb_accept_and_next,0);
  obj = fl_add_button(FL_NORMAL_BUTTON,240,210,30,30,"@8");
    fl_set_object_callback(obj,pfecb_accept_and_prev,0);
  obj = fl_add_button(FL_NORMAL_BUTTON,240,180,70,20,"Delete");
    fl_set_object_callback(obj,pfecb_delete,0);
  obj = fl_add_button(FL_NORMAL_BUTTON,240,150,70,20,"Insert");
    fl_set_object_callback(obj,pfecb_insert,0);
  obj = fl_add_button(FL_NORMAL_BUTTON,100,250,80,30,"Apply");
    fl_set_object_callback(obj,pfecb_apply,0);
  obj = fl_add_button(FL_NORMAL_BUTTON,10,250,80,30,"Cancel");
    fl_set_object_callback(obj,pfecb_cancel,0);
  obj = fl_add_button(FL_NORMAL_BUTTON,230,250,80,30,"Close");
    fl_set_object_callback(obj,pfecb_close,0);
  fdui->selected = obj = fl_add_menu(FL_PULLDOWN_MENU,40,10,270,30,"Select a PFunction");
    fl_set_object_boxtype(obj,FL_FRAME_BOX);
    fl_set_object_lsize(obj,FL_MEDIUM_SIZE);
    fl_set_object_callback(obj,pfecb_selected,0);
  fl_end_form();
  fl_set_border_width(oldbw);

  fdui->PlanetaryFunction->fdui = fdui;

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
  obj = fl_add_text(FL_NORMAL_TEXT,320,10,60,30,"Planet\nViews");
    fl_set_object_lalign(obj,FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
  obj = fl_add_frame(FL_ENGRAVED_FRAME,5,5,305,160,"");
  obj = fl_add_frame(FL_ENGRAVED_FRAME,310,5,80,160,"");
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
  fdui->ffeditor = obj = fl_add_button(FL_PUSH_BUTTON,400,10,60,50,"Display\nFleets");
  obj = fl_add_button(FL_NORMAL_BUTTON,400,70,60,50,"<future>");
  fdui->pfeditor = obj = fl_add_button(FL_NORMAL_BUTTON,320,90,60,30,"Editor");
    fl_set_object_callback(obj,mccb_pfeditorwindow,0);
  fdui->pflist = obj = fl_add_button(FL_NORMAL_BUTTON,320,50,60,30,"List");
    fl_set_object_callback(obj,mccb_pflistwindow,0);
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
  fdui->gravitydial = obj = fl_add_free(FL_INACTIVE_FREE,20,375,390,20,"",
			freeobj_gravitydial_handle);
  fdui->tempdial = obj = fl_add_free(FL_INACTIVE_FREE,20,395,390,20,"",
			freeobj_termpdial_handle);
  fdui->raddial = obj = fl_add_free(FL_INACTIVE_FREE,20,415,390,20,"",
			freeobj_raddial_handle);
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
  fdui->minscale = obj = fl_add_choice(FL_NORMAL_CHOICE2,20,240,110,20,"");
    fl_set_object_boxtype(obj,FL_FRAME_BOX);
    fl_set_object_callback(obj,pscb_setminscale,0);
  fdui->testobject = obj = fl_add_choice(FL_NORMAL_CHOICE2,140,240,110,20,"");
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

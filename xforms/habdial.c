#include "habdial.h"
#include <malloc.h>
// for abs, sign, etc.
#include "../src/starana-const.h"

/* new control for the XForms toolkit */

typedef struct {
  int current;
  int original;
  int tform;
  int maxtform;
  int habmin;
  int habmax;
} habdial_private;


static
int handle_habdial(FL_OBJECT* obj, int event, 
		   FL_Coord mx, FL_Coord my, int key, void* xev);


FL_OBJECT* fl_create_habdial(int type, FL_Coord x, FL_Coord y, 
			     FL_Coord w, FL_Coord h, const char* label)
{
  FL_OBJECT* ob;

  ob = fl_make_object(FL_HABDIAL, type, x, y, w, h, label, handle_habdial);

  /* allocate private data */
  ob->spec = fl_calloc(1, sizeof(habdial_private));

  return ob;
}


FL_OBJECT* fl_add_habdial(int type, FL_Coord x, FL_Coord y, 
			  FL_Coord w, FL_Coord h, const char* label)
{
  FL_OBJECT* ob;

  ob = fl_create_habdial(type, x, y, w, h, label);
  fl_add_object(fl_current_form, ob);

  return ob;
}


void fl_set_habdial(FL_OBJECT* ob, const int habmin, const int habmax,
		    const int current, const int original, 
		    const int tform, const int maxtform)
{
  /* do some sanity check? */
  habdial_private* hd = (habdial_private*)ob->spec;

  hd->habmin  = habmin;
  hd->habmax  = habmax;
  hd->current = current;
  hd->original= original;
  hd->tform   = tform;
  hd->maxtform= maxtform;

  fl_redraw_object(ob);
}


static
int handle_habdial(FL_OBJECT* ob, int event, 
		   FL_Coord mx, FL_Coord my, int key, void* xev)
{
  int width = ob->w - 2;
  int hahe = ob->h / 2;
  int xmin, xmax;
  int habcenter, habhwidth;
  const habdial_private* environment = (habdial_private*)ob->spec;
  GC gc = fl_state[fl_get_vclass()].gc[0];

  switch(event) {
  case FL_DRAW:
    XSetLineAttributes(fl_get_display(),gc,1,LineSolid,CapProjecting,JoinRound);

    // immune -> all green
    if (environment->habmin == -1) {
      fl_rectf(ob->x, ob->y+1, ob->w, ob->h-2, FL_GREEN);

    } else {
      habcenter = (environment->habmax + environment->habmin) / 2;
      habhwidth = (environment->habmax - environment->habmin) / 2;

      fl_rectf(ob->x, ob->y+1, ob->w, ob->h-2, FL_RED);

      // yellow band
      if (environment->tform != 0) {
	xmin = environment->habmin - environment->tform;
	xmax = environment->habmax + environment->tform;
	if (xmin < 0)
	  xmin = 0;
	if (xmax > 100)
	  xmax = 100;

	xmin = (xmin*width + width/2)/100;
	xmax = (xmax*width + width/2)/100;

	fl_rectf(ob->x+xmin, ob->y+1, xmax-xmin, ob->h-2, FL_YELLOW);
      }

      // green band
      xmin = environment->habmin;
      xmax = environment->habmax;

      xmin = (xmin*width + width/2)/100;
      xmax = (xmax*width + width/2)/100;

      fl_rectf(ob->x+xmin, ob->y+1, xmax-xmin, ob->h-2, FL_PALEGREEN);

      // inner green band
      xmin = habcenter - habhwidth/2;
      xmax = habcenter + habhwidth/2;

      xmin = (xmin*width + width/2)/100;
      xmax = (xmax*width + width/2)/100;

      fl_rectf(ob->x+xmin, ob->y+1, xmax-xmin, ob->h-2, FL_GREEN);
    }

    if (environment->original > 0) {
      // put black markers for current/original
      fl_linewidth(1);
      fl_linestyle(LineSolid);

      // current
      xmin = environment->current;
      xmin = (xmin*width + width/2)/100;
      fl_line(ob->x+xmin+4, ob->y+hahe, ob->x+xmin, ob->y+hahe+4, FL_BLACK);
      fl_line(ob->x+xmin, ob->y+hahe+4, ob->x+xmin-4, ob->y+hahe, FL_BLACK);
      fl_line(ob->x+xmin-4, ob->y+hahe, ob->x+xmin, ob->y+hahe-4, FL_BLACK);
      fl_line(ob->x+xmin, ob->y+hahe-4, ob->x+xmin+4, ob->y+hahe, FL_BLACK);

      // original
      xmin = environment->original;
      xmin = (xmin*width + width/2)/100;
      fl_line(ob->x+xmin, ob->y+hahe-7, ob->x+xmin, ob->y+hahe+7, FL_BLACK);

      // draw line from current to original+tform
      if (environment->habmin >= 0) {
	xmax = habcenter - environment->original;
	if (abs(xmax) > environment->tform)
	  xmax = sign(xmax) * environment->tform;

	xmax += environment->original;
	xmin = environment->current;

	xmin = (xmin*width + width/2)/100;
	xmax = (xmax*width + width/2)/100;

	fl_line(ob->x+xmin, ob->y+hahe, ob->x+xmax, ob->y+hahe, FL_BLACK);
      }

      // mark maxtform point
      if (environment->habmin >= 0) {
	xmax = habcenter - environment->original;
	if (abs(xmax) > environment->maxtform)
	  xmax = sign(xmax) * environment->maxtform;

	xmax += environment->original;
	xmax = (xmax*width + width/2)/100;

	fl_line(ob->x+xmax, ob->y+hahe-2, ob->x+xmax, ob->y+hahe+3, FL_BLACK);
      }
    }
    break;

  case FL_FREEMEM:
    fl_free(ob->spec);
    break;

    /* ignored events */
  case FL_DRAWLABEL:
  case FL_ENTER:
  case FL_LEAVE:
  case FL_MOTION:
  case FL_PUSH:
  case FL_RELEASE:
  case FL_MOUSE:
  case FL_FOCUS:
  case FL_STEP:
  case FL_SHORTCUT:
  case FL_OTHER:
    break;
  }

  return 0;
}

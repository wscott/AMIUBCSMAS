#include <forms.h>

#define FL_HABDIAL 1001

#define FL_HABNORMAL 0

FL_OBJECT* fl_create_habdial(int type, FL_Coord x, FL_Coord y, FL_Coord w, FL_Coord h, const char* label);
FL_OBJECT* fl_add_habdial(int type, FL_Coord x, FL_Coord y, FL_Coord w, FL_Coord h, const char* label);
void fl_set_habdial(FL_OBJECT* ob, const int habmin, const int habmax, const int current, const int original, const int tform, const int maxtform);

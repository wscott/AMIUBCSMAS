
#include "starana-classes.h"


// habitability display (stars-like)

class pla_stars_habitab : public planetary_function {
public:
  pla_stars_habitab(void)
  {
    _name = "Habitability - Stars!";
    _type = "Habitability";
    _desc = "This function works like the planet habitability display in Stars!\nfor the requested race.\n[0] use 0 to indicate the current viewpoint.";
    _pardesc[0] = "Race";
  }
  
  virtual void function(map_view& mw, planet* p, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = p->disp;

    // we can do something if we have the data
    if (!p->data_available())
      return;

    // we also need this
    race* rvw;

    if (par[0])
      rvw = mw.get_map()->find_race(par[0] - 1);
    else
      rvw = mw.viewpoint();
    
    if (!rvw)
      return;

    int hab = p->hab_now(rvw, when);
    int mxhab = p->hab_when_max_terraformed(rvw, when);

    // can't do the display!
    if (hab == -100 || mxhab == -100)
      return;

    if (mxhab <= 0) {
      d.vmin = 0;
      d.vmax = 60;
      d.values[0].value = -hab;
      d.values[0].color = COL_REDHAB;

    } else if (mxhab > 0 && hab < 0) {
      d.vmin = 0;
      d.vmax = 100;
      d.values[0].value = mxhab;
      d.values[0].color = COL_YELLOWHAB;

    } else {
      d.vmin = 0;
      d.vmax = 100;
      d.values[0].value = hab;
      d.values[0].color = COL_GREENHAB;
    }

    d.n_values = 1;
    d.flag = true;
  }
};

pla_stars_habitab pla_stars_habitab_proto;



// habitability display (current)

class pla_habitab_now : public planetary_function {
public:
  pla_habitab_now(void)
  {
    _name = "Habitability - now";
    _type = "Habitability";
    _desc = "This function displays the current habitability value of the\nplanet (i.e. no yellows) for the requested race.\n[0] use 0 to indicate the current viewpoint.";
    _pardesc[0] = "Race";
  }
  
  virtual void function(map_view& mw, planet* p, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = p->disp;

    // we can do something if we have the data
    if (!p->data_available())
      return;

    // we also need this
    race* rvw;

    if (par[0])
      rvw = mw.get_map()->find_race(par[0] - 1);
    else
      rvw = mw.viewpoint();
    
    if (!rvw)
      return;

    int hab = p->hab_now(rvw, when);

    // can't do the display!
    if (hab == -100)
      return;

    if (hab < 0) {
      d.vmin = 0;
      d.vmax = 60;
      d.values[0].value = -hab;
      d.values[0].color = COL_REDHAB;

    } else {
      d.vmin = 0;
      d.vmax = 100;
      d.values[0].value = hab;
      d.values[0].color = COL_GREENHAB;
    }

    d.n_values = 1;
    d.flag = true;
  }
};

pla_habitab_now pla_habitab_now_proto;



// habitability display (when max terraformed)

class pla_habitab_tform : public planetary_function {
public:
  pla_habitab_tform(void)
  {
    _name = "Habitability - terraformed";
    _type = "Habitability";
    _desc = "This function displays the maximum habitability value of the\nplanet (max terraforming) for the current race viewpoint.[0] use 0 to indicate the current viewpoint.\n[5,6,7] use 0 to indicate the race's own ability.";
    _pardesc[0] = "Race";
    _pardesc[5] = "Gravity";
    _pardesc[6] = "Tempreature";
    _pardesc[7] = "Radiation";
  }
  
  virtual void function(map_view& mw, planet* p, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = p->disp;

    // we can do something if we have the data
    if (!p->data_available())
      return;

    // we also need this
    race* rvw;
    int i;

    if (par[0])
      rvw = mw.get_map()->find_race(par[0] - 1);
    else
      rvw = mw.viewpoint();
    
    if (!rvw)
      return;

    // override race's tforming tech
    int tf_tech[3];

    for (i = 0; i < 3; i++)
      if (par[i+5])
	tf_tech[i] = par[i+5];
      else
	tf_tech[i] = rvw->terraform_tech(0)[i];

    int mxhab = p->hab_when_max_terraformed(mw.viewpoint(), when, tf_tech);

    // can't do the display!
    if (mxhab == -100)
      return;

    if (mxhab <= 0) {
      d.vmin = 0;
      d.vmax = 60;
      d.values[0].value = -mxhab;
      d.values[0].color = COL_REDHAB;

    } else {
      d.vmin = 0;
      d.vmax = 100;
      d.values[0].value = mxhab;
      d.values[0].color = COL_GREENHAB;
    }

    d.n_values = 1;
    d.flag = true;
  }
};

pla_habitab_tform pla_habitab_tform_proto;



// habitability display (global)

class pla_global_hab : public planetary_function {
public:
  pla_global_hab(void)
  {
    _name = "Habitability - 'global'";
    _type = "Habitability";
    _desc = "This function generates a pie for the planet with a radius based\non the maximum of the habitability for the various races. For all\nthe races with a positive habitability a slice is drawn, with an\nangle proportional to the race habitability value.";
  }

  virtual void function(map_view& mw, planet* p, const int* par, const int when)
  {
    int i;
    int someone = 0;

    // let's create a nice alias
    object_display& d = p->disp;

    // we can do something if we have the data
    if (!p->data_available())
      return;

    d.vmin = 0;
    d.vmax = 100;

    for (i = 0; i < mw.get_map()->number_of_players(); i++) {
      if (mw.set_alliances(MW_READ))
	if (!mw.get_map()->are_allies(mw.viewpoint(), mw.get_map()->find_race(i)))
	  continue;

      if ( (d.values[someone].value = p->hab_now(mw.get_map()->find_race(i), when)) > 0) {
	d.values[someone].color = COL_RACES + 4 * i;
	someone++;
      }
    }

    if (someone) {
      d.n_values = someone;
      d.flag = true;
    }
  }
};

pla_global_hab pla_global_hab_proto;



// habitability display (global w/max tform)

class pla_global_tformed : public planetary_function {
public:
  pla_global_tformed(void)
  {
    _name = "Habitability 'global' tformed.";
    _type = "Habitability";
    _desc = "This function generates a pie for the planet with a radius based\non the maximum of the maximum possible habitability for the\nvarious races. For all the races with a positive habitability a slice\nis drawn, with an angle proportional to the race habitability value.\n[5,6,7] use 0 to indicate the race's own ability.";
    _pardesc[5] = "Gravity";
    _pardesc[6] = "Tempreature";
    _pardesc[7] = "Radiation";
  }

  virtual void function(map_view& mw, planet* p, const int* par, const int when)
  {
    int i, j;
    int someone = 0;

    // let's create a nice alias
    object_display& d = p->disp;

    // we can do something if we have the data
    if (!p->data_available())
      return;

    d.vmin = 0;
    d.vmax = 100;

    // override race's tforming tech
    int tf_tech[3];
    race* rvw;

    for (i = 0; i < mw.get_map()->number_of_players(); i++) {
      if (mw.set_alliances(MW_READ))
	if (!mw.get_map()->are_allies(mw.viewpoint(), mw.get_map()->find_race(i)))
	  continue;

      rvw = mw.get_map()->find_race(i);

      for (j = 0; j < 3; j++)
	if (par[j+5])
	  tf_tech[j] = par[j+5];
	else
	  tf_tech[j] = rvw->terraform_tech(0)[j];

      if ( (d.values[someone].value = p->hab_when_max_terraformed(rvw, when, tf_tech)) > 0 ) {
	d.values[someone].color = COL_RACES + 4 * i;
	someone++;
      }
    }

    if (someone) {
      d.n_values = someone;
      d.flag = true;
    }
  }
};

pla_global_tformed pla_global_tformed_proto;



// filter on current hab value

class pla_F_habnowkill : public planetary_function {
public:
  pla_F_habnowkill(void)
  {
    _name = "Filter: habitability now";
    _type = "Habitability";
    _desc = "Filters planets depending on their current habitability value.\n[0] use 0 for the current viewpoint.";
    _pardesc[0] = "Race";
    _pardesc[1] = "Fields affect mask";
    _pardesc[2] = "Negate filter";
    _pardesc[3] = "Min value %";
    _pardesc[4] = "Max value %";
  }
  
  virtual void function(map_view& mw, planet* p, const int* par, const int when)
  {
    // let's create a nice alias
    object_display& d = p->disp;

    bool f = false;

    // we can do something if we have the data
    if (p->data_available()) {
      race* rvw;

      if (par[0])
	rvw = mw.get_map()->find_race(par[0] - 1);
      else
	rvw = mw.viewpoint();
    
      if (rvw) {
	int hab = p->hab_now(rvw, when);

	// can't do anything
	if (hab != -100) {
	  // check the value
	  f = (par[3] <= par[4] && hab >= par[3] && hab <= par[4]) ||
	    (par[3] > par[4] && (hab >= par[3] || hab <= par[4]));
	}
      }
    }

    if (par[2])
      f = !f;

    if (par[1]) {
      if (f)
	d.reset_something(par[1]);
    } else
      d.flag = f;
  }
};

pla_F_habnowkill pla_F_habnowkill_proto;

/*
  Zajal - Creative coding platform 
  Copyright (C) 2010 Ramsey Nasser
  
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*  Ruby openFrameworks bindings */

#ifndef ZAJAL_H
#define ZAJAL_H

#ifdef __cplusplus
 extern "C" {
#endif

/*  http://fonlake.blogspot.com/2009/07/cruby.html */
#define RB_FUNC(f) reinterpret_cast <VALUE (*)(...)>(f) 

/* app */
extern VALUE zj_mApp;

/* events */
extern VALUE zj_mEvents;

/* graphics */
extern VALUE zj_mGraphics;
void zj_graphics_reset_frame();
int zj_graphics_make_color(int argc, VALUE* argv, int* r, int* g, int* b, int* a);

/* images */
extern VALUE zj_mImages;

/* mathematics */
extern VALUE zj_mMathematics;

/* version */
extern VALUE zj_mVersion;

/* zajal */
extern VALUE zj_mZajal;
extern VALUE zj_cContext;

void zajal_init();

#ifdef __cplusplus
}
#endif

#endif /* ZAJAL_H */


/*
 * ==========================================================================
 *
 *       Filename:  halverson.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/12/21 21:47:15
 *       Revision:  none
 *       Compiler:  cgcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef __HALVERSON_H__
#define __HALVERSON_H__
#include <X11/Xlib.h> // Every Xlib program must include this
#include <assert.h>   // I include this to test return values the lazy way
#include <unistd.h>   // So we got the profile for 10 seconds
#include <stdio.h>    // This has the keyboard and file IO functions
#include <math.h>     // sine, cosine and various math functions
#include <stdbool.h>  // Defines true, false
#include <time.h>     // I will use the time to "seed" the random function
#include <stdlib.h>   // I need this because it has the random functions
#include <stdint.h>
#include <string.h>

#define NIL (0)       // A name for the void pointer

#define window_width 800
#define window_height 600

#define origin_x 400
#define origin_y 300


class halverson 
{
public:
    halverson (Display *cdpy, Window cwin, GC cgc); // constructor

    void display_owner_info (Display *cdpy, Window cwin, GC cgc,
                                                  int width, int height);
    double rand_range (double fMin, double fMax);
    int home ();
    int gotoxy (double new_x, double new_y, Display *cdpy, Window w, GC cgc);
    int forward(double distance, Display *cdpy, Window w, GC cgc);
    int right(double angle);
    int left(double angle);
    int get_pen(XColor desired_col, Display *cdpy, GC cgc);
    int pen_up();
    int pen_down();
    int get_pen_n(int pen_number, Display *cdpy, GC cgc);
    int branch(int depth, Display *cdpy, Window w, GC cgc);

    ~halverson ();          // destructor

protected:
    double turtle_x; 
    double turtle_y; 
    double turtle_heading;  //heading is in degrees.  zero is to the right.
    bool   turtle_pen_active = true;
    
    Display *cdpy;
    Window  cwin;
    GC      cgc;
};


/* 
 * ===  FUNCTION  ====================================================
 *         Name:  halverson::halverson (Display *cdpy, Window cwin, GC cgc)
 *  Description:  A constructor initialised here
 * ===================================================================
 */
halverson::halverson (Display *dpy, Window win, GC gc)
{
    cdpy = dpy;
    cwin = win;
    cgc  = gc;
}/* -----  end of function halverson::halverson (Display, Window, GC)  ----- */

/* 
 * ===  FUNCTION  ====================================================
 *         Name:  halverson::~halverson ()
 *  Description:  A default destructor
 * ===================================================================
 */
halverson::~halverson ()
{

}	/* -----  end of function halverson::~halverson ()  ----- */

double halverson::rand_range(double fMin, double fMax) {
    double f = (double)rand() / RAND_MAX;

    return fMin + f * (fMax - fMin);
}

/*
 * ===  FUNCTION  ====================================================
 *         Name:  display_owner_info (Display *cdpy, Window cwin, GC cgc,
 *                                  uint32_t width, uint32_t height)
 *  Description:  Display owner's info and copyrights etc.
 * ===================================================================
 */
    void
halverson::display_owner_info (Display *cdpy, Window cwin, GC cgc,
                        int width, int height)
{
    uint32_t x_offset, y_offset;
    char     *s =(char*)"Copyrights (C) by Peter G. Halverson, PhD.";
    char     *s1=(char*)"Designed & Developed by Peter G. Halverson";
    x_offset = 0;
    y_offset = 580;

    XDrawString (cdpy, cwin, cgc, x_offset, y_offset, (char*)s, strlen (s));
    y_offset += 20;
    XDrawString (cdpy, cwin, cgc, x_offset, y_offset, (char*)s1, strlen (s1));

}/* end of display_owner_info (Display *, Window, GC, uint32_t, uint32_t ) */

int halverson::home() {
  turtle_x=0.0;
  turtle_y=0.0;
  turtle_heading=0.0;

  return(0);
}

int halverson::gotoxy (double new_x, double new_y, 
                        Display *cdpy, Window cwin, GC cgc)
{
  int x1 = turtle_x + origin_x;
  int y1 = window_height - (turtle_y + origin_y);
  int x2 = new_x + origin_x;
  int y2 = window_height - (new_y + origin_y);

  if (turtle_pen_active)
      XDrawLine(cdpy, cwin, cgc, x1, y1, x2, y2);// Draw theline

  turtle_x = new_x;
  turtle_y = new_y;

  return(0);
}

int halverson::forward(double distance, Display *cdpy, Window cwin, GC cgc)
{
  double new_x = turtle_x + distance * cos(turtle_heading * M_PI/180.0);
  double new_y = turtle_y + distance * sin(turtle_heading * M_PI/180.0);

  int x1 = turtle_x + origin_x;
  int y1 = window_height - (turtle_y+origin_y);
  int x2 = new_x + origin_x;
  int y2 = window_height - (new_y+origin_y);

  if (turtle_pen_active)
      XDrawLine(cdpy, cwin, cgc, x1, y1, x2, y2); // Draw theline

  turtle_x = new_x;
  turtle_y = new_y;
  return(0);
}

int halverson::right(double angle) { 
    turtle_heading = turtle_heading-angle; return (0); }
int halverson::left(double angle)  { 
    turtle_heading = turtle_heading+angle; return (0); }

int halverson::get_pen(XColor desired_col, Display *cdpy, GC cgc) {
  XSetForeground(cdpy,
          cgc,
          desired_col.pixel); // Tell the GC we draw using the desired color

  return(0);
}

int halverson::pen_up()   { turtle_pen_active = false; return(0); }
int halverson::pen_down() { turtle_pen_active = true; return(0);  }

int halverson::get_pen_n(int pen_number, Display *cdpy, GC cgc) {
    XColor black_col,
            white_col,
            red_col,
            green_col,
            blue_col,
            yellow_col,
            magenta_col,
            cyan_col;

  switch (pen_number) {
    case 0: get_pen (black_col, cdpy, cgc);   break;
    case 1: get_pen (blue_col, cdpy, cgc);    break;
    case 2: get_pen (green_col, cdpy, cgc);   break;
    case 3: get_pen (cyan_col, cdpy, cgc);    break;
    case 4: get_pen (red_col, cdpy, cgc);     break;
    case 5: get_pen (magenta_col, cdpy, cgc); break;
    case 6: get_pen (yellow_col, cdpy, cgc);  break;
    case 7: get_pen (white_col, cdpy, cgc);   break;
  }
  return(0);
}

int halverson::branch(int depth, Display *cdpy, Window cwin, GC cgc) {
        // This is a RECURSIVE dunction that will make a FRACTAL
  double branch_length,
         branch_angle;

  //printf("depth=%d\n",depth);

  if (depth > 10) return(0);    // The is the recursion ESCAPE route.
                                // Without it the program crashes.
  depth++;
  get_pen_n (depth % 6 + 1, cdpy, cgc);

  branch_length = rand_range (100,300) / depth;
  branch_angle  = rand_range (1,25);

  left (branch_angle);

  forward (branch_length, cdpy, cwin, cgc);

  branch (depth, cdpy, cwin, cgc);  // branch is going to branch!  How weird!

  forward (-branch_length, cdpy, cwin, cgc);

  right (branch_angle);

  branch_length = rand_range(100,300)/depth;

  branch_angle = rand_range(1,25);

  right (branch_angle);

  forward (branch_length, cdpy, cwin, cgc);

  branch(depth, cdpy, cwin, cgc); //branch will branch again!  Weirder!

  forward (-branch_length, cdpy, cwin, cgc);

  left (branch_angle);

  get_pen_n ((depth-1)%6+1, cdpy, cgc);

  return(0);
}
#endif

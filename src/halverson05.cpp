/*
 * ========================================================================
 *
 *       Filename:  halverson05.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  27/11/21 20:32:34
 *       Revision:  none
 *       Compiler: gcc -Wall -W -Werror turtle_tree2.c -o turtle_tree2 -lX11
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 *   https://halverscience.net/c_programming/c_graphics_xwindows/c_graphics_xwindows.html
 * =========================================================================
 */
//==========================================================================
//
//  turtle_tree2.c
//  ==============
//
//  This example introduces RECURSION. This means that a function calls itself.
//
//  Imagine you could instantly create a copy of yourself.  
//
//  You could tell copy 1 to do your math homework
//  and copy 2 to do your english homework.
//  Then copy 1 copies itself.  It tells copy 1-1 to do all the even 
//  math problems and copy 1-2 to do all the
//  odd math problems and on and on.
//  Soon you have hundreds of copies of yourself and the homework gets 
//  done really really fast!   Wow!
//
//  In this example, "branch" draws a couple sticks.  
//  But it wants more sticks at the end of each stick.
//  So it copies itself and each copy draws more sticks!  
//
//  You'll see...
//  Compile command:  It must use C++ because the x-window graphics 
//  library is in C++
//
//  g++ -Wall -W -Werror turtle_tree2.c -o turtle_tree2 -lX11
//
//  After successful compile and build, this is the command to run it:
//
//  ("./turtle_tree2" means "here". Linux runs whatever it finds.)
//
//=========================================================================

#include <iostream>

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

#include "halverson.h"
#include "common.h"

#define _TEST_

halverson* halv;

/*  
#define NIL (0)       // A name for the void pointer
  
#define window_width 800
#define window_height 600

#define origin_x 400
#define origin_y 300
*/

/* 
 * ===  FUNCTION  ====================================================
 *         Name:  display_owner_info (Display *dpy, Window win, GC gc,
 *                                  uint32_t width, uint32_t height)
 *  Description:  Display owner's info and copyrights etc.
 * ===================================================================
 */
/*      void
display_owner_info (Display *dpy, Window win, GC gc,
                        uint32_t width, uint32_t height) 
{
    uint32_t x_offset, y_offset;
    char     *s =(char*)"Copyrights (C) by Peter G. Halverson, PhD.";
    char     *s1=(char*)"Designed & Developed by Peter G. Halverson";
    x_offset = 0;
    y_offset = 580;

    XDrawString (dpy, win, gc, x_offset, y_offset, (char*)s, strlen (s));
    y_offset += 20;
    XDrawString (dpy, win, gc, x_offset, y_offset, (char*)s1, strlen (s1));

} end of display_owner_info (Display *, Window, GC, uint32_t, uint32_t ) 

double rand_range(double fMin, double fMax) {
    double f = (double)rand() / RAND_MAX;

    return fMin + f * (fMax - fMin);
}

int home() {
  turtle_x=0.0; 
  turtle_y=0.0; 
  turtle_heading=0.0;

  return(0);
}

int gotoxy (double new_x, double new_y, Display *dpy, Window w, GC gc)   
{
  int x1 = turtle_x + origin_x;
  int y1 = window_height - (turtle_y + origin_y);
  int x2 = new_x + origin_x;
  int y2 = window_height - (new_y + origin_y);

  if (turtle_pen_active) 
      XDrawLine(dpy, w, gc, x1, y1, x2, y2);// Draw theline

  turtle_x = new_x;
  turtle_y = new_y;

  return(0);
}

int forward(double distance, Display *dpy, Window w, GC gc) 
{
  double new_x = turtle_x + distance * cos(turtle_heading * M_PI/180.0);
  double new_y = turtle_y + distance * sin(turtle_heading * M_PI/180.0);

  int x1 = turtle_x + origin_x;
  int y1 = window_height - (turtle_y+origin_y);
  int x2 = new_x + origin_x;
  int y2 = window_height - (new_y+origin_y);

  if (turtle_pen_active) 
      XDrawLine(dpy, w, gc, x1, y1, x2, y2); // Draw theline

  turtle_x = new_x;
  turtle_y = new_y;
  return(0);
}

int right(double angle) { turtle_heading = turtle_heading-angle; return (0); }
int left(double angle)  { turtle_heading = turtle_heading+angle; return (0); }


int get_pen(XColor desired_col, Display *dpy, GC gc) {
  XSetForeground(dpy, 
          gc, 
          desired_col.pixel); // Tell the GC we draw using the desired color

  return(0);
}
  
int get_pen_n(int pen_number, Display *dpy, GC gc) {
    XColor black_col,
            white_col,
            red_col,
            green_col,
            blue_col,
            yellow_col,
            magenta_col,
            cyan_col;

  switch (pen_number) {
    case 0: get_pen (black_col, dpy, gc);   break;
    case 1: get_pen (blue_col, dpy, gc);    break;
    case 2: get_pen (green_col, dpy, gc);   break;
    case 3: get_pen (cyan_col, dpy, gc);    break;
    case 4: get_pen (red_col, dpy, gc);     break;
    case 5: get_pen (magenta_col, dpy, gc); break;
    case 6: get_pen (yellow_col, dpy, gc);  break;
    case 7: get_pen (white_col, dpy, gc);   break;
  }
  return(0);
}

int pen_up()   { turtle_pen_active = false; return(0); }
int pen_down() { turtle_pen_active = true; return(0);  }

//=======================================================================

int branch(int depth, Display *dpy, Window w, GC gc) {
        // This is a RECURSIVE dunction that will make a FRACTAL
  double branch_length, 
         branch_angle;

  //printf("depth=%d\n",depth);

  if (depth > 10) return(0);    // The is the recursion ESCAPE route. 
                                // Without it the program crashes.
  depth++;
  get_pen_n (depth % 6 + 1, dpy, gc);

  branch_length = rand_range (100,300) / depth;
  branch_angle  = rand_range (1,25);

  left (branch_angle); 
  forward (branch_length, dpy, w, gc);

  branch (depth, dpy, w, gc);  // branch is going to branch!  How weird!

  //usleep(100000); 
  //XFlush(dpy); //Optional: use this to see the lines being drawn, one-by-one
  
  forward (-branch_length, dpy, w, gc);

  right (branch_angle);

  branch_length = rand_range(100,300)/depth;

  branch_angle = rand_range(1,25);

  right (branch_angle); 

  forward (branch_length, dpy, w, gc); 

  branch(depth, dpy, w, gc); //branch will branch again!  Weirder!

  //usleep(100000); 
  //XFlush(dpy); //Optional: use this to see the lines being drawn, one-by-one

  forward (-branch_length, dpy, w, gc);

  left (branch_angle);

  get_pen_n ((depth-1)%6+1, dpy, gc);

  return(0);
} */

//=========================================================================
#define MAX_VAL  50
/* 
 * ===  FUNCTION  ====================================================
 *         Name:  print_current_displayenv ()
 *  Description:  
 * ===================================================================
 */
    void
print_current_displayenv ()
{
    char *env_var = getenv ("DISPLAY");

    if (env_var == nullptr) {
        printf ("DISPLAY env is NULL.\n");
    } else {
        printf ("Current DISPLAY is:  %s\n",env_var);
    } 
}		/* -----  end of function print_current_displayenv ()  ----- */

#ifndef _TEST_
    int main()
#else
    int run_halverson05 ()
#endif
{
    GC gc;     // It remembers the colors and window and various details.
    Window w;
    
    Display *dpy;
    XColor black_col,
            white_col,
            red_col,
            green_col,
            blue_col,
            yellow_col,
            magenta_col,
            cyan_col;

  Colormap colormap;

  char black_bits[]   = "#000000";
  char white_bits[]   = "#FFFFFF";    // Mix red, green and blue to get white
  char red_bits[]     = "#FF0000";
  char green_bits[]   = "#00FF00";
  char blue_bits[]    = "#0000FF";
  char yellow_bits[]  = "#FFFF00";   // Mix red and green to get yellow
  char magenta_bits[] = "#FF00FF";  // A sort of purple color
  char cyan_bits[]    = "#00FFFF";     // A blue-green color
  int8_t done = 0;  
  print_current_displayenv ();
  //Display *dpy = XOpenDisplay(NIL); 
  dpy = XOpenDisplay(NIL); assert(dpy);   // Open the display

  // Define the colors we want to use
  colormap = DefaultColormap(dpy, 0);

  XParseColor(dpy, colormap, black_bits, &black_col); 
  XAllocColor(dpy, colormap, &black_col);
  XParseColor(dpy, colormap, white_bits, &white_col); 
  XAllocColor(dpy, colormap, &white_col);
  XParseColor(dpy, colormap, red_bits,   &red_col); 
  XAllocColor(dpy, colormap, &red_col);
  XParseColor(dpy, colormap, green_bits, &green_col);
  XAllocColor(dpy, colormap, &green_col);
  XParseColor(dpy, colormap, blue_bits,  &blue_col);
  XAllocColor(dpy, colormap, &blue_col);
  XParseColor(dpy, colormap, yellow_bits,&yellow_col);
  XAllocColor(dpy, colormap, &yellow_col);
  XParseColor(dpy, colormap, magenta_bits,&magenta_col);
  XAllocColor(dpy, colormap, &magenta_col);
  XParseColor(dpy, colormap, cyan_bits,  &cyan_col);
  XAllocColor(dpy, colormap, &cyan_col);

  // Create the window  The numbers are the x and y locations on the screen, 
  // the width and height, 

  // border width (which is usually zero)
  w = XCreateSimpleWindow(dpy, 
                         DefaultRootWindow(dpy), 
                         0, 0, 
                         window_width,
                         window_height,
                         0, 
                         black_col.pixel, 
                         black_col.pixel);

  Atom wmDeleteMsg = XInternAtom (dpy, "WM_DELETE_WINDOW", False);
  XSetWMProtocols (dpy, w, &wmDeleteMsg, 1);

  XSelectInput(dpy, w, StructureNotifyMask | ExposureMask); 
  // We want to get MapNotify events

  gc = XCreateGC (dpy, w, 0, NIL);
  
  halv = new halverson (dpy, w, gc);

  halv->get_pen (white_col, dpy, gc);

  XMapWindow(dpy, w); // "Map" the window (make it appear on the screen)

  for(;;) {
      XEvent e; XNextEvent(dpy,&e); 
        switch (e.type) {
            case Expose:
                    srand (time (NULL));
                for (int i=0; i<20; i++) {
                    halv->home ();
                    halv->get_pen (green_col, dpy, gc);
                    halv->pen_up ();
                    halv->left (90);
                    halv->forward (-300, dpy, w, gc);
                    halv->pen_down ();
                    halv->branch (1, dpy, w, gc);
                }
                halv->get_pen (white_col, dpy, gc);
                halv->display_owner_info (dpy, w, gc, 
                        window_width, window_height);
                break;
            case ClientMessage:
                if (e.xclient.data.l[0] == wmDeleteMsg) {
                    printf ("Shutting down!\n");
                    done = run_OkCancel ();
                    XFreeGC (dpy,gc);
                    XDestroyWindow (dpy, w);
                    XCloseDisplay (dpy);
                    return (EXIT_SUCCESS);
                }
                break;
            }
        }
  return(0);
}

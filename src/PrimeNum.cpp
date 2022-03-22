// Calculate prime numbers

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <cstdint>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <iomanip>
#include <string>

#include "common.h"

#define _TEST_

using namespace std;

extern int argc;
extern char *argv[];

/* 
 * ===  FUNCTION  ====================================================
 *         Name:  getGC (Window win, GC *gc, XFontStruct *font_info)
 *  Description:  
 * ===================================================================
 */
    void
getGc (Display *dpy, Window win, GC *gc, XFontStruct *fs)
{
#ifndef _SOLID_LINE_
    unsigned long valuemask = 0; /* Ignore XGCValues use defaults */
    XGCValues     values;

    /* Create default Graphics Context  */
    *gc = XCreateGC (dpy, win, valuemask, &values);
    /* Specify font  */
    XSetFont (dpy, *gc, fs->fid);

    uint8_t line_width = 6; /* 0 would be fast line of width 1 */
    int line_style = LineSolid;  /* LineOnOffDash or LineDoubleDash */
    int cap_style = CapRound;    /* CapNotLast, CapButt CapProjecting */
    int join_style = JoinRound;  /* JoinNitter or JoinBevel */

    XSetLineAttributes (dpy,
                        *gc,
                        line_width,
                        line_style,
                        cap_style,
                        join_style);
#else
    uint8_t       line_width = 2;
    int           line_style = LineOnOffDash;
    int           cap_style  = CapRound;
    int           join_style = JoinRound;
    int           dash_offset = 0;
    char          dash_list[] = {12, 24};
    int           list_length = 2;
    /* Specify black foreground since default window background
     * is white and default foreground is undefined 
     * */
    /*  Set line attributes  */
    XSetLineAttributes (dpy, *gc, line_width,
                        line_style, cap_style, join_style);
    /* Set dashes  */
    XSetDashes (dpy, *gc, dash_offset, dash_list, list_length);
#endif
}   /* end of function getGC (Window win, GC *gc, XFontStruct *font_info) */

/* 
 * ===  FUNCTION  ====================================================
 *         Name:  int get_pen (XColor desired_col)
 *  Description:  
 * ===================================================================
 */
    int
get_pen (Display *dpy, GC gc, XColor desired_col)
{   XSetForeground (dpy,
                    gc,
                    desired_col.pixel);
    return (0);
}       /* -----  end of function int get_pen (XColor desired_col)  ----- */

/* 
 * ===  FUNCTION  ====================================================
 *         Name:  Loadfont (XFontStruct **fs)
 *  Description:  
 * ===================================================================
 */
    void
Loadfont (XFontStruct **fs, Display *dpy, char *prName) 
{   char *fontname = (char*) \
       // "12x24";
       // "10x20";
       // "5x7";
       // "5x8";
       // "6x9";
       // "6x10";
       // "6x12";
       // "6x13";
       // "7x13";
       // "7x13bold";
       // "8x13";
        "8x13bold";
       // "8x16";
      //"-sun-open look glyph-----14-140-75-75-p-128-sunolglyph-1";
      //"-schumacher-clean-medium-r-normal--15-150-75-75-c-90-iso646.1991-irv";
      //"-misc-fixed-bold-r-normal--0-0-75-75-c-0-iso8859-4";
      //"-adobe-avant garde gothic-demi-r-normal--0-0-0-0-p-0-iso8859-15";
      //"-sony-fixed-medium-r-normal--16-120-100-100-c-80-iso8859-1";
      //"-misc-fixed-bold-r-semicondensed--0-0-75-75-c-0-iso8859-16";
      //"-urw-century schoolbook l-bold-i-normal--0-0-0-0-p-0-iso8859-15";
      //"-urw-urw chancery l-medium-i-normal-medium-0-0-0-0-p-0-iso8859-15";
      //"-urw-urw gothic l-demibold-o-normal--0-0-0-0-p-0-iso8859-15";
      //"-adobe-avant garde gothic-demi-o-normal--0-0-0-0-p-0-iso8859-15";
      //"-misc-fixed-bold-r-normal--0-0-75-75-c-0-iso8859-16";
      //"9x15bold";
        if ((*fs = XLoadQueryFont (dpy, fontname)) == NULL) {
            fprintf (stderr, "%s Cannot load font: %s\n", prName, fontname);
            exit (EXIT_FAILURE);
        }
}		/* -----  end of function Loadfont (XFontStruct **fs)  ----- */
/* 
 * ===  FUNCTION  ====================================================
 *         Name:  run_primeNum_header ()
 *  Description:  
 * ===================================================================
 */
    void
run_primeNum_header (Display *dpy, Window win, GC gc, XFontStruct *fs,
                        uint32_t win_width, uint32_t win_height)
{
    int8_t y_offset = 0;
    int8_t fs_height = fs->ascent + fs->descent;

    Colormap colormap;
    XColor  White_col,                  // 20
            Dark_Yellow_col,            // 21
            Light_Yellow_col,           // 22
            Black_col;                  // 23 

    char Black[]=          "#000000"; // 20 0% 0% 0% 0° 0% 0% 0% 0%
    char White[]=          "#FFFFFF"; // 21 100% 100% 100% 0° 0% 100% 0% 100%
    char Dark_Yellow[]=    "#FFCC00"; // 22 100% 80% 0% 48° 100% 50% 100% 100%
    char Light_Yellow[]=   "#FFFFE0"; // 23 100% 100% 88% 60° 100% 94% 12% 100%

    colormap = DefaultColormap (dpy, 0);  // this initialisation MUST be done
     
    XParseColor (dpy, colormap, Black, &Black_col);
    XAllocColor (dpy, colormap, &Black_col);
    XParseColor (dpy, colormap, White, &White_col);
    XAllocColor (dpy, colormap, &White_col);
    XParseColor (dpy, colormap, Dark_Yellow, &Dark_Yellow_col);
    XAllocColor (dpy, colormap, &Dark_Yellow_col);
    XParseColor (dpy, colormap, Light_Yellow, &Light_Yellow_col);
    XAllocColor (dpy, colormap, &Light_Yellow_col);

    const char *s = "Prime number generator max number 500";
    const char *s1= "Press x button at the right of window to exit";
    get_pen (dpy, gc, White_col);
    XDrawString (dpy, 
                 win, 
                 gc, 
                 (win_width-XTextWidth (fs, (char*)s, strlen (s)))/2,
                 y_offset + fs_height,
                 (char*)s,
                 strlen (s));

    XDrawLine (dpy, win, gc,
               (win_width/4),
               (20 +(10)),
               (3*(win_width/4)),
               (20+(10)));
    get_pen (dpy, gc, Dark_Yellow_col);
    y_offset += 10;
    XDrawString (dpy, 
                 win, 
                 gc, 
                 (win_width-XTextWidth (fs, (char*)s1, strlen (s1)))/2, 
                 y_offset + (2*fs_height), 
                 (char*)s1, 
                 strlen (s1));
    get_pen (dpy, gc, White_col);
}	/* -----  end of function run_primeNum_header -- */

/* 
 * ===  FUNCTION  ====================================================
 *         Name:  run_primeNum ()
 *  Description:  
 * ===================================================================
 */
    void
run_primeNum (Display *dpy, Window win, GC gc, XFontStruct *fs,
                        uint32_t win_width, uint32_t win_height)
{
 	const int16_t MAX = 500;					// number of prime required
	long primes[MAX] = { 2, 3, 5 };				// First three prime defined
	long trial = 5;								// Candidate prime
	int16_t count = 3;							// count of primes cound
	int8_t found = 0;							// indicate when prime is found
    char  buf[5] = {0};
    int16_t x_offset = 0;
    int16_t y_offset = 0;

    do
	{
		trial += 2;								// nex value for checking
		found = 0;								// set found indicator
		for( int i=0; i < count; i++ )
		{
			found = ( trial % *( primes + i )) == 0;	// true for exact;
			
			if( found )							// if division is exact
				break;							// it is not prime number
		}
		if( found == 0 )						// so we got one...
			*( primes + count ++ ) = trial;		// so save it in prime array
	} while( count < MAX );

    x_offset = 10;   //(win_width/40)+60;       
    y_offset = 90;
    int j=1;
    // out put the primes 5 to  line
	for( int i = 0; i < MAX; i++ )
	{
		if( i % 5 == 0 ) {
			cout << endl;
        }
	   //cout << setw(10) << *( primes + i );
        sprintf (buf, "%ld", (*(primes + i)) );
       
        XDrawString (dpy,
                     win,
                     gc,
                     x_offset +=100,
                     y_offset,
                     buf,
                     strlen (buf));
        if (j==12) {            
            buf[0] =  '\0'; 
            y_offset = y_offset + 20;
            x_offset = 10;
            j = 1; 
            continue; 
            }
           j++;
        }
    return ;
}		/* -----  end of function run_primeNum ()  ----- */
#ifndef _TEST_
    int main(int argc, char *argv[])
#else
    int run_prime_numbers()
#endif
{
#define NIL (0)
    Display             *dpy;
    Window              win;
    XSizeHints          *size_hints;
    XWMHints            *wm_hints;
    XClassHint          *class_hints;
    XTextProperty       winName, iconName;
    GC                  gc;
    XEvent              ev;
    XFontStruct         *fs;
    char                *win_name =(char*)"Prime Number Generator";
    char                *icon_name=(char*)"PrimeBum";
    uint32_t            win_width=0, win_height=0;
    int8_t              done=0;
    char                *prName = (char*)"PrimeNum";

    if (!(size_hints = XAllocSizeHints())) {
        fprintf (stderr, "%s: failed to allocating 'XAllocSizeHints' memory\n",
                prName);
        exit (EXIT_FAILURE);
    }
    if (!(wm_hints = XAllocWMHints())) {
        fprintf (stderr, "%s: failed to allocate 'XAllocWMHints' memory\n",
                prName);
        exit (EXIT_FAILURE);
    }
    if (!(class_hints = XAllocClassHint())) {
        fprintf (stderr, "%s: failed to allocate 'XAllocClassHint' memory\n",
                prName);
        exit (EXIT_FAILURE);
    }
    if (XStringListToTextProperty (&win_name, 1, &winName) == 0) {
        fprintf (stderr, "%s: structure allocation for winName failed\n",
                prName);
         exit (EXIT_FAILURE);
    }
    if (XStringListToTextProperty (&icon_name, 1, &iconName) == 0)
    {
        fprintf (stderr, "%s: Structure allocation iconName failed\n", 
                 prName);
         exit (EXIT_FAILURE);
    }

    size_hints->flags = PPosition | PSize | PMinSize;
    size_hints->min_width = 300;
    size_hints->min_height= 200;

    wm_hints->initial_state = NormalState;
    wm_hints->input = True;
    //wm_hints->icon_pixmap = icon_pixmap;
    wm_hints->flags = StateHint | IconPixmapHint | InputHint;
    class_hints->res_name = prName;
    class_hints->res_class = (char*)"PrimeNum";

    /* Connect to X server  */
    if ((dpy = XOpenDisplay (NIL)) == NULL) {
         fprintf (stderr, "%s: cannot connect to X server\n", prName );
        exit (EXIT_FAILURE);
    }
   
    /* Get screen size from display structure macro */
    short scrn = DefaultScreen (dpy);
    win_width = DisplayWidth (dpy, scrn);
    win_height= DisplayHeight (dpy, scrn);
    win_width = win_width/2;      // win_height = win_height/2;    
    win = XCreateSimpleWindow (dpy,
                               RootWindow (dpy,scrn),
                               0, 0,
                               win_width,
                               win_height,
                               4,
                               WhitePixel (dpy, scrn),
                               BlackPixel (dpy, scrn) );
    Atom wmDeleteMsg = XInternAtom (dpy, "WM_DELETE_WINDOW", False);
    XSetWMProtocols (dpy, win, &wmDeleteMsg, 1);

    gc = XCreateGC (dpy, win, 0, NULL);

    XSetWMProperties (dpy,
                      win,
                      &winName,
                      &iconName,
                      argv,
                      argc,
                      size_hints,
                      wm_hints,
                      class_hints);

    XSetWMIconName (dpy, win, &iconName);
    XSelectInput (dpy, 
                  win,
                  ExposureMask   |
                  KeyPressMask   |
                  StructureNotifyMask);

    /* Load a choice of Fonts in the XFontStruct variable */
    Loadfont (&fs, dpy, prName);
    /* Create GC for text and drawing with loaded Fonts */
    getGc (dpy, win, &gc, fs);
    run_primeNum (dpy, win, gc, fs, win_width, win_height);
    XMapWindow (dpy, win);

    while (done == 0) {
        XNextEvent (dpy, &ev);
        switch (ev.type) {
            case Expose:
                run_primeNum_header (dpy, win, gc, fs, win_width, win_height);
                //sleep (1);
                run_primeNum (dpy, win, gc, fs, win_width, win_height);
                break;
            case KeyPress:
                //XUnloadFont (dpy, fs->fid);
                //XFreeGC (dpy, gc);
                //XCloseDisplay (dpy);
                //return (EXIT_SUCCESS);
                break;
            case ClientMessage:
                if (ev.xclient.data.l[0] == wmDeleteMsg) {
                    printf ("Shutting down!\n"); done = run_OkCancel ();
                }
        }
    }
    XUnloadFont (dpy, fs->fid);
    XFreeGC (dpy, gc);
    XDestroyWindow (dpy, win);
    XCloseDisplay (dpy);
    printf ("All resources free\n");
	return (EXIT_SUCCESS);
}

// Ext
// using nested loop to generate a multiplcation table

#include <iostream>
#include <iomanip>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <iostream>
#include <iomanip>
#include <string>

#include "common.h"

using namespace std;

#define NIL (0)

#define _TEST_
extern int argc;
extern char *argv[];

/* 
 * ===  FUNCTION  ====================================================
 *         Name:  run_calc_multiplication (Display *dpy, Window win, GC gc, 
 *                              uint32_t win_width, uint32_t win_height)
 *  Description:  
 * ===================================================================
 */
    void
run_calc_multiplication (Display *dpy, Window win, GC gc, 
                             uint32_t win_width, uint32_t win_height)
{
 	const int size = 30;			// size of table
	int i = 0, j = 0;				// loop counter
	//system("clear");
    char  buf[25] = {0};
    int16_t x_offset = 10;
    int16_t y_offset = 90;
    int16_t k = 1;

	//cout << endl
	//  << size << " by " << size << " Multiplication Table" << endl  << endl;
	//cout << endl << "    |";
	//for ( i=1; i <= size; i++ )				// loop through
		//cout << setw(3) << i << "  ";
    

    XDrawLine (dpy, win, gc,
               (win_width/50),
               (100 +(10)),
               (2*(win_width)/2),
               (100+(10)));  

	//cout << endl;

    for( i=0; i <= size; i++ ) {
		//cout << "-----";						// under line headline
    }
    x_offset = win_width/100;
    y_offset = win_height/10;
    k = 1;
	// outer loop
	for( i=1; i <= size; i++ )
	{
		//cout << endl << setw(3) << i << " |";

				for( j=1; j <= size; j++ ) 
                {
					//cout << setw(3) << i * j << "  ";                
                    sprintf (buf, "%d",(i*j));
                
                    XDrawString (dpy, win, gc, 
                                 x_offset +=40,
                                 y_offset,
                                 buf,
                                 strlen (buf)); 
                    if (k == size) {
                        buf[0]  = '\0';
                        y_offset = y_offset +20;
                        x_offset=10;
                        k = 1;
                        continue;
                    }                
                k++; 
                }
	}   
    //cout << endl;
}	/*  end of function run_calc_multiplication ()  ----- */
/* 
 * ===  FUNCTION  ====================================================
 *         Name:  set_line_attributes (Display *dpy, Window win, GC gc)
 *  Description:  It is vital for creating pointer GC from normal GC
 * ===================================================================
 */
    void
set_line_attributes (Display *dpy, Window win, GC *gc, XFontStruct *fs,
                                    int8_t num)
{
    XGCValues     values;
    unsigned long umask = 0;      // GCForeground | GCBackground;
    uint8_t       line_width = num;
    uint16_t      line_style = LineSolid;
    uint16_t      cap_style = CapRound;
    uint16_t      join_style = JoinRound;

    // Create gc with pointer to point the fonts
    *gc = XCreateGC (dpy, win, umask, &values);
    // Now set the font to appropriate GC
    XSetFont (dpy, *gc, fs->fid);
    // subsequently to the line solid or dotted for GC
    XSetLineAttributes (dpy, 
                        *gc, 
                        line_width,
                        line_style,
                        cap_style,
                        join_style);
}		/* -----  end of function  ----- */
/* 
 * ===  FUNCTION  ====================================================
 *         Name:  int get_tpen (XColor desired_col)
 *  Description:  
 * ===================================================================
 */
    int
get_tpen (Display *dpy, GC gc, XColor desired_col)
{   XSetForeground (dpy,
                    gc,
                    desired_col.pixel);
    return (0);
}       /* -----  end of function int get_tpen (XColor desired_col)  ----- */
/* 
 * ===  FUNCTION  ====================================================
 *         Name:  run_table_header (Display *dpy, Window win, GC, 
 *                XFontStruct *fs, uint32_t win_width, uint32_t win_height)
 *  Description:  
 * ===================================================================
 */
    void
run_table_header (Display *dpy, Window win, GC gc, XFontStruct *fs, 
                                uint32_t win_width, uint32_t win_height)
{
    int8_t y_offset = 0; 
    int8_t fs_height = fs->ascent + fs->descent;

    Colormap colormap;
    XColor  White_col,                  // 20
            Dark_Yellow_col,            // 21
            Light_Yellow_col,           // 22
            Black_col;                  // 23 

    char Black[9]=          "#000000"; // 20 0% 0% 0% 0° 0% 0% 0% 0%
    char White[9]=          "#FFFFFF"; // 21 100% 100% 100% 0° 0% 100% 0% 100%
    char Dark_Yellow[9]=    "#FFCC00"; // 22 100% 80% 0% 48° 100% 50% 100% 100%
    char Light_Yellow[9]=   "#FFFFE0"; // 23 100% 100% 88% 60° 100% 94% 12% 100%

    colormap = DefaultColormap (dpy, 0);  // this initialisation MUST be done
     
    XParseColor (dpy, colormap, Black, &Black_col);
    XAllocColor (dpy, colormap, &Black_col);
    XParseColor (dpy, colormap, White, &White_col);
    XAllocColor (dpy, colormap, &White_col);
    XParseColor (dpy, colormap, Dark_Yellow, &Dark_Yellow_col);
    XAllocColor (dpy, colormap, &Dark_Yellow_col);
    XParseColor (dpy, colormap, Light_Yellow, &Light_Yellow_col);
    XAllocColor (dpy, colormap, &Light_Yellow_col);

    const char *s  = "Multiplication Table generator 30x30";
    const char *s1 = "Press x button at the right of window to exit";
    get_tpen (dpy, gc, White_col);
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
    get_tpen (dpy, gc, Dark_Yellow_col);
    y_offset += 10;
    XDrawString (dpy, 
                 win, 
                 gc, 
                 (win_width-XTextWidth (fs, (char*)s1, strlen (s1)))/2, 
                 y_offset + (2*fs_height), 
                 (char*)s1, 
                 strlen (s1));  
    get_tpen (dpy, gc, White_col); 
}/* -----  end of function   ----- */
/* 
 * ===  FUNCTION  ====================================================
 *         Name:  loadFont (Display *dpy,XFontStruct **fs)
 *  Description:  
 * ===================================================================
 */
    bool
loadFont (Display *dpy,  XFontStruct **fs)
{   char *fontname  = (char*) \
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
       // "8x13bold";
        "8x16";
      //"-*-helvetica-*-r-*-*-28-*-*-*-*-*-*-*";
      //"-sun-open look glyph-----14-140-75-75-p-128-sunolglyph-1";
      //"-schumacher-clean-medium-r-normal--15-150-75-75-c-90-iso646.1991-irv";
      //"-misc-fixed-bold-r-normal--0-0-75-75-c-0-iso8859-4";
      //"-sony-fixed-medium-r-normal--16-120-100-100-c-80-iso8859-1";
      //"-misc-fixed-bold-r-semicondensed--0-0-75-75-c-0-iso8859-16";
      //"-urw-century schoolbook l-bold-i-normal--0-0-0-0-p-0-iso8859-15";
      //"-urw-urw chancery l-medium-i-normal-medium-0-0-0-0-p-0-iso8859-15";
      //"-urw-urw gothic l-demibold-o-normal--0-0-0-0-p-0-iso8859-15";
      //"-adobe-avant garde gothic-demi-o-normal--0-0-0-0-p-0-iso8859-15";
      //"-misc-fixed-bold-r-normal--0-0-75-75-c-0-iso8859-16";
      //"9x15bold";
      //"-adobe-avant garde gothic-demi-r-normal--0-0-0-0-p-0-iso8859-15";
      //"-adobe-helvetica-medium-r-normal--0-0-0-0-p-0-iso8859-15";
      //"-urw-nimbus sans l-bold-r-normal--0-0-0-0-p-0-iso8859-15";
      //"-urw-urw gothic l-book-o-normal--0-0-0-0-p-0-iso8859-15";
      //"-adobe-times-bold-i-normal--0-0-0-0-p-0-iso8859-15";    
      //"-adobe-avant garde gothic-demi-o-normal--0-0-0-0-p-0-iso8859-15";

    if ((*fs = XLoadQueryFont (dpy, fontname)) == nullptr) {
        fprintf (stderr, "%s : cannot load font. Do not exists\n", fontname);
        exit (EXIT_FAILURE);
    }
    printf ("Font loaded: %s\n", fontname);
    return (true);
}	/*  end of function   */
/* 
 * ===  FUNCTION  ====================================================
 *         Name:  int main (int argc, char**argv)
 *  Description:  
 * ===================================================================
 */
#ifndef _TEST_
    int 
    main (int argc, char**argv)
#else
    int 
    run_Tables ()
#endif
{
    Display             *dpy;
    Window              win;
    GC                  gc;
    XFontStruct         *fs;
    XTextProperty       winName, iconName;
    XSizeHints          *size_hints;
    XWMHints            *wm_hints;
    XClassHint          *class_hints;
    XEvent              ev;

    uint16_t            win_width, win_height;
    char                *win_name = (char*)"TIMES Table Generator";
    char                *icon_name= (char*)"Timestable";
    char                *prName = (char*)"TimesTable";
    int8_t              done = 0;


    // call XAllocXXX functions to verify structure loaded correctly
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
    class_hints->res_class = (char*)"Tables";

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
    loadFont (dpy, &fs);
    set_line_attributes (dpy, win, &gc, fs, 2);

    XMapWindow (dpy, win);

    while (done == 0) {
        XNextEvent (dpy, &ev);
        switch (ev.type) {
            case Expose:
                run_table_header (dpy, win, gc, fs, win_width, win_height);
                run_calc_multiplication (dpy, win, gc, win_width, win_height);
                break;
            case KeyPress:
                XUnloadFont (dpy, fs->fid);
                XFreeGC (dpy, gc);
                XCloseDisplay (dpy);
                return (EXIT_SUCCESS);
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

    return (EXIT_SUCCESS);;
}	/* -----  end of function int main (int, char**)  ----- */

/*
 * ========================================================================
 *
 *       Filename:  ch03_BasicWin.c
 *
 *    Description:  Look at the complete code for basicwin and make sure you 
 *                  understand everything. Note that the draw_graphics, 
 *                  draw_text, get_GC, and loadfont routines have not 
 *                  yet been described but will be covered in later chapters
 *
 *        Version:  1.0
 *        Created:  24/05/20 22:13:13
 *       Revision:  none
 *       Compiler:  gcc  -lX11 -lXpm -lGL -lGLU
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *        Website:  http://csweb.cs.wfu.edu/~torgerse/Kokua/Irix_6.5.21_doc_cd/usr/share/Insight/library/SGI_bookshelves/SGI_Developer/books/XLib_PG/sgi_html/ch04.html 
 *        Website:  http://csweb.cs.wfu.edu/~torgerse/Kokua/Irix_6.5.21_doc_cd/usr/share/Insight/library/SGI_bookshelves/SGI_Developer/books/XLib_PG/sgi_html/ch05.html
 *
 *
 *     Example 5-1. The GCValues structure
 *
 * Data structure for setting graphics context  
 *    typedef struct {
 *       int function;                // Logical function 
 *       unsigned long plane_mask;    // Plane mask   
 *       unsigned long foreground;    // Foreground pixel   
 *       unsigned long background;    // Background pixel   
 *           int line_width;          // Line width 
 *       int line_style;              // LineSolid, LineOnOffDash,
 *                                    //  LineDoubleDash   
 *       int cap_style;               //  CapNotLast, CapButt, CapRound,
 *                                    //  CapProjecting   
 *       int join_style;              //  JoinMiter, JoinRound, JoinBevel   
 *       int fill_style;              //  FillSolid, FillTiled, FillStippled,
 *                                    //  FillOpaqueStippled   
 *       int fill_rule;               // EvenOddRule, WindingRule   
 *       int arc_mode;                //  ArcChord, ArcPieSlice   
 *       Pixmap tile;                 //  Tile pixmap for tiling operations   
 *       Pixmap stipple;              //  Pixmap of depth 1   
 *       int ts_x_origin;             //  Offset for tile or stipple operations
 *       int ts_y_origin;
 *       Font font;                   //  Font for text operations (except
 *                                    //  XDrawText)   
 *       int subwindow_mode;          //  ClipByChildren, IncludeInferiors   
 *       Bool graphics_exposures;     //  Should events be generated on
 *                                    //  XCopyArea, XCopyPlane    
 *       int clip_x_origin;           //  Origin for clipping   
 *       int clip_y_origin;
 *       Pixmap clip_mask;            //  Bitmap for clipping   
 *       int dash_offset;             //  Patterned/dashed line information   
 *       char dashes;
 *     } XGCValues;
 *
 *      Table 5-1 shows the symbols used to specify which members of the 
 *      XGCValues structure actually contain meaningful values. 
 *      The valuemask is made up of these symbols combined by means of a 
 *      bitwise OR (|).
 *
 *      Table 5-1. Symbols for Setting the XGCValues Structure
 *
 *      Member           Mask         Set Bit           Default
 *      ========================================================
 *
 *      Function         GCFunction      0              GXcopy
 *      plane_mask       GCPlaneMask     1              all 1 's
 *      foreground       GCForeground    2              0
 *      background       GCBackground    3              1
 *      line_width       GCLineWidth     4              0
 *      line_style       GCLineStyle     5              LineSolid
 *      cap_style        GCCapStyle      6              CapButt
 *      join_style       GCJoinStyle     7              JoinMiter
 *      fill_style       GCFillStyle     8              FillSolid
 *      fill_rule        GCFillRule      9              EvenOddRule
 *      arc_mode         GCArcMode       22             ArcPieSlice
 *      tile             GCTile          10 pixmap filled with foreground pixel
 *      stipple          GCStipple       11             pixmap filled with 1 's
 *      ts_x_origin      GCTileStipXOrigin 12           0
 *      ts_y_origin      GCTileStipYOrigin 13           0
 *      font             GCFont            14       (implementation dependent)
 *      subwindow_mode   GCSubwindowMode   15       ClipByChildren
 *      graphics_exposures GCGraphicsExposures 16   True
 *      clip_x_origin    GCClipXOrigin     17            0        
 *      clip_y_origin    GCClipYOrigin     18            0
 *      clip_mask        GCClipMask        19            None
 *      dash_offset      GCDashOffset      20            0
 *      dashes           GCDashList        21       4 (i.e., the list [4, 4])
 *
 * Table 5-3. The Default Values of a Graphics Context
 *
 *         Component                            Value
 *  =====================================================
 *       function                              GXcopy
 *       plane_mask                            all 1 's
 *       foreground                            0
 *       background                            1
 *       line_width                            0
 *       line_style                            LineSolid
 *       cap_style                             CapButt
 *       join_style                            JoinMiter
 *       fill_style                            FillSolid
 *       fill_rule                             EvenOddRule
 *       arc_mode                              ArcPieSlice
 *       tile                                  Pixmap filled with foreground 
 *                                             pixel
 *       stipple                               Pixmap filled with 1 's
 *       ts_x_origin                           0
 *       ts_y_origin                           0
 *       font                                  (Implementation dependent)
 *       subwindow_mode                        ClipByChildren
 *       graphics_exposures                    True
 *       clip_x_origin                         0
 *       clip_y_origin                         0
 *       clip_mask                             None
 *       dash_offset                           0
 *       dashes                                4 (i.e., the list [4, 4])
 *
 *           A useful quick reference to the graphics context is 
 *           provided inside the back cover of Volume Two.
 *
 * =========================================================================
 */
#include <X11/Xlib.h>    /*  These heder file mandatory for all X11 apps */
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>
#include <X11/xpm.h>     /* high resolution graphic icon link with -lXpm  */

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <stdint.h>

/*  #include "icon_bitmap" */

#include "rose.h"
#include "common.h"
#include "../include/adf_colors.h"
#include "../include/myMacro.h"

#ifdef Images
  #undef Images
#endif

#define BITMAPDEPTH   1
#define TOO_SMALL     0
#define BIG_ENOUGH    1
#define NIL (0)

extern int argc;
extern char *argv;

/* These are used as arguments to nearly every Xlib routine, so it
 * saves routine arguments to declare them global; if there were
 * additional source files, they would be declared extern there 
 * */

Display *dpy;
int     scrn;
char *prName;

/* progname is the string by which this program was invoked; this
 * is global because it is needed in most application functions 
 * */

/* 
 * ===  FUNCTION  ====================================================
 *         Name:  getGC (Window win, GC *gc, XFontStruct *font_info)
 *  Description:  
 * ===================================================================
 */
    void
getGC (Window win, GC *gc, XFontStruct *font_info)
{
    unsigned long valuemask = 0; /* Ignore XGCValues use defaults */
    XGCValues     values;
    uint32_t      line_width = 6;
    int           line_style = LineOnOffDash;
    int           cap_style  = CapRound;
    int           join_style = JoinRound;
    int           dash_offset = 0;
    char          dash_list[] = {12, 24};
    int           list_length = 2;

    /* Create default Graphics Context  */
    *gc = XCreateGC (dpy, win, valuemask, &values);

    /* Specify font  */
    XSetFont (dpy, *gc, font_info->fid);

    /* Specify black foreground since default window background
     * is white and default foreground is undefined 
     * */
    XSetForeground (dpy, *gc, WhitePixel (dpy, scrn));

    /*  Set line attributes  */
    XSetLineAttributes (dpy, *gc, line_width, 
                        line_style, cap_style, join_style);
    
    /* Set dashes  */
    XSetDashes (dpy, *gc, dash_offset, dash_list, list_length);

}	/* end of function getGC (Window win, GC *gc, XFontStruct *font_info) */


/* 
 * ===  FUNCTION  ====================================================
 *         Name:  loadfont (XFontStruct **font_info)
 *  Description:  
 * ===================================================================
 */
    void
loadfont (XFontStruct **font_info)
{
  char *fontname = (char*) \
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
      //"-sony-fixed-medium-r-normal--16-120-100-100-c-80-iso8859-1";
      //"-misc-fixed-bold-r-semicondensed--0-0-75-75-c-0-iso8859-16";
      //"-urw-century schoolbook l-bold-i-normal--0-0-0-0-p-0-iso8859-15";
      //"-urw-urw chancery l-medium-i-normal-medium-0-0-0-0-p-0-iso8859-15";
      //"-urw-urw gothic l-demibold-o-normal--0-0-0-0-p-0-iso8859-15";
      //"-adobe-avant garde gothic-demi-o-normal--0-0-0-0-p-0-iso8859-15";
      //"-misc-fixed-bold-r-normal--0-0-75-75-c-0-iso8859-16";
      //"9x15bold";
      //"-adobe-avant garde gothic-demi-r-normal--0-0-0-0-p-0-iso8859-15";

    /* Load font and get font information structure */
    if ((*font_info = XLoadQueryFont (dpy, fontname)) == NULL) {
        fprintf (stderr, "%s Cannot open font: %s \n", 
                       prName, fontname);
        exit (EXIT_FAILURE);
    }
}	/* -----  end of function loadfont (XFontStruct **font_info)  ----- */

/* 
 * ===  FUNCTION  ====================================================
 *         Name:  place_text (Window win, GC gc, unsigned int width, 
 *                              unsigned int height)
 *  Description:  
 * ===================================================================
 */
    void
place_header_text (Window win, GC gc, 
            XFontStruct *font_info, 
            unsigned int win_width, unsigned int win_height)
{
#ifndef _WIDE_CHAR_

    char *str_1 = (char*)"Hi I am a window, who are you?";
    char *str_2 = (char*)"To terminate program. Press X at right corner";
    char *str_4 = (char*)"Screen Dimensions: ";
    char cd_buff[250];

    /*  Need length for both XTextWidth and XDrawString */
    /*  Get string widths for centering  */

    int8_t font_height = font_info->ascent + font_info->descent;;
    int8_t x_offset = 0;
    int8_t y_offset = 20; 

    /* Output the text, centered on each line  */
    XDrawString (dpy, 
                 win, 
                 gc, 
                 (win_width-XTextWidth (font_info, (char*)str_1, 
                 strlen (str_1)))/2,
                 y_offset + font_height,
                 (char*)str_1, 
                 strlen (str_1));

     XDrawString (dpy, 
                 win, 
                 gc, 
                 (win_width-XTextWidth (font_info, (char*)str_2, 
                 strlen (str_2)))/2,
                 y_offset + (2*font_height),
                 (char*)str_2, 
                 strlen (str_2));

     XDrawString (dpy, 
                 win, 
                 gc, 
                 x_offset,     
                 y_offset + font_height,
                 (char*)str_4, 
                 strlen (str_4));
     
     /* Copy numbers into string variables  */
    sprintf (cd_buff, "Height = %d pixels", win_height);

    /* To center strings vertically, we place the first string
     * so that the top of it is two font heights above the center
     * of the window; since the baseline of the string is what
     * we need to locate for XDraString and the baseline is
     * one font info -> ascent below the top of the character,
     * the final offset of the origin up from the center of 
     * the window is one font_height/2 + one descent 
     * */

    XDrawString (dpy,
                 win,
                 gc,
                 x_offset,     
                 y_offset + (2*font_height),
                 (char*)cd_buff,
                 strlen (cd_buff));
    sprintf (cd_buff, "Width = %d pixels", win_width);
    XDrawString (dpy,
                 win,
                 gc,
                 x_offset,
                 y_offset + 20 + (2*font_height),
                 (char*)cd_buff,
                 strlen (cd_buff));
    sprintf (cd_buff, "Depth = %d", DefaultDepth (dpy,scrn));
    XDrawString (dpy,
                 win,
                 gc,
                 x_offset,
                 y_offset + 40 + (2*font_height),
                 (char*)cd_buff,
                 strlen (cd_buff));
#else
    wchar_t *str_1 = L"Hi I am a window, who are you?";
    wchar_t *str_2 = L"To terminate program. Press X at right corner";
    wchar_t *str_4 = L"Screen Dimensions: ";
    wchar_t cd_buff[250];

    /*  Need length for both XTextWidth and XDrawString */
    /*  Get string widths for centering  */

    int8_t font_height = font_info->ascent + font_info->descent;;
    int8_t x_offset = 0;
    int8_t y_offset = 20; 

    /* Output the text, centered on each line  */
    XDrawString (dpy, 
                 win, 
                 gc, 
                 (win_width-XTextWidth (font_info, (char*)str_1, 
                 wslen (str_1)))/2,
                 y_offset + font_height,
                 (char*)str_1, 
                 wcslen (str_1));

     XDrawString (dpy, 
                 win, 
                 gc, 
                 (win_width-XTextWidth (font_info, (char*)str_2, 
                 wslen (str_2)))/2,
                 y_offset + (2*font_height),
                 (char*)str_2, 
                 wcslen (str_2));

     XDrawString (dpy, 
                 win, 
                 gc, 
                 x_offset,     
                 y_offset + font_height,
                 (char*)str_4, 
                 wcslen (str_4));
     
     /* Copy numbers into string variables  */
    wprintf (cd_buff, L"Height = %d pixels", win_height);

    /* To center strings vertically, we place the first string
     * so that the top of it is two font heights above the center
     * of the window; since the baseline of the string is what
     * we need to locate for XDraString and the baseline is
     * one font info -> ascent below the top of the character,
     * the final offset of the origin up from the center of 
     * the window is one font_height/2 + one descent 
     * */

    XDrawString (dpy,
                 win,
                 gc,
                 x_offset,     
                 y_offset + (2*font_height),
                 (char*)cd_buff,
                 wcslen (cd_buff));
    wprintf (cd_buff, L"Width = %d pixels", win_width);
    XDrawString (dpy,
                 win,
                 gc,
                 x_offset,
                 y_offset + 20 + (2*font_height),
                 (char*)cd_buff,
                 wcslen (cd_buff));
    wprintf (cd_buff, L"Depth = %d", DefaultDepth (dpy,scrn));
    XDrawString (dpy,
                 win,
                 gc,
                 x_offset,
                 y_offset + 40 + (2*font_height),
                 (char*)cd_buff,
                 wcslen (cd_buff));
#endif
}	/* end of function place_text (Window, GC, unsigned int, unsigned int) */


/* 
 * ===  FUNCTION  ====================================================
 *         Name:  place_graphics (Window win, GC gc, 
 *                                unsigned int width, unsigned int height)
 *  Description:  
 * ===================================================================
 */
    void
place_graphics (Window win, GC gc,
                unsigned int win_width, unsigned int win_height)
{
    int x, y, width, height;

    height = win_height / 2;
    width  = win_width / 4;
    x = win_width / 2 - width / 2;  /* Center  */
    y = win_height / 2 - height / 2;
    XDrawRectangle (dpy, win, gc, x, y, width, height);

}	/* end of function place_graphics (Window, GC, unsigned int, unsigned int)*/


/* 
 * ===  FUNCTION  ====================================================
 *         Name:  TooSmall (Window win, GC gc, XFontStruct *font_into)
 *  Description:  
 * ===================================================================
 */
    void
TooSmall (Window win, GC gc, XFontStruct *font_info)
{
    char *str = (char*)"Too small";
    int  y_offset, x_offset;
    y_offset = font_info->ascent + 2;
    x_offset = 2;
    
    /* Out put text centered on each line */
    XDrawString (dpy,
                 win,
                 gc,
                 x_offset,
                 y_offset,
                 str,
                 strlen (str));
}	/* -----  end of function TooSmall (Window win, GC gc, XFontStruct *font_into)  ----- */

/* 
 * ===  FUNCTION  ====================================================
 *         Name:  main (int argc, char **argv)
 *  Description:  Program entry point 
 * ===================================================================
 */
#ifdef _TEST_
    int
main (int argc, char **argv)
#else
    int
run_systemInfo ()
#endif
{
    Window        win;
    uint32_t      width, height;    /* window size  */
    int           x, y;             /* Window position  */
    uint32_t      border_width = 4; /* 4 pixel border width */
    uint32_t      disp_width, disp_height;
    char          *win_name = (char*)"Basic Window X11 MIT R7";
    char          *icon_name = (char*)"basicwin";
    Pixmap        icon_pixmap;
    XSizeHints    *size_hints;
    XWMHints      *wm_hints;
    XIconSize     *size_list;
    XClassHint    *class_hints;
    XTextProperty winName, iconName;
    XEvent        ev;
    GC            gc, gca[NUMLINES];
    XFontStruct   *font_info;
    int           count, done = 0, win_size = 0;

    if (!(size_hints = XAllocSizeHints())) {
        fprintf (stderr, "%s: failed to allocating 'XAllocSizeHints' memory\n", 
                prName);
        exit (-1);
    }
    if (!(wm_hints = XAllocWMHints())) {
        fprintf (stderr, "%s: failed to allocate 'XAllocWMHints' memory\n", 
                prName);
        exit (-1);
    }
    if (!(class_hints = XAllocClassHint())) {
        fprintf (stderr, "%s: failed to allocate 'XAllocClassHint' memory\n", 
                prName);
        exit (-1);
    }
    /* Connect to X server  */
    if ((dpy = XOpenDisplay (NIL)) == NULL) {
        (void) fprintf (stderr, "%s: cannot connect to X server %s\n",
                prName, XDisplayName (NIL));
        exit (-1);
    }
    
    /* Get screen size from display structure macro */
    scrn = DefaultScreen (dpy);
    disp_width = DisplayWidth (dpy, scrn);
    disp_height= DisplayHeight (dpy, scrn);

    /* Note that in a real application, x and y would default
     * to 0 but would be settable from the command line or resource
     * database
     * */
    x = y = 0;
    /* size window with enough room for text */
    width = disp_width / 2; /* This will create full width! For small scrn /3 */
    height= disp_height;    /* Full height for half height use /4;  */

    /* create operque window  */
    win = XCreateSimpleWindow (dpy, 
                               RootWindow (dpy, scrn),
                               x, y,
                               width,
                               height,
                               border_width, 
                               WhitePixel (dpy, scrn),
                               BlackPixel (dpy, scrn) );

    /* Get available icon size from window manager */
    if (XGetIconSizes (dpy, RootWindow (dpy, scrn), &size_list, &count) == 0)
    {
        (void) fprintf (stderr, 
           "%s: Window manager did not set icon sizes - using default\n", 
                prName);
    }else {
        printf ("Setting default sizes\n");
        /* A real application would search through size list
         * here to find an acceptable icon size and then create a 
         * pixmap of that size this requires that the application
         * have data for several sizes of icons
         * */        
    }
    /* Create pixmap of depth 1 (bitmap) for an icon */
    icon_pixmap = XCreateBitmapFromData (dpy,
                                         win,
                                         (char*)Penguin_bits,  // icon_bitmap_bits,
                                         Penguin_width,
                                         Penguin_height);  

     /* Need graphic context in window  */
     gc = XCreateGC (dpy, win, 0, NULL);

    /* Set size hints for Window Manager; the window manager may
     * override these settings.
     * Note that in a real application, if size or position were
     * set by the user, the flags would USPosition and USSize and these
     * would  override the window manager's preferences for 
     * this window
     *
     * x, y, width, and height hints are now taken from the actual
     * settings of the window when mapped; note that PPosition
     * and PSize must specified anyway
     * */
    size_hints->flags = PPosition | PSize | PMinSize;
    size_hints->min_width = 300;
    size_hints->min_height= 200;

    Atom wmDeleteMsg = XInternAtom (dpy, "WM_DELETE_WINDOW", False);
    XSetWMProtocols (dpy, win, &wmDeleteMsg, 1);

    Atom win_icon = XInternAtom (dpy, "_NET_WM_ICON", False);
    Atom cardinal = XInternAtom (dpy, "CARDINAL", False);

    /* These calls store window_name and icon_name into
     * XTextProperty structures and set their other fields property 
     * */
    if (XStringListToTextProperty (&win_name, 1, &winName) == 0) {
        fprintf (stderr, "%s: structure allocation for winName failed\n",
                prName);
        // exit (-1);
    }
    if (XStringListToTextProperty (&icon_name, 1, &iconName) == 0)
    {
        fprintf (stderr, "%s: Structure allocation iconName failed\n", 
                 prName);
        // exit (-1);
    }
    wm_hints->initial_state = NormalState;
    wm_hints->input = True;
    wm_hints->icon_pixmap = icon_pixmap;
    wm_hints->flags = StateHint | IconPixmapHint | InputHint;
    class_hints->res_name = prName;
    class_hints->res_class = (char*)"SysIno win";

    XSetWMProperties (dpy, 
                      win,
                      &winName,
                      &iconName,
                      &argv,
                      argc,
                      size_hints,
                      wm_hints,
                      class_hints);

    XSetWMIconName (dpy, win, &iconName);

    /* Try to set application icon */
    int length = 2 + 16 * 16 + 2 + 32 * 32;
    XChangeProperty (dpy, 
                     win, 
                     win_icon, 
                     cardinal, 32,
                     PropModeReplace,
                     (const unsigned char*) buffer, length); 

    /* Select Event type wanted */
    XSelectInput (dpy,
                  win,
                  ExposureMask | 
                  KeyPressMask | 
                  ButtonPressMask |
                  StructureNotifyMask);

    /* Now load fonts */
    loadfont (&font_info);

    /* Create GC for text and drawings  */
    getGC (win, &gc, font_info);
    
    /* Call for multiple GC created for LINEs */
    set_dashes (dpy, win, gca);

    /*  Display window  */
    XMapWindow (dpy, win);

    /*  Get events, use first to display text and graphics */
    while (done == 0) 
    {
        XNextEvent (dpy, &ev);
        switch (ev.type)
        {
            case Expose: /* Unless this is the last contiguous expose */
                if (ev.xexpose.count != 0)
                    break;
                /*  if window too small to use  */
                if (win_size == TOO_SMALL)
                    TooSmall (win, gc, font_info);
                else {
                    /*  Place text in window */
                    place_header_text (win, gc, font_info, width, height);
                   
                   /* Place graphics in window  */
                    //place_graphics (win, gc, width, height);
                    display_sysinfo (dpy, win, scrn, gc, width, height);
                    //draw_lines (dpy, win, width, height, gca);
                }
                break;
            case ConfigureNotify:
                /* Window has been resized; change width and height
                 * to send to place_text and place_graphics in next
                 * expose
                 * */
                if ((width < size_hints->min_width) ||
                    (height < size_hints->min_height))
                    win_size = TOO_SMALL;
                else
                    win_size = BIG_ENOUGH;
                break;
            case ButtonPress:
                /* Tricke down into KeyPress (no break)  */
                // draw_lines (dpy, win, width, height, gca);
            case KeyPress:
                //XUnloadFont (dpy, font_info->fid);
                //XFreeGC (dpy, gc);
                //XCloseDisplay (dpy);
                //exit (1);
            case ClientMessage:
                if (ev.xclient.data.l[0] == wmDeleteMsg) {
                    printf ("Shutting down!\n");
                    done = run_OkCancel ();
                }
            default:
                /* All events selected by StructureNotifyMask
                 * except ConfigureNotify are thrown here,
                 * since nothing is done with them */
                break;
        } /*  End of switch */
    }  /*  End of while loop */   
    printf ("All resouces free!\n");
    XUnloadFont (dpy, font_info->fid);
    XFreeGC (dpy, gc);
    XDestroyWindow (dpy, win);
    XCloseDisplay (dpy);
    return EXIT_SUCCESS;
}		/* -----  end of function main (int argc, char **argv)  ----- */


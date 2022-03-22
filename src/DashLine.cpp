/*
 * ========================================================================
 *
 *       Filename:  ch05_DashLine.c
 *
 *    Description:  Dash List and Offset
 *                  The dashes member of XGCValues can only be directly set to 
 *                  a single, nonzero value specifying the length in pixels 
 *                  of both the dashes and the gaps. More complicated patterns 
 *                  can be set only with XSetDashes().
 *                  In XSetDashes(), the dash_list argument is a real list, 
 *                  with each value representing the length of a single dash or
 *                  gap in the line. The initial and alternating members of 
 *                  dash_list are the length of the even dashes; the others 
 *                  are the odd dashes (gaps). All members must be nonzero. 
 *                  The length of the dash_list is also an argument to 
 *                  XSetDashes(). The dashes element of XGCValues is 
 *                  equivalent to specifying a two-member dash_list [N, N] in 
 *                  XSetDashes(), where N is the single value specified 
 *                  in XGCValues.dashes.
 *                  The dash_offset for XSetDashes() defines the phase of the 
 *                  pattern, specifying how many pixels into the pattern the 
 *                  line should actually begin. Figure 5-6 shows the same line 
 *                  drawn with and without offset to demonstrate its effect.
 *                  Example 5-5 shows a code segment that creates and sets the 
 *                  line dashes of five GCs. Figure 5-6 shows the lines that 
 *                  result from drawing with these GCs.
 *
 *        Version:  1.0
 *        Created:  27/05/20 18:06:14
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * =========================================================================
 */

#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#pragma GCC diagnostic ignored "-Wpointer-sign"

/* 
 * ===  FUNCTION  ====================================================
 *         Name:  set_dashes (GC gca[])
 *  Description:  
 * ===================================================================
 */
    void
set_dashes (Display *dpy, Window win, GC gc[])
{
    XGCValues  gcv;
    int        i;
    int        dash_list_length[] = {
                    DOTTED_LIST_LENGTH,
                    DOT_DASHED_LIST_LENGTH,
                    SHORT_DASHED_LIST_LENGTH,
                    LONG_DASHED_LIST_LENGTH,
                    ODD_DASHED_LIST_LENGTH
    };

    /* At least one element in each list */
    unsigned char dotted [DOTTED_LIST_LENGTH] = {3, 1};
    unsigned char dot_dashed [DOT_DASHED_LIST_LENGTH] = {3,3,3,1};
    unsigned char short_dashed [SHORT_DASHED_LIST_LENGTH] = {4,4};
    unsigned char long_dashed [LONG_DASHED_LIST_LENGTH] = {4, 7};
    unsigned char odd_dashed [ODD_DASHED_LIST_LENGTH] = {1,2,3};

    unsigned char *dash_list [] = {
                                    dotted,
                                    dot_dashed,
                                    short_dashed,
                                    long_dashed,
                                    odd_dashed,
                                };
    int dash_offset = 0;

    gcv.line_style = GCLineStyle;
    unsigned long umask;
    umask = GCForeground | GCBackground;

    for (i=0; i<NUMLINES; i++) {
          gc[i]  =  XCreateGC (dpy,
                             win,
                             umask, &gcv);

        XSetDashes (dpy, gc[i], dash_offset,
                   (char*)dash_list[i], dash_list_length[i]);
        printf ("GC created %d\n", i);
    }
}       /* -----  end of function set_dashes (GC gca[])  ----- */

/* 
 * ===  FUNCTION  ====================================================
 *         Name:  draw_lines (Window win, unsigned int width, unsigned int height)
 *  Description:  
 * ===================================================================
 */
    void
draw_lines (Display *dpy, Window win,
        uint32_t width, uint32_t height, GC gc[])
{
    int i;

    for (i=0; NUMLINES; i++) {
        XDrawLine (dpy, win, gc[i],
                (width / 4),        /* x1 */
                (40 + (10 * i)),    /* y1 */
                (3  * (width/4)),   /* x2 */
                (40 + (10 * i)));   /* y2 */

        printf ("Draw line  %d\n", i);
    }
} /* end of function draw_lines (Window, int width, int height)  */

/* 
 * ===  FUNCTION  ====================================================
 *         Name:  set_line_attributes (GC gc)
 *  Description:  Example of Setting Line Characteristics
 *                Example 5-6 demonstrates how to set the line characteristics 
 *                with XSetLineAttributes(). This routine and XSetDashes() 
 *                (which sets dashes, demonstrated in Example 5-5) 
 *                are the only ways to set line characteristics, other 
 *                than with XCreateGC() or XChangeGC().
 *
 *                http://csweb.cs.wfu.edu/~torgerse/Kokua/Irix_6.5.21_doc_cd/usr/share/Insight/library/SGI_bookshelves/SGI_Developer/books/XLib_PG/sgi_html/ch05.html
 * ===================================================================
 */
    void
set_line_attributes (Display *dpy, GC gc)
{
    uint32_t line_width = 3; /* 0 would be fast line of width 1 */
    int line_style = LineSolid;  /* LineOnOffDash or LineDoubleDash */
    int cap_style = CapRound;    /* CapNotLast, CapButt CapProjecting */
    int join_style = JoinRound;  /* JoinNitter or JoinBevel */

    XSetLineAttributes (dpy, 
                        gc, 
                        line_width,
                        line_style,
                        cap_style,
                        join_style);
}		/* -----  end of function set_line_attributes (GC gc)  ----- */


/* 
 * ===  FUNCTION  ====================================================
 *         Name:  Changing_Window_attribute_existing_window
 *  Description:  If the window already exists, you can change those 
 *                same attributes with the procedure shown in Example 4-3.
 *                Table 4-2. Attributes that can be Set Individually
 *
 *               Attribute
 *
 *               Routine for Setting It=
 *               background_pixmap
 *               XSetWindowBackgroundPixmap()
 *               background_pixel
 *               XSetWindowBackground()
 *               border_pixmap
 *               XSetWindowBorderPixmap()
 *               border_pixel
 *               XSetWindowBorder()
 *               event_mask()
 *               XSelectInput()
 *               colormap
 *               XSetWindowColormap()
 *               cursor
 *               XDefineCursor() or XUndefineCursor()
 *
 *               Settable Attributes
 *
 *               The sections that follow describe the options and default 
 *               values for each member of the XSetWindowAttributes structure. 
 *               The attributes control a wide variety of ways for a window to 
 *               act. They can be grouped loosely to help you understand when 
 *               you might want to set each attribute.
 *
 *               One group of attributes controls the appearance of a window. 
 *               These are background_pixel, background_pixmap, border_pixel, 
 *               border_ pixmap, colormap, and cursor. Most clients will set 
 *               the border, background, and cursor but use the default colormap *
 *               A second group is provided to allow clients to improve their 
 *               redrawing performance under certain conditions. 
 *               These are backing_pixel, backing_planes, backing_store, 
 *               bit_gravity, and save_under. These attributes do not affect 
 *               the appearance or operation of a client. It is advisable to 
 *               consider bit_gravity when designing a client, but the code 
 *               for using these attributes can be added after a client's 
 *               functionality is complete.
 *
 *               The event_mask and do_not_propagate_mask attributes control 
 *               the selection and propagation of events. These attributes are 
 *               described briefly in this chapter but also in much more detail 
 *               in Chapter 8, “Events”
 *
 *               The win_gravity attribute provides a means for relocating a 
 *               window automatically when its parent is resized. 
 *               Applications can take advantage of this feature to simplify 
 *               the code that positions their subwindows when they are resized.
 *
 *               The override_redirect attribute controls whether requests to 
 *               map or reconfigure the window can be intercepted by the window 
 *               manager. override_redirect is meant to be set for the most 
 *               temporary types of windows such as pop-up menus. In practice, 
 *               this attribute only affects the top-level windows of an 
 *               application (all children of the root window).
 *
 *               As described in Chapter 2, there are two window classes: 
 *               InputOutput and InputOnly. The class of a window is specified 
 *               in the call to XCreateWindow(), or is InputOutput if the 
 *               window is created with XCreateSimpleWindow().
 *
 *               InputOutput windows have all of the attributes described in 
 *               the sections below. InputOnly windows have only the following 
 *
 *               subset of attributes:
 *
 *                   win_gravity
 *                   event_mask
 *                   do_not_propagate_mask
 *                   override_redirect
 *                   cursor
 *                   
 *               Any attempt to set attributes other than these five on an 
 *               InputOnly window will cause an X protocol error (BadMatch).
 * ===================================================================
 */
    void
Changing_Window_attribute_existing_window (Display *dpy, Window win)
{
    XSetWindowAttributes setwinattr;
    unsigned long valuemask;

    /* (Must open display, create window) */
    valuemask = CWBackPixel | CWBorderPixel;

    setwinattr.background_pixel = WhitePixel(dpy, DefaultScreen (dpy));

    setwinattr.border_pixel = BlackPixel(dpy, DefaultScreen (dpy));

    XChangeWindowAttributes(dpy, win, valuemask, &setwinattr);
}	/* -  end of function Changing_Window_attribute_existing_window  -- */

/* 
 * ===  FUNCTION  ====================================================
 *         Name:  Setting_Window_attributes_Creating_window
 *  Description:  To set the window attributes, you need to set the elements 
 *                of the XSetWindowAttributes structure to the desired values 
 *                and then set a valuemask argument that represents which 
 *                members are to be changed in the server's internal 
 *                structure. A symbol specifying each member to be changed is 
 *                combined with the bitwise OR operator (|). These symbols 
 *                are shown in Table 4-1. They begin with the letters CW 
 *                (“Create Window” or “Change Window”) because the routines 
 *                they are used in have those capital letters in their names.
 *                Table 4-1. Window Attribute Mask Symbols
 *
 *               Member                     Flag                   Bit
 *
 *               background_pixmap       CWBackPixmap               0
 *               background_pixel        CWBackPixel                1
 *               border_pixmap           CWBorderPixmap             2
 *               border_pixel            CWBorderPixel              3
 *               bit_gravity             CWBitGravity               4
 *               win_gravity             CWWinGravity               5
 *               backing_store           CWBackingStore             6
 *               backing_planes          CWBackingPlanes            7
 *               backing_pixel           CWBackingPixel             8
 *               override_redirect       CWOverrideRedirect         9
 *               save_under              CWSaveUnder               10
 *               event_mask              CWEventMask               11
 *               do_not_propagate_mask   CWDontPropagate           12
 *               colormap                CWColormap                13
 *               cursor                  CWCursor                  14
 * =========================================================================
 */

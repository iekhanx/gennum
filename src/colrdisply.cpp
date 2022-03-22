/*
 * ========================================================================
 *
 *       Filename:  colrdisply.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/12/21 13:30:44
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * =========================================================================
 */
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <cstdint>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "common.h"

#define _TEST_

extern int argc;
extern char *argv[];

#if true //Make it true to set ResizeRedirectMask and false to disable.
    #define Masks KeyPressMask|ResizeRedirectMask
#else
    #define Masks KeyPressMask
#endif
#ifndef _TEST_
    int main(int argc, char **argv)  {
#else
    int run_graphic_window ()  {
#endif        
    uint32_t RDM=0;
    uint16_t i=0;
    bool RunLoop=true;
    char *win_name = (char*)"This Program Source Codes found on Internet site who wrote? Unknown person....   Press spacebar to EXIT";
    char *icon_name= (char*)"RandomColor";
    XTextProperty  winName, iconName;

    XSizeHints    *size_hints;
    XWMHints      *wm_hints;
    XClassHint    *class_hints;

    if (!(size_hints = XAllocSizeHints())) {
        fprintf (stderr, "%s: failed to allocating 'XAllocSizeHints' memory\n",
                argv[0]);
        exit (EXIT_FAILURE);
    }
    if (!(wm_hints = XAllocWMHints())) {
        fprintf (stderr, "%s: failed to allocate 'XAllocWMHints' memory\n",
                argv[0]);
        exit (EXIT_FAILURE);
    }
    if (!(class_hints = XAllocClassHint())) {
        fprintf (stderr, "%s: failed to allocate 'XAllocClassHint' memory\n",
                argv[0]);
        exit (EXIT_FAILURE);
    }
    if (XStringListToTextProperty (&win_name, 1, &winName) == 0) {
        fprintf (stderr, "%s: structure allocation for winName failed\n",
                argv[0]);
         exit (EXIT_FAILURE);
    }
    if (XStringListToTextProperty (&icon_name, 1, &iconName) == 0)
    {
        fprintf (stderr, "%s: Structure allocation iconName failed\n",
                 argv[0]);
         exit (EXIT_FAILURE);
    }

    Display* XDisplay=XOpenDisplay(0);//Create a display
    uint32_t width,height;            // IK added
    width = DisplayWidth (XDisplay, DefaultScreen (XDisplay));
    height= DisplayHeight(XDisplay, DefaultScreen (XDisplay));
    Window XWindow=XCreateSimpleWindow(XDisplay,
                                       DefaultRootWindow(XDisplay),
                                       0,0,
                                       width, height,
                                       0,0,0); //Create a Window

    size_hints->flags = PPosition | PSize | PMinSize;
    size_hints->min_width = 300;
    size_hints->min_height= 200;
    wm_hints->initial_state = NormalState;
    wm_hints->input = True;
    //wm_hints->icon_pixmap = icon_pixmap;
    wm_hints->flags = StateHint | IconPixmapHint | InputHint;
    class_hints->res_name = argv[0];
    class_hints->res_class = (char*)"RandomColor";
    XSetWMProperties (XDisplay,
                      XWindow,
                      &winName,
                      &iconName,
                      argv,
                      argc,
                      size_hints,
                      wm_hints,
                      class_hints);

    XSetWMIconName (XDisplay, XWindow, &iconName);

    Atom wmDeleteMsg = XInternAtom (XDisplay, "WM_DELETE_WINDOW", False);
    XSetWMProtocols (XDisplay, XWindow, &wmDeleteMsg, 1);

    XMapWindow(XDisplay,XWindow);//Make the Window visible
    GC XGraphicCTX = XCreateGC(XDisplay,XWindow,0,0);//Create a Graphics Context
    //v Wait for a MapNotify XEvent for next commands
    XSelectInput(XDisplay,XWindow,StructureNotifyMask);
    while(1){
        XEvent e;
        XNextEvent(XDisplay,&e);
        if(e.type==MapNotify)break;
    }
    XSelectInput(XDisplay,XWindow,Masks); //Here is part of the magic error
    while(RunLoop){
        while(XPending(XDisplay)){//Get key changes
            XEvent Event;
            XNextEvent(XDisplay,&Event);
            if(Event.type==KeyPress){
                RunLoop=false;
            } else if (Event.xclient.data.l[0] == wmDeleteMsg) {
                RunLoop = run_OkCancel ();
                XDestroyWindow (XDisplay, XWindow);
                XFreeGC (XDisplay, XGraphicCTX);
                XFlush (XDisplay);                
                printf ("All resources freed\n");
                return (0);
            }
        }

        for(i=0;i<4096;i++){
            RDM=(RDM+1841)*9245;    //Not perfect but good enough
            XSetForeground(XDisplay,XGraphicCTX,RDM&0xFFFFFF);
            
            RDM=(RDM+1841)*9245;    //Not perfect but good enough
            XFillRectangle(XDisplay,XWindow,XGraphicCTX,RDM&0xFFFF,
                           (RDM>>16),64,64);
        }
        //XDestroyWindow (XDisplay, XWindow);
        //XFreeGC (XDisplay, XGraphicCTX);
        XFlush(XDisplay);

        usleep(16667); //AHHH there is 666!
    }
    return 0;
}


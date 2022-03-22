/*
 * ========================================================================
 *
 *       Filename:  xpmTest.c
 *
 *    Description:  Testing XPm usage
 *
 *        Version:  1.0
 *        Created:  31/05/20 17:50:24
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * =========================================================================
 */
#include<stdlib.h>
#include<X11/Xlib.h>
#include<X11/xpm.h>

#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <dirent.h>
#include <string.h>

#include "common.h"

/* #define _TEST_    */

#define MY_PATH "/home/imrank/gdrive/work/gennum/xpms"
#define MY_FILES "xpm"

#define FILENAME    "./xpms/monalisa.xpm"
#define FILENAME0   "./xpms/penguin.xpm"
#define FILENAME1   "./xpms/Screenshot_from_2021-11-20_16-07-08.xpm"
#define FILENAME2   "./xpms/Screenshot_from_2021-11-20_16-09-00.xpm"
#define FILENAME3   "./xpms/Screenshot_from_2021-11-20_16-10-04.xpm"
#define FILENAME4   "./xpms/Screenshot_from_2021-11-20_16-10-46.xpm"
#define FILENAME5   "./xpms/Screenshot_from_2021-11-20_16-22-53.xpm"
#define FILENAME6   "./xpms/Screenshot_from_2021-11-20_16-23-34.xpm"
#define FILENAME7   "./xpms/Screenshot_from_2021-11-20_16-25-21.xpm"
#define FILENAME8   "./xpms/Screenshot_from_2021-11-20_16-26-01.xpm"
#define FILENAME9   "./xpms/Screenshot_from_2021-11-20_16-26-30.xpm"
#define FILENAME10  "./xpms/Screenshot_from_2021-11-20_16-27-40.xpm"
#define FILENAME11  "./xpms/Screenshot_from_2021-11-20_16-44-36.xpm"
#define FILENAME12  "./xpms/Screenshot_from_2021-11-20_16-45-51.xpm"
#define FILENAME13  "./xpms/Screenshot_from_2021-11-20_16-46-17.xpm"

int argc = 0;
char *argv[0];

/* 
 * ===  FUNCTION  ====================================================
 *         Name:  directory_search (const char *path, int *nsdir, int *files)
 *  Description:  
 * ===================================================================
 */
    int
directory_search (const char *path)     
{
    DIR                *dir;
    struct dirent      *entry;
    char               spath[PATH_MAX] = {0};
    int                nsdir=0, nfiles=0;

    if (!(dir = opendir (path))) {
        perror ("opendir failed\n"); //exit (EXIT_FAILURE);
        return 0;
    }
    for (entry = readdir (dir); entry; entry = readdir (dir)) {
        sprintf (spath, "%s/%s", path, entry->d_name);

        if (entry->d_type == DT_REG) {nfiles++; /*printf ("%s\n",spath);*/ }
        if (entry->d_type == DT_DIR           &&
                (strcmp (".", entry->d_name)) &&
                (strcmp ("..", entry->d_name))) {
            (nsdir)++;
            directory_search (spath);
        }
    }
    closedir (dir);
    return nfiles;
}/* end of function directory_search(const char *, int *, int *) */

#ifdef _TEST_
    int
    main (int argc, char **argv)
#else
    int run_monalisa ()
#endif
{
  Display                   *dpy;
  Window                     win, rootw;
  XSetWindowAttributes       watt;       
  XWindowAttributes          wat;
  XImage                     *img, *peng;
  XImage                     *bk1,*bk2,*bk3,*bk4,*bk5,*bk6,*bk7,*bk8;
  XImage                     *bk9,*bk10,*bk11,*bk12,*bk13;
  XSizeHints                 *wmsize;
  XWMHints                   *wmhints;
  XClassHint                 *classhints;
  XTextProperty              winName, iconName;
  XEvent                     ev;
  GC                         gc;
  int                        scrn, done;
  char                       *win_name =(char*)"Image Display", 
                             *win_icon =(char*)"IMG";
  u_int32_t                  valuemask;
  u_int32_t                  disp_width, disp_height, x, y;

  printf ("\nTotal files counted %d\n",directory_search (MY_PATH));
  printf ("\nPlease wait loading Images ...\n");

  /* Section 1 - open the display (connect to the X server) */
  dpy = XOpenDisplay (getenv ("DISPLAY"));

  /* Section 2 - Create top level window  */
  scrn = DefaultScreen (dpy);

  /* get the Display size for the  window */
  rootw = DefaultRootWindow (dpy);
  disp_width = DisplayWidth (dpy, scrn);
  disp_height= DisplayHeight (dpy, scrn);

  /* display x y location */
  x = y =0;
  if (!(wmsize = XAllocSizeHints ())) {
        fprintf (stderr, "%s: XAllocSizeHints() memory failed!\n", argv[0]);
        exit (-1);
  }
  if (!(wmhints = XAllocWMHints ())) {
        fprintf (stderr, "%s: XAllocWMHints() memory failed!\n", argv[0]);
        exit (-1);
  }
 if (!(classhints = XAllocClassHint ())) {
        fprintf (stderr, "%s: XAlloClassHint() memory failed!\n", argv[0]);
        exit (-1);
  }

  /* set foreground color */
  watt.backing_pixel = WhitePixel (dpy, scrn);
  watt.border_pixel  = BlackPixel (dpy, scrn);
  watt.event_mask = ExposureMask | ButtonPressMask | KeyPressMask;
  
  valuemask = CWBackPixel | CWBorderPixel | CWEventMask;

  win = XCreateWindow (dpy,
                       rootw, 
                       x, y,
                       disp_width,
                       disp_height,
                       3,
                       DefaultDepth (dpy, scrn),
                       InputOutput,
                       DefaultVisual (dpy, scrn),
                       valuemask, &watt);

  /* Section 3 - Give the window manager hits */
  wmsize->flags = USPosition | USSize;
  XSetWMNormalHints (dpy, win, wmsize);
  
  wmhints->initial_state = NormalState;
  wmhints->flags = StateHint;
  XSetWMHints (dpy, win, wmhints);

  XStringListToTextProperty (&win_name, 1, &winName);
  XSetWMName (dpy, win, &winName);
  
  XStringListToTextProperty (&win_icon, 1, &iconName);
  XSetWMIconName (dpy, win, &iconName);

  XGetWindowAttributes (dpy, win, &wat);

  Atom wmDeleteMsg = XInternAtom (dpy, "WM_DELETE_WINDOW", False);
  XSetWMProtocols (dpy, win, &wmDeleteMsg, 1);

  //Atom winIcon = XInternAtom (dpy, "_NET_WM_ICON", False);
  //Atom cardinal= XInternAtom (dpy, "CARDINAL", False);

  /* Section 4 - Establish window resources  */
  /* read the XPM File for image */
  if (XpmReadFileToImage (dpy, FILENAME, &img, NULL, NULL)) {
      printf ("Error reading file: %s\n", FILENAME);
      exit (EXIT_FAILURE);
  }
  if (XpmReadFileToImage (dpy, FILENAME0, &peng, NULL, NULL)) {
      fprintf (stderr, "Error reading file %s\n", FILENAME2);
      exit (EXIT_FAILURE);
  }
  if (XpmReadFileToImage (dpy, FILENAME1, &bk1, NULL, NULL)) {
      fprintf (stderr, "Error reading file %s\n", FILENAME1);
      exit (EXIT_FAILURE);
  }
  if (XpmReadFileToImage (dpy, FILENAME2, &bk2, NULL, NULL)) {
      fprintf (stderr, "Error reading file %s\n", FILENAME2);
      exit (EXIT_FAILURE);
  }
  if (XpmReadFileToImage (dpy, FILENAME3, &bk3, NULL, NULL)) {
      fprintf (stderr, "Error reading file %s\n", FILENAME3);
      exit (EXIT_FAILURE);
  }
  if (XpmReadFileToImage (dpy, FILENAME4, &bk4, NULL, NULL)) {
      fprintf (stderr, "Error reading file %s\n", FILENAME4);
      exit (EXIT_FAILURE);
  }
  if (XpmReadFileToImage (dpy, FILENAME5, &bk5, NULL, NULL)) {
      fprintf (stderr, "Error reading file %s\n", FILENAME5);
      exit (EXIT_FAILURE);
  }
  if (XpmReadFileToImage (dpy, FILENAME6, &bk6, NULL, NULL)) {
      fprintf (stderr, "Error reading file %s\n", FILENAME6);
      exit (EXIT_FAILURE);
  }
  if (XpmReadFileToImage (dpy, FILENAME7, &bk7, NULL, NULL)) {
      fprintf (stderr, "Error reading file %s\n", FILENAME7);
      exit (EXIT_FAILURE);
  }
  if (XpmReadFileToImage (dpy, FILENAME8, &bk8, NULL, NULL)) {
      fprintf (stderr, "Error reading file %s\n", FILENAME8);
      exit (EXIT_FAILURE);
  }
  if (XpmReadFileToImage (dpy, FILENAME9, &bk9, NULL, NULL)) {
      fprintf (stderr, "Error reading file %s\n", FILENAME9);
      exit (EXIT_FAILURE);
  }
  if (XpmReadFileToImage (dpy, FILENAME10, &bk10, NULL, NULL)) {
      fprintf (stderr, "Error reading file %s\n", FILENAME10);
      exit (EXIT_FAILURE);
  }
  if (XpmReadFileToImage (dpy, FILENAME11, &bk11, NULL, NULL)) {
      fprintf (stderr, "Error reading file %s\n", FILENAME11);
      exit (EXIT_FAILURE);
  }
  if (XpmReadFileToImage (dpy, FILENAME12, &bk12, NULL, NULL)) {
      fprintf (stderr, "Error reading file %s\n", FILENAME12);
      exit (EXIT_FAILURE);
  }
  if (XpmReadFileToImage (dpy, FILENAME13, &bk13, NULL, NULL)) {
      fprintf (stderr, "Error reading file %s\n", FILENAME13);
      exit (EXIT_FAILURE);
  }
  classhints->res_name = argv[0];
  classhints->res_class= (char*)"ImageDisp";
 
  gc = XCreateGC (dpy, win, 0, NULL);

 /*   
  XAllocNamedColor (dpy,
                    DefaultColormapOfScreen (
                    DefaultScreenOfDisplay (dpy)),
                    "black",
                    &reds,
                    &redx);  

   //Set foreground color  
  XSetForeground (dpy, gc, reds.pixel); // for the ball */
  XSetBackground (dpy, gc, BlackPixel (dpy, scrn));

  XSetWMProperties (dpy,
                    win,
                    &winName,
                    &iconName,
                    argv,
                    argc,
                    wmsize,
                    wmhints,
                    classhints);

  /* Section 5 Create the other window needed */
  /* Section 6 Select Events for each window  */
  
  /* Section 7 Map the windows                */
  XMapWindow (dpy, win);

  /* Section 8 Enter into Event loop  */
  done = 0;
  /* draw something */

  while (done == 0)
    {
        XNextEvent  (dpy, &ev);
        switch (ev.type)
        {
            case Expose:
                //XSetBackground (dpy, gc, BlackPixel (dpy, scrn));
                //XSetForeground (dpy, gc, 0x0f0f0f0f);

                XPutImage(dpy, 
                           win, 
                           gc, 
                           img, 
                           0, 0, 
                            random() % (wat.width - img->width),
                            random() % (wat.height - img->height),
                            img->width, 
                            img->height); 
                 
                 XPutImage (dpy,
                            win,
                            gc,
                            peng,
                            0, 0, 
                            random()%(wat.width - peng->width), 
                            random()%(wat.width - peng->width), 
                            peng->width,
                            peng->height);
               XPutImage (dpy,
                            win,
                            gc,
                            bk1,
                            0, 0, 
                            random()%(wat.width - bk1->width), 
                            random()%(wat.width - bk1->width), 
                            bk1->width,
                            bk1->height);
               XPutImage (dpy,
                            win,
                            gc,
                            bk2,
                            0, 0, 
                            random()%(wat.width - bk2->width), 
                            random()%(wat.width - bk2->width), 
                            bk2->width,
                            bk2->height);
               XPutImage (dpy,
                            win,
                            gc,
                            bk3,
                            0, 0, 
                            random()%(wat.width - bk3->width), 
                            random()%(wat.width - bk3->width), 
                            bk3->width,
                            bk3->height);

               XPutImage (dpy,
                            win,
                            gc,
                            bk4,
                            0, 0, 
                            random()%(wat.width - bk4->width), 
                            random()%(wat.width - bk4->width), 
                            bk4->width,
                            bk4->height);

               XPutImage (dpy,
                            win,
                            gc,
                            bk5,
                            0, 0, 
                            random()%(wat.width - bk5->width), 
                            random()%(wat.width - bk5->width), 
                            bk5->width,
                            bk5->height);
               XPutImage (dpy,
                            win,
                            gc,
                            bk6,
                            0, 0, 
                            random()%(wat.width - bk6->width), 
                            random()%(wat.width - bk6->width), 
                            bk6->width,
                            bk6->height);
               XPutImage (dpy,
                            win,
                            gc,
                            bk7,
                            0, 0, 
                            random()%(wat.width - bk7->width), 
                            random()%(wat.width - bk7->width), 
                            bk7->width,
                            bk7->height);
               XPutImage (dpy,
                            win,
                            gc,
                            bk8,
                            0, 0, 
                            random()%(wat.width - bk8->width), 
                            random()%(wat.width - bk8->width), 
                            bk8->width,
                            bk8->height);
               XPutImage (dpy,
                            win,
                            gc,
                            bk9,
                            0, 0, 
                            random()%(wat.width - bk9->width), 
                            random()%(wat.width - bk9->width), 
                            bk9->width,
                            bk9->height);
               XPutImage (dpy,
                            win,
                            gc,
                            bk10,
                            0, 0, 
                            random()%(wat.width - bk10->width), 
                            random()%(wat.width - bk10->width), 
                            bk10->width,
                            bk10->height);
               XPutImage (dpy,
                            win,
                            gc,
                            bk11,
                            0, 0, 
                            random()%(wat.width - bk11->width), 
                            random()%(wat.width - bk11->width), 
                            bk11->width,
                            bk11->height);
               XPutImage (dpy,
                            win,
                            gc,
                            bk12,
                            0, 0, 
                            random()%(wat.width - bk12->width), 
                            random()%(wat.width - bk12->width), 
                            bk12->width,
                            bk12->height);
               XPutImage (dpy,
                            win,
                            gc,
                            bk13,
                            0, 0, 
                            random()%(wat.width - bk13->width), 
                            random()%(wat.width - bk13->width), 
                            bk13->width,
                            bk13->height);

                  /* once in a while, clear all */
                  if(random() % 500 < 1)
                     XClearWindow(dpy, win);
                   
                  break;

              case ButtonPress:         break;
              case EnterNotify:         break;
              case LeaveNotify:         break;

              default:
                  break;

           }   /* End of Switch block */

              /* flush changes and sleep */
               if (ev.type == ClientMessage &&
                       ev.xclient.data.l[0] == wmDeleteMsg) {
                   printf ("\nShutting down!!!\n");
                   done = run_OkCancel (); 
               }
    } /* End of while loop */
  XUnmapWindow (dpy, win);
  printf ("\nXUnmappedWindow (dpy,win)\n");
  XFreeGC (dpy, gc);
  XDestroyWindow (dpy, win);
  printf ("XDestroyWindow (dpy, win)\n");
  XCloseDisplay (dpy);
  printf("XCloseDisplay (dpy)\n");

  return 0;
}


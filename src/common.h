/*
 * ==========================================================================
 *
 *       Filename:  common.h
 *
 *    Description:  A common header file for the system info 
 *
 *        Version:  1.0
 *        Created:  30/04/20 15:39:20
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef _COMMON_H_
#define _COMMON_H_

#include <X11/Xlib.h>
#include <X11/xpm.h>


#define MAX_VAL     31
#define NUM_FONTS   30
#define MAX_IMAGES 100

#define NUMLINES                  5
#define DOTTED_LIST_LENGTH        2
#define DOT_DASHED_LIST_LENGTH    4
#define SHORT_DASHED_LIST_LENGTH  2
#define LONG_DASHED_LIST_LENGTH   2
#define ODD_DASHED_LIST_LENGTH    3


#pragma GCC diagnostic ignored "-Wunused-variable"
typedef struct {
    Font f;
    char *name;    
} FontCache;

static struct Image {
    int used;
    XpmAttributes xAtt;
    Pixmap pixmap;
    Pixmap clipmask;
    Pixmap saved;
    int x;
    int y;
} Images[MAX_IMAGES];

struct mysetting {
    char  varName[60];
    char  varValue[4096];
};

int run_OkCancel ();
int run_systemInfo ();
int run_halverson05 ();
int run_halverson02 ();
int run_graphic_window ();
int run_prime_numbers ();
int run_Tables ();


void  get_ip_address ();
void  get_mac_address ();
void  get_hostname ();

int get_pen (Display *dpy, GC gc, XColor desired_col);
int get_pen_n (Display *dpy, GC gc, int pen_number);

int scan_environment (struct mysetting my);

/* Systems information and OS info */
void display_sysinfo (Display *dpy, Window win, int scn_num, GC gc,
        unsigned int win_width, unsigned int win_height);

/* Load given font name  */
Bool loadFont (char *fontname, FontCache fnt[], Display *dpy, GC gc, int cf);

/*  Load xpm images  */
int LoadImage (char *fname, Display *dpy, Window win, int scrn);


/* Find XPM files  */
char *FindXPMFile (char *fname);

/* Function prototype declaration */
void set_dashes (Display *dpy, Window win, GC gc[]);

void draw_lines (Display *dpy, Window win,
                unsigned int width,
                unsigned int height, GC gca[]);

void set_line_attributes (Display *dpy, GC gc);

void Changing_Window_attribute_existing_window (Display *dpy, 
             Window win);

void Setting_Window_attributes_Creating_window();

#endif     /* ------- Eof ---------*/

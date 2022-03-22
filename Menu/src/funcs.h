/*
 * ==========================================================================
 *
 *       Filename:  funcs.h
 *
 *    Description:  Funcs.h header file 
 *
 *        Version:  1.0
 *        Created:  04/11/20 22:24:56
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef _FUNCS_H_
#define _FUNCS_H_

#include <X11/Xlib.h>
#include "common.h"
#include "app.h"
#include "menubar.h"
#include "menu.h"
#include "button.h"

typedef void (*EvCallback) (Block *, XEvent *);

typedef struct Funcs Funcs;

struct Funcs {
    EvCallback configureNotify;
    EvCallback leaveNotify;
    EvCallback enterNotify;
    EvCallback expose;
    EvCallback buttonPress;
    EvCallback buttonRelease;
};

union Block {
    struct Funcs          *funcs;
    struct App            app;
    struct MenuBar        menubar;
    struct Menu           menu;
    struct Button         button;
    struct MenuBarButton  menubarbutton;
};

#endif
/* ----------------------------> end of funcs.h <----------------------- */

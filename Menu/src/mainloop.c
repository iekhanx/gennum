/*
 * ========================================================================
 *
 *       Filename:  mainloop.c
 *
 *    Description:  Xtutorial main loop function 
 *
 *        Version:  1.0
 *        Created:  25/11/20 15:23:42
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * =========================================================================
 */
#include "funcs.h"
#include "button.h"
#include "appOption.h"
#include "myMacro.h"

#define _DEBUG_

typedef struct exitInfo ExitInfo;
struct exitInfo {
	Display *dpy;
};

void exitButton(void *cbdata, XEvent *ev)
{
    UNUSED (ev);

	ExitInfo *ei = (ExitInfo*)cbdata;
	XCloseDisplay (ei->dpy);
	exit(0);
}

typedef struct HelpInfo {
	Window menuToClose;
	char *text;
} HelpInfo;

void helpButtonCB(void *cbdata, XEvent *ev){
	HelpInfo *hi = (HelpInfo*)cbdata;
	printf("you pressed %s!\n", hi->text);
	if (hi->menuToClose)
		XUnmapWindow(ev->xany.display, hi->menuToClose);
}
/* 
 * ===  FUNCTION  ====================================================
 *         Name:  setUp
 *  Description:  Create context and save in var ctxt
 * ===================================================================
 */
XContext 
setup(Display * dpy, int argc, char ** argv)
{
	static XrmOptionDescRec xrmTable[] = {
		{"-bg",   "*background",   XrmoptionSepArg, NULL},
		{"-fg",   "*foreground",   XrmoptionSepArg, NULL},
		{"-bc",   "*bordercolour", XrmoptionSepArg, NULL},
		{"-font", "*font",         XrmoptionSepArg, NULL},
	};

	Window win;
	XrmDatabase db;
	XContext ctxt;
	char * progname = "xtut15";
	ExitInfo *exitInfo;
	HelpInfo *helpInfo;
	Window *filemenuwins, *helpmenuwins, *contextmenuwins;
	Window filemenu, helpmenu, contextmenu;
	Window menubar, helpButton;


	ctxt = XUniqueContext();

	db = setupDB(dpy, xrmTable, sizeof(xrmTable)/sizeof(xrmTable[0]),
			progname, &argc, argv);

	win = newApp(progname, dpy, db, ctxt, 400, 400, argc, argv);

	exitInfo = malloc(sizeof(*exitInfo));
	exitInfo->dpy = dpy;

	helpInfo = malloc(sizeof(*helpInfo));


	filemenu = newMenu(progname, dpy,  db, ctxt, "File");

	filemenuwins = malloc(sizeof(*filemenuwins));
    
    filemenuwins[0] = newButton (progname, dpy, filemenu, db, ctxt,
                      "New", 0, 0, 80, 0, False, XnewButton, exitInfo);

    filemenuwins[1] = newButton (progname, dpy, filemenu, db, ctxt,
                      "Open", 0, 0, 80, 0, False, OpenButton, exitInfo);  

    filemenuwins[2] = newButton (progname, dpy, filemenu, db, ctxt,
                      "Save", 0, 0, 80, 0, False, msgSaveButton, exitInfo);  

    filemenuwins[3] = newButton (progname, dpy, filemenu, db, ctxt,
                    "Save As", 0, 0, 80, 0, False, msgSaveAsButton, exitInfo);

    filemenuwins[4] = newButton (progname, dpy, filemenu, db, ctxt,
                      "Export", 0, 0, 80, 0, False, ExportButton, exitInfo);  

    filemenuwins[5] = newButton (progname, dpy, filemenu, db, ctxt,
                      "Import", 0, 0, 80, 0, False, ImportButton, exitInfo);  

	filemenuwins[6] = newButton(progname, dpy, filemenu, db, ctxt, 
                       "exit", 0, 0, 80, 0, False, exitButton, exitInfo); 

	menuSetSubWins(dpy, ctxt, filemenu, filemenuwins, 7);

	contextmenu = newPieMenu(progname, dpy, db, ctxt, "contextmenu");

	setAppContextMenu(dpy, ctxt, win, contextmenu);

	contextmenuwins = malloc(sizeof(*contextmenuwins)*6);

	contextmenuwins[0]  = newButton(progname, dpy, contextmenu, db, ctxt,
			"exit", 0, 0, 20, 0, True, exitButton, exitInfo);

	helpInfo = malloc(sizeof(*helpInfo));
	helpInfo->menuToClose = contextmenu;
	helpInfo->text = "contextmenu help";

	contextmenuwins[1]  = newButton(progname, dpy, contextmenu, db, ctxt,
			"Edit", 0, 0, 20, 0, True, helpButtonCB, helpInfo);

	contextmenuwins[2]  = newButton(progname, dpy, contextmenu, db, ctxt,
			"Append", 0, 0, 20, 0, True, helpButtonCB, helpInfo);

	contextmenuwins[3]  = newButton(progname, dpy, contextmenu, db, ctxt,
			"Save", 0, 0, 20, 0, True, helpButtonCB, helpInfo);

	contextmenuwins[4]  = newButton(progname, dpy, contextmenu, db, ctxt,
			"Modify", 0, 0, 20, 0, True, helpButtonCB, helpInfo);

	contextmenuwins[5]  = newButton(progname, dpy, contextmenu, db, ctxt,
			"Delete", 0, 0, 20, 0, True, helpButtonCB, helpInfo);

	menuSetSubWins(dpy, ctxt, contextmenu, contextmenuwins, 6);

	helpInfo = malloc(sizeof(*helpInfo));
	helpmenu = newMenu(progname, dpy,  db, ctxt, "Help");
	helpInfo->menuToClose = helpmenu;
	helpInfo->text = "help menu help";
	helpmenuwins = malloc(sizeof(*helpmenuwins)*2);

	helpmenuwins[0] = newButton(progname, dpy, helpmenu, db, ctxt, 
                     "help", 0, 0, 80, 0, False, helpButtonCB, helpInfo); 

	helpmenuwins[1] = newButton(progname, dpy, helpmenu, db, ctxt, 
                     "help2", 0, 80, 80, 0, False, helpButtonCB, helpInfo);

	menuSetSubWins(dpy, ctxt, helpmenu, helpmenuwins, 2);

	menubar = newMenuBar(progname, dpy, win, db, ctxt, 
                                 "menubar", 0, 0, 400, 20);
	newMenuBarButton(progname, dpy, menubar, db, ctxt, 
                                 "Filemenu", 0, 0, 30, 0, filemenu);

	helpButton = newMenuBarButton(progname, dpy, menubar, db, ctxt,
                                 "helpmenu", 0, 0, 30, 0, helpmenu);

	setHelpButton(dpy, ctxt, menubar, helpButton, 400-80);

	setAppMenuBar(dpy, ctxt, win, menubar, 400, 20);
    /*
	{
		HelpInfo *funInfo;
		funInfo = malloc(sizeof(*funInfo));
		funInfo->menuToClose = 0;
		funInfo->text = "fun";
		newButton(progname, dpy, win, db, ctxt,
                "funbutton", 80, 80, 80, 8, True, helpButtonCB, funInfo);
	}  */

	/* okay, put the window on the screen, please */
	XMapWindow(dpy, win);

	return ctxt;
}

	/* -----  end of function setUp  ----- */

/* 
 * ===  FUNCTION  ====================================================
 *         Name:  mainloop
 *  Description:  main event processor switch loop
 * ===================================================================
 */
int 
main_loop(Display *dpy, XContext context)
{
	XEvent ev;

	/* as each event that we asked about occurs, we respond. */
	while(1){
		Block *block = NULL;
		XNextEvent(dpy, &ev);
		XFindContext(ev.xany.display, ev.xany.window, context, 
                                            (XPointer*)&block);
		switch(ev.type){
		case ConfigureNotify:
			if (block && block->funcs && block->funcs->configureNotify)
				block->funcs->configureNotify(block, &ev);
			break;
		case Expose:
			if (block && block->funcs && block->funcs->expose)
				block->funcs->expose(block, &ev);
			break;

		case EnterNotify:
			if (block && block->funcs && block->funcs->enterNotify)
				block->funcs->enterNotify(block, &ev);
			break;
		case LeaveNotify:
			if (block && block->funcs && block->funcs->leaveNotify)
				block->funcs->leaveNotify(block, &ev);
			break;
		case ButtonPress:
			if (block && block->funcs && block->funcs->buttonPress)
				block->funcs->buttonPress(block, &ev);
			break;
		case ButtonRelease:
			if (block && block->funcs && block->funcs->buttonRelease)
				block->funcs->buttonRelease(block, &ev);
			break;
		}
	}
}
		/* -----  end of function mainloop  ----- */

/* 
 * ===  FUNCTION  ====================================================
 *         Name:  main
 *  Description:  main program entry point  
 * ===================================================================
 */
int 
main(int argc, char ** argv)
{
	Display *dpy;
	XContext ctxt;

	/* First connect to the display server */
	dpy = XOpenDisplay(NULL);
	if (!dpy) {fprintf(stderr, "unable to connect to display\n");return 7;}
	ctxt = setup(dpy, argc, argv);
	return main_loop(dpy, ctxt);
}
		/* -----  end of function main  ----- */

/* ----------------------------> End of mainloop.c <------------------ */

/*
 * ========================================================================
 *
 *       Filename:  getResources.c
 *
 *    Description:  getResources.c main implementation file 
 *
 *        Version:  1.0
 *        Created:  06/11/20 19:28:02
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * =========================================================================
 */
#include "common.h"
#include "myMacro.h"

//extern char* strdup(const char*);

typedef struct FontTable FontTable;
struct FontTable {
    int nnames, max_names;
    char **names;
    XFontStruct **fonts;
};

typedef struct ColorTable ColorTable;
struct ColorTable {
    int nnames, max_names;
    char **names;
    unsigned long  *colors;
};

/* 
 * ===  FUNCTION  ====================================================
 *         Name:  XrmDatabase setupDB (Display *dpy, 
 *                                     XrmOptionDescRec *xrmTable, 
 *                                     int nCommandLineResources, 
 *                                     const char *progname, 
 *                                     int *argc, char **argv)
 *  Description:  
 * ===================================================================
 */
XrmDatabase 
setupDB (Display *dpy, XrmOptionDescRec *xrmTable, 
         int nCommandLineResources, const char *progname, 
         int *argc, char **argv)
{
    XrmDatabase db;
    char filename[256];

    XrmInitialize ();
    db = XrmGetDatabase (dpy);

    XrmParseCommand (&db, xrmTable, nCommandLineResources, 
                     progname, argc, argv);

    sprintf (filename,"%.240s.resources", progname);

    if (XrmCombineFileDatabase (filename, &db, False))  {
        printf ("Reading setting from file %s\n", filename);
    } else {
        printf ("File NOT found: %s for reading!\n", filename);
    }
    return db;
} /* end of function XrmDatabase setupDB (Display *dpy, 
     XrmOptionDescRec *xrmTable, int nCommandLineResources, 
     const char *progname, int *argc, char **argv) */


/* 
 * ===  FUNCTION  ====================================================
 *         Name:  char *getResource (Display *dpy, XrmDatabase db, 
 *                                   char *name, char *cl, char *def)
 *  Description:  return filename
 * ===================================================================
 */
char *getResource (Display *dpy, XrmDatabase db, char *name, 
                    char *cl, char *def)
{
    XrmValue    v;
    char        *type;
   // char        *strdup (const char *);

    UNUSED (dpy);           /* unused veriable */

    if (XrmGetResource (db, name, cl, &type, &v))
        return strdup (v.addr);

    return strdup (def);
} /* end of function char *getResource (Display *dpy, 
     XrmDatabase db, char *name, char *cl, char *def)  */


/* 
 * ===  FUNCTION  ====================================================
 *         Name:  unsigned long getColor (Display *dpy, XrmDatabase db, 
 *                                        char *name, char *cl, char *def)
 *  Description:  return color ID
 * ===================================================================
 */
unsigned long 
getColor (Display *dpy, XrmDatabase db, char *name, char *cl, char *def) 
{
    XrmValue   v;
    XColor     c0, c1;
    Colormap   cmap = DefaultColormap (dpy, DefaultScreen(dpy));
    char       *type;
    int        i=0;
    static ColorTable table = {0, 0, NULL, NULL};
    // extern char *strdup (char *);    
    /* 
    for (i=0; i<table.nnames; i++) {
        if (!strcmp (table.names[i], name)) {
            return table.colors[i];
        }
    }  */ 

    if (XrmGetResource (db, name, cl, &type, &v) &&
            XAllocNamedColor (dpy, cmap, v.addr, &c0, &c1)) {
    } else {
        XAllocNamedColor (dpy, cmap, def, &c0, &c1); }
#ifdef _DEBUG_
    printf ("Returning color %ld\n", c1.pixel);
#endif
    if (i== 0) {
        table.names = malloc (sizeof (*table.names));
        table.colors = malloc (sizeof (*table.colors));    
    } else if (i >= table.max_names) {
        void *tmp;
        tmp = realloc (table.names, i * 2 * sizeof (*table.names));
        if (!tmp) return c1.pixel;
        table.max_names = i * 2;
        tmp = realloc (table.colors, i * 2 * sizeof (*table.colors));
        if (!tmp)  return c1.pixel;
        table.colors = tmp;
    }
    table.colors[i] = c1.pixel;
    table.names[i] = strdup (name);
    table.nnames = i + 1;

    return c1.pixel;
} /*  end of function unsigned long getColor (Display *dpy, XrmDatabase db, char *name, char *cl, char *def) */

/* 
 * ===  FUNCTION  ====================================================
 *         Name:  XFontStruct *getFont (Display *dpy, XrmDatabase db, 
 *                                      char *name, char *cl, char *def)
 *  Description:  
 * ===================================================================
 */
XFontStruct 
*getFont (Display *dpy, XrmDatabase db, char *name, char *cl, char *def) 
{
    static FontTable  table = {0,0,NULL,NULL};
    XrmValue          v;
    char              *type;
    XFontStruct       *font = NULL; 
    int               i=0;
    //extern char       *strdup (char *);

    for (i=0; i<table.nnames; i++) {
        if (!strcmp (table.names[i], name)) {
            return table.fonts[i];
        }
    }
    if (XrmGetResource (db, name, cl, &type, &v)) {
         if (v.addr)
             font = XLoadQueryFont (dpy, v.addr);
    }     
    if (!font) {
        if (v.addr)
          fprintf (stderr, "Unable to load fonts: %s\n", v.addr);
       else
        fprintf (stderr, "Cannot load preferred font (%s:%s)\n", name, cl);
#ifdef _DEBUG_
        printf ("Loading default font: %s\n", def);
#endif

       font = XLoadQueryFont (dpy, def); 
    }

    if (i == 0) {
        table.names = malloc (4 * sizeof (*table.names));
        table.fonts = malloc (4 * sizeof (*table.fonts));   
        
    } else if (i >= table.max_names) {
        void *tmp;
        tmp = realloc (table.names, i*2*sizeof (*table.names));
        if (!tmp)  return font;
        table.max_names = i * 2;
        table.names = tmp;
        tmp = realloc (table.fonts, i*2*sizeof (*table.fonts));
        if (!tmp)  return font;
        table.fonts = tmp;
    }
    table.fonts[i] = font;
    table.names[i] = strdup (name);
    table.nnames = i + 1;

    return font;
} /* -----  end of function XFontStruct *getFont (Display *dpy, 
     XrmDatabase db, char *name, char *cl, char *def)  ----- */


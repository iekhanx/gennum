/*
 * ========================================================================
 *
 *       Filename:  gradient.c
 *
 *    Description:  Gradient.c implementatin file. 
 *
 *        Version:  1.0
 *        Created:  07/11/20 00:11:21
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * =========================================================================
 */
#include "funcs.h"
#include "gradient.h"
#define  __USE_GNU
#include <math.h>

#define min(one, two) (((one) < (two))?(one):(two))

/* 
 * ===  FUNCTION  ====================================================
 *         Name:  Pixmap createGradPixmap (Display *dpy, 
 *                                        int width, int height, 
 *                                        char *basecolor)
 *  Description:  
 * ===================================================================
 */
static Pixmap 
createGradPixmap (Display *dpy, int width, int height, 
                   char *basecolor) 
{   int          y, x =0;
    double       cosine, l2rads;
    XColor       bcolor, col2, difcol;
    Colormap     cmap = DefaultColormap (dpy, DefaultScreen(dpy));
    Pixmap       pmap;
    GC           gc = DefGC (dpy);
    Window       win = DefaultRootWindow (dpy);

    /* assuming width == 1 for this iteration */
    width = 1;

   /* l2rads = M_PIl/(height); */
    l2rads = M_PIl/(height);

    XParseColor (dpy, cmap, basecolor, &bcolor);
    difcol.red = min (bcolor.red, 0xffff-bcolor.red);
    difcol.green = min (bcolor.green, 0xffff-bcolor.green);
    difcol.blue = min (bcolor.blue, 0xffff-bcolor.blue);
    fprintf (stderr, "height %d, width %d, %s\n", height, width, basecolor);

    pmap = XCreatePixmap (dpy, win, width, height, DefaultDepth (dpy,
                                            DefaultScreen (dpy)));

    for (y=0; y < height; y++) {
        cosine = cos(l2rads * y)/2.0;
        col2.red = bcolor.red + difcol.red * cosine;
        col2.green = bcolor.green + difcol.green * cosine;
        col2.blue = bcolor.blue + difcol.blue * cosine;
        XAllocColor (dpy, cmap, &col2);
        XSetForeground (dpy, gc, col2.pixel);
        for (x=0; x < width; x++) 
            XDrawPoint (dpy, pmap, gc, x, y);
    }
    return pmap;
} /* -----  end of function Pixmap createGradPixmap (Display *dpy, int width, int height, char *basecolor)  ----- */

struct pmap {
    char     *color;
    int      width, height, count;
    Display  *dpy;
    Pixmap   pmap;
};
struct pmaptable {
    int nnames, max_names;
    struct pmap *pmaps;
};
static struct pmaptable  pmaptable = {0, 0, NULL};


/* 
 * ===  FUNCTION  ====================================================
 *         Name:  Pixmap getGradPixmap (Display *dpy, int width,
 *                                      int height, char *basecolor)
 *  Description:  
 * ===================================================================
 */
Pixmap 
getGradPixmap (Display *dpy, int width, 
               int height, char *basecolor)
{
    Pixmap       pmap;
    int          i;
    //extern char  *strdup (char *);

    for (i=0; i < pmaptable.nnames; i++) {
        if (pmaptable.pmaps[i].width == width       && 
                pmaptable.pmaps[i].height == height &&
                height && pmaptable.pmaps[i].dpy    &&
                !strcmp (pmaptable.pmaps[i].color, basecolor)) {
            pmaptable.pmaps[i].count += 1;
            return pmaptable.pmaps[i].pmap;
        }
    }
    pmap = createGradPixmap (dpy, width, height, basecolor);
    if (!pmaptable.max_names) {
        pmaptable.pmaps = realloc (pmaptable.pmaps,8*sizeof(*pmaptable.pmaps));
    } else if (pmaptable.nnames >= pmaptable.max_names) {
        void *tmp;
        tmp = realloc (pmaptable.pmaps, pmaptable.max_names *2*
                sizeof (*pmaptable.pmaps));
        if (!tmp)  return pmap;
        pmaptable.pmaps = tmp;
    }
    pmaptable.pmaps[pmaptable.nnames].width = width;
    pmaptable.pmaps[pmaptable.nnames].height = height;
    pmaptable.pmaps[pmaptable.nnames].pmap = pmap;
    pmaptable.pmaps[pmaptable.nnames].dpy = dpy;
    pmaptable.pmaps[pmaptable.nnames].color = strdup (basecolor);
    pmaptable.pmaps[pmaptable.nnames].count = 1;
    pmaptable.nnames += 1;

    return pmap;
} /* -----  end of function Pixmap getGradPixmap (Display *dpy, int width, int height, char *basecolor)  ----- */

/* 
 * ===  FUNCTION  ====================================================
 *         Name:  freePixmap (Display *dpy, int width, 
 *                            int height, char *color)
 *  Description:  
 * ===================================================================
 */
    void
freePixmap (Display *dpy, int width, 
               int height, char *color)
{
    int i;

    for (i=0; i < pmaptable.nnames; i++)
    {
        if (pmaptable.pmaps[i].width == width
                && pmaptable.pmaps[i].height == height
                && pmaptable.pmaps[i].dpy == dpy
                && !strcmp (pmaptable.pmaps[i].color, color)) {
            pmaptable.pmaps[i].count -= 1;
            if (!pmaptable.pmaps[i].count) {
                XFreePixmap (dpy, pmaptable.pmaps[i].pmap);
                pmaptable.pmaps[i].pmap =
                    pmaptable.pmaps[pmaptable.nnames].pmap;
                pmaptable.pmaps[i].width = 
                    pmaptable.pmaps[pmaptable.nnames].width;
                pmaptable.pmaps[i].height =
                    pmaptable.pmaps[pmaptable.nnames].height;
                free (pmaptable.pmaps[i].color);
                pmaptable.pmaps[i].color =
                    pmaptable.pmaps[pmaptable.nnames].color;
                pmaptable.nnames -=1;
            } 
            return;
        }
    }
} /* -----  end of function freePixmap (Display *dpy, int width, 
            int height, char *color)  ----- */
/* -----------------------> end of gradient.c <-------------------------*/

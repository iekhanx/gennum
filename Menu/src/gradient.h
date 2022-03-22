/*
 * ==========================================================================
 *
 *       Filename:  gradient.h
 *
 *    Description:  gradient.h a header file 
 *
 *        Version:  1.0
 *        Created:  04/11/20 23:00:40
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef _GRADIENT_H_
#define _GRADIENT_H_

void freePixmap (Display *dpy, int width, int height, char *color);

Pixmap getGradPixmap (Display *dpy, int width, int height, char *basecolor);

#endif
/* -----------------------> end of gradient.h <-----------------------*/

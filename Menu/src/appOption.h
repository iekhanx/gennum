/*
 * ==========================================================================
 *
 *       Filename:  appOption.h
 *
 *    Description:  Application Option header file. 
 *
 *        Version:  1.0
 *        Created:  01/12/20 16:54:39
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef _APPOPTION_H_
#define _APPOPTION_H_

void XnewButton (void *cbdata, XEvent *ev);
void OpenButton (void *cbdata, XEvent *ev);
void msgSaveButton (void *cbdata, XEvent *ev);
void msgSaveAsButton (void *cbdata, XEvent *ev);
void ExportButton (void *cbdata, XEvent *ev);
void ImportButton (void *cbdata, XEvent *ev);

#endif

/* -----------------------> End of appOption.h <------------------------ */

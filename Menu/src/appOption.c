/*
 * ========================================================================
 *
 *       Filename:  appOption.c
 *
 *    Description:  Application options implmentation. 
 *
 *        Version:  1.0
 *        Created:  01/12/20 16:36:46
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
#include "myMacro.h"

/* 
 * ===  FUNCTION  ====================================================
 *         Name:  XnewButton
 *  Description:  
 * ===================================================================
 */
    void
XnewButton (void *cbdata, XEvent *ev)  
{
    UNUSED (cbdata);
    UNUSED (ev);
    printf ("You pressed 'New'->Filemenu' button\n");  
}		/* -----  end of function XnewButton  ----- */

/* 
 * ===  FUNCTION  ====================================================
 *         Name:  OpenButton
 *  Description:  
 * ===================================================================
 */
    void
OpenButton (void *cbdata, XEvent *ev)
{
    UNUSED (cbdata);
    UNUSED (ev);
    printf ("You pressed 'Open'->Filemenu' button\n");
}		/* -----  end of function OpenButton  ----- */

/* 
 * ===  FUNCTION  ====================================================
 *         Name:  msgSave
 *  Description:  
 * ===================================================================
 */
    void
msgSaveButton (void *cbdata, XEvent *ev)
{
    UNUSED (cbdata);
    UNUSED (ev);
   printf ("You pressed 'Save'->Filemenu' button\n");
}		/* -----  end of function msgSave  ----- */

/* 
 * ===  FUNCTION  ====================================================
 *         Name:  msgSaveAs
 *  Description:  
 * ===================================================================
 */
void
msgSaveAsButton (void *cbdata, XEvent *ev)
{
    UNUSED (cbdata);
    UNUSED (ev);
    printf ("You pressed 'Save As'->Filemenu' button\n");
}		/* -----  end of function msgSaveAs  ----- */

/* 
 * ===  FUNCTION  ====================================================
 *         Name:  Export
 *  Description:  
 * ===================================================================
 */
void
ExportButton (void *cbdata, XEvent *ev)
{
    UNUSED (cbdata);
    UNUSED (ev);
   printf ("You pressed 'Export'->Filemenu' button\n");
}		/* -----  end of function Export  ----- */

/* 
 * ===  FUNCTION  ====================================================
 *         Name:  Import
 *  Description:  
 * ===================================================================
 */
    void
ImportButton (void *cbdata, XEvent *ev)
{
    UNUSED (cbdata);
    UNUSED (ev);
   printf ("You pressed 'Import'->Filemenu' button\n");
}		/* -----  end of function Import  ----- */


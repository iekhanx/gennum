/*
 * ========================================================================
 *
 *       Filename:  xc2b.c
 *
 *    Description:  implementation file. xc2b.c 
 *
 *        Version:  1.0
 *        Created:  06/11/20 23:41:30
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * =========================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>

#include "common.h"


/* 
 * ===  FUNCTION  ====================================================
 *         Name:  char *get_var (char *p)
 *
 *  Description:  To get the enviornment variable LANG or any other env vars.
 *
 *                setlocale (LC_CTYPE, get_var ("LANG");
 *                setlocale (LC_ALL, get_var ("LANG");
 *
 * ===================================================================
 */
char 
*get_var (char *p)
{
    char *var = getenv (p);
    if (var)
        return (var);
    else
        return NULL;
}		/* -----  end of function char *get_var (char *p)  ----- */

/* 
 * ===  FUNCTION  ====================================================
 *         Name:  int XChar2bLen (XChar2 *str)
 *  Description:  
 * ===================================================================
 */
int 
XChar2bLen (XChar2b *str)
{   int i = 0;
    for (i=0; str[i].byte1 || str[i].byte2; i++)
        ;    
    return i;
}		/* -----  end of function int XChar2bLen (XChar2 *str)  ----- */

/* 
 * ===  FUNCTION  ====================================================
 *         Name:  int utf8toXChar2b (XChar2b *output_r, int outsize, 
 *                                   const char *input, int inlen)
 *  Description:  
 * ===================================================================
 */
int 
utf8toXChar2b (XChar2b *output_r, int outsize, 
               const char *input, int inlen)
{   int i, j;

    for (i=0, j=0; i<inlen && j<outsize; i++)
    {
        unsigned char c = input[i];
        if (c < 128) {
            output_r[j].byte1 = 0;
            output_r[j].byte2 = c;   j++;
        } else if (c < 0xC0) {
            fprintf (stderr, "Not a UTF-8\n"); exit (32);
        } else switch (c&0xF0)
        {
            case 0xC0:
            case 0xD0:  /* two bytes 5+6=11 bits */
                if (inlen < i+1) {
                    output_r[j].byte2 = 0;
                    output_r[j].byte1 = 0; 
                    return j;
                }
                output_r[j].byte1 = (c&0x1C) >> 2;    i++;
                output_r[j].byte2 = ((c&0x3) <<6) + (input[j]&0x3F);  j++;
                break;
            case 0xE0:
                if (inlen < i+2) {
                    output_r[j].byte2 = 0;
                    output_r[j].byte1 = 0;
                    return j;
                }
                i++;
                output_r [j].byte1 = ((c&0xF) << 4) + ((input[i]&0x3C) >> 2);
                c = input[i]; i++;
                output_r [j].byte2 = ((c&0x3) << 6) + (input[i]&0x3F); j++;
                break;
            case 0xFF:
                fprintf (stderr, "Cannot translate character\n");
                exit (33);
            default:
                break;
        }
    }
    output_r[j].byte1 = 0;
    output_r[j].byte2 = 0;
    return j;
} /* -----  end of function int utf8toXChar2b (XChar2b *output_r, int outsize, const char *input, int inlen)  ----- */

/* 
 * ===  FUNCTION  ====================================================
 *         Name:  printfXc (XChar2b *str)
 *  Description:  
 * ===================================================================
 */
    void
printfXc (XChar2b *str)
{
    int i, len = XChar2bLen (str);
    char buf[4];

    for (i=0; i < len; i++)
    {
        int ch = str[i].byte1 * 256 + str[i].byte2;
        if (ch < 128) {
            fputc (ch, stdout);
        } else if (ch < (1<<11)) {
            buf[0] = 0xB | (ch >> 6);
            buf[1] = 0XB | (ch &0x3F);
            buf[2] = 0;
            fputs (buf, stdout);
        } else {
            buf[0] = 0xB | (ch >> 12);
            buf[1] = 0xB | ((ch >> 6) &0x3F);
            buf[2] = 0xB | (ch &0x3F);
            buf[3] = 0;
            fputs (buf, stdout);
        }
    }
}		/* -----  end of function printfXc (XChar2b *str)  ----- */

/* --------------------------->  end of xc2b.c <---------------------------*/


/*
 * ========================================================================
 *
 *       Filename:  octdump.cpp
 *
 *    Description:  Convert text into octal decimal value
 *
 *        Version:  1.0
 *        Created:  04/25/19 23:17:40
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 *        Purpose:  This program types a file to the screen.
 *                  It displays the octal equivalent of each
 *                  character
 *============================================================================*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "octdump.h"

#ifdef __TEST__
int
main(int argv, char *argc[])
{
   if( argv != 2 )
   {
      printf("\n\nOops!  Proper usage is:");
      printf("\n\n%s in_file ", argc[0]);
      printf("\n\nOriginal file will be printed in Octal.");
      exit(1);
   }
#else
int open_file_to_octal_convert (const char *file)
{
#endif
   int ch;
   unsigned int line = 1;
   FILE *fp;

   /***  Open the file  ***/
#ifdef __TEST__
   if (( fp = fopen( argc[1], "r" )) == NULL )
#else
   if (( fp = fopen(file, "r" )) == NULL )
#endif
   {
#ifdef __TEST__
      printf( "\n\nOops!  Error in opening file: %s\n\n",argc[1]);
#else
      printf ("\n\nOops! Error in opening file: %s\n\n", file);
#endif
      exit(99);
   }

   printf("\n%5.5d:  ", line );

   while( (ch = fgetc( fp )) != EOF )
   {
      printf("%03o ", ch );

      if(ch == '\n')
      {
        line++;
        printf("\n%5.5d:  ", line );
      }
   }

   fclose( fp );

   return 0;
}


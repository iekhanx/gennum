/*
 * ========================================================================
 *
 *       Filename:  bindump.cpp
 *
 *    Description:  Display text equivelent to binary
 *
 *        Version:  1.0
 *        Created:  04/25/19 23:17:40
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * =========================================================================
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bindump.h"

char *char_to_binary( int );

#ifdef __TEST__
int 
main(int argv, char *argc[])
{
   if( argv != 2 )
   {
      printf("\n\nOops!  Proper usage is:");
      printf("\n\n%s in_file ", argc[0]);
      printf("\n\nOriginal file will be printed in Binary.\n");
      exit(1);
   }
#else
int
open_file_to_bin_convert (const char *file)
{
#endif
   int ch,
       letter = 0;

   unsigned int line = 1;

   FILE *fp;


   /***  Open the file  ***/
#ifdef __TEST__
   if (( fp = fopen( argc[1], "r" )) == NULL )
#else
   if ((fp = fopen (file, "r") ) == NULL ) 
#endif
   {
#ifdef __TEST__
      printf( "\n\nOops!  Error opening file: %s\n\n", argc[1]);
#else
      printf ("\n\nOops! Error opening file %s\n\n", file);
#endif
      exit(99);
   }

   printf("\n%5.5d: ", line );

   while( (ch = fgetc( fp )) != EOF )
   {

      printf("%s ", char_to_binary(ch) );

      if(ch == '\n')
      {
        line++;
        letter = 0;
        printf("\n%5.5d: ", line );
      }
      else
      if( ++letter >= 7 )            /* for formatting output */
      {
         printf("\n       ");
         letter = 0;
      }

   }
   printf ("\n");
   fclose( fp );

   return 0;
}

/* 
 * ===  FUNCTION  =======================================================
 *         Name:  char *char_to_binary (int ch)
 *  Description:  
 * ======================================================================
 */
    char 
*char_to_binary( int ch )
{
  int  ctr;
  char *binary_string;
  int  bitstatus;

  binary_string = (char*) malloc( 9 * sizeof(char) );
  for( ctr = 0; ctr < 8; ctr++)
  {
     switch( ctr )
     {
       case 0:  bitstatus = ch & 128;
                break;
       case 1:  bitstatus = ch & 64;
                break;
       case 2:  bitstatus = ch & 32;
                break;
       case 3:  bitstatus = ch & 16;
                break;
       case 4:  bitstatus = ch & 8;
                break;
       case 5:  bitstatus = ch & 4;
                break;
       case 6:  bitstatus = ch & 2;
                break;
       case 7:  bitstatus = ch & 1;
                break;
     }

     binary_string[ctr] = (bitstatus) ? '1' : '0';
   }
   binary_string[8] = 0;  /* Null Terminate */
   return( binary_string );
}		/* -----  end of function char *char_to_binary (int ch)  ----- */


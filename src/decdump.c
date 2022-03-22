/* Program:  decdump.c
 * Author:   Bradley L. Jones
 * Purpose:  This program types out a file. It displays
 *           the decimal equivalent of each character.
 *=======================================================*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//int argc = 0;
//char *argv[0];

#define _TEST_


#ifdef _TEST_
int 
main(int argc, char *argv[])
#else
int decdump ()
#endif
{
   char ch;
   unsigned int  line = 1;

   FILE *fp;

   if( argc != 2 )
   {
      printf("\n\nOops!  Proper usage is:");
      printf("\n\n%s in_file ", argv[1]);
      printf("\n\nOriginal file will be printed in HEX.");
      exit(1);
   }

   /***  Open the file  ***/
   if (( fp = fopen( argv[1], "r" )) == NULL )
   {
      printf( "\n\nOops!  Error in opening file: %s\n\n", argv[1]);
      exit(99);
   }

   printf("\n%5.5d:  ", line );

   while( (ch = fgetc( fp )) != EOF )
   {
      printf("%d ", ch );

      if(ch == '\n')
      {
        line++;
        printf("\n%5.5d:  ", line );
      }
   }

   fclose( fp );

   return 0;
}

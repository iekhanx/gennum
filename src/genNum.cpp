/*
 * ========================================================================
 *
 *       Filename:  genNum.cpp
 *
 *    Description:  Utility program for generating number at given quantity.
 *
 *        Version:  1.0
 *        Created:  04/12/19 18:26:11
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * =========================================================================
 */
#include <iostream>
#include <iomanip>
#include <ctype.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#include "adf_colors.h"
#include "myMacro.h"
#include "bindump.h"
#include "hexdump.h"
#include "octdump.h"
#include "genNum.h"
#include "techtest.h"
#include "revstr.h"

using namespace std;

extern int run_revstr_n_techarray ();

bool IS_COLOR = false;

/* 
 * ===  FUNCTION  ====================================================
 *         Name:  genNum::genNum()
 *  Description:  
 * ===================================================================
 */

genNum::genNum() 
{
    IS_COLOR = false;
    count = 0;
    maxnum = 0;
}	/* -----  end of function genNum::genNum()  ----- */

/* 
 * ===  FUNCTION  ====================================================
 *         Name:  genNum::~genNum()
 *  Description:  
 * ===================================================================
 */

genNum::~genNum()
{

}	/* -----  end of function genNum::~genNum()  ----- */

/* 
 * ===  FUNCTION  =======================================================
 *         Name:  checktty (int fd, const char *name)
 *  Description:  
 * ======================================================================
 */
    void
genNum::checktty (int fd, const char *name)
{
   if(isatty(fd) == 0)
   {
	  if(errno == EINVAL || errno == ENOTTY)
           cout << endl;
	  else 
           cout << endl;         
   }
   else { 
      IS_COLOR = true; 
    }
}		/* -----  end of function checktty (int fd, const char *name)  ----- */
/* 
 * ===  FUNCTION  =======================================================
 *         Name:  sort (int list[], int length, int num)
 *  Description:  
 * ======================================================================
 */
void
genNum::sort (int list[], int length, int num)
{
    int i, j, k, min;
    int nsort[num];

     i = j = k = min = 0;

    for(i=0; i<num; i++)
       nsort[i] = list[i];   // assign

    for(i=0; i<num; i++) {
       k = i;
       min = list[i];
           for(j=0; j<num; j++) {
          if(list[j] < min) {
            min = list[j];
                k = j;
              }
            }
           nsort[i] = min;
           list[k] = 99;
          }
      for(i=0; i<num; i++) 
           list[i] = nsort[i];

} /* -----  end of function sort (int list[], int length, int num)  ----- */

/* 
 * ===  FUNCTION  =======================================================
 *         Name:  void xsort(int list[], int length)
 *  Description:  
 * ======================================================================
 */
void
genNum::xsort(int list[], int length)
{
    int i=1;
    int j;

    while(i < length ) {
        for(j=i; list[j-1] > list[j]; j--)
        {
            int tmp = list[j];
            list[j] = list[j-1];
            list[j-1] = tmp;
        }
         i++;
    }
}	/* -----  end of function void xsort(int list[], int length)  ----- */


/* 
 * ===  FUNCTION  =======================================================
 *         Name:  int gen_multiplication_Table(const int count)
 *  Description:  
 * ======================================================================
 */
int genNum::gen_multiplication_Table(const int count)
{
    //const int size = 14;			// size of table
	int i = 0, j = 0;				// loop counter

	// system("cls");

	cout << endl
	     << count <<yellow<<" by "<<none<< count << " Multiplication Table" 
         << endl  << endl;

	cout << endl << "    |";

	for ( i=1; i <= count; i++ )				// loop through
		cout << setw(3) << i << "  ";

	cout << endl;

	for( i=0; i <= count; i++ )
		cout << "-----";						// under line headline

	// outer loop
	for( i=1; i <= count; i++ )
	{
		cout << endl << setw(3) << i << " |";

				for( j=1; j <= count; j++ )
					cout << setw(3) << i * j << "  ";
	}
	cout << endl;

    return 0;
} /*  end of function int gen_multiplication_Table(const int count)  */

/* 
 * ===  FUNCTION  =======================================================
 *         Name:  int generateNumber(int maxnum)
 *  Description:  
 * ======================================================================
 */
int 
genNum::generateNumber(int maxnum)
{
    return ((int) (rand()%maxnum +1));
}		/* -----  end of function int generateNumber(int maxnum)  ----- */

/* 
 * ===  FUNCTION  =======================================================
 *         Name:  int gen_euromillion(const int count)
 *  Description:  
 * ======================================================================
 */
int genNum::gen_euromillion(int count)
{
    cout << yellow << "Kicking off Euro Million Numbers total "<<none<< 
                           count << endl;
    int **matrix;
	int i,j;
	int row = 0;
	int max = 50;
    int col = 5;
	int ball[col];
    int str[2];
    int x = 12;
	int y = 2;
    int xcount;

	if(count >= 1)
	   row = count;

    srand(time(NULL));
	matrix = new int *[row];

	for(xcount = 0; xcount < row; xcount++) {
		matrix[xcount] = new int [col]; }

cout << "Euro Million Lottery Tickets Number                  Star Numbers" << endl;
cout << "-----------------------------------------------------------------" << endl;
cout << "                1       2       3       4       5       1       2" << endl;
cout << "=================================================================" << endl; 
	for (i=0; i<row; i++) 
	{
                for(j=0; j<col; j++)
		{
		   ball[j] = generateNumber(max);
		}
               for(y = 0; y < 2; y++)
		  str[y] = generateNumber(x);
		
	       sort(ball,  max, col);
	       sort(str, x, y);

          if(IS_COLOR) {
	       cout << setw(10) << i << ")\t" <<nred<< ball[0] <<none<< "\t" 
                    << ball[1] << "\t"<<ngreen<< ball[2]<<none<< "\t" 
                    <<nblue<< ball[3] <<none<<
                   "\t" <<yellow<< ball[4] <<none<< "\t" 
                    <<cyan<< str[0] <<none<<
				    "\t" <<magenta<< str[1]<<none <<endl;
           } else {
	       cout << setw(10) << i << ")\t"<< ball[0] << "\t" 
                    << ball[1] << "\t"<< ball[2] << "\t" << ball[3] << 
                                  "\t"<< ball[4] << "\t" << str[0]  <<
				  "\t"<< str[1] << endl;
             }
	}

	for(int j=0; j <= count; j++)
	delete[] matrix[j];
	delete[] matrix;
	matrix = 0;
 
    return 0;
}/* -----  end of function int gen_euromillion(int count, char *argv)  ----- */

/* 
 * ===  FUNCTION  =======================================================
 *         Name:  int gen_fibonacci(const int count)
 *  Description:  
 * ======================================================================
 */
int 
genNum::gen_fibonacci(const int count)
{
    cout << yellow << "Kicking off Fibonacci Numbers total "<<none<< 
        count << endl;

   int c, x, y, z;

    c = 1;
    while (1) {
        x =0;
        y =1;

      if(c == count)
         break;
      else
         c++;

        do {
            //printf("%d\n", x);
            cout <<nblue<<setw(10) << x <<none<< endl;
    
           z = x + y;
            x = y;
            y = z;
        } while (x < count);
    }
    return 0;
}		/* -----  end of function int gen_fibonacci(int count, char *argv)  ----- */

/* 
 * ===  FUNCTION  =======================================================
 *         Name:  int gen_primenum(const int count)
 *  Description:  
 * ======================================================================
 */
int 
genNum::gen_primenum(const int count) 
{
    cout << yellow << "Kicking off Prime Numbers total-> "<<none<< 
        count << endl;                          // display total counts

	const int MAX = count;						// number of prime required
	long primes[] = { 2, 3, 5 };				// First three prime defined
	long trial = 5;								// Candidate prime
	int xcount = 3;								// count of primes cound
	int found = 0;								// indicate when prime is found

	do
	{
		trial += 2;								// nex value for checking
		         								// set found indicator
		for( int i=0; i < xcount; i++ )
		{
			found = ( trial % *( primes + i )) == 0;	// true for exact;
			
			if( found )							// if division is exact
				break;							// it is not prime number
		}
		if( found == 0 )						// so we got one...
			*( primes + xcount ++ ) = trial;	// so save it in prime array

	} while( xcount < MAX );

	// out put the primes 5 to  line
	for( int i = 0; i < MAX; i++ )
	{
		if( i % 5 == 0 ) {
			cout << endl;
			cout << setw(10) << *( primes + i ); 
        }
	}
	cout << endl;
	
    return EXIT_SUCCESS;  // success 
} /* -----  end of function int gen_primenum(int count, char *argv)  ----- */

/* 
 * ===  FUNCTION  =======================================================
 *         Name:  void main_help()
 *  Description:  
 * ======================================================================
 */
void 
main_help(char *argv) 
{ 
    cout << endl;
    cout <<_0219_<< "\r\t(C) Copyright by Imran Khan 2019" <<none<< endl;
    cout <<_0220_<<"\tAll rights reserved by Author" << none<<endl<<endl;;
    cout <<white<< "Please enter at command line input to generate:"
        << endl<<endl;

    cout <<_0225_<< "-p = Prime Number                ex: Total num count = 10" 
         <<none<< endl;
    cout <<_0225_<< "-f = Fibonacci Number            ex: Total num count = 10" 
         <<none<< endl;
    cout <<_0225_<< "-e = Euro Million Number         ex: Total lines Num = 10" 
         <<none<< endl;
    cout <<_0225_<< "-m = Multiplication Table        ex: Table num 15x15   15"
         <<none<<endl;
    cout <<_0225_<< "-r = Roman Numberal              ex: Decimal to Roman  10"
         <<none<<endl;
    cout <<_0225_<< "-b = Convert file to binary      ex: -b ../text/text.txt"
        <<none<<endl;
    cout <<_0225_<< "-h = Convert file to Hex         ex: -h ../text/text.txt"
        <<none<<endl;
    cout <<_0225_<< "-o = Convert file to Octal       ex: -o ../text/text.txt"
        <<none<<endl;

    cout << "\nie. the syntax should read:\n\n";
    cout <<cyan<< "\t\t" << argv <<ngreen<< " -p 10"<<none<< endl;
    cout <<_0222_<< "\t\t"<< argv <<_0224_<< " -o ./text.txt"<< none<< endl;

    cout << endl; cout << endl;
}		/* -----  end of function void main_help()  ----- */

/* 
 * ===  FUNCTION  =======================================================
 *         Name:  int main
 *  Description:  Program entry point.
 * ======================================================================
 */
int
main (int argc, char **argv)
{
    int c;
    genNum gen;

    if (argv[1] == NULL ) // user did not provide input 
    {
        main_help (argv[0]);
        return -1;
    }

    if (argv[2] == NULL)
    {
        main_help (argv[0]);
        cout <<nred<<"Total number of count not provided " << 
        argv[0] << " "<<yellow<<argv[1] <<" ?"<< none << endl;     
        return -1;
    }

    gen.checktty(STDIN_FILENO,  "stdin");// establish color terminal exists?
	gen.checktty(STDOUT_FILENO, "stdout");
	gen.checktty(STDERR_FILENO, "stderr");

    while ((c = getopt (argc, argv, ":bpfemrho:")) != -1)
    {
        switch (c)
        {
            case 'p':
               gen.gen_primenum (atoi (argv[2]));           
                break;
            case 'f':
                gen.gen_fibonacci (atoi (argv[2]));
                break;
            case 'e':
                gen.gen_euromillion (atoi (argv[2]));
                break;
            case 'm':
                gen.gen_multiplication_Table (atoi (argv[2]));
                break;
            case 'r':
                run_revstr_n_techarray ();
                break;
            case 'b':{                
                    open_file_to_bin_convert (argv[2]);}
                break;
            case 'h': {
                   open_file_to_hex_convert (argv[2]);}
                break;
            case 'o':  {
                   open_file_to_octal_convert (argv[2]);}
                break; 
            case '?':
                if (optopt == 'c')
                 fprintf (stderr, "Option -%c requires an argument.\n", 
                            optopt);
                else
                    fprintf (stderr,
                            "Unknown option character `\\x%x'.\n",
                            optopt);
                return -1;
            default:
                abort ();
        }   
     }
    return EXIT_SUCCESS;
}	/* -----  end of function int main  ----- */


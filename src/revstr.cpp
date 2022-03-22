/*
 *   The following program develped only for the an Answer to 
 *   Technical Test for NCC Group
 *   requirement by 
 *
 *   Author Imran Khan
 *   Copyright reserved by Imran Khan 2015
 *
 *   The entire source code is an Intellectual property of Author.
 *             
 *   No Modification to the codes.
 *                
 *   User may use this binary program at their own peril.
 *
 *   Source code fully comply GNU/GPL License 2.0v 
 *
 *  History
 *  =======
 *  Created  by   Imran Khan            Date   25/04/2015  
 *
 **/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <exception>
#include <string>
#include <time.h>
#include <stdio.h>
#include <cstring>
#include <errno.h>    // for EINTR vars

#include "adf_colors.h"
#include "techtest.h"
#include "roman.h"
#include "common.h"

// #define _TEST_

using namespace std;

extern int run_roman_numerals ();
extern int run_monalisa ();

void my_sleep(unsigned msec)
{
	struct timespec req, rem;
	int err;

	req.tv_sec = msec / 1000;
	req.tv_nsec= (msec % 1000) * 1000000;
	while((req.tv_sec != 0) || (req.tv_nsec != 0)) {
		if(nanosleep(&req, &rem) == 0)
			break;
		err = errno;
		// Interrupt; continue
		if(err == EINTR) {
			req.tv_sec = rem.tv_sec;
			req.tv_nsec= rem.tv_nsec;
		}
		// EINVAL (bad time val in the tv_nsec.
	   break;
	}	   
}

string currentDateTime()
{
   time_t  now = time(0);
   tm      ltm;
   char    buf[80] = {0};

   ltm = *localtime(&now);
   strftime(buf, sizeof(buf), "%d/%m/%Y  Time: %X", &ltm);
    return buf;
}


int stringRev(char *cstr)
{
    int len = strlen(cstr);
    char swap;

    for (int 	i = 0; i < len/2; i++)
    {
        swap = cstr[i];
        cstr[i] = cstr[len-i-1];
        cstr[len-i-1] = swap;
    }
    return len;
}

int DoReverse(void) 
{
    char str[1024];
    cout << "Please Enter String. (max 1023 chars)" << endl;
    cin.getline(str, 1023);           // remember to minus for 0 terminated.
    cout << endl;
#ifdef _MONO_
    cout << "OUTPUT-Reversed: " << endl;
    stringRev(str);                   // call local function
    cout << str << endl;              // display it.
#else
    cout << ngreen << "OUTPUT-Reversed:" << none << endl << endl;
    stringRev(str);
    cout << cyan << str << none << endl;
#endif
    my_sleep(10000);
    return 0;
}

int showChoices()
{
     int nval;
     string input = "";

     while(true) {
        printf("%s",cls);
        cout << "                                    Date: "<<_0224_<< currentDateTime() <<none<< endl;
        cout <<_03_<< "                                    Time readable UK format"<< none << endl;
	cout << "                                    Further modification"<<endl;
	cout << _028_ << "                                    At Bash CommandLine #!/bin/bash" << none << endl;
	cout << _029_ << "      	                            NOW=$(date +'%m-%d-%Y') for UTC" << none << endl;
        cout <<_03_    <<"\t\t____________________" << none<<endl;
        cout <<_0192_  <<"\t\t|       MENU       |" << none<<endl;
        cout <<_06_    <<"\t\t|__________________|" << none<<endl;
        cout <<_07_    <<"\t\t|                  |" << none<<endl;
        cout <<_012_   <<"\t\t| 1 Reverse Str.   |" << none<<endl;
        cout <<_09_    <<"\t\t| 2 Speed Vector Q2|" << none<<endl;
        cout <<_010_   <<"\t\t| 3 conv Roman Num |" << none<<endl;
        cout <<_011_   <<"\t\t| 4 Display Images |" << none<<endl;
        cout <<_012_   <<"\t\t| 5 System Info    |" << none<<endl;
        cout <<_013_   <<"\t\t| 6 run Graphic Sq |" << none<<endl;
        cout <<_014_   <<"\t\t| 7 run HalverTree |" << none<<endl;
        cout <<_015_   <<"\t\t| 8 PrimeNumber 100|" << none<<endl;
        cout <<_039_   <<"\t\t| 9 Tables  30x30  |" << none<<endl;
        cout <<_029_   <<"\t\t|10                |" << none<<endl;
        cout <<_031_   <<"\t\t|11                |" << none<<endl;
        cout <<_034_   <<"\t\t|                  |" << none<<endl;
        cout <<_035_   <<"\t\t|                  |" << none<<endl;
        cout <<_036_   <<"\t\t|                  |" << none<<endl;
        cout <<_037_   <<"\t\t|                  |" << none<<endl;
        cout <<_038_   <<"\t\t|                  |" << none<<endl;
        cout <<_039_   <<"\t\t|                  |" << none<<endl;
        cout <<_040_   <<"\t\t|                  |" << none<<endl;
        cout <<_041_   <<"\t\t|                  |" << none<<endl;
        cout <<_042_   <<"\t\t|                  |" << none<<endl;
        cout <<_043_   <<"\t\t|__________________|" << none<<endl;
        cout <<_0193_  <<"\t\t|     0 Exit       |" << none<<endl;
        cout <<_044_   <<"\t\t|__________________|" << none<<endl;
        cout <<_048_   <<"\t\t                    " << none<<endl;
        cout << "Enter your Choice (1-29) [0 = Exit] ";

        getline(cin,input);
        stringstream myStream(input);   // convert string to number safely.
        if(myStream >> nval)
           break;
        cout << "\nInvalid number entered! Please try again\n" << endl;
    }

   return nval;
}
#ifdef _TEST_
int main ()
#else
int run_revstr_n_techarray ()
#endif
{    
    int choice;
    techarray tch;

    do {
        choice = showChoices();

        switch(choice)
        {
                case 1:
                        DoReverse();
                        break;

                case 2:
                       tch.Do_ArrayProcessor();
                        break;
                case 3:
                        { CRoman roman (0); cout <<cls<<endl;
                          long number = 0;
                          number = roman.getIntegerValue ();
                          if (number <= 0) {
                              cout << "Zero value entered. Exiting" << endl;
                              return 0;
                          }
                          roman.RomanNum (number, roman);
                          my_sleep (1000);
                        }
                        break;
                 case 4:
                        run_monalisa ();
                        break;
                 case 5:
                        run_systemInfo ();
                        break;
                 case 6:
                        run_graphic_window ();
                        break;
                 case 7:
                        run_halverson05 ();
                        break;
                 case 8:
                        run_prime_numbers ();
                        break;
                 case 9:
                        run_Tables ();
                        break;
                case 0:{cout << "Exiting  " << choice << endl; } 
                       printf("%s",cls);
                       break;

                default:                       
                        cout << "Invalid input or choice" << endl;
                        break;
        }
      } while (choice != 0);

   return 0;
}

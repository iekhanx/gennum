/*
 *  The following program develped only for the an Answer to 
 *  Technical Test for NCC Group
 *  requirement by 
 *  
 *  Author Imran Khan
 *  Copyright reserved by Imran Khan 2015
 *  
 *  The entire source code is an Intellectual property of Author.
 *              
 *  No Modification to the codes.
 *                 
 *  User may use this binary program at their own peril.
 *  
 *  Source code fully comply GNU/GPL License 2.0v 
 *  
 *  History
 *  =======
 *  Created  by   Imran Khan            Date   25/04/2015  
 *  
 ***/


#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <stdio.h>
#include <unistd.h>

#include "adf_colors.h"
#include "myMacro.h"
#include "techtest.h"

using namespace std;
    int 
techarray::Do_ArrayProcessor()	
{
	int a[NUM_INPUT];
    int b[NUM_INPUT];

	getArray(a);
        //sleep (1);
	getArray(b);
        sleep (1);
    PrintArray(a, b);
        sleep(1);
	MultiplyArray(a, b);
        sleep (1);
	reverseArray(a, b, NUM_INPUT);
        sleep(3);

	return 0;
}

    int 
techarray::getArray(int x[])
{
	int userInput;

	for (int count = 0; count < NUM_INPUT; count ++)
	{
	  cout <<_0224_<<"Please enter a number n hit return (total 6): "<< none;
	  cin >> userInput;
                // require sanity check here for an input, bit stronger
		if((userInput >= 1) && (userInput <= 99))		
		    x[count] = userInput;
		else
		   continue;
	}
   return userInput;
}

    int 
techarray::PrintArray(int x[], int y[])
{
    cout << _0224_ << "\nEntered Number into Array A and B:" << none << endl;
    cout << "========================================" << endl;
#ifndef _MONO_
  cout << setw(10) << "A" << ")\t" << _0244_<<
		x[0] << "\t" <<
		x[1] << "\t" <<
		x[2] << "\t" << none <<

	    "B" << ")\t" << _0154_ <<
		y[0] << "\t" <<
		y[1] << "\t" <<
		y[2] << "\t" << none << endl;
#else
  cout << setw(10) << "A" << ")\t" <<
		x[0] << "\t" <<
		x[1] << "\t" <<
		x[2] << "\t" <<
		      "B" << ")\t" <<
		y[0] << "\t" <<
		y[1] << "\t" <<
		y[2] << "\t" << endl;
#endif
  return 0;
} 
    int 
techarray::MultiplyArray(int x[], int y[])
{
   int i;
   int j[3];
#ifndef _MONO_
    cout <<_0224_<< "\nMultiplying an Array A[1] * B[1]" << none << endl;
#else
    cout << "\nMultiplying an Array A[1] * B[1]" << endl;
#endif
   cout << "==================================" << endl;
   for(i=0; i< NUM_INPUT; i++) {
       j[i] = x[i] * y[i];
   }
#ifndef _MONO_
   cout << ngreen << "Sum: "<< "\t" << j[0] << "\t" << j[1] << "\t" << j[2] << none << endl;
#else
   cout << "Sum: "<< "\t" << j[0] << "\t" << j[1] << "\t" << j[2] << endl;
#endif
#ifndef _MONO_
   cout <<_0224_<<  "\nAdding an Array sum" << none << endl;
#else
   cout << "\nAdding an Array sum" << endl;
#endif
   cout << "=====================" << endl;
#ifndef _MONO_
    cout << cyan << "\nTotal: " << j[0] + j[1] + j[2] << none << endl; 
#else
    cout << "\nTotal: " << j[0] + j[1] + j[2] << endl; 
#endif
    return 0;
}  


    int 
techarray::reverseArray(int a[], int b[], int i )
{
      	int n = NUM_INPUT;
#ifndef _MONO_
	cout  <<_0224_<< "\nThe new order No specific sequence" << none << endl;
#else
	cout  << "\nThe new order No specific sequence" << endl;
#endif

        cout  << "====================================" << endl;

	for(int i=n-1; i>=0; i--)
	{
		cout << a[i] << ' ';
		cout << b[i] << ' ';
	}
	cout << endl << endl;
    return 0;
}

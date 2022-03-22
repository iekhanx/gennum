//////////////////////////////////////////////////////////////
//
// Program : Roman number generator from an integer value
//
// Date    : 03/11/2014
//
// Test    : Input from keyboard
//////////////////////////////////////////////////////////////


#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <exception>
#include <string>
#include <cstring>
#include <unistd.h>

#include "adf_colors.h"
#include "roman.h"

// Make it pretty... using ANSI color codes coming from <adf_colors.h>
//#define cyan       "\033[1;36m"         /* 1 -> bold ;    36 -> cyan */
//#define yellow     "\033[1;33m"
#define Byellow    "\e[1;33;1m"         /* Bright Yellow     */
//#define cls        "\033[2J\033[1;1H"   /* Clear the screen */
//#define none       "\033[0m"            /* to flush the previous property */


using namespace std;

/* 
 * ===  FUNCTION  ====================================================
 *         Name:  int CRoman::getIntegerValue ()
 *  Description:  
 * ===================================================================
 */
    int 
CRoman::getIntegerValue ()
{
    string input = "";
    int nval;
    
    while(true) {
    cout << "Enter Integer number to convert in Roman numerals: ";
    getline(cin, input);
    stringstream myStream(input);   // convert string to number
    if(myStream >> nval) 
       break;
     cout << "Invalid Number." << endl;
    }
  return nval;
}	/* -----  end of function int CRoman::getIntegerValue ()  ----- */


/* 
 * ===  FUNCTION  ====================================================
 *         Name:  int CRoman::RomanNum (int number)
 *  Description:  
 * ===================================================================
 */
    void
CRoman::RomanNum (long number, CRoman roman)
{
    while (number != 0) 
    {
     
        if (number >= 1000)
        {
            roman.tailval('M', number / 1000);
            number = number - (number / 1000) * 1000;
        }
        else if (number >= 500)
        {
            if (number < (500 + 4 * 100))
            {
                roman.tailval('D', number / 500);
                number = number - (number / 500) * 500;
            }
            else
            {
                roman.headval('C','M');
                number = number - (1000-100);
            }
        }
        else if (number >= 100)
        {
            if (number < (100 + 3 * 100)) 
            {
                roman.tailval('C', number / 100);
                number = number - (number / 100) * 100;
            }
            else
            {
                roman.headval('L', 'D');
                number = number - (500 - 100);
            }
        }
        else if (number >= 50 )
        {
            if (number < (50 + 4 * 10))
            {
                roman.tailval('L', number / 50);
                number = number - (number / 50) * 50;
            }
            else
            {
                roman.headval('X','C');
                number = number - (100-10);
            }
        }
        else if (number >= 10)
        {
            if (number < (10 + 3 * 10))
            {
                roman.tailval('X', number / 10);
                number = number - (number / 10) * 10;
            }
            else
            {
                roman.headval('X','L');
                number = number - (50 - 10);
            }
        }
        else if (number >= 5)
        {
            if (number < (5 + 4 * 1))
            {
                roman.tailval('V', number / 5);
                number = number - (number / 5) * 5;
            }
            else
            {
                roman.headval('I', 'X');
                number = number - (10 - 1);
            }
        }
        else if (number >= 1)
        {
            if (number < 4)
            {
                roman.tailval('I', number / 1);
                number = number - (number / 1) * 1;
            }
            else
            {
                roman.headval('I', 'V');
                number = number - (5 - 1);
            }
        }
    }

    cout << endl; 
    cout << _048_<< "\t\tThe Hail Ceaser up yours" << none << endl;
    cout << _049_<< "\t\t************************" << none << endl;

    cout << _0224_ << "The Roman Numeral is --> ";

    for(int j=0; j < roman.i; j++)
        cout << cyan << roman.str[j];

    cout << none << endl << endl;
    sleep (5);
}	/* -----  end of function int CRoman::RomanNum (int number)  ----- */

/* 
 * ===  FUNCTION  ====================================================
 *         Name:  int main (int argc, char **argv)
 *  Description:  
 * ===================================================================
 */
#ifdef _TEST_
    int 
main (int argc, char **argv)
#else
    int
run_roman_numerals ()
#endif
{
    //UNUSED (argc);  // come from <myMacro.h>
    //UNUSED (argv);

    long number;
    CRoman roman(0);

    // Clear the screen
    cout << cls << endl;

    number = roman.getIntegerValue();

    if (number <= 0) {
        cout << "Zero value entered. Terminating" << endl;
        return 0;
    }

    roman.RomanNum (number, roman);
    return 0;
}	/* -----  end of function int main (int argc, char **argv)  ----- */

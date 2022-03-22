/*
 * ==========================================================================
 *
 *       Filename:  roman.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  16/11/21 00:29:43
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef _ROMAN_H_
#define _ROMAN_H_

#include <iostream>
using namespace std;

class CRoman {

public:
   char str[4090];
   int  i;

   CRoman(int a) : i(a) {};

   void headval(char val1, char val2)   {
      str[i++] = val1; str[i++] = val2; }

   void tailval(char val1, char val2)  {
     int j;
     for(j=0; j<val2; j++)
          str[i++] = val1;              }
   
   int getIntegerValue();
   void RomanNum (long number, CRoman roman);
};
#endif

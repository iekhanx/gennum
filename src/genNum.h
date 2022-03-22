/*
 * ==========================================================================
 *
 *       Filename:  genNum.h
 *
 *    Description: A class definition for genNum.cpp 
 *
 *        Version:  1.0
 *        Created:  12/11/21 22:08:45
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef __GENNUM_H__
#define __GENNUM_H__

#include <iostream>
#include <string>
using namespace std;

class genNum
{
    public:
        // constructor
        genNum ();

        void checktty (int fd, const char *name);
        void sort (int list[], int length, int num);
        void xsort (int list[], int length);

        int gen_multiplication_Table (const int count);
        int generateNumber (int maxnum);
        int gen_euromillion (int count);
        int gen_fibonacci (const int count);
        int gen_primenum (const int count);

        // destructor
        ~genNum ();
    private:
        bool IS_COLOR = false;
        int count;
        int maxnum;
};

#endif  /*  End of header genNum.h */

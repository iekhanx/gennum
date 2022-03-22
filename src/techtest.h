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
 *  Source code fully comply GNU/GPL License 2.0v 
 *  
 *  History
 *  =======
 *  Created  by   Imran Khan            Date   25/04/2015  
 *  
 ***/

#ifndef EXERCISE_QUESTIONS_H
#define EXERCISE_QUESTIONS_H


#define NUM_INPUT     3

//#define _TEST_

class techarray
{
public:
    techarray () {
    };   // default constructor

    // Prototype declaration of functions
    int getArray(int x[]);
    int GetArray(int x[]);
    int reverseArray(int x[], int b[], int);
    int PrintArray(int x[], int y[]);
    int MultiplyArray(int x[], int y[]);
    int Do_ArrayProcessor();

    ~techarray() {
    };  // default desturctor
private:

};

#endif


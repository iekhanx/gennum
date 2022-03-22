/*
 * ==========================================================================
 *
 *       Filename:  myMacro.h
 *
 *    Description:  A macro file and mixing C into CPP projects
 *                  To be able to call C functions from C++ (or C++ functions 
 *                  from C) you have to prevent the C++ name mangling, so that 
 *                  the linker will work properly.
 *
 *                  That is, C function int add(int, int) actually generates 
 *                  a symbol in the object file called add. But a C++ function 
 *                  int add(int, int) will generate a symbol named _Z3addii. 
 *                  And those will not link.
 *
 *                  Solution: the mixed language functions, when compiled 
 *                  in with C++ should be declared extern "C". Unfortunately 
 *                  the extern "C" declaration does not exist in C, only 
 *                  in C++.
 *                  So the standard idiom is:
 *
 *                  test1.h
 *                  =======
 *                  #ifndef _FILE_H
 *                  #define _FILE_H
 *
 *                  #ifdef __cplusplus
 *                  extern "C" {
 *                  #endif
 *                  
 *                  int add(int a, int b);
 *
 *                  #ifdef __cplusplus
 *                  }  //extern "C"
 *                  #endif
 *
 *                  #endif
 *
 *                  That way, the C code is just as before, but the C++ code 
 *                  will look for the add function using the undecoraded name, 
 *                  and all will link together.
 *
 *        Version:  1.0
 *        Created:  10/11/20 22:10:04
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef _MYMACRO_H_
#define _MYMACRO_H_

#ifdef __cplusplus
extern "C" {
#endif

    /* prototype declaration of C goes under here */
    int add (int a, int b);

#ifdef __cplusplus
}   /* Extern "C" end of */
#endif


#define DEBUG_INFO_MSG(msg) printf("%s: %s : %s(), at line: %d\n", \
                                   msg, __FILE__, __func__, __LINE__)

#define UNUSED(expr) do { (void)(expr); } while (0)

#define MIN(A,B)({\
                    typeof(A) _a = (A);\
                    typeof(B) _b = (B);\
                    _a < _b ? _a : _b;\
                    })

#endif
/*--`------------------------> end of myMacro.h<-------------------------*/

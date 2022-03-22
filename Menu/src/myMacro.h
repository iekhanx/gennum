/*
 * ==========================================================================
 *
 *       Filename:  myMacro.h
 *
 *    Description:  A macro file. 
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

#define DEBUG_INFO_MSG(msg) printf("%s: %s : %s(), at line: %d\n", \
                                   msg, __FILE__, __func__, __LINE__)

#define UNUSED(expr) do { (void)(expr); } while (0)

#endif
/*--------------------------> end of myMacro.h<---------------------------*/

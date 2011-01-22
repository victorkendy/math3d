/*
 * export.h
 *
 *  Created on: Jun 30, 2010
 *      Author: kendy
 */

#ifndef EXPORT_H_
#define EXPORT_H_

#ifdef _MSC_VER
    #ifdef MATH3D_EXPORT
        #define EXPORT __declspec(dllexport)
    #else
        #define EXPORT __declspec(dllimport)
    #endif
#else
    #define EXPORT
#endif


#endif /* EXPORT_H_ */

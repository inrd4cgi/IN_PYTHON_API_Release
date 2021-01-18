#pragma once

//DLL 分为mayaQt和Qt 5.8两种，对于PYTHON_Qt要预定义宏：INSDRIVER_PYTHON
#ifdef INSDRIVER_PYTHON
	#include <qglobal.h>
	#define INS_INTERFACE INI
	#define INS_CLIENT_PREFIX "DCC"

	#ifdef INSDRIVER_PYTHON
		#define INSDRIVER_EXPORT __declspec(dllexport)
	#else 
		#define INSDRIVER_EXPORT __declspec(dllimport)
	#endif // 
#define STREAM_VERSION 17
#else
	#include <QtCore/qglobal.h>
    #define INS_INTERFACE INS
	#define INS_CLIENT_PREFIX "IN"

	#ifndef BUILD_STATIC
		# if defined(INSDRIVER_LIB)
			#  define INSDRIVER_EXPORT Q_DECL_EXPORT
		# else
			#  define INSDRIVER_EXPORT Q_DECL_IMPORT
		# endif
	#else
		# define INSDRIVER_EXPORT
	#endif

#define STREAM_VERSION QDataStream::Qt_5_8
#endif // DEBUG
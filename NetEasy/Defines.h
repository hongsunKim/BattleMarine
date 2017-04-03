/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

#include <winsock2.h>
#include <iostream>

//
// Socket
//
#undef	INVALID_SOCKET
#define INVALID_SOCKET  (SOCKET)(~0)
#undef	SOCKET_ERROR
#define SOCKET_ERROR            (-1)

#define SOCKADDR_IN		struct sockaddr_in
#define SOCKADDR		struct sockaddr
#define IN_ADDR			struct in_addr
#define HOSTENT			struct hostent

#undef	ERRNO
#define ERRNO			errno

//
// Min, Max
//
#define MAX_INT8		127
#define MIN_INT8		-128
#define MAX_UINT8		255

#define MAX_INT16		32767
#define MIN_INT16		-32768
#define MAX_UINT16		65535

#define MAX_INT32		2147483647
#define MIN_INT32		(-MAX_INT32 - 1)
#define MAX_UINT32		4294967295U

#define MAX_INT64		LONGLONG_SUFFIX(9223372036854775807)
#define MIN_INT64		(-MAX_INT64 - LONGLONG_SUFFIX(1))
#define MAX_UINT64		ULONGLONG_SUFFIX(18446744073709551615)

//
// True, False
//
#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif

//
// Null Check
//
#ifndef NULL
#define NULL 0
#endif

#undef	isptr
#define isptr(o)				( (o) != NULL )///////

//
// Safe Delete
//
#undef SAFE_DELETE
#define SAFE_DELETE(p)			{ if(p) { delete (p); (p)=NULL; } }

#undef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p)	{ if(p) { delete[] (p); (p)=NULL; } }

#undef SAFE_DELETE_RELEASE
#define SAFE_DELETE_RELEASE(p)	{ if(p) { p->Release(); delete (p); (p)=NULL; } }

#define RAND(o)					int(double(o) * rand() / (RAND_MAX + 1.0))

//
// Output Log
//
#ifdef _DEBUG
	//#define TRACE(x)			do { std::cout << __FILE__ << " " <<__LINE__ << " "<< __func__ << ": "; std::cout << x << std::endl; } while(0)
	#define TRACE(x)			do { std::cout << __FILE__ << " " <<__LINE__ << ": "; std::cout << x << std::endl; } while(0)
#else
	#define TRACE(x)
#endif

#define OUTPUT(x)				do { std::cout << x << std::endl; } while(0)

/*
    Copyright (c) 2008 NetAllied Systems GmbH
	
    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
*/

#ifndef __COLLADA_MAYA_PLATFORM_H__
#define __COLLADA_MAYA_PLATFORM_H__


namespace COLLADAMaya
{
    /* Initial platform/compiler-related stuff to set.
    */
#define COLLADAMaya_PLATFORM_WIN32 1
#define COLLADAMaya_PLATFORM_LINUX 2
#define COLLADAMaya_PLATFORM_APPLE 3

#define COLLADAMaya_COMPILER_MSVC 1
#define COLLADAMaya_COMPILER_GNUC 2
#define COLLADAMaya_COMPILER_BORL 3

#define COLLADAMaya_ENDIAN_LITTLE 1
#define COLLADAMaya_ENDIAN_BIG 2

#define COLLADAMaya_ARCHITECTURE_32 1
#define COLLADAMaya_ARCHITECTURE_64 2

    /* Finds the compiler type and version.
    */
#if defined( _MSC_VER )
#   define COLLADAMaya_COMPILER COLLADAMaya_COMPILER_MSVC
#   define COLLADAMaya_COMP_VER _MSC_VER

#elif defined( __GNUC__ )
#   define COLLADAMaya_COMPILER COLLADAMaya_COMPILER_GNUC
#   define COLLADAMaya_COMP_VER (((__GNUC__)*100) + \
 (__GNUC_MINOR__*10) + \
 __GNUC_PATCHLEVEL__)

#elif defined( __BORLANDC__ )
#   define COLLADAMaya_COMPILER COLLADAMaya_COMPILER_BORL
#   define COLLADAMaya_COMP_VER __BCPLUSPLUS__

#else
#   pragma error "No known compiler. Abort! Abort!"

#endif

    /* ENOENT is not defined in vs2005 */
#if COLLADAMaya_COMPILER == COLLADAMaya_COMPILER_MSVC
#   if COLLADAMaya_COMP_VER >= 1400
#       define ENOENT 2
#   endif
#endif

    /* See if we can use __forceinline or if we need to use __inline instead */
#if COLLADAMaya_COMPILER == COLLADAMaya_COMPILER_MSVC
#   if COLLADAMaya_COMP_VER >= 1200
#       define FORCEINLINE __forceinline
#   endif
#elif defined(__MINGW32__)
#   if !defined(FORCEINLINE)
#       define FORCEINLINE __inline
#   endif
#else
#   define FORCEINLINE __inline
#endif

    /* Finds the current platform */

#if defined( __WIN32__ ) || defined( _WIN32 )
#   define COLLADAMaya_PLATFORM COLLADAMaya_PLATFORM_WIN32

#elif defined( __APPLE_CC__)
#   define COLLADAMaya_PLATFORM COLLADAMaya_PLATFORM_APPLE

#else
#   define COLLADAMaya_PLATFORM COLLADAMaya_PLATFORM_LINUX
#endif

    /* Find the arch type */
#if defined(__x86_64__) || defined(_M_X64)
#   define COLLADAMaya_ARCH_TYPE COLLADAMaya_ARCHITECTURE_64
#else
#   define COLLADAMaya_ARCH_TYPE COLLADAMaya_ARCHITECTURE_32
#endif

    // For generating compiler warnings - should work on any compiler
    // As a side note, if you start your message with 'Warning: ', the MSVC
    // IDE actually does catch a warning :)
#define COLLADAMaya_QUOTE_INPLACE(x) # x
#define COLLADAMaya_QUOTE(x) COLLADAMaya_QUOTE_INPLACE(x)
#define COLLADAMaya_WARN( x )  message( __FILE__ "(" QUOTE( __LINE__ ) ") : " x "\n" )

    //----------------------------------------------------------------------------
    // Windows Settings
#if COLLADAMaya_PLATFORM == COLLADAMaya_PLATFORM_WIN32

    // If we're not including this from a client build, specify that the stuff
    // should get exported. Otherwise, import it.
# if defined( COLLADAMaya_STATIC_LIB )
    // Linux compilers don't have symbol import/export directives.
#    define _CPFExport
#    define _CPFPrivate
#   else
#    if defined( COLLADAMaya_EXPORTS )
#        define _CPFExport __declspec( dllexport )
#    else
#           if defined( __MINGW32__ )
#               define _CPFExport
#           else
#            define _CPFExport __declspec( dllimport )
#           endif
#    endif
#    define _CPFPrivate
# endif
    // Win32 compilers use _DEBUG for specifying debug builds.
#   ifdef _DEBUG
#       define COLLADAMaya_DEBUG_MODE
#   else
#       undef COLLADAMaya_DEBUG_MODE
#   endif

#if !defined( __MINGW32__ )
#define snprintf _snprintf
#define vsnprintf _vsnprintf
#endif

    // Disable unicode support on MingW at the moment, poorly supported in stdlibc++
    // STLPORT fixes this though so allow if found
    // MinGW C++ Toolkit supports unicode and sets the define __MINGW32_TOOLKIT_UNICODE__ in _mingw.h
#if defined( __MINGW32__ ) && !defined(_STLPORT_VERSION)
#   include<_mingw.h>
#   if defined(__MINGW32_TOOLBOX_UNICODE__)
#     define COLLADAMaya_UNICODE_SUPPORT 1
#   else
#       define COLLADAMaya_UNICODE_SUPPORT 0
#   endif
#else
# define COLLADAMaya_UNICODE_SUPPORT 1
#endif

#endif
    //----------------------------------------------------------------------------

    //----------------------------------------------------------------------------
    // Linux/Apple Settings
#if COLLADAMaya_PLATFORM == COLLADAMaya_PLATFORM_LINUX || COLLADAMaya_PLATFORM == COLLADAMaya_PLATFORM_APPLE

    // Enable GCC symbol visibility
#   if defined( COLLADAMaya_GCC_VISIBILITY )
#       define _CPFExport  __attribute__ ((visibility("default")))
#       define _CPFPrivate __attribute__ ((visibility("hidden")))
#   else
#       define _CPFExport
#       define _CPFPrivate
#   endif

    // A quick define to overcome different names for the same function
#   define stricmp strcasecmp

    // Unlike the Win32 compilers, Linux compilers seem to use DEBUG for when
    // specifying a debug build.
    // (??? this is wrong, on Linux debug builds aren't marked in any way unless
    // you mark it yourself any way you like it -- zap ???)
#   ifdef DEBUG
#       define COLLADAMaya_DEBUG_MODE
#   else
#       undef COLLADAMaya_DEBUG_MODE
#   endif

#if COLLADAMaya_PLATFORM == COLLADAMaya_PLATFORM_APPLE
#define COLLADAMaya_PLATFORM_LIB "CPFPlatform.bundle"
#else
    //COLLADAMaya_PLATFORM_LINUX
#define COLLADAMaya_PLATFORM_LIB "libCPFPlatform.so"
#endif

    // Always enable unicode support for the moment
    // Perhaps disable in old versions of gcc if necessary
#define COLLADAMaya_UNICODE_SUPPORT 1

#endif

    //For apple, we always have a custom config.h file
#if COLLADAMaya_PLATFORM == COLLADAMaya_PLATFORM_APPLE
#    include "config.h"
#endif

    //----------------------------------------------------------------------------

    //----------------------------------------------------------------------------
    // Endian Settings
    // check for BIG_ENDIAN config flag, set COLLADAMaya_ENDIAN correctly
#ifdef COLLADAMaya_CONFIG_BIG_ENDIAN
#    define COLLADAMaya_ENDIAN COLLADAMaya_ENDIAN_BIG
#else
#    define COLLADAMaya_ENDIAN COLLADAMaya_ENDIAN_LITTLE
#endif

    // Integer formats of fixed bit width
    typedef unsigned char uint8;
    typedef unsigned short uint16;
    typedef unsigned int uint32;

    typedef signed char int8;
    typedef short int16;
    typedef long int32;
}

#endif // __COLLADA_MAYA_PLATFORM_H__




/* Define size of long long and/or __int64 bit integer type only if the type
   exists.  */
#if !defined(__APPLE__)
 #define H5_SIZEOF_LONG_LONG 8
#else
 #define H5_SIZEOF_LONG_LONG 8
#endif

#define H5_STDC_HEADERS 1
#define H5_HAVE_C99_FUNC
#define H5_DEFAULT_PLUGINDIR "h5plugin"

#ifdef HX_WINDOWS
  #define H5_HAVE_WIN32_API 1
  #define H5_HAVE_SYS_TIME 1
  #define H5_HAVE_WINSOCK2_H 1
   /* Define if C++ compiler recognizes offsetof */
  #define CXX_HAVE_OFFSETOF
#else
  #define H5_TIME_WITH_SYS_TIME 1
  #define H5_HAVE_DLFCN_H 1
  #define H5_HAVE_DIRENT_H 1
  #define H5_HAVE_FLOCK 1
#endif

//#define H5_HAVE_FCNTL

/* Width for printf() for type `long long' or `__int64', use `ll' */
#define H5_PRINTF_LL_WIDTH "ll"


/* The size of `bool', as computed by sizeof. */
#define H5_SIZEOF_BOOL 1

/* The size of `char', as computed by sizeof. */
#define H5_SIZEOF_CHAR 1

/* The size of `double', as computed by sizeof. */
#define H5_SIZEOF_DOUBLE 8

/* The size of `float', as computed by sizeof. */
#define H5_SIZEOF_FLOAT 4

/* The size of `int', as computed by sizeof. */
#define H5_SIZEOF_INT 4

/* The size of `int16_t', as computed by sizeof. */
#define H5_SIZEOF_INT16_T 2

/* The size of `int32_t', as computed by sizeof. */
#define H5_SIZEOF_INT32_T 4

/* The size of `int64_t', as computed by sizeof. */
#define H5_SIZEOF_INT64_T 8

/* The size of `int8_t', as computed by sizeof. */
#define H5_SIZEOF_INT8_T 1

/* The size of `int_fast16_t', as computed by sizeof. */
#define H5_SIZEOF_INT_FAST16_T 2

/* The size of `int_fast32_t', as computed by sizeof. */
#define H5_SIZEOF_INT_FAST32_T 4

/* The size of `int_fast64_t', as computed by sizeof. */
#define H5_SIZEOF_INT_FAST64_T 8

/* The size of `int_fast8_t', as computed by sizeof. */
#define H5_SIZEOF_INT_FAST8_T 1

/* The size of `int_least16_t', as computed by sizeof. */
#define H5_SIZEOF_INT_LEAST16_T 2

/* The size of `int_least32_t', as computed by sizeof. */
#define H5_SIZEOF_INT_LEAST32_T 4

/* The size of `int_least64_t', as computed by sizeof. */
#define H5_SIZEOF_INT_LEAST64_T 8

/* The size of `int_least8_t', as computed by sizeof. */
#define H5_SIZEOF_INT_LEAST8_T 1

/* The size of `long', as computed by sizeof. */
#define H5_SIZEOF_LONG 4

/* The size of `long double', as computed by sizeof. */
#define H5_SIZEOF_LONG_DOUBLE 8

/* The size of `long long', as computed by sizeof. */
#define H5_SIZEOF_LONG_LONG 8

/* The size of `short', as computed by sizeof. */
#define H5_SIZEOF_SHORT 2

/* The size of `size_t', as computed by sizeof. */
#ifdef HXCPP_M64
   #define H5_SIZEOF_SIZE_T 8
   #define H5_SIZEOF_OFF_T 8
   #define H5_SIZEOF_PTRDIFF_T 8
#else
   #define H5_SIZEOF_SIZE_T 4
   #define H5_SIZEOF_OFF_T 4
   #define H5_SIZEOF_PTRDIFF_T 4
#endif

/* The size of `uint16_t', as computed by sizeof. */
#define H5_SIZEOF_UINT16_T 2

/* The size of `uint32_t', as computed by sizeof. */
#define H5_SIZEOF_UINT32_T 4

/* The size of `uint64_t', as computed by sizeof. */
#define H5_SIZEOF_UINT64_T 8

/* The size of `uint8_t', as computed by sizeof. */
#define H5_SIZEOF_UINT8_T 1

/* The size of `uint_fast16_t', as computed by sizeof. */
#define H5_SIZEOF_UINT_FAST16_T 16

/* The size of `uint_fast32_t', as computed by sizeof. */
#define H5_SIZEOF_UINT_FAST32_T 4

/* The size of `uint_fast64_t', as computed by sizeof. */
#define H5_SIZEOF_UINT_FAST64_T 8

/* The size of `uint_fast8_t', as computed by sizeof. */
#define H5_SIZEOF_UINT_FAST8_T 1

/* The size of `uint_least16_t', as computed by sizeof. */
#define H5_SIZEOF_UINT_LEAST16_T 2

/* The size of `uint_least32_t', as computed by sizeof. */
#define H5_SIZEOF_UINT_LEAST32_T 4

/* The size of `uint_least64_t', as computed by sizeof. */
#define H5_SIZEOF_UINT_LEAST64_T 8

/* The size of `uint_least8_t', as computed by sizeof. */
#define H5_SIZEOF_UINT_LEAST8_T 1

/* The size of `unsigned', as computed by sizeof. */
#define H5_SIZEOF_UNSIGNED 4

/* The size of `_Quad', as computed by sizeof. */
#define H5_SIZEOF__QUAD 16

/* The size of `__float128', as computed by sizeof. */
#define H5_SIZEOF___FLOAT128 16

/* The size of `__int64', as computed by sizeof. */
#define H5_SIZEOF___INT64 8





























#undef DEBUG_BUILD

/* Define the default plugins path to compile */
#undef DEFAULT_PLUGINDIR

/* Define if dev_t is a scalar */
#undef DEV_T_IS_SCALAR





/* Define if support for deflate (zlib) filter is enabled */
#undef H5_HAVE_FILTER_DEFLATE

/* Define if support for szip filter is enabled */
#undef H5_HAVE_FILTER_SZIP





#define H5_HAVE_INLINE

/* Define to 1 if you have the <inttypes.h> header file. */
#define H5_HAVE_INTTYPES_H 1

/* Define to 1 if you have the `ioctl' function. */
#define H5_HAVE_IOCTL 1

/* Define to 1 if you have the <io.h> header file. */
#undef H5_HAVE_IO_H

/* Define to 1 if you have the `ws2_32' library (-lws2_32). */
#define H5_HAVE_LIBWS2_32 1

/* Define to 1 if you have the `z' library (-lz). */
#undef H5_HAVE_LIBZ

/* Define to 1 if you have the `longjmp' function. */
#define H5_HAVE_LONGJMP

/* Define to 1 if you have the `lstat' function. */
#define H5_HAVE_LSTAT

/* Define to 1 if you have the <memory.h> header file. */
#define H5_HAVE_MEMORY_H

/* Define to 1 if you have the `random' function. */
#define H5_HAVE_RANDOM 1

/* Define to 1 if you have the `rand_r' function. */
#undef H5_HAVE_RAND_R

/* Define to 1 if you have the `round' function. */
#define H5_HAVE_ROUND

/* Define to 1 if you have the `setjmp' function. */
#define H5_HAVE_SETJMP

/* Define to 1 if you have the <setjmp.h> header file. */
#define H5_HAVE_SETJMP_H

/* Define to 1 if you have the `snprintf' function. */
#define H5_HAVE_SNPRINTF

/* Define to 1 if you have the `srandom' function. */
#define H5_HAVE_SRANDOM

/* Define to 1 if you have the <stdint.h> header file. */
#define H5_HAVE_STDINT_H

/* Define to 1 if you have the <stdlib.h> header file. */
#define H5_HAVE_STDLIB_H

/* Define to 1 if you have the `strdup' function. */
#define H5_HAVE_STRDUP


/* Define to 1 if you have the <string.h> header file. */
#define H5_HAVE_STRING_H

/* Define to 1 if you have the `strtoll' function. */
#define H5_HAVE_STRTOLL

/* Define to 1 if you have the <sys/file.h> header file. */
#undef H5_HAVE_SYS_FILE_H

/* Define to 1 if you have the <sys/ioctl.h> header file. */
#undef H5_HAVE_SYS_IOCTL_H

/* Define to 1 if you have the <sys/resource.h> header file. */
#undef H5_HAVE_SYS_RESOURCE_H

/* Define to 1 if you have the <sys/socket.h> header file. */
#undef H5_HAVE_SYS_SOCKET_H

/* Define to 1 if you have the <sys/stat.h> header file. */
#define H5_HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/timeb.h> header file. */
#undef H5_HAVE_SYS_TIMEB_H

/* Define to 1 if you have the <sys/time.h> header file. */
#undef H5_HAVE_SYS_TIME_H

/* Define to 1 if you have the <sys/types.h> header file. */
#define H5_HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <szlib.h> header file. */
#undef H5_HAVE_SZLIB_H

/* Define if we have thread safe support */
#undef H5_HAVE_THREADSAFE

/* Define if timezone is a global variable */
#undef H5_HAVE_TIMEZONE

/* Define if the ioctl TIOCGETD is defined */
#undef H5_HAVE_TIOCGETD

/* Define if the ioctl TIOGWINSZ is defined */
#undef H5_HAVE_TIOCGWINSZ

/* Define to 1 if you have the `tmpfile' function. */
#undef H5_HAVE_TMPFILE

/* Define if tm_gmtoff is a member of struct tm */
#undef H5_HAVE_TM_GMTOFF

/* Define to 1 if you have the <unistd.h> header file. */
#ifdef _WIN32
#undef H5_HAVE_UNISTD_H
#else
#define H5_HAVE_UNISTD_H
#endif

/* Define to 1 if you have the `vasprintf' function. */
#undef H5_HAVE_VASPRINTF

/* Define to 1 if you have the `vsnprintf' function. */
#undef H5_HAVE_VSNPRINTF

/* Define to 1 if you have the `waitpid' function. */
#undef H5_HAVE_WAITPID

/* Define if your system has window style path name. */
#undef H5_HAVE_WINDOW_PATH

/* Define to 1 if you have the <zlib.h> header file. */
#undef H5_HAVE_ZLIB_H

/* Define to 1 if you have the `_getvideoconfig' function. */
#undef H5_HAVE__GETVIDEOCONFIG

/* Define to 1 if you have the `_scrsize' function. */
#undef H5_HAVE__SCRSIZE

/* Define if the compiler understands __inline */
#undef H5_HAVE___INLINE

/* Define if the compiler understands __inline__ */
#undef H5_HAVE___INLINE__

/* Define if the high-level library headers should be included in hdf5.h */
#undef INCLUDE_HL

/* Define if your system can convert long double to (unsigned) long long
   values correctly. */
#undef LDOUBLE_TO_LLONG_ACCURATE

/* Define if your system converts long double to (unsigned) long values with
   special algorithm. */
#undef LDOUBLE_TO_LONG_SPECIAL

/* Define if your system can convert (unsigned) long long to long double
   values correctly. */
#undef LLONG_TO_LDOUBLE_CORRECT

/* Define if your system can convert (unsigned) long to long double values
   with special algorithm. */
#undef LONG_TO_LDOUBLE_SPECIAL

/* Define to the sub-directory where libtool stores uninstalled libraries. */
#undef LT_OBJDIR

/* Define to enable internal memory allocation sanity checking. */
#undef MEMORY_ALLOC_SANITY_CHECK

/* Define if the metadata trace file code is to be compiled in */
#undef METADATA_TRACE_FILE

/* Define if we can violate pointer alignment restrictions */
#undef NO_ALIGNMENT_RESTRICTIONS

/* Define if deprecated public API symbols are disabled */
#undef NO_DEPRECATED_SYMBOLS

/* Name of package */
#undef PACKAGE

/* Define to the address where bug reports for this package should be sent. */
#undef PACKAGE_BUGREPORT

/* Define to the full name of this package. */
#undef PACKAGE_NAME

/* Define to the full name and version of this package. */
#undef PACKAGE_STRING

/* Define to the one symbol short name of this package. */
#undef PACKAGE_TARNAME

/* Define to the home page for this package. */
#undef PACKAGE_URL

/* Define to the version of this package. */
#undef PACKAGE_VERSION

/* Determine the maximum decimal precision in C */
#undef PAC_C_MAX_REAL_PRECISION

/* Define Fortran Maximum Real Decimal Precision */
#undef PAC_FC_MAX_REAL_PRECISION

/* Width for printf() for type `long long' or `__int64', use `ll' */
#undef PRINTF_LL_WIDTH


/* Define to 1 if you have the ANSI C header files. */
#undef STDC_HEADERS

/* Define if strict file format checks are enabled */
#undef STRICT_FORMAT_CHECKS

/* Define if your system supports pthread_attr_setscope(&attribute,
   PTHREAD_SCOPE_SYSTEM) call. */
#undef SYSTEM_SCOPE_THREADS

/* Define to 1 if you can safely include both <sys/time.h> and <time.h>. */
#undef TIME_WITH_SYS_TIME

/* Define using v1.6 public API symbols by default */
#undef USE_16_API_DEFAULT

/* Define using v1.8 public API symbols by default */
#undef USE_18_API_DEFAULT

/* Define if a memory checking tool will be used on the library, to cause
   library to be very picky about memory operations and also disable the
   internal free list manager code. */
#undef USING_MEMCHECKER

/* Version number of package */
#undef VERSION

/* Data accuracy is prefered to speed during data conversions */
#undef WANT_DATA_ACCURACY

/* Check exception handling functions during data conversions */
#undef WANT_DCONV_EXCEPTION

/* Define WORDS_BIGENDIAN to 1 if your processor stores words with the most
   significant byte first (like Motorola and SPARC, unlike Intel). */
#if defined AC_APPLE_UNIVERSAL_BUILD
# if defined __BIG_ENDIAN__
#  define WORDS_BIGENDIAN 1
# endif
#else
# ifndef WORDS_BIGENDIAN
#  undef WORDS_BIGENDIAN
# endif
#endif

/* Number of bits in a file offset, on hosts where this is settable. */
#undef _FILE_OFFSET_BITS

/* Define for large files, on AIX-style hosts. */
#undef _LARGE_FILES

/* Define to empty if `const' does not conform to ANSI C. */
#undef const

/* Define to `long int' if <sys/types.h> does not define. */
#undef off_t

/* Define to `long' if <sys/types.h> does not define. */
#undef ptrdiff_t

/* Define to `unsigned long' if <sys/types.h> does not define. */
#undef size_t

/* Define to `long' if <sys/types.h> does not define. */
#undef ssize_t

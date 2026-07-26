#ifndef _GNU_SOURCE
#define _GNU_SOURCE 1
#endif

#ifndef GLIBC_COMPAT_H
#define GLIBC_COMPAT_H

#include <sys/types.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <errno.h>
#include <stdint.h>

#ifndef _USECONDS_T_DECLARED
#define _USECONDS_T_DECLARED
#endif

#ifndef __ANDROID_API__
#define gettid() syscall(SYS_gettid)
#endif

#endif // GLIBC_COMPAT_H
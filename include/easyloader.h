/* ---------------------------------------------------------------------------
** easyloader.h
** Contains header declarations for easyloader 0.1.0.
**
** Author: Sk. Mohammadul Haque
** Copyright (c) 2016 Sk. Mohammadul Haque
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in all
** copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
** SOFTWARE.
**
** For more details and updates, visit http://mohammadulhaque.alotspace.com
** -------------------------------------------------------------------------*/

#ifndef __EASYLOADER_H__
#define __EASYLOADER_H__
#if defined(_WIN32) ||defined(WINNT)
#include <windows.h>
typedef HANDLE easyloader_lib;
#elif defined(__linux__) ||defined (__unix__)
#include <dlfcn.h>
#ifndef RTLD_NOW
#define RTLD_NOW 1
#endif
#ifndef RTLD_GLOBAL
#define RTLD_GLOBAL 0
#endif
typedef void* easyloader_lib;
#endif
#include <stdio.h>

extern easyloader_lib* easyloader_dllopen(const char* fname);
extern void* easyloader_dllfunc(easyloader_lib* l, const char* func);
extern int easyloader_dllclose(easyloader_lib* l);
extern char* easyloader_dlllasterror(void);






#endif // __EASYLOADER_H__

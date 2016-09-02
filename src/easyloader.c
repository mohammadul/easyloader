/* ---------------------------------------------------------------------------
** easyloader.c
** Contains  definitions for easyloader 0.1.0.
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

#include "../include/easyloader.h"

#if defined(_WIN32) ||defined(WINNT)
static char easyloader_last_error[512];
static void easyloader_dllseterror(void);

easyloader_lib* easyloader_dllopen(const char* fname)
{
    HMODULE h;
    int emd;
    emd = SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOOPENFILEERRORBOX);
    h = LoadLibrary(fname);
    SetErrorMode(emd);
    if(!h)
    {
        easyloader_dllseterror();
        return NULL;
    }
    easyloader_last_error[0] = 0;
    return (easyloader_lib*)h;
}

void *easyloader_dllfunc(easyloader_lib *l, const char *func)
{
    void *ptr;
    *(FARPROC*)(&ptr) = GetProcAddress((HMODULE)l, func);
    if(!ptr)
    {
        easyloader_dllseterror();
        return NULL;
    }
    easyloader_last_error[0] = 0;
    return ptr;
}

int easyloader_dllclose(easyloader_lib* l)
{
    if(!FreeLibrary((HMODULE) l))
    {
        easyloader_dllseterror();
        return 1;
    }
    easyloader_last_error[0] = 0;
    return 0;
}

static void easyloader_dllseterror(void)
{
    DWORD err = GetLastError();
    if(FormatMessage(FORMAT_MESSAGE_IGNORE_INSERTS|FORMAT_MESSAGE_FROM_SYSTEM, NULL, err, MAKELANGID(LANG_ENGLISH, SUBLANG_DEFAULT), easyloader_last_error, sizeof(easyloader_last_error)-1, NULL)==0)
    {
        sprintf(easyloader_last_error, "unknown error %lu", err);
    }
}

#elif defined(__linux__) ||defined (__unix__)

easyloader_lib* easyloader_dllopen(const char* fname)
{
    return (easyloader_lib*)dlopen(fname, RTLD_NOW | RTLD_GLOBAL);
}

void *easyloader_dllfunc(easyloader_lib *l, const char *func)
{
    return dlsym(l, func);
}

int easyloader_dllclose(easyloader_lib* l)
{
    return dlclose(l);
}

#endif


char *easyloader_dlllasterror(void)
{
#if defined(_WIN32) ||defined(WINNT)
    if (easyloader_last_error[0]) return easyloader_last_error;
    else return NULL;
#elif defined(__linux__) ||defined (__unix__)
    return dlerror();
#endif
}


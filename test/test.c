/* ---------------------------------------------------------------------------
** test.c
** Contains test example.
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
#include <meshlib.h>

int main(int argc, char *argv[])
{
    easyloader_lib *h = NULL;;
    MESH (*myload)(const char*) = NULL;
    void (*myunload)(MESH) = NULL;
    MESH m = NULL;
    char *error = NULL;
    if(argc<2)
    {
        printf("Not enough arguments.\n");
        exit(1);
    }
#if defined(_WIN32) ||defined(WINNT)
    h = easyloader_dllopen("meshlib.dll");
#elif defined(__linux__) ||defined (__unix__)
    h = easyloader_dllopen("./meshlib.so");
#endif
    if(!h)
    {
        printf("%s", easyloader_dlllasterror());
        exit(2);
    }
    printf("Library loaded.\n");
    *(void **)(&myload) = easyloader_dllfunc(h, "mesh_load_file");
    if((error = easyloader_dlllasterror())!=NULL)
    {
        printf("%s", error);
        exit(3);
    }
    *(void **)(&myunload) = easyloader_dllfunc(h, "mesh_free_mesh");
    if((error = easyloader_dlllasterror())!=NULL)
    {
        printf("%s", error);
        exit(4);
    }
    printf("All functions found.\n");
    m = (*myload)(argv[1]);
    if(m==NULL) printf("Cannot open mesh.\n");
    else
    {
        printf("Mesh Details:\n");
        printf("Number of Vertices: %d\n", m->num_vertices);
        printf("Number of Faces: %d\n", m->num_faces);
        (*myunload)(m);
        m = NULL;
    }
    easyloader_dllclose(h);
    printf("Library unloaded.\n");
    return 0;
}

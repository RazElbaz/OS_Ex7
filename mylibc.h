#include "myfs.h"
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define EOF '\0'

typedef struct myFILE {
    char* mode; //r,r+,w,a
    char *data;
    int fd;
    int size;
    int pointerFile;
}myFILE;

myFILE* myfopen(const char *pathname, const char *mode);
int myfclose(myFILE *stream);
size_t myfread(void * ptr, size_t size, size_t nmemb, myFILE * stream);
size_t myfwrite(const void * ptr, size_t size, size_t nmemb, myFILE * stream);
int myfseek(myFILE *stream, long offset, int whence);
int myfscanf(myFILE * stream, const char * format, ...);
int myfprintf(myFILE * stream, const char * format, ...);
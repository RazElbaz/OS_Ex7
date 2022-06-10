# OS_Ex7

# Introduction:
The final submission will include a ufs file system.

# Tasks:
## File system within a file
Realize a system close to ufs within a file. You must implement the following functions
mymkfs (1)
A program that creates the file in which you will find a file system receives a s parameter that describes the size
The file system. In your file system, 10% of the space will be automatically allocated to one-block nodes
Be a super block and the rest are regular blocks. In addition it can be assumed that mkfs produces the main directory.
Implement the following functions and the data structure myDIR mydirent:

```
int mymount(const char *source, const char *target, const char *filesystemtype, unsigned longmountflags, const void *data);

int myopen(const char *pathname, int flags);

int myclose(int myfd);

size_t myread(int myfd, void *buf, size_t count);

size_t mywrite(int myfd, const void *buf, size_t count);

off_t mylseek(int myfd, off_t offset, int whence);

myDIR *myopendir(const char *name);

struct mydirent *myreaddir(myDIR *dirp);

int myclosedir(myDIR *dirp);
```

## Mylibc


Above the file system) implemented in the previous section (yours you must implement the structure myFILE *

And the functions:
```
myFILE *myfopen(const char *restrict pathname, const char*restrict mode)

int myfclose(myFILE *stream);

size_t myfread(void *restrict ptr, size_t size, size_t nmemb,

myFILE *restrict stream);

size_t myfwrite(const void *restrict ptr, size_t size, size_t nmemb, myFILE *restrict stream);

int myfseek(myFILE *stream, long offset, int whence);

int myfscanf(myFILE *restrict stream,const char *restrict format, ...);

int myfprintf(myFILE *restrict stream, const char *restrict format, ...);
```

##  Run:
In order to run the tests for the file system, do the following:  
1. ```make```
2. run ```./test```
3. enjoy seeing the tests 😊!  
* We implemented errno for the functions above

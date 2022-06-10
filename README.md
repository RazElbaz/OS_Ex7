# OS_Ex7

# Introduction:
The final submission will include a stack server (component I) implementing multi
process shared memory and locking routines

## Tasks:
File system within a file
Realize a system close to ufs within a file. You must implement the following functions
mymkfs (1)
A program that creates the file in which you will find a file system receives a s parameter that describes the size
The file system. In your file system, 10% of the space will be automatically allocated to one-block nodes
Be a super block and the rest are regular blocks. In addition it can be assumed that mkfs produces the main directory.
Implement the following functions and the data structure myDIR mydirent:
int mymount(const char *source, const char *target, const char *filesystemtype, unsigned longmountflags, const void *data);
int myopen(const char *pathname, int flags);
int myclose(int myfd);
size_t myread(int myfd, void *buf, size_t count);
size_t mywrite(int myfd, const void *buf, size_t count);
off_t mylseek(int myfd, off_t offset, int whence);
myDIR *myopendir(const char *name);
struct mydirent *myreaddir(myDIR *dirp);
int myclosedir(myDIR *dirp);

Additional facilitations and guidelines
1. There is no limit to fields in * myDIR. Mydirent structure must contain a name_d field that contains the name
The file can contain additional fields as you wish.
2. You must maintain a table of open myfd files - you can save as much as you want in this table.
You may assume that you have a global variable [FILES_MAX [myopenfile struct when
 FILES_MAX is fixed and set to 10000. You can enter any information you want in myopenfile struct
Additional global variables can be set if you find it necessary.
3.myopen will only work on a file system assembled by mymount
4 .myclose, mylseek, mywrite, myread will only work on files opened by myopen
5. All functions will be available using so.libmyfs directory and can be used by one # include
myfs.h l
6. No need to support fragments and permissions.




##  Run:
In order to run the tests for the file system, do the following:  
1. ```make```
2. run ```./test```
3. enjoy seeing the tests :)!  

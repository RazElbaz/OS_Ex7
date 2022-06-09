#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stdbool.h"
#define  BLOCK_SIZE 512
#define MAX_FILES 10000
struct superblock {
    int num_inodes;
    int num_blocks;
};


struct disk_block {
    int next_block_num;
    char data[BLOCK_SIZE];
};


struct inode {
    char name[8];
    bool isFile;
    int first_block;
    int size;
};
struct myopenfile {
    int fd;
    int pos;
};
struct myDIR{
    int pos;
};
struct mydirent{
    char d_name[8];
    int size;
    char inside[50];
};

//the basic file system implementation:
///credit: https://www.youtube.com/watch?v=n2AAhiujAqs&ab_channel=drdelhart
void create_fs();// initialize new file system
void syns_fs();//write the file system
void mount_fs();//load file system
void print_fs();// print out info about the file system
int allocate_file(const char *name);//return file number
void set_filesize(int filenum, int size);//set the size of the file
void write_byte(int filenum, int pos,  char data);

//The functions we were asked to perform for the task:
int mymount(const char *source, const char *target,const char *filesystemtype, unsigned long mountflags, const void *data);
int myopen(const char *pathname, int flags);
int myclose(int myfd);
size_t myread(int myfd, void *buf, size_t count);
size_t mywrite(int myfd, const void *buf, size_t count);
int mylseek(int myfd, off_t offset, int whence);
struct myDIR *myopendir(const char *name);
struct mydirent *myreaddir(int dirp);
int myclosedir(struct myDIR *dirp);

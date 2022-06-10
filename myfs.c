#include "myfs.h"




void create_fs() {
    //init the sizes of the inodes and the blocks
    sb.num_inodes = 10;
    sb.num_blocks = 100;
    inodes = malloc(sb.num_inodes * sizeof(struct inode));
    dbs = malloc(sb.num_blocks * sizeof(struct disk_block));

    //this loop will init the inodes
    for (int i = 0; i < sb.num_inodes; i++) {
        strcpy(inodes[i].name, "empty");
        inodes[i].first_block = -1;
        inodes[i].isFile = true;
    }
    //init disk blocks
    for (int i = 0; i < sb.num_blocks; i++) {
        dbs[i].next_block_num = -1;
    }
    int firstDoc = allocate_file("home",64);
    if (firstDoc != 0) {
        printf("Error: cant build firstDoc");
        return;
    }
    inodes[firstDoc].isFile = false;
    struct mydirent *home = malloc(64);//size of the struct mydirent
    strcpy(home->d_name, "home");
    for (size_t i = 0; i < strlen((char *) home); i++) {
        write_byte(firstDoc, i, ((char *) home)[i]);
    }
    free(home);
}

void shorten_file(int bn) {
    int nn = dbs[bn].next_block_num;
    if (nn >= 0) {
        shorten_file(nn);
    }
    dbs[bn].next_block_num = -1;
}

int get_block_num(int file, int offset) {
    int togo = offset;
    int bn = inodes[file].first_block;
    while (togo > 0) {
        bn = dbs[bn].next_block_num;
        togo--;
    }
    return bn;

}

void mount_fs(const char *source) {
    FILE *file;
    file = fopen("fs_data", "r");
    //superblocks
    fread(&sb, sizeof(struct superblock), 1, file);
    inodes = malloc(sizeof(struct inode) * sb.num_inodes);
    dbs = malloc(sizeof(struct disk_block) * sb.num_blocks);
    fread(inodes, sizeof(struct inode), sb.num_inodes, file);
    fread(dbs, sizeof(struct disk_block), sb.num_blocks, file);

    fclose(file);
}

void syns_fs(const char *target) {
    FILE *file;
    file = fopen("fs_data", "w+");
    //superblocks
    fwrite(&sb, sizeof(struct superblock), 1, file);
    //write inodes
    int i;
    for (i = 0; i < sb.num_inodes; i++) {
        fwrite(&(inodes[i]), sizeof(struct inode), 1, file);
    }
    //write disk block
    for (i = 0; i < sb.num_blocks; i++) {
        fwrite(&(dbs[i]), sizeof(struct disk_block), 1, file);
    }
    fclose(file);
}

void print_fs() {
    printf("Superblock info\n");
    printf("\tnum inodes %d\n", sb.num_inodes);
    printf("\tnum blocks %d\n", sb.num_blocks);
    printf("inodes\n");
    int i;
    printf("%d\n",sb.num_inodes);

    for (i = 0; i < sb.num_inodes; i++) {
        printf("\tsize: %d block: %d name: %s\n", inodes[i].size, inodes[i].first_block, inodes[i].name);
    }

    for (i = 0; i < sb.num_blocks; i++) {
        printf("\tblock num: %d next block: %d\n", i, dbs[i].next_block_num);
    }


}

int find_empty_inode() {
    /***
     * find empty inode
     */
    int i;
    for (i = 0; i < sb.num_inodes; i++) {
        if (inodes[i].first_block == -1) {
            return i;
        }
    }
    return -1;
}

int find_empty_block() {
    /***
     * find empty block
     */
    int i;
    for (i = 0; i < sb.num_blocks; i++) {
        if (dbs[i].next_block_num == -1) {
            return i;
        }
    }
    return -1;
}

int allocate_file(const char *name,int size) {
    //find an empty inode
    int in = find_empty_inode();
    //find / claim a disk block
    int block = find_empty_block();
    //claim them
    inodes[in].first_block = block;
    inodes[in].size = size;
    dbs[block].next_block_num = -2;
    strcpy(inodes[in].name, name);
    //return the file description
    return in;
}

// add / delete blocks
void set_filesize(int filenum, int size) {
    int temp = size + BLOCK_SIZE - 1;

    //how many blocks should we have
    int num = temp / BLOCK_SIZE;
    int bn = inodes[filenum].first_block;
    num--;
    //grow the file if necessary
    while (num > 0) {
        //check the next block number
        int next_num = dbs[bn].next_block_num;
        if (next_num == -2) {
            int empty = find_empty_block();
            dbs[bn].next_block_num = empty;
            dbs[empty].next_block_num = -2;

        }
        bn = dbs[bn].next_block_num;
        num--;
    }
    //shorten if necessary
    shorten_file(bn);
    dbs[bn].next_block_num = -2;

}

void write_byte(int filenum, int pos, char data) {
    int offset = inodes[filenum].first_block;
    for (; pos >=BLOCK_SIZE ; pos -= BLOCK_SIZE) {
        switch (dbs[offset].next_block_num) {
            case -1:
                break;
            case -2:
                dbs[offset].next_block_num = find_empty_block();
                offset = dbs[offset].next_block_num;
                dbs[offset].next_block_num = -2;
                break;

                // dbs[offset].next_block_num doesn't match any case constant -1,-2
            default:
                offset = dbs[offset].next_block_num;
        }
    }
    inodes[filenum].size++;
    dbs[offset].data[pos] = data;
}


int mymount(const char *source, const char *target, const char *filesystemtype, unsigned long mountflags,
            const void *data) {
    /**
     * The mount command serves to attach the filesystem found on some device to the big file tree. Conversely, the umount(8) command will detach it again.
     */
    if (source == NULL) {
        return -1;
    }
    if (target == NULL) {
        return -1;
    }
    if (filesystemtype == NULL) {
        return -1;
    }
    mount_fs(source);
    syns_fs(target);
    return 0;
}


int myclose(int myfd) {
    /**
     *close() closes a file descriptor, so that it no longer refers to
       any file and may be reused.
       @return
       close() returns zero on success.  On error, -1 is returned, and
       errno is set to indicate the error.
     */
    ///credit: https://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm
    if (myopenfiles[myfd].pos >= 0 && myopenfiles[myfd].fd >= 0 && myfd >= 0) {
        myopenfiles[myfd].pos = -1;
        myopenfiles[myfd].fd = -1;
        return 0;
    }
    return -1;
}

////check the for loop
size_t myread(int myfd, void *buf, size_t count) {
    /**
     * read() attempts to read up to count bytes from file descriptor fd
       into the buffer starting at buf.
       @return
       On error, -1 is returned, and errno is set to indicate the error.
       In this case, it is left unspecified whether the file position
       (if any) changes.
     */
    if (myopenfiles[myfd].fd == -1 || myopenfiles[myfd].pos == -1) {
        printf("Error:There is an error reading from the file");
        return -1;
    }
    if (inodes[myfd].isFile == false) {
        printf("Error: You cannot read anything that is not a file in this function");
        return -1;
    }
    size_t size = count,i=0;
    char *buff = malloc(sizeof(char) * size);
    while (i<count){
        buff[i++] = dbs[myfd].data[myopenfiles[myfd].pos];
        myopenfiles[myfd].pos++;
    }
    strcpy(buf, buff);
    free(buff);
    return myopenfiles[myfd].pos;
}

size_t mywrite(int myfd, const void *buf, size_t count) {
    if (myopenfiles[myfd].fd == -1 || myopenfiles[myfd].pos == -1) {
        printf("Error:There is an error reading from the file");
        return -1;
    }
    if (inodes[myfd].isFile == false) {
        printf("Error: You cannot read anything that is not a file in this function");
        return -1;
    }
    for (int i = 0; i < count; i++) {
        write_byte(myfd, myopenfiles[myfd].pos, ((char *) buf)[i]);
        //increase the position for write the next byte
        myopenfiles[myfd].pos++;
    }
    return (size_t)(myopenfiles[myfd].pos);

}

int mylseek(int myfd, off_t offset, int whence) {
    /**
     *  lseek - reposition read/write file offset
     *  lseek() repositions the file offset of the open file description
       associated with the file descriptor fd to the argument offset
       according to the directive whence as follows:
       SEEK_SET
              The file offset is set to offset bytes.
       SEEK_CUR
              The file offset is set to its current location plus offset
              bytes.
       SEEK_END
              The file offset is set to the size of the file plus offset
              bytes.
       @return
       Upon successful completion, lseek() returns the resulting offset
       location as measured in bytes from the beginning of the file.  On
       error, the value (off_t) -1 is returned and errno is set to
       indicate the error.
     */
    //credit: https://www.programiz.com/c-programming/c-switch-case-statement
    if (myopenfiles[myfd].fd == myfd) {
        switch (whence) {
            case SEEK_SET:
                myopenfiles[myfd].pos = offset;
                break;
            case SEEK_END:
                myopenfiles[myfd].pos = inodes[myfd].size + offset;
                break;

            case SEEK_CUR:
                myopenfiles[myfd].pos += offset;
                break;
                // whence doesn't match any case constant SEEK_SET, SEEK_END, SEEK_CUR
            default:
                myopenfiles[myfd].pos = 0;
        }
    } else {
        return -1;
    }
    return myopenfiles[myfd].pos;
}

int lastDirectory(const char *path, const char *name) {
    int myfd = myopendir(path);

    if (myfd == -1) {return -1;}
    if (inodes[myfd].isFile == true) {return -1;}

    struct mydirent *mydirent = (struct mydirent *)dbs[inodes[myfd].first_block].data;
    int file = allocate_file(name,1);
    mydirent->inside[mydirent->size++] = file;
    inodes[file].isFile = false;
    return file;
}

struct myDIR *myopendir(const char *name) {
    /**
     * The opendir() function opens a directory stream corresponding to
       the directory name, and returns a pointer to the directory
       stream.  The stream is positioned at the first entry in the
       directory
     *@return    The opendir() function return a pointer to the
       directory stream.  On error, NULL is returned, and errno is set
       to indicate the error.
       @credit: https://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm
     */
    if(!name){ return NULL;}
    char curr[8] = "", old[8] = "",string[100];
    strcpy(string, name);
    for(char *i = strtok(string, "/"); i != NULL; i = strtok(NULL, "/")){
        strcpy(old, curr);
        strcpy(curr, i);}

    for (int j = 0; j < sb.num_inodes; j++) {
        if (strcmp(inodes[j].name, curr) == false) {
            if (inodes[j].isFile != false) {
                return NULL;
            }
            return (struct myDIR *) j;
        }}
    return lastDirectory(old, curr);
}

struct mydirent *myreaddir(int dirp) {
    return (struct mydirent *) dbs[inodes[dirp].first_block].data;
}

int myclosedir(struct myDIR *dirp) {
    /**
     * The closedir() function closes the directory stream associated
       with dirp.  A successful call to closedir() also closes the
       underlying file descriptor associated with dirp.
       @return
       The closedir() function returns 0 on success.  On error, -1 is
       returned, and errno is set to indicate the error.
     */
    if (!dirp) return -1;
    free(dirp);
    return 0;
}

int myopen(const char *pathname, int flags) {
    /**
   *The open() system call opens the file specified by pathname.  If
   the specified file does not exist, it may optionally (if O_CREAT
   is specified in flags) be created by open().
    @return
   The return value of open() is a file descriptor, a small,
   non negative integer that is an index to an entry in the process's
   table of open file descriptors.
   @credit: https://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm
 */
    if(!pathname){return -1;}
    char str[100],curr[8], old[8];
    strcpy(str, pathname);
    for(char *i = strtok(str, "/"); i != NULL; i = strtok(NULL, "/")){
        strcpy(old, curr);
        strcpy(curr, i);}

    for (int j = 0; j < sb.num_inodes; j++) {
        if (strcmp(inodes[j].name, curr) == false) {
            if (inodes[j].isFile == false) {
                return -1;
            }
            myopenfiles[j].fd = j;
            myopenfiles[j].pos = 0;
            return j;
        }
    }
    int file = allocate_file(curr,1);
    struct mydirent *mydirent = myreaddir((myopendir(old)));
    mydirent->inside[mydirent->size++] = file;
    //init:
    myopenfiles[file].fd = file;
    myopenfiles[file].pos = 0;
    return file;
}
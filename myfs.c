#include "myfs.h"

struct superblock sb;
struct inode *inodes;
struct disk_block *dbs;
struct myopenfile myopenfiles[MAX_FILES];


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
    int firstDoc = allocate_file("home");
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

int allocate_file(const char *name) {
    //find an empty inode
    int in = find_empty_inode();
    //find / claim a disk block
    int block = find_empty_block();
    //claim them
    inodes[in].first_block = block;
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
    dbs[offset].data[pos] = data;
}





#include <stdio.h>
#include <string.h>
#include "assert.h"
#include "mylibc.h"
int main() {
    printf("*******************************************************************\n");
    printf("============ Welcome to our file system implementation ============\n");
    printf("*******************************************************************\n");
    create_fs();
    ///Test myopendir functuin:
    int openDir1 = myopendir("home/Task7");
    int openDir2 = myopendir("home/Task7");

    assert(openDir1 == openDir2);
    if (openDir1 == openDir2) {
        printf("Test function: myopendir | status: Passed\n");
    } else {
        printf("Test function: myopendir | status: Failed\n");
    }

    ///Test myopen functuin:
    myopendir("home/new_dic");
    int openFile1 = myopen("home/Task7/file1", 0);
    int openFile2 = myopen("home/Task7/file1", 0);
    int openFile3 = myopen("home/new_dic/file2", 0);
    int openFile4 = myopen("home/Task7/file2", 0);
    int openFile5 = myopen("home/new_dic/file2", 0);

    assert(openFile1 == openFile2);
    if (openFile1 == openFile2) {
        printf("Test function: myopen | status: Passed\n");
    } else {
        printf("Test function: myopen | status: Failed\n");
    }
    assert(openFile3 == openFile5);
    if (openFile3 == openFile5) {
        printf("Test function: myopen | status: Passed\n");
    } else {
        printf("Test function: myopen | status: Failed\n");
    }

    ///Test two different folders but the same file inside them
    assert(openFile3 == openFile4);
    if (openFile3 == openFile4) {
        printf("Test: different folders | status: Passed\n");
    } else {
        printf("Test: different folders | status: Failed\n");
    }
    assert(openFile5 == openFile3);
    if (openFile5 == openFile3) {
        printf("Test: different folders | status: Passed\n");
    } else {
        printf("Test: different folders | status: Failed\n");
    }
    assert(openFile5 == openFile4);
    if (openFile5 == openFile4) {
        printf("Test: different folders | status: Passed\n");
    } else {
        printf("Test: different folders | status: Failed\n");
    }


    ///Test myclose functuin:
    openFile2 = myclose(openFile2);
    assert(openFile1 != openFile2);
    if (openFile1 != openFile2) {
        printf("Test function: myclose | status: Passed\n");
    } else {
        printf("Test function: myclose | status: Failed\n");
    }

    ///Test mywrite function
    char *string = "Our Ufs @c-Raz, Amir\n";
    int myWrite = mywrite(openFile3, string, 25);
    assert(myWrite != -1);
    if (myWrite != -1) {
        printf("Test function: mywrite | status: Passed\n");
    } else {
        printf("Test function: mywrite | status: Failed\n");
    }

    ///Test mylseek function
    char s1[30], s2[30];
    int myLseek = mylseek(openFile3, -30, SEEK_CUR);
    assert(myLseek != -1);
    if (myLseek != -1) {
        printf("Test function: mylseek | status: Passed\n");
    } else {
        printf("Test function: mylseek | status: Failed\n");
    }

    ///Test myread function
    int myRead = myread(openFile3, s1, 25);
    assert(myRead != -1);
    if (myRead != -1) {
        printf("Test function: myread | status: Passed\n");
    } else {
        printf("Test function: myread | status: Failed\n");
    }

    ///Test 2 mylseek function
    int myLseek2 = mylseek(openFile3, -20, SEEK_CUR);
    assert(myLseek2 != -1);
    if (myLseek2 != -1) {
        printf("Test2 function: mylseek | status: Passed\n");
    } else {
        printf("Test2 function: mylseek | status: Failed\n");
    }

    ///Test 2 myread function
    int myRead2 = myread(openFile3, s2, 25);
    assert(myRead2 != -1);
    if (myRead2 != -1) {
        printf("Test2 function: myread | status: Passed\n");
    } else {
        printf("Test2 function: myread | status: Failed\n");
    }
    if (!strcmp(s2, "Our Ufs @c-Raz, Amir\n")) {
        printf("Test: Reading string | status: Passed\n");
    } else {
        printf("Test: Reading string | status: Failed\n");
    }

    //5,000 chars
    char *string2 = "razamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirvvrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamirrazamir";
    int openFile6 = myopen("home/Task7/BIG", 0);
    char *BIG = malloc(sizeof(char) * 15);

    ///Test2 mywrite function
    int myWrite2 = mywrite(openFile6, string2, 5000);
    assert(myWrite2 != -1);
    if (myWrite2 != -1) {
        printf("Test2 function: mywrite | status: Passed\n");
    } else {
        printf("Test2 function: mywrite | status: Failed\n");
    }


    ///Test 3 myread function
    int myRead3 = myread(openFile6, BIG, 15);
    assert(myRead3 != -1);
    if (myRead3 != -1) {
        printf("Test2 function: myread | status: Passed\n");
    } else {
        printf("Test2 function: myread | status: Failed\n");
    }

    ///Test 3 mylseek function
    int myLseek3 = mylseek(openFile6, -15, SEEK_CUR);
    assert(myLseek3 != -1);
    if (myLseek3 != -1) {
        printf("Test3 function: mylseek | status: Passed\n");
    } else {
        printf("Test3 function: mylseek | status: Failed\n");
    }
    assert(!strcmp(BIG, "rrazamirrazamir"));
    if (!strcmp(BIG, "rrazamirrazamir")) {
        printf("Test2: Reading string | status: Passed\n");
    } else {
        printf("Test2: Reading string | status: Failed\n");
    }
    ///Test 3 mymount function
    int mymMount=mymount("fs_data.txt", "home", NULL,0,"Task7");
    assert(mymMount);
    if (mymMount) {
        printf("Test function: mymount | status: Passed\n");
    } else {
        printf("Test function: mymount | status: Failed\n");
    }


    printf("*************************************************\n");
    printf("Print the Superblock info: ");
    print_fs();
    printf("\nWe were pleased to present our file system implementation!\n");

    printf("*********************************************************************************\n");
    printf("============ Welcome to our file system implementation | MYLIBC TEST ============\n");
    printf("*********************************************************************************\n");

    myFILE *myfd = myfopen("home/Task7/BIG", "r");
    if (sizeof (myfd->data)>0) {
        printf("Test function: myfopen | data | status: Passed\n");
    } else {
        printf("Test function: myopen| data  | status: Failed\n");
    }
    if (sizeof (myfd->mode)>0) {
        printf("Test function: myfopen | mode | status: Passed\n");
    } else {
        printf("Test function: myopen| mode  | status: Failed\n");
    }
    if ( (myfd->size)== (strlen (string2)-42)) {// we remove the size because we want only the string
        printf("Test function: myfopen | size | status: Passed\n");
    } else {
        printf("Test function: myopen| size  | status: Failed\n");
    }
    if (sizeof (myfd->pointerFile)>0) {
        printf("Test function: myfopen | pointerFile | status: Passed\n");
    } else {
        printf("Test function: myopen| pointerFile  | status: Failed\n");
    }
    if (sizeof (myfd->fd)>0) {
        printf("Test function: myfopen | fd | status: Passed\n");
    } else {
        printf("Test function: myopen| fd  | status: Failed\n");
    }
    ///Test myfwrite
    int myFwrite=myfwrite("abcds",1, 5,myfd);
    if  (myFwrite==(int) (myfd->data)+5) {
        printf("Test function: myfwrite | status: Passed\n");
    } else {
        printf("Test function: myfwrite  | status: Failed\n");
    }
    ///Test myfwrite
    char read[256];
    int myFread = myfread(read,1, 256, myfd);
    if  (myFread>0) {
        printf("Test function: myfread | status: Passed\n");
    } else {
        printf("Test function: myfread  | status: Failed\n");
    }


    ///Test myfprintf
    char input_ch = 'R';
    int input_num = 10;
    if  (myfprintf(myfd, "%c%d", input_ch, input_num)) {
        printf("Test function: myfprintf | status: Passed\n");
    } else {
        printf("Test function: myfprintf  | status: Failed\n");
    }

    //Test myfscanf
    if  (myfscanf(myfd, "%c%d", &input_ch, &input_num)) {
        printf("The input char and number (accordingly) are: %c, %d!\n", input_ch, input_num);
        printf("Test function: myfscanf | status: Passed\n");
    } else {
        printf("Test function: myfscanf  | status: Failed\n");
    }

    //Test myfseek
    int resFseek = myfseek(myfd, 1, 1);
    assert(resFseek != -1);
    if  (resFseek != -1) {
        printf("Test function: myfseek | status: Passed\n");
    } else {
        printf("Test function: myfseek  | status: Failed\n");
    }

    /* Check fclose function*/
    int res = myfclose(myfd);
    assert(res != -1);
    if  (res != -1) {
        printf("Test function: myfclose | status: Passed\n");
    } else {
        printf("Test function: myfclose  | status: Failed\n");
    }
    printf("*************************************************\n");
    return 0;
}
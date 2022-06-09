#include "myfs.h"
#include <stdio.h>
#include <string.h>


int main() {
    printf("*****************************************\n");
    printf("Welcome to our file system implementation\n");
    printf("*****************************************\n");
    create_fs();
    ///Test myopendir functuin:
    int openDir1 = myopendir("home/Task7");
    int openDir2 = myopendir("home/Task7");

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

    if (openFile1 == openFile2) {
        printf("Test function: myopen | status: Passed\n");
    } else {
        printf("Test function: myopen | status: Failed\n");
    }
    if (openFile3 == openFile5) {
        printf("Test function: myopen | status: Passed\n");
    } else {
        printf("Test function: myopen | status: Failed\n");
    }

    ///Test two different folders but the same file inside them
    if (openFile3 == openFile4) {
        printf("Test: different folders | status: Passed\n");
    } else {
        printf("Test: different folders | status: Failed\n");
    }
    if (openFile5 == openFile3) {
        printf("Test: different folders | status: Passed\n");
    } else {
        printf("Test: different folders | status: Failed\n");
    }
    if (openFile5 == openFile4) {
        printf("Test: different folders | status: Passed\n");
    } else {
        printf("Test: different folders | status: Failed\n");
    }


    ///Test myclose functuin:
    openFile2 = myclose(openFile2);
    if (openFile1 != openFile2) {
        printf("Test function: myclose | status: Passed\n");
    } else {
        printf("Test function: myclose | status: Failed\n");
    }

    ///Test mywrite function
    char *string = "Our Ufs @c-Raz, Amir\n";
    int myWrite = mywrite(openFile3, string, 25);
    if (myWrite != -1) {
        printf("Test function: mywrite | status: Passed\n");
    } else {
        printf("Test function: mywrite | status: Failed\n");
    }

    ///Test mylseek function
    char s1[30], s2[30];
    int myLseek = mylseek(openFile3, -30, SEEK_CUR);
    if (myLseek != -1) {
        printf("Test function: mylseek | status: Passed\n");
    } else {
        printf("Test function: mylseek | status: Failed\n");
    }

    ///Test myread function
    int myRead = myread(openFile3, s1, 25);
    if (myRead != -1) {
        printf("Test function: myread | status: Passed\n");
    } else {
        printf("Test function: myread | status: Failed\n");
    }

    ///Test 2 mylseek function
    int myLseek2 = mylseek(openFile3, -20, SEEK_CUR);
    if (myLseek2 != -1) {
        printf("Test2 function: mylseek | status: Passed\n");
    } else {
        printf("Test2 function: mylseek | status: Failed\n");
    }

    ///Test 2 myread function
    int myRead2 = myread(openFile3, s2, 25);
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
    if (myWrite2 != -1) {
        printf("Test2 function: mywrite | status: Passed\n");
    } else {
        printf("Test2 function: mywrite | status: Failed\n");
    }


    ///Test 3 myread function
    int myRead3 = myread(openFile6, BIG, 15);
    if (myRead3 != -1) {
        printf("Test2 function: myread | status: Passed\n");
    } else {
        printf("Test2 function: myread | status: Failed\n");
    }

    ///Test 3 mylseek function
    int myLseek3 = mylseek(openFile6, -15, SEEK_CUR);
    if (myLseek3 != -1) {
        printf("Test3 function: mylseek | status: Passed\n");
    } else {
        printf("Test3 function: mylseek | status: Failed\n");
    }

    if (!strcmp(BIG, "rrazamirrazamir")) {
        printf("Test2: Reading string | status: Passed\n");
    } else {
        printf("Test2: Reading string | status: Failed\n");
    }
    ///Test 3 mymount function
    int mymMount=mymount("fs_data.txt", "home", NULL,0,"Task7");
    if (mymMount) {
        printf("Test function: mymount | status: Passed\n");
    } else {
        printf("Test function: mymount | status: Failed\n");
    }


    printf("\n*************************************************\n");
    printf("Print the Superblock info: ");
    print_fs();
    printf("\nWe were pleased to present our file system implementation!\n");

    return 0;
}

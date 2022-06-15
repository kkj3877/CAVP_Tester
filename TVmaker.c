#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TVmaker.h"

int main(void)
{
    unsigned int ret;

    int passState_KEY_IV_PT_CT[] = { 1, 1, 1, 0 };
    ret = txtToReq_NonePass("ARIA/ARIA256(CBC)KAT.txt", "ARIA/ARIA256(CBC)KAT.req", passState_KEY_IV_PT_CT, 4, 2001, 100);


    // ret = HMAC_SHA256_Make("Test_List/HMAC-SHA256.txt", "Test_List/TV_HMAC-SHA256.req", 1577);

    // ret = SHA2_TV_Make("Test_List/SHA2(256)ShortMsg.txt", "Test_List/TV_SHA2(256)ShortMsg.req", 262);
    // ret = SHA2_TV_Make("Test_List/SHA2(256)LongMsg.txt", "Test_List/TV_SHA2(256)LongMsg.req", 258);
    // ret = SHA2_MCT_TV_Make("Test_List/SHA2(256)Monte.txt", "Test_List/TV_SHA2(256)Monte.req");

    // ret = LEA_TV_Make("Test_List/LEA256(CBC)KAT.txt", "Test_List/TV_LEA256(CBC)KAT.req", 2021);
    // ret = LEA_TV_Make("Test_List/LEA256(CBC)MMT.txt", "Test_List/TV_LEA256(CBC)MMT.req", 51);
    // ret = LEA_MCT_TV_Make("Test_List/LEA256(CBC)MCT.txt", "Test_List/TV_LEA256(CBC)MCT.req");
}

void copyLine(char * buffer, unsigned int BUFFER_SIZE, FILE * src, FILE * dest)
{
    fgets(buffer, BUFFER_SIZE, src);
    fputs(buffer, dest);
}

void passLine(FILE * src)
{
    int c;
    while ((c = fgetc(src)) != '\n') { }
}

unsigned int txtToReq_NonePass(const char * txtFileName, const char * reqFileName, const int * passNonPass, unsigned int lineNumOfSet, unsigned int numOfLine, unsigned int BUFFER_SIZE)
{
    unsigned int ret = EXIT_FAILURE;
    
    unsigned int i, j;

    char * buffer;

    FILE * txtFile, * reqFile;

    printf("txtToReq_NonePass(%s, %s)\n", txtFileName, reqFileName);

    txtFile = fopen(txtFileName, "r");
    if (!txtFile) { perror("txtFile Opening Failed"); return ret; }

    reqFile = fopen(reqFileName, "w+");
    if (!txtFile) { perror("reqFile Opening Failed"); return ret; }

    buffer = (char*)malloc(sizeof(char) * BUFFER_SIZE);

    for (i = 1; i < numOfLine - 2; i += lineNumOfSet + 1)
    {
        for (j = 0; j < lineNumOfSet; ++j) {
            if (passNonPass[j]) copyLine(buffer, BUFFER_SIZE, txtFile, reqFile);
            else passLine(txtFile);
        }
        copyLine(buffer, BUFFER_SIZE, txtFile, reqFile);
    }

    free(buffer);

    fclose(reqFile);
    fclose(txtFile);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TVmaker.h"

int main(void)
{
    unsigned int ret;

    // ret = makeTV_ARIA();
    // ret = makeTV_LEA();
    ret = makeTV_SHA2();


}

void copyLine(char * buffer, unsigned int BUFFER_SIZE, FILE * src, FILE * dest)
{
    fgets(buffer, BUFFER_SIZE, src);
    fputs(buffer, dest);
}

void copyLineWithoutBuffer(FILE * src, FILE * dest)
{
    int c;
    while ((c = fgetc(src)) != '\n')
    {
        fputc(c, dest);
    }
    fputc(c, dest);
}

void passLine(FILE * src)
{
    int c;
    while ((c = fgetc(src)) != '\n') { }
}

unsigned int txtToReq_NonPass(const char * txtFileName, const char * reqFileName, const int * passNonPass, unsigned int lineNumOfSet, unsigned int numOfLine, unsigned int BUFFER_SIZE)
{
    unsigned int ret = EXIT_FAILURE;
    
    unsigned int i, j;

    char * buffer;

    FILE * txtFile, * reqFile;

    printf(">> txtToReq_NonePass(%s, %s)\n", txtFileName, reqFileName);

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

unsigned int txtToReq_Pass(const char * txtFileName, const char * reqFileName, const int * passNonPass, unsigned int lineNumOfSet, unsigned int numOfLine, unsigned int BUFFER_SIZE, unsigned int numOfPassLine)
{
    unsigned int ret = EXIT_FAILURE;
    
    unsigned int i, j;

    char * buffer;

    FILE * txtFile, * reqFile;

    printf(">> txtToReq_NonePass(%s, %s)\n", txtFileName, reqFileName);

    txtFile = fopen(txtFileName, "r");
    if (!txtFile) { perror("txtFile Opening Failed"); return ret; }

    reqFile = fopen(reqFileName, "w+");
    if (!txtFile) { perror("reqFile Opening Failed"); return ret; }

    buffer = (char*)malloc(sizeof(char) * BUFFER_SIZE);

    for (i = 1; i < numOfPassLine + 1; ++i) passLine(txtFile);

    for (i = numOfPassLine + 1; i < numOfLine - 2; i += lineNumOfSet + 1)
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

unsigned int txtToReq_PassWithCopy(const char * txtFileName, const char * reqFileName, const int * passNonPass, unsigned int lineNumOfSet, unsigned int numOfLine, unsigned int BUFFER_SIZE, unsigned int numOfPassLine)
{
    unsigned int ret = EXIT_FAILURE;
    
    unsigned int i, j;

    char * buffer;

    FILE * txtFile, * reqFile;

    printf(">> txtToReq_NonePass(%s, %s)\n", txtFileName, reqFileName);

    txtFile = fopen(txtFileName, "r");
    if (!txtFile) { perror("txtFile Opening Failed"); return ret; }

    reqFile = fopen(reqFileName, "w+");
    if (!txtFile) { perror("reqFile Opening Failed"); return ret; }

    buffer = (char*)malloc(sizeof(char) * BUFFER_SIZE);

    for (i = 1; i < numOfPassLine + 1; ++i) copyLine(buffer, BUFFER_SIZE, txtFile, reqFile);

    for (i = numOfPassLine + 1; i < numOfLine - 2; i += lineNumOfSet + 1)
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

unsigned int makeTV_ARIA(void)
{
    unsigned int ret = 0;

    int passState_KEY_PT_CT[] = { 1, 1, 0 };
    int passState_KEY_IV_PT_CT[] = { 1, 1, 1, 0 };
    int passState_MCT[] = { 1, 1, 1, 0 };
    int passState_MCT_NON_IV[] = { 1, 1, 0 };

    ret = txtToReq_NonPass("ARIA/ARIA256(ECB)KAT.txt", "ARIA/req/ARIA256(ECB)KAT.req", passState_KEY_PT_CT, 3, 1601, 100);
    ret = txtToReq_Pass("ARIA/ARIA256(ECB)MCT.txt", "ARIA/req/ARIA256(ECB)MCT.req", passState_MCT_NON_IV, 3, 6, 100, 1);
    ret = txtToReq_NonPass("ARIA/ARIA256(ECB)MMT.txt", "ARIA/req/ARIA256(ECB)MMT.req", passState_KEY_PT_CT, 3, 41, 350);

    ret = txtToReq_NonPass("ARIA/ARIA256(CBC)KAT.txt", "ARIA/req/ARIA256(CBC)KAT.req", passState_KEY_IV_PT_CT, 4, 2001, 100);
    ret = txtToReq_Pass("ARIA/ARIA256(CBC)MCT.txt", "ARIA/req/ARIA256(CBC)MCT.req", passState_MCT, 4, 7, 100, 1);
    ret = txtToReq_NonPass("ARIA/ARIA256(CBC)MMT.txt", "ARIA/req/ARIA256(CBC)MMT.req", passState_KEY_IV_PT_CT, 4, 51, 350);

    ret = txtToReq_NonPass("ARIA/ARIA256(CTR)KAT.txt", "ARIA/req/ARIA256(CTR)KAT.req", passState_KEY_IV_PT_CT, 4, 2001, 100);
    ret = txtToReq_Pass("ARIA/ARIA256(CTR)MCT.txt", "ARIA/req/ARIA256(CTR)MCT.req", passState_MCT, 4, 7, 100, 1);
    ret = txtToReq_NonPass("ARIA/ARIA256(CTR)MMT.txt", "ARIA/req/ARIA256(CTR)MMT.req", passState_KEY_IV_PT_CT, 4, 51, 350);

    return ret;
}

unsigned int makeTV_LEA(void)
{
    unsigned int ret = 0;

    int passState_KEY_PT_CT[] = { 1, 1, 0 };
    int passState_KEY_IV_PT_CT[] = { 1, 1, 1, 0 };
    int passState_MCT[] = { 1, 1, 1, 0 };
    int passState_MCT_NON_IV[] = { 1, 1, 0 };

    ret = txtToReq_NonPass("LEA/LEA256(ECB)KAT.txt", "LEA/req/LEA256(ECB)KAT.req", passState_KEY_PT_CT, 3, 1617, 100);
    ret = txtToReq_Pass("LEA/LEA256(ECB)MCT.txt", "LEA/req/LEA256(ECB)MCT.req", passState_MCT_NON_IV, 3, 6, 100, 1);
    ret = txtToReq_NonPass("LEA/LEA256(ECB)MMT.txt", "LEA/req/LEA256(ECB)MMT.req", passState_KEY_PT_CT, 3, 41, 350);

    ret = txtToReq_NonPass("LEA/LEA256(CBC)KAT.txt", "LEA/req/LEA256(CBC)KAT.req", passState_KEY_IV_PT_CT, 4, 2021, 100);
    ret = txtToReq_Pass("LEA/LEA256(CBC)MCT.txt", "LEA/req/LEA256(CBC)MCT.req", passState_MCT, 4, 7, 100, 1);
    ret = txtToReq_NonPass("LEA/LEA256(CBC)MMT.txt", "LEA/req/LEA256(CBC)MMT.req", passState_KEY_IV_PT_CT, 4, 51, 350);

    ret = txtToReq_NonPass("LEA/LEA256(CTR)KAT.txt", "LEA/req/LEA256(CTR)KAT.req", passState_KEY_IV_PT_CT, 4, 2021, 100);
    ret = txtToReq_Pass("LEA/LEA256(CTR)MCT.txt", "LEA/req/LEA256(CTR)MCT.req", passState_MCT, 4, 7, 100, 1);
    ret = txtToReq_NonPass("LEA/LEA256(CTR)MMT.txt", "LEA/req/LEA256(CTR)MMT.req", passState_KEY_IV_PT_CT, 4, 51, 350);

    return ret;
}

unsigned int makeTV_SHA2(void)
{
    unsigned int ret = 0;

    int passState_LEN_MSG_MD[] = { 1, 1, 0 };
    int passState_SEED[] = { 1 };

    ret = txtToReq_PassWithCopy("SHA2/SHA2(256)ShortMsg.txt", "SHA2/req/SHA2(256)ShortMsg.req", passState_LEN_MSG_MD, 3, 263, 150, 2);
    ret = txtToReq_PassWithCopy("SHA2/SHA2(256)LongMsg.txt", "SHA2/req/SHA2(256)LongMsg.req", passState_LEN_MSG_MD, 3, 259, 12850, 2);
    ret = txtToReq_PassWithCopy("SHA2/SHA2(256)Monte.txt", "SHA2/req/SHA2(256)Monte.req", NULL, 0, 5, 100, 4);

    return ret;
}








#ifndef _TVMAKER_H_
#define _TVMAKER_H_

#include <stdlib.h>

void copyLine(char * buffer, unsigned int BUFFER_SIZE, FILE * src, FILE * dest);
void copyLineWithoutBuffer(FILE * src, FILE * dest);
void passLine(FILE * src);

unsigned int txtToReq_NonPass(const char * txtFileName, const char * reqFileName, const int * passNonPass, unsigned int lineNumOfSet, unsigned int numOfLine, unsigned int BUFFER_SIZE);
unsigned int txtToReq_Pass(const char * txtFileName, const char * reqFileName, const int * passNonPass, unsigned int lineNumOfSet, unsigned int numOfLine, unsigned int BUFFER_SIZE, unsigned int numOfPassLine);
unsigned int txtToReq_PassWithCopy(const char * txtFileName, const char * reqFileName, const int * passNonPass, unsigned int lineNumOfSet, unsigned int numOfLine, unsigned int BUFFER_SIZE, unsigned int numOfPassLine);

unsigned int makeTV_ARIA(void);
unsigned int makeTV_LEA(void);
unsigned int makeTV_SHA2(void);
#endif

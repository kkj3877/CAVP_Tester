#ifndef _TVMAKER_H_
#define _TVMAKER_H_

#include <stdlib.h>

void copyLine(char * buffer, unsigned int BUFFER_SIZE, FILE * src, FILE * dest);
void passLine(FILE * src);

unsigned int txtToReq_NonPass(const char * txtFileName, const char * reqFileName, const int * passNonPass, unsigned int lineNumOfSet, unsigned int numOfLine, unsigned int BUFFER_SIZE);
unsigned int txtToReq_Pass(const char * txtFileName, const char * reqFileName, const int * passNonPass, unsigned int lineNumOfSet, unsigned int numOfLine, unsigned int BUFFER_SIZE, unsigned int numOfPassLine);


#endif

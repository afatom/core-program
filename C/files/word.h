#ifndef _WORD_H_
#define _WORD_H_
#include <stdlib.h>

typedef struct Word Word;

typedef struct WC WC;

void WordsCount(const char *_fileName);

int CountLetters(const char *_destFileName);

int EraseBlinks(const char *_destinationFile, const char *_sourceFile);

void PrintLastNLines(const char *_destinationFile, size_t _num);
#endif /*_WORD_H_*/

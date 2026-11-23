#ifndef BANKINGSYS_CRYPTO_H
#define BANKINGSYS_CRYPTO_H

#define SHIFT 7

#if SHIFT > 26
#warning "Shift size is too large"
#endif

#include <stdio.h>

void cryptString(char **string);
void decryptString(char **string);

#endif

#include "../include/cryptString.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

static int isLetter(char c)
{
	return 'a' <= (c | 0x20) && (c | 0x20) <= 'z';
}

static int isNumber(char c)
{
	return '0' <= c && c <= '9';
}

static char shiftLetter(char letter, int shift_len)
{
	shift_len %= 26;
	if (shift_len < 0)
		shift_len += 26;
	if ((letter | 0x20) + shift_len > 'z')
		return letter - (26 - shift_len);
	return letter + shift_len;
}

static char shiftNumber(char number, int shift_len)
{
	shift_len %= 10;
	if (shift_len < 0)
		shift_len += 10;
	if (number + shift_len > '9')
		return number - (10 - shift_len);
	return number + shift_len;
}

void cryptString(char **string)
{
	size_t string_len = strlen(*string);
	for (size_t i = 0; i < string_len; ++i) {
		if (isLetter((*string)[i]))
			(*string)[i] = shiftLetter((*string)[i], SHIFT);
		else if (isNumber((*string)[i]))
			(*string)[i] = shiftNumber((*string)[i], -SHIFT);
	}
}

void decryptString(char **string)
{
	for (int i = 0; i < (int)strlen(*string); ++i) {
		if (isalpha((*string)[i]))
			(*string)[i] = shiftLetter(((*string)[i]), SHIFT);
		else if (isdigit(((*string)[i])))
			(*string)[i] = shiftNumber(((*string)[i]), -SHIFT);
	}
}

#ifndef UTIL_H
#define UTIL_H

#include <ctype.h>

inline unsigned long long strtoull(const char *nptr, char *endptr, int base)
{
	const char *s = nptr;
	unsigned long long acc;
	unsigned char c;
	unsigned long long qbase, cutoff;
	int neg, any, cutlim;

	s = nptr;
	do {
		c = *s++;
	} while (isspace(c));
	if (c == '-') {
		neg = 1;
		c = *s++;
	}
	else {
		neg = 0;
		if (c == '+')
			c = *s++;
	}
	if ((base == 0 || base == 16) &&
		c == '0' && (*s == 'x' || *s == 'X')) {
		c = s[1];
		s += 2;
		base = 16;
	}
	if (base == 0)
		base = c == '0' ? 8 : 10;
	qbase = (unsigned)base;
	cutoff = (unsigned long long)18446744073709551615 / qbase;
	cutlim = (unsigned long long)18446744073709551615 % qbase;
	for (acc = 0, any = 0;; c = *s++) {
		if (!isascii(c))
			break;
		if (isdigit(c))
			c -= '0';
		else if (isalpha(c))
			c -= isupper(c) ? 'A' - 10 : 'a' - 10;
		else
			break;
		if (c >= base)
			break;
		if (any < 0 || acc > cutoff || (acc == cutoff && c > cutlim))
			any = -1;
		else {
			any = 1;
			acc *= qbase;
			acc += c;
		}
	}
	if (any < 0) {
		acc = 18446744073709551615;
	}
	else if (neg)
		acc = -acc;
	//if (endptr != 0)
	//    *endptr = (char *)(any ? s - 1 : nptr);
	return (acc);
}

inline char * uintToStr(const uint64_t num, char *str)
{
	uint8_t i = 0;
	uint64_t n = num;

	do
		i++;
	while (n /= 10);

	str[i] = '\0';
	n = num;

	do
		str[--i] = (n % 10) + '0';
	while (n /= 10);

	return str;
}

#ifdef __arm__
// should use uinstd.h to define sbrk but Due causes a conflict
extern "C" char* sbrk(int incr);
#else  // __ARM__
extern char *__brkval;
#endif  // __arm__
//Gets the remaining free memory.
inline int GetFreeMemory() {
	char top;
#ifdef __arm__
	return &top - reinterpret_cast<char*>(sbrk(0));
#elif defined(CORE_TEENSY) || (ARDUINO > 103 && ARDUINO != 151)
	return &top - __brkval;
#else  // __arm__
	return __brkval ? &top - __brkval : &top - __malloc_heap_start;
#endif  // __arm__
}

#endif
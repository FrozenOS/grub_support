#ifndef COMMON_H
#define COMMON_H

#include <stddef.h>
#include <stdint.h>

static inline void *memcpy(void *restrict dest, const void *restrict src, size_t size) {
	uint8_t *d = dest;
	const uint8_t *s = src;

	for (size_t i = 0; i < size; i++) {
		d[i] = s[i];
	}

	return dest;
}

static inline void *memset(void *s, uint8_t c, size_t n) {
	uint8_t *ss = s;

	for (size_t i = 0; i < n; i++) {
		ss[i] = c;
	}

	return s;
}

#endif

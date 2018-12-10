#include "example.h"

// int8_t is defined by c standard while int8 is not (same for 32) in C99
// Different from int since that can be any size >= 16 bytes
int8_t AverageThreeBytes(int8_t a, int8_t b, int8_t c){
	return (int8_t)(((int16_t)a + (int16_t)b + (int16_t)c) / 3);
}


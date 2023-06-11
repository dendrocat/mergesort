#pragma once

#include <stdio.h>
#include <stdlib.h>

// typedef можно убрать и везде вместо него везде поставить unsigned int или просто int
typedef unsigned long long int size_t;

int mergesort(void* arr, size_t elements, size_t element_size,
	int (*comparator)(const void*, const void*));

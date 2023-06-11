#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "mergesort.h"

int int_comparator(const void* a, const void* b) {
	return *(int*)a - *(int*)b;
}

int char_comparator(const void* a, const void* b) {
	// сначала приводим void указатель к указателю на char
	// затем разыменовываем его и получаем char
	char ca = *(char*)a;
	char cb = *(char*)b;
	if (ca > cb) return 1;
	else if (ca < cb) return -1;
	else return 0;
}

int str_comparator(const void* a, const void* b) {
	//сначала приводим void указатель к указателю на char*
	// затем разыменовываем и получаем char*
	char* ca = *(char**)a;
	char* cb = *(char**)b;
	return strcmp(ca, cb);
}

int main(int argc, char** argv[]) {
	// указатель на фукнцию comparator
	int (*comparator) (const void*, const void*);
	void* data;
	int el_size;
	int size = argc - 2;
	if (strcmp(argv[1], "int") == 0) {
		comparator = int_comparator;
		data = malloc(sizeof(int)*size);
		for (int i = 0; i < size; i++) {
			((int*)data)[i] = atoi(argv[i + 2]);
		}
		el_size = sizeof(int);
	}
	else if (strcmp(argv[1], "char") == 0) {
		comparator = char_comparator;
		data = malloc(sizeof(char)*size);
		for (int i = 0; i < size; i++) {
			// argv[i] - строка, она является символом char + '\0'
			// поэтому берем только 1-й символ
			((char*)data)[i] = argv[i + 2][0];
		}
		el_size = sizeof(char);
	}
	else {
		comparator = str_comparator;
		data = malloc(sizeof(char*)*size);
		for (int i = 0; i < size; i++) {
			((char**)data)[i] = argv[i + 2];
		}
		el_size = sizeof(char**);
	}
	if (mergesort(data, size, el_size, comparator)) {
		printf("Error: memory allocation failed");
		return 1;
	}
	if (strcmp(argv[1], "int") == 0) {
		for (int i = 0; i < size; i++) {
			printf("%d", ((int*)data)[i]);
			if (i != size - 1) printf(" ");
		}
	}
	else if (strcmp(argv[1], "char") == 0)
		for (int i = 0; i < size; i++) {
			printf("%c", ((char*)data)[i]);
			if (i != size - 1) printf(" ");
		}
	else
		for (int i = 0; i < size; i++) {
			printf("%s", ((char**)data)[i]);
			if (i != size - 1) printf(" ");
		}
	printf("\n");
	free(data);
	return 0;
}
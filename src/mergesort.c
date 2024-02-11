#include "../mergesort/src_h/mergesort.h"

int mergesort(void* arr, size_t elements, size_t element_size,
	int (*comparator)(const void*, const void*))
{
	int res = 0;
	void* res_arr = malloc(elements * element_size);
	if (!res_arr) return 1;
	// переводим все void указатели в char указатели
	// зачем переводим? да чтоб была возможность проходить по массиву с помощью арифметики указателей
	// у void* не работает арифметика указателей
	char* res_arr0 = res_arr;
	char* arr0 = arr;
	size_t size_prom_arr = 1; // размер промежуточных массивов
	// т.е тех которые склеиваются
	
	while (size_prom_arr < elements) {
		size_t step = size_prom_arr;
		size_t p_arr = 0, k = 0; // p_arr - позиция первого массива для слияния
		while (p_arr < elements) {
			size_t i = p_arr, j = p_arr + step;
			// i - позиция элемента первого массива для слияния, j - второго
			// цикл для слияния массивов
			while ((i < p_arr + step) && (j < elements) && (j < p_arr + 2 * step)) {
				// element_size - размер элемента в байтах
				// i * element_size - сдвиг на i элементов
				// arr0 + i * element_size - получение i-того элемента массива arr
				void* a = arr0 + i * element_size;
				void* b = arr0 + j * element_size;
				// res - результат сравнения, comparator работает также как и strcmp
				res = comparator(a, b);
				if (res < 0) {
					// из-за того, что указатель на void нельзя разыменовать,
					// приходится копировать весь участок памяти, на который указывает void указатель
					memcpy(res_arr0 + k * element_size, a, element_size);
					k++; i++;
				}
				else {
					memcpy(res_arr0 + k * element_size, b, element_size);
					k++; j++;
				}
			}
			// циклы для склеивания остатков массивов
			while ((i < p_arr + step) && (i < elements)) {
				memcpy(res_arr0 + k * element_size, arr0 + i * element_size, element_size);
				k++; i++;
			}
			while ((j < elements) && (j < p_arr + 2 * step)) {
				memcpy(res_arr0 + k * element_size, arr0 + j * element_size, element_size);
				k++; j++;
			}
			//перешагиваем через склеенный массив
			p_arr += 2 * step;
		}
		// все массивы предыдущего размера склеены
		// значит, увеличиваем размер всех оставшихся массивов как минимум
		// два размера предыдущих
		// меньше этого числа может быть на границе основого массива
		size_prom_arr = size_prom_arr * 2;
		
		//перенос из буфера в основной массив промежуточного/конечного результата
		for (size_t i = 0; i < elements; i++) {
			memcpy(arr0 + i * element_size, res_arr0 + i * element_size, element_size);
		}
	}
	// обнуляем указатели, чтобы не удалилось лишнего
	arr0 = NULL;
	res_arr0 = NULL;
	free(res_arr);
	return 0;
}

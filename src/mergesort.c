#include "mergesort.h"

int mergesort(void* arr, size_t elements, size_t element_size,
	int (*comparator)(const void*, const void*))
{
	//show_arr(arr, elements, element_size);
	int res = 0;
	void* res_arr = malloc(elements * element_size);
	if (!res_arr) return 1;
	// ��������� ��� void ��������� � char ���������
	// ������ ��������� �� ����, �� �����, ������ �����, ��-�� ������� ���� char 
	// ����� ���������� �� 1 ���� ��� ������������� ���������� ����������
	// ����� ���������? �� ���� ���� ����������� ��������� �� ������� � ������� ���������� ����������
	char* res_arr0 = res_arr;
	char* arr0 = arr;
	size_t size_prom_arr = 1; // ������ ������������� ��������
	// �.� ��� ������� �����������
	
	while (size_prom_arr < elements) {
		size_t step = size_prom_arr;
		int p_arr = 0, k = 0; // p_arr - ������� ������� ������� ��� �������
		while (p_arr < elements) {
			int i = p_arr, j = p_arr + step;
			// i - ������� �������� ������� ������� ��� �������, j - �������
			// ���� ��� ������� ������
			while ((i < p_arr + step) && (j < elements) && (j < p_arr + 2 * step)) {
				// ���������� � ���������� �� void
				// element_size - ������ �������� � ������
				// i * element_size - ����� �� i ���������
				// arr0 + i * element_size - ��������� i-���� �������� ������� arr
				//printf("%s\t%s\n", ((char**)arr)[i], ((char**)arr)[j]);
				void* a = arr0 + i * element_size;
				void* b = arr0 + j * element_size;
				// res - ��������� ���������, compar �������� ����� ��� � strcmp
				res = comparator(a, b);
				if (res < 0) {
					// ������� � ���������� �� void
					// ��-�� ����, ��� ��������� �� void ������ ������������,
					// ���������� ���������� ���� ������� ������, �� ������� ��������� void ���������
					memcpy(res_arr0 + k * element_size, a, element_size);
					k++; i++;
				}
				else {
					memcpy(res_arr0 + k * element_size, b, element_size);
					k++; j++;
				}
			}
			// ����� ��� ���������� �������� ��������
			while ((i < p_arr + step) && (i < elements)) {
				memcpy(res_arr0 + k * element_size, arr0 + i * element_size, element_size);
				k++; i++;
			}
			while ((j < elements) && (j < p_arr + 2 * step)) {
				memcpy(res_arr0 + k * element_size, arr0 + j * element_size, element_size);
				k++; j++;
			}
			//������������ ����� ������ ������
			p_arr += 2 * step;
		}
		// ��� ������� ����������� ������� �������
		// ������, ����������� ������ ���� ���������� �������� ��� �������
		// ��� ������� ����������
		// ������ ����� ����� ����� ���� �� ������� �������� �������
		size_prom_arr = size_prom_arr * 2;
		
		//������� �� ������ � �������� ������ ��������������/��������� ����������
		for (size_t i = 0; i < elements; i++) {
			memcpy(arr0 + i * element_size, res_arr0 + i * element_size, element_size);
		}
	}
	// �������� ���������, ����� �� ��������� �������
	arr0 = NULL;
	res_arr0 = NULL;
	free(res_arr);
	return 0;
}
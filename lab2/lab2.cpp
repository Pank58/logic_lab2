#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

const int size = 100000;
int randmasShell[size], randmasQs[size], randmasQsort[size], increasmasShell[size], increasmasQs[size], increasmasQsort[size];
int decreasmasShell[size], decreasmasQs[size], decreasmasQsort[size], incdecmasShell[size], incdecmasQs[size], incdecmasQsort[size];

void copyArray(int* source, int* destination, int* destination2, int size) {
	for (int i = 0; i < size; i++) {
		destination[i] = source[i];
		destination2[i] = source[i];
	}
}

void shell(int* items, int count) {
	int i, j, gap, k;
	int x, a[5];

	a[0] = 9; a[1] = 5; a[2] = 3; a[3] = 2; a[4] = 1;

	for (k = 0; k < 5; k++) {
		gap = a[k];
		for (i = gap; i < count; ++i) {
			x = items[i];
			for (j = i - gap; (x < items[j]) && (j >= 0); j = j - gap)
				items[j + gap] = items[j];
			items[j + gap] = x;
		}
	}
}

int compare(const void* a, const void* b) {
	return (*(int*)a - *(int*)b);
}

void qs(int* items, int left, int right) {
	int i, j;
	int x, y;

	i = left; j = right;
	x = items[(left + right) / 2];

	do {
		while ((items[i] < x) && (i < right)) i++;
		while ((x < items[j]) && (j > left)) j--;

		if (i <= j) {
			y = items[i];
			items[i] = items[j];
			items[j] = y;
			i++; j--;
		}
	} while (i <= j);

	if (left < j) qs(items, left, j);
	if (i < right) qs(items, i, right);
}
int main(){
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	double timeR1, timeR2, timeR3, timeI1, timeI2, timeI3, timeD1, timeD2, timeD3, timeID1, timeID2, timeID3;

	for (int i = 0; i < size; i++) {
		randmasShell[i] = rand() % 2000;
		increasmasShell[i] = i;
		decreasmasShell[i] = size - i;
		incdecmasShell[i] = (i < size / 2) ? i : size - 1;
	}

	copyArray(randmasShell, randmasQs, randmasQsort, size);
	copyArray(increasmasShell, increasmasQs, increasmasQsort, size);
	copyArray(decreasmasShell, decreasmasQs, decreasmasQsort, size);
	copyArray(incdecmasShell, incdecmasQs, incdecmasQsort, size);

	clock_t start = clock();
	shell(randmasShell, size);
	clock_t end = clock();
	timeR1 = ((double)(end - start) / CLOCKS_PER_SEC);

	start = clock();
	qs(randmasQs, 0, size-1);
	end = clock();
	timeR2 = ((double)(end - start) / CLOCKS_PER_SEC);

	start = clock();
	qsort(randmasQsort, size, sizeof(int), compare);
	end = clock();
	timeR3 = ((double)(end - start) / CLOCKS_PER_SEC);


	start = clock();
	shell(increasmasShell, size);
	end = clock();
	timeI1 = ((double)(end - start) / CLOCKS_PER_SEC);

	start = clock();
	qs(increasmasQs, 0, size - 1);
	end = clock();
	timeI2 = ((double)(end - start) / CLOCKS_PER_SEC);

	start = clock();
	qsort(increasmasQsort, size, sizeof(int), compare);
	end = clock();
	timeI3 = ((double)(end - start) / CLOCKS_PER_SEC);


	start = clock();
	shell(decreasmasShell, size);
	end = clock();
	timeD1 = ((double)(end - start) / CLOCKS_PER_SEC);

	start = clock();
	qs(decreasmasQs, 0, size - 1);
	end = clock();
	timeD2 = ((double)(end - start) / CLOCKS_PER_SEC);

	start = clock();
	qsort(decreasmasQsort, size, sizeof(int), compare);
	end = clock();
	timeD3 = ((double)(end - start) / CLOCKS_PER_SEC);
	

	start = clock();
	shell(incdecmasShell, size);
	end = clock();
	timeID1 = ((double)(end - start) / CLOCKS_PER_SEC);

	start = clock();
	qs(incdecmasQs, 0, size - 1);
	end = clock();
	timeID2 = ((double)(end - start) / CLOCKS_PER_SEC);

	start = clock();
	qsort(incdecmasQsort, size, sizeof(int), compare);
	end = clock();
	timeID3 = ((double)(end - start) / CLOCKS_PER_SEC);

	printf("|     | Rand|  Inc|  Dec|IncDec|\n");
	printf("|-----|-----|-----|-----|------|\n");
	printf("|Shell|%3.3lf|%3.3lf|%3.3lf|%3.4lf|\n", timeR1, timeI1, timeD1, timeID1);
	printf("| QS  |%3.3lf|%3.3lf|%3.3lf|%3.4lf|\n", timeR2, timeI2, timeD2, timeID2);
	printf("|QSort|%3.3lf|%3.3lf|%3.3lf|%3.4lf|\n", timeR3, timeI3, timeD3, timeID3);

	return 0;

}
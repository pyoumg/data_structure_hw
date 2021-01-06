#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
	FILE *fp = NULL, *fp1 = NULL;
	int n, *arr, min, temp,step=10;
	double duration = 0;
	fp = fopen("lab1.data", "r");
	fp1 = fopen("lab2.txt", "w");
	fscanf(fp, "%d", &n);
	fprintf(fp1, "Input: ");
	arr = malloc(sizeof(int)*n);
	for (int i = 0; i < n; i++) {
		fscanf(fp, "%d", &arr[i]);
		fprintf(fp1, "%d", arr[i]);
		if (i != n - 1) {
			fprintf(fp1, ", ");
		}
	}

	fprintf(fp1, "\n");
	fprintf(fp1, "Sorted: ");
	clock_t start = clock();
	long repetitions = 0;
	do {
		repetitions++;
		for (int i = 0; i < n - 1; i++) {
			min = i;
			for (int j = i + 1; j < n; j++) {
				if (arr[min] > arr[j]) {
					min = j;
				}
			}
			temp = arr[i];
			arr[i] = arr[min];
			arr[min] = temp;
			

		}
	} while (clock() - start < 1000);
	duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
	duration /= repetitions;
	for (int i = 0; i < n-1; i++) {
		fprintf(fp1, "%d, ", arr[i]);
	}
	fprintf(fp1, "%d\n", arr[n - 1]);
	fprintf(fp1, "실행시간: %lf초", duration);


	free(arr);
	fclose(fp);
	fclose(fp1);
	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
	FILE *fp = NULL, *fp1 = NULL;
	int n, *arr, search, searched = -1;
	long repetitions = 0;
	double duration = 0;
	fp = fopen("lab1.data", "r");
	fp1 = fopen("lab2.txt", "w");
	fscanf(fp, "%d", &n);

	arr = malloc(sizeof(int)*n);
	for (int i = 0; i < n; i++) {
		arr[i] = i + 1;
	}
	fscanf(fp, "%d", &search);
	fprintf(fp1, "Input: %d\n", n);
	fprintf(fp1, "Search number: %d\n", search);

	clock_t start = clock();
	do {
		repetitions++;
		for (int i = 0; i < n; i++)
		{
			if (arr[i] == search) {
				searched = i;
				break;
			}

		}
	} while (clock() - start < 1000);
	duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
	duration /= repetitions;

	fprintf(fp1, "Searched: %d\n", searched);
	fprintf(fp1, "Time: %lf\n", duration);

	free(arr);
	fclose(fp);
	fclose(fp1);
	return 0;
}
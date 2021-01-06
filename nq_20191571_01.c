#include <stdio.h>
#include <stdlib.h>
int correct(int depth, int* arr, int* check);
void queen(int depth, int* arr, int* check);
int n,now=0;
int main() {
	printf("Input N: ");
	scanf("%d", &n);
	int *arr = calloc(n, sizeof(int));
	int *check = calloc(n, sizeof(int));
	queen(0,arr,check);
	if (now== 0) {
		printf("No solution");
	}
	free(arr);
	free(check);
	return 0;
}

void queen(int depth,int* arr,int* check) {
	if (depth == n && now == 0)
	{
		for (int i = 0; i < n; i++) {
			printf("%d ", arr[i]);
		}
		now = 1;

		return;
	}
	else if (now == 1)
		return;
	for (int i = 0; i < n; i++) {
		arr[depth] = i;
		check[i]++;
		if (correct(depth + 1, arr, check) == 1)
			queen(depth + 1, arr, check);
		check[i]--;
	}
}
int correct(int depth, int* arr,int* check) {
	for (int i = 0; i < n; i++) {
		if (check[i] > 1) {
			return 0;
		}
	}
	for (int i = 0; i < depth-1; i++) {
			if (abs(i - depth+1) == abs(arr[i] - arr[depth-1]))
				return 0;
	}
	return 1;
}
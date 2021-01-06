#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 50
typedef enum tagfield { head, entry } tagfield;
typedef struct matrix_node *matrix_pointer;
typedef struct entry_node {
	int row;
	int col;
	int value;
}entry_node;
typedef struct matrix_node {
	matrix_pointer down;
	matrix_pointer right;
	enum tagfield tag;
	union
	{
		matrix_pointer next;
		entry_node entry;
	} u;
}matrix_node;

matrix_pointer hdnode[MAX_SIZE];

matrix_pointer mread(FILE*);

void mwrite(matrix_pointer);
void merase(matrix_pointer*);

matrix_pointer new_node();

void main() {
	matrix_pointer a, b;

	FILE* fp1 = fopen("A.txt", "r");
	FILE* fp2 = fopen("B.txt", "r");
	a = mread(fp1);
	b = mread(fp2);
	mwrite(a);
	mwrite(b);
	merase(&a);
	merase(&b);
	mwrite(a);
	mwrite(b);


}
matrix_pointer mread(FILE* fp)
{
	int num_rows, num_cols, num_terms = 0, num_heads, i;
	int row, col, value, current_row = 0;

	matrix_pointer temp, last, node;
	fscanf(fp, "%d %d", &num_rows, &num_cols);

	num_heads = (num_cols > num_rows) ? num_cols : num_rows;
	node = new_node();
	node->tag = entry;
	node->u.entry.row = num_rows;
	node->u.entry.col = num_cols;

	if (!num_heads)
		node->right = node;
	else {
		for (i = 0; i < num_heads; i++) {
			temp = new_node();
			hdnode[i] = temp;
			hdnode[i]->tag = head;
			hdnode[i]->right = temp;
			hdnode[i]->u.next = temp;
		}
		current_row = 0;
		last = hdnode[0];
		for (i = 0; i < num_rows; i++) {
			for (int j = 0; j < num_cols; j++) {
				fscanf(fp, " %d", &value);
				if (value != 0) {
					num_terms++;
					row = i, col = j;
					if (row > current_row) {
						last->right = hdnode[current_row];
						current_row = row;
						last = hdnode[row];
					}

					temp = new_node();
					temp->tag = entry;
					temp->u.entry.col = col;
					temp->u.entry.row = row;
					temp->u.entry.value = value;
					last->right = temp;
					last = temp;

					hdnode[col]->u.next->down = temp;
					hdnode[col]->u.next = temp;
				}
			}
		}
		last->right = hdnode[current_row];
		for (i = 0; i < num_cols; i++)
			hdnode[i]->u.next->down = hdnode[i];
		for (i = 0; i < num_heads - 1; i++)
			hdnode[i]->u.next = hdnode[i + 1];
		hdnode[num_heads - 1]->u.next = node;
		node->right = hdnode[0];
	}
	fclose(fp);
	return node;
}



matrix_pointer new_node() {
	matrix_pointer n;
	n = (matrix_pointer)malloc(sizeof(*n));
	return n;
}



void mwrite(matrix_pointer node)
{
	int i;
	matrix_pointer temp, head;
	if (node == NULL) {
		printf("NODE is NULL\n");
		return; //행렬이 존재하지 않으므로 노드가 NULL이라는 내용을 출력하고 return
	}
	else {
		head = node->right;
		for (i = 0; i < node->u.entry.row; i++) {
			for (temp = head->right; temp != head; temp = temp->right)
				printf("%5d%5d%5d \n", temp->u.entry.row, temp->u.entry.col, temp->u.entry.value);
			head = head->u.next;
		}
	}
}

void merase(matrix_pointer *node) {
	matrix_pointer x, y;
	if (*node != NULL) {
		matrix_pointer head = (*node)->right;
		int i;
		for (i = 0; i < (*node)->u.entry.row; i++) {
			y = head->right;
			while (y != head)
			{
				x = y;
				y = y->right;
				free(x);
			}
			x = head;
			head = head->u.next;
			free(x);
		}
		y = head;
		while (y != *node)
		{
			x = y;
			y = y->u.next;
			free(x);
		}
		free(*node);
		*node = NULL;
	}
	else {
		printf("NODE is NULL\n"); //NULL parameter인 경우 경고문 출력 
	}
}




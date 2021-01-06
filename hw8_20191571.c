#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 50
typedef enum { head, entry } tagfield;
typedef struct matrix_node *matrix_pointer;
typedef struct entry_node {
	int row;
	int col;
	int value;
};
typedef struct matrix_node {
	matrix_pointer down;
	matrix_pointer right;
	tagfield tag;
	union
	{
		matrix_pointer next;
		struct entry_node entry;
	} u;
};

matrix_pointer hdnode[MAX_SIZE];

matrix_pointer mread(FILE*);
void mwrite(matrix_pointer);
void merase(matrix_pointer*);
matrix_pointer msub(matrix_pointer, matrix_pointer);
matrix_pointer mtranspose(matrix_pointer);
matrix_pointer new_node();

void main() {
	matrix_pointer a, b,d;

	FILE* fp1 = fopen("A.txt", "r");
	FILE* fp2 = fopen("B.txt", "r");
	a = mread(fp1);
	b = mread(fp2);
	mwrite(a);
	mwrite(b);
	d = msub(a, b);
	mwrite(d);
	merase(&d);
	d = mtranspose(a);
	mwrite(d);
	merase(&d);
	merase(&a);
	merase(&b);
	mwrite(a);
	mwrite(b);
	mwrite(d);
	
}

matrix_pointer msub(matrix_pointer a, matrix_pointer b) {
	int num_rows, num_cols,num_heads,i,current_row,num_terms=0;
	matrix_pointer node=NULL,h, temp,last,temp_a=a,temp_b=b;
	int row, col, value;
	if (a->u.entry.col != b->u.entry.col || a->u.entry.row != b->u.entry.row) {
		printf("두 행렬의 row와 col이 일치하지 않음\n");
		return node;
	}
	else {

		node = new_node();//malloc
		node->tag = entry;
		num_rows = a->u.entry.row;
		num_cols = a->u.entry.col;
		num_heads = (num_cols > num_rows) ? num_cols : num_rows;
		h = node;//뒤에 num_terms구한다음 넣을 노드
		node->u.entry.row = num_rows;
		node->u.entry.col = num_cols;
		if (!num_heads)node->right = node;
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
			a = a->right, b = b->right;
			for (i = 0; i < num_rows; i++) {
				temp_a =a->right, temp_b = b->right;
				//a랑 b랑 row는 같은 상태
				while (temp_a != a && temp_b != b) {
					if (temp_a->u.entry.col < temp_b->u.entry.col) {
						//a를 attach해야함
						value = temp_a->u.entry.value;
						col = temp_a->u.entry.col;
						temp_a = temp_a->right;
					}
					else if (temp_a->u.entry.col > temp_b->u.entry.col) {
						//-b를 attach
						value = temp_b->u.entry.value*-1;
						col = temp_b->u.entry.col;
						temp_b = temp_b->right;
					}
					else {//a-b를 attach
						value = temp_a->u.entry.value - temp_b->u.entry.value;
						col = temp_a->u.entry.col;
						temp_a = temp_a->right, temp_b = temp_b->right;
						
					}
					if (value != 0) {//빼서 0나오면 node를 추가하면 안되므로
						row = i;
						num_terms++;
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
				if (temp_a != a)//temp_a가 남아있으면
				{
					while (temp_a != a) {
						value = temp_a->u.entry.value;
						col = temp_a->u.entry.col;
						row = temp_a->u.entry.row;
						temp_a = temp_a->right;
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
				else if (temp_b != b) {//temp_b가 남아있으면
					while (temp_b != b) {
						value = temp_b->u.entry.value*-1;
						col = temp_b->u.entry.col;
						row = temp_b->u.entry.row;
						temp_b = temp_b->right;
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
				a = a->u.next, b = b->u.next;
			}
			last->right = hdnode[current_row];
			for (i = 0; i < num_cols; i++)
				hdnode[i]->u.next->down = hdnode[i];
			for (i = 0; i < num_heads - 1; i++)
				hdnode[i]->u.next = hdnode[i + 1];
			hdnode[num_heads - 1]->u.next = node;
			node->right = hdnode[0];
		}

	}
	h->u.entry.value = num_terms;
	return node;
			

}
matrix_pointer mtranspose(matrix_pointer a) {
	matrix_pointer node,h=a->right,temp,last,temp_a=a;
	int row, col, value;
	int num_rows, num_cols, num_heads,num_terms, i, current_col;
	node = new_node();//malloc
	node->tag = entry;
	num_rows = a->u.entry.row;
	num_cols = a->u.entry.col;
	num_terms = a->u.entry.value;
	num_heads = (num_cols > num_rows) ? num_cols : num_rows;
	node->u.entry.row = num_cols;
	node->u.entry.col = num_rows;
	if (!num_heads)node->right = node;
	else {
		for (i = 0; i < num_heads; i++) {
			temp = new_node();
			hdnode[i] = temp;
			hdnode[i]->tag = head;
			hdnode[i]->down = temp;
			hdnode[i]->u.next = temp;
		}//초기화
		current_col = 0;
		last = hdnode[0];
		a = a->right;
		for (i = 0; i < num_rows; i++) {
			for (temp_a = h->right; temp_a != h; temp_a = temp_a->right) {
				row = temp_a->u.entry.col, col = temp_a->u.entry.row;
				value = temp_a->u.entry.value;
				if (col > current_col) {
					last->down = hdnode[current_col];
					current_col = col;
					last = hdnode[col];
				}
				
				temp = new_node();
				temp->tag = entry;
				temp->u.entry.col = col;
				temp->u.entry.row = row;
				temp->u.entry.value = value;
				last->down = temp;
				last = temp;

				hdnode[row]->u.next->right = temp;
				hdnode[row]->u.next = temp;
			}
			h = h->u.next;
			}
		}
		last->down = hdnode[current_col];
		for (i = 0; i < num_cols; i++)
			hdnode[i]->u.next->right = hdnode[i];
		for (i = 0; i < num_heads - 1; i++)
			hdnode[i]->u.next = hdnode[i + 1];
		hdnode[num_heads - 1]->u.next = node;
		node->right = hdnode[0];
	

	return node;
}


matrix_pointer mread(FILE* fp)
{
	int num_rows, num_cols, num_terms = 0, num_heads, i;
	int row, col, value, current_row = 0;

	matrix_pointer temp, last, node,h;
	fscanf(fp, "%d %d", &num_rows, &num_cols);

	num_heads = (num_cols > num_rows) ? num_cols : num_rows;
	node = new_node();
	h = node;//나중에 num_terms구하고 넣을때 필요
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
	h->u.entry.col = num_cols;
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
	int i,j;
	matrix_pointer temp, head;
	
	if (node == NULL) {
		printf("NODE is NULL\n");
		return; //행렬이 존재하지 않으므로 노드가 NULL이라는 내용을 출력하고 return
	}
	else {
		head = node->right;
		for (i = 0; i < node->u.entry.row; i++) {
			temp = head->right;
			for (j = 0; j < node->u.entry.col; j++) {
				if (temp != head && temp->u.entry.row == i && temp->u.entry.col == j) {
					printf("%4d ",temp->u.entry.value);
					temp = temp->right;
				}
				else
					printf("%4d ",0);
			}
			head = head->u.next;
			printf("\n");
		}
	}
	printf("\n");
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




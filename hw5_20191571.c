#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 101
#define TRUE 1
#define FALSE 0
typedef struct {
	short int vert;
	short int horiz;
} offsets;
offsets move[8];

typedef struct {
	short int row;
	short int col;
	short int dir;
} element;

void path();
void push(element);
element pop();
element stackEmpty();
void stackFull();
element stack[MAX_STACK_SIZE*MAX_STACK_SIZE];
int EXIT_ROW, EXIT_COL, top;
int mark[MAX_STACK_SIZE][MAX_STACK_SIZE];
int maze[MAX_STACK_SIZE][MAX_STACK_SIZE];


int main() {
	int m, p;
	move[0].vert = -1, move[0].horiz = 0;
	move[1].vert = -1, move[1].horiz = 1;
	move[2].vert = 0, move[2].horiz = 1;
	move[3].vert = 1, move[3].horiz = 1;
	move[4].vert = 1, move[4].horiz = 0;
	move[5].vert = 1, move[5].horiz = -1;
	move[6].vert = 0, move[6].horiz = -1;
	move[7].vert = -1, move[7].horiz = -1;
	FILE* fp;
	fp = fopen("maze.txt", "r");
	fscanf(fp, "%d %d", &m, &p);
	EXIT_COL = p;
	EXIT_ROW = m;
	for (int i = 0; i <=m+1; i++) {
		maze[i][0] = 1, maze[i][p + 1] = 1;
	}
	for (int i = 0; i <= p+1; i++) {
		maze[0][i] = 1, maze[m + 1][i] = 1;
	}
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= p; j++) {
			fscanf(fp, "%d", &maze[i][j]);
			mark[i][j] = 0;
		}
	}
	

	path();

	fclose(fp);
	return 0;
}
void path(void)
{
	int i, row, col, nextRow, nextCol, dir, found = FALSE;
	element position;
	mark[1][1] = 1; top = 0;
	stack[0].row = 1; stack[0].col = 1; stack[0].dir = 1;
	while (top > -1 && !found) {
		position = pop();
		row = position.row;
		col = position.col, dir = position.dir;
		while (dir < 8 && !found) {
			/* move in direction dir */
			nextRow = row + move[dir].vert;
			nextCol = col + move[dir].horiz;
			if (nextRow == EXIT_ROW && nextCol == EXIT_COL)
				found = TRUE;
			else if (!maze[nextRow][nextCol] && !mark[nextRow][nextCol] ) {
				mark[nextRow][nextCol] = 1;
				position.row = row; position.col = col;
				position.dir = ++dir;
				push(position);
				row = nextRow; col = nextCol; dir = 0;
			}
			else ++dir;
		}

	}
	if (found) {

		for (i = 0; i <= top; i++)
			printf("% 2d % 5d\n", stack[i].row, stack[i].col);
		printf("% 2d % 5d\n", row, col);
		printf("% 2d % 5d\n", EXIT_ROW, EXIT_COL);
	}
	else
		printf("-1\n");
}

void push(element item)
{
	/* add an item to the global stack */
	if (top >= MAX_STACK_SIZE - 1)
		stackFull();
	stack[++top] = item;
}
element pop()
{
	/* return the top element from the stack */
	if (top <= -1)
		return stackEmpty(); /* return an error key */
	return stack[top--];
}

element stackEmpty() {
	fprintf(stderr, "stack is empty. cannot pop element");
	return stack[top];
}

void stackFull() {
	fprintf(stderr, "Stack is full, cannot add element");
	exit(EXIT_FAILURE);
}

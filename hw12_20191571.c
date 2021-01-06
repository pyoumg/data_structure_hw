#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTICES 30
#define MIN2(x,y) ((x) < (y) ? (x) : (y)) 

typedef struct node *node_pointer;
typedef struct node {
	int vertex;
	node_pointer link;
};

node_pointer graph[MAX_VERTICES];
typedef struct stack *stack_pointer;
typedef struct  stack{
	int key1;
	int key2;//vertex�̴�.
	stack_pointer link;
};
stack_pointer top;

short int dfn[MAX_VERTICES]; 
short int low[MAX_VERTICES]; 
int num,n=0; 
void init(); 
void bicon(int, int);
void push(int u, int w);
void pop(int* u, int* w);//�����͸� �Ἥ ���� ����


void main() {  
	int temp = 0,j=0;
	char inputread[500];//�Է� ������ ���� �迭
	node_pointer pNew,pPre;//��������Ʈ�� ������ �ʿ�

	FILE* fp = fopen("input.txt", "r");
	
	fscanf(fp, "%d ", &n);//���� ���� �б�,n�� global variable
	for (int i = 0; i < n; i++) {
		j = 0;//�ʱ�ȭ
		fgets(inputread, sizeof(char)*500, fp);
		temp = atoi(inputread);
		graph[temp] = malloc(sizeof(struct node));//�����Ҵ�
		graph[temp]->vertex = temp;
		if (temp < 10)
			j++;//���ڸ���
		else
			j += 2;//max�� 30�̶� 100�� �Ѿ ���� ����
		pPre = graph[temp];
		
		for (j; j < strlen(inputread); j++) {
			if (inputread[j]>='0'&&inputread[j]<='9') {//�ش� �ε����� �����Ͱ� ����
				if (j == 0) {//�����Ҷ� �б�
					temp = atoi(inputread + j);
					pNew = malloc(sizeof(struct node));
					pNew->vertex = temp;
					pPre->link = pNew;
					pPre = pNew;
					pPre->link = NULL;
				}
				else if (inputread[j - 1] == ' ')
				{
					temp = atoi(inputread + j);
					pNew = malloc(sizeof(struct node));
					pNew->vertex = temp;
					pPre->link = pNew;
					pPre = pNew;
					pPre->link = NULL;
				}
			}
		}
	}
	// ���� �����Ͽ� ������ �о� adjacency list�� �����Ѵ�. 
	init();  //���� �ʱ�ȭ
	bicon(3, -1);
	fclose(fp);
}
void init() {
	int i;
	for (i = 0; i < n; i++) {
		dfn[i] = low[i] = -1;
	}
	num = 0;
}
void bicon(int u, int v) {
	node_pointer ptr;
	int w, x, y;
	dfn[u] = low[u] = num++;
	for (ptr = graph[u]; ptr; ptr = ptr->link) {
		w = ptr->vertex;
		if (v != w && dfn[w] < dfn[u]) {
			push(u, w);
			if (dfn[w] < 0) {
				bicon(w, u);
				low[u] = MIN2(low[u], low[w]);
				if (low[w] >= dfn[u]){
					printf("New biconnected component: ");
					do {
						pop(&x, &y);
						printf(" <%d, %d>", x, y);
					} while (!((x == u) && (y == w)));
					printf("\n");
				}
					
			}
			else if (w != v)low[u] = MIN2(low[u], dfn[w]);

		}
	}



}
void push(int u, int w) {
	stack_pointer stack_new = malloc(sizeof(struct stack));
	stack_new->key1 = u;
	stack_new->key2 = w;
	stack_new->link = top;
	top = stack_new;
}
void pop(int* u, int* w) {//top�� pop
	stack_pointer temp = top;
	*u = top->key1;
	*w = top->key2;
	top = top->link;
	free(temp);
}
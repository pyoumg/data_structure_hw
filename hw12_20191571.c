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
	int key2;//vertex이다.
	stack_pointer link;
};
stack_pointer top;

short int dfn[MAX_VERTICES]; 
short int low[MAX_VERTICES]; 
int num,n=0; 
void init(); 
void bicon(int, int);
void push(int u, int w);
void pop(int* u, int* w);//포인터를 써서 값을 변경


void main() {  
	int temp = 0,j=0;
	char inputread[500];//입력 읽을때 사용될 배열
	node_pointer pNew,pPre;//인접리스트에 넣을때 필요

	FILE* fp = fopen("input.txt", "r");
	
	fscanf(fp, "%d ", &n);//정점 개수 읽기,n은 global variable
	for (int i = 0; i < n; i++) {
		j = 0;//초기화
		fgets(inputread, sizeof(char)*500, fp);
		temp = atoi(inputread);
		graph[temp] = malloc(sizeof(struct node));//동적할당
		graph[temp]->vertex = temp;
		if (temp < 10)
			j++;//한자리수
		else
			j += 2;//max가 30이라 100을 넘어갈 일은 없다
		pPre = graph[temp];
		
		for (j; j < strlen(inputread); j++) {
			if (inputread[j]>='0'&&inputread[j]<='9') {//해당 인덱스의 데이터가 숫자
				if (j == 0) {//시작할때 읽기
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
	// 파일 오픈하여 파일을 읽어 adjacency list에 저장한다. 
	init();  //값들 초기화
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
void pop(int* u, int* w) {//top을 pop
	stack_pointer temp = top;
	*u = top->key1;
	*w = top->key2;
	top = top->link;
	free(temp);
}
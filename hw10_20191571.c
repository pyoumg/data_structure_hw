#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 100 
typedef struct treeNode* treePtr;
typedef struct treeNode
{
	treePtr lchild;
	int data;
	treePtr rchild;
};
void inorder(treePtr);
void preorder(treePtr);
void insert(treePtr*, int);
treePtr modifiedSearch(treePtr, int);
void main() {
	int i, n, A[MAX_TERMS];
	treePtr tree = NULL;
	// 파일 오픈한다.       
	FILE *fp = fopen("input.txt", "r");
	fscanf(fp, "%d ", &n);
	for (i = 0; i < n; i++)
	{
		fscanf(fp, "%d ", &A[i]);
	}
	//파일을 읽어 정수의 개수는 n에, 삽입하여야할 정수들은 A에 저장한다.  
	// 순서대로 binary search tree에 삽입한다     
	for (i = 0; i < n; i++)
		insert(&tree, A[i]);
	inorder(tree);
	preorder(tree);
	fclose(fp);
	// 구성된 binary search tree를 inorder와 preorder로 출력하여 올바르게 트리 가 생성되었는지 확인한다. 
}	
void inorder(treePtr ptr) {
	if (ptr) {
		inorder(ptr->lchild);
		printf("%d\n", ptr->data);
		inorder(ptr->rchild);
	}

}
void preorder(treePtr ptr) {
	if (ptr) {
		printf("%d\n", ptr->data);
		preorder(ptr->lchild);
		preorder(ptr->rchild);
	}
}
void insert(treePtr* ptr, int n) {
	treePtr ans,temp;
	temp=modifiedSearch(*ptr, n);

	if (temp || !(*ptr)) {

		ans = malloc(sizeof(struct treeNode));
		ans->data = n;
		ans->lchild = ans->rchild = NULL;
		if (*ptr) {
			if (n < temp->data)
				temp->lchild = ans;
			else
				temp->rchild = ans;
		}
		else
			*ptr = ans;
	}

}
treePtr modifiedSearch(treePtr ptr, int k) {
	if (ptr == NULL) {
		return NULL;
	}
	while (ptr) {
		if (k == ptr->data) { 
			printf("같은 키를 갖는 노드가 있음\n");
			return NULL; }
		if (k < ptr->data)
		{
			if (ptr->lchild == NULL)return ptr;
			ptr = ptr->lchild;
		}
		else {
			if (ptr->rchild == NULL)return ptr;
			ptr = ptr->rchild;
		}
	}
	

}
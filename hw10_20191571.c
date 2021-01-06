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
	// ���� �����Ѵ�.       
	FILE *fp = fopen("input.txt", "r");
	fscanf(fp, "%d ", &n);
	for (i = 0; i < n; i++)
	{
		fscanf(fp, "%d ", &A[i]);
	}
	//������ �о� ������ ������ n��, �����Ͽ����� �������� A�� �����Ѵ�.  
	// ������� binary search tree�� �����Ѵ�     
	for (i = 0; i < n; i++)
		insert(&tree, A[i]);
	inorder(tree);
	preorder(tree);
	fclose(fp);
	// ������ binary search tree�� inorder�� preorder�� ����Ͽ� �ùٸ��� Ʈ�� �� �����Ǿ����� Ȯ���Ѵ�. 
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
			printf("���� Ű�� ���� ��尡 ����\n");
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
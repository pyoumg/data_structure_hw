#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 100 
int n1;//subtree개수를 구하기위해 필요한 변수를 추가로 선언
typedef struct treeNode* treePtr;
typedef struct treeNode
{
	treePtr lchild;
	int key;
	treePtr rchild;
};
//treePtr onechildDelete(treePtr ptr,int n);//추가로 구현한 함수
treePtr modifiedSearch2(treePtr ptr, int k,treePtr* target);//추가로 구현한 함수

void inorder(treePtr);
void preorder(treePtr);
void insert(treePtr*, int);
treePtr modifiedSearch(treePtr, int);
void delete(treePtr*, int);
void rangeSearch(treePtr, int, int);
void bigsubtree(treePtr ptr);//추가로 구현한 함수
void main() {
	int i,j, n,m, A[MAX_TERMS],D[MAX_TERMS],k1,k2;
	treePtr tree = NULL;
	// 파일 오픈한다.       
	FILE *fp = fopen("input2.txt", "r");
	fscanf(fp, "%d ", &n);
	for (i = 0; i < n; i++)
	{
		fscanf(fp, "%d ", &A[i]);
	}
	fscanf(fp, "%d ", &m);
	for ( i = 0; i < m; i++) {
		fscanf(fp, "%d ", &D[i]);
	}
	fscanf(fp, "%d %d", &k1, &k2);
	   
	for (i = 0; i < n; i++)
		insert(&tree, A[i]);
	inorder(tree);
	printf("\n");
	preorder(tree);
	printf("\n");
	for (j = 0; j < m; j++) {
		delete(&tree, D[j]);
		inorder(tree);
		printf("\n");
		preorder(tree);
		printf("\n");
	}
	rangeSearch(tree, k1, k2);
	fclose(fp);
	// 구성된 binary search tree를 inorder와 preorder로 출력하여 올바르게 트리 가 생성되었는지 확인한다. 
}
void inorder(treePtr ptr) {
	if (ptr) {
		inorder(ptr->lchild);
		printf("%d ", ptr->key);
		inorder(ptr->rchild);
	}

}
void preorder(treePtr ptr) {
	if (ptr) {
		printf("%d ", ptr->key);
		preorder(ptr->lchild);
		preorder(ptr->rchild);
	}
}
void insert(treePtr* ptr, int n) {
	treePtr ans, temp;
	temp = modifiedSearch(*ptr, n);

	if (temp || !(*ptr)) {

		ans = malloc(sizeof(struct treeNode));
		ans->key = n;
		ans->lchild = ans->rchild = NULL;
		if (*ptr) {
			if (n < temp->key)
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
		if (k == ptr->key) {
			printf("같은 키를 갖는 노드가 있음\n");
			return NULL;
		}
		if (k < ptr->key)
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

void delete(treePtr* ptr, int n) {
	treePtr ans, temp,target;
	int a = 0, b = 0,c=-1;
	temp = modifiedSearch2(*ptr, n,&target);
	//target:삭제해아하는 노드,temp:target의 부모노드
	if (*ptr == NULL) {
		printf("NODE is NULL\n");
		return;
	}
	if (temp == NULL) {
			printf("삭제하려는 값이 노드에 존재하지 않음\n");//적절한 메시지 출력
			return;
	}
		if (target->lchild == NULL && target->rchild == NULL) {
			//자식 노드가 없을떄
			if (target == temp->lchild) {
				temp->lchild = NULL;
			}
			else {
				temp->rchild = NULL;
			}
		}
		else if (target->lchild == NULL){
			//자식 노드가 1개일때(rchild)
			if (target == temp->lchild) {
				temp->lchild = target->rchild;
			}
			else {
				temp->rchild = target->rchild;
			}
			free(target);//동적할당 해제

		}
		else if (target->rchild == NULL) {
			//자식 노드가 1개일때
			if (target == temp->lchild) {
				temp->lchild = target->lchild;
			}
			else {
				temp->rchild = target->lchild;
			}
			free(target);//동적할당 해제
		}
		else {//자식 노드가 2개일 때
			n1 = 1;
			bigsubtree(target->lchild);
			a = n1;
			n1 = 1;//초기화
			bigsubtree(target->rchild);
			b = n1;
			if (a == b)
			{
				c = rand() % 2;
			}
			if (a > b||c==1) {
				ans = target->lchild;
				temp = target;//여기서 temp는 ans의 부모노드로 쓰임
				while (ans->rchild) {
					temp = ans;
					ans = ans->rchild;//왼쪽 subtree에서 가장 큰 원소
					
				}
				target->key = ans->key;
				temp->rchild = NULL;

			}
			else {
				ans = target->rchild;
				temp = target;//여기서 temp는 ans의 부모노드로 쓰임
				while (ans->lchild) {
					temp = ans;
					ans = ans->lchild;//왼쪽 subtree에서 가장 큰 원소
				}
				target->key = ans->key;
				temp->lchild = NULL;
			}
		}
		
}

void bigsubtree(treePtr ptr) {
	if (ptr == NULL)return;
	if (ptr->lchild) {
		n1++;//global variable
		bigsubtree(ptr->lchild);

	}
	if (ptr->rchild) {
		n1++;
		bigsubtree(ptr->rchild);
	}
}



treePtr modifiedSearch2(treePtr ptr,int k,treePtr* target) {//delete를 위한 search 함수, 지워야하는 해당 노드를 return
	if (ptr == NULL) {
		return NULL;//노드가 비어있음
	}
	treePtr ans=ptr;
	while (ptr) {
		if(k==ptr->key){
			*target = ptr;
			return ans;
			
		}
		if (k < ptr->key)
		{
			ans = ptr;
			ptr = ptr->lchild;
		}
		else {
			ptr = ptr->rchild;
		}
	}
	return NULL;
}
void rangeSearch(treePtr ptr, int k1, int k2) {
	if (ptr) {
		rangeSearch(ptr->lchild,k1,k2);
		if(ptr->key>=k1&&ptr->key<=k2)
			printf("%d ", ptr->key);
		rangeSearch(ptr->rchild,k1,k2);
	}
}
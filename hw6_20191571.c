#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#define MAX_EXPR_SIZE 100 
typedef enum {lparen, rparen, plus, minus, times, divide, mod, eos, operand}
precedence; 

int top = 0;  
char expr[MAX_EXPR_SIZE]; 
int isp[] = {0, 19, 12, 12, 13, 13, 13, 0};  // 교과서 3.6절 pp. 136 참고
int icp[] = {20, 19, 12, 12, 13, 13, 13, 0};  
// 필요한 함수 선언 

typedef struct __NODE{
	precedence data;
	struct __NODE* link;
	
}NODE;
NODE* stack[MAX_EXPR_SIZE];


void printToken(int item);
void push(precedence);
precedence pop();
void postfix( ); 
precedence getToken(char*, int*);
void rExpr(FILE*, char*); //다시 출력해보기

void main() {       // 파일을 오픈하고 수식을 읽어 배열 expr에 저장.   
	FILE* fp;
	fp=fopen("expr.txt", "r");
	rExpr(fp,expr);   
	postfix( );
	fclose(fp);
}        
void postfix(void) {
	/*  output the postfix of the expression.
	The expression string, stack, and the top are global  */
	char symbol;
	int n = 0;
	precedence token;
	stack[0] = malloc(sizeof(NODE));
	stack[0]->data = eos;
	for (int i = 0; i < strlen(expr); i++) {
		token = getToken(&symbol, &n);
		if (token == operand)
			printf("%c", symbol);
		else  if (token == rparen) {

			while (stack[top]->data != lparen)
				printToken(pop());
			pop();  /* discard the left paranthesis  */
		}
		else {
			/*  remove and print symbols whose isp is greater
			than or equal to the current token’s icp  */
			while (isp[stack[top]->data] >= icp[token])
				printToken(pop(top));
			push(token);
		}
	}

	while ((token = pop()) != eos)
		printToken(token);

}
precedence getToken(char *symbol, int *n)
{ /*  get the next token, symbol is the character representation,
  which is returned, the token is represented by its enumerated value,
  which is returned in the function name  */
	*symbol = expr[(*n)++];
	switch (*symbol) {
	case '(':
		return  lparen;
	case ')':
		return  rparen;
	case '+':
		return  plus;
	case '-':
		return  minus;
	case '/':
		return  divide;
	case '*':
		return  times;
	case '%':
		return mod;
	case ' ':
		return eos;

	default: return  operand;  /* no error checking, default is operand */
	}
}


void rExpr(FILE* fp, char *expr) {
	int i = 0;
	while (fscanf(fp," %c",&expr[i])!=EOF)
	{
		i++;
	}
}

void push(precedence item) {
	NODE *temp;
	temp = malloc(sizeof(NODE));
	temp->data = item;
	temp->link = stack[top];
	stack[++top] = temp;
	


}
precedence pop() {
	NODE * temp = stack[top];
	precedence item;
	if (!temp) {
		printf("stack is EMPTY\n");
		return -1;
	}
	item = temp->data;
	stack[top--] = temp->link;
	free(temp);
	return item;
}

void printToken(int item) {
	switch (item) {
	case plus:
		printf("+");
		break;
	case minus:
		printf("-");
		break;
	case divide:
		printf("/");
		break;
	case times:
		printf("*");
		break;
	case mod:
		printf("%");
		break;
	case eos:
		printf(" ");
		break;

		/* no error checking, default is operand */
	}
}
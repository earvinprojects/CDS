/**
 * prog6.5.c
 * 這個程式寫的太不直覺了，不好理解，我看沒多久就會忘了
 * 20170405 : 思考把它改寫好一點
 */
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h> /* 記錄bool列舉值 */

#define MaxStackSize 100
#define MaxExprSize 100

typedef enum {
	LPAREN,		// 0
	RPAREN,		// 1
	PLUS,		// 2
	MINUS,		// 3
	TIMES,		// 4
	DIVIDE,		// 5
	EOE,		// 6
	OPERAND		// 7 
} TokenType;

TokenType stack[MaxStackSize];	// 工作用堆疊
char expr[MaxExprSize];			// 存放使用者輸入的運算式

// 優先權：   (,  ),  +,  -,  *,  /, EOE
int isp[] = { 0, 19, 12, 12, 13, 13, 0  };	// 在堆疊內優先權(in stack precedence)
int icp[] = {20, 19, 12, 12, 13, 13, 0  };	// 在堆疊外優先權(incoming precedence)

TokenType GetOneToken(char *symbol, int *c) {
	*symbol = expr[*c];	// 從輸入的字串中取出位置c的那個字元
	(*c)++;				// 指標移往下一個位置
	switch (*symbol) {
	case '(': return LPAREN;
	case ')': return RPAREN;
	case '+': return PLUS;
	case '-': return MINUS;
	case '*': return TIMES;
	case '/': return DIVIDE;
	case '@': return EOE;
	default : return OPERAND;
	}
}

void PrintTokenOperator(TokenType token_operator) {
	switch (token_operator) {
	case PLUS   : printf("+"); break;
	case MINUS  : printf("-"); break;
	case TIMES  : printf("*"); break;
	case DIVIDE : printf("/"); break;
	default     : break;
	}
}

void push(int *top, TokenType token_operator) {
	if ((*top) >= (MaxStackSize - 1)) {
		printf("Stack is full!");
		exit(1);
	}
	stack[++(*top)] = token_operator;
}

TokenType pop(int *top) {
	if ((*top) == -1) {
		printf("Stack is empty!");
		exit(1);
	}
	return stack[(*top)--];
}

void TransToPostfix(void) {
	char symbol;
	TokenType token;
	int top = 0;
	int c = 0;
	stack[0] = EOE;

	token = GetOneToken(&symbol, &c);	// 參數傳址是為了與外部程式碼溝通~~
	while (token != EOE) {
		if (token == OPERAND) {	// 遇到運算元
			printf("%c", symbol);
		} else {
			if (token == RPAREN) {
				while (stack[top] != LPAREN) {
					PrintTokenOperator(pop(&top));
				}
				pop(&top);	//僅pop出來<為 '(' 符號>，但不印出
			} else {			// 遇到非 ')' 的任何運算子
				while (isp[stack[top]] >= icp[token]) {
					PrintTokenOperator(pop(&top));
				}
				push(&top, token);
			}
		}
		token = GetOneToken(&symbol, &c);
	}

	while ((token = pop(&top)) != EOE) {
		PrintTokenOperator(token);
	}
}

int main(void) {
	printf("請輸入中序表示法，結尾字元為@：");
	scanf("%s", expr);

	printf("後序表示法為：");
	TransToPostfix();
	printf("\n");

	system("pause");	// 在畫面上顯示「請按任意鍵繼續 . . .」
	return 0;
}


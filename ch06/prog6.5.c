/**
 * prog6.5.c
 * �o�ӵ{���g���Ӥ���ı�F�A���n�z�ѡA�ڬݨS�h�[�N�|�ѤF
 * 20170405 : ��ҧ⥦��g�n�@�I
 */
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h> /* �O��bool�C�|�� */

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

TokenType stack[MaxStackSize];	// �u�@�ΰ��|
char expr[MaxExprSize];			// �s��ϥΪ̿�J���B�⦡

// �u���v�G   (,  ),  +,  -,  *,  /, EOE
int isp[] = { 0, 19, 12, 12, 13, 13, 0  };	// �b���|���u���v(in stack precedence)
int icp[] = {20, 19, 12, 12, 13, 13, 0  };	// �b���|�~�u���v(incoming precedence)

TokenType GetOneToken(char *symbol, int *c) {
	*symbol = expr[*c];	// �q��J���r�ꤤ���X��mc�����Ӧr��
	(*c)++;				// ���в����U�@�Ӧ�m
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

	token = GetOneToken(&symbol, &c);	// �Ѽƶǧ}�O���F�P�~���{���X���q~~
	while (token != EOE) {
		if (token == OPERAND) {	// �J��B�⤸
			printf("%c", symbol);
		} else {
			if (token == RPAREN) {
				while (stack[top] != LPAREN) {
					PrintTokenOperator(pop(&top));
				}
				pop(&top);	//��pop�X��<�� '(' �Ÿ�>�A�����L�X
			} else {			// �J��D ')' ������B��l
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
	printf("�п�J���Ǫ�ܪk�A�����r����@�G");
	scanf("%s", expr);

	printf("��Ǫ�ܪk���G");
	TransToPostfix();
	printf("\n");

	system("pause");	// �b�e���W��ܡu�Ы����N���~�� . . .�v
	return 0;
}


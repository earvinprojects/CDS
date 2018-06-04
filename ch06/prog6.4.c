/**
 * prog6.4.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h> /* 記錄bool列舉值 */

typedef struct {
    int ItemKey;
} element;

struct Stack_Node {
    element Item;
    struct Stack_Node *link;
};
typedef struct Stack_Node S_Node;   // S_Node是Stack_Node的別名
typedef S_Node *S_Node_P;           // S_Node_P是Stack_Node的指標別名 

int push(S_Node_P *top, element Item) {
    S_Node_P temp = (S_Node_P) malloc(sizeof(S_Node));
    if (temp == NULL) {
        printf("Out of memory!");
        return false;
    }
    temp->Item = Item;
    temp->link = *top;
    *top = temp;
    return true;
}

// *Item : 由於回傳值已被代表pop成功與否的值所使用
// 因此要與呼叫方溝通元素值，只能利用傳指標呼叫
int pop(S_Node_P *top, element *Item) {
    S_Node_P temp = *top;
    
    if (temp == NULL) {
        printf("Stack is Empty!");
        return false;
    }
    *Item = temp->Item;
    *top = temp->link;
    free(temp);
    return true;
}

void PrintStack(S_Node_P top) {
    S_Node_P visitP;
    visitP = top;
    printf("In Stack's top!");
    while (visitP != NULL) {
        printf("%d|", visitP->Item.ItemKey);
        visitP = visitP->link;
    }
    printf("In Stack's bottom\n");
}

int main(void) {
    element Item;
    char ch = 'I';
    S_Node_P top = NULL;

    while ((ch != 'E') || (ch != 'e')) {
        fflush(stdin);
        printf("[I]=push,[O]=pop,[P]=print,[E] and [Others]=Exit:");
        scanf("%c", &ch);
        switch(ch) {
            case 'I':
            case 'i':
                printf("push :");
                scanf("%d", &Item.ItemKey);
                if (push(&top,Item) == true) {
                    printf("push sucessful...\n");
                } else {
                    printf("push unsucessful...\n");
                }
                break;
            case 'O':
            case 'o':
                if (pop(&top, &Item) == true) {
                    printf("pop %d sucessful...\n", Item.ItemKey);
                } else {
                    printf("pop sucessful...\n");
                }
                break;              
            case 'P':
            case 'p':
                PrintStack(top);  
                break;              
            default:
                ch = 'E';
                printf("Byebye!!\n");
                break;            
        }
    }
    system("pause");
	return 0;
}


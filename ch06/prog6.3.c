/**
 * prog6.3.c : 環狀佇列
 */
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h> /* 記錄bool列舉值 */

#define MaxCQueueSize 5

typedef struct {
    int ItemKey;
} element;

typedef struct {
    element cqueue[MaxCQueueSize];
    int front;
    int rear;
} CQueueADT;

bool isEmpty(CQueueADT CQ) {
    if (CQ.front == CQ.rear) return true;
    else return false;
}

bool isFull(CQueueADT CQ) {
    if (CQ.front == CQ.rear) return true;
//    if (CQ.front == ((CQ.rear + 1) % MaxCQueueSize)) return true;
    else return false;
}

void addCQ(CQueueADT *CQ, element item) {
    CQ->rear = (CQ->rear + 1) % MaxCQueueSize;
    if (isFull(*CQ) == true) {
        printf("Circle Queue is full!");
        exit(1);
    } else {
        CQ->cqueue[CQ->rear] = item;
    }
}

element deleteCQ(CQueueADT *CQ) {
    if (isEmpty(*CQ) == true) {
        printf("Circle Queue is empty!!");
        exit(1);
    } else {
        CQ->front = (CQ->front + 1) % MaxCQueueSize;
        return CQ->cqueue[CQ->front];
    }
}

void PrintCQueue(CQueueADT *CQ) {
    int i;
    printf("front value is=%d, rear value is=%d, Circle Queue contents :\n", CQ->front, CQ->rear);
    
    if (isEmpty(*CQ) == true) {
        printf("Circle Queue is empty!\n");
        return;
    }
    
    for (i = 0; i <= 5; i++) {
    	printf("  CQ[%d]  ", i);
    }
    printf(".....\n");
    
    for (i = 0; i <= 5; i++) {
    	if (i == CQ->front) {
    		printf("|   N==\t");
    	} else {
    		printf("|%4d\t", CQ->cqueue[i]);
    	}
    }
    printf("|\n");   
}

int main(void) {
    element Item;
    int i;
    CQueueADT CQ1;
    char ch = 'I';
    // 使用佇例前必須先將front與rear都設為0
	CQ1.front = 0;
	CQ1.rear = 0;

    for (i = 0; i < MaxCQueueSize; i++) {
        CQ1.cqueue[i].ItemKey = 0;
    }
    while ((ch != 'E') || (ch != 'e')) {
        fflush(stdin);
        printf("[A]=addCQ,[D]=deleteCQ,[E] and [Others]=Exit:");
        scanf("%c", &ch);
        switch(ch) {
            case 'A':
            case 'a':
                printf("addCQ :");
                scanf("%d", &Item.ItemKey);
                addCQ(&CQ1, Item);
                printf("addQ人%d,", Item.ItemKey);
                PrintCQueue(&CQ1);
                break;
            case 'D':
            case 'd':
            	// 回傳值是一個element結構型態的變數，可透過.取出項目
                printf("deleteCQ出%d,", deleteCQ(&CQ1).ItemKey);
                PrintCQueue(&CQ1);  
                break;              
            default:
                ch = 'E';
                PrintCQueue(&CQ1);
                printf("Byebye!!\n");
                break;            
        }
    }
    system("pause");
	return 0;
}


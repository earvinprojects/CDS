/**
 * prog6.2.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h> /* 記錄bool列舉值 */

#define MaxQueueSize 100

typedef struct {
    int ItemKey;
} element;

typedef struct {
    element queue[MaxQueueSize];
    int front;
    int rear;
} QueueADT;

bool isEmpty(QueueADT Q) {
    if (Q.front >= Q.rear) return true;
    else return false;
}

bool isFull(QueueADT Q) {
    if (Q.rear >= MaxQueueSize - 1) return true;
    else return false;
}

void addQ(QueueADT *Q, element item) {
    if (isFull(*Q) == true) {
        printf("Queue is full!");
        exit(1);
    } else {
        Q->queue[++Q->rear] = item;
    }
}

element deleteQ(QueueADT *Q) {
    if (isEmpty(*Q) == true) {
        printf("Queue is empty!!");
        exit(1);
    } else {
        return Q->queue[++Q->front];
        // Q->front++;
        // return Q->queue[front];
    }
}

void PrintQueue(QueueADT *Q) {
    int i;
    printf("front value is=%d, rear value is=%d, Queue contents :\n", Q->front, Q->rear);
    
    if (Q->front >= Q->rear) {
        printf("Queue is empty!\n");
        return;
    }
    
    for (i = 0; i <= 5; i++) {
    	printf("  Q[%d]  ", i);
    }
    printf(".....\n");
    
    for (i = 0; i <= 5; i++) {
    	if (i <= Q->front || i > Q->rear) {
    		printf("|  ==\t");
    	} else {
    		printf("|  %2d\t", Q->queue[i]);
    	}
    }
    printf("|.....\n");   
}

int main(void) {
    element Item;
    int i;
    QueueADT Q1;
    char ch = 'I';
	Q1.front = -1;
	Q1.rear = -1;

    while ((ch != 'E') || (ch != 'e')) {
        fflush(stdin);
        printf("[A]=addQ,[D]=deleteQ,[E] and [Others]=Exit:");
        scanf("%c", &ch);
        switch(ch) {
            case 'A':
            case 'a':
                printf("addQ :");
                scanf("%d", &Item.ItemKey);
                addQ(&Q1, Item);
                printf("addQ人%d,", Item.ItemKey);
                PrintQueue(&Q1);
                break;
            case 'D':
            case 'd':
            	// 回傳值是一個element結構型態的變數，可透過.取出項目
                printf("deleteQ出%d,", deleteQ(&Q1).ItemKey);
                PrintQueue(&Q1);  
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


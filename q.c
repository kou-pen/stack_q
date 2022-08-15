#include <stdio.h>/*おまじない*/
#include <stdlib.h>/*ゴリ押し強制終了用*/
#include <signal.h>/*安心と安全のシグナルハンドラ*/
#include <stdlib.h>/*ターミナルの処理用*/

#define MAX_SIZE (10 + 1)

typedef struct queue{
    int tail;
    int head;
    int data[MAX_SIZE];
}queue_t;

void init_queue(queue_t*);
void enqueue(queue_t*,int);
int dequeue(queue_t*);
void show_all(queue_t*);

void exit(int status);/*強制終了用*/

/*Ctrl+C 処理*/
void signal_handler(int signum){
    printf("プログラムを終了します");
}

void init_queue(queue_t *queue){
    queue->head = 0; /*リングバッファなるものを見つけたので実装*/
    queue->tail = -1;
}

void enqueue(queue_t *queue,int input){
    if ((queue->tail + 2) % MAX_SIZE == queue->head){ /*headの１つ前にはデータを追加しないほうがいいらしい*/
        /* code */
        system("cls");
        printf("キューがいっぱいのため、%dをenqueueできませんでした\n",input);
        return;
    }
    system("cls");
    queue->data[(queue->tail + 1) % MAX_SIZE] = input;
    queue->tail = (queue->tail + 1) % MAX_SIZE;
    printf("%dをenqueueしました\n",input);
}

int dequeue(queue_t *queue){
    int returns = 0;

    if ((queue->tail + 1) % MAX_SIZE == queue->head){
        system("cls");
        printf("キューが空っぽです！\n");
        printf("プログラムを終了します\n");
        exit(0);/*GORIOSHI*/
    }
    returns = queue->data[queue->head];
    queue->head =(queue->head + 1) % MAX_SIZE;
    return returns;
}

void show_all(queue_t *queue){/*すべてdequeueしたあとにやるとバグる...?*/
    int i = 0;
    int num;

    if (queue ->tail < queue->head){
        num = queue->tail + MAX_SIZE - queue->head + 1;
    }
    else{
        num = queue->tail - queue->head + 1;
    }
    system("cls");
    printf("入力順に表示されています 要素数:%d\n",num);
    printf("=======================\n");
    for ( i = 0; i < num; i++){
        /* code */
        printf("%d\n", queue->data[(queue->head + i) % MAX_SIZE]);
    } 
    printf("=======================\n");
}

int main(void){
    int menu;
    int input;
    int output;
    queue_t queue;

    init_queue(&queue);
    system("cls");
    while(1){
        printf("enqueue:1,dequeue:2,show_all:3,プログラムを終了:その他のキーかctrl+c\n");
        printf(">>>");
        scanf("%d",&menu);
        switch (menu){
            case 1: /*enqueue:1*/
                system("cls");
                printf("整数を入力してください\n");
                printf(">>>");
                scanf("%d", &input);
                if (input < 0) {
                    system("cls");
                    printf("%d は整数ではありません\n",input);
                    continue;
                }
                enqueue(&queue,input);
                break;

            case 2: /*dequeue:2*/
                system("cls");
                output = dequeue(&queue);
                if(output != -1){
                    printf("%d\n",output);
                }
                break;

            case 3: /*show_all:3*/
                system("cls");
                show_all(&queue);
                break;

            default:
                system("cls");
                printf("プログラムを終了します\n");
                exit(0); /*GORIOSHI*/
            }
    }
    return 0;
}

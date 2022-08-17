#include <stdio.h>
#include <stdlib.h>/*ターミナルの処理用*/
#include <signal.h>/*シグナルハンドラ用*/
#include <ctype.h>/*なんだっけ*/
/*
<<<<<<<<未来の俺へ:コンパイルは--exec-charset=cp932をつけろ>>>>>>>>
*/

#define data_size 100 /*最大の個数*/

typedef struct STACK{
    /* data */
    int final;
    int data[data_size];
}STACK_T;

void init_stack(STACK_T*);
void print_stack(STACK_T*);
void push_to_stack(STACK_T*,int);
int pop_from_stack(STACK_T*);
int peek_from_stack(STACK_T*);

/*ctrl+c 処理*/
void signal_handler(int signum){
    printf("プログラムを終了します.");
    system("cls");
}

/*スタック初期化*/
void init_stack(STACK_T *stack){
    stack->final = -1;
}

/*push関数*/
void push_to_stack(STACK_T *stack,int input){
    if (stack->final >= data_size -1){
        /* code */
        printf("スタックがいっぱいです！");
        return;
    }
    stack->data[stack->final +1] = input;
    stack->final = stack->final +1;
}

/*pop用関数*/
int pop_from_stack(STACK_T *stack){
    int get_data =0;
    if(stack->final == -1){
        printf("スタックがすっからかんです！\n");
        return -1;
    }
    get_data = stack->data[stack->final];
    stack->final = stack->final -1;
    return get_data;
}

/*全部表示する関数。主に動作チェック用*/
void print_stack(STACK_T *stack){
    int i =0;
    printf("すべてのデータ:\n");
    for ( i = 0; i <= stack->final; i++){   
        printf("%d\n",stack->data[stack->final -i]);
    }
}

/*peek関数*/
int peek_from_stack(STACK_T *stack){
    if(stack->final == -1){
        printf("スタックがすっからかんです！\n");
        return -1;
    }
    printf("%dが最新です\n",stack->data[stack->final]);
    return 0;
}

int main(void){
    int ans;
    int input;
    int output;
    STACK_T stack;
    signal(SIGINT, signal_handler);/*シグナルハンドラ登録*/

    init_stack(&stack);
    system("cls");

    while(1){
        /* code */
        printf("push:1,pop all:2,pop:3,peek:4,終了:ctrl+cか他のキー\n");
        scanf("%d",&ans);
        system("cls");
        if (ans == 1)/*push*/{
            /* code */
            printf("pushしたい整数を入力");
            scanf("%d",&input);
            system("cls");
            if(input < 0){
                printf("これは負の数です\n");
                continue;
            }
            push_to_stack(&stack,input);
            printf("pushされました\n");
        }
        else if (ans == 3)/*pop*/{
            output = pop_from_stack(&stack);
            if(output != -1){
                system("cls");
                printf("%dです\n",output);
            }
        }
        else if (ans ==2)/*print all*/{
            /* code */
            system("cls");
            print_stack(&stack);
        }
        else if (ans ==4)/*peek*/{
            /* code */
            system("cls");
            peek_from_stack(&stack);
        }
        else{ /*else*/
            printf("プログラムを終了します");
            break;
        }  
    }
    return 0;
}


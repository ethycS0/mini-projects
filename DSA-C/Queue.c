#include <stdio.h>
#include <stdlib.h>

#define size 10

struct queue{
    int front;
    int rear;
    int s[size];
}Q;

void enqueue(int item){
    if(Q.rear != size - 1){
        Q.front = 0;
        Q.rear = Q.rear + 1;
        Q.s[Q.rear] = item;
    }
    else{
        printf("Queue is overflow");
    }
}
void dequeue(){
    if(Q.front != -1 || Q.front >! Q.rear ){
        printf("Deleted item is %d", Q.s[Q.front]);
        Q.front = Q.front + 1;
    }
    else{
        printf("Queue is underflow");
    }
}
void display(){
    for (int i = Q.front; i <= Q.rear; i++){
        printf("%d, ", Q.s[i]);
    }
    printf("\n");
}

int main()
{
    int c;
    int item;
    Q.rear = -1 ;
    Q.front = - 1;
    while (1){
        printf("\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &c);
        switch(c)
        {
            case 1:
                printf("Enter item: ");
                scanf("%d", &item);
                enqueue(item);
                break;
            case 2:
                dequeue();
                break;
            case 3:
                display();
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid Choice.");
        }
    }
   return 0;
}
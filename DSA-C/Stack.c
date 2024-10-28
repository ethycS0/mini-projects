#include <stdio.h>
#include <stdlib.h>

#define size 10

struct stack{
    int s[size];
    int top;
}st;

void push(int item)
{
    if (st.top!=size-1)
    {
        st.top++;
        st.s[st.top]= item;
    }
    else{
        printf("Stack overflow. Please Pop Items");
    }
    
}

void pop()
{
    int item;
    if (st.top != -1)
    {
        item = st.s[st.top];
        st.top--;
        printf("Popped item: %d\n", item);
    }
    else
    {
        printf("Stack underflow. Please push items");
    }
}

void display(){
    printf("top \n");
    for (int i = st.top; i>-1; i--)
    {
        printf("%d \n", st.s[i]);
    }
}

int main() {
    int c;
    int item;
    st.top = -1;
    while (1){
        printf("\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &c);
        switch(c)
        {
            case 1:
                printf("Enter item: ");
                scanf("%d", &item);
                push(item);
                break;
            case 2:
                pop();
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

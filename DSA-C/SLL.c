#include <stdio.h>
#include <stdlib.h>
// insert delete traversal search display
struct Node{
    int data;
    struct Node *next;
}ll;

void insert(struct Node** head, int data){
    struct Node* newNode = (struct Node*)
    malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = *head;
    *head = newNode;
    printf("Inserted %d \n",newNode->data);
}

void delete(struct Node** head){
    struct Node* temp = *head;

    if(*head ==NULL){
        printf("Cannot delete empty Singly Linked List.");
        return;
    }
    *head = (*head)->next;
    // for alternate deletion
    // *head = ((*head)->next)-next;
    printf("Deleted: %d \n",temp->data);
    free(temp);
}

void display(struct Node* node){
    printf("\n Linked List: ");
    while(node!=NULL){
        printf("%d ",node->data);
        node = node->next;
        // for alternate display
        // node = (node->next)->next;
    }
    printf("\n");
}

void count(struct Node* node){
    int i = 0;
    while(node!=NULL){
        i=i+1;
        node = node->next;
    }
    printf("Count: %d",i);
}

void search(struct Node* node, int key){
    int i = 1;
    
    while(node->data!=key ){
        i=i+1;
        node = node->next;
    }
    printf("Node you are searching for is on position: %d",i);
}

int main()
{   
    struct Node* head = NULL;
    int c;
    int data;
    int key;
    while (1){
        printf("\n");
        // printf("%p", (void *)head);
        printf("\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Display\n");
        printf("4. Count\n");
        printf("5. Search\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &c);
        switch(c)
        {
            case 1:
                printf("Enter data: ");
                scanf("%d", &data);
                insert(&head,data);
                break;
            case 2:
                delete(&head);
                break;
            case 3:
                display(head);
                break;
            case 4:
                count(head);
                break;
            case 5:
                printf("Enter data you want to search: ");
                scanf("%d", &key);
                search(head,key);
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid Choice.");
        }
    }
    return 0;
}
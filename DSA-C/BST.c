#include <stdio.h>
#include <stdlib.h>

struct node {
    int key;
    struct node *left, *right;
};

struct node *newNode(int item) {
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

void inorder(struct node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d -> ", root->key);
        inorder(root->right);
    }
}

void preorder(struct node *root) {
    if (root != NULL) {
        printf("%d -> ", root->key);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(struct node *root) {
    if (root == NULL) 
        return;
        postorder(root->left);
        postorder(root->right);
        printf("%d -> ", root->key);
}

struct node *insert(struct node *node, int key) {
    if (node == NULL) return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else
        node->right = insert(node->right, key);

    return node;
}

struct node *minValueNode(struct node *node) {
    struct node *current = node;

    while (current && current->left != NULL)
        current = current->left;

    return current;
}

struct node *deleteNode(struct node *root, int key) {
    if (root == NULL) return root;
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL) {
        struct node *temp = root->right;
        free(root);
        return temp;
        } else if (root->right == NULL) {
        struct node *temp = root->left;
        free(root);
        return temp;
        }
        struct node *temp = minValueNode(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

int main() {// Create a node

    int item;
    int c;
    struct node *root = NULL;
    printf("\nInsert Root Node: ");
    scanf("%d", &item);
    root = insert(root, item);
    while (1){
        printf("\n");
        printf("\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Inorder\n");
        printf("4. Preorder\n");
        printf("5. Postorder\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &c);
        switch(c)
        {
            case 1:
                printf("\nInsert Node: ");
                scanf("%d", &item);
                root = insert(root, item);  
                break;
            case 2: 
                printf("\nDelete Node: ");
                scanf("%d", &item);
                printf("\nAfter deleting %d \n", item);
                root = deleteNode(root, item);
                break;
            case 3:
                printf("Inorder traversal: ");
                inorder(root);
                break;
            case 4:
                printf("Preorder traversal: ");
                preorder(root);
                break;
            case 5:
                printf("Postorder traversal: ");
                postorder(root);
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid Choice.");
        }
    }
}
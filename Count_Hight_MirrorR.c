#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *left, *right;
};

struct node *createNode(int key)
{
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    newnode->data = key;
    newnode->left = NULL;
    newnode->right = NULL;
    return (newnode);
}

struct node *insertRecursive(struct node *root, int value)
{
    if (root == NULL)
        return createNode(value);

    if (value < root->data)
        root->left = insertRecursive(root->left, value);
    else if (value > root->data)
        root->right = insertRecursive(root->right, value);

    return root;
}

void inorderRecursive(struct node *root)
{
    if (root == NULL)
        return;
    inorderRecursive(root->left);
    printf("%d ", root->data);
    inorderRecursive(root->right);
}

void countNodesWithRecursion(struct node *root, int *count)
{
    if (root != NULL)
    {
        countNodesWithRecursion(root->left, count);
        (*count)++;
        countNodesWithRecursion(root->right, count);
    }
}

void mirrorWithRecursion(struct node *node)
{
    if (node == NULL)
        return;
    else
    {
        struct node *temp;

        mirrorWithRecursion(node->left);
        mirrorWithRecursion(node->right);

        temp = node->left;
        node->left = node->right;
        node->right = temp;
    }
}

int heightWithRecursion(struct node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    else
    {
        int left = heightWithRecursion(root->left);
        int right = heightWithRecursion(root->right);
        if (left > right)
        {
            return left + 1;
        }
        else
        {
            return right + 1;
        }
    }
}

int main()
{
    struct node *root = NULL;
    int count = 0;
    int choice, value;
    do
    {
        printf("\n\n1. Insert (Recursive)\n");
        printf("2. Inorder Traversal (Recursive)\n");
        printf("3. Count Nodes (Recursive)\n");
        printf("4. Mirror Tree (Recursive)\n");
        printf("5. Height of Tree (Recursive)\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter value to insert: ");
            scanf("%d", &value);
            root = insertRecursive(root, value);
            break;
        case 2:
            printf("Inorder Traversal (Recursive): ");
            inorderRecursive(root);
            printf("\n");
            break;
        case 3:
            countNodesWithRecursion(root, &count);
            printf("Number of nodes in tree (Recursive): %d\n", count);
            break;
        case 4:
            mirrorWithRecursion(root);
            printf("Mirror tree (Recursive) created.\n");
            inorderRecursive(root);
            printf("\n");
            break;
        case 5:
            printf("Height of tree (Recursive): %d\n", heightWithRecursion(root));
            break;
        case 0:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice. Please enter a number between 0 and 5.\n");
        }
    } while (choice != 0);

    return 0;
}

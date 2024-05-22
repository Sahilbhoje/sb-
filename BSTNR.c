#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

typedef struct TreeNode TreeNode;

TreeNode* createNode(int val) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

TreeNode* insert(TreeNode* root, int val) {
    if (root == NULL) {
        return createNode(val);
    }
    TreeNode* current = root;
    TreeNode* parent = NULL;
    while (current != NULL) {
        parent = current;
        if (val < current->data) {
            current = current->left;
        } else if (val > current->data) {
            current = current->right;
        } else {
            // If the value already exists, do nothing.
            return root;
        }
    }
    if (val < parent->data) {
        parent->left = createNode(val);
    } else {
        parent->right = createNode(val);
    }
    return root;
}

void preorderTraversal(TreeNode* root) {
    if (root == NULL) return;
    TreeNode* stack[100]; // Assuming maximum 100 nodes for simplicity
    int top = -1;
    stack[++top] = root;
    while (top >= 0) {
        TreeNode* node = stack[top--];
        printf("%d ", node->data);
        if (node->right != NULL) stack[++top] = node->right;
        if (node->left != NULL) stack[++top] = node->left;
    }
}

void inorderTraversal(TreeNode* root) {
    if (root == NULL) return;
    TreeNode* stack[100]; // Assuming maximum 100 nodes for simplicity
    int top = -1;
    TreeNode* current = root;
    while (current != NULL || top >= 0) {
        while (current != NULL) {
            stack[++top] = current;
            current = current->left;
        }
        current = stack[top--];
        printf("%d ", current->data);
        current = current->right;
    }
}

void postorderTraversal(TreeNode* root) {
    if (root == NULL) return;
    TreeNode* stack[100]; // Assuming maximum 100 nodes for simplicity
    int top = -1;
    TreeNode* prev = NULL;
    do {
        while (root != NULL) {
            stack[++top] = root;
            root = root->left;
        }
        while (root == NULL && top != -1) {
            root = stack[top];
            if (root->right == NULL || root->right == prev) {
                printf("%d ", root->data);
                top--;
                prev = root;
                root = NULL;
            } else {
                root = root->right;
            }
        }
    } while (top != -1);
}

TreeNode* minValueNode(TreeNode* node) {
    TreeNode* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

TreeNode* deleteNode(TreeNode* root, int val) {
    if (root == NULL) return root;

    TreeNode* current = root;
    TreeNode* parent = NULL;

    // Find the node to be deleted and its parent
    while (current != NULL && current->data != val) {
        parent = current;
        if (val < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    // If the node with val doesn't exist
    if (current == NULL) return root;

    // Node to be deleted has no children or only one child
    if (current->left == NULL) {
        if (parent == NULL) {
            TreeNode* temp = current->right;
            free(current);
            return temp;
        }
        if (parent->left == current) {
            parent->left = current->right;
        } else {
            parent->right = current->right;
        }
        free(current);
        return root;
    } else if (current->right == NULL) {
        if (parent == NULL) {
            TreeNode* temp = current->left;
            free(current);
            return temp;
        }
        if (parent->left == current) {
            parent->left = current->left;
        } else {
            parent->right = current->left;
        }
        free(current);
        return root;
    }

    // Node to be deleted has two children
    TreeNode* temp = minValueNode(current->right);
    current->data = temp->data;
    current->right = deleteNode(current->right, temp->data);
    return root;
}

void displayMenu() {
    printf("\n1. Insert\n");
    printf("2. Preorder Traversal\n");
    printf("3. Inorder Traversal\n");
    printf("4. Postorder Traversal\n");
    printf("5. Delete Node\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    TreeNode* root = NULL;
    int choice, val;
    do {
        displayMenu();
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &val);
                root = insert(root, val);
                break;
            case 2:
                printf("Preorder Traversal: ");
                preorderTraversal(root);
                printf("\n");
                break;
            case 3:
                printf("Inorder Traversal: ");
                inorderTraversal(root);
                printf("\n");
                break;
            case 4:
                printf("Postorder Traversal: ");
                postorderTraversal(root);
                printf("\n");
                break;
            case 5:
                printf("Enter value to delete: ");
                scanf("%d", &val);
                root = deleteNode(root, val);
                printf("Node deleted.\n");
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 6);

    return 0;
}
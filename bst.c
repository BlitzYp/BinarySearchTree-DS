#include <stdio.h>
#include <malloc.h>

typedef struct treeNode
{
    int value;
    struct treeNode *right;
    struct treeNode *left;
} treeNode;

typedef struct binaryTree
{
    size_t size;
    treeNode *root;
    treeNode* (*addNode)(treeNode *root, int value, struct binaryTree* tree);
    treeNode *(*createNode)(int value);
    void (*createNodePut)(int value, treeNode** dest);
    int (*search)(treeNode* root, int value);
} binaryTree;

treeNode *createNode(int value)
{
    treeNode *node = malloc(sizeof(treeNode));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
}

void createNodePut(int value, treeNode** dest)
{
    *dest = malloc(sizeof(treeNode));
    (*dest)->value = value;
    (*dest)->right = NULL;
    (*dest)->left = NULL;
}

treeNode* addNode(treeNode* root, int value, binaryTree* tree)
{
    if (root == NULL)
    {
        root = tree->createNode(value);
        /*
        Can also be done as 
        tree->createNodePut(value, &root);
        */
        tree->size++;
        return root;
    }

    if (value < root->value) root->left = addNode(root->left, value, tree);
    else root->right = addNode(root->right, value, tree);
    return root;
}


int search(treeNode *root, int value)
{
    if (root->value == value) return 1;
    if (value < root->value) return search(root->left, value);
    else if (value > root->value) return search(root->right, value);
}

binaryTree *createTree()
{
    binaryTree *tree = malloc(sizeof(binaryTree));
    tree->addNode = addNode;
    tree->createNode = createNode;
    tree->search = search;
    tree->createNodePut = createNodePut;
    tree->size = 1;
    tree->root = NULL;
    return tree;
}

void inOrder(treeNode* root, int* values)
{
    static int index = 0;
    if (root->left != NULL) inOrder(root->left, values);
    values[index++] = root->value;
    if (root->right != NULL) inOrder(root->right, values);
}

void postOrder(treeNode* root, int* values)
{
    static int index = 0;
    if (root->left != NULL) inOrder(root->left, values);
    if (root->right != NULL) inOrder(root->right, values);
    values[index++] = root->value;
}

void preOrder(treeNode* root, int* values) 
{
    static int index = 0;
    values[index++] = root->value;
    if (root->left != NULL) inOrder(root->left, values);
    if (root->right != NULL) inOrder(root->right, values);
}

int main(void)
{
    binaryTree *tree = createTree();
    tree->createNodePut(3, &tree->root);
    tree->addNode(tree->root, 5, tree);
    tree->addNode(tree->root, 2, tree);
    tree->addNode(tree->root, 4, tree);
    tree->addNode(tree->root, 23, tree);
    int res = tree->search(tree->root, 2);
    printf("%d\n", res);
    return 0;
}

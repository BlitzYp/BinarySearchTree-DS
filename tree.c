#include <stdio.h>
#include <stdint.h>
#include <malloc.h>

typedef struct node_t {
    uint8_t value;
    struct node_t* right;
    struct node_t* left;
} node_t;

static node_t* create_node(uint8_t value);
static void insert(node_t* root, uint8_t value, node_t* prev);

int main()
{
    node_t* root = create_node(2);
    insert(root, 3, root);
    insert(root, 1, root);
    insert(root, 5, root);
    printf("%d\n", root->right->value);
}

static node_t* create_node(uint8_t value) 
{
    node_t* res = (node_t*)malloc(sizeof(node_t));
    res->value = value;
    res->right = NULL;
    res->left = NULL;
    return res;
}

static void insert(node_t* root, uint8_t value, node_t* prev) 
{
    if (root == NULL) 
    {
        root = create_node(value);
        if (value > prev->value) 
            prev->right = root;
        else 
            prev->left = root;
        return;
    }

    if (root->value < value)
        return insert(root->right, value, root);

    else if (root->value > value)
        return insert(root->left, value, root);
}

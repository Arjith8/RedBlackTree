#include <stdio.h>

enum Color{
    RED,
    BLACK
};

struct RedBlackTreeNode {
    int val;
    enum Color color; 
    struct RedBlackTreeNode *left_child;
    struct RedBlackTreeNode *right_child;
    struct RedBlackTreeNode *parent;
};

struct RedBlackTreeNode *create_node(int value);
struct RedBlackTreeNode* insertNode(struct RedBlackTreeNode *node, struct RedBlackTreeNode *root);
void print_tree(const struct RedBlackTreeNode *root);

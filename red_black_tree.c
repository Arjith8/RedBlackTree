#include <stdlib.h>
#include <stdio.h>
#include "red_black_tree.h"

struct RedBlackTreeNode *create_node(int value) {
    struct RedBlackTreeNode *node = malloc(sizeof(*node));
    if (node==NULL){
        return NULL;
    }

    node->val = value;
    node->color = RED;
    node->left_child = NULL;
    node->right_child = NULL;
    node->parent = NULL;

    return node;
}

static struct RedBlackTreeNode *resolveConflicts(struct RedBlackTreeNode *node, struct RedBlackTreeNode *root);

struct RedBlackTreeNode *insertNode(struct RedBlackTreeNode *node, struct RedBlackTreeNode *root){
    struct RedBlackTreeNode *current = root;
    while (current != NULL){
        if (current->val > node->val){
            if (current->left_child == NULL){
                node->parent = current;
                current->left_child = node;
                break;
            }
            current = current->left_child;
        } else {
            if (current->right_child == NULL){
                node->parent = current;
                current->right_child = node;
                break;
            }
            current = current->right_child;
        }
    };
    return resolveConflicts(node, root);
}


static struct RedBlackTreeNode *left_rotate(struct RedBlackTreeNode *node, struct RedBlackTreeNode *root){
    struct RedBlackTreeNode *parent_node = node->parent;
    struct RedBlackTreeNode *grand_parent_node = parent_node->parent;

    struct RedBlackTreeNode *great_grand_parent_node = grand_parent_node->parent;
    if (great_grand_parent_node != NULL){
        if (great_grand_parent_node->left_child == grand_parent_node)
            great_grand_parent_node->left_child = parent_node;
        else
            great_grand_parent_node->right_child = parent_node;
    }

    struct RedBlackTreeNode *parent_left_child = parent_node->left_child;
    parent_node->left_child = grand_parent_node;
    parent_node->parent = great_grand_parent_node;
    grand_parent_node->parent = parent_node;
    grand_parent_node->right_child = parent_left_child;
    if (parent_left_child != NULL)
        parent_left_child->parent = grand_parent_node;

    if (great_grand_parent_node == NULL)
        root = parent_node;
    
    return root;
}

static struct RedBlackTreeNode *right_rotate(struct RedBlackTreeNode *node, struct RedBlackTreeNode *root){
    struct RedBlackTreeNode *parent_node = node->parent;
    struct RedBlackTreeNode *grand_parent_node = parent_node->parent;

    struct RedBlackTreeNode *great_grand_parent_node = grand_parent_node->parent;
    if (great_grand_parent_node != NULL){
        if (great_grand_parent_node->left_child == grand_parent_node)
            great_grand_parent_node->left_child = parent_node;
        else
            great_grand_parent_node->right_child = parent_node;
    }

    struct RedBlackTreeNode *parent_right_child = parent_node->right_child;
    parent_node->right_child = grand_parent_node;
    parent_node->parent = great_grand_parent_node;
    grand_parent_node->parent = parent_node;
    grand_parent_node->left_child = parent_right_child;
    if (parent_right_child != NULL)
        parent_right_child->parent = grand_parent_node;

    if (great_grand_parent_node == NULL)
        root = parent_node;
    
    return root;
}

static struct RedBlackTreeNode *resolveConflicts(struct RedBlackTreeNode *node, struct RedBlackTreeNode *root){
    if (node->color != RED || node->parent->color != RED)
        return root;
    

    struct RedBlackTreeNode *parent_node = node->parent;
    if (parent_node->parent == NULL){
        return root;
    }

    struct RedBlackTreeNode *grandparent_node = parent_node->parent;
    struct RedBlackTreeNode *uncle_node;
    if (grandparent_node->left_child == node->parent)
        uncle_node = grandparent_node->right_child;
    else
        uncle_node = grandparent_node->left_child;

    if (uncle_node != NULL && uncle_node->color != BLACK){
        uncle_node->color = BLACK;
        parent_node->color = BLACK;
        if (grandparent_node != root){
            grandparent_node->color = RED;
            return resolveConflicts(grandparent_node, root);
        }
    } else {
        if (grandparent_node->right_child == parent_node && parent_node->right_child == node){
            root = left_rotate(node, root);
        } else if (grandparent_node->left_child == parent_node && parent_node->left_child == node){
            root = right_rotate(node, root);
        } else if (grandparent_node->left_child == parent_node && parent_node->right_child == node){
            root = left_rotate(node, root);
            root = right_rotate(node, root);
        } else {
            root = right_rotate(node, root);
            root = left_rotate(node, root);
        }
        grandparent_node->color = RED;
        parent_node->color = BLACK;
    }
    return root;
}

static void print_tree_helper(const struct RedBlackTreeNode *node, int depth) {
    if (node == NULL) {
        return;
    }
    print_tree_helper(node->right_child, depth + 1);
    for (int i = 0; i < depth; i++){
        if (i == depth - 1 && node->val < 0){
            printf("   ");
            continue;
        }
        printf("    ");
    }
    printf("%d(%c)\n", node->val, node->color == RED ? 'R' : 'B');
    print_tree_helper(node->left_child, depth + 1);
}

void print_tree(const struct RedBlackTreeNode *root) {
    if (root == NULL) {
        printf("(empty tree)\n");
        return;
    }
    print_tree_helper(root, 0);
}


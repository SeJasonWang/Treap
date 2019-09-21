//
//  main.c
//  Treap
//
//  Created by Jason on 18/5/19.
//  Copyright © 2019 UTAS. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bst.h"

// 左旋转
BSTNodePtr rotate_left(BSTNodePtr node) {
    BSTNodePtr x = node->right;
    node->right = x->left;
    x->left =node;
    
    return x;
}

// 右旋转
BSTNodePtr rotate_right(BSTNodePtr node) {
    BSTNodePtr x = node->left;
    node->left = x->right;
    x->right = node;
    
    return x;
}

// 插入操作
BSTNodePtr treap_insert(BSTNodePtr self, int key, int priority) {
    //根为NULL，则直接创建此结点为根结点
    if (self == NULL) {
        self = malloc(sizeof( *self));
        self->priority = priority;
        self->key = key;
        self->left = self->right = NULL;
    }
    //向左插入结点
    else if (key < self->key) {
        self->left = treap_insert(self->left, key, priority);
        if (self->left->priority > self->priority)
            self = rotate_right(self);
    }
    
    //向右插入结点
    else
    {
        self->right = treap_insert(self->right, key, priority);
        if (self->right->priority > self->priority)
            self = rotate_left(self);
    }
    return self;
}

void insert_bst(BST *self, int key, int priority) {
    self->root = treap_insert(self->root, key, priority);
}


BSTNodePtr min_node(BSTNodePtr self) {
    BSTNodePtr current = self;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

BSTNodePtr delete_bst_node(BSTNodePtr self, int key) {
    if (self != NULL) {
        if (key == self->key) {
            if (self->left != NULL && self->right != NULL) {
                // two child case
                BSTNodePtr successor = min_node(self->right);
                self->key = successor->key;
                self->right = delete_bst_node(self->right, self->key);
            } else { // one or zero child case
                BSTNodePtr to_free = self;
                if (self->left) {
                    self = self->left;
                } else {
                    self = self->right;
                }
                free(to_free);
            }
        } else if (key < self->key) {
            self->left = delete_bst_node(self->left, key);
        } else {
            self->right = delete_bst_node(self->right, key);
        }
    }
    return self;
}

BSTNodePtr treap_delete(BSTNodePtr self, int key) {
    if (self != NULL) {
        if (key == self->key) {
            if (self->left != NULL && self->right != NULL) {
                // two child case
                if (self->left->priority > self->right->priority) {
                    rotate_right(self);
                    treap_delete(self->right, key);
                } else {
                    rotate_left(self);
                    treap_delete(self->left, key);
                }
            } else { // one or zero child case
                BSTNodePtr to_free = self;
                if (self->left) {
                    self = self->left;
                } else {
                    self = self->right;
                }
                free(to_free);
            }
        } else if (key < self->key) {
            self->left = treap_delete(self->left, key);
        } else {
            self->right = treap_delete(self->right, key);
        }
    }
    return self;
}

void delete_bst(BST *self, int key) {
//    self->root = delete_bst_node(self->root, key);
    self->root = treap_delete(self->root, key);
}


//中序遍历
void in_order_traverse(BSTNodePtr self) {
    if (self != NULL) {
        printf("(");
        in_order_traverse(self ->left);
        printf(" %d ", self ->key);
        in_order_traverse(self ->right);
        printf(")");
    } else {
        printf("_");
    }
}

void print_in_order_bst(BST *self) {
    in_order_traverse(self->root);
}

//计算树的高度
int depth(BSTNodePtr node) {
    if (node == NULL)
        return -1;
    int l = depth(node->left);
    int r = depth(node->right);
    return (l < r) ? (r+1) : (l+1);
}

int main() {
    
    BST tree = new_bst();
    
    int number = 9;

    int key[9] =      {5, 2, 7,  6, 3,  17, 10, 8, 12};
    int priority[9] = {9, 8, 11, 7, 14, 1,  10, 15, 2};
    
    //插入9个节点
    printf("----------------------创建Treap树堆-----------------------\n");
    for (int i = 0; i < number; i++) {
        int pri = priority[i];
        int k = key[i];
        printf("key:%d priority: %d\n", k, pri);
        insert_bst(&tree, k, pri);
    }
    
    //中序遍历Treap
    printf("\n插入完毕，中序遍历Treap所得结果为:\n");
    print_in_order_bst(&tree);
    
    printf("\nTreap高度：%d\n", depth(tree.root));
    
    printf("----------------------删除结点-----------------------\n");
    printf("请输入要删除的结点键值\n");
    int rmKey;
    scanf("%d",&rmKey);
    delete_bst(&tree, rmKey);
    
    printf("\n删除完毕，中序遍历Treap所得结果为:\n");
    print_in_order_bst(&tree);
    
    printf("\nTreap高度：%d\n", depth(tree.root));
    getchar();

    return 0;
}

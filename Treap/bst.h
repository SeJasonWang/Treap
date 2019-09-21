//
//  bst.h
//  Treap
//
//  Created by Jason on 18/5/19.
//  Copyright © 2019 UTAS. All rights reserved.
//

#ifndef bst_h
#define bst_h

#include <stdio.h>

typedef struct bstNode {
    int key; // 关键字
    int priority; // 随机优先级
    struct bstNode *left;
    struct bstNode *right;
} *BSTNodePtr;

typedef struct bst {
    BSTNodePtr root;
} BST;

BST new_bst(void);

#endif /* bst_h */

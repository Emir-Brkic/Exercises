#include <stdio.h>
#include <stdlib.h>
// Strict/Proper binary tree
// each node have either 2 or 0 children

//Balanced Binray Tree
//difference between height of left
//and right subree for evry node is
//not more than k(mostly 1)

//Complete Binary tree
// all leveles except the last
//are completely filled and all nodes are
//as left as possible
//h = log2(n)

//Perfect Binary tree
//h = log2(n+1)-1

//BST
//For each node the value of all the nodes in left subtree
//is lesser and value of all the nodes in right subtree is greater

//Min-height
//log2(n)
//Max-height
//n-1




//        Array(unsorted)  Linked LIsit Array(sorted)   BST
//Search      O(n)            O(n)          O(log(n))  O(log(n))             
//Insert      O(1)            O(1)          O(n)       O(log(n))
//Remove      O(n)            O(n)          O(n)       O(log(n))
typedef struct node
{
    int data;
    node *l_child;
    node *r_child;
}node;


int main() {
    node *root;

    root = calloc(1, sizeof(node));
    root->data = -1;
    int val = 0;
    while(1) {
        
        printf("Inserisci valore : ");
        scanf("%d", &val);

        insert_v(root,val);

    }

    return 0;
}

void insert_v(node *node, int val) {
    if(node->data == -1) {
        node->data = val;
        return;
    }
    else if(node->data > val) {
        if(node->l_child != NULL) {
            insert_v(node->l_child, val);
            return;
        }
        else {
            node->l_child = calloc(1,sizeof(node));
            if(node->l_child == NULL) {
                printf("Failed to allocate memori for a ndoe.");
                return;
            }
            node->l_child->data = -1;
            insert_v(node->l_child, val);
            return;
        }
    }
    else {
        if(node->l_child != NULL) {
            insert_v(node->r_child, val);
            return;
        }
        else {
            node->r_child = calloc(1,sizeof(node));
            if(node->r_child == NULL) {
                printf("Failed to allocate memori for a ndoe.");
                return;
            }
            node->r_child->data = -1;
            insert_v(node->r_child, val);
            return;
        }
    }
    return ;
}
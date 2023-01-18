#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
typedef struct node_t
{
    int data;
    struct node *l_child;
    struct node *r_child;
}node_t;

#define max(a,b) (((a) > (b)) ? (a) : (b))

node_t *new_node(int val);
node_t *insert_node(node_t *node, int val);
int depth(node_t *node);

int main() {
    node_t *root;

    root = new_node(5);

    int val = 0;
    printf("Inizio\n");
    for(int i = 0; i < 3; i ++) {
        
        printf("Inserisci valore : ");
        scanf("%d", &val);

        insert_node(root,val);

    }

    printf("\nD = %d", depth(root));



    return 0;
}

node_t *new_node(int val) {
    node_t *new_node;
    new_node = calloc(1, sizeof(node_t));

    if(new_node == NULL) {
        printf("Failed to allocate memory!");
        exit(1);
    }

    new_node->data = val;
    new_node->l_child = NULL;
    new_node->r_child = NULL;

    return new_node;
}

node_t *insert_node(node_t *node, int val) {
    if(node == NULL) {
        return new_node(val);
    }
    else if(val < node->data){
        node_t *new_node = insert_node(node->l_child, val);
        if(new_node != NULL) {
            node->l_child = new_node;
        }
        return NULL;
    }
    else if(val > node->data){
        node_t *new_node = insert_node(node->r_child, val);
        if(new_node != NULL) {
            node->r_child = new_node;
        }
        return NULL;
    }
    else if(val == node->data) {
        printf("Value already exist in the tree!");
        return NULL;
    }
}



int depth(node_t *node) { 
    if(node == NULL) {return 0;}
    int left = depth(node->l_child);
    int right = depth(node->r_child);
    return max(left,right) + 1;
}


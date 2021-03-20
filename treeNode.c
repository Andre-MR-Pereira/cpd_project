#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    double radius;
    long node_id;
    struct Node* L;
    struct Node* R;
    double* coordinates;

} node_t;

extern int n_dims;
extern long node_id;

void copyCoordinates(double* copy, double* original){

    for (int i = 0; i < n_dims; i++){

        copy[i] = original[i];
    }
}

node_t* createNode(double* point, double radius){

    node_t* node = malloc(sizeof(node_t));

    node->radius = radius;
    node->node_id = ++node_id;
    node->L = NULL;
    node->R = NULL;
    node->coordinates = malloc(n_dims * sizeof(double));
    copyCoordinates(node->coordinates, point);

    return node;
}

void printCoordinates(double* point){

    for (int i = 0; i < n_dims; i++){
        printf(" %.6f", point[i]);
    }
    printf("\n");
}

void printNode(node_t* node){

    if (node->L != NULL){
        printNode(node->L);
        printNode(node->R);

        printf("%ld %ld %ld %.6f", node->node_id, node->L->node_id, node->R->node_id, node->radius);
        printCoordinates(node->coordinates);
    }
    else{
        printf("%ld -1 -1 %.6f", node->node_id, node->radius);
        printCoordinates(node->coordinates);
    }
}

void freeNode(node_t* node){

    free(node->coordinates);
    free(node);
}

void freeTree(node_t* node){

    if (node->L != NULL){
        freeTree(node->L);
        freeTree(node->R);
    }
    
    freeNode(node);
}
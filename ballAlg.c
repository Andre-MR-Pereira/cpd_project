#include <stdio.h>
#include <omp.h>
#include <math.h>

#include "treeNode.c"
#include "gen_points.c"
#include "point_operations.c"

int n_dims = 0;
long node_id = -1;

node_t* build_tree(double** pts, long n_points){

    if (n_points < 2){
        return createNode(pts[0], 0.0); 
    }

    long* furthestApart = computeFurthestApart(pts, n_points);

    double** orthogonalPoints = malloc(n_points * sizeof(double*));

    for(long i = 0; i < n_points; i++){

        orthogonalPoints[i] = computeOrthogonalProjection(
                                pts[i], pts[furthestApart[0]],pts[furthestApart[1]]);
    }

    double* center = computeMedian(orthogonalPoints, n_points);

    long countL = 0;

    for (long i = 0; i < n_points; i++){
        if (orthogonalPoints[i][0] < center[0]){
            countL++;
        }
    }

    double** arrayL = malloc(countL * sizeof(double*));

    double** arrayR = malloc((n_points - countL) * sizeof(double*));

    long l = 0, r = 0;

    for (long i = 0; i < n_points; i++){
        if (orthogonalPoints[i][0] < center[0]){
            arrayL[l] = malloc(n_dims * sizeof(double));
            copyCoordinates(arrayL[l], pts[i]);
            l++;
        }
        else{
            arrayR[r] = malloc(n_dims * sizeof(double));
            copyCoordinates(arrayR[r], pts[i]);
            r++;
        }
    }

    double maxDist = 0.0;

    for (long i = 0; i < n_points; i++){

        double dist = computeDistance(center, pts[i]);

        if (dist > maxDist){
            maxDist = dist;
        }
    }

    node_t* node = createNode(center, maxDist);

    node->L = build_tree(arrayL, countL);
    node->R = build_tree(arrayR, n_points - countL);

    for (long i = 0; i < n_points; i++){
        free(orthogonalPoints[i]);
    }
    for (long i = 0; i < countL; i++){
        free(arrayL[i]);
    }
    for (long i = 0; i < (n_points - countL); i++){
        free(arrayR[i]);
    }
    free(orthogonalPoints);
    free(arrayL);
    free(arrayR);
    free(furthestApart);
    free(center);

    return node;
}

void dump_tree(node_t* root){

    printf("%d %ld\n", n_dims, node_id + 1);

    printNode(root);
}

int main(int argc, char*argv[]){

    if(argc < 4){
        printf("Usage: %s <n_dimensions> <n_points> <seed>\n", argv[0]);
        exit(1);
    }

    n_dims = atoi(argv[1]);
    long n_points = atol(argv[2]);
    
    double exec_time;
    exec_time = -omp_get_wtime();
    double ** pts = get_points(argc, argv, &n_dims, &n_points);

    node_t* root = build_tree(pts, n_points);

    exec_time += omp_get_wtime();
    fprintf(stderr, "%.1lf\n", exec_time);
    dump_tree(root);

    freeTree(root);
    free(pts[0]);
    free(pts);

    return 0;
}
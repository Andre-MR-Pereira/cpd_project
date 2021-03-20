#include "quickSortPoints.c"

extern int n_dims;

double** createArrayCopy(double** pts, long n_points){

    double** ptsCopy = malloc(n_points * sizeof(double*));

    for (long i = 0; i < n_points; i++){

        double* point = malloc(n_dims * sizeof(double));

        for (int j = 0; j < n_dims; j++){

            point[j] = pts[i][j];
        }

        ptsCopy[i] = point;
    }

    return ptsCopy;
}

void freeArray(double** pts, long n_points){

    for (long i = 0; i < n_points; i++){
        free(pts[i]);
    }

    free(pts);
}

double computeDistance(double* pointA, double* pointB){

    double dist = 0.0;

    for(int d = 0; d < n_dims; d++){

        dist += (pointA[d] - pointB[d]) * (pointA[d] - pointB[d]);
    }

    return sqrt(dist);
}

long* computeFurthestApart(double** pts, long n_points){

    long* pointsAB = malloc(2 * sizeof(long));

    double maxDist = 0.0;
    double dist = 0.0;

    for (long i = 1; i < n_points; i++){    

        dist = computeDistance(pts[0], pts[i]);
        if (dist > maxDist) {
            pointsAB[0] = i;
            maxDist = dist;
        }
    }

    maxDist = 0;

    for (long i = 0; i < n_points; i++){    

        dist = computeDistance(pts[pointsAB[0]], pts[i]);
        if (dist > maxDist) {
            pointsAB[1] = i;
            maxDist = dist;
        }
    }

    return pointsAB;
}

double computeInnerProduct(double* pointA, double* pointB){

    double InnerProduct = 0.0;

    for (int i = 0; i < n_dims; i++){

        InnerProduct += pointA[i] * pointB[i];
    }

    return InnerProduct;
}

double* computeDifference(double* pointA, double* pointB){

    double* point = malloc(n_dims * sizeof(double));

    for (int i = 0; i < n_dims; i++){

        point[i] = pointA[i] - pointB[i];
    }

    return point;
}

double* computeOrthogonalProjection(double* point, double* pointA, double* pointB){

    double* diffBA = computeDifference(pointB, pointA);

    double* diffPA = computeDifference(point, pointA);

    double val1 = computeInnerProduct(diffPA, diffBA);

    double val2 = computeInnerProduct(diffBA, diffBA);

    double val = val1/val2;

    for (int i = 0; i < n_dims; i++) {

        diffBA[i] = diffBA[i] * val;
    }

    for (int i = 0; i < n_dims; i++) {

        diffBA[i] = diffBA[i] + pointA[i];
    }

    free(diffPA);

    return diffBA;
}

double* computeMedian(double** pts, long n_points){

    double** ptsCopy = createArrayCopy(pts, n_points);

    quickSort(ptsCopy, 0, n_points - 1);

    double* center = malloc(n_dims * sizeof(double));

    if (n_points % 2 == 1){

        for (int i = 0; i < n_dims; i++){

            center[i] = ptsCopy[(n_points - 1)/2][i];
        }

        freeArray(ptsCopy, n_points);

        return center;
    }
    else {

        for (int i = 0; i < n_dims; i++){

            center[i] = (ptsCopy[(n_points - 2)/2][i] + ptsCopy[n_points/2][i])/2;
        }

        freeArray(ptsCopy, n_points);

        return center;
    }
    
}
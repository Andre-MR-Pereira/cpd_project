#include <stdio.h> 

extern int n_dims;

int lessOrEqual(double* pointA, double* pointB){

    for (int i = 0; i < n_dims; i++) {

        if (pointA[i] < pointB[i]) {
            return 1;
        }

        if (pointA[i] > pointB[i]) {
            return 0;
        }
    }

    return 1;
}

void swap(double* pointA, double* pointB) 
{ 
    for (int i = 0; i < n_dims; i++){

        double temp = pointA[i]; 
        pointA[i] = pointB[i]; 
        pointB[i] = temp; 
    }
} 

long partition(double** pts, long l, long h) 
{ 
    double* p = pts[h]; 
    long i = l - 1;
  
    for (long j = l; j <= h - 1; j++) { 

        if (lessOrEqual(pts[j], p)) { 
            i++; 
            swap(pts[i], pts[j]); 
        } 
    } 

    swap(pts[i + 1], pts[h]); 
    return (i + 1); 
} 
  
void quickSort(double** pts, long l, long h) 
{ 
    if (l < h) { 

        long p = partition(pts, l, h); 
        quickSort(pts, l, p - 1); 
        quickSort(pts, p + 1, h); 
    } 
} 
ballAlg: ballAlg.c gen_points.c point_operations.c quickSortPoints.c treeNode.c
	gcc -g -pedantic -Wall -fopenmp -O3 -o ballAlg ballAlg.c -lm
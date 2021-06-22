#include <stdio.h>


void add(int A[3][3], int B[3][3], int C[3][3])
{
    int i, j;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            C[i][j] = A[i][j] + B[i][j];
}

int main() {
	//create matrixs 
	int matrix_1[3][3] = {
		{1, 1, 1},
        {2, 2, 2},
		{3, 3, 3}};
	int matrix_2[3][3] = {
		{1, 1, 1},
        {2, 2, 2},
		{3, 3, 3}};
	//create a new matrix to store
	int C[3][3];
	add(matrix_1 , matrix_2, C);
	
	printf("Result matrix is \n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
           printf("%d ", C[i][j]);
        printf("\n");
    }
 
    return 0;
}

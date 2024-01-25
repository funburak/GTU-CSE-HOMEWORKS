#include <stdio.h>
#include <stdlib.h>


void createMatrix(char matrix[], int row, int col);
void printMatrix(char matrix[], int row, int col);
void addBomb(char matrix[], int col, int bombRow, int bombCol);
void addBombEverywhere(char matrix[], int row, int col);
void copyMatrix(char matrix1[], char matrix2[], int row, int col);
void detonateBombs(char matrix[], char matrix2[], int row, int col);

int main(){
    int rowMatrix, colMatrix;
    int bombCount;
    int bombRow,bombCol;
    char* matrix;
    char* matrix2;

    printf("Please enter the number of row in matrix: ");
    scanf("%d",&rowMatrix);
    printf("Please enter the number of columns in matrix: ");
    scanf("%d",&colMatrix);
    printf("Please enter the number of bombs that will be placed on matrix: ");
    scanf("%d",&bombCount);

    matrix = (char *)malloc((rowMatrix*colMatrix) * sizeof(char *));
    matrix2 = (char *)malloc((rowMatrix*colMatrix) * sizeof(char *));

    createMatrix(matrix,rowMatrix,colMatrix);
    createMatrix(matrix2,rowMatrix,colMatrix);

    for(int i=0; i<bombCount; ++i){
        printf("Enter the row and column of bomb %d: ", (i+1));
        scanf("%d %d",&bombRow, &bombCol);
        addBomb(matrix,colMatrix,bombRow,bombCol);
    }

    printf("Initial State\n");
    printMatrix(matrix,rowMatrix,colMatrix);
    printf("After 1 second\n");
    copyMatrix(matrix,matrix2, rowMatrix, colMatrix);
    printMatrix(matrix2,rowMatrix,colMatrix);
    printf("After 2 seconds\n");
    addBombEverywhere(matrix2,bombRow,bombCol);
    printMatrix(matrix2,bombRow,bombCol);
    printf("After 3 seconds\n");
    detonateBombs(matrix,matrix2,bombRow,bombCol);
    printMatrix(matrix2,rowMatrix,colMatrix);
    copyMatrix(matrix2,matrix,rowMatrix,colMatrix);



    return 0;
}


void createMatrix(char matrix[], int row, int col){
    for(int r=0; r<row; r++){
        for(int c=0; c<col; c++){
            matrix[r * col + c] = '.';
        }
    }
}

void printMatrix(char matrix[], int row, int col){
    for(int r=0; r<row; ++r){
        for(int c=0; c<col; ++c){
            printf("%c ",matrix[r * col + c]);
        }
        printf("\n");
    }
}

void addBomb(char matrix[], int col, int bombRow, int bombCol){
    matrix[bombRow * col + bombCol] = 'O';
}

void addBombEverywhere(char matrix[], int row, int col){
    for(int r=0; r<row; ++r){
        for(int c=0; c<col; ++c){
            if(matrix[r * col + c] != 'O'){
                matrix[r * col + c] = 'O';
            }
        }
    }
}

void copyMatrix(char matrix1[], char matrix2[], int row, int col){
    for(int r=0; r<row; ++r){
        for(int c=0; c<col; ++c){
            matrix2[r * col + c] = matrix1[r * col + c];
        }
    }
}

void detonateBombs(char matrix1[], char matrix2[], int row, int col){
    for(int r=0; r<row; ++r){
        for(int c=0; c<col; ++c){
            if(matrix1[r * col + c] == 'O'){
                matrix2[r + col + c] = '.';
                if (r - 1 >= 0) matrix2[(r - 1) * col + c] = '.';
                if (r + 1 < 16) matrix2[(r + 1) * col + c] = '.';
                if (c - 1 >= 0) matrix2[r * col + (c - 1)] = '.';
                if (c + 1 < 16) matrix2[r * col + (c + 1)] = '.';
            }
        }
    }
}

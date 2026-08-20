//Preprocessor Directives
#include <stdio.h>
#include <stdlib.h>//Required for malloc

int main() {
    // Gathering the values from the user.
    printf("Welcome! \n");
    printf("This program will develop a square matrix for you.\n");
    
    int matrixSizex, matrixSizey; // Matrix Size (X,Y)

    printf("To begin, please enter two numbers separated by commas and starting with X for the size of the Matrix:\n");
    scanf("%d,%d", &matrixSizex, &matrixSizey);

    //Memory allocation for the matrix itself, because C code won't let me have variable size for an array.
    int** spiralMatrix = (int**)malloc(matrixSizex * sizeof(int*));//Allocates memory for 2D array of pointers
   
    if (spiralMatrix == NULL) {//Error Handling - Applies if malloc breaks
        printf("Memory allocation failed.\n Terminating program....\n");
        return 1;
    }

    for (int i = 0; i < matrixSizex; ++i) {
        
        if (spiralMatrix[i] == NULL) {//Error Handling - Applies if malloc breaks
            printf("Memory allocation failed.\n Terminating program....\n");
            return 1;
        }

        spiralMatrix[i] = (int*)malloc(matrixSizey * sizeof(int));//Allocates memory for the individual rows
    }
  
    /* Spiral Creation Section:*/
    
    //Keeping track of the boundaries of the Matrix
    int top = 0, bottom = matrixSizex - 1, left = 0, right = matrixSizey - 1;

    int direction = 0; // 0: right, 1: down, 2: left, 3: up || Shifts direction when needed

    int currentValue = 1;//Ensures that the values of the matrix are in sequence.
    int maxValue = matrixSizex * matrixSizey; // Maximum value to be filled in the spiralMatrix

    while (currentValue <= maxValue) {
        if (direction == 0) {//Prints top row
            for (int i = left; i <= right; i++) {
                spiralMatrix[top][i] = currentValue;
                currentValue++;
            }
            top++;//Increment top to prevent the program from overwriting this row
        }
        else if (direction == 1) {//Prints rightside of the spiral
            for (int i = top; i <= bottom; i++) {
                spiralMatrix[i][right] = currentValue;
                currentValue++;
            }
            right--;//Decrease to prevent that column from being overwritten
        }
        else if (direction == 2) {//Prints leftside of the sprial
            for (int i = right; i >= left; i--) {
                spiralMatrix[bottom][i] = currentValue;
                currentValue++;
            }
            bottom--;//Decrease to prevent bottom row from being overwritten
        }
        else if (direction == 3) {//Prints bottom of the spiral
            for (int i = bottom; i >= top; i--) {
                spiralMatrix[i][left] = currentValue;
                currentValue++;
            }
            left++;//Increase to prevent left side being overwritten.
        }

        direction = (direction + 1) % 4;//Changes the value of Direction to change the direction of flow
    }

   //All of the above was background procedures, now to print the actual spiral to show the user...

    printf("\nSpiral Matrix:\n");

    //All of what was done in the previous bit was saved to the result array 
    //So its just a matter of printing out an array
    for (int i = 0; i < matrixSizex; i++) {
        for (int j = 0; j < matrixSizey; j++) {
            printf("%d ", spiralMatrix[i][j]);
        }
        printf("\n");
    }
    //Freeing the previously allocated memory
    free(spiralMatrix);

    return 0;
}

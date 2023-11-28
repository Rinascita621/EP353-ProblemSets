Exam

#include <stdio.h>

// function prototype
void printMatrix(int width, int height);

int main(){
    int width, height;

    // ask user for width
    printf("enter the width of the matrix:");
    scanf("%d", &width);

    // ask user for height
    printf("enter the height of the matrix:");
    scanf("%d", &height);

    //call the function
    printMatrix(width, height);

    return 0;
}

//function to print the matrix
void printMatrix(int width, int height){
    //make sure the width and height are positive
    if(width <= 0 || height <= 0){
        printf("Invalid values, please enter positive values of width and height");
        return;

    }
    //Loop for iterating row
     for(int i = 0; i < height; i++){
        //loop for iterating column
        for(int z = 0; z < width; z++){
            int value = (i + z) % 10 + 1;

            printf("%i", value);
            
            }

        }
        //create new line for next row
        printf("\n");
     }


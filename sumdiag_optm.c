// optimized versions of matrix diagonal summing
#include "matvec.h"
#include <string.h>
// You can write several different versions of your optimized function
// in this file and call one of them in the last function.

int sumdiag_VER1(matrix_t mat, vector_t vec) {
  int len = vec.len;
  int i;
  for(i = 0; i < len-3; i+=3){   //initialize all values of the sum vector to 0
    VSET(vec, i, 0);             //unrolling the loop 3 times
    VSET(vec, i+1, 0);
    VSET(vec, i+2, 0);
  }
  for(; i < len; i++){          //cleanup loop for the unrolled loop above
    VSET(vec, i, 0);
  }
  int d1, d2, d3;               //initialize values to store diagonal values
  int rows = mat.rows;          //set pointer values to integer values rather than
  int cols = mat.cols;          //needing to access them throughout the loop
  for(int x = 0; x < rows; x++){    //loop through all rows
    int y = 0;                      //needed due to loop unrolling
    for(; y < cols-3; y+=3){        //loop through all columns, unrolled 3 times
      d1 = y - x + cols - 1;        //calculate the diagonal value associated with the current location
      d2 = y - x + cols;
      d3 = y - x + cols + 1;
      VSET(vec, d1, VGET(vec, d1) + MGET(mat, x, y));   //set the value of the diagonal to its previous value + the current value in the matrix
      VSET(vec, d2, VGET(vec, d2) + MGET(mat, x, y+1));
      VSET(vec, d3, VGET(vec, d3) + MGET(mat, x, y+2));
    }
    for(; y < cols; y++){           //cleanup loop for the unrolled loop above
      d1 = y - x + cols - 1;         //calculate the diagonal value associated with the current location
      VSET(vec, d1, VGET(vec, d1) + MGET(mat, x, y)); //set the value of the diagonal to its previous value
    }
  }
  return 0;   //return success
}

int sumdiag_VER2(matrix_t mat, vector_t vec) {
  int len = vec.len;              //store values of pointers in variables in order to avoid needing to access them every time
  int rows = mat.rows;
  int cols = mat.cols;
  if(len != rows + cols - 1){     //ensure length is the currect size
    printf("Bad sizes");
    return 1;
  }
  int i;
  for(i = 0; i < len-3; i+=3){   //initialize all values of the sum vector to 0
    VSET(vec, i, 0);             //unrolled 3 times
    VSET(vec, i+1, 0);
    VSET(vec, i+2, 0);
  }
  for(; i < len; i++){          //cleanup loop for the unrolled loop above
    VSET(vec, i, 0);
  }
  int d1, d2, d3, sum1, sum2, sum3, prev1, prev2, prev3, cur1, cur2, cur3;  //initialize variable to store different diagonal, current value, and value in matrix
  for(int x = 0; x < rows; x++){    //loop through all rows
    int y = 0;                      //necessary for loop unrolling
    for(; y < cols-3; y+=3){        //loop through all columns, unrolled 3 times
      d1 = y - x + cols - 1;        //calculate the diagonal value associated with the current location
      d2 = y - x + cols;
      d3 = y - x + cols + 1;
      prev1 = VGET(vec, d1);        //fetch current sum stored in the vector at the diagonal location
      cur1 = MGET(mat, x, y);       //fetch the current value in the matrix
      sum1 = prev1 + cur1;          //add the two above variables, represents the new sum to put into the vector
      prev2 = VGET(vec, d2);
      cur2 = MGET(mat, x, y+1);
      sum2 = prev2 + cur2;
      prev3 = VGET(vec, d3);
      cur3 = MGET(mat, x, y+2);
      sum3 = prev3 + cur3;
      VSET(vec, d1, sum1);          //set the value of the diagonal to the sum calculated above
      VSET(vec, d2, sum2);
      VSET(vec, d3, sum3);
    }
    for(; y < cols; y++){  //loop through all columns
      d1 = y - x + cols - 1;         //calculate the diagonal value associated with the current location
      prev1 = VGET(vec, d1);
      cur1 = MGET(mat, x, y);
      sum1 = prev1 + cur1;
      VSET(vec, d1, sum1); //set the value of the diagonal to its previous value
    }
  }
  return 0;
}

int sumdiag_OPTM(matrix_t mat, vector_t vec) {
  //run VER1, because it is much faster
  return sumdiag_VER1(mat, vec);
}

#include <stdlib.h>
#include <stdio.h>
#include <error.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include "search.h"

int main(int argc, char *argv[]){
  if(argc <= 3){                         //terminate the program if the user does not specify sufficient data
    printf("Program terminated: too few arguments");
    return 1;
  }
  int run_linear_array = 0, run_linear_list = 0, run_binary_array = 0, run_binary_tree = 0;   //boolean values for whether or not to run each algorithm
  int min = atoi(argv[1]);                //set minimum to the second argument, converted to an integer
  int max = atoi(argv[2]);                //set maximum to the third argument, converted to an integer
  int reps = atoi(argv[3]);               //set reps to the fourth argument, converted to an integer
  if(argc == 4){                          //if there is no argument for which algorithm(s) to run, run them all
    run_linear_array = 1;
    run_linear_list = 1;
    run_binary_array = 1;
    run_binary_tree = 1;
  }
  if(argc == 5){
    char *c = argv[4];                          //if there are arguments for algorithms, set the values associated with the
    if(strchr(c, 'a') != NULL){                 //algorithms specified to 1 (so that they are ran)
      run_linear_array = 1;
    }
    if(strchr(c, 'l') != NULL){
      run_linear_list = 1;
    }
    if(strchr(c, 'b') != NULL){
      run_binary_array = 1;
    }
    if(strchr(c, 't') != NULL){
      run_binary_tree = 1;
    }
  }
  printf("%-s", "LENGTH ");                //print out "LENGTH" and "SEARCHES" in all cases
  printf("%-s   ", "SEARCHES");
  if(run_linear_array == 1){              //print labels for algorithms that are to be ran
    printf("%6s     ", "array");
  }
  if(run_linear_list == 1){
    printf("%6s     ", " list");
  }
  if(run_binary_array == 1){
    printf("%6s     ", "  binary");
  }
  if(run_binary_tree == 1){
    printf("%6s     ", "   tree");
  }
  printf("\n");
  int cur_length = 1;                     //variable to store the current value of the length being calculated
  for(int i = 0; i < min; i++){           //calculate (2^min)
    cur_length *= 2;
  }
  double timeLA = 0.0, timeLL = 0.0, timeBA = 0.0, timeBT = 0.0;   //time variables to store the times associated with each algorithm
  clock_t start_la, end_la, start_ll, end_ll, start_ba, end_ba, start_bt, end_bt;
  int num_things;                           //total number of things to be searched for, searching this many times accounts for items in the data structure and also items not in the structure
  for(int y = min; y <= max; y++){          //loop from minimum to maximum
    printf("%6d ",cur_length);              //print the length of the data structure(s) being tested
    printf("  %6d ",cur_length * reps * 2);  //print the number of searches to be done
    num_things = 2 * cur_length;
    if(run_linear_array==1){                  //run this algorithm if specified or none were specified
      int *arrLA = make_evens_array(cur_length);   //make an array of evens
      start_la = clock();                     //start the clock
      for(int i = 0; i < reps; i++){          //search the specified reps number of times
        for(int j = 0; j < num_things; j++){  //loop for every element (both in the structure and not in the structure)
          linear_array_search(arrLA, cur_length, j);    //call the search algorithm to search for the specific element (j)
        }
      }
      end_la = clock();                       //stop the clock
      timeLA = ((double) (end_la - start_la)) / CLOCKS_PER_SEC; //calculate the total time taken by the CPU
      printf("%10.4e  ", timeLA);             //print the time calculated above in scientific notation
      free(arrLA);                            //free the data structure
      timeLA = 0;                             //set time back to zero to eliminate risk of something going wrong the next time it is calculated
    }
    if(run_linear_list==1){                         //run this algorithm if specified or none were specified
      list_t *lst = make_evens_list(cur_length);    //make a list of evens
      start_ll = clock();
      for(int i = 0; i < reps; i++){
        for(int j = 0; j < num_things; j++){
          linkedlist_search(lst, cur_length, j);
        }
      }
      end_ll = clock();
      timeLL = ((double) (end_ll - start_ll)) / CLOCKS_PER_SEC;
      printf("%10.4e  ", timeLL);
      list_free(lst);
      timeLL = 0;
    }
    if(run_binary_array == 1){                       //run this algorithm if specified or none were specified
      int *arrBA = make_evens_array(cur_length);     //make an array of evens
      start_ba = clock();
      for(int i = 0; i < reps; i++){
        for(int j = 0; j < num_things; j++){
          binary_array_search(arrBA, cur_length, j);
        }
      }
      end_ba = clock();
      timeBA = ((double) (end_ba - start_ba)) / CLOCKS_PER_SEC;
      printf("%10.4e  ", timeBA);
      free(arrBA);
      timeBA = 0;
    }
    if(run_binary_tree == 1){                       //run this algorithm if specified or none were specified
      bst_t *tree = make_evens_tree(cur_length);    //make a tree of evens
      start_bt = clock();
      for(int i = 0; i < reps; i++){
        for(int j = 0; j < num_things; j++){
          binary_tree_search(tree, 0, j);
        }
      }
      end_bt = clock();
      timeBT = ((double) (end_bt - start_bt)) / CLOCKS_PER_SEC;
      printf("%10.4e  ", timeBT);
      bst_free(tree);
      timeBT = 0;
    }
    cur_length *= 2;                              //increment the length by a power of 2
    printf("\n");
  }
  return 0;       //return success
}

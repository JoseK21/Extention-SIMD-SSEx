#include <stdio.h>
#include <stdlib.h>
#include <emmintrin.h>
#include <smmintrin.h>
#include <time.h>

 // Vars
void init_array(int *array);
void init_matrix(int **matrix, int length);
void init_vectors(__m128i vector[5]);
int vector[4], column0[4], column1[4], column2[4], column3[4];
int *matrix[5] = {vector, column0, column1, column2, column3};


// # Operaciones 
int main(){
  srand(time(0));
  init_matrix(matrix, 5);
  __m128i mult_array[5];
  init_vectors(mult_array);

  __m128i mult_column_0 = _mm_mullo_epi16(mult_array[0], mult_array[1]);
  __m128i mult_column_1 = _mm_mullo_epi16(mult_array[0], mult_array[2]);
  __m128i mult_column_2 = _mm_mullo_epi16(mult_array[0], mult_array[3]);
  __m128i mult_column_3 = _mm_mullo_epi16(mult_array[0], mult_array[4]);
  __m128i mult_row_0 = _mm_set_epi32(_mm_extract_epi32(mult_column_0, 3),_mm_extract_epi32(mult_column_1, 3),_mm_extract_epi32(mult_column_2, 3),_mm_extract_epi32(mult_column_3, 3));
  __m128i mult_row_1 = _mm_set_epi32(_mm_extract_epi32(mult_column_0, 2),_mm_extract_epi32(mult_column_1, 2),_mm_extract_epi32(mult_column_2, 2),_mm_extract_epi32(mult_column_3, 2));
  __m128i mult_row_2 = _mm_set_epi32(_mm_extract_epi32(mult_column_0, 1),_mm_extract_epi32(mult_column_1, 1),_mm_extract_epi32(mult_column_2, 1),_mm_extract_epi32(mult_column_3, 1));
  __m128i mult_row_3 = _mm_set_epi32(_mm_extract_epi32(mult_column_0, 0),_mm_extract_epi32(mult_column_1, 0),_mm_extract_epi32(mult_column_2, 0),_mm_extract_epi32(mult_column_3, 0));
  __m128i result_temp_1, result_temp_2, result;
  result_temp_1 = _mm_add_epi32(mult_row_0, mult_row_1);
  result_temp_2 = _mm_add_epi32(mult_row_2, mult_row_3);
  result = _mm_add_epi32(result_temp_1, result_temp_2);




  //############################################################################################

  printf("Vector:\n");
  printf("[");
  for (int i = 0; i < 4; i++){
    printf("%5d", matrix[0][i]);
  }
  printf("\t]");
  
  printf("\n");
  printf("Matriz:\n");

  for (int i = 0; i < 4; i++){
    printf("[");
    for (int j = 1; j < 5; j++){
      printf("%5d", matrix[j][i]);
    }
    printf("\t]");
    printf("\n");
  }

  //############################################################################################
  printf("\n");
  printf("Resultados:\n");
  printf("[");
  int data = 0;
  data = _mm_extract_epi32(result, 3);
  printf("%d \t", data);
  data = _mm_extract_epi32(result, 2);
  printf("%d \t", data);
  data = _mm_extract_epi32(result, 1);
  printf("%d \t", data);
  data = _mm_extract_epi32(result, 0);
  printf("%d", data);
  printf("]");
  printf("\n");
  printf("\n");
  return 0;
}

//------------------------------------Utils----------------------------------------------------
void init_array(int *array){
  for (int i = 0; i < 4; i++){
    array[i] = (rand() % 10) + 1;
  }
}


void init_vectors(__m128i vector[5]){
  for (int i = 0; i < 5; i++){
    vector[i] = _mm_set_epi32(matrix[i][0], matrix[i][1], matrix[i][2], matrix[i][3]); 
  }
}


void init_matrix(int **matrix, int length){
  for (int i = 0; i < length; ++i){
    init_array(matrix[i]); 
  }
}

//---------------------------------------------------------------------------------------------
#include <stdio.h>
#include <emmintrin.h>
#include <smmintrin.h>

void printMatrix(__m128i row[]){
  printf("\n\t  \033[0;34mMatrix\033[0m\n");
  int data = 0;
  for (int y = 0; y < 3; y++)
  {
    data = _mm_extract_epi32(row[y], 0);
    printf("%d\t", data);

    data = _mm_extract_epi32(row[y], 1);
    printf("%d\t", data);

    data = _mm_extract_epi32(row[y], 2);
    printf("%d\t", data);

    data = _mm_extract_epi32(row[y], 3);
    printf("%d\t\n", data);
  }
}

void printResults(__m128i maxRow){
  printf("\n\t  \033[0;34mResultador\033[0m\n");
  int data = 0;
  data = _mm_extract_epi32(maxRow, 0);
  printf("Column 1 > Max: %d \n", data);

  data = _mm_extract_epi32(maxRow, 1);
  printf("Column 2 > Max: %d \n", data);

  data = _mm_extract_epi32(maxRow, 2);
  printf("Column 3 > Max: %d \n", data);

  data = _mm_extract_epi32(maxRow, 3);
  printf("Column 4 > Max: %d \n", data);
  printf("\n");
}

int main(int argc, char *argv[])
{
  if (argc != 13)
  {
    printf("\033[1;31mInvalid input parameters, 12 positive numbers must be provided.\033[0m\n");
    return 0;
  }

  int data = 0;
  __m128i rows[3];

  rows[0] = _mm_set_epi32(atoi(argv[4]), atoi(argv[3]), atoi(argv[2]), atoi(argv[1]));
  rows[1] = _mm_set_epi32(atoi(argv[8]), atoi(argv[7]), atoi(argv[6]), atoi(argv[5]));
  rows[2] = _mm_set_epi32(atoi(argv[12]), atoi(argv[11]), atoi(argv[10]), atoi(argv[9]));

  printMatrix(rows);

  __m128i maxTempRow = _mm_max_epi32(rows[0], rows[1]);
  __m128i maxRow = _mm_max_epi32(maxTempRow, rows[2]);

  printResults(maxRow);

  return 0;
}

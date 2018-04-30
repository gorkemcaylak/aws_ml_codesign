/*===============================================================*/
/*                                                               */
/*                       check_result.cpp                        */
/*                                                               */
/*      Software evaluation of training and test error rate      */
/*                                                               */
/*===============================================================*/

#include <cstdio>
#include "typedefs.h"

void check_results(bit4_t * result, const bit4_t * expected, int cnt)
{
  int correct_cnt = 0;

  for (int i = 0; i < cnt; i ++ )
  {
    if (result[i] != expected[i])
      printf("Test %d: expected = %d, result = %d\n", i, expected[i], result[i]);
    else
      correct_cnt ++;
  }

  printf("\n\t %d / %d correct!\n", correct_cnt, cnt);  

}

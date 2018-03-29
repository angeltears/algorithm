/*
希尔排序的核心思想是不断生成间隔h的有序数组，本算法使用的是递增性数组
生成递增数组用的是直插排序的思想，寻找元素适合的位置。
特点：1.权衡了子数组的规模和有序性，使得插入排序排序的数组接近有序，从而使插入排序的性能得到体现
     2.希尔排序适合对大数组的排序，并且数组越大，优势越大
算法复杂度
    1.希尔排序的时间复杂度为O(n^3/2)，希尔排序时间复杂度的下界是n*log2n（仅仅一个小小优化降低了n^1/2令人佩服～)
    2.空间复杂度为O（1）1
*/
#include <iostream>
#include "basic_algo.h"
using std::cout;
using std::cin;
using std::endl;

void shell(int list[], int length)
{
    int h = 1;
    while (h < length / 3)
    {
      h = h * 3 + 1;
    }
    while (h >= 1)
    {
        for (int i = h; i < length; i++)
        {
            for (int j = i; j >= h && less<int>()(list[j], list[j-h]);j -= h)
            {
              exch<int>()(list, j, j - h);
            }
        }
        h = h / 3;
    }
}

int main()
{
  int a[5];
  for (int i = 0; i < 5; i++)
    cin >> a[i];
  shell(a, 5);
  show<int>()(a, 5);
  return 0;
}

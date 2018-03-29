/*
插入排序的核心思想在于寻找一个合适的位置，并把相应的元素插入进去。
特点：1.时间复杂度与插入顺序有关，当数组有序（接近有序）算法复杂度将远远低于随机数组
     2.比较次数 = 交换次数 + 额外项（此项为N减去已知最小元素次数，如最坏情况倒序数组为N - 1）
算法复杂度：
      平均情况需要 N^2/4 比较和交换，最坏则需要N^2/2 次交换和比较，最好情况是N -1 次比较不需要交换。
      时间复杂度：最佳O（N）其他情况为O（N^2)
      空间复杂度： O（1）
*/
#include <iostream>
#include "basic_algo.h"
using std::cout;
using std::cin;
using std::endl;

 void insert(int list[], int length)
 {
    for (int i = 1; i < length; i++)
    {
      for (int j = i; j > 0 && less<int>()(list[j],list[j-1]); j--)
      {
        exch<int>()(list, j, j - 1);
      }
    }
 }
int main()
{
  int a[5];
  for (int i = 0; i < 5; i++)
    cin >> a[i];
  insert(a, 5);
  show<int>()(a, 5);
  return 0;
}

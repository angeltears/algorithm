/*
选择排序算法的核心思想在于不断寻找剩余数组中最下的元素，然后与首位元素进行交换。
特点：1.运行时间和初始顺序的无关
     2.交换次数至多为N次
算法复杂度：
    空间可以实现O(1)
    时间复杂度：需要比较次数为N(N-1)/2次，交换N次，所以时间复杂度为O(N^2)
*/
#include <iostream>
#include "basic_algo.h"
using std::cout;
using std::cin;
using std::endl;


void select(int list[],int length)
{
    for (int i = 0; i < length; i++)
    {
        int min = i;
        for (int j = i + 1; j < length; j++)
        {
            if (less<int>()(list[j],list[min]))
            {
              min = j;
            }
        }
        exch<int>()(list, i, min);
    }
}
int main()
{
  int a[5];
  for (int i = 0; i < 5; i++)
    cin >> a[i];
  select(a, 5);
  show<int>()(a, 5);
  return 0;
}

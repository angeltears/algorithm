/*
堆排序是利用堆这种数据结构而设计的一种排序算法，堆排序是一种选择排序。
堆是具有以下性质的完全二叉树：每个结点的值都大于或等于其左右孩子结点的值，称为大顶堆或者每个结点
的值都小于或等于其左右孩子结点的值，称为小顶堆。而堆排序是基于前者大顶堆
特点：1.它的最坏，最好，平均时间复杂度均为O(nlogn)，它也是不稳定排序
算法复杂度：
      1.时间复杂度为O（nlogn)
      2.空间复杂度 O（1）
*/


#include <iostream>
#include "basic_algo.h"
using std::cout;
using std::cin;
using std::endl;


/*
二叉树的性质：第N个节点的孩子节点为 2 * N + 1 OR  2 * N + 2
*/
void sink(int list[], int length, int k)
{
  while(2 * k <= length)
  {
    int j = 2 * k;
    if (j < length && less<int>()(list[j], list[j+1]))
      j++;
    if(!less<int>()(list[k], list[j]))
      break;
    exch<int>()(list,k, j);
    k = j;
  }
}

void heapsort(int list[], int length)
{
    for(int k = length / 2; k >= 1; k--)
    {
      sink(list, length, k);
    }
    while (length >= 1)
    {
      exch<int>()(list, 1, length--);
      sink(list, length, 1);
    }
}

int main()
{
  int a[6];
  for (int i = 1; i < 6; i++)
    cin >> a[i];
  heapsort(a, 5);
  show<int>()(a + 1, 5);
  return 0;
}

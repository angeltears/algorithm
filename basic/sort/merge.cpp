/*
归并排序的核心思想类似与分治策略，通过不断分治，将数组不断缩小，直到1， 合并生成2的有序数组，在
继续向上生成合并，直到生成有序数组；
本程序采用和自顶向下的方法，不断产生子数组，依靠子数组的有序，进行合并。并且将合并的实现提取出来
防止由于大数组导致递归的失败的问题；
特点：1.采用分而治之的思想，将问题规模不断缩小。
     2.在空间复杂度上，与N成正比。
算法复杂度
    1.时间复杂度为O(n log(n))，在merge中会产生一个递归树，由树的性质可知第K层，一共有2^k的
    叶子节点，并且每个叶子节点的长度为2^（n -k）所以每层需要比较2^n，又因为树高为n，所以一共
    需要比较2^n*n次 = nlgn;
    2.空间复杂度为数组的长度O（N）
*/

#include <iostream>
#include "basic_algo.h"
using std::cout;
using std::cin;
using std::endl;


void merge_aux(int list[], int lo, int middle, int hi)
{
  int a[hi - lo];
  for (int k = lo; k <= hi; k++)
  {
    a[k] = list[k];
  }
  int i = lo;
  int j = middle + 1;
  for (int k = lo; k <= hi; k++)
  {
    if (i > middle)
        list[k] = a[j++];
    else if (j > hi)
        list[k] = a[i++];
    else if (less<int>()(a[j], a[i]))
        list[k] = a[j++];
    else
        list[k] = a[i++];
  }
}

void merge(int list[], int lo, int hi)
{
  if (hi <= lo)
    return;
  int mid = (lo + hi) / 2;
  merge(list, lo, mid);
  merge(list, mid + 1, hi);
  merge_aux(list, lo, mid, hi);
}
int main()
{
  int a[6];
  for (int i = 0; i < 6; i++)
    cin >> a[i];
  merge(a, 0, 5);
  show<int>()(a, 6);
  return 0;
}

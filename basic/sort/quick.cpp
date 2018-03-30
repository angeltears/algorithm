/*
快速排序的核心思想类似与归并排序，都是采用分治策略，但是归并是有序子序列的生成有序序列,而快速排序
采用切分，将数组不断进行切分，切分的数组生成有序的序列的时，整个序列也就有序了。切分的思想在于从
数组两端不断迭代，找到一个监视站正好可以将其分成两个数组的部分并交换。
特点：1.时间复杂度和空间复杂度都较低，是一个性能良好的算法，可以继续优化（三切分等）！
     2.有一个很大缺点，就是切分不均衡问题，解决方法随机打乱排列！
算法复杂度：
     1.时间复杂度：（证明太复杂 汗！）
     假定Cn为n个元素所需要排序的比较次数
     Cn = 1 + n + (Cn-1 + Cn-2 + .... + C0) * 2 / n; 前面为切分的成本，后面为左右子序列成本；
     nCn = n(n + 1) + 2 (C0+ ... + Cn - 1);0,
     同时减去n - 1
     nCn - (n - 1)Cn-1 = 2n + 2Cn - 1   //没看懂
     同时除以n + 1
     Cn/(n + 1) = Cn-1/ n + 2 / (n + 1)
     所以 Cn  ～ 2（n + 1)(1 / 3+ 1 / 4 + ....+  1 / (n+1))
     Cn ~ 2nln(n) ~ 1.39nlgn
     2.空间复杂度 o(lgn) ~ o(n)   //切分n - 1
*/
#include <iostream>
#include "basic_algo.h"
using std::cout;
using std::cin;
using std::endl;

int partition(int list[], int lo, int hi)
{
  int i = lo;
  int j = hi + 1;
  int v = list[i];
  while (1)
  {
    while (less<int>()(list[++i], v))
        if (i == hi)
            break;
    while (less<int>()(v,list[--j]))
        if (j == lo)
          break;
    if (i >= j)
      break;
    exch<int>()(list, i, j);
  }
  exch<int>()(list, lo, j);
  return j;
}

int partition2(int list[], int lo, int hi)   //nomoral aux
{
    int i = lo;
    int j = hi + 1;
    int v = list[i];
    while(i < j)
    {
      while (i < j && less<int>()(v,list[j]))
      {
          --j;
      }
      list[i] = list[j];
      while (i < j && less<int>()(list[i], v))
      {
          ++i;
      }
      list[j] = list[i];
    }
    list[i] = v;
    return i;
}

void quick(int list[], int lo, int hi)
{
  if (hi < lo)
      return;
  int j = partition2(list, lo, hi);
  quick(list, j+1, hi);
  quick(list, lo, j-1);
}

int main()
{
  int a[6];
  for (int i = 0; i < 6; i++)
    cin >> a[i];
  quick(a, 0, 5);
  show<int>()(a, 6);
  return 0;
}

/*
这里一些代码，作为公共代码，部分c++algorithm中已经存在
但是还是已仿函数的形式实现了，也算是对寒假看的STL用点皮毛
*/
#include <iostream>
using std::cout;
using std::endl;
 template<class T>
 class less
 {
 public:
   bool operator()(T &a, T &b)
   {
     if (a < b)
        return true;
     else
        return false;
   }
 };

 template<class T>
 class exch
 {
 public:
   void operator()(T a[], int i, int j)
   {
      T t = a[i];
      a[i] =  a[j];
      a[j] = t;
   }
 };


template<class T>
class show
{
public:
  void operator()(T a[], int length)
  {
    for (int i = 0; i < length; i++)
    {
      cout << a[i]<< " ";
    }
    cout << endl;
  }
};

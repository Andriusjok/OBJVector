#include "Vector.h"
#include "timer.h"
#include <iostream>
#include <vector>
#include <chrono>
using std::cout;
using std::endl;
int main()
{
	
	
	Timer t;// Pradėti v1 užpildymo laiko matavimą
unsigned int sz = 100000000;  // 100000, 1000000, 10000000, 100000000
std::vector<int> v1;
for (int i = 1; i <= sz; ++i)
  v1.push_back(i);
cout << "stdvector " <<t.elapsed() << endl;
// Baigti v1 užpildymo laiko matavimą

// Pradėti v2 užpildymo laiko matavimą
Timer t2;
Vector<int> v2;
for (int i = 1; i <= sz; ++i)
  v2.push_back(i);
	cout << "vector " << t2.elapsed() << " s" << endl;
}
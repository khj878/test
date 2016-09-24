#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

int N;

int main()
{
	cin >> N;
	if (N % 2 == 0)
		cout << "YES";
	else
		cout << "NO";
	return 0;
}
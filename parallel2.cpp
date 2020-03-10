#include <iostream>
#include <cstdlib>
#include <omp.h>
#include <ctime>
#define N 100000000
using namespace std;
int main()
{
	int* mass = new int[N];
	for (int i = 0; i < N; i++)
	{
		mass[i] = rand() % 100;
		//cout<<mass[i]<<" ";
	}
	cout << endl;
	unsigned t1 = clock();
	int max;
	int m1 = mass[0];
	int m2 = mass[N / 4];
	int m3 = mass[N / 2];
	int m4 = mass[3 * N / 4];
#pragma omp parallel
	{
		
#pragma omp sections
		{
#pragma omp section
			{
				for (int i = 1; i < N / 4; i++)
					if (m1 < mass[i])
						m1 = mass[i];
			}
#pragma omp section
			{
				for (int i = N / 4 + 1; i < N / 2; i++)
					if (m2 < mass[i])
						m2 = mass[i];
			}
#pragma omp section
			{
				for (int i = N / 2 + 1; i < 3 * N / 4; i++)
					if (m3 < mass[i])
						m3 = mass[i];
			}
#pragma omp section
			{
				for (int i = 3 * N / 4 + 1; i < N; i++)
					if (m4 < mass[i])
						m4 = mass[i];
			}
		}
		
	}
	//cout << m1 << " " << m2 << " " << m3 << " " << m4 << endl;
		if (m4 >= m1 && m4 >= m2 && m4 >= m3)
			max = m4;
		if (m3 >= m1 && m3 >= m2 && m3 >= m4)
			max = m3;
	    if (m2 >= m1 && m2 >=m4 && m2 >= m3)
			max = m2;
		if (m1 >= m4 && m1 >= m2 && m1 >= m3)
			max = m1;

	cout << max << endl;
	unsigned t2 = clock();
	cout <<"parallel " << t2 - t1 << endl;
	unsigned t3 = clock();

	for (int i = 1; i < N; i++)
		if (max < mass[i])
			max = mass[i];

	cout << max << endl;
	unsigned t4 = clock();
	cout << "simple " << t4 - t3 << endl;

}
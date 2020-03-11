#include <iostream>
#include <cstdlib>
#include <omp.h>
#include <ctime>

using namespace std;

#define N 10000
#define M 10000

int* multipl1(int** a, int* v, int n, int m)
{
    int i, j;
    int g = 0;
    int* v1 = new int[n];
    
    for (i = 0; i < n; i++)
    {
        g = 0;
        for (j = 0; j < m; j++)
            g += a[i][j]*v[j];
        v1[i] = g;
    }
    return v1;
}
int* multipl2(int** a, int* v, int n, int m)
{
    int i, j;
    int g = 0;
    int* v1 = new int[n];
    #pragma omp parallel sections
    {
        #pragma omp section
        for (i = 0; i < n/3; i++)
        {
            g = 0;
            #pragma omp parallel for
            for (j = 0; j < m; j++)
                g += a[i][j] * v[j];
            v1[i] = g;
        }
        #pragma omp section
        for (i = n/3+1; i < 2*n/3; i++)
        {
            g = 0;
            #pragma omp parallel for
            for (j = 0; j < m; j++)
                g += a[i][j] * v[j];
            v1[i] = g;
        }
        #pragma omp section
        for (i = 2*n/3+1; i < n; i++)
        {
            g = 0;
            #pragma omp parallel for
            for (j = 0; j < m; j++)
                g += a[i][j] * v[j];
            v1[i] = g;
        }
    }
    return v1;
}
/*int* multipl2(int** a, int* v, int n, int m)
{
    int i, j;
    int g = 0;
    int* v1 = new int[n];
    for (i = 0; i < n; i++)
    {
        g = 0;
      #pragma omp parallel sections
        {
        #pragma omp section
            {
                for (j = 0; j < m / 3; j++)
                    g += a[i][j] * v[j];
                v1[i] = g;
            }
        #pragma omp section
            {
                for (j = m/3+1; j < 2*m/3; j++)
                    g += a[i][j] * v[j];
                v1[i] = g;
            }
        #pragma omp section
            {
                for (j = 2*m/3+1; j < m; j++)
                    g += a[i][j] * v[j];
                v1[i] = g;
            }
        }
    }
    return v1;
}*/
void printmas(int** a, int n, int m)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
            cout << a[i][j] << " ";
        cout << endl;
    }
}
void printvec(int* v, int m)
{
    int i;
    for (i = 0; i < m; i++)
        cout << v[i] << endl;
}
void zapvector(int* v, int m)
{
    int i;
    for (i = 0; i < m; i++)
        v[i] = rand() % 3;
}
void zapmatrix(int** a, int n, int m)
{
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            a[i][j] = rand() % 3;
}
int main()
{
    int i, j;
    int** a = new int*[N];
    int* v = new int[M];
    int* v1 = new int[N];
    for (i = 0; i < N; i++)
        a[i] = new int[M];
    zapvector(v,M);
    //printvec(v, M); cout << endl;
    zapmatrix(a, N, M);
    unsigned int t1 = clock();
    v1=multipl1(a, v, N, M);
    unsigned int t2 = clock();
    cout << "Vremya normal " << t2 - t1 << endl;

    unsigned int t3 = clock();
    v1 = multipl2(a, v, N, M);
    unsigned int t4 = clock();
    cout << "Vremya parall " << t4 - t3 << endl;
    //printmas(a, N, M);
    cout << endl;
    //printvec(v1, N);

    delete[] a;
    for (i = 0; i < M; i++)
        delete[] a[i];
    delete[] v;
}



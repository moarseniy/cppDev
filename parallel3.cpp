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
            g += a[i][j] * v[j];
        v1[i] = g;
    }
    return v1;
}
int* multipl2(int** a, int* v, int n, int m)
{
    int i, j;
    int* v1 = new int[n];
    omp_set_num_threads(omp_get_num_procs());
    #pragma omp parallel for shared(a,v,v1) private(i, j)
    for (i = 0; i < n; i++)
    {
        v1[i] = 0;
        for (j = 0; j < m; j++)
           v1[i] += a[i][j] * v[j];
    }
    return v1;
}
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
    unsigned t1, t2,t3,t4;
    int** a = new int* [N];
    int* v = new int[M];
    int* v1 = new int[N];
    int* v2 = new int[N];
    for (i = 0; i < N; i++)
        a[i] = new int[M];

    zapvector(v, M);
    //printvec(v, M); cout << endl;
    zapmatrix(a, N, M);
    //printmas(a, N, M);

    t1 = clock();
    v1=multipl1(a, v, N, M);
    t2 = clock();
    cout << "norm vremya " << t2 - t1 << endl;

    //printvec(v1, N);
    cout << endl;

    t3 = clock();
    v2 = multipl2(a, v, N, M);
    t4 = clock();
    cout << "parall vremya " << t4 - t3 << endl;

    //printvec(v1, N);

    for (i = 0; i < M; i++)
        delete[] a[i];
    delete[] a;
    delete[] v;
    delete[] v1;
    return 0;
}

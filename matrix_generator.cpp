

#include <iostream>
#include <fstream>
using namespace std;
int main()
{
    ofstream fout;
    fout.open("matrix.csv");

    int i, j, n, m, k=10, p=17;
    cout << "N= ";
    cin >> n;
    cout << "M= ";
    cin >> m;

    int** a = new int* [n];
    for (i = 0; i < n; i++)
        a[i] = new int[m];

    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            a[i][j] = 0;

    for (i = 0; i < n; i=i+rand()%k)
        for (j = 0; j < m; j=j+rand()%p)
            a[i][j] = rand()%9;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            if (j != 0)
                fout << " ";
            fout << a[i][j];
        }
        fout << "\n";
    }
    fout.close();
    return 0;
    
}


//
//  main.cpp
//  cs33hw3
//
//  Created by Maeneka Grewal on 5/24/18.
//  Copyright © 2018 Maeneka Grewal. All rights reserved.
//

#include <iostream>
using namespace std;

void transpose(int *dst, int *src, int dim)
{
    const int BLOCK = 8;
    int i, j;
    int n, m;

    for (i = 0; i < dim; i += BLOCK)
    {
        for (j = 0; j < dim; j += BLOCK)
        {
            for (n = i; (n < dim && n < (i+BLOCK)); n++)
            {
                for (m = j; (m < dim && m < (j+BLOCK)); m++)
                    dst[m*dim + n] = src[n*dim + m];
            }
        }
    }
}

int main()
{
    int a[2][2] = {{4, 5},
                   {7, 8}};
    int b[2][2];
    transpose(*b, *a, 2);

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
            cout << b[i][j] << " ";
        cout << endl;
    }
}



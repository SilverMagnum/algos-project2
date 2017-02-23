#include "otherfuncs.h"

int align(const string &a, const string &b, int alpha_gap,
        int alpha[alphabets][alphabets], string &a_aligned,
        string &b_aligned)
{
    size_t n = a.size();
    size_t m = b.size();

    vector<vector<int> > A(n + 1, vector<int>(m + 1));

    for (size_t i = 0; i <= m; ++i)
        A[0][i] = alpha_gap * i;
    for (size_t i = 0; i <= n; ++i)
        A[i][0] = alpha_gap * i;

    for (size_t i = 1; i <= n; ++i)
    {
        for (size_t j = 1; j <= m; ++j)
        {
            char x_i = a[i-1];
            char y_j = b[j-1];
            A[i][j] = min(A[i-1][j-1] + alpha[x_i - 'A'][y_j - 'A'],
                          A[i-1][j] + alpha_gap,
                          A[i][j-1] + alpha_gap);
        }
    }

    // print2DVector(A);

    a_aligned = "";
    b_aligned = "";
    size_t j = m;
    size_t i = n;
    for (; i >= 1 && j >= 1; --i)
    {
        char x_i = a[i-1];
        char y_j = b[j-1];
        if (A[i][j] == A[i-1][j-1] + alpha[x_i - 'A'][y_j - 'A'])
        {
            /*
             * I think prepending chars this way to a std::string is very inefficient.
             * Is there any better way of doing this without using C-style strings?
             */
            a_aligned = x_i + a_aligned;
            b_aligned = y_j + b_aligned;
            --j;
        }
        else if (A[i][j] == A[i-1][j] + alpha_gap)
        {
            a_aligned = x_i + a_aligned;
            b_aligned = '-' + b_aligned;
        }
        else
        {
            a_aligned = '-' + a_aligned;
            b_aligned = y_j + b_aligned;
            --j;
        }
    }

    while (i >= 1 && j < 1)
    {
        a_aligned = a[i-1] + a_aligned;
        b_aligned = '-' + b_aligned;
        --i;
    }
    while (j >= 1 && i < 1)
    {
        a_aligned = '-' + a_aligned;
        b_aligned = b[j-1] + b_aligned;
        --j;
    }

    return A[n][m];
}


int min(int a, int b, int c)
{
    if (a <= b && a <= c)
        return a;
    else if (b <= a && b <= c)
        return b;
    else
        return c;
}


void print2DVector(const vector<vector<int> > &A)
{
    for (auto i : A)
    {
        for (auto j : i)
            cout << j << " ";
        cout << endl;
    }
}

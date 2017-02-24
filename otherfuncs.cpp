#include "otherfuncs.h"

int align(const string &a, const string &b, int alpha_gap,
		  int alpha[matrix_size][matrix_size], string &a_aligned,
		  string &b_aligned, int weights[matrix_size][matrix_size]) {

	int n = a.size();
    int m = b.size();

	//2D Vector of (n + 1) * (m + 1)
    vector<vector<int> > A(n + 1, vector<int>(m + 1));

	
	//Set the top edge to progressively higher values.
    for (int i = 0; i <= m; ++i) {
        A[0][i] = alpha_gap * i;
    }
	
	//Set the left edge to progressively higher values.
    for (int i = 0; i <= n; ++i) {
        A[i][0] = alpha_gap * i;
    }
	
	//This is done above so that we're sloped towards 0,0

	//Rewritten to not use characters.
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			A[i][j] = min(	A[i-1][j-1] + arr[x][y],	//
							A[i-1][j] + arr[0][y],		//
							A[i][j-1] + arr[x][0]);		//
		}
	}
	
		//  int arr[5][5] = {
	//	 -  A  T  G  C	
    //  {0, 1, 2, 1, 3},//-
    //  {1, 0, 1, 5, 1},//A
    //  {2, 1, 0, 9, 1},//T
    //  {1, 5, 9, 0, 1},//G
    //  {3, 1, 1, 1, 0}	//C
    //};
	
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            char x_i = a[i-1]; //ith x coordinate
            char y_j = b[j-1]; //jth y coordinate
            //int gap_pen = gapWeight(weights, x_i, y_j);
            //cout << "The gap_pen for char " << x_i << " and " << y_j << " is: " << gap_pen << endl;
            A[i][j] = min(A[i-1][j-1] + alpha[x_i - 'A'][y_j - 'A'],
                          A[i-1][j] + alpha_gap,
                          A[i][j-1] + alpha_gap);
        }
    }
	
	//My version, without copying their spacing included...
	int j = m;
    int i = n;
    for (; i >= 1 && j >= 1; --i) {
        if (contour[i-1][j-1] + alpha[inputOne[i-1]][inputTwo[j-1]])  {
            outputOne[] = inputOne[];
            outputTwo[] = inputTwo[];
            --j;
        }
        else if (contour[i-1][j] + alpha[0][inputTwo[j-1]]) {
            outputOne[] = inputOne[];
            outputTwo[] = 0;
        }
        else {
            outputOne[] = 0;
            outputTwo[] = inputTwo[];
            --j;
        }
    }
	
	//Their version
    a_aligned = "";
    b_aligned = "";
    int j = m;
    int i = n;
    for (; i >= 1 && j >= 1; --i) {
        char x_i = a[i-1];
        char y_j = b[j-1];
        if (A[i][j] == A[i-1][j-1] + /*alpha*/weights[x_i - 'A'][y_j - 'A'])  {
            a_aligned = x_i + a_aligned;
            b_aligned = y_j + b_aligned;
            --j;
        }
        else if (A[i][j] == A[i-1][j] + alpha_gap) {
            a_aligned = x_i + a_aligned;
            b_aligned = '-' + b_aligned;
        }
        else {
            a_aligned = '-' + a_aligned;
            b_aligned = y_j + b_aligned;
            --j;
        }
    }

    while (i >= 1 && j < 1) {
        a_aligned = a[i-1] + a_aligned;
        b_aligned = '-' + b_aligned;
        --i;
    }
    while (j >= 1 && i < 1) {
        a_aligned = '-' + a_aligned;
        b_aligned = b[j-1] + b_aligned;
        --j;
    }

    return A[n][m];
}

int min(int a, int b, int c) {
    if (a <= b && a <= c) {
        return a;
    }
    else if (b <= a && b <= c) {
        return b;
    }
    else {
        return c;
    }
}

void printVector(const vector<vector<int> > &A) {
    for (const auto &i : A) {
        for (auto &j : i) {
            cout << j << " ";
        }
        cout << endl;
    }
}

int gapWeight(int weights[matrix_size][matrix_size], char c1, char c2) {
    int return_weight = 0;
	int positionOne = 0, positionTwo = 0;
	
	if(c1 == '-') {
		positionOne = 0;
	}
	
	else if(c1 == 'A') {
		positionOne = 1;
	}
	
	else if(c1 == 'T') {
		positionOne = 2;
	}	
	
	else if(c1 == 'G') {
		positionOne = 3;
	}
	
	else if(c1 == 'C') {
		positionOne = 4;
	}

	
	if(c2 == '-') {
		positionTwo = 0;
	}
	
	else if(c2 == 'A') {
		positionTwo = 1;
	}
	
	else if(c2 == 'T') {
		positionTwo = 2;
	}	
	
	else if(c1 == 'G') {
		positionTwo = 3;
	}
	
	else if(c1 == 'C') {
		positionTwo = 4;
	}
	
	return_weight = weights[positionOne][positionTwo];
	
	/*

    if (c1 == '-' && c2 == 'A') {
        return_weight = weights[0][1];
    }
    else if (c1 == '-' && c2 == 'T') {
        return_weight = weights[0][2];
    }
    else if (c1 == '-' && c2 == 'G') {
        return_weight = weights[0][3];
    }
    else if (c1 == '-' && c2 == 'C') {
        return_weight = weights[0][4];
    }
	
	
    else if (c1 == 'A' && c2 == '-') {
        return_weight = weights[1][0];
    }
    else if (c1 == 'T' && c2 == '-') {
        return_weight = weights[2][0];
    }
    else if (c1 == 'G' && c2 == '-') {
        return_weight = weights[3][0];
    }
    else if (c1 == 'C' && c2 == '-') {
        return_weight = weights[4][0];
    }
	
	else if (c1 == '-' && c2 == '-') {
        return_weight = weights[0][0];
    }
	
	else if (c1 == 'A' && c2 == 'T') {
        return_weight = weights[2][1];
    }
	else if (c1 == 'A' && c2 == 'G') {
        return_weight = weights[3][1];
    }
	else if (c1 == 'A' && c2 == 'C') {
        return_weight = weights[4][1];
    }
	
	else if (c1 == 'T' && c2 == 'A') {
        return_weight = weights[1][2];
    }
	else if (c1 == 'G' && c2 == 'A') {
        return_weight = weights[1][3];
    }
	else if (c1 == 'C' && c2 == 'A') {
        return_weight = weights[1][4];
    }
	
	else if (c1 == 'A' && c2 == 'A') {
        return_weight = weights[1][1];
    }
	
	*/
	
	//	 -  A  T  G  C	
	//	{0, 1, 2, 1, 3},	//-
    //	{1, 0, 1, 5, 1},	//A
    //	{2, 1, 0, 9, 1},	//T
    //	{1, 5, 9, 0, 1},	//G
	//  {3, 1, 1, 1, 0}		//C
    //};

    return return_weight;
}

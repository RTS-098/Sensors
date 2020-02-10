#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include<math.h>
using namespace std;
 
void readfromstr(string text, int *A)
{
    //[0]x,[1]y,[2]data,[3]check

    int i = 0;
    int n = 0;
    while (text[i] != NULL) {
        string numconv = "";
        while (text[i] != ',' && text[i]!= NULL) {
            numconv = numconv + text[i];

            i++;
        }
        if (text[i]==',')
        {
            i++;
        }
        
        int num = 0;
        int x = 0;
        while (numconv[x] != NULL)
        {
            num = num * 10 + (numconv[x] - 48);
            x++;
        }
        A[n] = num;
        n++;
    }
}

int countrows(string filename)
{
    int count = 0;
    string line;
    ifstream file;
    file.open(filename);
    while (file >> line)
        count++;
    file.close();
    return count;

}

bool check(int **A,int rows,int numcheck)
{
    for (size_t i = 0; i < rows; i++)
    {
        if (A[i][3] == numcheck)
            return true;
    }
    
    return false;
}

bool checkdistance(int distance, int x1, int x2, int y1, int y2)
{
    if (distance<=sqrt(pow(fabs(x1-x2),2)+ pow(fabs(y1 - y2), 2)))
    {
        return true;
    }
    return false;
}

void coutbroken(int **A,int rows)
{
    cout << "Please check sensors at: ";
    for (size_t i = 0; i < rows; i++)
    {
        if (A[i][3]==2)
        {
            cout << "(" << A[i][0] << "," << A[i][1] << ")"<<" ";
        }

    }

}


int main()
{
    string x;
    string filename;
    int distance;
    int maxerror;
    cout << "Filename: ";
    cin >> filename;
    cout << "Neighbours distance: ";
    cin >> distance;
    cout << "Max error: ";
    cin >> maxerror;
    int rows = countrows(filename);
    int **A = new int*[rows];
    ifstream inFile;
    inFile.open(filename);
    for (int i = 0; i <= rows; i++)
    {
        getline(inFile, x);
        A[i] = new int[4];
        int B[4];
        readfromstr(x, B);
        for (int m = 0; m < 3; m++)
        {
            A[i][m] = B[m];

        }
        A[i][3] = 0;
    }
    inFile.close();
    int current = 0;
    while (check(A, rows,0) && current<=rows)
    {        
        if (A[current][3] == 0)
        {
            for (size_t i = 0; i < rows; i++)
            {
                
                if (i != current && checkdistance(distance, A[current][0], A[i][0], A[current][1], A[i][1]))
                {
                    //there isnt a possibility of a sensor showing 0 in a city
                    if (A[i][2]==0)
                    {
                        A[i][3] = 2;
                    }
                    else if (A[current][2] == 0)
                    {
                        A[current][3] == 2;
                    }
                    
                    else {
                        //if theres data
                        if (A[i][3] == 1)
                        {
                            if (fabs(A[i][2] - A[current][2]) > maxerror) {
                                A[current][3] = 2;
                            }
                            else A[current][3] = 1;
                        }
                        if (A[i][3] == 2)
                        {
                            if (fabs(A[i][2] - A[current][2]) > maxerror) {
                                A[current][3] = 1;
                            }
                            
                        }
                        //if theres no data 
                        if (A[i][3] == 0)
                        {
                            if (fabs(A[i][2] - A[current][2]) <= maxerror)
                            {
                                A[i][3] = 1;
                                A[current][3] = 1;
                            }

                        }
                    }
                    
                }
                
            }

        }
        current++;

        }
    if (check(A, rows, 2)) {
        coutbroken(A, rows);
    }
    else cout << "All sensors are OK.";
    
    //delete??
    return 0;  

}


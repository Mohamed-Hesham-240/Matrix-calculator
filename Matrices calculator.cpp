#include <iostream>
#include<vector>
#include <iomanip>
#include<stdlib.h>
using namespace std;

//defines
#define endl "\n"
#define IO ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); 

//global matrices
vector < vector<double>>matrix1;
vector < vector<double>>matrix2;

//fumctions declarations
vector<vector<double>> createMatrix(); 
void sum();
void multiply(vector<vector<double>>matrix1, vector<vector<double>>matix2);
void divide(vector<vector<double>>matrix1, vector<vector<double>>matix2);
void subtract(vector<vector<double>>matrix1, vector<vector<double>>matix2);
double getDeterminant(vector<vector<double>>matrix);
int pickOpertaion();
vector<vector<double>> inverse(vector<vector<double>> matrix);
double det2(double one, double two, double three, double four);
void errorAction(int flag);

//main function
int main()
{
    IO;
    cout <<setw(75)<<" Welcome to matrix calculator" << endl;
    newInput:
    cout << "MATRIX #1 :" << endl;
    matrix1=createMatrix();
    cout << "MATRIX #2 :" << endl;
    matrix2=createMatrix();
    cout << "Type youe operation number" << endl;
    newOperation:
    int Flag = pickOpertaion();
    errorAction( Flag );
    if (Flag != 0 && Flag != 12) {
        cout << "Try another operation" << endl;
        goto newOperation;
    }
    else if (Flag == 12) goto newInput;
    cout << "Press 1 to perform another opertaion using the same matrices" << endl <<
            "Press 2 to enter other matrices" << endl <<
            "Press 3 to exit the program" << endl; 
    int choice; cin >> choice;
    if (choice == 1)        goto newOperation;
    else if (choice == 2)   goto newInput;
    else if (choice == 3)   exit(0);
    else                    cout << "Please enter a valid choice" << endl;
    
}

//functios definitions
vector<vector<double>> createMatrix() {
    cout << "Number of rows : ";
    int row1;  cin >> row1;
    cout << "Number of columns : ";
    int col1;  cin >> col1;
    vector <vector<double>> matrix1(row1, vector<double>(col1));
    cout << "Please, enter the matrix " << endl;
    for (int i = 0; i < row1; ++i) 
        for (int j = 0; j < col1; ++j)
            cin >> matrix1[i][j];
    return matrix1; 
}


//
int pickOpertaion() {
    cout << "1 \t Sum" << endl << "2 \t Subtract matrix #2 from matrix #1" << endl << "3 \t Subtract matrix #1 from matrix #2" << endl <<
        "4 \t Multiply matrix #1 by matrix #2" << endl << "5 \t Multiply matrix #2 by matrix #1" << endl << "6 \t To get determinant of matrix #1" << endl << "7 \t To get determinant of matrix #2" << endl <<
        "8 \t Inverse of matrix #1" << endl << "9 \t Inverse of matrix #2" << endl << "10 \t Calculate (matrix #1^-1) * matrix #2" << endl << "11 \t Calculate (matrix #2^-1) * matrix #1" << endl << "12 \t Enter new matrices" << endl;
    cout << "note: The divison, inverse & determinant operations are only applied for 1*1, 2*2 and 3*3 matrices" << endl;
    int numberOfOperation; cin >> numberOfOperation;

    if (numberOfOperation == 1) {
        if (matrix1.size() == matrix2.size() && matrix1[0].size() == matrix2[0].size()) {
            sum();
            return 0;
        }
        else
            return 1;
    }

    else if (numberOfOperation == 2) {
        if (matrix1.size() == matrix2.size() && matrix1[0].size() == matrix2[0].size()) {
            subtract(matrix1, matrix2);
            return 0;
        }
        else
            return 1;
    }

    else if (numberOfOperation == 3) {
        if (matrix1.size() == matrix2.size() && matrix1[0].size() == matrix2[0].size()) {
            subtract(matrix2, matrix1);
            return 0;
        }
        else
            return 1;
    }

    else if (numberOfOperation == 4) {
        if (matrix1[0].size() == matrix2.size()) {
            cout << "The multiplication matrix" << endl;
            multiply(matrix1, matrix2);
            return 0;
        }
        else
            return 2;
    }
    else if (numberOfOperation == 5) {
        if (matrix1.size() == matrix2[0].size()) {
            cout << "The multiplication matrix" << endl;
            multiply(matrix2, matrix1);
            return 0;
        }
        else
            return 2;
    }

    else if (numberOfOperation == 6) {
        if (matrix1.size() == matrix1[0].size()) {
            cout << getDeterminant(matrix1) << endl;;
            return 0;
        }
        else return 3;
    }
    else if (numberOfOperation == 7) {
        if (matrix2.size() == matrix2[0].size()) {
            cout << getDeterminant(matrix2) << endl;;
            return 0;
        }
        else return 3;
    }
    else if (numberOfOperation == 8) {
        if (getDeterminant(matrix1) != 0 && matrix1.size() == matrix1[0].size() && (matrix1.size() == 2 || matrix1.size() == 3 || matrix1.size() == 1)) {
            vector < vector < double>>inv = inverse(matrix1);
            cout << "The inverse matrix=: " << endl;
            for (int i = 0; i < inv.size(); ++i) {
                for (int j = 0; j < inv.size(); ++j)
                    cout << inv[i][j] << " ";
                cout << endl;
            }
            return 0;
        }
        else return 3;
    }
    else if (numberOfOperation == 9) {
        if (getDeterminant(matrix2) != 0 && matrix2.size() == matrix2[0].size() && (matrix2.size() == 2 || matrix2.size() == 3 || matrix2.size() == 1)) {
            vector < vector < double>>inv = inverse(matrix2);
            cout << "The inverse matrix=: " << endl;
            for (int i = 0; i < inv.size(); ++i) {
                for (int j = 0; j < inv.size(); ++j)
                    cout << inv[i][j] << " ";
                cout << endl;
            }
            return 0;
        }
        else return 3;
    }
    else if (numberOfOperation == 10) {
        if (getDeterminant(matrix1) != 0 && matrix1.size() == matrix1[0].size() && (matrix1.size() == 2 || matrix1.size() == 3 || matrix1.size() == 1)
            && matrix1[0].size() == matrix2.size()) {
            divide(matrix1, matrix2);
            return 0;
        }
        else return 3;
    }
    else if (numberOfOperation == 11) {
        if (getDeterminant(matrix2) != 0 && matrix2.size() == matrix2[0].size() && (matrix2.size() == 2 || matrix2.size() == 3 || matrix2.size() == 1)
            && matrix2[0].size() == matrix1.size()) {
            divide(matrix2, matrix1);
            return 0;
        }
        else return 3;
    }
    else if (numberOfOperation == 12)   return 12;
    else return 4;
}

void sum() {
    cout<<"The sum matrix ="<<endl;
    for (int i = 0; i < matrix1.size(); ++i) {
        for (int j = 0; j < matrix1[0].size(); ++j)
            cout << matrix1[i][j] + matrix2[i][j]<<" ";
        cout << endl;
    }
}

void subtract(vector<vector<double>> matrix1, vector<vector<double>> matrix2) {
    cout << "The subtraction matrix =" << endl;
    for (int i = 0; i < matrix1.size(); ++i) {
        for (int j = 0; j < matrix1[0].size(); ++j)
            cout << matrix1[i][j] - matrix2[i][j] << " ";
        cout << endl;
    }
}

void multiply(vector<vector<double>> matrix1, vector<vector<double>> matrix2) {
    int col1 = matrix2.size();
    int answerRows = matrix1.size();
    int answerCols = matrix2[0].size();
    for (int i = 0; i < answerRows; ++i) {
        for (int j = 0; j < answerCols; ++j) {
            double sum = 0;
            for (int ii = 0; ii < col1; ++ii)
                sum += matrix1[i][ii] * matrix2[ii][j];
            cout << sum << " ";
        }
        cout << endl;
    }
}
double getDeterminant(vector<vector<double>>matrix) {
    if (matrix.size() == 2)
        return det2(matrix[0][0], matrix[0][1], matrix[1][0], matrix[1][1]);
    else if (matrix.size() == 3) {
        double a = matrix[1][1] * matrix[2][2] - matrix[2][1] * matrix[1][2];
        double b = matrix[1][0] * matrix[2][2] - matrix[2][0] * matrix[1][2];
        double c = matrix[1][0] * matrix[2][1] - matrix[2][0] * matrix[1][1];
        return matrix[0][0] * a - matrix[0][1] * b + matrix[0][2] * c;
    }
}

double det2(double one, double two, double three, double four) {
    return one * four - two * three;
}

vector<vector<double>> inverse(vector<vector<double>>matrix) {
    double determinant = getDeterminant(matrix);
    vector<vector<double>> answer;
    if (matrix.size() == 2) {
        vector<vector<double>> answer(2, vector<double>(2));
        answer[0][0] =  matrix[1][1] / determinant ;
        answer[1][1] =  matrix[0][0] / determinant ;
        answer[0][1] = -1 * matrix[0][1] / determinant ;
        answer[1][0] = -1 * matrix[1][0] / determinant ;
        return answer;
    }
    else if (matrix.size() == 3) {
        vector<vector<double>> answer(3, vector<double>(3));
        answer[0][0] =  det2(matrix[1][1], matrix[1][2], matrix[2][1], matrix[2][2]) / determinant ;
        answer[1][0] = -1 *  det2(matrix[1][0], matrix[1][2], matrix[2][0], matrix[2][2]) / determinant ;
        answer[2][0] =  det2(matrix[1][0], matrix[1][1], matrix[2][0], matrix[2][1]) / determinant ;
        answer[0][1] = -1 * det2(matrix[0][1], matrix[0][2], matrix[2][1], matrix[2][2]) / determinant ;
        answer[1][1] =  det2(matrix[0][0], matrix[0][2], matrix[2][0], matrix[2][2]) / determinant ;
        answer[2][1] = -1 *  det2(matrix[0][0], matrix[0][1], matrix[2][0], matrix[2][1]) / determinant ;
        answer[0][2] =  det2(matrix[0][1], matrix[0][2], matrix[1][1], matrix[1][2]) / determinant ;
        answer[1][2] = -1 *  det2(matrix[0][0], matrix[0][2], matrix[1][0], matrix[1][2]) / determinant ;
        answer[2][2] =  det2(matrix[0][0], matrix[0][1], matrix[1][0], matrix[1][1]) / determinant ;
        return answer;
        }
    else {
        vector<vector<double>> answer(1, vector<double>(1));
        answer[0][0] = 1 / matrix[0][0];
        return answer;
    }
}

void divide(vector<vector<double>>matrix1, vector<vector<double>>matix2) {
    vector <vector<double>>inv(matrix1.size(), vector<double>(matrix1[0].size()));
    inv = inverse(matrix1);
    multiply(inv, matrix2);
}

void errorAction(int flag) {
    if (flag == 0 || flag ==12)    return;
    else if (flag == 1) cout << "Size compatibility error" << endl;
    else if (flag == 2) cout << "Multiplication error" << endl;
    else if (flag == 3) cout << "Calculation Error" << endl;
    else                cout << "Please enter a valid number" << endl;;
}

// This project was done within a day by Mohamed Hesham Alsaied
// C++ structured programming project
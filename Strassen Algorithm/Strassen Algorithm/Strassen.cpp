#include <iostream>
#include <string>
#include <fstream>
#include <sstream>  // 문자열로부터 입력을 받기 위해 사용. 여기선 main함수의 stoi를 사용하기위해 선언한다.
#include <stdlib.h>

using namespace std;

void MatrixSum(int n, int **X, int **Y, int **Z);
void MatrixSub(int n, int **X, int **Y, int **Z);
void MatrixMul(int**A, int **B, int **C);
void Strassen(int n, int **A, int **B, int **C);

int i;

int main()
{
	string size;
	int n = 0;
	int Size;

	ifstream f_in;  // 파일로부터의 입력을 위해 ifstream 클래스의 객체 f_in 선언
	f_in.open("Strassen.txt");  // 파일 오픈

	if (f_in.is_open()) 
	{
		cout << "파일을 여는데 성공했습니다." << endl << endl;
	}

	else
	{
		cout << "파일을 여는데 실패했습니다." << endl << endl;
	}

	f_in >> size;
	i = stoi(size);  // 이때 stoi는 string of int의 줄임말로 string클래스를 정수로 변경해 주는 함수이다.
	Size = i * i;    // 몇 by 몇 행렬인지 나타냄

	string *file = new string[Size * 2];

	// 행렬 A를 저장하기 위한 배열 arr1 동적 할당
	int **arr1 = (int**)malloc(sizeof(int)*i);

	for (int j = 0; j < i; j++)
	{
		arr1[j] = (int*)malloc(sizeof(int)*i);
	}

	// 행렬 B를 저장하기 위한 배열 arr2 동적 할당
	int **arr2 = (int**)malloc(sizeof(int)*i);

	for (int j = 0; j < i; j++)
	{
		arr2[j] = (int*)malloc(sizeof(int)*i);
	}

	// 행렬 C를 저장하기 위한 배열 arr3 동적 할당
	int **arr3 = (int**)malloc(sizeof(int)*i);

	for (int j = 0; j < i; j++)
	{
		arr3[j] = (int*)malloc(sizeof(int)*i);
	}


	for (int k = 0; k < Size * 2; k++)
	{
		f_in >> file[k];
	}

	for (int k = 0; k < i; k++)
	{
		for (int p = 0; p < i; p++)
		{
			arr1[k][p] = stoi(file[n]);
			n++;
		}
	}

	n = 4;

	for (int k = 0; k < i; k++)
	{
		for (int p = 0; p < i; p++)
		{
			arr2[k][p] = stoi(file[n]);
			n++;
		}
	}

	// 사용자에게 행렬 A를 출력해준다.
	cout << "[행렬 A]" << endl;
	for (int k = 0; k < i; k++)
	{
		if (k != 0)
			cout << endl;
		for (int p = 0; p < i; p++)
		{
			cout << arr1[k][p] << " ";
		}
	}
	cout << endl << endl;

	// 사용자에게 행렬 B를 출력해준다.
	cout << "[행렬 B]" << endl;
	for (int k = 0; k < i; k++)
	{
		if (k != 0)
			cout << endl;
		for (int p = 0; p < i; p++)
		{
			cout << arr2[k][p] << " ";
		}
	}
	cout << endl << endl;

	Strassen(i, arr1, arr2, arr3);  // 슈트라센 알고리즘 적용

	// 슈트라센을 이용한 행렬 곱의 결과를 출력해준다.
	cout << "[A와 B 곱한 결과인 행렬 C]" << endl;
	for (int k = 0; k < i; k++)
	{
		if (k != 0)
			cout << endl;
		for (int p = 0; p < i; p++)
		{
			cout << arr3[k][p] << " ";
		}
	}
	cout << endl << endl;

	f_in.close(); // 사용이 끝난 파일을 닫음
	return 0;
}

// 행렬 A와 B를 더하여 C에 저장시키는 함수(A행렬 B행렬 C행렬의 크기는 모두 같다)
void MatrixSum(int n, int **X, int **Y, int **Z)
{
	for (int p = 0; p<n; p++)
	{
		for (int q = 0; q<n; q++)
		{
			Z[p][q] = X[p][q] + Y[p][q];
		}
	}
}

// 행렬 A와 B를 빼서 C에 저장시키는 함수(A행렬 B행렬 C행렬의 크기는 모두 같다)
void MatrixSub(int n, int **X, int **Y, int **Z)
{
	for (int q = 0; q<n; q++)
	{
		for (int p = 0; p<n; p++) {
			Z[q][p] = X[q][p] - Y[q][p];
		}
	}
}

// 행렬 A와 B를 곱해서 C에 저장시키는 함수(A행렬 B행렬 C행렬의 크기는 모두 같다)
void MatrixMul(int**A, int **B, int **C)
{
	for (int n = 0; n<i; n++)
	{
		for (int j = 0; j<i; j++)
		{
			C[n][j] = 0;
			for (int t = 0; t<i; t++)
			{
				C[n][j] = C[n][j] + A[n][t] * B[t][j];
			}
		}
	}
}

// Strassen Algorithm  함수
void Strassen(int n, int **A, int **B, int **C)
{
	// 각 부분행렬들과 그 계산으로 나오는 부분들 모두 동적 할당
	int **A11 = (int**)malloc(sizeof(int)*i);
	int **A12 = (int**)malloc(sizeof(int)*i);
	int **A21 = (int**)malloc(sizeof(int)*i);
	int **A22 = (int**)malloc(sizeof(int)*i);
	int **B11 = (int**)malloc(sizeof(int)*i);
	int **B12 = (int**)malloc(sizeof(int)*i);
	int **B21 = (int**)malloc(sizeof(int)*i);
	int **B22 = (int**)malloc(sizeof(int)*i);
	int **C11 = (int**)malloc(sizeof(int)*i);
	int **C12 = (int**)malloc(sizeof(int)*i);
	int **C21 = (int**)malloc(sizeof(int)*i);
	int **C22 = (int**)malloc(sizeof(int)*i);
	int **M1 = (int**)malloc(sizeof(int)*i);
	int **M2 = (int**)malloc(sizeof(int)*i);
	int **M3 = (int**)malloc(sizeof(int)*i);
	int **M4 = (int**)malloc(sizeof(int)*i);
	int **M5 = (int**)malloc(sizeof(int)*i);
	int **M6 = (int**)malloc(sizeof(int)*i);
	int **M7 = (int**)malloc(sizeof(int)*i);
	int **AA = (int**)malloc(sizeof(int)*i);
	int **BB = (int**)malloc(sizeof(int)*i);

	for (int j = 0; j < i; j++)
	{
		A11[j] = (int*)malloc(sizeof(int)*i);
		A12[j] = (int*)malloc(sizeof(int)*i);
		A21[j] = (int*)malloc(sizeof(int)*i);
		A22[j] = (int*)malloc(sizeof(int)*i);
		B11[j] = (int*)malloc(sizeof(int)*i);
		B12[j] = (int*)malloc(sizeof(int)*i);
		B21[j] = (int*)malloc(sizeof(int)*i);
		B22[j] = (int*)malloc(sizeof(int)*i);
		C11[j] = (int*)malloc(sizeof(int)*i);
		C12[j] = (int*)malloc(sizeof(int)*i);
		C21[j] = (int*)malloc(sizeof(int)*i);
		C22[j] = (int*)malloc(sizeof(int)*i);
		M1[j] = (int*)malloc(sizeof(int)*i);
		M2[j] = (int*)malloc(sizeof(int)*i);
		M3[j] = (int*)malloc(sizeof(int)*i);
		M4[j] = (int*)malloc(sizeof(int)*i);
		M5[j] = (int*)malloc(sizeof(int)*i);
		M6[j] = (int*)malloc(sizeof(int)*i);
		M7[j] = (int*)malloc(sizeof(int)*i);
		AA[j] = (int*)malloc(sizeof(int)*i);
		BB[j] = (int*)malloc(sizeof(int)*i);
	}

	// 행렬의 크기가 2일 경우 바로 계산 가능
	if (n == 2)
	{
		MatrixMul(A, B, C);
	}

	// 행렬의 크기가 2보다 클 경우 다시 4개의 부분행으로 나눈다.
	else
	{
		for (int i = 0; i<n / 2; i++)
		{
			for (int j = 0; j<n / 2; j++) {
				A11[i][j] = A[i][j];
				A12[i][j] = A[i][j + n / 2];
				A21[i][j] = A[i + n / 2][j];
				A22[i][j] = A[i + n / 2][j + n / 2];

				B11[i][j] = B[i][j];
				B12[i][j] = B[i][j + n / 2];
				B21[i][j] = B[i + n / 2][j];
				B22[i][j] = B[i + n / 2][j + n / 2];
			}
		}

		MatrixSum(n / 2, A11, A22, AA);
		MatrixSum(n / 2, B11, B22, BB);
		Strassen(n / 2, AA, BB, M1);

		MatrixSum(n / 2, A21, A22, AA);
		Strassen(n / 2, AA, B11, M2);

		MatrixSub(n / 2, B12, B22, BB);
		Strassen(n / 2, A11, BB, M3);


		MatrixSub(n / 2, B21, B11, BB);
		Strassen(n / 2, A22, BB, M4);

		MatrixSum(n / 2, A11, A12, AA);
		Strassen(n / 2, AA, B22, M5);

		MatrixSub(n / 2, A21, A11, AA);
		MatrixSum(n / 2, B11, B12, BB);
		Strassen(n / 2, AA, BB, M6);

		MatrixSub(n / 2, A12, A22, AA);
		MatrixSum(n / 2, B21, B22, BB);
		Strassen(n / 2, AA, BB, M7);


		MatrixSum(n / 2, M1, M4, AA);
		MatrixSub(n / 2, M7, M5, BB);
		MatrixSum(n / 2, AA, BB, C11);

		MatrixSum(n / 2, M3, M5, C12);

		MatrixSum(n / 2, M2, M4, C21);

		MatrixSub(n / 2, M1, M2, AA);
		MatrixSum(n / 2, M3, M6, BB);
		MatrixSum(n / 2, AA, BB, C22);

		for (int i = 0; i<n / 2; i++)
		{
			for (int j = 0; j<n / 2; j++)
			{
				C[i][j] = C11[i][j];
				C[i][j + n / 2] = C12[i][j];
				C[i + n / 2][j] = C21[i][j];
				C[i + n / 2][j + n / 2] = C22[i][j];
			}
		}
	}
}
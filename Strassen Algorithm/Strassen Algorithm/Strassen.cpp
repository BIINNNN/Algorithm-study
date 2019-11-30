#include <iostream>
#include <string>
#include <fstream>
#include <sstream>  // ���ڿ��κ��� �Է��� �ޱ� ���� ���. ���⼱ main�Լ��� stoi�� ����ϱ����� �����Ѵ�.
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

	ifstream f_in;  // ���Ϸκ����� �Է��� ���� ifstream Ŭ������ ��ü f_in ����
	f_in.open("Strassen.txt");  // ���� ����

	if (f_in.is_open()) 
	{
		cout << "������ ���µ� �����߽��ϴ�." << endl << endl;
	}

	else
	{
		cout << "������ ���µ� �����߽��ϴ�." << endl << endl;
	}

	f_in >> size;
	i = stoi(size);  // �̶� stoi�� string of int�� ���Ӹ��� stringŬ������ ������ ������ �ִ� �Լ��̴�.
	Size = i * i;    // �� by �� ������� ��Ÿ��

	string *file = new string[Size * 2];

	// ��� A�� �����ϱ� ���� �迭 arr1 ���� �Ҵ�
	int **arr1 = (int**)malloc(sizeof(int)*i);

	for (int j = 0; j < i; j++)
	{
		arr1[j] = (int*)malloc(sizeof(int)*i);
	}

	// ��� B�� �����ϱ� ���� �迭 arr2 ���� �Ҵ�
	int **arr2 = (int**)malloc(sizeof(int)*i);

	for (int j = 0; j < i; j++)
	{
		arr2[j] = (int*)malloc(sizeof(int)*i);
	}

	// ��� C�� �����ϱ� ���� �迭 arr3 ���� �Ҵ�
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

	// ����ڿ��� ��� A�� ������ش�.
	cout << "[��� A]" << endl;
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

	// ����ڿ��� ��� B�� ������ش�.
	cout << "[��� B]" << endl;
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

	Strassen(i, arr1, arr2, arr3);  // ��Ʈ�� �˰��� ����

	// ��Ʈ���� �̿��� ��� ���� ����� ������ش�.
	cout << "[A�� B ���� ����� ��� C]" << endl;
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

	f_in.close(); // ����� ���� ������ ����
	return 0;
}

// ��� A�� B�� ���Ͽ� C�� �����Ű�� �Լ�(A��� B��� C����� ũ��� ��� ����)
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

// ��� A�� B�� ���� C�� �����Ű�� �Լ�(A��� B��� C����� ũ��� ��� ����)
void MatrixSub(int n, int **X, int **Y, int **Z)
{
	for (int q = 0; q<n; q++)
	{
		for (int p = 0; p<n; p++) {
			Z[q][p] = X[q][p] - Y[q][p];
		}
	}
}

// ��� A�� B�� ���ؼ� C�� �����Ű�� �Լ�(A��� B��� C����� ũ��� ��� ����)
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

// Strassen Algorithm  �Լ�
void Strassen(int n, int **A, int **B, int **C)
{
	// �� �κ���ĵ�� �� ������� ������ �κе� ��� ���� �Ҵ�
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

	// ����� ũ�Ⱑ 2�� ��� �ٷ� ��� ����
	if (n == 2)
	{
		MatrixMul(A, B, C);
	}

	// ����� ũ�Ⱑ 2���� Ŭ ��� �ٽ� 4���� �κ������� ������.
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
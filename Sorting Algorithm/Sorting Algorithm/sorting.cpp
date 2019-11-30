#include <iostream>
#include <sstream> 
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;

class StudentInfo
{
public:
	string name;
	string major;
	int score;
};

int Menu(StudentInfo *TXT);  // �޴��Լ�
void InsertionSort(StudentInfo *TXT, int IS_NUM, int IS_ORDER);  // Insertion Sort�� �����ϴ� �Լ�
void MergeSort_Intro(StudentInfo *TXT, int MS_NUM, int MS_ORDER);   // Merge Sort�� �����ϱ� ���� �Լ�
void MergeSort(StudentInfo *TXT, int Start, int End, int MS_NUM);  // Merge Sort�� ������ �� �ʿ��� ����� �Լ�
															      // �Ҵ�� Ŭ���� �迭�� ������ �����鼭 �̸� �ݺ�
void Merge(StudentInfo *TXT, int Start, int MID, int End, int MS_NUM);  //Merge Sort�� ������ ��, ���� ���ĵǾ����� �κ��� �ٷ� �Լ�
void Print_MS(StudentInfo *TXT, int MS_ORDER);  // Merge Sort�� ��� ��� �Լ�

int number = 0;// �л���
int MainCounter = 0;// ��Ƚ�� ī��Ʈ

int main()
{
	int menu = 0;
	int i = 0;

	string filename;

	// ����ڿ��� ���ϴ� ���ϸ��� ���� �Է¹���
	cout << "���� ���ϸ��� �Է��ϼ���(ex.input.txt) :";
	cin >> filename;
	ifstream get(filename.c_str());

	getline(get, filename);
	number = filename[0] - 48; // ���� ������ ������ �ξ��� �ؽ�Ʈ ������ �л���(number)�� ����

	StudentInfo *FirstText = new StudentInfo[number];  // Ŭ������ �� ���� �Ҵ�
	StudentInfo *LastText = new StudentInfo[number];   // ������ ���� �� ����� Ŭ������ �Ҵ�

	// ������ �� �ҷ��������� �˻� ����
	if (get.is_open())
	{
		cout << "���� �ҷ����� �Ϸ�.\n\n";
		while (!get.eof())   // �ؽ�Ʈ�� �� ������ �� ������ �ݺ���
		{
			menu = 0;
			getline(get, filename);

			// stringstream �̿��Ͽ� Ŭ������ �����͸� ����
			stringstream string(filename);

			//i�� �������Ѱ��鼭 ���������� Ŭ������ �־���
			//�ʹ� ���� �޸� ��������� ����� �������� ����.
			string >> FirstText[i].name >> FirstText[i].major >> FirstText[i].score; 
			i++;
		}
	}
	else
	{
		cout << "������ ���µ� �����Ͽ����ϴ�.\n";
		Sleep(1000);
		return 0;
	}

	while (1)
	{
		MainCounter = 0;  // ��Ƚ�� ī��Ʈ 
		for (int i = 0; i < number; i++)
		{
			// ������ �޾Ҵ� Ŭ���� ������ ������ Ŭ������ �������ֱ�
			LastText[i].name = FirstText[i].name;
			LastText[i].major = FirstText[i].major;
			LastText[i].score = FirstText[i].score;			
		}
		menu = Menu(LastText);

	}
	delete[] LastText;

	return 0;
}

int Menu(StudentInfo *TXT)
{
	int menu1 = 0, menu2 = 0, menu3 = 0;  // ���� ����, ����, ���� ������ ���ϴ� ���� 3��

	cout << "���ϴ� ���� ������ ��ȣ�� �Է��ϼ���.(���ڸ� �Է��� ��)\n";
	cout << "Insertion Sort = 1\n"
		<< "Merge Sort= 2\n" << "�Է� :";
	cin >> menu1;

	cout << "\n���ϴ� ���� ������ ��ȣ�� �Է��ϼ���.(���ڸ� �Է��� ��)\n";
	cout << "������ = 1\n�а��� = 2\n�̸��� = 3\n" << "�Է� :";
	cin >> menu2;

	cout << "\n���ϴ� ���� ������ ��ȣ�� �Է��ϼ���.(���ڸ� �Է��� ��)\n";
	cout << "�������� = 1\n�������� = 2\n" << "�Է� :";
	cin >> menu3;
	cout << "\n";

	if (menu1 == 1)
		InsertionSort(TXT, menu2, menu3);
	else if (menu1 == 2)
		MergeSort_Intro(TXT, menu2, menu3);

	return 0;
}

void InsertionSort(StudentInfo *TXT, int IS_NUM, int IS_ORDER) // Insertion Sort �Լ�
{
	StudentInfo temp; // swap���� temp Ŭ����
	int i, j;

	if (IS_NUM == 1)  // menu2�� �������� ���
	{
		int  pointer;
		for (i = 1; i < number; i++)
		{
			pointer = TXT[i].score;
			temp = TXT[i];
			for (j = i - 1; j >= 0 && (TXT[j].score > pointer); j--)
			{
				MainCounter++;
				TXT[j + 1] = TXT[j];
			}
			TXT[j + 1] = temp;
		}
	}

	else // menu2�� �а� Ȥ�� �̸����� ���
	{
		string Spointer;
		if (IS_NUM == 2)  // �а�
		{
			for (i = 1; i < number; i++)
			{
				Spointer = TXT[i].major;
				temp = TXT[i];
				for (j = i - 1; j >= 0 && (TXT[j].major > Spointer); j--)
				{
					MainCounter++;
					TXT[j + 1] = TXT[j];
				}
				TXT[j + 1] = temp;
			}
		}

		else if (IS_NUM == 3)  // �̸�
		{
			for (i = 1; i < number; i++)
			{
				Spointer = TXT[i].name;
				temp = TXT[i];
				for (j = i - 1; j >= 0 && (TXT[j].name > Spointer); j--)
				{
					MainCounter++;
					TXT[j + 1] = TXT[j];
				}
				TXT[j + 1] = temp;
			}
		}
	}

	// ���� ����(��������/��������)
	if (IS_ORDER == 1)   // ��������
	{
		cout << "\n��Ƚ���� " << MainCounter << "ȸ �Դϴ�.\n";
		for (i = 0; i < number; i++)
		{
			cout << TXT[i].name << " " << TXT[i].major << " " << TXT[i].score << " \n";
		}
	}

	else if (IS_ORDER == 2)   // ��������(���������� ������ ���)
	{
		cout << "\n��Ƚ���� " << MainCounter << "ȸ �Դϴ�.\n";
		for (i = number - 1; i >= 0; i--)
		{
			cout << TXT[i].name << " " << TXT[i].major << " " << TXT[i].score << " \n";
		}
	}
	cout << "\n";
}

// Merge Sort�� Insertion Sort�� �ٸ��� �Լ��� �������� ������ ����
void MergeSort_Intro(StudentInfo *TXT, int MS_NUM, int MS_ORDER)//�պ����� ���� �Լ�
{
	int start = 0, end = number - 1;

	MergeSort(TXT, start, end, MS_NUM);  //Merge Sort ����
	Print_MS(TXT, MS_ORDER);  // Merge Sort�� ���ĵ� Ŭ���� ���
	cout << "\n";
}

// Merge �Լ��� �������� �Լ�
// �迭�� ���� �迭�� ������ Merge()�� ȣ���Ͽ� ����
void MergeSort(StudentInfo *TXT, int Start, int End, int MS_NUM)
{
	int mid = 0;
	if (Start < End)
	{
		mid = ((Start + End) / 2); // ����� ����ų mid����
								 
		MergeSort(TXT, Start, mid, MS_NUM);
		MergeSort(TXT, mid + 1, End, MS_NUM);
		Merge(TXT, Start, mid, End, MS_NUM);

	}
}
void Merge(StudentInfo *TXT, int Start, int MID, int End, int MS_NUM)
{
	int Left = MID - Start + 1;  // �������� ����
	int Right = End - MID; // �������� ������

	StudentInfo *L = new StudentInfo[Left + 1];
	StudentInfo *R = new StudentInfo[Right + 1];
	// ��, ��� ����� Ŭ���� �迭 �����Ҵ�(�ӽ�)

	for (int i = 0; i < Left; i++)
	{
		L[i].name = TXT[Start + i].name;
		L[i].score = TXT[Start + i].score;
		L[i].major = TXT[Start + i].major;		
	}
	for (int j = 0; j < Right; j++)
	{
		R[j].name = TXT[MID + j + 1].name;
		R[j].score = TXT[MID + j + 1].score;
		R[j].major = TXT[MID + j + 1].major;		
	}

	// int�� �������� �ʱ�ȭ ����� name�� major�� '0'
	// string���� �ʱ�ȭ ����� hakjum�� -1
	L[Left].name = '0';
	L[Left].score = -1;
	L[Left].major = '0';
	
	R[Right].name = '0';
	R[Right].score = -1;
	R[Right].major = '0';
	

	// �� �ܰ� �Լ����� ���ļ� ���������� �迭�� ��ġ�� ����
	// 1������ �����ؼ� ��ġ�� ����
	if (MS_NUM == 1)
	{
		int i = 0;
		int j = 0;

		for (int k = Start; k < End + 1; k++) // ����
		{
			MainCounter++;
			if (L[i].score >= R[j].score)
			{
				TXT[k].name = L[i].name;
				TXT[k].major = L[i].major;
				TXT[k].score = L[i].score;
				i++;
			}
			else
			{
				TXT[k].name = R[j].name;
				TXT[k].major = R[j].major;
				TXT[k].score = R[j].score;
				j++;
			}
		}
	}
	else if (MS_NUM == 2)
	{
		int i = 0;
		int j = 0;

		for (int k = Start; k < End + 1; k++) // �а�
		{
			MainCounter++;
			if (L[i].major >= R[j].major)
			{
				TXT[k].name = L[i].name;
				TXT[k].major = L[i].major;
				TXT[k].score = L[i].score;
				i++;
			}
			else
			{
				TXT[k].name = R[j].name;
				TXT[k].major = R[j].major;
				TXT[k].score = R[j].score;
				j++;
			}
		}
	}
	else if (MS_NUM == 3)
	{
		int i = 0;
		int j = 0;

		for (int k = Start; k < End + 1; k++) // �̸�
		{
			MainCounter++;
			if (L[i].name >= R[j].name)
			{
				TXT[k].name = L[i].name;
				TXT[k].major = L[i].major;
				TXT[k].score = L[i].score;
				i++;
			}
			else
			{
				TXT[k].name = R[j].name;
				TXT[k].major = R[j].major;
				TXT[k].score = R[j].score;
				j++;
			}
		}
	}

	// �Ҵ��ߴ� Ŭ������ ���� �Ҵ� Ǯ��
	delete[] L;
	delete[] R;

}
void Print_MS(StudentInfo *TXT, int MS_ORDER)
{
	int i = 0;
	if (MS_ORDER == 1)
	{
		cout << "\n��Ƚ���� " << MainCounter/2 << "ȸ �Դϴ�.\n";
		for (i = number - 1; i >= 0; i--)

		{
			cout << TXT[i].name << " " << TXT[i].major << " " << TXT[i].score << " \n";
		}
	}
	else if (MS_ORDER == 2)
	{
		cout << "\n��Ƚ���� " << MainCounter/2 << "ȸ �Դϴ�.\n";
		for (i = 0; i < number; i++)
		{
			cout << TXT[i].name << " " << TXT[i].major << " " << TXT[i].score << " \n";
		}
	}
}
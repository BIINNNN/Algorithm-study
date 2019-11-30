#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

class StudentInfo  // �л����� Ŭ����
{
public:
	string name;
	int hakbun;
	int score;
};

StudentInfo heap_extract_max(StudentInfo *stu);
void max_heapify(StudentInfo *stu, int i);
void build_max_heapify(StudentInfo *stu);
int left(int i);
int right(int i);
int parent(int i);

int number;
int Size;
int right(int i)
{
	return (2 * i) + 2;
}

int left(int i) 
{ 
	return (2 * i) + 1;
}

int parent(int i) 
{
	return i / 2;
}

void max_heapify(StudentInfo *stu, int i)//�ִ��� ����
{
	int l, r, largest;
	StudentInfo temp;

	l = left(i);
	r = right(i);

	if (l < Size && stu[l].score > stu[i].score)
		largest = l;
	else
		largest = i;

	if (r < Size && stu[r].score > stu[largest].score)
		largest = r;

	if (largest != i)
	{
		temp = stu[i];
		stu[i] = stu[largest];
		stu[largest] = temp;
		max_heapify(stu, largest);
	}
}

StudentInfo heap_extract_max(StudentInfo *stu)  //�켱������� �� ����
{
	StudentInfo max;

	if (number < 1)
	{
		cout << "underflow";
		exit(0);
	}

	for (int i = 0; i < number; i++)
	{
		max = stu[0];
		stu[0] = stu[Size - 1];
		stu[Size - 1] = max;
		Size = Size - 1;

		cout << max.name << setw(10) << max.hakbun << setw(3) << max.score << endl;

		max_heapify(stu, 0);
	}
	return max;
}

void build_max_heapify(StudentInfo *stu)  //������
{
	for (int i = (Size - 1) / 2; i >= 0; i--)
		max_heapify(stu, i);
}

void main()
{
	char title[10];
	static int count = 0;

	cout << "�ؽ�Ʈ ���ϸ��� �Է��Ͻÿ�:";
	cin >> title;

	ifstream fin;

	fin.open(title);
	fin >> number;
	Size = number;

	StudentInfo *s = new StudentInfo[number];

	for (int i = 0; i < number; i++)
	{
		fin >> s[i].name;
		fin >> s[i].hakbun;
		fin >> s[i].score;
		cout << s[i].name << " " << s[i].hakbun << " " << s[i].score << endl;
	}
	cout << "\n" << ">> �ִ� �켱 ���� ��� <<"  << "\n";

	fin.close();

	build_max_heapify(s);
	heap_extract_max(s);

}

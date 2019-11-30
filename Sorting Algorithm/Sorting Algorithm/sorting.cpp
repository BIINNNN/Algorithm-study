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

int Menu(StudentInfo *TXT);  // 메뉴함수
void InsertionSort(StudentInfo *TXT, int IS_NUM, int IS_ORDER);  // Insertion Sort를 실행하는 함수
void MergeSort_Intro(StudentInfo *TXT, int MS_NUM, int MS_ORDER);   // Merge Sort를 시작하기 위한 함수
void MergeSort(StudentInfo *TXT, int Start, int End, int MS_NUM);  // Merge Sort를 실행할 때 필요한 재귀형 함수
															      // 할당된 클래스 배열을 반으로 나누면서 이를 반복
void Merge(StudentInfo *TXT, int Start, int MID, int End, int MS_NUM);  //Merge Sort를 실행할 때, 실제 정렬되어지는 부분을 다룬 함수
void Print_MS(StudentInfo *TXT, int MS_ORDER);  // Merge Sort의 결과 출력 함수

int number = 0;// 학생수
int MainCounter = 0;// 비교횟수 카운트

int main()
{
	int menu = 0;
	int i = 0;

	string filename;

	// 사용자에게 원하는 파일명을 직접 입력받음
	cout << "읽을 파일명을 입력하세요(ex.input.txt) :";
	cin >> filename;
	ifstream get(filename.c_str());

	getline(get, filename);
	number = filename[0] - 48; // 전역 변수로 설정해 두었던 텍스트 파일의 학생수(number)를 받음

	StudentInfo *FirstText = new StudentInfo[number];  // 클래스의 수 동적 할당
	StudentInfo *LastText = new StudentInfo[number];   // 정렬이 끝난 후 저장될 클래스를 할당

	// 파일이 잘 불러와졌는지 검사 시작
	if (get.is_open())
	{
		cout << "파일 불러오기 완료.\n\n";
		while (!get.eof())   // 텍스트가 빈 공간이 될 때까지 반복함
		{
			menu = 0;
			getline(get, filename);

			// stringstream 이용하여 클래스에 데이터를 저장
			stringstream string(filename);

			//i를 증가시켜가면서 순차적으로 클래스에 넣어줌
			//너무 많은 메모리 사용하지만 방법이 떠오르지 않음.
			string >> FirstText[i].name >> FirstText[i].major >> FirstText[i].score; 
			i++;
		}
	}
	else
	{
		cout << "파일을 여는데 실패하였습니다.\n";
		Sleep(1000);
		return 0;
	}

	while (1)
	{
		MainCounter = 0;  // 비교횟수 카운트 
		for (int i = 0; i < number; i++)
		{
			// 기존에 받았던 클래스 내용을 저장할 클래스에 복사해주기
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
	int menu1 = 0, menu2 = 0, menu3 = 0;  // 정렬 종류, 기준, 정렬 순서를 정하는 변수 3개

	cout << "원하는 정렬 종류의 번호를 입력하세요.(숫자만 입력할 것)\n";
	cout << "Insertion Sort = 1\n"
		<< "Merge Sort= 2\n" << "입력 :";
	cin >> menu1;

	cout << "\n원하는 정렬 기준의 번호를 입력하세요.(숫자만 입력할 것)\n";
	cout << "학점순 = 1\n학과순 = 2\n이름순 = 3\n" << "입력 :";
	cin >> menu2;

	cout << "\n원하는 정렬 순서의 번호를 입력하세요.(숫자만 입력할 것)\n";
	cout << "오름차순 = 1\n내림차순 = 2\n" << "입력 :";
	cin >> menu3;
	cout << "\n";

	if (menu1 == 1)
		InsertionSort(TXT, menu2, menu3);
	else if (menu1 == 2)
		MergeSort_Intro(TXT, menu2, menu3);

	return 0;
}

void InsertionSort(StudentInfo *TXT, int IS_NUM, int IS_ORDER) // Insertion Sort 함수
{
	StudentInfo temp; // swap위하 temp 클래스
	int i, j;

	if (IS_NUM == 1)  // menu2가 학점순인 경우
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

	else // menu2가 학과 혹은 이름순일 경우
	{
		string Spointer;
		if (IS_NUM == 2)  // 학과
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

		else if (IS_NUM == 3)  // 이름
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

	// 정렬 순서(오름차순/내림차순)
	if (IS_ORDER == 1)   // 오름차순
	{
		cout << "\n비교횟수는 " << MainCounter << "회 입니다.\n";
		for (i = 0; i < number; i++)
		{
			cout << TXT[i].name << " " << TXT[i].major << " " << TXT[i].score << " \n";
		}
	}

	else if (IS_ORDER == 2)   // 내림차순(오름차순을 역으로 출력)
	{
		cout << "\n비교횟수는 " << MainCounter << "회 입니다.\n";
		for (i = number - 1; i >= 0; i--)
		{
			cout << TXT[i].name << " " << TXT[i].major << " " << TXT[i].score << " \n";
		}
	}
	cout << "\n";
}

// Merge Sort는 Insertion Sort와 다르게 함수를 여러개로 나누어 진행
void MergeSort_Intro(StudentInfo *TXT, int MS_NUM, int MS_ORDER)//합병정렬 시작 함수
{
	int start = 0, end = number - 1;

	MergeSort(TXT, start, end, MS_NUM);  //Merge Sort 실행
	Print_MS(TXT, MS_ORDER);  // Merge Sort로 정렬된 클래스 출력
	cout << "\n";
}

// Merge 함수와 나누어진 함수
// 배열을 하위 배열로 나누고 Merge()를 호출하여 병합
void MergeSort(StudentInfo *TXT, int Start, int End, int MS_NUM)
{
	int mid = 0;
	if (Start < End)
	{
		mid = ((Start + End) / 2); // 가운데를 가리킬 mid설정
								 
		MergeSort(TXT, Start, mid, MS_NUM);
		MergeSort(TXT, mid + 1, End, MS_NUM);
		Merge(TXT, Start, mid, End, MS_NUM);

	}
}
void Merge(StudentInfo *TXT, int Start, int MID, int End, int MS_NUM)
{
	int Left = MID - Start + 1;  // 기준점의 왼쪽
	int Right = End - MID; // 기준점의 오른쪽

	StudentInfo *L = new StudentInfo[Left + 1];
	StudentInfo *R = new StudentInfo[Right + 1];
	// 좌, 우로 나뉘어서 클래스 배열 동적할당(임시)

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

	// int로 데이터형 초기화 해줬던 name과 major는 '0'
	// string으로 초기화 해줬던 hakjum은 -1
	L[Left].name = '0';
	L[Left].score = -1;
	L[Left].major = '0';
	
	R[Right].name = '0';
	R[Right].score = -1;
	R[Right].major = '0';
	

	// 전 단계 함수에서 걸쳐서 나누어졌던 배열을 합치기 시작
	// 1개부터 시작해서 합치기 시작
	if (MS_NUM == 1)
	{
		int i = 0;
		int j = 0;

		for (int k = Start; k < End + 1; k++) // 학점
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

		for (int k = Start; k < End + 1; k++) // 학과
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

		for (int k = Start; k < End + 1; k++) // 이름
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

	// 할당했던 클래스의 동적 할당 풀기
	delete[] L;
	delete[] R;

}
void Print_MS(StudentInfo *TXT, int MS_ORDER)
{
	int i = 0;
	if (MS_ORDER == 1)
	{
		cout << "\n비교횟수는 " << MainCounter/2 << "회 입니다.\n";
		for (i = number - 1; i >= 0; i--)

		{
			cout << TXT[i].name << " " << TXT[i].major << " " << TXT[i].score << " \n";
		}
	}
	else if (MS_ORDER == 2)
	{
		cout << "\n비교횟수는 " << MainCounter/2 << "회 입니다.\n";
		for (i = 0; i < number; i++)
		{
			cout << TXT[i].name << " " << TXT[i].major << " " << TXT[i].score << " \n";
		}
	}
}
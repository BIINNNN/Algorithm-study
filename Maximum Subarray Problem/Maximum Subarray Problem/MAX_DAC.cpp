// ���� ���� ������� �ִ� �κй迭 ���� �ذ�

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int Max(int a, int b);
int Max(int a, int b, int c);
int maxCrossingSum(int A[], int low, int middle, int high);
int maxSubArraySum(int A[], int low, int high);

FILE *in_fp;

int main()
{
	in_fp = fopen("MaxSubarray.txt", "r");
	int length;
	freopen("MaxSubarray.txt", "r", stdin);
	scanf("%d", &length);
	int* A = (int*)malloc(sizeof(int)*(length));
	printf("�������� ����: %d\n", length);
	printf("�Էµ� ������: ");
	for (int i = 0; i < length; i++)
	{
		scanf("%d", &A[i]);		
		printf("%d  ", A[i]);		
	}
	printf("\n\n");
	
	int max_sum = maxSubArraySum(A, 0, length - 1);
	printf(">> �κ� �迭���� �ִ���  %d\n\n", max_sum);
	getchar();
	return 0;
}
// �ִ� 2���� ������ ã�� �Լ�
int Max(int a, int b)
{
	return (a > b) ? a : b;
}

// �ִ� 3���� ������ ã�� �Լ�
int Max(int a, int b, int c)
{
	return Max(Max(a, b), c);
}

// A[middle]�� �Ϻ��� �� A[]���� ������ �ִ��� �� ã�� �Լ�
int maxCrossingSum(int A[], int low, int middle, int high)
{
	// middle ���� ��� ����
	int sum = 0;
	int left_sum = INT_MIN;
	for (int i = middle; i >= low; i--)
	{
		sum = sum + A[i];
		if (sum > left_sum)
			left_sum = sum;
	}

	// middle ������ ��� ����
	sum = 0;
	int right_sum = INT_MIN;
	for (int i = middle + 1; i <= high; i++)
	{
		sum = sum + A[i];
		if (sum > right_sum)
			right_sum = sum;
	}

	return left_sum + right_sum;
}

// A[low..high]���� �ִ� �κй迭�� �� ��ȯ
int maxSubArraySum(int A[], int low, int high)
{
	// �⺻: �ϳ��� ����
	if (low == high)
		return A[low];

	// middle point ã��
	int middle = (low + high) / 2;

	/* ������ ���� �� ������ ��� �� �ִ밪 ��ȯ
	* 1) A[low,middle]������ �ִ� �κ� �迭�� ��
	* 2) A[middle+1,high]������ �ִ� �κ� �迭�� ��
	* 3) middle point �� �������� ����� �ִ� �κ� �迭�� ��*/
	return Max(maxSubArraySum(A, low, middle), maxSubArraySum(A, middle + 1, high), maxCrossingSum(A, low, middle, high));
}

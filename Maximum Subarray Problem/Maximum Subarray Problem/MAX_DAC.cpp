// 분할 정복 방법으로 최대 부분배열 문제 해결

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
	printf("데이터의 갯수: %d\n", length);
	printf("입력된 데이터: ");
	for (int i = 0; i < length; i++)
	{
		scanf("%d", &A[i]);		
		printf("%d  ", A[i]);		
	}
	printf("\n\n");
	
	int max_sum = maxSubArraySum(A, 0, length - 1);
	printf(">> 부분 배열합의 최댓값은  %d\n\n", max_sum);
	getchar();
	return 0;
}
// 최대 2개의 정수를 찾는 함수
int Max(int a, int b)
{
	return (a > b) ? a : b;
}

// 최대 3개의 정수를 찾는 함수
int Max(int a, int b, int c)
{
	return Max(Max(a, b), c);
}

// A[middle]이 일부일 때 A[]에서 가능한 최대의 합 찾는 함수
int maxCrossingSum(int A[], int low, int middle, int high)
{
	// middle 왼쪽 요소 포함
	int sum = 0;
	int left_sum = INT_MIN;
	for (int i = middle; i >= low; i--)
	{
		sum = sum + A[i];
		if (sum > left_sum)
			left_sum = sum;
	}

	// middle 오른쪽 요소 포함
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

// A[low..high]에서 최대 부분배열의 합 반환
int maxSubArraySum(int A[], int low, int high)
{
	// 기본: 하나의 원소
	if (low == high)
		return A[low];

	// middle point 찾기
	int middle = (low + high) / 2;

	/* 가능한 다음 세 가지의 경우 중 최대값 반환
	* 1) A[low,middle]에서의 최대 부분 배열의 합
	* 2) A[middle+1,high]에서의 최대 부분 배열의 합
	* 3) middle point 를 가로질러 생기는 최대 부분 배열의 합*/
	return Max(maxSubArraySum(A, low, middle), maxSubArraySum(A, middle + 1, high), maxCrossingSum(A, low, middle, high));
}

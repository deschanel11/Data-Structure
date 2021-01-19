// Date : Sep 12, 2020 11 : 59 pm

/*
 입력으로 먼저 정수의 개수 N<100이 주어지고, 이어서 N개의 정수가 주어진다. 
 N개의 정수들을 오름차순으로 정렬하여 한 줄에 하나씩 출력하는 프로그램을 완성하라. 
 단, 프로그램의 어떤 부분에서도 배열 인덱스 연산자 []를 사용해서는 안된다.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable : 4996)
#define MAX 100

void sort(int* data, int n);

int main() {

    
	int N;
	int data[MAX];

	scanf("%d", &N);

	for (int i = 0; i < N; i++)
		scanf("%d", (data + i));


	sort(data, N);

	for (int i = 0; i < N; i++)
		printf("%d\n", *(data + i));

  return 0;
}


void sort(int* data, int n) {
	//int n = strlen(data);
	for (int i = n-1; i > 0; i--) //i>0 (j 때문)
		for (int j = 0; j < i; j++) //j<i (bubble sort에서 i와 j는 절대 같아질 수 없음.)
			if (*(data + j) > *(data + j + 1)) {
				int tmp;
				tmp = *(data + j);
				*(data + j) = *(data + j + 1);
				*(data + j + 1) = tmp;
			}
}

//Date : Sep 12, 2020 11:59

/*왼쪽의 프로그램은 먼저 정수의 개수 N<100을 입력받고 이어서 N개의 정수를 입력받아 배열 data에 저장한다. 
함수 find_max는 배열에 저장된 정수들 중 최대값을 찾아 반환해야 한다. 
함수 find_max를 완성하라. 단, find_max 함수에서는 배열 인덱스 연산자([])를 사용해서는 안된다. 
주어진 코드를 변경해서는 안된다*/

#include <stdio.h>
#define MAX 100
int find_max(int, int *);
int main()
{
    int N;
    int data[MAX];
    scanf("%d", &N);
    for (int i=0; i<N; i++)
        scanf("%d", &data[i]);
    int mx = find_max(N, data);
    printf("%d\n", mx);
}

int find_max(int n, int *data)
{
	    /* Do not use array index operator [ ] */

int max = *data;

	for (int i = 0; i < n; i++) {
		if (*(data + i) > max)
			max = *(data + i);
	}

	return max;


}

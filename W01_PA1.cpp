// date : Sep 12, 2020 11:59

/*왼쪽의 프로그램에서 입력된 세 정수 a, b, c가 오름차순으로 정렬되어 출력되도록 함수 sort_abc를 추가하라. 
주어진 코드를 수정해서는 안된다. */


#include <stdio.h>


void sort_abc(int* a, int* b, int* c);

int main()
{
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    sort_abc(&a, &b, &c);
    printf("%d %d %d\n", a, b, c);
}


void sort_abc(int* a, int* b, int* c) {
	int tmp;
	int array[3];

	if (*b > * c) {
		tmp = *b;
		*b = *c;
		*c = tmp;
	}

	if (*a > *b) {
		tmp = *a;
		*a = *b;
		*b = tmp;
	}

	if (*b > *c) {
		tmp = *b;
		*b = *c;
		*c = tmp;
	}
}

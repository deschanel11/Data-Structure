//Date : Sep 12, 2020 06 : 59 pm

/*
입력의 첫 줄에는 테이블의 행의 개수 m<10과 열의 개수 n<10이 주어진다.  
이어서 m*n개의 영문 알파벳으로만 구성된 단어들이 주어진다. 
각 단어의 길이는 최대 20이다. 
단어들은 행우선 순서로 테이블에 채워진다.  
불필요한 공백이 없이 세로로 줄맞춤된 형태로 테이블을 화면에 출력하는 프로그램을 작성하라. 
출력은 매우 엄격하게 체크된다. 
열 간의 간격은 가능한 한 최소(즉, 하나의 공백 문자)여야하고, 각 행의 마지막 열은 불필요한 공백 없이 줄바꿈 문자로 끝나야 한다.

입력 예:
3 4
Implement a function that sort an integer array 
without using bracket operators

출력 예:
Implement a     function that↩︎         /* 각 행은 불필요한 공백없이 */
sort      an    integer  array↩︎        /* 줄바꿈 문자로 끝나야 한다 */
without   using bracket  operators↩︎    /* 마지막 행도 마찬가지이다 */

*/

#include <stdio.h>
#include <string.h>
#pragma warning (disable : 4996)

int main(void) {


	char buffer[20];
	char* words[100];

	int row, col;
	scanf("%d %d", &row, &col);

	int maxLen[10] = { 0 };
	//int maxLen[] = {0} 이렇게 하면 안 됨..

	//아... 열마다 maxLen을 다르게 해야하는구나..
	//col만큼의 maxLen.. col = 1일 떄, col = 2일 때, col = 3일 때...
	/* ex. 3x4 = 12이면
	col = 1 : 첫 번쨰 1열
	col = 5 : 두 번쨰 1열
	-> 4로 나눈 나머지가 1인 열(column), 4로 나눈 나머지가 2인 열, ... <- 그냥 for문 쓰기로 함.
	*/

	int l = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			scanf("%s", buffer);
			words[l] = strdup(buffer);
			if (strlen(buffer) > maxLen[j])
				maxLen[j] = strlen(buffer);
			l++;
		}
	}




	int m = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			printf("%s", words[m]);
			if (j == col - 1) {
				m++;
				break;
			}
			for (int k = 0; k < maxLen[j] - strlen(words[m]); k++)
				printf(" ");
			printf(" ");
			m++;
		}
		printf("\n");
	}


	return 0;
}


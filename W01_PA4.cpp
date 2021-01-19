//Date : Sep 12, 2020 11 : 59 pm

/*
입력으로 주어진 텍스트에 등장하는 서로 다른 단어의 개수를 카운트하여 출력하는 프로그램을 작성하라. 
입력 텍스트는 오로지 영문 소문자 혹은 대문자로만 구성되며, 단어를 비교할 때 대소문자 구분은 하지 않는다. 
즉 hello와 HeLLo는 동일한 단어로 간주한다. 입력은 표준입력파일로 부터 받으며,  입력의 끝은 EOF라는 단어로 표시된다. 
즉, EOF라는 문자열이 입력되면 입력이 끝난 것으로 간주하며, EOF 자체는 입력 단어로 간주하지 않다. 
입력되는 단어의 개수는 최대 100개이고, 각 단어의 길이는 20을 넘지 않는다.
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#pragma warning (disable : 4996)

#define BUFFER_SIZE 20

//void read_line(char str[], int limit);
int compare(char* a, char* b);

int main(void) {

	char buffer[20];

	char* words[100];
	char* unique_words[100];

	int n = 0;
	
	while (1) {
		//fgets(buffer, strlen(buffer), stdin);

		int flag = 0; //같은 게 아무것도 없는 상태.
		//read_line(buffer, BUFFER_SIZE);
		scanf("%s", buffer);

		if (strcmp(buffer,"EOF") == 0)
			break;



		if (n == 0) {
			unique_words[n++] = strdup(buffer);
		}
		else {
			for (int i = 0; i < n; i++) {
				if (compare(buffer, unique_words[i]) == 1) { //1이 비교결과가 같은 것
					//unique_words[n++] = strdup(buffer);
					flag = 1;
				}
			}

			if(flag == 0)
				unique_words[n++] = strdup(buffer);
		}
		//words[n++] = strdup(buffer);
	}
	

	/*
	unique_words[0] = strdup(words[0]);
	int m = 1;

	for (int i = 1; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (compare(words[i], unique_words[j]) == 0) { //0이 비교결과가 다른 것
				unique_words[m++] = strdup(words[i]); 
				break;
			}
		}
	}

	//문제 : 다 비교함. 이 중에 하나라도 있으면 괜찮은데 하나라도 다르면 다 카피함.
	//같은 게 하나라도 있으면 괜찮은 것. 달라도 괜찮음. 다 비교해볼때까지는 모름.
	//받자 마자 비교하고 flag 쓰는걸로 바꿈.
	//같을 경우 -> flag를 1로.

	*/


	printf("%d", n);

	return 0;
}

/*
void read_line(char str[], int limit) {
	int ch, i = 0;

	while ((ch = getchar()) != '\n')
		if (i < limit - 1)
			str[i++] = ch;
	str[i] = '\0';
}
*/

int compare(char* a, char* b) {

	//strcmp는 대문자와 소문자를 구분한다.
	for (int i = 0; i < strlen(a); i++) {
		a[i] = tolower(a[i]);
	}
	for (int i = 0; i < strlen(b); i++) {
		b[i] = tolower(b[i]);
	}

	if (strcmp(a, b) == 0)
		return 1;
	else
		return 0;
}

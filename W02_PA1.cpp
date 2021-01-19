//Date : Sep 20, 2020 11 : 59 pm

/*
영문 소문자로 구성된 하나의 단어를 입력받아서 단어에 포함된 문자들을 알파벳 순으로 정렬하여 출력하는 프로그램을 작성하라. 
예를 들어 hello가 입력되면 ehllo를 출력하면 된다. 단어의 길이는 최대 20이다.
*/

#include <stdio.h>
#include <string.h>

int main(void) {

	char word[21];
	scanf("%s", word);

	for (int i = strlen(word) - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (word[j] > word[j + 1]) {
				char tmp;
				tmp = word[j];
				word[j] = word[j + 1];
				word[j + 1] = tmp;
			}
		}
	}

	printf("%s", word);

	return 0;
}

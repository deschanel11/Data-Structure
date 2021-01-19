//

/*
입력으로 제공된 텍스트 파일 pride_and_prejudice.txt를 읽어서 이 파일에 등장하는 길이가 7이상인 모든 단어의 목록과 각 단어의 등장 빈도를 구하여 화면으로 출력하는 프로그램을 작성하라. 

프로그램 내에서 단어들은 강의 슬라이드 16페이지와 같은 자료구조로 저장되어야 한다.
대소문자의 구분은 없다. 출력에서 모든 단어들은 소문자로 구성되어야 한다. 
단어들은 사전식 순서로 정렬되어 출력되어야 한다. 
영문 알파벳이 하나도 포함되지 않은 문자열은 무시되어야 한다. 또한 단어의 앞과 뒤에 붙은 알파벳이 아닌 기호들은 제거되어야 한다. 예를 들어 쉼표, 마침표, 물음표 등은 제거되어야 한다.
단, 단어의 중간에 삽입된 따옴표(')와 하이픈(-)은 단어의 일부로 간주한다. 예를 들어 o'clock이나 brother's 혹은 breakfast-parlour 등은 그자체로 하나의 단어로 취급한다.  
하지만 단어의 중간에 따옴표(')와 하이픈(-)을 제외한 다른 기호나 혹은 따옴표(')와 하이픈(-)이라고 하더라도 
두 개 이상 연속될 경우에는 그것을 기준으로 문자열을 분리하여 2개의 별개의 단어로 취급한다. 
예를 들어 enough--one은 enough와 one이라는 2개의 단어로 취급한다. 가령 half-an-hour--was는 half-an-hour 와 was라는 2개의 단어로 취급한다.
출력은 화면으로 한다. 
한 줄에 하나의 단어와 그 단어의 등장 빈도를 출력하라. 
단어와 등장빈도 사이에 한 칸을 띄워라. 모든 단어를 출력하지말고 10개씩 건너띄어서 출력한다. 
즉, 정렬된 순서에서 1번째 단어, 11번째 단어, 21번째 단어,... 이런 식으로 출력한다.

출력 예:
absolutely 2
acquaint 1
adjusting 1
against 2
amusement 3
apothecary 1
arrived 1
astonished 1
authorized 1
bennet's 5
...
*/

//지난주와 같은 문제인데 문제를 좀 더 친절하게 설명해주심.
//다른 학생들이 더 시도해보기를 바라신 것 같음.

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#pragma warning (disable : 4996)


char buffer[100];
char* words_list[1000000];
int freq[1000000] = { 0 };
char * unique[1000000];

int main(void) {

	FILE* fp = fopen("Text.txt", "r");

	

	/*먼저 영문자가 하나도 없으면 무시하고
	아니라면 첫 혹은 마지막 알파벳이 나올때까지 떼어내야 한다.
		
	소문자로 변환해야 한다.*/

	int j = 0;
	while (fscanf(fp, "%s", buffer) != EOF) {

		int flag = 0;
		for (int i = 0; i < strlen(buffer); i++) {
			if (isalpha(buffer[i])) {	//**여기 들어오자 마자 assertion failure가 남....
				flag = 1;
				buffer[i] = tolower(buffer[i]);
			}
		}


		if (flag == 1) {//영문자가 하나라도 있다는 것. 이제 앞뒤에 알파벳 외 문자가 있는지 확인하고 없애야 함

			//알파벳인것만 뽑아서 저장 -> 안 됨. 중간에 다른문자 있으면 그것도 저장해야 함
			//*알파벳이 나오는 순간부터* 따로 저장
			//-> 끝에도 알파벳이 있는지 확인을 할 수 있어야 하는데..
			/*계속 저장하다가 마지막(\0)이 나왔는데 그 전 칸이 알파벳이 아닌 경우에는 알파벳이 나올 때 까지 앞으로 가기.*/


			char trimmed[100]; //처음과 끝에 알파벳만 있도록 뽑아내기.
			int i = 0, t = 0;
			while (buffer[i] != '\0') {
				/*치명적 실수..... "hi?" ?why? 같은 게 있다 치면 얘네는 여기서 계속 돌게 됨...
				그러면 계속 두줄 왔다갔다함.
				왜냐면 i도 증가하지 않고 t도 증가하지 않으니까... 최소한 i는 증가를 해야 함.
				if (isalpha(buffer[i]) || (!isalpha(buffer[i]) && t>0))
					trimmed[t++] = buffer[i++]; //여기서 알파벳이 아닌 끝도 다 저장해놓고 ++함. \0자리를 가리키게 된 것.
				*/
			
				
				if (t == 0 && !isalpha(buffer[i])) { //이 조건을 걸어주면
					i++;
					continue;
				}
				if (isalpha(buffer[i]) || (!isalpha(buffer[i]) && t > 0)) //여기서 || 뒷부분은 필요없나..? -> 웅.. 그치만 그래도..
					trimmed[t++] = buffer[i++];
					//뭐가 또 문제여서 "whyisthat?"은 안뜨지?
				
			
			
			}
			while (!isalpha(trimmed[t-1]))
				t--; //바로 앞자리가 알파벳이 나올 때 까지 계속해서 \0의 자리가 하나씩 앞으로 가는 것.

			trimmed[t] = '\0';

			if (strlen(trimmed) >= 7) {//strlen()-1 하면 안 됨. 알아서 '\0' 빼고 세나봄.
				words_list[j++] = strdup(trimmed);
				trimmed[0] = '\0'; //hello에서 끔찍한 일이 생겨버림.
			}

		}
	}

	//이제 유효한 단어는 다 저장했음.
	//빈도를 구해야 함. freq[] 배열에 저장.



	//words_list를 사전식 순서로 정렬해야 함
	//일단 정렬을 하고 난 뒤에 개수를 세어야 함.
	//정렬을 하면서 하면(개수를 세면).. 당장 두개가 같을때는 괜찮지만 나중에 또 다르면... 엄청 복잡해짐.

	//그치만 그러려면 unique 배열도 이미 정렬이 다 끝난 상태여야 함.


	for (int i = j-1; i > 0; i--) {
		for (int k = 0; k < i; k++){
			if (strcmp(words_list[k], words_list[k + 1]) > 0) {
				char* tmp = words_list[k];
				words_list[k] = words_list[k + 1];
				words_list[k + 1] = tmp;
			}
		}
	}

	//10개씩 띄어서 출력하려면 unique 배열도 따로 있어야 함.
	//이제 개수.

	//언제까지 세고 언제부터 0으로 초기화할지가 중요함.★☆★☆★☆

	/*strcmp 결과가 == 0인 동안 해당 freq++
	!= 0 이면 unique배열에 넣음. 해당 freq ++.
	일단 unique 배열에 하나는 넣고 시작해야 함.
	*/

	/*
	for (int i = 0; i < j; i++) {
		printf(words_list[i]);
		printf("\n");
	}
	printf("***\n");
	*/






	int m = 0;
	unique[m] = words_list[0]; freq[m]++;

	
	for (int i = 1; i < j; i++) { //words_list를 다 돌면서 빈도를 세고, unique에 저장해 준다.
		if (strcmp(unique[m], words_list[i]) == 0) {
			freq[m]++;
		}
		else {
			m++;
			unique[m] = strdup(words_list[i]);
			freq[m]++;
		}
	}






	
	for (int i = 0; i <= m; i++) {
		if (i % 10 == 0)
			printf("%s %d\n", unique[i], freq[i]);
	}

	/*
	for (int i = 0; i < j; i++) {
		printf(words_list[i]);
		printf("\n");
	}
	printf("***\n");
	*/

	/*
	for (int i = 0; i <= m; i++) { //m++는 꼭 필요할 때만 일어남. ++하고 끝이 아님. 따라서 <m이 아니라 <=m이어야 함.
		printf("%s %d\n", unique[i], freq[i]);
	}
	*/

	fclose(fp);

	return 0;
}


/*
좋은 친구가 되어준 테스트 텍스트 파일
"hello,areyouokay?"
"whyisthat?"
absolutely
absolutely
against
amongst
against
amongst
anything

arrival
arrival
anything
acquaint
adjusting
anything
anything
o'clock
brother's
break*-,!fast--parlour
/
*/

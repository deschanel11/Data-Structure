//Date : Sep 20, 2020 11 : 59 pm

/*
어떤  앨범의 수록곡 목록이 입력으로 주어진다. 
입력의 각 라인은 하나의 음원 파일명이며, 그 형식은 예를 들어 다음과 같다:

11
134340 - BTS - #4.mp3
Airplane Pt. 2 - BTS - #8.mp3
Anpanman - BTS - #9.mp3
Fake Love - BTS - #2.mp3
Intro: Singularity - BTS - #1.mp3
Love Maze - BTS - #6.mp3
Magic Shop - BTS - #7.mp3
Outro: Tear - BTS - #11.mp3
Paradise - BTS - #5.mp3
So What - BTS - #10.mp3
The Truth Untold - BTS - #3.mp3
우선 입력의 첫 줄에는 앞으로 입력될 라인의 개수 N<100이 주어진다. 이어진 N라인에는 한 줄에 하나씩 음원 파일명이 주어진다. 즉, 각 음원 파일명은  "제목",  "아티스트", 그리고 "트랙 번호"의 3개의 필드로 구성되고, 필드들은 한 칸의 공백, 하이픈(-), 그리고 다시 하나의 공백으로 구분되어 있다. 파일명의 확장자는 모두 mp3이다.  각 라인들을 다음과 같은 포맷으로 수정하고, 라인들을 사전식 순서로 정렬하여 출력하여야 한다. 

01-Intro: Singularity-BTS.mp3
02-Fake Love-BTS.mp3
03-The Truth Untold-BTS.mp3
04-134340-BTS.mp3
05-Paradise-BTS.mp3
06-Love Maze-BTS.mp3
07-Magic Shop-BTS.mp3
08-Airplane Pt. 2-BTS.mp3
09-Anpanman-BTS.mp3
10-So What-BTS.mp3
11-Outro: Tear-BTS.mp3
즉,  필드들은 "트랙번호-제목-아티스트" 순서로 재배열 되어야 하고, 트랙번호는 반드시 2자리 정수로 표현되어야 하며, 하이픈의 좌우에 있던 공백들과 트랙 번호 앞에 붙어있던 # 문자는 모두 제거되어야 한다. 
*/



#include <stdio.h>
#include <string.h>
#include <stdlib.h> //atoi함수를 사용하기 위한 것.
#include <ctype.h>
#pragma warning(disable:4996)
#define BUFFER_SIZE 200

//void trim(char buffer[]);

char buffer[200];
char* playlist[100]; //N < 100

char* named[100];
char* artist_[100];
int t_number[100]; //track number

int main(void) {

	//일단은 받는 걸 한번에 다 끝내는 게 좋겠지?

	//그 다음에는 tokenizing을 해야 하겠지? ' - '으로?
	//각 필드를 다른 자료구조에 저장해야 하겠지?
	//사전식으로 정렬 할 때는 같은 인덱스 묶음끼리는 항상 같이 옮겨주고..
	//그래도 한꺼번에 다 받고 정렬하기 때문에 한 번만 정렬하면 됨!

	//제목, 아티스트, 트랙 번호 순으로 구성된 라인이 입력됨.
	// -> 트랙번호, 제목, 아티스트 순으로. (출력은 어렵지 않음.)
	//출력을 문자열을 아예 갖춰서 출력할 것이냐, 순서만 갖춰서 '-'는 따로 입력할 것이냐에 따라 달라짐.
	//여기서 sprintf를 써야 하나..?


	//받을 때 토크나이징을 다 해서 받는 게 좋겠지?
	//정렬도 그냥 받으면 그때그때 하면 좋을텐데.. -> 아님.
	//sprintf는 그럼 언제 하면 제일 좋을까? 정렬을 한 다음?
	//(출력 직전에 하면 sprintf를 하는 의미가 없을 것 같다 -> '알맞은 자료구조에 저장'에 의의가 있는 건가?)

	//#를 떼어내는 건 언제 하면 좋을까? -> 토크나이징 직후?
	//트랙 넘버 2자리로 출력하는 것도 sprintf로?


	int N;
	scanf("%d ", &N); //띄어쓰기 안해주면 fgets가 여기서 받은 \n을 인식해버림.

	char delim[] = "-";

	for (int i = 0; i < N; i++) {
		fgets(buffer, BUFFER_SIZE, stdin);
		buffer[strlen(buffer) - 1] = '\0'; //fgets는 줄바꿈 문자까지 저장하기 때문.

		char* name;
		name = strtok(buffer, delim); //strdup를 사용하지 않아도 되는걸까..? buffer의 주소는 변하지 않으니까 써야겠지?

		//trim(name);


		char trimmed[100]; //처음과 끝에 있는 공백문자를 없애기.
		int k = 0, t = 0;
		while (name[k] != '\0') {
			if (t == 0 && isspace(name[k])) { //이 조건을 걸어주면
				k++;
				continue;
			}
			if (!isspace(name[k]) || (isspace(name[k]) && t > 0))
				trimmed[t++] = name[k++];
		}

		while (isspace(trimmed[t - 1]))
			t--; //바로 앞자리가 white space가 아닌 게 나올 때 까지 계속해서 \0의 자리가 하나씩 앞으로 가는 것.

		trimmed[t] = '\0';


		//printf("%s", name);

		named[i] = strdup(trimmed);
		//printf("%s,", named[i]);


		char *artist;

		artist = strtok(NULL, delim);




		//trim(artist);
		k = 0, t = 0;
		while (artist[k] != '\0') {
			if (t == 0 && isspace(artist[k])) { //이 조건을 걸어주면
				k++;
				continue;
			}
			if (!isspace(artist[k]) || (isspace(artist[k]) && t > 0))
				trimmed[t++] = artist[k++];
		}

		while (isspace(trimmed[t - 1]))
			t--; //바로 앞자리가 white space가 아닌 게 나올 때 까지 계속해서 \0의 자리가 하나씩 앞으로 가는 것.

		trimmed[t] = '\0';

		artist_[i] = strdup(trimmed);

		//printf("%s,", artist_[i]);


		char *number;
		char trimmed_number[5];

		number = strtok(NULL, delim); //이 때 number에는 #가 포함된 "문자열"이 저장되게 된다. ex) #4.mp3, #8.mp3, #11.mp3..

		k = 0;
		int flag = 0; //만약에 flag가 1 됐고, 그 이후로 non digit이 나왔는데 또 다시 digit이 나왔다 -> 저장 x
		for (int j = 0; j < strlen(number); j++) {
			if ((isdigit(number[j])&& k == 0) || (isdigit(number[j]) && flag == 1 && isdigit(number[j - 1]))) { //10, 11같은 경우를 조심해야 함..
				trimmed_number[k++] = number[j];
				flag = 1;
			}
		}
		trimmed_number[k] = '\0';
		t_number[i] = atoi(trimmed_number);

		//printf("%d,", t_number[i]);
		

	}
	//트랙 넘버로 정렬을 할 때, 문자열로 저장된 트랙 넘버를 어떻게 정수로 바꾸면 좋을까? -> atoi함수 이용.
	//아니면 아예 저장할 때도 atoi로 변경해서 정수로 저장해주는 게 좋은 걸까? -> yes.


	//이제 트랙 넘버로 정렬을 해 줘야 함.

	
	
	for (int i = N-1; i > 0;i--) {
		for (int j = 0; j < i;j++) {
			if (t_number[j] > t_number[j + 1]) {
				char *name_tmp;
				char *artist_tmp;
				int number_tmp;
				name_tmp = named[j], artist_tmp = artist_[j], number_tmp = t_number[j];
				named[j] = named[j + 1], artist_[j] = artist_[j + 1], t_number[j] = t_number[j + 1];
				named[j + 1] = name_tmp, artist_[j + 1] = artist_tmp, t_number[j + 1] = number_tmp;
			}
		}
	}

	//이제 sprintf를 이용해서 정렬 된 순서대로 저장해줌.
	//최종 정렬된 문자열들을 저장할 자료구조가 필요함. -> char *playlist[100]


	/* 여기서 오류가 남.
	for (int i = 0; i < N; i++) {
		sprintf(playlist[i], "%d-%s-%s.mp3", t_number[i], named[i], artist_[i]);
	}
*/
	/*
	for (int i = 0; i < N; i++) {
		printf("%s", playlist[i]);
	}
*/

	for(int i=0;i<N;i++)
		printf("%02d-%s-%s.mp3\n", t_number[i], named[i], artist_[i]);


	return 0;
}

/*
void trim (char buffer[]){

	char trimmed[30]; //처음과 끝에 있는 공백문자를 없애기.
	int i = 0, t = 0;
	while (buffer[i] != '\0') {
		if (t == 0 && isspace(buffer[i])) { //이 조건을 걸어주면
			i++;
			continue;
		}
		if (!isspace(buffer[i]) || (isspace(buffer[i]) && t > 0))
			trimmed[t++] = buffer[i++];
	}

	while (isspace(trimmed[t - 1]))
		t--; //바로 앞자리가 white space가 아닌 게 나올 때 까지 계속해서 \0의 자리가 하나씩 앞으로 가는 것.

	trimmed[t] = '\0';



	//buffer = trimmed; 그치.. 버퍼는 지역변수일 뿐이니까....
	//이걸 어떻게 main에 전해주지..?


}*/



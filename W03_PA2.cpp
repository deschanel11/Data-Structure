
//W03_Ex1번과 동일한 문제를 풀어라. 단, 이번에는 다음과 같이 MyDate* 타입의 배열을 사용하라.

//typedef struct {
//int year, month, day, hour, minute, second;
/* add other members if you want */
//} MyDate;

//MyDate *dates[MAX]; /* MyDate 포인터 타입의 배열에 시간 데이터를 저장하라. */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 200
#define BUFFER_SIZE 200


typedef struct {
	int year, month, day, hour, minute, second;
}MyDate;

MyDate *dates[MAX]; //MyDate 타입의 배열에 시간 데이터 저장.

char buffer[200];



int main(void) {

	int n;
	scanf("%d ", &n);

	char delim[] = "/:[]";

	//시간 표현 형식을 "년-월-일:시:분:초" 로 변경

	for (int i = 0; i < n; i++) {

		fgets(buffer, BUFFER_SIZE, stdin);
		buffer[strlen(buffer) - 1] = '\0'; //fgets는 줄바꿈 문자까지 저장하니까.


		dates[i] = (MyDate*)malloc(sizeof(MyDate));


		char* day = strtok(buffer, delim);
		int day_;
		day_ = atoi(day);
		dates[i] -> day = day_; //malloc으로 구조체 생성 따로 안 하면 여기서 바로 에러가 발생함.

		char* month = strtok(NULL, delim);

		if (strcmp(month, "Jan") == 0) dates[i] -> month = 1;
		else if (strcmp(month, "Feb") == 0) dates[i]->month = 2;
		else if (strcmp(month, "Mar") == 0) dates[i]->month = 3;
		else if (strcmp(month, "Apr") == 0) dates[i]->month = 4;
		else if (strcmp(month, "May") == 0) dates[i]->month = 5;
		else if (strcmp(month, "Jun") == 0) dates[i]->month = 6;
		else if (strcmp(month, "Jul") == 0) dates[i]->month = 7;
		else if (strcmp(month, "Aug") == 0) dates[i]->month = 8;
		else if (strcmp(month, "Sep") == 0) dates[i]->month = 9;
		else if (strcmp(month, "Oct") == 0) dates[i]->month = 10;
		else if (strcmp(month, "Nov") == 0) dates[i]->month = 11;
		else if (strcmp(month, "Dec") == 0) dates[i]->month = 12;


		char* year = strtok(NULL, delim);
		dates[i]->year = atoi(year);

		char* hour = strtok(NULL, delim);
		dates[i]->hour = atoi(hour);

		char* minute = strtok(NULL, delim);
		dates[i]->minute = atoi(minute);

		char* second = strtok(NULL, delim);
		dates[i]->second = atoi(second);

	}



	//시간 순으로 정렬.
	//먼저 년도로 정렬하고, 그 다음 달, 일, 시, 분 초 순으로



	//about second
	for (int i = n - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (dates[j]->second > dates[j + 1]->second) {
				MyDate* tmp = dates[j];
				dates[j] = dates[j + 1];
				dates[j + 1] = tmp;
			}
		}
	}


	//about minute
	for (int i = n - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (dates[j]->minute > dates[j + 1]->minute) {
				MyDate* tmp = dates[j];
				dates[j] = dates[j + 1];
				dates[j + 1] = tmp;
			}
		}
	}

	//about hour
	for (int i = n - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (dates[j]->hour > dates[j + 1]->hour) {
				MyDate* tmp = dates[j];
				dates[j] = dates[j + 1];
				dates[j + 1] = tmp;
			}
		}
	}

	//about day
	for (int i = n - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (dates[j]->day > dates[j + 1]->day) {
				MyDate* tmp = dates[j];
				dates[j] = dates[j + 1];
				dates[j + 1] = tmp;
			}
		}
	}

	//about month
	for (int i = n - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (dates[j]->month > dates[j + 1]->month) {
				MyDate* tmp = dates[j];
				dates[j] = dates[j + 1];
				dates[j + 1] = tmp;
			}
		}
	}

	//about year
	for (int i = n - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (dates[j]->year > dates[j + 1]->year) {

				MyDate* tmp = dates[j];
				dates[j] = dates[j + 1];
				dates[j + 1] = tmp;
			}
		}
	}





	for (int i = 0; i < n; i++) {
		printf("%d-%02d-%02d:%02d:%02d:%02d\n", dates[i]->year, dates[i]->month, dates[i]->day, dates[i]->hour, dates[i]->minute, dates[i]->second);
	}


	return 0;
}


Date : Oct 04, 2020 11 : 59 pm

/*
아래와 같은 형식으로 시간 데이터가 표현된다.

[일/월/년:시:분:초]

먼저 입력 데이터의 개수 n이 주어지고 이어서 위와 같은 형식으로 표현된 n개의 시간 데이터가 한 줄에 하나씩 입력된다. 
이 시간 데이터들을 시간 순으로 정렬하여 출력하는 프로그램을 작성하라. 
단, 출력에서 시간의 표현 형식은 아래의 예와 같이 “년-월-일:시:분:초”로 변경되어야 하며, 월, 일, 시, 분, 초는 2자리 정수로 출력해야 한다. 
다음과 같이 하나의 시간 데이터를 저장하기 위한 구조체를 정의해서 사용하라.

typedef struct {
int year, month, day, hour, minute, second;
/* add other members if you want */
} MyDate;
MyDate dates[MAX]; /* MyDate 타입의 배열에 시간 데이터를 저장하라. */

입력 예:
12
[29/Jan/2018:20:41:46]
[17/Nov/2017:18:03:26]
[12/Nov/2017:11:18:40]
[29/Jan/2018:20:18:48]
[30/Nov/2017:13:01:30]
[29/Jan/2018:20:20:52]
[30/Nov/2017:17:23:50]
[03/Dec/2017:10:19:29]
[16/Nov/2017:19:51:59]
[29/Jan/2018:20:48:22]
[30/Nov/2017:16:30:52]
[22/Feb/2018:13:01:21]

출력 예:
2017-11-12:11:18:40
2017-11-16:19:51:59
2017-11-17:18:03:26
2017-11-30:13:01:30
2017-11-30:16:30:52
2017-11-30:17:23:50
2017-12-03:10:19:29
2018—01-29:20:18:48
2018-01-29:20:20:52
2018-01-29:20:41:46
2018-01-29:20:48:22
2018-02-22:13:01:21
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 200
#define BUFFER_SIZE 200


typedef struct {
	int year, month, day, hour, minute, second;
	
}MyDate;

MyDate dates[MAX]; //MyDate 타입의 배열에 시간 데이터 저장.

char buffer[200];

int main(void) {

	int n;
	scanf("%d ", &n);

	char delim[] = "/:[]";

	//시간 표현 형식을 "년-월-일:시:분:초" 로 변경

	for (int i = 0; i < n; i++) {

		fgets(buffer, BUFFER_SIZE, stdin);
		buffer[strlen(buffer) - 1] = '\0'; //fgets는 줄바꿈 문자까지 저장하니까.

		char* day = strtok(buffer, delim);
		dates[i].day = atoi(day);

		char* month = strtok(NULL, delim);

		if (strcmp(month, "Jan") == 0) dates[i].month = 1;
		else if(strcmp(month, "Feb")==0) dates[i].month = 2;
		else if (strcmp(month, "Mar") == 0) dates[i].month = 3;
		else if (strcmp(month, "Apr") == 0) dates[i].month = 4;
		else if (strcmp(month, "May") == 0) dates[i].month = 5;
		else if (strcmp(month, "Jun") == 0) dates[i].month = 6;
		else if (strcmp(month, "Jul") == 0) dates[i].month = 7;
		else if (strcmp(month, "Aug") == 0) dates[i].month = 8;
		else if (strcmp(month, "Sep") == 0) dates[i].month = 9;
		else if (strcmp(month, "Oct") == 0) dates[i].month = 10;
		else if (strcmp(month, "Nov") == 0) dates[i].month = 11;
		else if (strcmp(month, "Dec") == 0) dates[i].month = 12;


		char* year = strtok(NULL, delim);
		dates[i].year = atoi(year);

		char* hour = strtok(NULL, delim);
		dates[i].hour = atoi(hour);

		char* minute = strtok(NULL, delim);
		dates[i].minute = atoi(minute);

		char* second = strtok(NULL, delim);
		dates[i].second = atoi(second);

	}

	

	//시간 순으로 정렬.
	//먼저 년도로 정렬하고, 그 다음 달, 일, 시, 분 초 순으로



	//about second
	for (int i = n - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (dates[j].second > dates[j + 1].second) {
				MyDate tmp = dates[j];
				dates[j] = dates[j + 1];
				dates[j + 1] = tmp;
			}
		}
	}

	//about minute
	for (int i = n - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (dates[j].minute > dates[j + 1].minute) {
				MyDate tmp = dates[j];
				dates[j] = dates[j + 1];
				dates[j + 1] = tmp;
			}
		}
	}

	//about hour
	for (int i = n - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (dates[j].hour > dates[j + 1].hour) {
				MyDate tmp = dates[j];
				dates[j] = dates[j + 1];
				dates[j + 1] = tmp;
			}
		}
	}

	//about day
	for (int i = n - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (dates[j].day > dates[j + 1].day) {
				MyDate tmp = dates[j];
				dates[j] = dates[j + 1];
				dates[j + 1] = tmp;
			}
		}
	}

	//about month
	for (int i = n - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (dates[j].month > dates[j + 1].month) {
				MyDate tmp = dates[j];
				dates[j] = dates[j + 1];
				dates[j + 1] = tmp;
			}
		}
	}

	//about year
	for (int i = n - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (dates[j].year > dates[j + 1].year) {

				MyDate tmp = dates[j];
				dates[j] = dates[j + 1];
				dates[j + 1] = tmp;
			}
		}
	}


	
	for (int i = 0; i < n; i++) {
		printf("%d-%02d-%02d:%02d:%02d:%02d\n", dates[i].year, dates[i].month, dates[i].day, dates[i].hour, dates[i].minute, dates[i].second);
	}
	

	return 0;
}

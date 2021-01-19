

webLog.csv 파일이 주어져 있다. 이 파일은 어떤 사이트의 웹 로그를 기록한 csv 파일이다. 파일의 각 라인마다 하나의 로그 정보가 저장된다. 각각의 로그 정보는 IP, Time, URL, 그리고 Status의 4가지 항목으로 구성되고, 항목들은 콤마(,)로 구분되어 있다. 파일의 첫 줄은 항목의 이름이므로 무시한다. 이 파일을 읽은 후 다음과 같은 명령을 처리하는 프로그램을 작성하라. 

프로그램을 실행하면 프롬프트($ )를 출력하고 사용자의 명령을 대기한다. 
사용자의 명령은 search와 exit이다. search는 주어진 조건에 따라서 로그를 검색하는 기능을 수행하고 exit은 프로그램을 종료한다. 
search 명령은 -date 옵션과 -ip 옵션을 지원한다. 
-date 옵션은 날짜 범위를 매개변수로 입력받은 후 그 날짜 범위 안에서 사이트에 접속한 모든 ip 주소를 찾아내어 접속 횟수에 대해 내림차순으로 정렬하여 출력한다. 
-ip 옵션은 ip 주소를 매개변수로 받아서 그 ip 주소에 해당하는 모든 로그 기록들을 시간 순으로 정렬하여 출력한다. 예를 들어 다음과 같이 작동한다.  

$ search -date 03/Dec/2017 16/Jan/2018           /* 날짜는 이런 형식으로 받는다. */
24 ips found:                                    /* 총 ip주소의 개수를 출력한다. */
10.129.2.1: 10                                   /* ip 주소와 접속 횟수를 접속 횟수에 */
10.111.2.1: 9                                    /* 대한 내림차순으로 정렬하여 출력한다. */
10.127.2.1: 9                                    /* 접속 회수가 동일한 ip들은  */
10.111.0.1: 8                                    /* ip 주소의 사전식 순서로 정렬한다. */
10.120.2.1: 7
10.121.2.1: 7
10.123.2.1: 7
…
$ search -ip 10.129.2.1
94 logs found                                    /* 발견된 로그의 개수를 출력한다. */
[09/Nov/2017:10:27:48],GET / HTTP/1.1,302
[09/Nov/2017:14:39:53],GET /login.php?value=fail HTTP/1.1,200
[11/Nov/2017:19:47:07],GET /archive.php HTTP/1.1,200
[12/Nov/2017:12:58:13],GET /home.php HTTP/1.1,200
[12/Nov/2017:15:51:21],GET /login.php HTTP/1.1,200  
[13/Nov/2017:17:58:27],GET /css/main.css HTTP/1.1,200
[16/Nov/2017:15:51:03],GET /css/main.css HTTP/1.1,304
[16/Nov/2017:16:12:16],GET /css/bootstrap.min.css HTTP/1.1,304
[17/Nov/2017:13:29:53],GET /contestsubmission.php?id=13 HTTP/1.1,200
[18/Nov/2017:07:36:49],GET / HTTP/1.1,200
…                                             /* 로그 들은 시간 순으로 출력되어야 한다. */
$ exit                                        /* 프로그램을 종료한다. */



#include <stdio.h>
#include <string.h>
#include <stdlib.h> //for malloc
#pragma warning (disable:4996)
#define BUFFER_LENGTH 300
#define MAX 2000 //파일이 총 1499줄이었음.

int read_line(FILE* fp, char str[], int n);
void do_search(char * argument);
int compare_time(char* str1, char*str2);
int compare_time_2(char* str1, char*str2);
int n = 0;


typedef struct {
	char* IP, *Time, *URL, *Status;
}webLog;

webLog *data[MAX];

//문제 : 날짜로 크기비교를 해야하는데 문자열로 저장돼있음.
//시간을 비교할 수 있는 함수같은 게 있어야 함.
//시간에서 []를 떼어낼 수 있어야 함. -> strtok을 사용할 것인가? ->yes.
//

int main(void) {

	FILE* fp = fopen("webLog.csv", "r");

	char buffer[BUFFER_LENGTH];
	char delim[] = ",";

	read_line(fp, buffer, BUFFER_LENGTH);

	
	while (1) {
		if (read_line(fp, buffer, BUFFER_LENGTH) <= 0)
			break;

		data[n] = (webLog *)malloc(sizeof(webLog));

		char* IP, *Time, *URL, *Status;

		IP = strtok(buffer, delim);
		data[n]->IP = strdup(IP);

		Time = strtok(NULL, delim);
		data[n]->Time = strdup(Time);

		URL = strtok(NULL, delim);
		data[n]->URL = strdup(URL);

		Status = strtok(NULL, delim);
		data[n]->Status = strdup(Status);

		n++; //이거 안해서 큰일날뻔 함
	}
	fclose(fp);

	/*
	for (int i = 0; i < n; i++)
		printf("IP : %s, Time : %s, URL : %s, Status : %s\n", dates[i]->IP, dates[i]->Time, dates[i]->URL, dates[i]->Status);
	*/


	char command_line[BUFFER_LENGTH];
	char *command, *argument;

	while (1) {
		printf("$ ");
		if (read_line(stdin, command_line, BUFFER_LENGTH) <= 0)
			continue;

		command = strtok(command_line, " ");

		if (strcmp(command, "search") == 0) {
			argument = strtok(NULL, " ");
			if (argument == NULL) {
				printf("Invalid arguments.\n");
				continue;
			}
			do_search(argument);
		}
		else if (strcmp(command, "exit") == 0)
			break;
	}

	return 0;
}

int read_line(FILE* fp, char str[], int n)
{
	int ch, i = 0;

	while ((ch = fgetc(fp)) != '\n' && ch != EOF)
		if (i < n)
			str[i++] = ch;

	str[i] = '\0';
	return i;
}


void do_search(char * argument)
{
	char *argument1, *argument2;
	   
	if (strcmp(argument, "-date") == 0) {

		argument1 = strtok(NULL, " ");
		argument2 = strtok(NULL, " ");

		/*argument1, 2랑 비교를 하려면 Time 데이터가 정리가 돼있어야함..
		아니면 Time 데이터를 그때그때 불러와서 비교할 수 있어야 함.*/

		//아니면 둘 다 string이니까 괜찮은가..? 주어지는 범위는 시, 분, 초는 따지지 않음. 날짜만 비교하면 됨.
		//그러면 []:로 strtok를 하면 되겠다..!

		//날짜는 앞이 더 과거, 뒤는 더 가까운 과거로 딱 그 범위만큼 주는 것 같다.
		//argument1보다 크거나 같고, argument2보다 작거나 같은 줄에서 IP주소만 가져오면 된다. 
		//대신 ★접속회수★에 대한 내림차순으로!!

		webLog *valid_data[2000]; //날짜에 해당하는 로그들
		webLog *unique[2000];
		int freq[2000] = { 0 }; //unique IP별 개수를 기록해줌.

		//malloc으로 항상 생성해줘야하는 걸 잊지 않기! ->여기서는 근데 이미 있는 걸 같이 가리키는 거니까 필요 없음.

		int k = 0;
		for (int i = 0; i < n; i++) {
			
			char *Time_ = strdup(data[i]->Time); //strtok은 원본 문자열을 변형시키니까.
			//Time_ = strtok(Time_, "[]:"); <= 이렇게 하면 안됨.. 그러면 -date 했다가 -ip하면 Time에 변형이 일어나버려서 또 에러남..

			Time_ = strtok(Time_, "[]:");

			/*argument들이랑 어떻게 비교할지를 생각해야 함. ★일단은 년 월 일만 떼어냈고★, 
			다행히 주는 날짜랑 갖고있는 날짜의 형식이 같음.
			하지만... 날짜 형식이 '일/월/년'인데 월이 영어로 돼있기때문에 따로 떼어내서 숫자화를 해야 함.. ㅜㅜ
			=> 결국 Time은 숫자 date, month, year로 다 쪼개서 따로 저장해야 하는건가...? */

			//아니면 아예 시간 비교해주는 함수를 만들면..??

			//Time_ >= argument1 && Time_ <= argument2
			if (((compare_time(Time_, argument1)>0||compare_time(Time_, argument1) == 0)) && ((compare_time(Time_, argument2)<0 || compare_time(Time_, argument2) == 0))) {
				//여기서 이 조건을 만족하는 data[i]들을 다 찾아서 따로 얘네를 가리킬 수 있는 배열을 만들어야 함.
				//그 배열을 내림차순으로 정렬해서 각각 횟수를 세야 함. 일전에 했던 1주차 4, 5번처럼!

				valid_data[k++] = data[i];

			}

		}

		//k--;

		//이제 valid_data를 접속 회수에 대한 내림차순으로 정렬해야 함.
		//먼저 쉽게 IP주소별 빈도수를 세려면 IP순으로(!!!) 정렬을 해야 함. (오 세상에...이번엔 그냥 정렬하지 말까..?)
		//(아닌가 어차피 strcmp로 정렬할거같으면 쉬우려나...?) ->그냥 정렬 안하기로 함. for문 두개 돌리기...

		int m = 0;
		unique[m] = valid_data[0];
		freq[m]++;
		m++;

		//아 맞아..... flag가 있어야 함....(x) continue문을 쓰면 됨. <= 정렬을 안해서 일어나는 문제인가...?

		//지금 valid_data의 원소 개수는 k개.
		for (int i = 1; i < k; i++) {
			int flag = 0;
			for (int j = 0; j < m; j++) {
				//여기서 엄청 여러번 저장해버리는구나... 한번 저장을 했는데도 계속 검사해서.... ->그럼 있지도 않은 2000 초과 자리에 저장하려 하고 엑세스 오류 날 만 함..
				if (strcmp(valid_data[i]->IP, unique[j]->IP) == 0) {
					freq[j]++;
					flag = 1;
					break;
				}
			}
			if (flag == 0) {
				unique[m] = valid_data[i];
				freq[m]++;
				m++;
			}
		}

		//m--;

		//이제 횟수를 토대로 IP를 정렬을 해야 함. -> unique배열이 갖고 있으니 unique를 정렬하면 됨.

		//횟수가 같으면 IP순 정렬이니 먼저 IP순대로도 정렬을 해야 함...

		for (int i = m - 1; i > 0; i--) {
			for (int j = 0; j < i; j++) {
				if (strcmp(unique[j]->IP, unique[j + 1]->IP) < 0) { //내림차순 정렬 안하려고 출력을 거꾸로 하니까 얘도 거꾸로..^^
					webLog* tmp;
					tmp = unique[j];
					unique[j] = unique[j + 1];
					unique[j + 1] = tmp;

					int tmp2 = freq[j];
					freq[j] = freq[j + 1];
					freq[j + 1] = tmp2;
				}
			}
		}


		for (int i = m-1; i > 0 ; i--) {
			for (int j = 0; j < i; j++) {
				if (freq[j] > freq[j + 1]) {
					webLog* tmp;
					tmp = unique[j];
					unique[j] = unique[j + 1];
					unique[j + 1] = tmp;

					int tmp2 = freq[j];
					freq[j] = freq[j + 1];
					freq[j + 1] = tmp2;

				}
			}
		}

		printf("%d ips found:\n", m);
		for (int i = m - 1; i >= 0; i--)
			printf("%s: %d\n", unique[i]->IP, freq[i]);

	}
	else if (strcmp(argument, "-ip") == 0) { //왜 ==를 쓰면 안되느걸까..?
		
	//이 argument1이 IP주소이다.
	argument1 = strtok(NULL, " ");


		webLog *valid_data[2000];

		int k = 0;
		for (int i = 0; i < n; i++) {
			if (strcmp(data[i]->IP, argument1) == 0)
				valid_data[k++] = data[i];
		}

		//k--;
		
		//이제 시간 순으로 정렬해야 함.
		//여기서는 년도, 월, 일 뿐만 아니라 시, 분, 초도 고려해줘야 함.
		//compare함수를 하나 더 만들어야 할 것 같다. 거기서는 시, 분 초까지도 tokenizing을 해서 비교하면 될 것 같다.
		//함수이름 : compare_time_2
		
		for (int i = k-1; i > 0; i--) { //세상에.. i++로 해놓음.
			for (int j = 0; j < i; j++) {
				if (compare_time_2(valid_data[j]->Time, valid_data[j + 1]->Time) > 0) {
					webLog* tmp;
					tmp = valid_data[j];
					valid_data[j] = valid_data[j + 1];
					valid_data[j + 1] = tmp;
				}
			}
		}



		printf("%d logs found\n", k);

		for (int i = 0; i < k; i++) {
			printf("%s,%s,%s\n", valid_data[i]->Time, valid_data[i]->URL, valid_data[i]->Status);
		}

	}

	return;
}

int compare_time(char* str1_, char*str2_) {

	//시간은 이제 /로 일, 월, 년이 구분되어 있음.
	char* str1 = strdup(str1_); //보존의 의미 -> compare_Time함수 호출이 같은 string으로 여러번 일어나기 때문에 필요함.
	char* str2 = strdup(str2_);

	char *day_, *month_, *year_, *day2_, *month2_, *year2_;

	day_ = strtok(str1, "/"); int day = atoi(day_);

	month_ = strtok(NULL, "/");
	month_ = strdup(month_);

	int month;

	
	if (strcmp(month_, "Jan") == 0) month = 1; //★★여기서 왜 예외가....? ★★여기서 month_가 NULL로 바뀜. => compar_Time함수를 한번 호출하고 나면 호출자쪽 str이 변형돼버려서 그럼.
	else if (strcmp(month_, "Feb") == 0) month = 2;
	else if (strcmp(month_, "Mar") == 0) month = 3;
	else if (strcmp(month_, "Apr") == 0) month = 4;
	else if (strcmp(month_, "May") == 0) month = 5;
	else if (strcmp(month_, "Jun") == 0) month = 6;
	else if (strcmp(month_, "Jul") == 0) month = 7;
	else if (strcmp(month_, "Aug") == 0) month = 8;
	else if (strcmp(month_, "Sep") == 0) month = 9;
	else if (strcmp(month_, "Oct") == 0) month = 10;
	else if (strcmp(month_, "Nov") == 0) month = 11;
	else if (strcmp(month_, "Dec") == 0) month = 12;

	year_ = strtok(NULL, "/");	int year = atoi(year_);

	day2_ = strtok(str2, "/");	int day2 = atoi(day2_);

	month2_ = strtok(NULL, "/");
	int month2;

	if (strcmp(month2_, "Jan") == 0) month2 = 1;
	else if (strcmp(month2_, "Feb") == 0) month2 = 2;
	else if (strcmp(month2_, "Mar") == 0) month2 = 3;
	else if (strcmp(month2_, "Apr") == 0) month2 = 4;
	else if (strcmp(month2_, "May") == 0) month2 = 5;
	else if (strcmp(month2_, "Jun") == 0) month2 = 6;
	else if (strcmp(month2_, "Jul") == 0) month2 = 7;
	else if (strcmp(month2_, "Aug") == 0) month2 = 8;
	else if (strcmp(month2_, "Sep") == 0) month2 = 9;
	else if (strcmp(month2_, "Oct") == 0) month2 = 10;
	else if (strcmp(month2_, "Nov") == 0) month2 = 11;
	else if (strcmp(month2_, "Dec") == 0) month2 = 12;

	year2_ = strtok(NULL, "/");	int year2 = atoi(year2_);



	//여기서 둘을 비교할 땐 같은지, 뭐가 더 앞인지, 뭐가 더 뒤인지만 알 수 있으면 된다. 마치 strcmp처럼!
	//그럼 어떻게 비교하면 좋을까? 지난 문제처럼 둘을 비교해서 바꾸는 게 아니라 더 앞인지 아닌지만 판별할땐?

	//년도를 먼저 비교. 년도가 같으면 월을 비교. 월이 같으면 일을 비교.
	//년도도 같고 월도 같고 일도 같으면 다 같은 것.

	//return값 : strcmp처럼, str1이 더 작으면(빠르면) -1(음수), 더 크면 1, 같으면 0 반환.

	if (year < year2)
		return -1;
	else if (year > year2)
		return 1;
	else{
		if (month < month2)
			return -1;
		else if (month > month2)
			return 1;
		else {
			if (day < day2)
				return -1;
			else if (day > day2)
				return 1;
			else
				return 0;
		}
	}
}


int compare_time_2(char* str1_, char*str2_) {
	char* str1 = strdup(str1_); //보존의 의미 -> compare_Time함수 호출이 같은 string으로 여러번 일어나기 때문에 필요함.
	char* str2 = strdup(str2_);

	char *day_, *month_, *year_, *hour_, *minute_, *second_;
	char *day2_, *month2_, *year2_, *hour2_, *minute2_, *second2_;

	day_ = strtok(str1, "[/"); int day = atoi(day_);

	month_ = strtok(NULL, "/");
	month_ = strdup(month_);

	int month;


	if (strcmp(month_, "Jan") == 0) month = 1; //★★여기서 왜 예외가....? ★★여기서 month_가 NULL로 바뀜. => compar_Time함수를 한번 호출하고 나면 호출자쪽 str이 변형돼버려서 그럼.
	else if (strcmp(month_, "Feb") == 0) month = 2;
	else if (strcmp(month_, "Mar") == 0) month = 3;
	else if (strcmp(month_, "Apr") == 0) month = 4;
	else if (strcmp(month_, "May") == 0) month = 5;
	else if (strcmp(month_, "Jun") == 0) month = 6;
	else if (strcmp(month_, "Jul") == 0) month = 7;
	else if (strcmp(month_, "Aug") == 0) month = 8;
	else if (strcmp(month_, "Sep") == 0) month = 9;
	else if (strcmp(month_, "Oct") == 0) month = 10;
	else if (strcmp(month_, "Nov") == 0) month = 11;
	else if (strcmp(month_, "Dec") == 0) month = 12;

	year_ = strtok(NULL, ":");	int year = atoi(year_);


	hour_ = strtok(NULL, ":"); int hour = atoi(hour_);

	minute_ = strtok(NULL, ":"); int minute = atoi(minute_);

	second_ = strtok(NULL, ":]"); int second = atoi(second_);


	char delim[] = "[]:/";

	day2_ = strtok(str2, delim);	int day2 = atoi(day2_);

	month2_ = strtok(NULL, delim);
	int month2;

	if (strcmp(month2_, "Jan") == 0) month2 = 1;
	else if (strcmp(month2_, "Feb") == 0) month2 = 2;
	else if (strcmp(month2_, "Mar") == 0) month2 = 3;
	else if (strcmp(month2_, "Apr") == 0) month2 = 4;
	else if (strcmp(month2_, "May") == 0) month2 = 5;
	else if (strcmp(month2_, "Jun") == 0) month2 = 6;
	else if (strcmp(month2_, "Jul") == 0) month2 = 7;
	else if (strcmp(month2_, "Aug") == 0) month2 = 8;
	else if (strcmp(month2_, "Sep") == 0) month2 = 9;
	else if (strcmp(month2_, "Oct") == 0) month2 = 10;
	else if (strcmp(month2_, "Nov") == 0) month2 = 11;
	else if (strcmp(month2_, "Dec") == 0) month2 = 12;

	year2_ = strtok(NULL, delim);	int year2 = atoi(year2_);

	hour2_ = strtok(NULL, delim); //이번엔 여기서 에러가 남....
	int hour2 = atoi(hour2_); 

	minute2_ = strtok(NULL, delim); int minute2 = atoi(minute2_);

	second2_ = strtok(NULL, delim); int second2 = atoi(second2_);


	if (year < year2)
		return -1;
	else if (year > year2)
		return 1;
	else {
		if (month < month2)
			return -1;
		else if (month > month2)
			return 1;
		else {
			if (day < day2)
				return -1;
			else if (day > day2)
				return 1;
			else {
				if (hour < hour2)
					return -1;
				else if (hour > hour2)
					return 1;
				else {
					if (minute < minute2)
						return -1;
					else if (minute > minute2)
						return 1;
					else {
						if (second < second2)
							return -1;
						else if (second > second2)
							return 1;
						else
							return 0;
					}
				}
			}
		}
	}
}

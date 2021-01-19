
Date : Oct 11, 2020 12 : 59 pm

/*
다음과 같이 작동하는 프로그램을 작성하라. 이 프로그램은 사용자로부터 정수들을 하나씩 입력 받아서 연결리스트의 지정된 위치에 삽입하고, 검색하고, 삭제하는 일을 한다. 먼저 프로그램이 시작되면 화면에 $를 출력하고 사용자의 명령을 대기하며 add, find, count, delete, list, 그리고 exit의 6가지 명령을 지원한다. 

add 명령은 다음과 같은 형식이다.
$ add index value
여기서 value는 추가할 정수이고 index는 정수를 추가할 위치이다. 엄밀하게 말하면 추가된 값의 연결리스트에서의 인덱스가 index가 되어야 한다. 이때 index는 0에서 시작한다. 즉 index가 0이면 연결리스트의 맨 앞에 추가하라는 의미이고, index가 1이면 추가한 값이 결과적으로 두 번째 노드가 되도록 하라는 의미이다. 만약 index값이 유효한 범위를 벗어나면 invalid index라고 출력한다.

find 명령은 다음과 같은 형식이다.
$ find value
이 명령이 하는 일은 연결리스트에 정수 value를 찾아서 그 위치, 즉 index를 출력하는 것이다. 정수 value가 연결리스트에 여러 개 저장되어 있을 경우에는 그 중 첫 번째 값의 위치를 출력하고, 존재하지 않을 경우에는 -1을 출력한다.

count 명령은 다음과 같은 형식이다.
$ count value
이 명령이 하는 일은 연결리스트에 정수 value가 몇 개 저장되어 있는지 카운트하여 그 개수를 출력하는 것이다. 

delete 명령은 다음과 같은 형식이다.
$ delete value
이 명령은 연결리스트에서 정수 value를 찾아서 연결리스트로 부터 삭제한다. 정수 value가 여러 개 저장되어 있는 경우에는 그 중 첫 번째 값을 제거한다. 만약 정수 value가 존재하지 않으면 not exist라고 출력한다.

list명령은 연결리스트에 저장된 정수들을 순서대로 한 줄로 출력하는 것이고, 마지막으로 exit 명령은 프로그램을 종료한다.


프로그램 실행 예:
$ add 1 5
invalid index
$ add 0 5
$ find 5
0
$ add 0 6
$ find 5
1
$ add 2 7
$ list
6 5 7
$ add 4 5
invalid index
$ add 3 5
$ list 
6 5 7 5
$ count 5
2
$ find 5
1
$ find 8
-1
$ add 1 7
$ list 
6 7 5 7 5
$ add 5 7
$ list 
6 7 5 7 5 7
$ delete 8
not exist
$ delete 7
$ list
6 5 7 5 7
$ count 7
2
$ add 3 6
$ list
6 5 7 6 5 7
$ delete 7
$ list 
6 5 6 5 7
$ delete 7
$ list 
6 5 6 5
$ count 5
2
$ exit

*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BUFFER_LENGTH 300
#define MAX
#pragma warning(disable : 4996)

struct node {
	int value;
	struct node *next;
};
typedef struct node Node;
Node *head = NULL;

int read_line(FILE* fp, char str[], int n);
int add(int index, int item);
void add_first(int item);
void add_after(Node *prev, int item);
int find(int item);
int count(int item);
void remove(int index);
void remove_first();
void remove_after(Node *prev);
Node *get_node(int index);
void print_list(void);


int main(void) {



	while (1) {

		char command_line[BUFFER_LENGTH];
		char *command, *argument, *argument2;


		printf("$ ");
		if (read_line(stdin, command_line, BUFFER_LENGTH) <= 0)
			continue;

		command = strtok(command_line, " ");

		if (strcmp(command, "add") == 0) {
			argument = strtok(NULL, " "); //index
			argument2 = strtok(NULL, " "); //value

			if (argument == NULL) {
				printf("invalid index\n");
				continue;
			}

			int argument1 = atoi(argument);
			int argument2_ = atoi(argument2);
			int result = add(argument1, argument2_);
			
			if (result == 0)
				printf("invalid index\n");

		}
		else if (strcmp(command, "find") == 0) {
			argument = strtok(NULL, " "); //value
			int argument_ = atoi(argument);

			int result = find(argument_);


			printf("%d\n", result);



		}
		else if (strcmp(command, "count") == 0) {
			argument = strtok(NULL, " "); //value
			int argument_ = atoi(argument);

			int result = count(argument_);
			printf("%d\n", result);
		}
		else if (strcmp(command, "delete") == 0) {
			argument = strtok(NULL, " ");
			int argument_ = atoi(argument); //value

			
			int index = find(argument_);
			if (index == -1) {
				printf("not exist\n");
				continue;
			}
				
			remove(index);
		}
		else if (strcmp(command, "list") == 0) {
			print_list();
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

int add(int index, int item) {
	if (index < 0)
		return 0;
	if (index == 0) {
		add_first(item);
		return 1;
	}
	Node *prev = get_node(index - 1);
	if (prev != NULL) {
		add_after(prev, item);
		return 1;
	}
	return 0;
}



void add_first(int item) {
	Node *temp = (Node*)malloc(sizeof(Node));
	temp->value = item;
	temp->next = head;
	head = temp;
}

void add_after(Node *prev, int item) {
	if (prev == NULL)
		return;
	Node *tmp = (Node*)malloc(sizeof(Node));
	tmp->value = item;
	tmp->next = prev->next;
	prev->next = tmp;

	return;
}


int find(int item) {
	Node *p = head;
	int index = 0;
	while (p != NULL) {
		if (p->value == item)
			return index;
		p = p->next;
		index++;
	}
	return -1;
}

int count(int item) {
	Node *p = head;
	int counts = 0;
	while (p != NULL) {
		if (p->value == item)
			counts++;
		p = p->next;
	}
	return counts;
}

void remove(int index) {
	if (index < 0)
		return; //NULL;
	if (index == 0) {
		remove_first();
		return;
	}
	Node *prev = get_node(index - 1);
	if (prev == NULL)
		return; //NULL;
	else
	{
		remove_after(prev);
	}
}


void remove_first() {
	if (head == NULL)
		return;
	else {
		Node *tmp = head;
		head = head->next;
		return;
	}
}

void remove_after(Node *prev) {
	Node *tmp = prev->next;
	if (tmp == NULL)
		return;
	else {
		prev->next = tmp->next;
		return;
		//return tmp;
	}
}



Node *get_node(int index) {
	if (index < 0)
		return NULL;
	Node *p = head;
	for (int i = 0; i < index && p != NULL; i++)
		p = p->next;
	return p;
}

void print_list(void) {
	Node *p = head;
	while (p != NULL) {
		printf("%d ", p->value);
		p = p->next;
	}
	printf("\n");
}

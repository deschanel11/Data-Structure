/*
W05_Ex2와 동일한 문제이다. 다만 함수 insert의 signature만 다음과 같이 변경되었다.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 100

typedef struct { /* 하나의 단어와 그 단어의 빈도수를 저장하기 위한 구조체 */
  char *word;
  int freq;
} Item; 

struct node { /* 연결리스트의 노드의 구조를 정의하는 구조체 */
  Item *data;
  struct node *next;
}; 
typedef struct node Node;

void insert(Node **, char buf[]);

int main()
{
  char buf[MAXLEN];
  Node *head = NULL;   /* head는 지역변수이다. */
  while(1) {
    scanf("%s", buf);
    if (strcmp(buf, "EOF") == 0) break; /* 문자열 “EOF”를 입력하면 종료 */
    insert(&head, buf); /* 입력된 문자열을 연결리스트에 반영 */
  }
  Node *p = head;
  while(p!=NULL) {
    printf("%s:%d\n", p->data->word, p->data->freq);
    p = p->next;
  }
  return 0;
}

void insert(Node **ptr_head, char buf[]) {
  /* 입력된 문자열을 연결리스트에 반영한다. 즉, 이미 존재하는  */
  /* 문자열이면 카운트만 증가 하고, 아니라면 정렬된 순서로 연결리스트에 추가한다.  */ 
}

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 100
#pragma warning(disable:4996)

typedef struct {	//하나의 단어와 그 단어의 빈도수를 저장하기 위한 구조체
	char *word;
	int freq;
}Item;

struct node {	//연결리스트의 노드의 구조를 정의하는 구조체
	Item *data;
	struct node *next;
};

typedef struct node Node;

void insert(Node**, char buf[]);


int main(void) {

	char buf[MAXLEN];
	Node *head = NULL;

	while (1) {
		scanf("%s", buf);
		if (strcmp(buf, "EOF") == 0)
			break;

		insert(&head, buf);
	}

	Node *p = head; //<= 왜 head가 NULL이지??????????
	while (p != NULL) {
		printf("%s:%d\n", p->data->word, p->data->freq);
		p = p->next;
	}

	return 0;
}

void insert(Node **ptr_head, char buf[]) {


	//Node 만들어서 Node에 Item을 저장.
	Node *temp = (Node*)malloc(sizeof(Node));
	Item *tmp = (Item*)malloc(sizeof(Item));
	//Item
	tmp->word = strdup(buf);
	tmp->freq = 1;
	//Node
	temp->data = tmp;
	temp->next = NULL;

	
	Node *p = *ptr_head; //이렇게 하면 똑같은가..?
	Node *q = NULL;
	
	/*
	Node **p = head;
	Node **q = NULL;
	*q = NULL;*/

	if (p == NULL) { //연결리스트가 비어있을 때.
		*ptr_head = temp;
		return;
	}
	while (p != NULL && strcmp(p->data->word, buf) < 0) {
		q = p;
		p = p->next;
	}
	/*※주의!!
	위 while문을 나오는 이유는 두 가지.
	p는 NULL이 된 경우는 겹치는 단어가 없어서인 것.
	p가 NULL이 아니라면....
	하지만 p가 NULL이 되더라도...... strcmp역시 >인 경우는? -> 없음. p가 NULL이라는 건 정말 다 돌아봤다는 거니까.*/


	if (q == NULL) { //연결 리스트에 노드가 하나 있을 때.

		if (strcmp(p->data->word, buf) == 0) {
			(p->data->freq)++;	//이때는 그럼 temp랑 tmp 전혀 쓸 데가 없는건가..? free()해줘야하나?
			return;
		}
		temp->next = *ptr_head;
		*ptr_head = temp;
		return;
	}


	if (p == NULL) {
		q->next = temp;
		return;
	}

	if (strcmp(p->data->word, buf) == 0) {
		(p->data->freq)++;	//이때는 그럼 temp랑 tmp 전혀 쓸 데가 없는건가..? free()해줘야하나?
		return;
	}
	temp->next = q->next;
	q->next = temp;//q다음에 원래 p가 있었음을 잊지 말것..
}

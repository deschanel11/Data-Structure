/*

아래의 프로그램의 목적은 단어들을 입력받은 후 입력된 단어들의 등장 빈도를 카운트하고 사전식 순서로 정렬하여 출력하는 것이다. 단어 “EOF”가 입력되면 종료한다. 함수 insert를 완성하라. 함수 insert는 입력된 문자열을 연결리스트에 반영하고 head노드의 주소를 반환한다. 여기서 반영한다는 것은 이미 존재하는 문자열이면 카운트만 증가하고, 아니라면 정렬된 순서로 연결리스트에 추가한다는 의미이다. 함수 insert 외부의 어떤 부분도 수정하거나 전역변수를 추가해서는 안된다. 

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

Node *insert(Node *, char buf[]);

int main()
{
  char buf[MAXLEN];
  Node *head = NULL; /* head는 지역변수이다. */
  while(1) {
    scanf("%s", buf);
    if (strcmp(buf, "EOF") == 0) break; /* 문자열 “EOF”를 입력하면 종료 */ 
    head = insert(head, buf); /* 입력된 문자열을 연결리스트에 반영 */
  }

  Node *p = head;
  while(p!=NULL) {
    printf("%s:%d\n", p->data->word, p->data->freq);
    p = p->next;
  }
  return 0;
}

Node *insert(Node *head, char buf[]) {
  /* 입력된 문자열을 연결리스트에 반영하고 head노드의 주소를 반환한다. 이미 존재하는.  */
  /* 문자열이면 카운트만 증가 하고, 아니라면 정렬된 순서로 연결리스트에 추가한다.  */ 




}

입력 예:
head hello part one is head hello hello
and board is cool EOF

출력 예:
and:1
board:1
cool:1
head:2
hello:3
is:2
one:1
part:1

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

Node *insert(Node*, char buf[]);


int main(void) {

	char buf[MAXLEN];
	Node *head = NULL;

	while (1) {
		scanf("%s", buf);
		if (strcmp(buf, "EOF") == 0) 
			break;

		head = insert(head, buf);
	}

	Node *p = head;
	while (p != NULL) {
		printf("%s:%d\n", p->data->word, p->data->freq);
		p = p->next;
	}

	return 0;
}

Node *insert(Node *head, char buf[]) {


	//Node 만들어서 Node에 Item을 저장.
	Node *temp = (Node*)malloc(sizeof(Node));
	Item *tmp = (Item*)malloc(sizeof(Item));
	//Item
	tmp->word = strdup(buf);
	tmp->freq = 1;
	//Node
	temp->data = tmp;
	temp->next = NULL;
	

	Node *p = head;
	Node *q = NULL;

	if (p == NULL) { //연결리스트가 비어있을 때.
		p = temp;
		return p;
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
			return head;
		}
		temp->next = head;
		head = temp;
		return head;
	}


	if (p == NULL) {
		q->next = temp;
		return head;
	}

	if (strcmp(p->data->word, buf) == 0) {
		(p->data->freq)++;	//이때는 그럼 temp랑 tmp 전혀 쓸 데가 없는건가..? free()해줘야하나?
		return head;
	}
	temp->next = q->next;
	q->next = temp;//q다음에 원래 p가 있었음을 잊지 말것..

	return head;
}

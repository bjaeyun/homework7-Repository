/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 if necessary */


typedef struct Node { //Node 구조체 선언
	int key;
	struct Node* llink; //포인터 llink 선언
	struct Node* rlink; //포인터 rlink 선언
} listNode;



typedef struct Head { //Head 구조체 선언
	struct Node* first; //포인터 first 선언
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
         lab3의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h); //headNode에 메모리를 할당하여 초기화하는 함수 선언 (이중포인터를 매개변수로 함)

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
         - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h); //할당된 메모리 해제하는 함수

int insertNode(headNode* h, int key); //list에 key노드를 추가하는 함수 선언
int insertLast(headNode* h, int key); //list의 끝 부분에 key노드를 추가하는 함수 선언
int insertFirst(headNode* h, int key); //list의 첫 부분에 key노드를 추가하는 함수 선언
int deleteNode(headNode* h, int key); //list의 노드 하나를 삭제하는 함수 선언
int deleteLast(headNode* h); //list의 마지막 노드를 삭제하는 함수 선언
int deleteFirst(headNode* h); //list의 첫 노드를 삭제하는 함수 선언
int invertList(headNode* h); //list의 link를 역순으로 재배치하는 함수 선언

void printList(headNode* h); //list를 출력하는 함수 선언


int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("--------------------- [변재윤] [2022041046] --------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z': //z 또는 Z인 경우
			initialize(&headnode); //initialize함수 호출
			break;
		case 'p': case 'P': //p 또는 P인 경우
			printList(headnode); //printList함수 호출
			break;
		case 'i': case 'I': //i 또는 I인 경우
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key); //insertNode함수 호출
			break;
		case 'd': case 'D': //d 또는 D인 경우
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key); //deleteNode함수 호출
			break;
		case 'n': case 'N': //n 또는 N인 경우
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key); //insertLast함수 호출
			break;
		case 'e': case 'E': //e 또는 E인 경우
			deleteLast(headnode); //deleteLast함수 호출
			break;
		case 'f': case 'F': //f 또는 F인 경우
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key); //insertFirst함수 호출
			break;
		case 't': case 'T': //t 또는 T인 경우
			break;
		case 'r': case 'R': //r 또는 R인 경우
			invertList(headnode); //invertList함수 호출
			break;
		case 'q': case 'Q': //q 또는 Q인 경우 
			freeList(headnode); //freeList함수 호출
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL) //만약 포인터 h가 NULL이 아니라면
		freeList(*h); //메모리 해제

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (headNode*)malloc(sizeof(headNode)); //포인터 h에 headNode의 크기만큼의 메모리 할당
	(*h)->first = NULL; //포인터 h의 first에 NULL 저장
	return 1;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first; //listNode 포인터 p선언 후 h의 first 노드에 저장

	listNode* prev = NULL; //listNode 포인터 prev 선언 후 초기화
	while(p != NULL) { //p가 NULL이 아닐 때까지
		prev = p; //prev에 p 저장
		p = p->rlink; //p에 p의 rlink 저장 
		free(prev); //메모리 해제
	}
	free(h); //메모리 해제
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) { //만약 h가 NULL이라면
		printf("Nothing to print....\n");
		return;
	}

	p = h->first; //p에 h의 first저장

	while(p != NULL) { //p가 NULL이 아닐 때까지
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink; //p에 p의 rlink 저장 
		i++; //i값 증가
	}

	printf("  items = %d\n", i);
}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listNode 포인터 node에 listNode 크기만큼의 메모리 할당
	node->key = key; //node의 key 부분에 key 저장
	node->rlink = NULL; //node의 key 부분에 key 저장
	node->llink = NULL; //node의 llink NULL로 초기화

	if (h->first == NULL) //만약 h의 first가 NULL이라면
	{
		h->first = node; //h의 first에 node 저장
		return 0;
	}

	listNode* n = h->first; //listNode 포인터 n에 h의 first 저장
	while(n->rlink != NULL) { //n의 rlink가 NULL이 아닐 때까지
		n = n->rlink; //n에 n의 rlink 저장
	}
	n->rlink = node; //n의 rlink에 node 저장
	node->llink = n; //node의 llink에 n 저장 
	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	if (h->first == NULL) //만약 h의 first가 NULL이라면
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first; //listNode 포인터 n 선언 후 h의 first 저장
	listNode* trail = NULL; //listNode 포인터 trail 선언 후 초기화

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if(n->rlink == NULL) { //만약 n의 rlink가 NULL이라면
		h->first = NULL; //h의 first 초기화
		free(n); //메모리 해제
		return 0;
	}

	/* 마지막 노드까지 이동 */
	while(n->rlink != NULL) { //n의 rlink가 NULL이 아닐 때까지
		trail = n; //trail에 n 저장
		n = n->rlink; //n에 n의 rlink 저장
	}

	/* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->rlink = NULL; //trail의 rlink 초기화
	free(n); //메모리 해제

	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listNode 포인터 node에 listNode 크기만큼의 메모리 할당
	node->key = key; //node의 key에 입력받은 key 저장
	node->rlink = node->llink = NULL; //node의 rlink에 node의 llink 저장 후 초기화

	if(h->first == NULL) //h의 first가 NULL일 경우
	{
		h->first = node; //h의 first에 node 저장
		return 1; //1반환
	}

	node->rlink = h->first; //node의 rlink에 h의 first 저장
	node->llink = NULL;  //node의 rlink에 h의 first 저장

	listNode *p = h->first; //listNode 포인터 p에 h의 first 저장
	p->llink = node; //p의 llink에 node 저장
	h->first = node; //h의 first에 node 저장

	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	if (h->first == NULL) //만약 h의 first가 NULL이라면
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first; //listNode 포인터 n에 h의 first 저장
	h->first = n->rlink; //h의 first에 n의 rlink저장

	free(n); //메모리 해제

	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {


	if(h->first == NULL) { //만약 h의 first가 NULL이라면
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first; //listNode 포인터 n에 h의 first 저장
	listNode *trail = NULL; //listNode 포인터 trail 초기화
	listNode *middle = NULL; //listNode 포인터 middle 초기화

	while(n != NULL){ //n이 NULL이 아닐 때까지
		trail = middle; //trail에 middle 저장
		middle = n; //middle에 n 저장
		n = n->rlink; //n에 n의 rlink 저장
		middle->rlink = trail; //middle의 rlink에 trail 저장
		middle->llink = n; //middle의 llink에 n 저장
	}

	h->first = middle; //h의 first에 middle 저장

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listNode의 포인터 node에 listNode의 크기만큼 메모리할당
	node->key = key; //node의 key에 입력받은 key 저장
	node->llink = node->rlink = NULL; //node의 llink에 node의 rlink 저장=초기화

	if (h->first == NULL) //만약 h의 first가 NULL이라면
	{
		h->first = node; //h의 first에 node 저장
		return 0;
	}

	listNode* n = h->first; //listNode 포인터 n에 h의 first 저장

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) { //n이 NULL이 아닐 때까지
		if(n->key >= key) { //만약 n의 key 보다 입력받은 key가 작거나 같다면
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) { //만약 n이 h의 first이라면
				insertFirst(h, key); //insertFirst함수 호출
			} else { /* 중간이거나 마지막인 경우 */
				node->rlink = n; //node의 rlink에 n 저장
				node->llink = n->llink; //node의 llink에 n의 llink 저장
				n->llink->rlink = node; //n의 llink의 rlink가 가리키는 위치에 node 저장
			}
			return 0;
		}

		n = n->rlink; //n에 n의 rlink 저장
	}

	/* 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
	insertLast(h, key); //insertLast함수 호출
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL) //만약 h의 first가 NULL이라면
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* n = h->first; //n에 h의 first저장

	while(n != NULL) { //n이 NULL이 아닐 때까지
		if(n->key == key) { //만약 n의 key가 입력받은 key와 같다면
			if(n == h->first) { /* 첫 노드째 노드 인경우 */
				deleteFirst(h); //deleteFirst함수 호출
			} else if (n->rlink == NULL){ /* 마지막 노드인 경우 */
				deleteLast(h); //deleteLast함수 호출
			} else { /* 중간인 경우 */
				n->llink->rlink = n->rlink;  //n의 llink의 rlink가 가리키는 위치에 n의 rlink 저장
				n->rlink->llink = n->llink; //n의 rlink의 llink가 가리키는 위치에 n의 llink 저장
				free(n); //메모리 해제
			}
			return 1; //1 반환
		}

		n = n->rlink; //n에 n의 rlink 저장
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 1;
}


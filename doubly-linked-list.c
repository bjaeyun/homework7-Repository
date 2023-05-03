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
/* �ʿ��� ������� �߰� if necessary */


typedef struct Node { //Node ����ü ����
	int key;
	struct Node* llink; //������ llink ����
	struct Node* rlink; //������ rlink ����
} listNode;



typedef struct Head { //Head ����ü ����
	struct Node* first; //������ first ����
}headNode;

/* �Լ� ����Ʈ */

/* note: initialize�� ���������͸� �Ű������� ����
         lab3�� initialize�� �������� ���� �Ұ� */
int initialize(headNode** h); //headNode�� �޸𸮸� �Ҵ��Ͽ� �ʱ�ȭ�ϴ� �Լ� ���� (���������͸� �Ű������� ��)

/* note: freeList�� �̱������͸� �Ű������� ����
        - initialize�� �� �ٸ��� ���� �Ұ�
         - ���������͸� �Ű������� �޾Ƶ� ������ �� ���� �� */
int freeList(headNode* h); //�Ҵ�� �޸� �����ϴ� �Լ�

int insertNode(headNode* h, int key); //list�� key��带 �߰��ϴ� �Լ� ����
int insertLast(headNode* h, int key); //list�� �� �κп� key��带 �߰��ϴ� �Լ� ����
int insertFirst(headNode* h, int key); //list�� ù �κп� key��带 �߰��ϴ� �Լ� ����
int deleteNode(headNode* h, int key); //list�� ��� �ϳ��� �����ϴ� �Լ� ����
int deleteLast(headNode* h); //list�� ������ ��带 �����ϴ� �Լ� ����
int deleteFirst(headNode* h); //list�� ù ��带 �����ϴ� �Լ� ����
int invertList(headNode* h); //list�� link�� �������� ���ġ�ϴ� �Լ� ����

void printList(headNode* h); //list�� ����ϴ� �Լ� ����


int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("--------------------- [������] [2022041046] --------------------\n");
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
		case 'z': case 'Z': //z �Ǵ� Z�� ���
			initialize(&headnode); //initialize�Լ� ȣ��
			break;
		case 'p': case 'P': //p �Ǵ� P�� ���
			printList(headnode); //printList�Լ� ȣ��
			break;
		case 'i': case 'I': //i �Ǵ� I�� ���
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key); //insertNode�Լ� ȣ��
			break;
		case 'd': case 'D': //d �Ǵ� D�� ���
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key); //deleteNode�Լ� ȣ��
			break;
		case 'n': case 'N': //n �Ǵ� N�� ���
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key); //insertLast�Լ� ȣ��
			break;
		case 'e': case 'E': //e �Ǵ� E�� ���
			deleteLast(headnode); //deleteLast�Լ� ȣ��
			break;
		case 'f': case 'F': //f �Ǵ� F�� ���
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key); //insertFirst�Լ� ȣ��
			break;
		case 't': case 'T': //t �Ǵ� T�� ���
			break;
		case 'r': case 'R': //r �Ǵ� R�� ���
			invertList(headnode); //invertList�Լ� ȣ��
			break;
		case 'q': case 'Q': //q �Ǵ� Q�� ��� 
			freeList(headnode); //freeList�Լ� ȣ��
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) {

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(*h != NULL) //���� ������ h�� NULL�� �ƴ϶��
		freeList(*h); //�޸� ����

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	*h = (headNode*)malloc(sizeof(headNode)); //������ h�� headNode�� ũ�⸸ŭ�� �޸� �Ҵ�
	(*h)->first = NULL; //������ h�� first�� NULL ����
	return 1;
}

int freeList(headNode* h){
	/* h�� ����� listNode �޸� ����
	 * headNode�� �����Ǿ�� ��.
	 */
	listNode* p = h->first; //listNode ������ p���� �� h�� first ��忡 ����

	listNode* prev = NULL; //listNode ������ prev ���� �� �ʱ�ȭ
	while(p != NULL) { //p�� NULL�� �ƴ� ������
		prev = p; //prev�� p ����
		p = p->rlink; //p�� p�� rlink ���� 
		free(prev); //�޸� ����
	}
	free(h); //�޸� ����
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) { //���� h�� NULL�̶��
		printf("Nothing to print....\n");
		return;
	}

	p = h->first; //p�� h�� first����

	while(p != NULL) { //p�� NULL�� �ƴ� ������
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink; //p�� p�� rlink ���� 
		i++; //i�� ����
	}

	printf("  items = %d\n", i);
}




/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listNode ������ node�� listNode ũ�⸸ŭ�� �޸� �Ҵ�
	node->key = key; //node�� key �κп� key ����
	node->rlink = NULL; //node�� key �κп� key ����
	node->llink = NULL; //node�� llink NULL�� �ʱ�ȭ

	if (h->first == NULL) //���� h�� first�� NULL�̶��
	{
		h->first = node; //h�� first�� node ����
		return 0;
	}

	listNode* n = h->first; //listNode ������ n�� h�� first ����
	while(n->rlink != NULL) { //n�� rlink�� NULL�� �ƴ� ������
		n = n->rlink; //n�� n�� rlink ����
	}
	n->rlink = node; //n�� rlink�� node ����
	node->llink = n; //node�� llink�� n ���� 
	return 0;
}



/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {

	if (h->first == NULL) //���� h�� first�� NULL�̶��
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first; //listNode ������ n ���� �� h�� first ����
	listNode* trail = NULL; //listNode ������ trail ���� �� �ʱ�ȭ

	/* ��尡 �ϳ��� �ִ� ���, �� first node == last node��  ��� ó�� */
	if(n->rlink == NULL) { //���� n�� rlink�� NULL�̶��
		h->first = NULL; //h�� first �ʱ�ȭ
		free(n); //�޸� ����
		return 0;
	}

	/* ������ ������ �̵� */
	while(n->rlink != NULL) { //n�� rlink�� NULL�� �ƴ� ������
		trail = n; //trail�� n ����
		n = n->rlink; //n�� n�� rlink ����
	}

	/* n�� �����ǹǷ�, ���� ����� ��ũ NULL ó�� */
	trail->rlink = NULL; //trail�� rlink �ʱ�ȭ
	free(n); //�޸� ����

	return 0;
}



/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listNode ������ node�� listNode ũ�⸸ŭ�� �޸� �Ҵ�
	node->key = key; //node�� key�� �Է¹��� key ����
	node->rlink = node->llink = NULL; //node�� rlink�� node�� llink ���� �� �ʱ�ȭ

	if(h->first == NULL) //h�� first�� NULL�� ���
	{
		h->first = node; //h�� first�� node ����
		return 1; //1��ȯ
	}

	node->rlink = h->first; //node�� rlink�� h�� first ����
	node->llink = NULL;  //node�� rlink�� h�� first ����

	listNode *p = h->first; //listNode ������ p�� h�� first ����
	p->llink = node; //p�� llink�� node ����
	h->first = node; //h�� first�� node ����

	return 0;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {

	if (h->first == NULL) //���� h�� first�� NULL�̶��
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first; //listNode ������ n�� h�� first ����
	h->first = n->rlink; //h�� first�� n�� rlink����

	free(n); //�޸� ����

	return 0;
}



/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {


	if(h->first == NULL) { //���� h�� first�� NULL�̶��
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first; //listNode ������ n�� h�� first ����
	listNode *trail = NULL; //listNode ������ trail �ʱ�ȭ
	listNode *middle = NULL; //listNode ������ middle �ʱ�ȭ

	while(n != NULL){ //n�� NULL�� �ƴ� ������
		trail = middle; //trail�� middle ����
		middle = n; //middle�� n ����
		n = n->rlink; //n�� n�� rlink ����
		middle->rlink = trail; //middle�� rlink�� trail ����
		middle->llink = n; //middle�� llink�� n ����
	}

	h->first = middle; //h�� first�� middle ����

	return 0;
}



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listNode�� ������ node�� listNode�� ũ�⸸ŭ �޸��Ҵ�
	node->key = key; //node�� key�� �Է¹��� key ����
	node->llink = node->rlink = NULL; //node�� llink�� node�� rlink ����=�ʱ�ȭ

	if (h->first == NULL) //���� h�� first�� NULL�̶��
	{
		h->first = node; //h�� first�� node ����
		return 0;
	}

	listNode* n = h->first; //listNode ������ n�� h�� first ����

	/* key�� �������� ������ ��ġ�� ã�´� */
	while(n != NULL) { //n�� NULL�� �ƴ� ������
		if(n->key >= key) { //���� n�� key ���� �Է¹��� key�� �۰ų� ���ٸ�
			/* ù ��� ���ʿ� �����ؾ��� ��� ���� �˻� */
			if(n == h->first) { //���� n�� h�� first�̶��
				insertFirst(h, key); //insertFirst�Լ� ȣ��
			} else { /* �߰��̰ų� �������� ��� */
				node->rlink = n; //node�� rlink�� n ����
				node->llink = n->llink; //node�� llink�� n�� llink ����
				n->llink->rlink = node; //n�� llink�� rlink�� ����Ű�� ��ġ�� node ����
			}
			return 0;
		}

		n = n->rlink; //n�� n�� rlink ����
	}

	/* ������ ������ ã�� ���� ���, �������� ���� */
	insertLast(h, key); //insertLast�Լ� ȣ��
	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL) //���� h�� first�� NULL�̶��
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* n = h->first; //n�� h�� first����

	while(n != NULL) { //n�� NULL�� �ƴ� ������
		if(n->key == key) { //���� n�� key�� �Է¹��� key�� ���ٸ�
			if(n == h->first) { /* ù ���° ��� �ΰ�� */
				deleteFirst(h); //deleteFirst�Լ� ȣ��
			} else if (n->rlink == NULL){ /* ������ ����� ��� */
				deleteLast(h); //deleteLast�Լ� ȣ��
			} else { /* �߰��� ��� */
				n->llink->rlink = n->rlink;  //n�� llink�� rlink�� ����Ű�� ��ġ�� n�� rlink ����
				n->rlink->llink = n->llink; //n�� rlink�� llink�� ����Ű�� ��ġ�� n�� llink ����
				free(n); //�޸� ����
			}
			return 1; //1 ��ȯ
		}

		n = n->rlink; //n�� n�� rlink ����
	}

	/* ã�� �� �Ѱ�� */
	printf("cannot find the node for key = %d\n", key);
	return 1;
}


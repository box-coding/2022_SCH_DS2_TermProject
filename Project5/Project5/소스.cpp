//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#define MAX 100
//
//typedef struct Time {
//	int start_time;
//	int finish_time;
//	int week;
//}Time;
//
//typedef struct subjectNode {
//	int grade; 
//	int semester;
//	Time time;
//	char name[MAX];
//	int score;
//	struct subjectNode* link;
//}subjectNode;
//
//typedef struct subjectType {
//	int n;
//	subjectNode* list[MAX];
//}subjectType;
//
//subjectNode* chart[12] = { 0 };
//char schedule[20][5] = { 0, };
//int chart_num = 0;  // �ð�ǥ�� ���� ���� ����
//int sum = 0;		// ������ ���� �� ����
//
//// -------------------- stack --------------------
//
//typedef struct StackNode {
//	subjectNode* node;
//	struct StackNode* link;
//}StackNode;
//
//typedef struct stackType {
//	StackNode* top;
//}stackType;
//
//void init(stackType* s) {
//	s->top = NULL;
//}
//
//int is_empty(stackType* s) {
//	return (s->top == NULL);
//}
//
//void push(stackType* s, subjectNode* node) {
//	StackNode* tmp = (StackNode*)malloc(sizeof(StackNode));
//	tmp->node = node;
//	tmp->link = s->top;
//	s->top = tmp;
//}
//
//subjectNode* pop(stackType* s) {
//	if (is_empty(s)) {
//		fprintf(stderr, "������ �������\n");
//		return NULL;
//	}
//	else
//		return s->;
//}
//
//// -------------------- �Լ� --------------------
//
//// ��� ����
//void create_subject(subjectType* g, int index, int grade, int semester, char name[], int start_time, int finish_time, int week) {
//	subjectNode* node = (subjectNode*)malloc(sizeof(subjectNode));
//	node->grade = grade;
//	node->semester = semester;
//	//memset(node->name, name, sizeof(char));
//	node->time.start_time = start_time;
//	node->time.finish_time = finish_time;
//	node->time.week = week;
//	node->link = NULL;
//	node->link = g->list[index];
//	g->list[index] = node;
//}
//
//// �� ����
//subjectType* reverse_sort(subjectType* sub) {
//	subjectType* r = (subjectType*)malloc(sizeof(subjectType));  // �� ���� ����Ʈ ����
//
//	for (int i = 0; i < 39; i++) {
//		stackType s;  // ����
//		init(&s);
//
//		subjectNode* node = sub->list[i]->link;  // �ӽ� ����Ʈ
//
//		while (node != NULL) {
//			push(&s, node);
//			if (node->link == NULL)
//				break;
//			subjectNode* tmp = node->link;
//			node = tmp;
//		}
//
//		while (!is_empty(&s)) {
//			subjectNode* node1 = pop(&s);
//			node1->link = r->list[i];
//			r->list[i] = node1;
//		}
//	}
//	return r;
//}
//
//// �˻�(����)
//// �˻���(����) �ޱ�
//void search_name( ) {
//
//}
//
//// �� ���� ����
//subjectNode* search_next_name(char* name, subjectType* fList) {
//	subjectNode* node;
//
//	for (int i = 0; i < fList->n; i++) { // ���� ����Ʈ�� i��° ����
//		node = fList->list[i];
//
//		if (node->name == name) // ���Ϸ��� ����� i��° ������ �̸��� ���ٸ�
//			return node;		// ��� ��ȯ
//	}
//	return NULL;
//}
//
//// �� ���� ����
//subjectNode* search_pre_name(char* name, subjectType* pList) {
//	subjectNode* node;
//
//	for (int i = 0; i <= pList->n; i++) {
//		node = pList->list[i]; // �� ��������Ʈ�� i��° ����
//
//		if (node->name == name) // ���Ϸ��� ����� i���� ������ �̸��� ���ٸ�
//			return node;		// ��� ��ȯ
//	}
//
//	return NULL;
//}
//
//// �˻���(�й�/�б�) �ޱ�
//void search_GS() {
//
//}
//
//// �˻�(�й�/�б�)
//int* search_grade_semester(int grade, int semester, subjectType* pList) {
//	int index[40];
//	int j = 0;
//	subjectNode* node;
//
//	for (int i = 0; i < pList->n; i++) { // �� ���� ����Ʈ
//		node = pList->list[i];
//
//		if (node->grade == grade && node->semester == semester)
//			index[j++] = i;
//	}
//	return index;
//}
//
//// �ð�ǥ ����
//void insert_schedule(subjectNode subject) {
//	for (int i = subject.time.start_time; i < subject.time.finish_time; i++)
//		schedule[i][subject.time.week] = '��';
//
//	sum += subject.score;
//}
//
//// �ð�ǥ ���
//void show_schedule() {
//	// �ð�ǥ ���·� ���
//	printf("�� ȭ �� �� ��");
//	for (int i = 0; i < 19; i++)
//		for (int j = 0; j < 4; j++) {
//			if (schedule[i][j] == '��')
//				printf("%c", schedule[i][j]);
//			else
//				printf(" ");
//		}
//
//	printf("----------------------------");
//
//	for (int i = 0; i < 5; i++) {
//		switch (i)
//		{
//		case 0:
//			printf("������: ");
//			break;
//		case 1:
//			printf("ȭ����: ");
//			break;
//		case 2:
//			printf("������: ");
//			break;
//		case 3:
//			printf("�����: ");
//			break;
//		case 4:
//			printf("�ݿ���: ");
//			break;
//		default:
//			break;
//		}
//
//		int j = 0; // �ð� (9��~ 6�ù�)
//		while (j > 20) {
//			int n = 0; // chart �׸� �˻�
//			while (n = chart_num) {
//				if (chart[n]->time.week == i)
//					if (chart[n]->time.start_time == j)
//						printf("1"); // chart�� n��° �� ���� ���
//				n++;
//			}
//			j++;
//		}
//	}
//}
//
//// �޴�
//void menu() {
//	int num;
//	scanf("%d", &num);
//	switch (num) {
//	case 1:
//		search_name();  // �˻�- ����
//		break;
//	case 2:
//		search_GS(); // �˻� - �г�/�б�
//		break;
//	case 3:
//		show_schedule();
//		break;
//	case 4:
//		exit(1);
//	}
//}
//
//// �˻�
//void search() {
//	int num;
//	scanf("%d", &num);
//	switch (num) {
//	case 1:
//		search_name();
//		break;
//	case 2:
//		search_GS();
//		break;
//	case 3:
//		break;
//	}
//}
//
//int main() {
//	subjectType* s = (subjectType*)malloc(sizeof(subjectType)); // �� ����
//	subjectType* r = (subjectType*)malloc(sizeof(subjectType)); // �� ����
//	s->n = 39; r->n = 39;
//	// �� ���� ����Ʈ�� ���� ���� (�����ʼ�����: ** / �����ٽɰ���: *)
//	{
//		//create_subject(s, ��ȣ, �г�, �б�, �̸�, ���۽ð�, ������ �ð�, ����)
//		create_subject(s, 0, 1, 1, "**���м����Թ�**", 0, 0, 0);
//		printf("clear\n");
//		create_subject(s, 1, 1, 1, "**���α׷��� ����1**", 0, 0, 0);
//		create_subject(s, 2, 1, 1, "��ǻ�� ����", 0, 0, 0);
//		create_subject(s, 3, 1, 1, "��ǻ�� ����1", 0, 0, 0);
//		create_subject(s, 4, 1, 2, "**�������**", 0, 0, 0);
//		create_subject(s, 5, 1, 2, "���α׷��� ����2", 0, 0, 0);
//		create_subject(s, 6, 1, 2, "**C���α׷���**", 0, 0, 0);
//		create_subject(s, 7, 1, 2, "��ǻ�� ����2", 0, 0, 0);
//		create_subject(s, 8, 2, 1, "**�������**", 0, 0, 0);
//		create_subject(s, 9, 2, 1, "**������ ����**", 0, 0, 0);
//		create_subject(s, 10, 2, 1, "**������ ����1**", 0, 0, 0);
//		create_subject(s, 11, 2, 1, "JAVA ���α׷���", 0, 0, 0);
//		create_subject(s, 12, 2, 1, "C ���α׷���", 0, 0, 0);
//		create_subject(s, 13, 2, 2, "**Ȯ�� �� ���**", 0, 0, 0);
//		create_subject(s, 14, 2, 2, "���� ����ȸ��", 0, 0, 0);
//		create_subject(s, 15, 2, 2, "**��ǻ�� ����**", 0, 0, 0);
//		create_subject(s, 16, 2, 2, "**������ ����2**", 0, 0, 0);
//		create_subject(s, 17, 2, 2, "��ü���� ���α׷���", 0, 0, 0);
//		create_subject(s, 18, 2, 2, "�� ���α׷���", 0, 0, 0);
//		create_subject(s, 19, 3, 1, "*�ü��*", 0, 0, 0);
//		create_subject(s, 20, 3, 1, "��ǻ�ͱ׷��Ƚ�", 0, 0, 0);
//		create_subject(s, 21, 3, 1, "����ó��", 0, 0, 0);
//		create_subject(s, 22, 3, 1, "*���α׷��� ����*", 0, 0, 0);
//		create_subject(s, 23, 3, 1, "�������� ���α׷���", 0, 0, 0);
//		create_subject(s, 24, 3, 1, "JAVA ���� ���α׷���", 0, 0, 0);
//		create_subject(s, 25, 3, 2, "*����ũ�� ���μ���*", 0, 0, 0);
//		create_subject(s, 26, 3, 2, "*��ǻ�� ��Ʈ��ũ*", 0, 0, 0);
//		create_subject(s, 27, 3, 2, "�ΰ�����", 0, 0, 0);
//		create_subject(s, 28, 3, 2, "*������ ���̽�*", 0, 0, 0);
//		create_subject(s, 29, 3, 2, "�����Ϸ�", 0, 0, 0);
//		create_subject(s, 30, 3, 2, "*����Ʈ�������*", 0, 0, 0);
//		create_subject(s, 31, 4, 1, "�����ȣ �� ����", 0, 0, 0);
//		create_subject(s, 32, 4, 1, "�Ӻ���� ����Ʈ����", 0, 0, 0);
//		create_subject(s, 33, 4, 1, "������ ����", 0, 0, 0);
//		create_subject(s, 34, 4, 1, "����Ʈ�� ���� ���α׷���", 0, 0, 0);
//		create_subject(s, 35, 4, 1, "�˰��� ����", 0, 0, 0);
//		create_subject(s, 36, 4, 2, "������ ���α׷���", 0, 0, 0);
//		create_subject(s, 37, 4, 2, "������ ����", 0, 0, 0);
//		create_subject(s, 38, 4, 2, "��� �� ���� ���α׷���", 0, 0, 0);
//		printf("create subject clear\n");
//	}
//
//	// �� ���� ����Ʈ�� ���� ����
//	{
//		s->list[0]->link = s->list[5];
//		printf("clear\n");
//		s->list[0]->link->link = NULL;
//		s->list[1]->link = s->list[5];
//		s->list[1]->link->link = NULL;
//		s->list[2]->link = s->list[5]; s->list[2]->link->link = s->list[6];
//		s->list[2]->link->link->link = NULL;
//		s->list[3]->link = s->list[7]; // �Ŀ�
//		s->list[3]->link->link = NULL;
//		s->list[4]->link = s->list[8];
//		s->list[4]->link->link = NULL;
//		s->list[5]->link = s->list[10];
//		s->list[5]->link->link = NULL;
//		s->list[6]->link = s->list[10]; s->list[6]->link->link = s->list[11]; s->list[6]->link->link->link = s->list[12];
//		s->list[6]->link->link->link->link = NULL;
//		s->list[7]->link = NULL;
//		s->list[8]->link = s->list[13];
//		s->list[8]->link->link = NULL;
//		s->list[9]->link = s->list[14]; s->list[9]->link->link = s->list[15];
//		s->list[9]->link->link->link = NULL;
//		s->list[10]->link = s->list[16];
//		s->list[10]->link->link = NULL;
//		s->list[11]->link = s->list[17]; s->list[11]->link->link = s->list[18]; s->list[11]->link->link->link = s->list[22];
//		s->list[11]->link->link->link->link = NULL;
//		s->list[12]->link = NULL;
//		s->list[13]->link = s->list[27]; s->list[13]->link->link = s->list[31];
//		s->list[13]->link->link->link = NULL;
//		s->list[14]->link = s->list[25]; // ����ȸ
//		s->list[14]->link->link = NULL;
//		s->list[15]->link = s->list[19];
//		s->list[15]->link->link = NULL;
//		s->list[16]->link = s->list[20]; s->list[16]->link->link = s->list[21]; s->list[16]->link->link->link = s->list[27];
//		s->list[16]->link->link->link->link = NULL;
//		s->list[17]->link = s->list[22]; s->list[17]->link->link = s->list[23];
//		s->list[17]->link->link->link = NULL;
//		s->list[18]->link = s->list[38]; // ���� 18
//		s->list[18]->link->link = NULL;
//		s->list[19]->link = s->list[26];
//		s->list[19]->link->link = NULL;
//		s->list[20]->link = s->list[33];
//		s->list[20]->link->link = NULL;
//		s->list[21]->link = s->list[28];
//		s->list[21]->link->link = NULL;
//		s->list[22]->link = s->list[29]; s->list[22]->link->link = s->list[30];
//		s->list[22]->link->link->link = NULL;
//		s->list[23]->link = NULL;
//		s->list[24]->link = NULL;
//		s->list[25]->link = s->list[32];
//		s->list[25]->link->link = NULL;
//		s->list[26]->link = s->list[32];
//		s->list[26]->link->link = NULL;
//		s->list[27]->link = s->list[33];
//		s->list[27]->link->link = NULL;
//		s->list[28]->link = NULL;
//		s->list[29]->link = NULL;
//		s->list[30]->link = NULL;
//		s->list[31]->link = NULL;
//		s->list[32]->link = NULL;
//		s->list[33]->link = NULL;
//		s->list[34]->link = NULL;
//		s->list[35]->link = NULL;
//		s->list[36]->link = NULL;
//		s->list[37]->link = NULL;
//		s->list[38]->link = NULL;
//		printf("connect list clear\n");
//	}
//
//	// �� ���� ����Ʈ ����
//	r = reverse_sort(s);
//
//
//	return 0;
//}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

typedef struct Time {
	int start_time[2];
	int finish_time[2];
	int week[2];
}Time;

typedef struct subjectNode {
	int index;
	int grade;
	int semester;
	Time time;
	char name[MAX];
	int score;
	struct subjectNode* link;
	int link1[4];
}subjectNode;

typedef struct subjectType {
	int n;
	subjectNode* list[MAX];
}subjectType;

subjectNode* chart[12] = { 0 }; // ������û�� ����
char schedule[20][5] = { 0, }; // �ð��� �ð�ǥ
int chart_num = 0;  // ������û�� ���� ����
int sum = 0;		// ������ ���� �� ����

// ------------------------------------------------------------ stack ------------------------------------------------------------
typedef struct StackNode {
	subjectNode* node;
	struct StackNode* link;
}StackNode;

typedef struct stackType {
	StackNode* top;
}stackType;

void init(stackType* s) {
	s->top = NULL;
}

subjectNode* is_empty(stackType* s) {
	return (s->top == NULL);
}

void push(stackType* s, subjectNode* node) {
	StackNode* tmp = (StackNode*)malloc(sizeof(StackNode));
	tmp->node = node;
	tmp->link = s->top;
	s->top = tmp;
}

subjectNode* pop(stackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "������ �������\n");
		return NULL;
	}
	else
		return s->top;
}

// ------------------------------------------------------------ �Լ� ------------------------------------------------------------

void menu(subjectType* s, subjectType* r);
void insert_schedule(subjectNode* subject);

// ��� ����
void create_subject(subjectType* g, int index, int grade, int semester, 
	char name[], int start_time1, int start_time2, int finish_time1, int finish_time2, int week1, int week2) {
	subjectNode* node = (subjectNode*)malloc(sizeof(subjectNode));
	node->index = index;
	node->grade = grade;
	node->semester = semester;
	strcpy(node->name, name);
	node->time.start_time[0] = start_time1;
	node->time.start_time[1] = start_time2;
	node->time.finish_time[0] = finish_time1;
	node->time.finish_time[1] = finish_time2;
	node->time.week[0] = week1;
	node->time.week[1] = week2;
	node->link1[0] = -1; 	node->link1[1] = -1;
	node->link1[2] = -1;	node->link1[3] = -1;
	node->link = g->list[index];
	g->list[index] = node;
}

// �� ����
subjectType* reverse_sort(subjectType* sub) {
	subjectType* r = (subjectType*)malloc(sizeof(subjectType));  // �� ���� ����Ʈ ����

	for (int i = 0; i < 39; i++) {
		stackType s;  // ����
		init(&s);

		subjectNode* node = sub->list[i]->link;  // �ӽ� ����Ʈ

		while (node != NULL) {
			push(&s, node);
			if (node->link == NULL)
				break;
			node = node->link;
		}

		while (!is_empty(&s)) {
			subjectNode* node1 = pop(&s);
			node1->link = r->list[i];
			r->list[i] = node1;
		}
	}
	return r;
}

// �˻�(����)
void search_name(subjectType* pList, subjectType* fList) {
	printf("�˻��� ������ �Է��ϼ���:\n>>");
	char name[MAX];
	scanf("%s", &name);

	subjectNode* nodeP = pList->list[0];
	subjectNode* nodeF = fList->list[0];

	for (int i = 0; i <= pList->n; i++) {
		nodeP = pList->list[i]; // i��° ����
		if (strcmp(nodeP->name, name) == 0) // ���Ϸ��� ����� i���� ������ �̸��� ���ٸ�
			break;
	}
	
	for (int i = 0; i <= fList->n; i++) {
		nodeF = fList->list[i]; // i��° ����
		if (strcmp(nodeF->name, name) == 0) // ���Ϸ��� ����� i���� ������ �̸��� ���ٸ�
			break;
	}

	printf("\n�˻� ��� (�����ʼ�����: ** / �����ٽɰ���: *):\n");

	//�� ���� ���� ���
	for (int i = 0; i < 4;i++) {
		subjectNode* name1 = nodeP->link1[i];
		printf(" %s ", name1->name);
		if (nodeP->link1[i] == -1)
			break;
		else
			nodeP = pList->list[nodeP->link1[i]];
	}

	printf(" -> %s -> ", &name);

	// �� ���� ���� ���
	for (int i = 1; i < 4; i++) {
		printf(" %s ", &nodeF->name);
		if (nodeF->link1[i] == -1)
			break;
		else
			nodeF = fList->list[nodeF->link1[i]];
	}

	printf("\n\n1) �ð�ǥ�� �ֱ� || 2) �޴��� ���ư���\n>>");
	int num;
	scanf("%d", &num);
	switch (num)
	{
	case 1:
		// �߰�
		while (1) {
			printf("���ϴ� ������ �Է��ϼ��� (���: 0 �Է�)\n>>");
			char* n;
			scanf("%s", &n);
			subjectNode* node;
			int flag = 0;
			for (int i = 0; i <= pList->n; i++) {
				node = pList->list[i]; // i��° ����
				if (strcmp(node->name, n) == 0){ // ���Ϸ��� ����� i���� ������ �̸��� ���ٸ�
					chart[chart_num++] = node;
					insert_schedule(node);
					flag = 1;
					break;
				}
			}
			if (flag == 1) {
				printf("\n�߰��Ǿ����ϴ�\n");

			}
			else if (n == "0") {
				printf("\n��ҵǾ����ϴ�\n");
				break;
			}
			else
				printf("\n�ٽ� �Է����ּ���.\n");
		}
		break;
	case 2: 
		menu(pList, fList);
		break;
	}

}


// �˻�(�й�/�б�)
int* search_grade_semester(subjectType* pList, subjectType* fList) {
	int grade, semester;
	while (1) {
		printf("�˻��� '�г�' '�б�' �� �Է��ϼ���\n>>");
		scanf("%d %d", &grade, &semester);
		if (grade < 1 || grade>4 || semester < 1 || semester>2)
			printf("\n�ٽ� �Է����ּ���\n");
		else
			break;
	}
	int index[40];
	int j = 0;
	subjectNode* node;

	for (int i = 0; i < pList->n; i++) { // �� ���� ����Ʈ
		node = pList->list[i];

		if (node->grade == grade && node->semester == semester)
			index[j++] = i;
	}

	printf("�˻� ��� (�����ʼ�����: ** / �����ٽɰ���: *):\n");
	// ���� ���
	for (int i = 0; i < j; i++) {
		printf("%s, ", &pList->list[index[i]]->name);
	}


	printf("\n\n1) �ð�ǥ�� �ֱ� || 2) �޴��� ���ư���\n>>");
	int num;
	scanf("%d", &num);
	switch (num)
	{
	case 1:
		// �߰�
		while (1) {
			printf("���ϴ� ������ �Է��ϼ��� (���: 0 �Է�)\n>>");
			char n[MAX];
			scanf("%s", &n);
			subjectNode* node;
			int flag = 0;
			for (int i = 0; i <= pList->n; i++) {
				node = pList->list[i]; // i��° ����
				if (strcmp(node->name, n) == 0) { // ���Ϸ��� ����� i���� ������ �̸��� ���ٸ�
					chart[chart_num++] = node;
					insert_schedule(node);
					flag = 1;
					break;
				}
			}
			if (flag == 1) {
				printf("\n�߰��Ǿ����ϴ�\n");
			}
			else if (n == "0") {
				printf("\n��ҵǾ����ϴ�\n");
				break;
			}
			else
				printf("\n�ٽ� �Է����ּ���.\n");
		}
		break;
	case 2:
		menu(pList, fList);
		break;
	}

}

// �ð�ǥ ����
void insert_schedule(subjectNode* subject) {

	for (int i = subject->time.start_time[0]; i < subject->time.finish_time[0]; i++)
		schedule[i][subject->time.week[0]] = '��';

	for (int i = subject->time.start_time[1]; i < subject->time.finish_time[1]; i++)
		schedule[i][subject->time.week[1]] = '��';

	sum += subject->score;
}

// �ð�ǥ ���
void show_schedule(subjectType* s, subjectType* r) {
	// �ð�ǥ ���·� ���
	printf("\n�� ȭ �� �� ��");
	for (int i = 0; i < 19; i++)
		for (int j = 0; j < 4; j++) {
			if (schedule[i][j] == '��')
				printf("%c", schedule[i][j]);
			else
				printf(" ");
		}

	printf("\n____________________________________________");

	for (int i = 0; i < 5; i++) {
		switch (i)
		{
		case 0:
			printf("\n������: ");
			for (int i = 0; i < 12; i++)
				if (chart[i]->time.week == 0)
					printf("%s ", &chart[i]->name);
			break;
		case 1:
			printf("\nȭ����: ");
			for (int i = 0; i < 12; i++)
				if (chart[i]->time.week == 0)
					printf("%s ", &chart[i]->name);
			break;
		case 2:
			printf("������: ");
			for (int i = 0; i < 12; i++)
				if (chart[i]->time.week == 0)
					printf("%s ", &chart[i]->name);
			break;
		case 3:
			printf("�����: ");
			for (int i = 0; i < 12; i++)
				if (chart[i]->time.week == 0)
					printf("%s ", &chart[i]->name);
			break;
		case 4:
			printf("�ݿ���: ");
			for (int i = 0; i < 12; i++)
				if (chart[i]->time.week == 0)
					printf("%s ", &chart[i]->name);
			break;
		default:
			break;
		}

		int j = 0; // �ð� (9��~ 6�ù�)
		while (j > 20) {
			int n = 0; // chart �׸� �˻�
			while (n = chart_num) {
				if (chart[n]->time.week == i)
					if (chart[n]->time.start_time == j)
						printf("1"); // chart�� n��° �� ���� ���
				n++;
			}
			j++;
		}
	}
	menu(s, r);
}

// �޴�
void menu(subjectType* s, subjectType* r) {
	printf("\n_________________________________________________________\n");
	printf("                  ������û ���α׷�\n");
	printf("\t1) �˻� - ����\n");
	printf("\t2) �˻� - �г� / �б�\n");
	printf("\t3) �ð�ǥ ���� & ����\n");
	printf("\t4) ������\n");
	printf("_________________________________________________________\n");

	int num;
	scanf("%d", &num);
	switch (num) {
	case 1:
		search_name(s, r);  // �˻�- ����
		break;
	case 2:
		search_grade_semester(s, r); // �˻� - �г�/�б�
		break;
	case 3:
		show_schedule(s, r);
		break;
	case 4:
		exit(1);
	}
}

int main() {
	subjectType* s = (subjectType*)malloc(sizeof(subjectType)); // �� ����
	subjectType* r = (subjectType*)malloc(sizeof(subjectType)); // �� ����
	s->n = 39; r->n = 39;
	
	// �� ���� ����Ʈ�� ���� ���� (�����ʼ�����: ** / �����ٽɰ���: *)
	{
		// create_subject(s, ��ȣ, �г�, �б�, �̸�, ����1���۽ð�, ����2���۽ð�, ����1����ð�, ����2����ð�, ����1, ����2)
		// ����2�� ������ NULL ó��
		create_subject(s, 0, 1, 1, "**���м����Թ�**", 0, 0, 0, 0, 0, 0);
		create_subject(s, 1, 1, 1, "**���α׷��� ����1**", 0, 0, 0, 0, 0, 0);
		create_subject(s, 2, 1, 1, "��ǻ�� ����", 0, 0, 0, 0, 0, 0);
		create_subject(s, 3, 1, 1, "��ǻ�� ����1", 0, 0, 0, 0, 0, 0);
		create_subject(s, 4, 1, 2, "**�������**", 0, 0, 0, 0, 0, 0);
		create_subject(s, 5, 1, 2, "���α׷��� ����2", 0, 0, 0, 0, 0, 0);
		create_subject(s, 6, 1, 2, "**C���α׷���**", 0, 0, 0, 0, 0, 0);
		create_subject(s, 7, 1, 2, "��ǻ�� ����2", 0, 0, 0, 0, 0, 0);
		create_subject(s, 8, 2, 1, "**�������**", 0, 0, 0, 0, 0, 0);
		create_subject(s, 9, 2, 1, "**������ ����**", 0, 0, 0, 0, 0, 0);
		create_subject(s, 10, 2, 1, "**������ ����1**", 0, 0, 0, 0, 0, 0);
		create_subject(s, 11, 2, 1, "JAVA ���α׷���", 0, 0, 0, 0, 0, 0);
		create_subject(s, 12, 2, 1, "C ���α׷���", 0, 0, 0, 0, 0, 0);
		create_subject(s, 13, 2, 2, "**Ȯ�� �� ���**", 0, 0, 0, 0, 0, 0);
		create_subject(s, 14, 2, 2, "���� ����ȸ��", 0, 0, 0, 0, 0, 0);
		create_subject(s, 15, 2, 2, "**��ǻ�� ����**", 0, 0, 0, 0, 0, 0);
		create_subject(s, 16, 2, 2, "**������ ����2**", 0, 0, 0, 0, 0, 0);
		create_subject(s, 17, 2, 2, "��ü���� ���α׷���", 0, 0, 0, 0, 0, 0);
		create_subject(s, 18, 2, 2, "�� ���α׷���", 0, 0, 0, 0, 0, 0);
		create_subject(s, 19, 3, 1, "*�ü��*", 0, 0, 0, 0, 0, 0);
		create_subject(s, 20, 3, 1, "��ǻ�ͱ׷��Ƚ�", 0, 0, 0, 0, 0, 0);
		create_subject(s, 21, 3, 1, "����ó��", 0, 0, 0, 0, 0, 0);
		create_subject(s, 22, 3, 1, "*���α׷��� ����*", 0, 0, 0, 0, 0, 0);
		create_subject(s, 23, 3, 1, "�������� ���α׷���", 0, 0, 0, 0, 0, 0);
		create_subject(s, 24, 3, 1, "JAVA ���� ���α׷���", 0, 0, 0, 0, 0, 0);
		create_subject(s, 25, 3, 2, "*����ũ�� ���μ���*", 0, 0, 0, 0, 0, 0);
		create_subject(s, 26, 3, 2, "*��ǻ�� ��Ʈ��ũ*", 0, 0, 0, 0, 0, 0);
		create_subject(s, 27, 3, 2, "�ΰ�����", 0, 0, 0, 0, 0, 0);
		create_subject(s, 28, 3, 2, "*������ ���̽�*", 0, 0, 0, 0, 0, 0);
		create_subject(s, 29, 3, 2, "�����Ϸ�", 0, 0, 0, 0, 0, 0);
		create_subject(s, 30, 3, 2, "*����Ʈ�������*", 0, 0, 0, 0, 0, 0);
		create_subject(s, 31, 4, 1, "�����ȣ �� ����", 0, 0, 0, 0, 0, 0);
		create_subject(s, 32, 4, 1, "�Ӻ���� ����Ʈ����", 0, 0, 0, 0, 0, 0);
		create_subject(s, 33, 4, 1, "������ ����", 0, 0, 0, 0, 0, 0);
		create_subject(s, 34, 4, 1, "����Ʈ�� ���� ���α׷���", 0, 0, 0, 0, 0, 0);
		create_subject(s, 35, 4, 1, "�˰��� ����", 0, 0, 0, 0, 0, 0);
		create_subject(s, 36, 4, 2, "������ ���α׷���", 0, 0, 0, 0, 0, 0);
		create_subject(s, 37, 4, 2, "������ ����", 0, 0, 0, 0, 0, 0);
		create_subject(s, 38, 4, 2, "��� �� ���� ���α׷���", 0, 0, 0, 0, 0, 0);
	}

	// �� ���� ����Ʈ�� ���� ���� (������ ����)
	{
		create_subject(r, 0, 1, 1, "**���м����Թ�**", 0, 0, 0, 0, 0, 0);
		create_subject(r, 1, 1, 1, "**���α׷��� ����1**", 0, 0, 0, 0, 0, 0);
		create_subject(r, 2, 1, 1, "��ǻ�� ����", 0, 0, 0, 0, 0, 0);
		create_subject(r, 3, 1, 1, "��ǻ�� ����1", 0, 0, 0, 0, 0, 0);
		create_subject(r, 4, 1, 2, "**�������**", 0, 0, 0, 0, 0, 0);
		create_subject(r, 5, 1, 2, "���α׷��� ����2", 0, 0, 0, 0, 0, 0);
		create_subject(r, 6, 1, 2, "**C���α׷���**", 0, 0, 0, 0, 0, 0);
		create_subject(r, 7, 1, 2, "��ǻ�� ����2", 0, 0, 0, 0, 0, 0);
		create_subject(r, 8, 2, 1, "**�������**", 0, 0, 0, 0, 0, 0);
		create_subject(r, 9, 2, 1, "**������ ����**", 0, 0, 0, 0, 0, 0);
		create_subject(r, 10, 2, 1, "**������ ����1**", 0, 0, 0, 0, 0, 0);
		create_subject(r, 11, 2, 1, "JAVA ���α׷���", 0, 0, 0, 0, 0, 0);
		create_subject(r, 12, 2, 1, "C ���α׷���", 0, 0, 0, 0, 0, 0);
		create_subject(r, 13, 2, 2, "**Ȯ�� �� ���**", 0, 0, 0, 0, 0, 0);
		create_subject(r, 14, 2, 2, "���� ����ȸ��", 0, 0, 0, 0, 0, 0);
		create_subject(r, 15, 2, 2, "**��ǻ�� ����**", 0, 0, 0, 0, 0, 0);
		create_subject(r, 16, 2, 2, "**������ ����2**", 0, 0, 0, 0, 0, 0);
		create_subject(r, 17, 2, 2, "��ü���� ���α׷���", 0, 0, 0, 0, 0, 0);
		create_subject(r, 18, 2, 2, "�� ���α׷���", 0, 0, 0, 0, 0, 0);
		create_subject(r, 19, 3, 1, "*�ü��*", 0, 0, 0, 0, 0, 0);
		create_subject(r, 20, 3, 1, "��ǻ�ͱ׷��Ƚ�", 0, 0, 0, 0, 0, 0);
		create_subject(r, 21, 3, 1, "����ó��", 0, 0, 0, 0, 0, 0);
		create_subject(r, 22, 3, 1, "*���α׷��� ����*", 0, 0, 0, 0, 0, 0);
		create_subject(r, 23, 3, 1, "�������� ���α׷���", 0, 0, 0, 0, 0, 0);
		create_subject(r, 24, 3, 1, "JAVA ���� ���α׷���", 0, 0, 0, 0, 0, 0);
		create_subject(r, 25, 3, 2, "*����ũ�� ���μ���*", 0, 0, 0, 0, 0, 0);
		create_subject(r, 26, 3, 2, "*��ǻ�� ��Ʈ��ũ*", 0, 0, 0, 0, 0, 0);
		create_subject(r, 27, 3, 2, "�ΰ�����", 0, 0, 0, 0, 0, 0);
		create_subject(r, 28, 3, 2, "*������ ���̽�*", 0, 0, 0, 0, 0, 0);
		create_subject(r, 29, 3, 2, "�����Ϸ�", 0, 0, 0, 0, 0, 0);
		create_subject(r, 30, 3, 2, "*����Ʈ�������*", 0, 0, 0, 0, 0, 0);
		create_subject(r, 31, 4, 1, "�����ȣ �� ����", 0, 0, 0, 0, 0, 0);
		create_subject(r, 32, 4, 1, "�Ӻ���� ����Ʈ����", 0, 0, 0, 0, 0, 0);
		create_subject(r, 33, 4, 1, "������ ����", 0, 0, 0, 0, 0, 0);
		create_subject(r, 34, 4, 1, "����Ʈ�� ���� ���α׷���", 0, 0, 0, 0, 0, 0);
		create_subject(r, 35, 4, 1, "�˰��� ����", 0, 0, 0, 0, 0, 0);
		create_subject(r, 36, 4, 2, "������ ���α׷���", 0, 0, 0, 0, 0, 0);
		create_subject(r, 37, 4, 2, "������ ����", 0, 0, 0, 0, 0, 0);
		create_subject(r, 38, 4, 2, "��� �� ���� ���α׷���", 0, 0, 0, 0, 0, 0);
	}

	// �� ���� ����Ʈ�� ���� ����
	{
		s->list[0]->link1[0] = 5;
		s->list[1]->link1[0] = 5;
		s->list[2]->link1[0] = 5; 
		s->list[2]->link1[1] = 6;
		s->list[3]->link1[0] = 7;
		s->list[4]->link1[0] = 8;
		s->list[5]->link1[0] = 10;
		s->list[6]->link1[0] = 10;
		s->list[6]->link1[1] = 11;
		s->list[6]->link1[2] = 12;
		s->list[8]->link1[0] = 13;
		s->list[9]->link1[0] = 14;
		s->list[9]->link1[1] = 15;
		s->list[10]->link1[0] = 16;
		s->list[11]->link1[0] = 17;
		s->list[11]->link1[1] = 18;
		s->list[11]->link1[2] = 22;
		s->list[13]->link1[0] = 27;
		s->list[13]->link1[1] = 31;
		s->list[14]->link1[0] = 25; 
		s->list[15]->link1[0] = 19;
		s->list[16]->link1[0] = 20;
		s->list[16]->link1[1] = 21;
		s->list[16]->link1[2] = 27;
		s->list[17]->link1[0] = 22;
		s->list[17]->link1[1] = 23;
		s->list[18]->link1[0] = 38;
		s->list[19]->link1[0] = 26;
		s->list[20]->link1[0] = 33;
		s->list[21]->link1[0] = 28;
		s->list[22]->link1[0] = 29;
		s->list[22]->link1[1] = 30;
		s->list[25]->link1[0] = 32;
		s->list[26]->link1[0] = 32;
		s->list[27]->link1[0] = 33;
	}

	// �� ���� ����Ʈ�� ���� ���� (������ ����)
	{
		r->list[5]->link1[0] = 0; 
		r->list[5]->link1[1] = 1;
		r->list[5]->link1[1] = 2;
		r->list[6]->link1[0] = 2;
		r->list[7]->link1[0] = 3; //�Ŀ� 2 
		r->list[8]->link1[0] = 4; //������ 
		r->list[10]->link1[0] = 6;
		r->list[11]->link1[0] = 6;
		r->list[12]->link1[0] = 6;
		r->list[13]->link1[0] = 8; //Ȯ���� ���
		r->list[14]->link1[0] = 9;
		r->list[15]->link1[0] = 9;
		r->list[16]->link1[0] = 10;    //����2
		r->list[17]->link1[0] = 11;
		r->list[18]->link1[0] = 11;
		r->list[19]->link1[0] = 10;
		r->list[20]->link1[0] = 16;
		r->list[21]->link1[0] = 16;
		r->list[22]->link1[0] = 17;
		r->list[22]->link1[1] = 11;
		r->list[23]->link1[0] = 17;
		r->list[24]->link1[0] = 17;
		r->list[25]->link1[0] = 14;
		r->list[25]->link1[1] = 15;
		r->list[26]->link1[0] = 19;
		r->list[27]->link1[0] = 16;
		r->list[28]->link1[0] = 21;
		r->list[29]->link1[0] = 22;
		r->list[30]->link1[0] = 22;
		r->list[31]->link1[0] = 13;
		r->list[31]->link1[1] = 27;
		r->list[32]->link1[0] = 25;
		r->list[32]->link1[1] = 26;
		r->list[33]->link1[0] = 27;
		r->list[33]->link1[1] = 20;
		r->list[34]->link1[0] = 17;
		r->list[35]->link1[0] = 16;
	}

	// �� ���� ����Ʈ ���� (�� ���� ����)
	//r = reverse_sort(s);

	menu(s, r);

	printf("\n���α׷� ����");
	return 0;
}
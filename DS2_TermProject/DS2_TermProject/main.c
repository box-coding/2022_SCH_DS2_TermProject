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

subjectNode* chart[12] = { 0 }; // 수강신청한 과목
char schedule[20][5] = { 0, }; // 시각적 시간표
int chart_num = 0;  // 수강신청한 과목 개수
int sum = 0;		// 선택한 과목 총 학점

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
		fprintf(stderr, "스택이 비어있음\n");
		return NULL;
	}
	else
		return s->top;
}

// ------------------------------------------------------------ 함수 ------------------------------------------------------------

void menu(subjectType* s, subjectType* r);
void insert_schedule(subjectNode* subject);

// 노드 생성
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

// 역 정렬
subjectType* reverse_sort(subjectType* sub) {
	subjectType* r = (subjectType*)malloc(sizeof(subjectType));  // 역 인접 리스트 생성

	for (int i = 0; i < 39; i++) {
		stackType s;  // 스택
		init(&s);

		subjectNode* node = sub->list[i]->link;  // 임시 리스트

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

// 검색(과목)
void search_name(subjectType* pList, subjectType* fList) {
	printf("검색할 과목을 입력하세요:\n>>");
	char name[MAX];
	scanf("%s", &name);

	subjectNode* nodeP = pList->list[0];
	subjectNode* nodeF = fList->list[0];

	for (int i = 0; i <= pList->n; i++) {
		nodeP = pList->list[i]; // i번째 과목
		if (strcmp(nodeP->name, name) == 0) // 구하려는 과목과 i번쨰 과목의 이름이 같다면
			break;
	}
	
	for (int i = 0; i <= fList->n; i++) {
		nodeF = fList->list[i]; // i번째 과목
		if (strcmp(nodeF->name, name) == 0) // 구하려는 과목과 i번쨰 과목의 이름이 같다면
			break;
	}

	printf("\n검색 결과 (전공필수과목: ** / 전공핵심과목: *):\n");

	//선 선수 과목 출력
	for (int i = 0; i < 4;i++) {
		subjectNode* name1 = nodeP->link1[i];
		printf(" %s ", name1->name);
		if (nodeP->link1[i] == -1)
			break;
		else
			nodeP = pList->list[nodeP->link1[i]];
	}

	printf(" -> %s -> ", &name);

	// 후 선수 과목 출력
	for (int i = 1; i < 4; i++) {
		printf(" %s ", &nodeF->name);
		if (nodeF->link1[i] == -1)
			break;
		else
			nodeF = fList->list[nodeF->link1[i]];
	}

	printf("\n\n1) 시간표에 넣기 || 2) 메뉴로 돌아가기\n>>");
	int num;
	scanf("%d", &num);
	switch (num)
	{
	case 1:
		// 추가
		while (1) {
			printf("원하는 과목을 입력하세요 (취소: 0 입력)\n>>");
			char* n;
			scanf("%s", &n);
			subjectNode* node;
			int flag = 0;
			for (int i = 0; i <= pList->n; i++) {
				node = pList->list[i]; // i번째 과목
				if (strcmp(node->name, n) == 0){ // 구하려는 과목과 i번쨰 과목의 이름이 같다면
					chart[chart_num++] = node;
					insert_schedule(node);
					flag = 1;
					break;
				}
			}
			if (flag == 1) {
				printf("\n추가되었습니다\n");

			}
			else if (n == "0") {
				printf("\n취소되었습니다\n");
				break;
			}
			else
				printf("\n다시 입력해주세요.\n");
		}
		break;
	case 2: 
		menu(pList, fList);
		break;
	}

}


// 검색(학번/학기)
int* search_grade_semester(subjectType* pList, subjectType* fList) {
	int grade, semester;
	while (1) {
		printf("검색할 '학년' '학기' 를 입력하세요\n>>");
		scanf("%d %d", &grade, &semester);
		if (grade < 1 || grade>4 || semester < 1 || semester>2)
			printf("\n다시 입력해주세요\n");
		else
			break;
	}
	int index[40];
	int j = 0;
	subjectNode* node;

	for (int i = 0; i < pList->n; i++) { // 역 인접 리스트
		node = pList->list[i];

		if (node->grade == grade && node->semester == semester)
			index[j++] = i;
	}

	printf("검색 결과 (전공필수과목: ** / 전공핵심과목: *):\n");
	// 과목 출력
	for (int i = 0; i < j; i++) {
		printf("%s, ", &pList->list[index[i]]->name);
	}


	printf("\n\n1) 시간표에 넣기 || 2) 메뉴로 돌아가기\n>>");
	int num;
	scanf("%d", &num);
	switch (num)
	{
	case 1:
		// 추가
		while (1) {
			printf("원하는 과목을 입력하세요 (취소: 0 입력)\n>>");
			char n[MAX];
			scanf("%s", &n);
			subjectNode* node;
			int flag = 0;
			for (int i = 0; i <= pList->n; i++) {
				node = pList->list[i]; // i번째 과목
				if (strcmp(node->name, n) == 0) { // 구하려는 과목과 i번쨰 과목의 이름이 같다면
					chart[chart_num++] = node;
					insert_schedule(node);
					flag = 1;
					break;
				}
			}
			if (flag == 1) {
				printf("\n추가되었습니다\n");
			}
			else if (n == "0") {
				printf("\n취소되었습니다\n");
				break;
			}
			else
				printf("\n다시 입력해주세요.\n");
		}
		break;
	case 2:
		menu(pList, fList);
		break;
	}

}

// 시간표 삽입
void insert_schedule(subjectNode* subject) {

	for (int i = subject->time.start_time[0]; i < subject->time.finish_time[0]; i++)
		schedule[i][subject->time.week[0]] = '■';

	for (int i = subject->time.start_time[1]; i < subject->time.finish_time[1]; i++)
		schedule[i][subject->time.week[1]] = '■';

	sum += subject->score;
}

// 시간표 출력
void show_schedule(subjectType* s, subjectType* r) {
	// 시간표 형태로 출력
	printf("\n월 화 수 목 금");
	for (int i = 0; i < 19; i++)
		for (int j = 0; j < 4; j++) {
			if (schedule[i][j] == '■')
				printf("%c", schedule[i][j]);
			else
				printf(" ");
		}

	printf("\n____________________________________________");

	for (int i = 0; i < 5; i++) {
		switch (i)
		{
		case 0:
			printf("\n월요일: ");
			for (int i = 0; i < 12; i++)
				if (chart[i]->time.week == 0)
					printf("%s ", &chart[i]->name);
			break;
		case 1:
			printf("\n화요일: ");
			for (int i = 0; i < 12; i++)
				if (chart[i]->time.week == 0)
					printf("%s ", &chart[i]->name);
			break;
		case 2:
			printf("수요일: ");
			for (int i = 0; i < 12; i++)
				if (chart[i]->time.week == 0)
					printf("%s ", &chart[i]->name);
			break;
		case 3:
			printf("목요일: ");
			for (int i = 0; i < 12; i++)
				if (chart[i]->time.week == 0)
					printf("%s ", &chart[i]->name);
			break;
		case 4:
			printf("금요일: ");
			for (int i = 0; i < 12; i++)
				if (chart[i]->time.week == 0)
					printf("%s ", &chart[i]->name);
			break;
		default:
			break;
		}

		int j = 0; // 시간 (9시~ 6시반)
		while (j > 20) {
			int n = 0; // chart 항목 검사
			while (n = chart_num) {
				if (chart[n]->time.week == i)
					if (chart[n]->time.start_time == j)
						printf("1"); // chart의 n번째 값 정보 출력
				n++;
			}
			j++;
		}
	}
	menu(s, r);
}

// 메뉴
void menu(subjectType* s, subjectType* r) {
	printf("\n_________________________________________________________\n");
	printf("                  수강신청 프로그램\n");
	printf("\t1) 검색 - 과목\n");
	printf("\t2) 검색 - 학년 / 학기\n");
	printf("\t3) 시간표 보기 & 수정\n");
	printf("\t4) 나가기\n");
	printf("_________________________________________________________\n");

	int num;
	scanf("%d", &num);
	switch (num) {
	case 1:
		search_name(s, r);  // 검색- 과목
		break;
	case 2:
		search_grade_semester(s, r); // 검색 - 학년/학기
		break;
	case 3:
		show_schedule(s, r);
		break;
	case 4:
		exit(1);
	}
}

int main() {
	subjectType* s = (subjectType*)malloc(sizeof(subjectType)); // 후 선수
	subjectType* r = (subjectType*)malloc(sizeof(subjectType)); // 선 선수
	s->n = 39; r->n = 39;
	
	// 후 선수 리스트에 과목 세팅 (전공필수과목: ** / 전공핵심과목: *)
	{
		// create_subject(s, 번호, 학년, 학기, 이름, 요일1시작시간, 요일2시작시간, 요일1종료시간, 요일2종료시간, 요일1, 요일2)
		// 요일2가 없으면 NULL 처리
		create_subject(s, 0, 1, 1, "**공학설계입문**", 0, 0, 0, 0, 0, 0);
		create_subject(s, 1, 1, 1, "**프로그래밍 기초1**", 0, 0, 0, 0, 0, 0);
		create_subject(s, 2, 1, 1, "컴퓨팅 이해", 0, 0, 0, 0, 0, 0);
		create_subject(s, 3, 1, 1, "컴퓨터 영어1", 0, 0, 0, 0, 0, 0);
		create_subject(s, 4, 1, 2, "**전산수학**", 0, 0, 0, 0, 0, 0);
		create_subject(s, 5, 1, 2, "프로그래밍 기초2", 0, 0, 0, 0, 0, 0);
		create_subject(s, 6, 1, 2, "**C프로그래밍**", 0, 0, 0, 0, 0, 0);
		create_subject(s, 7, 1, 2, "컴퓨터 영어2", 0, 0, 0, 0, 0, 0);
		create_subject(s, 8, 2, 1, "**선형대수**", 0, 0, 0, 0, 0, 0);
		create_subject(s, 9, 2, 1, "**디지털 로직**", 0, 0, 0, 0, 0, 0);
		create_subject(s, 10, 2, 1, "**데이터 구조1**", 0, 0, 0, 0, 0, 0);
		create_subject(s, 11, 2, 1, "JAVA 프로그래밍", 0, 0, 0, 0, 0, 0);
		create_subject(s, 12, 2, 1, "C 프로그래밍", 0, 0, 0, 0, 0, 0);
		create_subject(s, 13, 2, 2, "**확률 및 통계**", 0, 0, 0, 0, 0, 0);
		create_subject(s, 14, 2, 2, "기초 전자회로", 0, 0, 0, 0, 0, 0);
		create_subject(s, 15, 2, 2, "**컴퓨터 구조**", 0, 0, 0, 0, 0, 0);
		create_subject(s, 16, 2, 2, "**데이터 구조2**", 0, 0, 0, 0, 0, 0);
		create_subject(s, 17, 2, 2, "객체지향 프로그래밍", 0, 0, 0, 0, 0, 0);
		create_subject(s, 18, 2, 2, "웹 프로그래밍", 0, 0, 0, 0, 0, 0);
		create_subject(s, 19, 3, 1, "*운영체제*", 0, 0, 0, 0, 0, 0);
		create_subject(s, 20, 3, 1, "컴퓨터그래픽스", 0, 0, 0, 0, 0, 0);
		create_subject(s, 21, 3, 1, "파일처리", 0, 0, 0, 0, 0, 0);
		create_subject(s, 22, 3, 1, "*프로그래밍 언어론*", 0, 0, 0, 0, 0, 0);
		create_subject(s, 23, 3, 1, "윈도우즈 프로그래밍", 0, 0, 0, 0, 0, 0);
		create_subject(s, 24, 3, 1, "JAVA 응용 프로그래밍", 0, 0, 0, 0, 0, 0);
		create_subject(s, 25, 3, 2, "*마이크로 프로세서*", 0, 0, 0, 0, 0, 0);
		create_subject(s, 26, 3, 2, "*컴퓨터 네트워크*", 0, 0, 0, 0, 0, 0);
		create_subject(s, 27, 3, 2, "인공지능", 0, 0, 0, 0, 0, 0);
		create_subject(s, 28, 3, 2, "*데이터 베이스*", 0, 0, 0, 0, 0, 0);
		create_subject(s, 29, 3, 2, "컴파일러", 0, 0, 0, 0, 0, 0);
		create_subject(s, 30, 3, 2, "*소프트웨어공학*", 0, 0, 0, 0, 0, 0);
		create_subject(s, 31, 4, 1, "현대암호 및 응용", 0, 0, 0, 0, 0, 0);
		create_subject(s, 32, 4, 1, "임베디드 소프트웨어", 0, 0, 0, 0, 0, 0);
		create_subject(s, 33, 4, 1, "빅데이터 이해", 0, 0, 0, 0, 0, 0);
		create_subject(s, 34, 4, 1, "스마트폰 응용 프로그래밍", 0, 0, 0, 0, 0, 0);
		create_subject(s, 35, 4, 1, "알고리즘 응용", 0, 0, 0, 0, 0, 0);
		create_subject(s, 36, 4, 2, "리눅스 프로그래밍", 0, 0, 0, 0, 0, 0);
		create_subject(s, 37, 4, 2, "딥러닝 이해", 0, 0, 0, 0, 0, 0);
		create_subject(s, 38, 4, 2, "고급 웹 응용 프로그래밍", 0, 0, 0, 0, 0, 0);
	}

	// 선 선수 리스트에 과목 세팅 (역정렬 실패)
	{
		create_subject(r, 0, 1, 1, "**공학설계입문**", 0, 0, 0, 0, 0, 0);
		create_subject(r, 1, 1, 1, "**프로그래밍 기초1**", 0, 0, 0, 0, 0, 0);
		create_subject(r, 2, 1, 1, "컴퓨팅 이해", 0, 0, 0, 0, 0, 0);
		create_subject(r, 3, 1, 1, "컴퓨터 영어1", 0, 0, 0, 0, 0, 0);
		create_subject(r, 4, 1, 2, "**전산수학**", 0, 0, 0, 0, 0, 0);
		create_subject(r, 5, 1, 2, "프로그래밍 기초2", 0, 0, 0, 0, 0, 0);
		create_subject(r, 6, 1, 2, "**C프로그래밍**", 0, 0, 0, 0, 0, 0);
		create_subject(r, 7, 1, 2, "컴퓨터 영어2", 0, 0, 0, 0, 0, 0);
		create_subject(r, 8, 2, 1, "**선형대수**", 0, 0, 0, 0, 0, 0);
		create_subject(r, 9, 2, 1, "**디지털 로직**", 0, 0, 0, 0, 0, 0);
		create_subject(r, 10, 2, 1, "**데이터 구조1**", 0, 0, 0, 0, 0, 0);
		create_subject(r, 11, 2, 1, "JAVA 프로그래밍", 0, 0, 0, 0, 0, 0);
		create_subject(r, 12, 2, 1, "C 프로그래밍", 0, 0, 0, 0, 0, 0);
		create_subject(r, 13, 2, 2, "**확률 및 통계**", 0, 0, 0, 0, 0, 0);
		create_subject(r, 14, 2, 2, "기초 전자회로", 0, 0, 0, 0, 0, 0);
		create_subject(r, 15, 2, 2, "**컴퓨터 구조**", 0, 0, 0, 0, 0, 0);
		create_subject(r, 16, 2, 2, "**데이터 구조2**", 0, 0, 0, 0, 0, 0);
		create_subject(r, 17, 2, 2, "객체지향 프로그래밍", 0, 0, 0, 0, 0, 0);
		create_subject(r, 18, 2, 2, "웹 프로그래밍", 0, 0, 0, 0, 0, 0);
		create_subject(r, 19, 3, 1, "*운영체제*", 0, 0, 0, 0, 0, 0);
		create_subject(r, 20, 3, 1, "컴퓨터그래픽스", 0, 0, 0, 0, 0, 0);
		create_subject(r, 21, 3, 1, "파일처리", 0, 0, 0, 0, 0, 0);
		create_subject(r, 22, 3, 1, "*프로그래밍 언어론*", 0, 0, 0, 0, 0, 0);
		create_subject(r, 23, 3, 1, "윈도우즈 프로그래밍", 0, 0, 0, 0, 0, 0);
		create_subject(r, 24, 3, 1, "JAVA 응용 프로그래밍", 0, 0, 0, 0, 0, 0);
		create_subject(r, 25, 3, 2, "*마이크로 프로세서*", 0, 0, 0, 0, 0, 0);
		create_subject(r, 26, 3, 2, "*컴퓨터 네트워크*", 0, 0, 0, 0, 0, 0);
		create_subject(r, 27, 3, 2, "인공지능", 0, 0, 0, 0, 0, 0);
		create_subject(r, 28, 3, 2, "*데이터 베이스*", 0, 0, 0, 0, 0, 0);
		create_subject(r, 29, 3, 2, "컴파일러", 0, 0, 0, 0, 0, 0);
		create_subject(r, 30, 3, 2, "*소프트웨어공학*", 0, 0, 0, 0, 0, 0);
		create_subject(r, 31, 4, 1, "현대암호 및 응용", 0, 0, 0, 0, 0, 0);
		create_subject(r, 32, 4, 1, "임베디드 소프트웨어", 0, 0, 0, 0, 0, 0);
		create_subject(r, 33, 4, 1, "빅데이터 이해", 0, 0, 0, 0, 0, 0);
		create_subject(r, 34, 4, 1, "스마트폰 응용 프로그래밍", 0, 0, 0, 0, 0, 0);
		create_subject(r, 35, 4, 1, "알고리즘 응용", 0, 0, 0, 0, 0, 0);
		create_subject(r, 36, 4, 2, "리눅스 프로그래밍", 0, 0, 0, 0, 0, 0);
		create_subject(r, 37, 4, 2, "딥러닝 이해", 0, 0, 0, 0, 0, 0);
		create_subject(r, 38, 4, 2, "고급 웹 응용 프로그래밍", 0, 0, 0, 0, 0, 0);
	}

	// 후 선수 리스트에 과목 연결
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

	// 선 선수 리스트에 과목 연결 (역정렬 실패)
	{
		r->list[5]->link1[0] = 0; 
		r->list[5]->link1[1] = 1;
		r->list[5]->link1[1] = 2;
		r->list[6]->link1[0] = 2;
		r->list[7]->link1[0] = 3; //컴영 2 
		r->list[8]->link1[0] = 4; //선행대수 
		r->list[10]->link1[0] = 6;
		r->list[11]->link1[0] = 6;
		r->list[12]->link1[0] = 6;
		r->list[13]->link1[0] = 8; //확률과 통계
		r->list[14]->link1[0] = 9;
		r->list[15]->link1[0] = 9;
		r->list[16]->link1[0] = 10;    //데구2
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

	// 선 선수 리스트 생성 (역 정렬 실패)
	//r = reverse_sort(s);

	menu(s, r);

	printf("\n프로그램 종료");
	return 0;
}
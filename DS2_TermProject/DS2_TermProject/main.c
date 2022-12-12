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
	int grade;
	int semester;
	Time time;
	char name[MAX];
	int score;
	struct subjectNode* link;
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
typedef struct stackType {
	subjectNode* stack[MAX];
	int top;
}stackType;

void init(stackType* s) {
	s->top = -1;
}

int is_empty(stackType* s) {
	return (s->top == -1);
}

int is_full(stackType* s) {
	return (s->top == MAX - 1);
}

void push(stackType* s, subjectNode* node) {
	if (!is_full(s))
		s->stack[++(s->top)] = node;
}

subjectNode* pop(stackType* s) {
	if (is_empty(s)) {
		return s->stack[(s->top)--];
	}
}

// ------------------------------------------------------------ 함수 ------------------------------------------------------------
// 노드 생성
void create_subject(subjectType* g, int index, int grade, int semester, 
	char name[], int start_time1, int start_time2, int finish_time1, int finish_time2, int week1, int week2) {
	subjectNode* node = (subjectNode*)malloc(sizeof(subjectNode));
	node->grade = grade;
	node->semester = semester;
	strcpy(node->name, name);
	node->time.start_time[0] = start_time1;
	node->time.start_time[1] = start_time2;
	node->time.finish_time[0] = finish_time1;
	node->time.finish_time[1] = finish_time2;
	node->time.week[0] = week1;
	node->time.week[1] = week2;
	node->link = NULL;
	node->link = g->list[index];
	g->list[index] = node;
}


// 역 정렬
subjectType* reverse_sort(subjectType* sub, subjectType* r) {

	for (int i = 0; i < 39; i++) {
		stackType s;  // 스택
		init(&s);

		// 리스트의 i번째 노드
		subjectNode* node = sub->list[i];

		// 스택에 리스트 한줄 넣기
		do{
			node = node->link;
			printf("11%s11 \n", node->name);
			push(&s, node);
			if (node->link == NULL)
				break;
			printf("프린트\n");
		} while (node->link != NULL);
		
		// 스택에 해당하는 위치에 i번째 node 넣기
		int j = 0;
		while (!is_empty(&s)) {
			printf("22%s %s \n", r->list[j]->name, node->name);
			// if 조건 오류
			if(strncmp(r->list[j]->name, node->name, sizeof(node->name)) == 0) {
				subjectNode* node1 = pop(&s);
				node->link = r->list[j];
				r->list[j++] = node;
				printf("삽입");
			}
			printf("비교 실패");
		}
	}
	return r;
}

// 검색(과목)
// 검색어(과목) 받기
void search_name() {

}

// 후 선수 과목
subjectNode* search_next_name(char* name, subjectType* fList) {
	subjectNode* node;

	for (int i = 0; i < fList->n; i++) { // 인접 리스트의 i번째 과목
		node = fList->list[i];

		if (node->name == name) // 구하려는 과목과 i번째 과목의 이름이 같다면
			return node;		// 노드 반환
	}
	return NULL;
}

// 선 선수 과목
subjectNode* search_pre_name(char* name, subjectType* pList) {
	subjectNode* node;

	for (int i = 0; i <= pList->n; i++) {
		node = pList->list[i]; // 역 인접리스트의 i번째 과목

		if (node->name == name) // 구하려는 과목과 i번쨰 과목의 이름이 같다면
			return node;		// 노드 반환
	}

	return NULL;
}

// 검색어(학번/학기) 받기
void search_GS() {

}

// 검색(학번/학기)
int* search_grade_semester(int grade, int semester, subjectType* pList) {
	int index[40];
	int j = 0;
	subjectNode* node;

	for (int i = 0; i < pList->n; i++) { // 역 인접 리스트
		node = pList->list[i];

		if (node->grade == grade && node->semester == semester)
			index[j++] = i;
	}
	return index;
}

// 시간표 삽입
void insert_schedule(subjectNode subject) {
	for (int i = subject.time.start_time[0]; i < subject.time.finish_time[0]; i++)
		schedule[i][subject.time.week[0]] = '■';

	for (int i = subject.time.start_time[1]; i < subject.time.finish_time[1]; i++)
		schedule[i][subject.time.week[1]] = '■';

	sum += subject.score;
}

// 시간표 출력
void show_schedule() {
	// 시간표 형태로 출력
	printf("월 화 수 목 금");
	for (int i = 0; i < 19; i++)
		for (int j = 0; j < 4; j++) {
			if (schedule[i][j] == '■')
				printf("%c", schedule[i][j]);
			else
				printf(" ");
		}

	printf("----------------------------");

	for (int i = 0; i < 5; i++) {
		switch (i)
		{
		case 0:
			printf("월요일: ");
			break;
		case 1:
			printf("화요일: ");
			break;
		case 2:
			printf("수요일: ");
			break;
		case 3:
			printf("목요일: ");
			break;
		case 4:
			printf("금요일: ");
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
}

// 메뉴
void menu() {
	int num;
	scanf("%d", &num);
	switch (num) {
	case 1:
		search_name();  // 검색- 과목
		break;
	case 2:
		search_GS(); // 검색 - 학년/학기
		break;
	case 3:
		show_schedule();
		break;
	case 4:
		exit(1);
	}
}

// 검색
void search() {
	int num;
	scanf("%d", &num);
	switch (num) {
	case 1:
		search_name();
		break;
	case 2:
		search_GS();
		break;
	case 3:
		break;
	}
}

int main() {
	subjectType* l = (subjectType*)malloc(sizeof(subjectType));
	subjectType* s = (subjectType*)malloc(sizeof(subjectType)); // 후 선수
	subjectType* r = (subjectType*)malloc(sizeof(subjectType)); // 선 선수
	s->n = 39;
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
		printf("create subject clear\n");
	}
	
	r = s; l = s;

	// 후 선수 리스트에 과목 연결
	{
		s->list[0]->link = l->list[5];
		s->list[0]->link->link = NULL;
		printf("clear\n");
		s->list[1]->link = l->list[5];
		s->list[1]->link->link = NULL;
		s->list[2]->link = s->list[5]; s->list[2]->link->link = s->list[6];
		s->list[2]->link->link->link = NULL;
		s->list[3]->link = s->list[7]; // 컴영
		s->list[3]->link->link = NULL;
		s->list[4]->link = s->list[8];
		s->list[4]->link->link = NULL;
		s->list[5]->link = s->list[10];
		s->list[5]->link->link = NULL;
		s->list[6]->link = s->list[10]; s->list[6]->link->link = s->list[11]; s->list[6]->link->link->link = s->list[12];
		s->list[6]->link->link->link->link = NULL;
		s->list[7]->link = NULL;
		s->list[8]->link = s->list[13];
		s->list[8]->link->link = NULL;
		s->list[9]->link = s->list[14]; s->list[9]->link->link = s->list[15];
		s->list[9]->link->link->link = NULL;
		s->list[10]->link = s->list[16];
		s->list[10]->link->link = NULL;
		s->list[11]->link = s->list[17]; s->list[11]->link->link = s->list[18]; s->list[11]->link->link->link = s->list[22];
		s->list[11]->link->link->link->link = NULL;
		s->list[12]->link = NULL;
		s->list[13]->link = s->list[27]; s->list[13]->link->link = s->list[31];
		s->list[13]->link->link->link = NULL;
		s->list[14]->link = s->list[25]; // 기전회
		s->list[14]->link->link = NULL;
		s->list[15]->link = s->list[19];
		s->list[15]->link->link = NULL;
		s->list[16]->link = s->list[20]; s->list[16]->link->link = s->list[21]; s->list[16]->link->link->link = s->list[27];
		s->list[16]->link->link->link->link = NULL;
		s->list[17]->link = s->list[22]; s->list[17]->link->link = s->list[23];
		s->list[17]->link->link->link = NULL;
		s->list[18]->link = s->list[38]; // 웹프 18
		s->list[18]->link->link = NULL;
		s->list[19]->link = s->list[26];
		s->list[19]->link->link = NULL;
		s->list[20]->link = s->list[33];
		s->list[20]->link->link = NULL;
		s->list[21]->link = s->list[28];
		s->list[21]->link->link = NULL;
		s->list[22]->link = s->list[29]; s->list[22]->link->link = s->list[30];
		s->list[22]->link->link->link = NULL;
		s->list[23]->link = NULL;
		s->list[24]->link = NULL;
		s->list[25]->link = s->list[32];
		s->list[25]->link->link = NULL;
		s->list[26]->link = s->list[32];
		s->list[26]->link->link = NULL;
		s->list[27]->link = s->list[33];
		s->list[27]->link->link = NULL;
		s->list[28]->link = NULL;
		s->list[29]->link = NULL;
		s->list[30]->link = NULL;
		s->list[31]->link = NULL;
		s->list[32]->link = NULL;
		s->list[33]->link = NULL;
		s->list[34]->link = NULL;
		s->list[35]->link = NULL;
		s->list[36]->link = NULL;
		s->list[37]->link = NULL;
		s->list[38]->link = NULL;
		printf("connect list clear\n");
	}

	// 선 선수 리스트 생성
	r = reverse_sort(s, r);

	return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

typedef struct Time {
	int start_time;
	int finish_time;
	int week;
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

subjectNode* chart[12] = { 0 };
char schedule[20][5] = { 0, };
int chart_num = 0;  // ½Ã°£Ç¥¿¡ ³ÖÀº °ú¸ñ °³¼ö
int sum = 0;		// ¼±ÅÃÇÑ °ú¸ñ ÃÑ ÇÐÁ¡

<<<<<<< HEAD
// ------------------------------------------------------------ stack ------------------------------------------------------------
=======
// -------------------- stack --------------------

typedef struct StackNode {
	subjectNode* node;
	struct StackNode* link;
}StackNode;

>>>>>>> parent of 48029d2 (í•œ ê³¼ëª© ë‹¹ ì‹œê°„ 2ê°œë¡œ ìˆ˜ì •)
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

// -------------------- ÇÔ¼ö --------------------

// ³ëµå »ý¼º
void create_subject(subjectType* g, int index, int grade, int semester, char name[], int start_time, int finish_time, int week) {
	subjectNode* node = (subjectNode*)malloc(sizeof(subjectNode));
	node->grade = grade;
	node->semester = semester;
<<<<<<< HEAD
	strcpy(node->name, name);
	node->time.start_time[0] = start_time1;
	node->time.start_time[1] = start_time2;
	node->time.finish_time[0] = finish_time1;
	node->time.finish_time[1] = finish_time2;
	node->time.week[0] = week1;
	node->time.week[1] = week2;
=======
	memset(node->name, name, sizeof(char));
	node->time.start_time = start_time;
	node->time.finish_time = finish_time;
	node->time.week = week;
>>>>>>> parent of 48029d2 (í•œ ê³¼ëª© ë‹¹ ì‹œê°„ 2ê°œë¡œ ìˆ˜ì •)
	node->link = NULL;
	node->link = g->list[index];
	g->list[index] = node;
}


// ¿ª Á¤·Ä
subjectType* reverse_sort(subjectType* sub, subjectType* r) {

	for (int i = 0; i < 39; i++) {
		stackType s;  // ½ºÅÃ
		init(&s);

		// ¸®½ºÆ®ÀÇ i¹øÂ° ³ëµå
		subjectNode* node = sub->list[i];

		// ½ºÅÃ¿¡ ¸®½ºÆ® ÇÑÁÙ ³Ö±â
		do{
			node = node->link;
			printf("11%s11 \n", node->name);
			push(&s, node);
			if (node->link == NULL)
				break;
<<<<<<< HEAD
			printf("ÇÁ¸°Æ®\n");
		} while (node->link != NULL);
		
		// ½ºÅÃ¿¡ ÇØ´çÇÏ´Â À§Ä¡¿¡ i¹øÂ° node ³Ö±â
		int j = 0;
=======
			subjectNode* tmp = node->link;
			node = tmp;
		}

>>>>>>> parent of 48029d2 (í•œ ê³¼ëª© ë‹¹ ì‹œê°„ 2ê°œë¡œ ìˆ˜ì •)
		while (!is_empty(&s)) {
			printf("22%s %s \n", r->list[j]->name, node->name);
			// if Á¶°Ç ¿À·ù
			if(strncmp(r->list[j]->name, node->name, sizeof(node->name)) == 0) {
				subjectNode* node1 = pop(&s);
				node->link = r->list[j];
				r->list[j++] = node;
				printf("»ðÀÔ");
			}
			printf("ºñ±³ ½ÇÆÐ");
		}
	}
	return r;
}

// °Ë»ö(°ú¸ñ)
// °Ë»ö¾î(°ú¸ñ) ¹Þ±â
void search_name() {

}

// ÈÄ ¼±¼ö °ú¸ñ
subjectNode* search_next_name(char* name, subjectType* fList) {
	subjectNode* node;

	for (int i = 0; i < fList->n; i++) { // ÀÎÁ¢ ¸®½ºÆ®ÀÇ i¹øÂ° °ú¸ñ
		node = fList->list[i];

		if (node->name == name) // ±¸ÇÏ·Á´Â °ú¸ñ°ú i¹øÂ° °ú¸ñÀÇ ÀÌ¸§ÀÌ °°´Ù¸é
			return node;		// ³ëµå ¹ÝÈ¯
	}
	return NULL;
}

// ¼± ¼±¼ö °ú¸ñ
subjectNode* search_pre_name(char* name, subjectType* pList) {
	subjectNode* node;

	for (int i = 0; i <= pList->n; i++) {
		node = pList->list[i]; // ¿ª ÀÎÁ¢¸®½ºÆ®ÀÇ i¹øÂ° °ú¸ñ

		if (node->name == name) // ±¸ÇÏ·Á´Â °ú¸ñ°ú i¹ø¤Š °ú¸ñÀÇ ÀÌ¸§ÀÌ °°´Ù¸é
			return node;		// ³ëµå ¹ÝÈ¯
	}

	return NULL;
}

// °Ë»ö¾î(ÇÐ¹ø/ÇÐ±â) ¹Þ±â
void search_GS() {

}

// °Ë»ö(ÇÐ¹ø/ÇÐ±â)
int* search_grade_semester(int grade, int semester, subjectType* pList) {
	int index[40];
	int j = 0;
	subjectNode* node;

	for (int i = 0; i < pList->n; i++) { // ¿ª ÀÎÁ¢ ¸®½ºÆ®
		node = pList->list[i];

		if (node->grade == grade && node->semester == semester)
			index[j++] = i;
	}
	return index;
}

// ½Ã°£Ç¥ »ðÀÔ
void insert_schedule(subjectNode subject) {
	for (int i = subject.time.start_time; i < subject.time.finish_time; i++)
		schedule[i][subject.time.week] = '¡á';

	sum += subject.score;
}

// ½Ã°£Ç¥ Ãâ·Â
void show_schedule() {
	// ½Ã°£Ç¥ ÇüÅÂ·Î Ãâ·Â
	printf("¿ù È­ ¼ö ¸ñ ±Ý");
	for (int i = 0; i < 19; i++)
		for (int j = 0; j < 4; j++) {
			if (schedule[i][j] == '¡á')
				printf("%c", schedule[i][j]);
			else
				printf(" ");
		}

	printf("----------------------------");

	for (int i = 0; i < 5; i++) {
		switch (i)
		{
		case 0:
			printf("¿ù¿äÀÏ: ");
			break;
		case 1:
			printf("È­¿äÀÏ: ");
			break;
		case 2:
			printf("¼ö¿äÀÏ: ");
			break;
		case 3:
			printf("¸ñ¿äÀÏ: ");
			break;
		case 4:
			printf("±Ý¿äÀÏ: ");
			break;
		default:
			break;
		}

		int j = 0; // ½Ã°£ (9½Ã~ 6½Ã¹Ý)
		while (j > 20) {
			int n = 0; // chart Ç×¸ñ °Ë»ç
			while (n = chart_num) {
				if (chart[n]->time.week == i)
					if (chart[n]->time.start_time == j)
						printf("1"); // chartÀÇ n¹øÂ° °ª Á¤º¸ Ãâ·Â
				n++;
			}
			j++;
		}
	}
}

// ¸Þ´º
void menu() {
	int num;
	scanf("%d", &num);
	switch (num) {
	case 1:
		search_name();  // °Ë»ö- °ú¸ñ
		break;
	case 2:
		search_GS(); // °Ë»ö - ÇÐ³â/ÇÐ±â
		break;
	case 3:
		show_schedule();
		break;
	case 4:
		exit(1);
	}
}

// °Ë»ö
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
	subjectType* s = (subjectType*)malloc(sizeof(subjectType)); // ÈÄ ¼±¼ö
	subjectType* r = (subjectType*)malloc(sizeof(subjectType)); // ¼± ¼±¼ö
	s->n = 39;
	// ÈÄ ¼±¼ö ¸®½ºÆ®¿¡ °ú¸ñ ¼¼ÆÃ (Àü°øÇÊ¼ö°ú¸ñ: ** / Àü°øÇÙ½É°ú¸ñ: *)
	{
		//create_subject(s, ¹øÈ£, ÇÐ³â, ÇÐ±â, ÀÌ¸§, ½ÃÀÛ½Ã°£, ³¡³ª´Â ½Ã°£, ¿äÀÏ)
		create_subject(s, 0, 1, 1, "**°øÇÐ¼³°èÀÔ¹®**", 0, 0, 0);
		printf("clear\n");
		create_subject(s, 1, 1, 1, "**ÇÁ·Î±×·¡¹Ö ±âÃÊ1**", 0, 0, 0);
		create_subject(s, 2, 1, 1, "ÄÄÇ»ÆÃ ÀÌÇØ", 0, 0, 0);
		create_subject(s, 3, 1, 1, "ÄÄÇ»ÅÍ ¿µ¾î1", 0, 0, 0);
		create_subject(s, 4, 1, 2, "**Àü»ê¼öÇÐ**", 0, 0, 0);
		create_subject(s, 5, 1, 2, "ÇÁ·Î±×·¡¹Ö ±âÃÊ2", 0, 0, 0);
		create_subject(s, 6, 1, 2, "**CÇÁ·Î±×·¡¹Ö**", 0, 0, 0);
		create_subject(s, 7, 1, 2, "ÄÄÇ»ÅÍ ¿µ¾î2", 0, 0, 0);
		create_subject(s, 8, 2, 1, "**¼±Çü´ë¼ö**", 0, 0, 0);
		create_subject(s, 9, 2, 1, "**µðÁöÅÐ ·ÎÁ÷**", 0, 0, 0);
		create_subject(s, 10, 2, 1, "**µ¥ÀÌÅÍ ±¸Á¶1**", 0, 0, 0);
		create_subject(s, 11, 2, 1, "JAVA ÇÁ·Î±×·¡¹Ö", 0, 0, 0);
		create_subject(s, 12, 2, 1, "C ÇÁ·Î±×·¡¹Ö", 0, 0, 0);
		create_subject(s, 13, 2, 2, "**È®·ü ¹× Åë°è**", 0, 0, 0);
		create_subject(s, 14, 2, 2, "±âÃÊ ÀüÀÚÈ¸·Î", 0, 0, 0);
		create_subject(s, 15, 2, 2, "**ÄÄÇ»ÅÍ ±¸Á¶**", 0, 0, 0);
		create_subject(s, 16, 2, 2, "**µ¥ÀÌÅÍ ±¸Á¶2**", 0, 0, 0);
		create_subject(s, 17, 2, 2, "°´Ã¼ÁöÇâ ÇÁ·Î±×·¡¹Ö", 0, 0, 0);
		create_subject(s, 18, 2, 2, "À¥ ÇÁ·Î±×·¡¹Ö", 0, 0, 0);
		create_subject(s, 19, 3, 1, "*¿î¿µÃ¼Á¦*", 0, 0, 0);
		create_subject(s, 20, 3, 1, "ÄÄÇ»ÅÍ±×·¡ÇÈ½º", 0, 0, 0);
		create_subject(s, 21, 3, 1, "ÆÄÀÏÃ³¸®", 0, 0, 0);
		create_subject(s, 22, 3, 1, "*ÇÁ·Î±×·¡¹Ö ¾ð¾î·Ð*", 0, 0, 0);
		create_subject(s, 23, 3, 1, "À©µµ¿ìÁî ÇÁ·Î±×·¡¹Ö", 0, 0, 0);
		create_subject(s, 24, 3, 1, "JAVA ÀÀ¿ë ÇÁ·Î±×·¡¹Ö", 0, 0, 0);
		create_subject(s, 25, 3, 2, "*¸¶ÀÌÅ©·Î ÇÁ·Î¼¼¼­*", 0, 0, 0);
		create_subject(s, 26, 3, 2, "*ÄÄÇ»ÅÍ ³×Æ®¿öÅ©*", 0, 0, 0);
		create_subject(s, 27, 3, 2, "ÀÎ°øÁö´É", 0, 0, 0);
		create_subject(s, 28, 3, 2, "*µ¥ÀÌÅÍ º£ÀÌ½º*", 0, 0, 0);
		create_subject(s, 29, 3, 2, "ÄÄÆÄÀÏ·¯", 0, 0, 0);
		create_subject(s, 30, 3, 2, "*¼ÒÇÁÆ®¿þ¾î°øÇÐ*", 0, 0, 0);
		create_subject(s, 31, 4, 1, "Çö´ë¾ÏÈ£ ¹× ÀÀ¿ë", 0, 0, 0);
		create_subject(s, 32, 4, 1, "ÀÓº£µðµå ¼ÒÇÁÆ®¿þ¾î", 0, 0, 0);
		create_subject(s, 33, 4, 1, "ºòµ¥ÀÌÅÍ ÀÌÇØ", 0, 0, 0);
		create_subject(s, 34, 4, 1, "½º¸¶Æ®Æù ÀÀ¿ë ÇÁ·Î±×·¡¹Ö", 0, 0, 0);
		create_subject(s, 35, 4, 1, "¾Ë°í¸®Áò ÀÀ¿ë", 0, 0, 0);
		create_subject(s, 36, 4, 2, "¸®´ª½º ÇÁ·Î±×·¡¹Ö", 0, 0, 0);
		create_subject(s, 37, 4, 2, "µö·¯´× ÀÌÇØ", 0, 0, 0);
		create_subject(s, 38, 4, 2, "°í±Þ À¥ ÀÀ¿ë ÇÁ·Î±×·¡¹Ö", 0, 0, 0);
		printf("create subject clear\n");
	}
	
	r = s; l = s;

	// ÈÄ ¼±¼ö ¸®½ºÆ®¿¡ °ú¸ñ ¿¬°á
	{
		s->list[0]->link = l->list[5];
		s->list[0]->link->link = NULL;
		printf("clear\n");
		s->list[1]->link = l->list[5];
		s->list[1]->link->link = NULL;
		s->list[2]->link = s->list[5]; s->list[2]->link->link = s->list[6];
		s->list[2]->link->link->link = NULL;
		s->list[3]->link = s->list[7]; // ÄÄ¿µ
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
		s->list[14]->link = s->list[25]; // ±âÀüÈ¸
		s->list[14]->link->link = NULL;
		s->list[15]->link = s->list[19];
		s->list[15]->link->link = NULL;
		s->list[16]->link = s->list[20]; s->list[16]->link->link = s->list[21]; s->list[16]->link->link->link = s->list[27];
		s->list[16]->link->link->link->link = NULL;
		s->list[17]->link = s->list[22]; s->list[17]->link->link = s->list[23];
		s->list[17]->link->link->link = NULL;
		s->list[18]->link = s->list[38]; // À¥ÇÁ 18
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

	// ¼± ¼±¼ö ¸®½ºÆ® »ý¼º
	r = reverse_sort(s, r);


	return 0;
}
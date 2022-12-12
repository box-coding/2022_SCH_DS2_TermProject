#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 40

void search_name() {
	//show과목에 대한  선선수, 후선수 show();
	int chose;

	printf("1.시간표에 넣기,2.재검색,3메뉴");
	scanf_s("%d", &chose);
	switch (chose) {
	case1:
		//시간표에 넣기 
	case2:
		
	case 3:
	default:
		break;
	}

}
void search_GS() {
	int chose;
	//학년학기에 대한 과목 리스트 출력 

	printf("1.시간표에 넣기,2.재검색,3메뉴");
	scanf_s("%d", &chose);
	switch (chose) {
	case1:
		//시간표에 넣기 
	case2:

	case 3:
	default:
		break;
	}
}
show_schedul() {
	//시간ㅍ ㅛ 출력 
	char subject[MAX];
	int chose;
	printf("과목 입력:");
	gets(subject);
	printf("%s 1.삭제, 2.삽입", subject);
	scanf_s("%d", &chose);
	if (chose == 1) {
		//시간표에서 과목 삭제 
	}
	else if (chose == 2) {
		//시간표에서 과목 삽입
	}
	else {
		printf("error");
	}
}
int main() {
	int chose=5;
	int loop = 1;
	char id[MAX];
	char year[MAX];

	printf("수강신청 프로그램\n");
	while (loop) {
		printf("아이디: ");
		gets(id);
		printf("패스워드: ");
		gets(year);
		if (strcmp(id," ")==0||strcmp(year," ")==0) {
			continue;
		}
		break;
	}
	while (loop) {
		printf("1.검색(과목)\n");
		printf("2.검색(학년/학기)\n");
		printf("3.시간표 보기\n");
		printf("4.종료\n");
		printf("입력: ");
		scanf("%d",&chose);
		switch (chose) {
		case 1:
			search_name();
			break;
		case 2:
			search_GS();
			break;
		case 3:
			show_schedule();
			break;
		case 4:
			loop = 0;
			break;
		default:
			printf("잘못입력하셨습니다 다시 입력하세요\n");
			continue;
		}
	}
	return 0;
}
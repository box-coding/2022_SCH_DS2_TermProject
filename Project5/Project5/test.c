#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 40

void search_name() {
	//show���� ����  ������, �ļ��� show();
	int chose;

	printf("1.�ð�ǥ�� �ֱ�,2.��˻�,3�޴�");
	scanf_s("%d", &chose);
	switch (chose) {
	case1:
		//�ð�ǥ�� �ֱ� 
	case2:
		
	case 3:
	default:
		break;
	}

}
void search_GS() {
	int chose;
	//�г��б⿡ ���� ���� ����Ʈ ��� 

	printf("1.�ð�ǥ�� �ֱ�,2.��˻�,3�޴�");
	scanf_s("%d", &chose);
	switch (chose) {
	case1:
		//�ð�ǥ�� �ֱ� 
	case2:

	case 3:
	default:
		break;
	}
}
show_schedul() {
	//�ð��� �� ��� 
	char subject[MAX];
	int chose;
	printf("���� �Է�:");
	gets(subject);
	printf("%s 1.����, 2.����", subject);
	scanf_s("%d", &chose);
	if (chose == 1) {
		//�ð�ǥ���� ���� ���� 
	}
	else if (chose == 2) {
		//�ð�ǥ���� ���� ����
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

	printf("������û ���α׷�\n");
	while (loop) {
		printf("���̵�: ");
		gets(id);
		printf("�н�����: ");
		gets(year);
		if (strcmp(id," ")==0||strcmp(year," ")==0) {
			continue;
		}
		break;
	}
	while (loop) {
		printf("1.�˻�(����)\n");
		printf("2.�˻�(�г�/�б�)\n");
		printf("3.�ð�ǥ ����\n");
		printf("4.����\n");
		printf("�Է�: ");
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
			printf("�߸��Է��ϼ̽��ϴ� �ٽ� �Է��ϼ���\n");
			continue;
		}
	}
	return 0;
}
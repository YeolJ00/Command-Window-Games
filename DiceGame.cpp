#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

void MyState();
void DRG();

int Cash = 100000, Wins = 0, Loses = 0;

int main() {
	srand(time(NULL));
	char choice;
	while (true) {
		system("cls");
		while (true) {
			printf("1. My State \n2. Dice Rolling Game \n3. End \n\nEnter your choice :");
			choice = getchar();
			if (choice ==49 || choice == 50 || choice == 51) {
				break;
			}
			else {
				choice = 0;
				break;
			}
		}
		switch (choice) {
		case 49:
			MyState();
			choice = 0;
			break;
		case 50:
			DRG();
			choice = 0;
			break;
		case 51:
			return 0;
		}
	}
}

void MyState() {
	int trash;
	system("cls");
	printf("Current cash : %d\nWins : %d\nLoses : %d\n", Cash, Wins, Loses);
	printf("\nType any key to go to main menu...");
	trash = getche();											//�ƹ� �Է½� ������
}																//scanf ���� ���ڿ� ���� �Է½� ���̰� �־���

void drawDice(int _i, int _number)								//(�ֻ����� ��ġ,����)


{
	switch (_i)
	{
	case 1:
		printf("����������");
		break;
	case 2:
		switch (_number)
		{
		case 0:
			printf("��      ��");
			break;
		case 1:
		case 2:
			printf("��      ��");
			break;
		case 3:
			printf("��    �ܦ�");
			break;
		case 4:
		case 5:
		case 6:
			printf("����  �ܦ�");
			break;
		}
		break;
	case 3:
		switch (_number)
		{
		case 0:
			printf("��      ��");
			break;
		case 1:
		case 3:
		case 5:
			printf("��  ��  ��");
			break;
		case 2:
		case 6:
			printf("����  �ܦ�");
			break;
		case 4:
			printf("��      ��");
			break;
		}
		break;
	case 4:
		switch (_number)
		{
		case 0:
			printf("��      ��");
			break;
		case 1:
		case 2:
			printf("��      ��");
			break;
		case 3:
			printf("����    ��");
			break;
		case 4:
		case 5:
		case 6:
			printf("����  �ܦ�");
			break;
		}
		break;
	case 5:
		printf("����������");
		break;
	}
}

void DRG() {
	system("cls");
	int com[3];
	int betting;
	int i = 1;
	int *user;
	int whowins = 0;
	com[0] = rand() % 6 + 1;								//��ǻ�� ���� 6�� ����
	com[1] = rand() % 6 + 1;
	com[2] = rand() % 6 + 1;
	int total = com[0] + com[1] + com[2];
	printf("Current cash : %d\n\n", Cash);
	printf("Sum of computer's dice : %d\n", total);
	while (i) {												//���� ���� ����.
		printf("Input your betting :");
		scanf("%d", &betting);
		if (betting < Cash) {
			i = 0;
		}
		else {
			printf("Enter a money lower than your cash\n");
		}
	}
	while (1) {
		system("cls");
		printf("Computer's dice total is %d\n", total);		//while�� �ȿ��� ��� �׸�3���� user dice roll���� �ֻ��� �׸�.
		int j, nex;
		for (i = 1; i < 7; i++) {
			drawDice(i, 0);
			drawDice(i, 0);
			drawDice(i, 0);
			printf("\n");
		}
		int u1, u2, u3, utotal = 0;							//������ �������� ��ǻ�Ϳ� ��ġ�� ������ while
		int user[3];
		while (total != utotal) {
			u1 = rand() % 6 + 1;
			u2 = rand() % 6 + 1;
			u3 = rand() % 6 + 1;
			utotal = u1 + u2 + u3;
		}
		int i;
		for (i = 1; i < 7; i++) {							//user �ֻ��� �׸��� ����
			drawDice(i, u1);
			drawDice(i, u2);
			drawDice(i, u3);
			printf("\n");
		}
		user[0] = u1;
		user[1] = u2;
		user[2] = u3;										//user ���ڵ� ����

		printf("-1.Rolling dices again(Type any key)\n-2.Start game(Type esc key)\n-3.Surrender(Type 's' key)\n");
		nex = getche();
		if (nex == 27) {
			system("cls");
			printf("Stage 1\n");				//�̺κ� for ������ �����ϰԹٲٱ�->����
			for (i = 1; i < 7; i++) {
				drawDice(i, *user);				//�ֻ��� �׸��鼭 ���� ��� �����ִ� �κ�
				printf("\n");
			}
			for (i = 1; i < 7; i++) {
				drawDice(i, com[0]);
				printf("\n");
			}
			Sleep(1000);
			system("cls");
			printf("Stage 2\n");
			for (i = 1; i < 7; i++) {
				drawDice(i, *user);
				drawDice(i, *(user + 1));
				printf("\n");
			}
			for (i = 1; i < 7; i++) {
				drawDice(i, com[0]);
				drawDice(i, com[1]);
				printf("\n");
			}
			Sleep(1000);
			system("cls");
			printf("Stage 3\n");
			for (i = 1; i < 7; i++) {
				drawDice(i, *user);
				drawDice(i, *(user + 1));
				drawDice(i, *(user + 2));
				printf("\n");
			}
			for (i = 1; i < 7; i++) {
				drawDice(i, com[0]);
				drawDice(i, com[1]);
				drawDice(i, com[2]);
				printf("\n");
			}
			Sleep(1000);
			for (i = 0; i < 3; i++) {					//��� �Ǵ� �κ�, �迭�� �����ؼ� ����
				if (*(user + i) > com[i]) {
					whowins += 1;
				}
				else {
					whowins -= 1;
				}
			}
			if (whowins > 0) {
				printf("Final Winner User!!");
				Wins += 1;
				Cash = Cash + betting * 2;
			}
			else {
				printf("Final Winner Computer!!");
				Loses += 1;
				Cash = Cash - betting;
			}
			while (i) {
				printf("\n1. Retry\n2. Back to main menu\nEnter your choice:");	//�ٽ� ���࿩��, j�� ���� ����Ͽ����� �ٽ� �ʱ�ȭ�ؼ� ���
				j = getche();
				if (j == '1') {
					DRG();
				}
				else if (j == '2') {
					break;
				}
				else {
					system("cls");
					printf("\nEnter a number from the menu\n");
					i = 1;
				}
			}
			break;
		}
		else if (nex == 's') {
			Cash = Cash - 5000;					//������ ���� �� �� �ִٰ� ����
			DRG();
		}
	}
}
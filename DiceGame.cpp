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
	trash = getche();											//아무 입력시 지나감
}																//scanf 사용시 숫자와 문자 입력시 차이가 있었음

void drawDice(int _i, int _number)								//(주사위의 위치,숫자)


{
	switch (_i)
	{
	case 1:
		printf("┌───┐");
		break;
	case 2:
		switch (_number)
		{
		case 0:
			printf("│      │");
			break;
		case 1:
		case 2:
			printf("│      │");
			break;
		case 3:
			printf("│    ●│");
			break;
		case 4:
		case 5:
		case 6:
			printf("│●  ●│");
			break;
		}
		break;
	case 3:
		switch (_number)
		{
		case 0:
			printf("│      │");
			break;
		case 1:
		case 3:
		case 5:
			printf("│  ●  │");
			break;
		case 2:
		case 6:
			printf("│●  ●│");
			break;
		case 4:
			printf("│      │");
			break;
		}
		break;
	case 4:
		switch (_number)
		{
		case 0:
			printf("│      │");
			break;
		case 1:
		case 2:
			printf("│      │");
			break;
		case 3:
			printf("│●    │");
			break;
		case 4:
		case 5:
		case 6:
			printf("│●  ●│");
			break;
		}
		break;
	case 5:
		printf("└───┘");
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
	com[0] = rand() % 6 + 1;								//컴퓨터 숫자 6개 생성
	com[1] = rand() % 6 + 1;
	com[2] = rand() % 6 + 1;
	int total = com[0] + com[1] + com[2];
	printf("Current cash : %d\n\n", Cash);
	printf("Sum of computer's dice : %d\n", total);
	while (i) {												//많이 배팅 못함.
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
		printf("Computer's dice total is %d\n", total);		//while문 안에서 계속 네모3개랑 user dice roll에서 주사위 그림.
		int j, nex;
		for (i = 1; i < 7; i++) {
			drawDice(i, 0);
			drawDice(i, 0);
			drawDice(i, 0);
			printf("\n");
		}
		int u1, u2, u3, utotal = 0;							//유저의 숫자합이 컴퓨터와 일치할 때까지 while
		int user[3];
		while (total != utotal) {
			u1 = rand() % 6 + 1;
			u2 = rand() % 6 + 1;
			u3 = rand() % 6 + 1;
			utotal = u1 + u2 + u3;
		}
		int i;
		for (i = 1; i < 7; i++) {							//user 주사위 그리는 과정
			drawDice(i, u1);
			drawDice(i, u2);
			drawDice(i, u3);
			printf("\n");
		}
		user[0] = u1;
		user[1] = u2;
		user[2] = u3;										//user 숫자들 저장

		printf("-1.Rolling dices again(Type any key)\n-2.Start game(Type esc key)\n-3.Surrender(Type 's' key)\n");
		nex = getche();
		if (nex == 27) {
			system("cls");
			printf("Stage 1\n");				//이부분 for 문으로 간편하게바꾸기->포기
			for (i = 1; i < 7; i++) {
				drawDice(i, *user);				//주사위 그리면서 게임 양상 보여주는 부분
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
			for (i = 0; i < 3; i++) {					//우승 판단 부분, 배열로 저장해서 간편
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
				printf("\n1. Retry\n2. Back to main menu\nEnter your choice:");	//다시 시행여부, j는 위에 사용하였으나 다시 초기화해서 사용
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
			Cash = Cash - 5000;					//빚지고 도박 할 수 있다고 가정
			DRG();
		}
	}
}
#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>

#define LEFT 75		// Keyboard Input
#define RIGHT 77 
#define UP 72 
#define DOWN 80

#define LEFTa 97		// Keyboard Input2
#define RIGHTd 100 
#define UPw 119
#define DOWNs 115
#define LEFTA 65
#define RIGHTD 68
#define UPW 87
#define DOWNS 83

#define f 102
#define F 70
#define m 109
#define M 77

#define p 112
#define P 80 
#define ESC 27  

#define false 0
#define true 1

#define ACTIVE_BLOCK2 -3
#define ACTIVE_BLOCK -2 // Block State
#define CEILLING -1      
#define EMPTY 0         
#define WALL 1
#define INACTIVE_BLOCK 2 
#define INACTIVE_BLOCK2 3

#define MAIN_X 11	// Game borad Size
#define MAIN_Y 23 
#define MAIN_X_ADJ 3 
#define MAIN_Y_ADJ 1  

#define STATUS_X_ADJ MAIN_X_ADJ+MAIN_X+1 // Status info position

int STATUS_Y_GOAL; // Status info position

int STATUS_Y_SCORE;

int blocks[7][4][4][4] = {
	{ { 0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0 },{ 0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0 },
	{ 0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0 },{ 0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0 } },
	{ { 0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0 },{ 0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0 },
	{ 0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0 },{ 0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0 } },
	{ { 0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0 },{ 0,0,0,0,0,0,1,0,0,1,1,0,0,1,0,0 },
	{ 0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0 },{ 0,0,0,0,0,0,1,0,0,1,1,0,0,1,0,0 } },
	{ { 0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0 },{ 0,0,0,0,1,0,0,0,1,1,0,0,0,1,0,0 },
	{ 0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0 },{ 0,0,0,0,1,0,0,0,1,1,0,0,0,1,0,0 } },
	{ { 0,0,0,0,0,0,1,0,1,1,1,0,0,0,0,0 },{ 0,0,0,0,1,1,0,0,0,1,0,0,0,1,0,0 },
	{ 0,0,0,0,0,0,0,0,1,1,1,0,1,0,0,0 },{ 0,0,0,0,0,1,0,0,0,1,0,0,0,1,1,0 } },
	{ { 0,0,0,0,1,0,0,0,1,1,1,0,0,0,0,0 },{ 0,0,0,0,0,1,0,0,0,1,0,0,1,1,0,0 },
	{ 0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,0 },{ 0,0,0,0,0,1,1,0,0,1,0,0,0,1,0,0 } },
	{ { 0,0,0,0,0,1,0,0,1,1,1,0,0,0,0,0 },{ 0,0,0,0,0,1,0,0,0,1,1,0,0,1,0,0 },
	{ 0,0,0,0,0,0,0,0,1,1,1,0,0,1,0,0 },{ 0,0,0,0,0,1,0,0,1,1,0,0,0,1,0,0 } }
}; // Shape of block

int b_type; // block type
int b_rotation; // block rotation
int b_type_next; //new block

int main_org[MAIN_Y][MAIN_X];
int main_cpy[MAIN_Y][MAIN_X];

int bx, by; // x,y position of moving block

int key; // keyboard input 

int speed; // Game Speed 
int turn = 0;

int score; // Game Score
int score2;
int item = 0;
int item2 = 0;

int new_block_on = 0;
int crush_on = 0;
int itemused=0;
int itemcount = 0;
int itemcount2 = 0;


void title(void);
void reset(void);
void reset_main(void); // 
void reset_main_cpy(void);
void draw_map(void);
void draw_main(void);
void new_block(void);
void new_block2(void);
void check_key(void);
void check_key2(void);

int check_crush(int bx, int by, int rotation);
void drop_block(void);
void drop_block2(void);
void move_block(int dir);
void move_block2(int dir);
void check_line(void);
void check_line2(void);

void P1turn();
void P2turn();

void check_game_over(void);
void pause(void);

void gotoxy(int x, int y) {
	COORD pos = { 2 * x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE; // hide cursor
void setcursortype(CURSOR_TYPE c) { // hide cursor
	CONSOLE_CURSOR_INFO CurInfo;

	switch (c) {
	case NOCURSOR:
		CurInfo.dwSize = 1;
		CurInfo.bVisible = FALSE;
		break;
	case SOLIDCURSOR:
		CurInfo.dwSize = 100;
		CurInfo.bVisible = TRUE;
		break;
	case NORMALCURSOR:
		CurInfo.dwSize = 20;
		CurInfo.bVisible = TRUE;
		break;
	}
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}

int main() {
	FILE* fpp = fopen("result.txt","w");
	time_t curr;
	struct tm *d;
	curr = time(NULL);
	d = localtime(&curr);
	fprintf(fpp,"%d시%d분%d초\n", d->tm_hour, d->tm_min, d->tm_sec);
	fclose(fpp);
	int i;
	int x = 5;
	int y = 3;
	char choice;
	int block;
	srand((unsigned)time(NULL));
	setcursortype(NOCURSOR);
	title();
	reset();
	while (turn <= 60) {
		if (turn % 2 == 0) {
			gotoxy(STATUS_X_ADJ + 10, y + 2); printf("P1's turn");
			P1turn();
			turn++;
			if (itemused == 1) {
				gotoxy(STATUS_X_ADJ + 10, y + 4); printf("Choose a Block from 1 to 4");
				gotoxy(STATUS_X_ADJ + 10, y + 5); printf("1. □  2. ㅣ  3. ㄱㄴ   4. ㅗ" );
				Sleep(5000);
				rewind(stdin);
				choice = getch();
				block = choice - '0';
				if (block == 4) block = 7;
				itemused = 0;
				b_type_next = block-1;
				new_block();
				gotoxy(STATUS_X_ADJ + 10, y + 4); printf("                                 ");
				gotoxy(STATUS_X_ADJ + 10, y + 5); printf("                                 ");

			}

		}
		else {
			gotoxy(STATUS_X_ADJ+10, y + 2); printf("P2's turn");
			P2turn();
			turn++;
			if (itemused == 1) {
				gotoxy(STATUS_X_ADJ + 10, y + 4); printf("Choose a Block from 1 to 4");
				gotoxy(STATUS_X_ADJ + 10, y + 5); printf("1. □  2. ㅣ  3. ㄱㄴ   4. ㅗ");
				Sleep(5000);
				rewind(stdin);
				choice = getch();
				block = choice - '0';
				if (block == 4) block = 7;
				itemused = 0;
				b_type_next = block-1;
				new_block2();
				gotoxy(STATUS_X_ADJ + 10, y + 4); printf("                                ");
				gotoxy(STATUS_X_ADJ + 10, y + 5); printf("                                ");

			}
			
		}		
	}
	y = 5;
	gotoxy(x, y + 0); printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤");
	gotoxy(x, y + 1); printf("▤                              ▤");
	gotoxy(x, y + 2); printf("▤  +-----------------------+   ▤");
	gotoxy(x, y + 3); printf("▤  |  G A M E  O V E R..   |   ▤");
	gotoxy(x, y + 4); printf("▤  +-----------------------+   ▤");
	gotoxy(x, y + 5); printf("▤   P1   SCORE: %6d         ▤", score);
	gotoxy(x, y + 6); printf("▤                              ▤");
	gotoxy(x, y + 7); printf("▤   P2   SCORE: %6d         ▤", score2);
	gotoxy(x, y + 8); printf("▤  Press any key to restart..  ▤");
	gotoxy(x, y + 9); printf("▤                              ▤");
	gotoxy(x, y + 10); printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤");
	FILE * fp = fopen("result.txt", "a");
	fprintf(fp, "Game Results\n\t\tP1\tP2\nScore:\t\t%d\t%d\nItem obtained:\t%d\t%d\nItem used:\t%d\t%d\n\nWinner is %s", score, score2, item + itemcount, item2 + itemcount2, itemcount, itemcount2, score > score2 ? "P1!":"P2!");
	fclose(fp);
}

void P1turn() {
	int i;
	while (1) {
		for (i = 0; i < 5; i++) {
			check_key();
			draw_main();

			Sleep(speed);
			if (crush_on&&check_crush(bx, by + 1, b_rotation) == false) Sleep(100);

		}
		drop_block();

		check_game_over();
		if (new_block_on == 1) {
			new_block2();
			break;
		}
	}
}
void P2turn() {
	int i;
	while (1) {
		for (i = 0; i < 5; i++) {
			check_key2();
			draw_main();

			Sleep(speed);
			if (crush_on&&check_crush(bx, by + 1, b_rotation) == false) Sleep(100);

		}
		drop_block2();

		check_game_over();
		if (new_block_on == 1) {
			new_block();
			break;
		}
	}
}
void title(void) {
	int x = 5; //
	int y = 4; //


	gotoxy(x, y + 0); printf("┌─────────────┐");
	gotoxy(x, y + 1); printf("│                          │");
	gotoxy(x, y + 2); printf("│                          │");
	gotoxy(x, y + 3); printf("│                          │");
	gotoxy(x, y + 4); printf("└─────────────┘");

	gotoxy(x + 5, y + 2); printf("T E T R I S");
	gotoxy(x, y + 7); printf("Please Enter Any Key to Start..");
	gotoxy(x, y + 9); printf("  △   : Shift");
	gotoxy(x, y + 10); printf("◁  ▷ : Left / Right");
	gotoxy(x, y + 11); printf("  ▽   : Drop");
	gotoxy(x, y + 12); printf("   F   : Use Item");
	gotoxy(x, y + 13); printf("   P   : Pause");
	gotoxy(x, y + 14); printf("  ESC  : Quit");

	gotoxy(x + 15, y + 9); printf("  W   : Shift");
	gotoxy(x + 15, y + 10); printf(" A D  : Left / Right");
	gotoxy(x + 15, y + 11); printf("  S   : Drop");
	gotoxy(x + 15, y + 12); printf("  M   : Use Item");
	while (true) {
		if (kbhit()) break;
	}

	while (kbhit()) getch();

}

void reset(void) {

	score = 0;
	score2 = 0;
	key = 0;
	crush_on = 0;
	turn = 0;
	speed = 100;

	system("cls");
	reset_main();
	draw_map();
	draw_main();

	b_type_next = rand() % 7;
	new_block();

}

void reset_main(void) {
	int i, j;

	for (i = 0; i<MAIN_Y; i++) { // Game board initialize
		for (j = 0; j<MAIN_X; j++) {
			main_org[i][j] = 0;
			main_cpy[i][j] = 100;
		}
	}
	for (j = 1; j<MAIN_X; j++) {
		main_org[3][j] = CEILLING;
	}
	for (i = 1; i<MAIN_Y - 1; i++) {
		main_org[i][0] = WALL;
		main_org[i][MAIN_X - 1] = WALL;
	}
	for (j = 0; j<MAIN_X; j++) {
		main_org[MAIN_Y - 1][j] = WALL;
	}
}

void reset_main_cpy(void) {
	int i, j;

	for (i = 0; i<MAIN_Y; i++) {
		for (j = 0; j<MAIN_X; j++) {
			main_cpy[i][j] = 100;
		}
	}
}



void draw_map(void) { // Game Status 
	int y = 3;


	gotoxy(STATUS_X_ADJ, y + 2); printf("+-  N E X T  -+ ");
	gotoxy(STATUS_X_ADJ, y + 3); printf("|             | ");
	gotoxy(STATUS_X_ADJ, y + 4); printf("|             | ");
	gotoxy(STATUS_X_ADJ, y + 5); printf("|             | ");
	gotoxy(STATUS_X_ADJ, y + 6); printf("|             | ");
	gotoxy(STATUS_X_ADJ, y + 7); printf("+-- -  -  - --+ ");
	gotoxy(STATUS_X_ADJ, y + 8); printf("P1 score  :");
	gotoxy(STATUS_X_ADJ, STATUS_Y_SCORE = y + 9); printf("        %6d", score);
	gotoxy(STATUS_X_ADJ, STATUS_Y_SCORE + 1); printf("Item num:");
	gotoxy(STATUS_X_ADJ, STATUS_Y_SCORE + 2); printf("        %6d", item);
	gotoxy(STATUS_X_ADJ+10, y + 8); printf("P2 score  :");
	gotoxy(STATUS_X_ADJ+10, STATUS_Y_SCORE = y + 9); printf("        %6d", score2);
	gotoxy(STATUS_X_ADJ+10, STATUS_Y_SCORE + 1); printf("Item num:");
	gotoxy(STATUS_X_ADJ+10, STATUS_Y_SCORE + 2); printf("        %6d", item2);

	gotoxy(STATUS_X_ADJ, y + 17); printf("  △   : Shift        Use Item : F");
	gotoxy(STATUS_X_ADJ, y + 18); printf("◁  ▷ : Left / Right   P   : Pause");
	gotoxy(STATUS_X_ADJ, y + 19); printf("  ▽   : Soft Drop     ESC  : Quit");
	
	gotoxy(STATUS_X_ADJ, y + 13); printf("   W   : Shift        Use Item : M");
	gotoxy(STATUS_X_ADJ, y + 14); printf("  A D  : Left / Right ");
	gotoxy(STATUS_X_ADJ, y + 15); printf("   S   : Soft Drop ");

}

void draw_main(void) {
	int i, j;

	for (j = 1; j<MAIN_X - 1; j++) {
		if (main_org[3][j] == EMPTY) main_org[3][j] = CEILLING;
	}
	for (i = 0; i<MAIN_Y; i++) {
		for (j = 0; j<MAIN_X; j++) {
			if (main_cpy[i][j] != main_org[i][j]) {

				gotoxy(MAIN_X_ADJ + j, MAIN_Y_ADJ + i);
				switch (main_org[i][j]) {
				case EMPTY:
					printf("  ");
					break;
				case CEILLING:
					printf(". ");
					break;
				case WALL:
					printf("▩");
					break;
				case INACTIVE_BLOCK://inactive block 2를 만들기
					printf("□");
					break;
				case INACTIVE_BLOCK2:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
					printf("□");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					break;
				case ACTIVE_BLOCK:// same
					printf("■");
					break;
				case ACTIVE_BLOCK2:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
					printf("■");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					break;
				}
			}
		}
	}
	for (i = 0; i<MAIN_Y; i++) {
		for (j = 0; j<MAIN_X; j++) {
			main_cpy[i][j] = main_org[i][j];
		}
	}
}

void new_block(void) {
	int i, j;

	bx = (MAIN_X / 2) - 1;
	by = 0;
	b_type = b_type_next;
	b_type_next = rand() % 7;
	b_rotation = 0;

	new_block_on = 0;

	for (i = 0; i<4; i++) {
		for (j = 0; j<4; j++) {
			if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = ACTIVE_BLOCK;
		}
	}
	for (i = 1; i<3; i++) {
		for (j = 0; j<4; j++) {
			if (blocks[b_type_next][0][i][j] == 1) {
				gotoxy(STATUS_X_ADJ + 2 + j, i + 6);
				printf("■");
			}
			else {
				gotoxy(STATUS_X_ADJ + 2 + j, i + 6);
				printf("  ");
			}
		}
	}
}
void new_block2(void) {//2p
	int i, j;

	bx = (MAIN_X / 2) - 1;
	by = 0;
	b_type = b_type_next;
	b_type_next = rand() % 7;
	b_rotation = 0;

	new_block_on = 0;

	for (i = 0; i<4; i++) {
		for (j = 0; j<4; j++) {
			if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = ACTIVE_BLOCK2;
		}
	}
	for (i = 1; i<3; i++) {
		for (j = 0; j<4; j++) {
			if (blocks[b_type_next][0][i][j] == 1) {
				gotoxy(STATUS_X_ADJ + 2 + j, i + 6);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				printf("■");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			}
			else {
				gotoxy(STATUS_X_ADJ + 2 + j, i + 6);
				printf("  ");
			}
		}
	}
}
void check_key2(void) {//2p
	key = 0;

	if (kbhit()) {
		key = getch();
		if (key == 224) { // direction key
			do { key = getch(); } while (key == 224);
		}
		else { // Not direction eky
			switch (key) {

			case P:
			case p:
				pause();
				break;
			case f://자신이2p
			case F:
				if (item2 > 0) {
					itemused = 1;
					item2 -= 1;
					itemcount2 += 1;
				}
				break;
			case m://상대방이
			case M:
				if (item > 0) {
					itemused = 1;
					item -= 1;
					itemcount += 1;
				}
				break;
			case ESC:
				system("cls");
				exit(0);
			case LEFTA:
			case LEFTa:
				if (check_crush(bx - 1, by, b_rotation) == true) move_block2(LEFTa);
				break;
			case RIGHTD:
			case RIGHTd:
				if (check_crush(bx + 1, by, b_rotation) == true) move_block2(RIGHTd);
				break;
			case DOWNS:
			case DOWNs:
				if (check_crush(bx, by + 1, b_rotation) == true) move_block2(DOWNs);
				break;
			case UPW:
			case UPw:
				if (check_crush(bx, by, (b_rotation + 1) % 4) == true) move_block2(UPw);

				else if (crush_on == 1 && check_crush(bx, by - 1, (b_rotation + 1) % 4) == true) move_block2(1001);
			}
		}
	}
	while (kbhit()) getch();
}
void check_key(void) {
	key = 0;

	if (kbhit()) {
		key = getch();
		if (key == 224) { // direction key
			do { key = getch(); } while (key == 224);
			switch (key) {
			case LEFT:
				if (check_crush(bx - 1, by, b_rotation) == true) move_block(LEFT);
				break;
			case RIGHT:
				if (check_crush(bx + 1, by, b_rotation) == true) move_block(RIGHT);
				break;
			case DOWN:
				if (check_crush(bx, by + 1, b_rotation) == true) move_block(DOWN);
				break;
			case UP:
				if (check_crush(bx, by, (b_rotation + 1) % 4) == true) move_block(UP);

				else if (crush_on == 1 && check_crush(bx, by - 1, (b_rotation + 1) % 4) == true) move_block(100);
			}
		}
		else { // Not direction eky
			switch (key) {

			case P:
			case p:
				pause();
				break;
			case m:
			case M:
				if (item > 0) {
					itemused = 1;
					item -= 1;
					itemcount += 1;
				}
				break;
			case f:
			case F:
				if (item2 > 0) {
					itemused = 1;
					item2 -= 1;
					itemcount2 += 1;
				}
				break;
			case ESC:
				system("cls");
				exit(0);
			}
		}
	}
	while (kbhit()) getch();
}


int check_crush(int bx, int by, int b_rotation) {
	int i, j;

	for (i = 0; i<4; i++) {
		for (j = 0; j<4; j++) {
			if (blocks[b_type][b_rotation][i][j] == 1 && main_org[by + i][bx + j]>0) return false;
		}
	}
	return true;
};

void drop_block(void) {
	int i, j;

	if (crush_on&&check_crush(bx, by + 1, b_rotation) == true) crush_on = 0;
	if (crush_on&&check_crush(bx, by + 1, b_rotation) == false) {
		for (i = 0; i<MAIN_Y; i++) {
			for (j = 0; j<MAIN_X; j++) {
				if (main_org[i][j] == ACTIVE_BLOCK) main_org[i][j] = INACTIVE_BLOCK;
			}
		}
		crush_on = 0;
		check_line();
		new_block_on = 1;
		return;
	}
	if (check_crush(bx, by + 1, b_rotation) == true) move_block(DOWN);
	if (check_crush(bx, by + 1, b_rotation) == false) crush_on++;
}

void drop_block2(void) {//2p
	int i, j;

	if (crush_on&&check_crush(bx, by + 1, b_rotation) == true) crush_on = 0;
	if (crush_on&&check_crush(bx, by + 1, b_rotation) == false) {
		for (i = 0; i<MAIN_Y; i++) {
			for (j = 0; j<MAIN_X; j++) {
				if (main_org[i][j] == ACTIVE_BLOCK2) main_org[i][j] = INACTIVE_BLOCK2;
			}
		}
		crush_on = 0;
		check_line2();
		new_block_on = 1;
		return;
	}
	if (check_crush(bx, by + 1, b_rotation) == true) move_block2(DOWNs);
	if (check_crush(bx, by + 1, b_rotation) == false) crush_on++;
}

void move_block(int dir) {
	int i, j;

	switch (dir) {
	case LEFT:
		for (i = 0; i<4; i++) {
			for (j = 0; j<4; j++) {
				if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = EMPTY;
			}
		}
		for (i = 0; i<4; i++) {
			for (j = 0; j<4; j++) {
				if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j - 1] = ACTIVE_BLOCK;
			}
		}
		bx--;
		break;

	case RIGHT:
		for (i = 0; i<4; i++) {
			for (j = 0; j<4; j++) {
				if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = EMPTY;
			}
		}
		for (i = 0; i<4; i++) {
			for (j = 0; j<4; j++) {
				if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j + 1] = ACTIVE_BLOCK;
			}
		}
		bx++;
		break;

	case DOWN:
		for (i = 0; i<4; i++) {
			for (j = 0; j<4; j++) {
				if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = EMPTY;
			}
		}
		for (i = 0; i<4; i++) {
			for (j = 0; j<4; j++) {
				if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i + 1][bx + j] = ACTIVE_BLOCK;
			}
		}
		by++;
		break;

	case UP:
		for (i = 0; i<4; i++) {
			for (j = 0; j<4; j++) {
				if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = EMPTY;
			}
		}
		b_rotation = (b_rotation + 1) % 4;
		for (i = 0; i<4; i++) {
			for (j = 0; j<4; j++) {
				if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = ACTIVE_BLOCK;
			}
		}
		break;

	case 100:

		for (i = 0; i<4; i++) {
			for (j = 0; j<4; j++) {
				if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = EMPTY;
			}
		}
		b_rotation = (b_rotation + 1) % 4;
		for (i = 0; i<4; i++) {
			for (j = 0; j<4; j++) {
				if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i - 1][bx + j] = ACTIVE_BLOCK;
			}
		}
		by--;
		break;
	}
}

void move_block2(int dir) {//2p
	int i, j;

	switch (dir) {
	case LEFTA:
	case LEFTa:
		for (i = 0; i<4; i++) {
			for (j = 0; j<4; j++) {
				if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = EMPTY;
			}
		}
		for (i = 0; i<4; i++) {
			for (j = 0; j<4; j++) {
				if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j - 1] = ACTIVE_BLOCK2;
			}
		}
		bx--;
		break;
	case RIGHTD:
	case RIGHTd:
		for (i = 0; i<4; i++) {
			for (j = 0; j<4; j++) {
				if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = EMPTY;
			}
		}
		for (i = 0; i<4; i++) {
			for (j = 0; j<4; j++) {
				if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j + 1] = ACTIVE_BLOCK2;
			}
		}
		bx++;
		break;
	case DOWNS:
	case DOWNs:
		for (i = 0; i<4; i++) {
			for (j = 0; j<4; j++) {
				if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = EMPTY;
			}
		}
		for (i = 0; i<4; i++) {
			for (j = 0; j<4; j++) {
				if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i + 1][bx + j] = ACTIVE_BLOCK2;
			}
		}
		by++;
		break;
	case UPW:
	case UPw:
		for (i = 0; i<4; i++) {
			for (j = 0; j<4; j++) {
				if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = EMPTY;
			}
		}
		b_rotation = (b_rotation + 1) % 4;
		for (i = 0; i<4; i++) {
			for (j = 0; j<4; j++) {
				if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = ACTIVE_BLOCK2;
			}
		}
		break;

	case 1001:

		for (i = 0; i<4; i++) {
			for (j = 0; j<4; j++) {
				if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = EMPTY;
			}
		}
		b_rotation = (b_rotation + 1) % 4;
		for (i = 0; i<4; i++) {
			for (j = 0; j<4; j++) {
				if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i - 1][bx + j] = ACTIVE_BLOCK2;
			}
		}
		by--;
		break;
	}
}

void check_line(void) {
	int i, j, k, l;
	int count = 0;
	int block_amount; // block num of one line


	for (i = MAIN_Y - 2; i>3;) {
		block_amount = 0;
		for (j = 1; j<MAIN_X - 1; j++) {
			if (main_org[i][j]>0) block_amount++;
		}
		if (block_amount == MAIN_X - 2) {

			score += 1;
			count += 1;
			for (k = i; k>1; k--) {  // Block Down
				for (l = 1; l<MAIN_X - 1; l++) {
					if (main_org[k - 1][l] != CEILLING) main_org[k][l] = main_org[k - 1][l];
					if (main_org[k - 1][l] == CEILLING) main_org[k][l] = EMPTY;

				}
			}
		}
		else i--;
	}
	if (count >= 2) item++;
	gotoxy(STATUS_X_ADJ, STATUS_Y_SCORE+1); printf("Item num:");
	gotoxy(STATUS_X_ADJ, STATUS_Y_SCORE+2); printf("        %6d", item);
	gotoxy(STATUS_X_ADJ, STATUS_Y_SCORE); printf("        %6d", score);
}
void check_line2(void) {
	int i, j, k, l;
	int block_amount; // block num of one line
	int count=0;

	for (i = MAIN_Y - 2; i>3;) {
		
		block_amount = 0;
		for (j = 1; j<MAIN_X - 1; j++) {
			if (main_org[i][j]>0) block_amount++;
		}
		if (block_amount == MAIN_X - 2) {

			score2 += 1;
			count += 1;
			for (k = i; k>1; k--) {  // Block Down
				for (l = 1; l<MAIN_X - 1; l++) {
					if (main_org[k - 1][l] != CEILLING) main_org[k][l] = main_org[k - 1][l];
					if (main_org[k - 1][l] == CEILLING) main_org[k][l] = EMPTY;

				}
			}
		}
		else i--;
	}
	if (count >= 2) item2++;
	gotoxy(STATUS_X_ADJ+10, STATUS_Y_SCORE + 1); printf("Item num:");
	gotoxy(STATUS_X_ADJ+10, STATUS_Y_SCORE + 2); printf("        %6d", item2);
	gotoxy(STATUS_X_ADJ+10, STATUS_Y_SCORE); printf("        %6d", score2);
}


void check_game_over(void) {
	int i;

	int x = 5;
	int y = 5;

	for (i = 1; i<MAIN_X - 2; i++) {
		if (main_org[3][i]>0) {  // end condition 
			gotoxy(x, y + 0); printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤");
			gotoxy(x, y + 1); printf("▤                              ▤");
			gotoxy(x, y + 2); printf("▤  +-----------------------+   ▤");
			gotoxy(x, y + 3); printf("▤  |  G A M E  O V E R..   |   ▤");
			gotoxy(x, y + 4); printf("▤  +-----------------------+   ▤");
			gotoxy(x, y + 5); printf("▤   P1   SCORE: %6d         ▤", score);
			gotoxy(x, y + 6); printf("▤                              ▤");
			gotoxy(x, y + 7); printf("▤   P2   SCORE: %6d         ▤", score2);
			gotoxy(x, y + 8); printf("▤  Press any key to restart..  ▤");
			gotoxy(x, y + 9); printf("▤                              ▤");
			gotoxy(x, y + 10); printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤");
			FILE * fp = fopen("result.txt", "a");
			fprintf(fp, "Game Results\n\t\tP1\tP2\nScore:\t\t%d\t%d\nItem obtained:\t%d\t%d\nItem used:\t%d\t%d\n\nWinner is %s", score, score2, item + itemcount, item2 + itemcount2, itemcount, itemcount2, score > score2 ? "P1!" : "P2!");
			fclose(fp);

			Sleep(1000);
			while (kbhit()) getch();
			key = getch();
			reset();
		}
	}
}

void pause(void) {
	int i, j;

	int x = 5;
	int y = 5;

	for (i = 1; i<MAIN_X - 2; i++) {
		gotoxy(x, y + 0); printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤");
		gotoxy(x, y + 1); printf("▤                              ▤");
		gotoxy(x, y + 2); printf("▤  +-----------------------+   ▤");
		gotoxy(x, y + 3); printf("▤  |       P A U S E       |   ▤");
		gotoxy(x, y + 4); printf("▤  +-----------------------+   ▤");
		gotoxy(x, y + 5); printf("▤  Press any key to resume..   ▤");
		gotoxy(x, y + 6); printf("▤                              ▤");
		gotoxy(x, y + 7); printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤");
	}
	getch();

	system("cls");
	reset_main_cpy();
	draw_main();
	draw_map();

	for (i = 1; i<3; i++) {
		for (j = 0; j<4; j++) {
			if (blocks[b_type_next][0][i][j] == 1) {
				gotoxy(MAIN_X + MAIN_X_ADJ + 3 + j, i + 6);
				printf("■");
			}
			else {
				gotoxy(MAIN_X + MAIN_X_ADJ + 3 + j, i + 6);
				printf("  ");
			}
		}
	}
}
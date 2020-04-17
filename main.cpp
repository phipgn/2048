#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>

#define MARGIN_TOP 1
#define MARGIN_LEFT 2
#define SIZE 6

using namespace std;

//Ham di chuyen con tro den vi tri nao do trong Console
void gotoxy(short x, short y) {
    HANDLE hConsoleOutput;
    COORD Cursor_an_Pos = {x, y};
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}

//Ham thay doi textcolor va backgroundcolor
void setColor(short x) { 
	HANDLE hConsoleColor;
	hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleColor, x);
}

short countNumbers(int x) {
	short count = 0;
	do {
		count++;
		x = x / 10;
	} while (x > 0);
	return count;
}

void drawTable(int map[4][4], short &currentCol, short &currentRow) {
		
	currentCol = MARGIN_LEFT;
	currentRow = MARGIN_TOP;
		
	gotoxy(currentCol, currentRow);
	cout << char(218);
	for (short i = 1; i < 32; i++) {
		if ( i % 8 == 0) {
			cout << char(194);
		} else {
			cout << char(196);
		}
		
	}
	cout << char(191);
	currentRow++;
	
	for (short i = 1; i < 16; i++) {
		currentCol = MARGIN_LEFT;
		if (i == 4 || i == 8 || i == 12) {
			currentCol = MARGIN_LEFT;
			gotoxy(currentCol, currentRow);
			cout << char(195);
			for (short j = 1; j < 32; j++) {
				if (j % 8 == 0) {
					cout << char(197); // dau chu thap '+'
				} else {
					cout << char(196); // dau gach ngang '-'
				}
			}
			cout << char(180);
		} else if (i == 2 || i == 6 || i == 10 || i == 14) {
			currentCol = MARGIN_LEFT;
			gotoxy(currentCol, currentRow);
			cout << char(179);
			for (short j = 1; j < 32; j++) {
				if (j == 8 || j == 16 || j == 24) {
					currentCol++;
					gotoxy(currentCol, currentRow);
					cout << char(179); // dau gach dung '|'					
				} else if (j == 4 || j == 12 || j == 20 || j == 28) {
					// draw numbers
					currentCol++;
					gotoxy(currentCol, currentRow);
					
					short x, y;
					if (i == 2)	 y = 0;
					if (i == 6)  y = 1;
					if (i == 10)  y = 2;
					if (i == 14)  y = 3;
					if (j == 4) x = 0;
					if (j == 12) x = 1;
					if (j == 20) x = 2;
					if (j == 28) x = 3;
					
					int number = map[x][y];
					if (number != 0) {
					
					if (number == 2) setColor(128);
					if (number == 4) setColor(30);
					if (number == 8) setColor(46);
					if (number == 16) setColor(62);
					if (number == 32) setColor(78);
					if (number == 64) setColor(94);
					if (number == 128) setColor(110);
					if (number == 256) setColor(126);
					if (number == 512) setColor(142);
					if (number == 1024) setColor(158);
					if (number == 2048) setColor(174);
					if (number == 4096) setColor(190);
					if (number == 8192) setColor(206);
					if (number == 16384) setColor(222);
					if (number == 32768) setColor(222);
						
						switch(countNumbers(number)) {
							case 1:
								currentCol-=4;
								cout << " " << map[x][y] << " ";
								currentCol+=4;
								break;
							case 2:
								currentCol--;
								gotoxy(currentCol, currentRow);
								cout << " " << map[x][y] << " ";
								currentCol++;
								break;
							case 3:
								currentCol-=2;
								gotoxy(currentCol, currentRow);
								cout << " " << map[x][y] << " ";
								currentCol+=2;
								break;
							case 4:
								currentCol-=5;
								gotoxy(currentCol, currentRow);
								cout << " " << map[x][y] << " ";
								currentCol+=5;
								break;
							default:
								currentCol-=3;
								gotoxy(currentCol, currentRow);
								cout << " " << map[x][y] << " ";
								currentCol+=3;
						}
						setColor(15);
					}
				} else {
					currentCol++;
					gotoxy(currentCol, currentRow);
				}
			}
			currentCol++;
			gotoxy(currentCol, currentRow);
			cout << char(179);
		} else if (i == 1 || i == 3 || i ==5 || i == 7 || i == 9 || i == 11 || i == 13 || i == 15) {
			for (short j = 0; j <= 32; j++) {
				if (j == 0 || j == 8 || j == 16 || j == 24 || j == 32) {
					gotoxy(currentCol, currentRow);
					cout << char(179);					
					currentCol++;
				} else {
					currentCol++;
					gotoxy(currentCol, currentRow);
				}
			}
		}		
		currentRow++;
	}
	
	currentCol = MARGIN_LEFT;
	gotoxy(currentCol, currentRow);
	cout << char(192);
	for (short i = 1; i < 32; i++) {
		if ( i % 8 == 0) {
			cout << char(193);
		} else {
			cout << char(196);
		}
	}
	cout << char(217);
	currentRow++;
}

void goUp(int map[4][4]) {
	
	// fill spaces
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			if (!map[x][y]) {
				for (int z = y + 1; z < 4; z++) {
					if (map[x][z]) {
						map[x][y] = map[x][z];
						map[x][z] = 0;
						break;
					}
				}
			}
		}
	}
	
	// update values
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 3; y++) {
			if (map[x][y] == map[x][y+1]) {
				map[x][y] *= 2;
				map[x][y+1] = 0;
			}
		}
	}
	
	// fill spaces
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			if (!map[x][y]) {
				for (int z = y + 1; z < 4; z++) {
					if (map[x][z]) {
						map[x][y] = map[x][z];
						map[x][z] = 0;
						break;
					}
				}
			}
		}
	}
	
}

void goDown(int map[4][4]) {
	// fill spaces
	for (int x = 0; x < 4; x++) {
		for (int y = 3; y > 0; y--) {
			if (!map[x][y]) {
				for (int z = y - 1; z >= 0; z--) {
					if (map[x][z]) {
						map[x][y] = map[x][z];
						map[x][z] = 0;
						break;
					}
				}
			}
		}
	}
	
	// update values
	for (int x = 3; x >= 0; x--) {
		for (int y = 3; y > 0; y--) {
			if (map[x][y] == map[x][y-1]) {
				map[x][y] *= 2;
				map[x][y-1] = 0;
			}
		}
	}
	
	// fill spaces
	for (int x = 0; x < 4; x++) {
		for (int y = 3; y > 0; y--) {
			if (!map[x][y]) {
				for (int z = y - 1; z >= 0; z--) {
					if (map[x][z]) {
						map[x][y] = map[x][z];
						map[x][z] = 0;
						break;
					}
				}
			}
		}
	}
}

void goLeft(int map[4][4]) {
	// fill spaces
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			if (!map[y][x]) {
				for (int z = y + 1; z < 4; z++) {
					if (map[z][x]) {
						map[y][x] = map[z][x];
						map[z][x] = 0;
						break;
					}
				}
			}
		}
	}
	
	// update values
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 3; y++) {
			if (map[y][x] == map[y+1][x]) {
				map[y][x] *= 2;
				map[y+1][x] = 0;
			}
		}
	}
	
	// fill spaces
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			if (!map[y][x]) {
				for (int z = y + 1; z < 4; z++) {
					if (map[z][x]) {
						map[y][x] = map[z][x];
						map[z][x] = 0;
						break;
					}
				}
			}
		}
	}
}

void goRight(int map[4][4]) {
	// fill spaces
	for (int x = 0; x < 4; x++) {
		for (int y = 3; y >= 0; y--) {
			if (!map[y][x]) {
				for (int z = y - 1; z >= 0; z--) {
					if (map[z][x]) {
						map[y][x] = map[z][x];
						map[z][x] = 0;
						break;
					}
				}
			}
		}
	}
	
	for (int x = 0; x < 4; x++) {
		for (int y = 3; y >= 0; y--) {
			if (map[y][x] == map[y - 1][x]) {
				map[y-1][x] *= 2;
				map[y][x] = 0;
			}
		}
	}
			
	// fill spaces
	for (int x = 0; x < 4; x++) {
		for (int y = 3; y >= 0; y--) {
			if (!map[y][x]) {
				for (int z = y - 1; z >= 0; z--) {
					if (map[z][x]) {
						map[y][x] = map[z][x];
						map[z][x] = 0;
						break;
					}
				}
			}
		}
	}
}

void randomNumber(int map[4][4]) {
	int pos1,pos2;
	srand(time(0));
	do {
		pos1 = rand() % 4;
		pos2 = rand() % 4;
	} while (map[pos1][pos2] != 0);
	
	do { 
		map[pos1][pos2] = 2 + rand() % 3;
	} while (map[pos1][pos2] == 3);
}

bool gameChanged(int a[4][4], int b[4][4]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (a[i][j] != b[i][j]) {
				return true;
			}
		}
	}
	return false;
}

int main(int argc, char** argv) {
	
	int map[4][4];
	int a[4][4];
	
	for (short i = 0; i < 4; i++) {
		for (short j = 0; j < 4; j++) {
			map[i][j] = 0;
		}
	}
	
	map[0][0] = 2;
	map[1][0] = 2;
	map[2][0] = 2;
	map[3][0] = 2;
	
	short currentCol = MARGIN_LEFT;
	short currentRow = MARGIN_TOP;	
	
	system("cls");
	drawTable(map, currentCol, currentRow);
	
	while (true) {
		
		memcpy(a, map, sizeof(map));
		int key = getch();
		system("cls");
		
		if (key == 224) {
			int k = getch();
			// UP
			if (k == 72) {
				goUp(map);
				gotoxy(MARGIN_LEFT, currentRow);
				cout << "UP";
			}
			// LEFT
			if (k == 75) {
				goLeft(map);
				gotoxy(MARGIN_LEFT, currentRow);
				cout << "LEFT";
			}
			// RIGHT
			if (k == 77) {
				goRight(map);
				gotoxy(MARGIN_LEFT, currentRow);
				cout << "RIGHT";
			}
			// DOWN
			if (k == 80) {
				goDown(map);
				gotoxy(MARGIN_LEFT, currentRow);
				cout << "DOWN";
			}
			
			if (gameChanged(map, a)) {
				randomNumber(map);
			}
			drawTable(map, currentCol, currentRow);
		} else {
			exit(EXIT_SUCCESS);
		}		
	};
	
	return 0;
}

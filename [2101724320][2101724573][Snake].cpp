#include <stdio.h>
#include <time.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <stdlib.h>
#include <time.h>
#include <conio.h>

FILE *fp;

struct data {
	char name[20];
	int level;
	int score;
};

struct single {
	char nama[20];
	int score;
};

void readFileSaveGame(int *totalSave, struct data save[]) {
	*totalSave = 0;
	fp = fopen("Saves.txt", "r");
	if (fp != NULL) {
		while (!feof(fp)) {
			fscanf(fp, "%[^-]-%d-%d\n", save[*totalSave].name, &save[*totalSave].level, &save[*totalSave].score);
			*totalSave += 1;
		}
	}
	fclose(fp);
}

void readFileScoresNormal(int *totalnormalHs, struct data normalHs[]) {
	*totalnormalHs = 0;
	fp = fopen("Scores - Normal Mode.txt", "r");
	if (fp != NULL) {
		while (!feof(fp)) {
			fscanf(fp, "%[^-]-%d-%d\n", normalHs[*totalnormalHs].name, &normalHs[*totalnormalHs].level, &normalHs[*totalnormalHs].score);
			*totalnormalHs += 1;
		}
	}
	fclose(fp);
}
/*
void readFileScoresSingle(int totalsingleHs[],struct data singleHs[]) {
for (int i = 0; i < 10; i++) {
totalsingleHs[i] = 0;
}
fp = fopen("Arcade Scores.txt", "r");
if (fp != NULL) {
int i = 0;
while (!feof(fp)) {
fscanf(fp, "%[^-]-%d-%d\n", singleHs[totalsingleHs[i]].name, singleHs[totalsingleHs].level, singleHs[totalsingleHs].score);
i++;
(totalsingleHs[i])
}
}
}
*/

void writeFileScoresNormal(int totalnormalHs, struct data normalHs[]) {
	fp = fopen("Scores - Normal Mode.txt", "w");
	for (int i = 0; i < totalnormalHs; i++) {
		fprintf(fp, "%s-%d-%d\n", normalHs[i].name, normalHs[i].level, normalHs[i].score);
	}
	fclose(fp);
}

void writeFileSaveGame(int totalSave, struct data save[4]) {
	fp = fopen("Saves.txt", "w");
	for (int i = 0; i < totalSave; i++) {
		fprintf(fp, "%s-%d-%d\n", save[i].name, save[i].level, save[i].score);
	}
	fclose(fp);
}

void saveGame(int totalSave, struct data save[4]) {

}

const int mapwidth = 40;
const int maplength = 40;

struct map {
	int idx[maplength][mapwidth];
}content;

struct position {
	int posX;
	int posY;
}frog, pellet, mouse, snake[1599];

//function initialize map template
void initTemplateMap() {
	int i, j;
	for (i = 0; i < 40; i++) {
		for (j = 0; j < 40; j++) {
			if (i == 0 | i == 39 | j == 0 | j == 39) {
				content.idx[j][i] = -3;
			}
			else {
				content.idx[j][i] = -1;
			}
		}
	}
}

void initLevel1() {
	int i, j;
	for (i = 0; i < 40; i++) {
		for (j = 0; j < 40; j++) {
			if (i == 0 | i == 39 | j == 0 | j == 39) {
				content.idx[j][i] = -3;
			}
			else {
				content.idx[j][i] = -1;
			}
		}
	}
}

void initLevel2() {
	int i, j;
	for (i = 0; i < 40; i++) {
		for (j = 0; j < 40; j++) {
			if (i == 20 || j == 20) {
				if (j != 1 && j != 38 && i != 1 && i != 38) {
					content.idx[j][i] = -2;
				}
			}
		}
	}
}

void initLevel3() {
	int i, j;
	for (i = 0; i < 40; i++) {
		for (j = 0; j < 40; j++) {
			if (i == 10 || i == 30) {
				if (j < 10 && j > 30){
					content.idx[j][i] = -2;
				}
			}
		}
	}
}

void initLevel4() {
	int i, j;
	for (i = 0; i < 40; i++) {
		for (j = 0; j < 40; j++) {
			if (i == 20 || j == 20) {
				content.idx[j][i] = -2;
			}
		}
	}
}

void initLevel5() {
	int i, j;
	for (i = 0; i < 40; i++) {
		for (j = 0; j < 40; j++) {
			if (i == 20 || j == 20) {
				content.idx[j][i] = -2;
			}
		}
	}
}

void initLevel6() {
	int i, j;
	for (i = 0; i < 40; i++) {
		for (j = 0; j < 40; j++) {
			if (i == 20 || j == 20) {
				content.idx[j][i] = -2;
			}
		}
	}
}

void initLevel7() {
	int i, j;
	for (i = 0; i < 40; i++) {
		for (j = 0; j < 40; j++) {
			if (i == 20 || j == 20) {
				content.idx[j][i] = -2;
			}
		}
	}
}

void initLevel8() {
	int i, j;
	for (i = 0; i < 40; i++) {
		for (j = 0; j < 40; j++) {
			if (i == 20 || j == 20) {
				content.idx[j][i] = -2;
			}
		}
	}
}

void initLevel9() {
	int i, j;
	for (i = 0; i < 40; i++) {
		for (j = 0; j < 40; j++) {
			if (i == 20 || j == 20) {
				content.idx[j][i] = -2;
			}
		}
	}
}

void initLevel10() {
	int i, j;
	for (i = 0; i < 40; i++) {
		for (j = 0; j < 40; j++) {
			if (i == 20 || j == 20) {
				content.idx[j][i] = -2;
			}
		}
	}
}

int snakeLength;
int eat1, eat2;
int headX;
int headY;
int direction;
int point;
int timeSleep;

void printMap(int goalLength,int goalScore) {
	for (int i = 0; i < maplength; i++) {
		for (int j = 0; j < mapwidth; j++) {
			if (i == 0 && j == 0) {
				printf("%c", 201);
			}
			else if (i == 0 && j == 39) {
				printf("%c", 187);
			}
			else if (i == 39 && j == 0) {
				printf("%c", 200);
			}
			else if (i == 39 && j == 39) {
				printf("%c", 188);
			}
			else if (i == 0 || i == 39) {
				printf("%c%c", 205, 205);
			}
			else if (j == 0 || j == 39) {
				printf("%c", 186);
			}
			else if (content.idx[i][j] == 0) {
				printf("%c ", 157); //kepala ular - 0
			}
			else if (content.idx[i][j] == 1) {
				printf("%c ", 245);//badan ular - 1
			}
			else if (content.idx[i][j] == 4) {
				printf("%c ", 232); //kodok - 4
			}
			else if (content.idx[i][j] == 3) {
				printf("%c ", 248); //tikus - 3
			}
			else if (content.idx[i][j] == 2) {
				printf("O "); //pellet - 2
			}
			else if (content.idx[i][j] == -2) {
				printf("%c ", 61); //tembok lapangan - -2 & tembok pinggir -3
			}
			else if (content.idx[i][j] == -1) {
				printf(". "); //lapangan - -1
			}
		}
		printf("\n");
	}
	printf("\nScore Goal = %d \t\tCurrent Score: %d", goalScore, point);
	printf("\nLength Goal = %d \t\tCurrent Length: %d", goalLength, snakeLength);
}

void generatePellet() {
	int pelletX;
	int pelletY;
	do {
		pelletX = rand() % (mapwidth - 1) + 1;
		pelletY = rand() % (maplength - 1) + 1;
	} while (content.idx[pelletY][pelletX] != -1);
	content.idx[pelletY][pelletX] = 2;
	pellet.posY = pelletY;
	pellet.posX = pelletX;
}
//function to randomize frog position
void generateFrog() {
	int frogX;
	int frogY;
	do {
		frogX = rand() % (mapwidth - 1) + 1;
		frogY = rand() % (maplength - 1) + 1;
	} while (content.idx[frogY][frogX] != -1);
	content.idx[frogY][frogX] = 4;
	frog.posY = frogY;
	frog.posX = frogX;
}
//function to randomize mouse position
void generateMouse() {
	int mouseX;
	int mouseY;
	do {
		mouseX = rand() % (mapwidth - 1) + 1;
		mouseY = rand() % (maplength - 1) + 1;
	} while (content.idx[mouseY][mouseX] != -1);
	content.idx[mouseY][mouseX] = 3;
	mouse.posY = mouseY;
	mouse.posX = mouseX;
}

void eat_() {
	if (eat1 > 0) {
		point += 3;
		if (timeSleep > 200) {
			timeSleep -= 25;
		}
		else if (timeSleep > 100) {
			timeSleep -= 12.5;
		}
		else if (timeSleep > 50) {
			timeSleep -= 6.25;
		}
		else if (timeSleep > 10) {
			timeSleep -= 3.125;
		}
		snakeLength++;
		generateMouse();
		eat1 = 0;
	}
	else if (eat2 > 0) {
		point += 5;
		if (timeSleep > 200) {
			timeSleep -= 50;
		}
		else if (timeSleep > 100) {
			timeSleep -= 25;
		}
		else if (timeSleep > 50) {
			timeSleep -= 12.5;
		}
		else if (timeSleep > 10) {
			timeSleep -= 6.25;
		}
		snakeLength++;
		generateFrog();
		eat2 = 0;
	}
}

bool isOnSnakeBody(int x, int y) {
	for (int i = 0; i < snakeLength - 1; i++) {
		if (snake[i].posX == x && snake[i].posY == y) {
			return true;
		}
	}
	return false;
}
//moving snake to next position
void moveSnake(int changex, int changey, int ****live) {
	int newx = headX + changex;
	int newy = headY + changey;
	int flag = 0;
	struct position temp;
	if (content.idx[newy][newx] == 2) {
		point += 1;
		snakeLength++;
		generatePellet();
		flag += 1;
	}
	else if (content.idx[newy][newx] == 3) {
		eat1 += 1;
		flag += 1;
	}
	else if (content.idx[newy][newx] == 4) {
		eat2 += 1;
		flag += 1;
	}
	else if (content.idx[newy][newx] == -3 || content.idx[newy][newx] == -2) {
		(****live) = 0;
		return;
	}
	else if (isOnSnakeBody(newx, newy) == true) {
		(****live) = 0;
		return;
	}
	headX = newx;
	headY = newy;
	//emptying the content of the last part of the snake
	content.idx[snake[0].posY][snake[0].posX] = -1;
	for (int i = 0; i < snakeLength; i++) {
		snake[i] = snake[i + 1];
		content.idx[snake[i].posY][snake[i].posX] = 1;
	}
	//assigning head to snakeLength - 1 array
	snake[snakeLength - 1].posY = headY;
	snake[snakeLength - 1].posX = headX;
	//choosing whether need to replace headX & headY position or not
	if (flag == 0) {
		content.idx[headY][headX] = 0;
	}
	else if (flag == 1 && eat1 > 0 || eat2 > 0) {
		if (eat1 > 0 || eat2 > 0) {
			eat_();
		}
		else {
			if (timeSleep > 200) {
				timeSleep -= 10;
			}
			else if (timeSleep > 100) {
				timeSleep -= 5;
			}
			else if (timeSleep > 50) {
				timeSleep -= 2.5;
			}
			else if (timeSleep > 10) {
				timeSleep -= 1.25;
			}
		}
		flag -= 1;
	}
}

void moveFrog() {
	int x, y;
	int direction;
	int jump;
	do {
		direction = rand() % 4 + 1;
		jump = rand() % 2 + 2;
		x = frog.posX;
		y = frog.posY;
		content.idx[y][x] = -1;
		if (direction == 1) {
			y += jump; //up
		}
		else if (direction == 2) {
			y -= jump; //down
		}
		else if (direction == 3) {
			x -= jump; //left
		}
		else if (direction == 4) {
			x += jump; //right
		}
	} while (isOnSnakeBody(x, y) == true || content.idx[y][x] == 2 || content.idx[y][x] == 3 || content.idx[y][x] == -2 || content.idx[y][x] == 6 || x > 38 || x < 1 || y < 1 || y > 38);
	if (content.idx[y][x] == 0) {
		eat2 += 1;
		eat_();
	}
	else {
		frog.posX = x;
		frog.posY = y;
		content.idx[y][x] = 4;
	}
}

void moveMouse() {
	int x, y;
	int jump;
	int direction;
	do {
		direction = rand() % 4 + 1;
		jump = rand() % 2 + 1;
		x = mouse.posX;
		y = mouse.posY;
		content.idx[y][x] = -1;
		if (direction == 1) {
			y += jump; //up
		}
		else if (direction == 2) {
			y -= jump; //down
		}
		else if (direction == 3) {
			x -= jump; //left
		}
		else if (direction == 4) {
			x += jump; //right
		}
	} while (isOnSnakeBody(x, y) == true || content.idx[y][x] == 2 || content.idx[y][x] == 3 || content.idx[y][x] == -2 || x > 38 || x < 1 || y < 1 || y > 38);
	if (content.idx == 0) {
		eat1 += 1;
		eat_();
	}
	else {
		mouse.posX = x;
		mouse.posY = y;
		content.idx[y][x] = 3;
	}
}

void updatePositionSnake(int ***live) {
	switch (direction) {
	case 1: moveSnake(0, -1, &live); break;
	case 2: moveSnake(0, 1, &live); break;
	case 3: moveSnake(-1, 0, &live); break;
	case 4: moveSnake(1, 0, &live); break;
	}

}

void scanInputSnake(char inp) {
	switch (inp) {
	case 'W':
	case 'w': direction = 1; break;
	case 'S':
	case 's': direction = 2; break;
	case 'A':
	case 'a': direction = 3; break;
	case 'D':
	case 'd': direction = 4; break;
	}
}

//Main Function
void run(int **live, int level,int **totalScoreTemp) {
	int goal = 0;
	int goalLength = 20 + 2 * level;
	int goalScore = 150 + level * 25;
	snakeLength = 3;
	headX = 1;
	headY = 1;
	point = 0;
	timeSleep = 750;
	system("color 30");
	initTemplateMap();
	switch (level) {
	case 1: initLevel1(); break;
	case 2: initLevel2(); break;
	case 3: initLevel3(); break;
	case 4: initLevel4(); break;
	case 5: initLevel5(); break;
	case 6: initLevel6(); break;
	case 7: initLevel7(); break;
	case 8: initLevel8(); break;
	case 9: initLevel9(); break;
	case 10: initLevel10(); break;
	}
	generatePellet();
	generateFrog();
	generateMouse();
	while ((**live) == 1 && goal == 0) {
		system("cls");
		moveFrog();
		moveMouse();
		if (kbhit()) {
			scanInputSnake(getch());
		}
		updatePositionSnake(&live);
		printMap(goalLength, goalScore);
		Sleep(timeSleep);
		if (timeSleep > 200) {
			timeSleep -= 3;
		}
		else if (timeSleep > 100) {
			timeSleep -= 1.5;
		}
		else if (timeSleep > 50) {
			timeSleep -= 0.75;
		}
		if (snakeLength >= goalLength || point >= goalScore) {
			goal += 1;
		}
	}
	if ((**live) == 1 && goal == 1) {
		printf("\nCONGRATULATION!!!");
		printf("\nYour Score is: %d", point);
		printf("\nDo you want to save your progress?");
	}
	else {
		printf("\n[GAME OVER]");
		printf("\nYour Score is %d", point);
	}
	printf("\n\n");
	system("pause");
	(**totalScoreTemp) += point;
}


void counter(int level) {
	printf("Level %d", level);
	printf("\nGet Ready");
	Sleep(500);
	printf("\n     1    ");
	Sleep(500);
	printf("\n     2    ");
	Sleep(500);
	printf("\n     3    ");
	for (int i = 0; i < 10; i++) {
		system("cls");
		system("color bc");
		printf("\n\n                                           ``````````                                    ");
		printf("\n                                     `````..--------..`````                                ");
		printf("\n                                  ```.-://:-...`....-://:-.```                            ");
		printf("\n                               `.`.:/:.`                `.:/:.`.`                         ");
		printf("\n                              `.`-/:.                        .//.`.`                      ");
		printf("\n                             .`./:`                            `:/.`.                     ");
		printf("\n                            .`:/`                                .+:`.                    ");
		printf("\n                           .`//                                   `// .                   ");
		printf("\n                          . //                                     `/: .                  ");
		printf("\n                         .`-+`                                      `+.`.                 ");
		printf("\n                         . +:                                        :/ .                 ");
		printf("\n                         .`+.        :---`-::- `/.  /--:`-::-`       -+`.                 ");
		printf("\n                        `..+`       `/-..  :-  :-/  +``/` .:         .+`.`                ");
		printf("\n                         .`+.       `. .+` :- `+-/:`+./-  .:         -+`.                 ");
		printf("\n                         . /:        ----  -. -.  :`:  -` .-         // .                 ");
		printf("\n                         .`-+`                                      .+.`.                 ");
		printf("\n                          . //                                     `/: .                  ");
		printf("\n                           .`//`                                  `/: .                   ");
		printf("\n                            .`:+.                                .+- .                    ");
		printf("\n                             .`./:`                            .//``.                     ");
		printf("\n                              `.`.//.                        .//.`.`                      ");
		printf("\n                                `.``:/:-`                `-//-``.`                        ");
		printf("\n                                   ````-://:--......--://:.````                           ");
		printf("\n                                      ``````...----...``````                              ");
		printf("\n                                           ````````````							    	");
		Sleep(50);
	}
}

void level1_(int *live,int *totalScoreTemp) {
	system("cls");
	counter(1);
	run(&live, 1, &totalScoreTemp);
}

void level2_(int *live,int *totalScoreTemp) {
	system("cls");
	counter(2);
	run(&live, 2, &totalScoreTemp);
}

void level3_(int *live, int *totalScoreTemp) {
	system("cls");
	counter(3);
	run(&live, 3, &totalScoreTemp);
}

void level4_(int *live, int *totalScoreTemp) {
	system("cls");
	counter(4);
	run(&live, 4, &totalScoreTemp);
}

void level5_(int *live, int *totalScoreTemp) {
	system("cls");
	counter(5);
	run(&live, 5, &totalScoreTemp);
}

void level6_(int *live, int *totalScoreTemp) {
	system("cls");
	counter(6);
	run(&live, 6, &totalScoreTemp);
}

void level7_(int *live, int *totalScoreTemp) {
	system("cls");
	counter(7);
	run(&live, 7, &totalScoreTemp);
}

void level8_(int *live, int *totalScoreTemp) {
	system("cls");
	counter(8);
	run(&live, 8, &totalScoreTemp);
}

void level9_(int *live, int *totalScoreTemp) {
	system("cls");
	counter(9);
	run(&live, 9, &totalScoreTemp);
}

void level10_(int *live, int *totalScoreTemp) {
	system("cls");
	counter(10);
	run(&live, 10, &totalScoreTemp);
}

void swapStruct(struct data *temp1, struct data *temp2) {
	struct data temp;
	temp = *temp1;
	(*temp1) = (*temp2);
	(*temp2) = temp;
}

void updateHsNormal(struct data normalHs[],int ****totalNormalHs,struct data temp) {
	int tempCont;
	normalHs[****totalNormalHs] = temp;
	(*totalNormalHs) += 1;
	for (int i = 0; i < ****totalNormalHs; i++) {
		tempCont = i;
		for (int j = 0; j < ****totalNormalHs; j++) {
			if (normalHs[tempCont].score < normalHs[j].score) {
				tempCont = j;
			}
		}
		swapStruct(&normalHs[i], &normalHs[tempCont]);
	}
}

void startGame(int ****totalSave, int **type, struct data save[4], struct data temp) {
	int live = 1;
	int finish = 0;
	int totalScoreTemp = 0;
	if (**type == 1) {
		if (live == 1) {
			level1_(&live, &totalScoreTemp);
		}
		if (live == 1) {
			level2_(&live, &totalScoreTemp);
		}
		if (live == 1) {
			level3_(&live, &totalScoreTemp);
		}
		if (live == 1) {
			level4_(&live, &totalScoreTemp);
		}
		if (live == 1) {
			level5_(&live, &totalScoreTemp);
		}
		if (live == 1) {
			level6_(&live, &totalScoreTemp);
		}
		if (live == 1) {
			level7_(&live, &totalScoreTemp);
		}
		if (live == 1) {
			level8_(&live, &totalScoreTemp);
		}
		if (live == 1) {
			level9_(&live, &totalScoreTemp);
		}
		if (live == 1) {
			level10_(&live, &totalScoreTemp);
		}
		temp.score = totalScoreTemp;
	}
	else if (**type == 2) {
		do {


		} while (live == 1);
	}
	else if (**type == 3) {
		do {

		} while (live == 1);
	}
	(**type) = 0;
}


void newGame(int ***totalSave, int *type, struct data save[4], struct data normalHs[11],int ***totalNormalHs) {
	struct data temp;
	system("cls");
	printf("Name: "); scanf("%[^\n]", temp.name);
	startGame(&totalSave, &type, save, temp);
	updateHsNormal(normalHs, &totalNormalHs, temp);
}

void loadGame(int ***totalSave, int *type, struct data save[4], struct data normalHs[11],int ***totalNormalHs) {
	struct data temp;
	int inp;
	system("cls");
	printf("Which save do you want to load? [1..3]");
	for (int i = 0; i < 3; i++) {
		if (save[i].name != NULL) {
			printf("\n%d. %-20s %d", i + 1, save[i].name, save[i].level);
		}
		else {
			printf("\n%d. %-20s %-5s", i + 1, "Empty", "Empty");
		}
	}
	do {
		printf("\n>> "); scanf("%d", &inp);
	} while (inp < 1 || inp > 3);
	temp = save[inp];
	startGame(&totalSave, &type, save, temp);
	updateHsNormal(normalHs, &totalNormalHs, temp);
}

void singlePlay(int *type, struct data singleHs[][11]) {
	struct data temp;
	system("cls");
	int inp;
	printf("Select the level you want to play");
	for (int i = 0; i < 10; i++) {
	printf("%d ", i + 1);
	}
	do {
	printf("\n>> "); scanf("%d", &inp);
	} while (inp < 1 || inp > 10);
	//startGame(inp);
}

void playMode(int **totalSave, struct data save[], struct data normalHs[], struct data singleHs[][10],int **totalNormalHs) {
	int type;
	system("cls");
	printf("******************");
	printf("\n****   PLAY   ****");
	printf("\n******************\n");
	printf("\n1. New Game");
	printf("\n2. Load Game");
	printf("\n3. Single Play");
	do {
		printf("\n>> "); scanf("%d", &type); fflush(stdin);
	} while (type < 1 || type > 3);
	switch (type) {
	case 1: newGame(&totalSave, &type, save, normalHs, &totalNormalHs); break;
	case 2: loadGame(&totalSave, &type, save, normalHs, &totalNormalHs); break;
	//case 3: singlePlay(type, singleHs, &totalScoreTemp); break;
	}
}

void viewScoreNormal(int totalnormalHs, struct data normalHs[]) {
	system("cls");
	printf("*******************************");
	printf("\n****   NORMAL HIGHSCORES   ****");
	printf("\n*******************************\n");
	printf("===================================================");
	printf("\n| No. | Name                 | Level | Score      |");
	printf("\n===================================================");
	for (int i = 0; i < 10; i++) {
		printf("\n| %02d. | %-20s | %-5d | %-10d |", i + 1, normalHs[i].name, normalHs[i].level, normalHs[i].score);
	}
	printf("\n===================================================");
}

void viewScoreArcade(int totalsingleHs[][11], struct data singleHs[][11]) {
	system("cls");
	int inp;
	do{
		printf("Select level [1..10]: "); scanf("%d", &inp);
	}while(inp < 1 ||inp > 10);
	printf("*********************************");
	printf("\n****   LEVEL %d HIGHSCORES   ****", inp);
	printf("\n*********************************\n");
	printf("===================================================");
	printf("\n| No. | Name                 | Level | Score      |");
	printf("\n===================================================");
	for (int i = 0; i < 10; i++) {
		printf("\n| %d. | %-20s | %-2d | %-5d |", i+1, singleHs[i][i], singleHs[i][i], singleHs[i][i]);
	}
	printf("===================================================");
}

void Leaderboard(int totalnormalHs, int totalsingleHs[], struct data normalHs[], struct data singleHs[][10]) {
	int inp;
	system("cls");
	printf("************************");
	printf("\n****   HIGHSCORES   ****");
	printf("\n************************\n");
	printf("\n1. Normal Mode");
	printf("\n2. Arcade Mode");
	do {
		printf("\n>> "); scanf("%d", &inp); fflush(stdin);
	} while (inp < 1 || inp > 2);
	switch (inp) {
	case 1: viewScoreNormal(totalnormalHs, normalHs);
		//case 2: viewScoreArcade(totalsingleHs, singleHs);
	}
	printf("\n");
	system("pause");
}

void howToPlay() {
	system("cls");
	printf("********************");
	printf("\n****   HOW TO   ****");
	printf("\n********************\n");
	printf("\nThe game is pretty easy, you just need to move around the snake from the head using these keys");
	printf("\nw: up");
	printf("\ns: down");
	printf("\na: left");
	printf("\nd: right");
	printf("\nEvery time you eat a food, your score and the speed of the snake will increase, and there is a goal for every level");
	printf("\nReach that goal and you will pass that level!");
	printf("\nBe careful not to touch the walls or yourself! Beware of them. They may kill you");
	printf("\nHere is a list of foods available in this game: ");
	printf("\n==========================================");
	printf("\n| Name                 | Picture | Score |");
	printf("\n==========================================");
	printf("\n| %-20s | %4c    | %-5d |", "Pellet", 'O', 1);
	printf("\n| %-20s | %4c    | %-5d |", "Mouse", 248, 3);
	printf("\n| %-20s | %4c    | %-5d |", "Pellet", 232, 5);
	printf("\n==========================================\n");
	system("pause");
}

void credits() {
	system("cls");
	printf("Made by Kevin");
	printf("\nFew Ideas by Astrid");
	printf("\nIdea about frog and mouse by my sister\n");
	system("pause");
}

void game(int *exit, struct data save[], struct data normalHs[11], int *totalSave, int *totalNormalHs, int totalsingleHs[11], struct data singleHs[][10]) {
	int inp;
	system("cls");
	system("color b0");
	printf("*******************");
	printf("\n****   SNAKE   ****");
	printf("\n*******************\n");
	printf("\n1. Play");
	printf("\n2. Leaderboard");
	printf("\n3. How to play");
	printf("\n4. Credits");
	printf("\n5. Exit");
	do {
		printf("\n>> "); scanf("%d", &inp); fflush(stdin);
	} while (inp < 1 || inp > 5);
	switch (inp) {
	case 1: playMode(&totalSave, save, normalHs, singleHs, &totalNormalHs); break;
	case 2: Leaderboard(*totalNormalHs, totalsingleHs, normalHs, singleHs); break;
	case 3: howToPlay(); break;
	case 4: credits(); break;
	case 5: printf("Thank you for playing our game, we hope you enjoy it");
		printf("\nCome back next time\n");
		writeFileScoresNormal(*totalNormalHs, normalHs);
		writeFileSaveGame(*totalSave, save);
		(*exit) += 1;
		break;
	}
}

int main() {
	struct data save[4];
	struct data normalHs[10];
	struct data singleHs[6][10];
	int speed, exit = 0, totalSave, totalNormalHs, totalsingleHs[10];
	readFileScoresNormal(&totalNormalHs, normalHs);
	readFileSaveGame(&totalSave, save);
	do {
		game(&exit, save, normalHs, &totalSave, &totalNormalHs, totalsingleHs, singleHs);
	} while (exit == 0);
}

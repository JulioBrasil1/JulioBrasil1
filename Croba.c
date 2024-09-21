#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <locale.h>
#include <time.h>
#include <mmsystem.h>

#define MEDIO 10
#define DIFICIL 20
#define MAX_RANKING 5

typedef struct {
    char name[30];
    int score;
    int timePlayed;
    int difficulty;
} Player;
Player ranking[MAX_RANKING]; 
Player currentPlayer1, currentPlayer2;

int width,height;
int gameOver;
int cobrax, cobray, cobra2x, cobra2y, fruitX, fruitY, score,score2;
int tailX[100], tailX2[100], tailY2[100], tailY[100];
int nTail, nTail2;
int dif;
int speed;
int modo;
int vencedor;

const char *RANKING_FILE_SINGLE = "ranking_single.txt";
const char *RANKING_FILE_MULTI = "ranking_multi.txt";

enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN };
enum eDirection dir,dir2;

void Check();
void Croba();
void modo_de_jogo();
void Dificuldade();
void Setup();
void Setup2();
void Draw();
void Draw2();
void gotoxy(int x, int y);
void HideCursor();
void InputP1();
void InputP2();
void Logic();
void Logic2();
void UpdateRanking();
void DisplayRanking();
void LoadRanking();
void SaveRanking();
void stopSound();

int main() {
    setlocale(LC_ALL, "Portuguese");
    
    Croba();

    system("cls");

    printf("\nAdeus\n");

    Sleep(1500);

    return 0;
}
void Croba() {
    time_t startTime, endTime;
        double timePlayed;
    gameOver = 0;
    PlaySoundA("menu.wav", NULL, SND_ASYNC | SND_LOOP);
    modo_de_jogo();
    LoadRanking();
    startTime = time(NULL);
    if(modo == 1) {
        Dificuldade();
        stopSound();
        PlaySoundA("singleplayer.wav", NULL, SND_ASYNC | SND_LOOP);
        Setup();
        HideCursor();
        while (!gameOver) {
            Draw();
            Sleep(speed);
            InputP1();
            Logic();
        }
        Beep(400, 150);
        Beep(300, 150);
        Beep(200, 150);
        Beep(100, 150);
        system("cls");
        printf("\nFim de jogo\n");
        printf("Pontuação: %d\n\n", score);
        printf("Digite seu nome: ");
        scanf("%s", currentPlayer1.name);
        currentPlayer1.score = score;
        currentPlayer1.difficulty = dif;
        endTime = time(NULL);
        timePlayed = difftime(endTime, startTime);
        currentPlayer1.timePlayed = (int)timePlayed;
        UpdateRanking();
        SaveRanking();
        DisplayRanking();
        system("pause");
        Sleep(400);
    }

    else if(modo == 2) {
        Setup2();
        PlaySoundA("multiplayer.wav", NULL, SND_ASYNC | SND_LOOP);
        HideCursor();
        while (!gameOver) {
            Draw2();
            Sleep(speed);
            InputP2();
            Logic2();
        }
        Beep(400, 150);
        Beep(300, 150);
        Beep(200, 150);
        Beep(100, 150);
        system("cls");
        printf("\nFim de jogo\n");
        if(vencedor == 1){
            score += 300;
            printf("\nPlayer 1 venceu!\n");
        }
        if(vencedor == 2){
            score2 += 300;
            printf("\nPlayer 2 venceu!\n");
        }
        if(vencedor == 0){
            printf("Empate!\n");
        }
        printf("Pontuação P1: %d\n", score);
        printf("Pontuação P2: %d\n", score2);
        printf("\nDigite o nome do Jogador 1: ");
        scanf("%s", currentPlayer1.name);
        currentPlayer1.score = score;
        currentPlayer1.difficulty = 20;

        printf("\nDigite o nome do Jogador 2: ");
        scanf("%s", currentPlayer2.name);
        currentPlayer2.score = score2;
        currentPlayer2.difficulty = 20;
        endTime = time(NULL);
        timePlayed = difftime(endTime, startTime);
        currentPlayer1.timePlayed = (int)timePlayed;
        currentPlayer2.timePlayed = (int)timePlayed;
        UpdateRanking();
        SaveRanking();
        DisplayRanking();
        system("pause");
    }
    Sleep(400);
    Check();
}

void stopSound() {
    PlaySoundA(NULL, NULL, SND_PURGE);
}

void modo_de_jogo() {
    printf("..._____.....______......_____....._______.....________......\n");
    printf("./.____|...|..__...|....|..__.|...|..__..|....|...__...|.....\n"); 
    printf("|.|........|..|_)..|....|.|.|.|...|..|_).|....|..|..|..|.....\n"); 
    printf("|.|........|..__./.|....|.|.|.|...|..__..L....|..|__|..|.....\n");
    printf("|.|____....|..|.L..L....|.|_|.|...|..|_)..L...|..|..|..|.....\n");
    printf(".L_____|...|__|..L__|...|_____|...|_______|...|__|..|__|.....\n\n");
    printf("        Pressione qualquer tecla para começar");
    switch(getch()) {
    default:
        system("cls");
    }
    system("cls");
    printf("Escolha um modo de jogo:\n\n");
    printf("1 - Single Player\n2 - Multiplayer\n");

    switch(getch()) {
    case '1':
        modo = 1;
        break;
    case '2':
        modo = 2;
        break;
    default:
        system("cls");
        modo_de_jogo();
    }
    system("cls");
}
void Dificuldade() {
    printf("Escolha a dificuldade\n\n");
    printf("1 - Fácil\n2 - Médio\n3 - Difícil\n");

    switch(getch()) {
    case '1':
        dif = 0;
        break;
    case '2':
        dif = MEDIO;
        break;
    case '3':
        dif = DIFICIL;
        break;
    default:
        system("cls");
        Dificuldade();
    }
    system("cls");
}
void Setup() {
    speed = 250;
    width = 18;
    height = 18;
    dir = STOP;
    cobrax = width / 2;
    cobray = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    nTail = 0;
    score = 0;
    Beep(500, 150);
    Beep(600, 150);
    Beep(700, 150);
}
void Setup2() {
    speed = 150;
    width = 20;
    height = 20;
    dir = STOP;
    dir2 = STOP;
    cobrax = 2;
    cobray = height / 2;
    cobra2x = width - 2;
    cobra2y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    nTail = 0;
    nTail2 = 0;
    score = 0;
    score2 = 0;
    Beep(500, 150);
    Beep(600, 150);
    Beep(700, 150);
}
void Draw() {
    int i,j,k;

    gotoxy(0,0);
    printf("w/a/s/d: movimentação\nx: encerrar\n");
    printf("\t\t\tPontuação: %d\n", score);

    for (i = 0; i < width + 2; i++)
        printf("\033[44m \033[104m ");
    printf("\n");

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            if (j == 0)
                printf("\033[0m \033[104m ");
            if (i == cobray && j == cobrax)
                printf("\033[45m \033[45m ");
            else if (i == fruitY && j == fruitX)
                printf("\033[41m \033[41m ");
            else {
                int print = 0, printfruit = 0;
                for (k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        printf("\033[105m \033[105m ");
                        print = 1;
                    }
                }
                for (k = 0; k < nTail; k++) {
                    if(tailX[k] == fruitX && tailY[k] == fruitY) {
                        fruitX = rand() % width;
                        fruitY = rand() % height;
                        k = 0;
                        printfruit = 0;
                        continue;
                    }
                    else
                        printfruit = 1;
                }
                if(printfruit && fruitX == j && fruitY == i) {
                    printf("\033[41m \033[41m ");
                    print = 1;
                }
                if (!print)
                    printf("\033[42m \033[102m ");
            }
            if (j == width - 1)
                printf("\033[44m \033[104m");
        }
        printf("\n");
    }
    for (i = 0; i < width + 2; i++)
        printf("\033[44m \033[104m ");
    printf("\033[0m \033[0m ");    
    printf("\n");
}
void Draw2() {
    int i,j,k;

    gotoxy(0,0);
    printf("movimentação P1: w/a/s/d\nmovimentação P2: i/j/k/l\nx: encerrar\n\n");
    printf("Pontuação P1: %d        Pontuação P2: %d\n", score,score2);

    for (i = 0; i < width + 1; i++)
        printf("\033[44m \033[104m ");
    printf("\n");

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            if (j == 0)
                printf("\033[44m \033[104m");
            if (i == cobray && j == cobrax)
                printf("\033[45m \033[45m ");
            else if (i == cobra2y && j == cobra2x)
                printf("\033[43m \033[43m ");
            else if (i == fruitY && j == fruitX)
                printf("\033[41m \033[41m ");
            else {
                int print = 0, printfruit = 0;
                for (k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        printf("\033[105m \033[105m ");
                        print = 1;
                    }
                }
                for (k = 0; k < nTail2; k++) {
                    if(tailX2[k] == j && tailY2[k] == i) {
                        printf("\033[103m \033[103m ");
                        print = 1;
                    }
                }
                for (k = 0; k < nTail || k < nTail2; k++) {
                    if(tailX[k] == fruitX && tailY[k] == fruitY) {
                        fruitX = rand() % width;
                        fruitY = rand() % height;
                        k = 0;
                        printfruit = 0;
                        continue;
                    }
                    else if (tailX2[k] == fruitX && tailY2[k] == fruitY) {
                        fruitX = rand() % width;
                        fruitY = rand() % height;
                        k = 0;
                        printfruit = 0;
                        continue;
                    }
                    else
                        printfruit = 1;
                }
                if(printfruit && fruitX == j && fruitY == i) {
                    printf("\033[41m \033[41m ");
                    print = 1;
                }
                if (!print)
                    printf("\033[42m \033[102m ");
            }

            if (j == width - 1)
                printf("\033[44m \033[104m");
        }
        printf("\n");
    }
    for (i = 0; i < width + 1; i++)
        printf("\033[44m \033[104m ");
    printf("\033[0m \033[0m ");
    printf("\n");
}
void InputP1() {
    if (_kbhit()) {
        switch (getch()) {
        case 'a':
        case 'A':
            if(dir != RIGHT) {
                dir = LEFT;
                Beep(600, 30);
                break;
            }
            else
                break;
        case 'd':
        case 'D':
            if(dir != LEFT) {
                dir = RIGHT;
                Beep(600, 30);
                break;
            }
            else
                break;
        case 'w':
        case 'W':
            if(dir != DOWN) {
                dir = UP;
                Beep(600, 30);
                break;
            }
            else
                break;
        case 's':
        case 'S':
            if(dir != UP) {
                dir = DOWN;
                Beep(600, 30);
                break;
            }
            else
                break;
        case 'x':
        case 'X':
            gameOver = 1;
            break;
        }
    }
}
void InputP2() {
    if (_kbhit()) {
        switch (getch()) {
        case 'a':
        case 'A':
            if(dir != RIGHT) {
                Beep(600, 30);
                dir = LEFT;
                break;
            }
            else
                break;
        case 'd':
        case 'D':
            if(dir != LEFT) {
                Beep(600, 30);
                dir = RIGHT;
                break;
            }
            else
                break;
        case 'w':
        case 'W':
            if(dir != DOWN) {
                Beep(600, 30);
                dir = UP;
                break;
            }
            else
                break;
        case 's':
        case 'S':
            if(dir != UP) {
                Beep(600, 30);
                dir = DOWN;
                break;
            }
            else
                break;
        case 'j':
        case 'J':
            if(dir2 != RIGHT) {
                Beep(600, 30);
                dir2 = LEFT;
                break;
            }
            else
                break;
        case 'l':
        case 'L':
            if(dir2 != LEFT) {
                Beep(600, 30);
                dir2 = RIGHT;
                break;
            }
            else
                break;
        case 'i':
        case 'I':
            if(dir2 != DOWN) {
                Beep(600, 30);
                dir2 = UP;
                break;
            }
            else
                break;
        case 'k':
        case 'K':
            if(dir2 != UP) {
                Beep(600, 30);
                dir2 = DOWN;
                break;
            }
            else
                break;
        case 'x':
        case 'X':
            gameOver = 1;
            break;
        }
    }
}
void Logic() {
    int i;
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = cobrax;
    tailY[0] = cobray;

    for (i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
    case LEFT:
        cobrax--;
        break;
    case RIGHT:
        cobrax++;
        break;
    case UP:
        cobray--;
        break;
    case DOWN:
        cobray++;
        break;
    default:
        break;
    }

    if (cobrax >= width || cobrax < 0)
        gameOver = 1;
    if (cobray >= height || cobray < 0)
        gameOver = 1;

    for (i = 0; i < nTail; i++) {
        if (tailX[i] == cobrax && tailY[i] == cobray)
            gameOver = 1;
    }

    if (cobrax == fruitX && cobray == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
        Beep(1000, 30);
        if(dif == MEDIO && speed > 120)
            speed -= dif;
        if(dif == DIFICIL && speed > 50)
            speed -= dif;
    }
}
void Logic2() {
    int i;
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = cobrax;
    tailY[0] = cobray;
    int prevX2 = tailX2[0];
    int prevY2 = tailY2[0];
    int prev2X2, prev2Y2;
    tailX2[0] = cobra2x;
    tailY2[0] = cobra2y;

    for (i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    for (i = 1; i < nTail2; i++) {
        prev2X2 = tailX2[i];
        prev2Y2 = tailY2[i];
        tailX2[i] = prevX2;
        tailY2[i] = prevY2;
        prevX2 = prev2X2;
        prevY2 = prev2Y2;
    }

    switch (dir) {
    case LEFT:
        cobrax--;
        break;
    case RIGHT:
        cobrax++;
        break;
    case UP:
        cobray--;
        break;
    case DOWN:
        cobray++;
        break;
    default:
        break;
    }

    switch (dir2) {
    case LEFT:
        cobra2x--;
        break;
    case RIGHT:
        cobra2x++;
        break;
    case UP:
        cobra2y--;
        break;
    case DOWN:
        cobra2y++;
        break;
    default:
        break;
    }

    if (cobrax >= width || cobrax < 0) {
        vencedor = 2;
        gameOver = 1;
    }
    if (cobray >= height || cobray < 0) {
        vencedor = 2;
        gameOver = 1;
    }
    if (cobra2x >= width || cobra2x < 0) {
        vencedor = 1;
        gameOver = 1;
    }
    if (cobra2y >= height || cobra2y < 0) {
        vencedor = 1;
        gameOver = 1;
    }
    if(cobra2y == cobray && cobra2x == cobrax) {
        vencedor = 0;
        gameOver = 1;
    }

    for (i = 0; i < nTail; i++) {
        if (tailX[i] == cobrax && tailY[i] == cobray) {
            vencedor = 2;
            gameOver = 1;
        }
    }
    for (i = 0; i < nTail2; i++) {
        if (tailX2[i] == cobra2x && tailY2[i] == cobra2y) {
            vencedor = 1;
            gameOver = 1;
        }
    }
    for (i = 0; i < nTail; i++) {
        if (tailX[i] == cobra2x && tailY[i] == cobra2y) {
            vencedor = 1;
            gameOver = 1;
        }
    }
    for (i = 0; i < nTail2; i++) {
        if (tailX2[i] == cobrax && tailY2[i] == cobray) {
            vencedor = 2;
            gameOver = 1;
        }
    }

    if (cobrax == fruitX && cobray == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
        Beep(1000, 30);
    }
    if (cobra2x == fruitX && cobra2y == fruitY) {
        score2 += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail2++;
        Beep(1000, 30);
    }
}
void Check() {
    Sleep(400);
    system("cls");
    printf("\nDeseja continuar?\n");
    printf("1 - Sim\n2 - Não\n");
    switch(getch()) {
    case '1':
        system("cls");
        Croba();
    case '2':
        break;
        stopSound();
    default:
        Check();
    }
}
void gotoxy(int x, int y){
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void HideCursor(){
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}
void LoadRanking() {
    const char *RANKING_FILE;
    if (modo == 1) {
        RANKING_FILE = RANKING_FILE_SINGLE;
    } else {
        RANKING_FILE = RANKING_FILE_MULTI;
    }    
    FILE *file = fopen(RANKING_FILE, "r");
    if (!file) {
        file = fopen(RANKING_FILE, "w");
        if (file) {
            for (int i = 0; i < MAX_RANKING; i++) {
                fprintf(file, "N/A 0 0 0\n");
            }
            fclose(file);
        }
        file = fopen(RANKING_FILE, "r");
    }
    if (file) {
        for (int i = 0; i < MAX_RANKING; i++) {
            if (fscanf(file, "%29s %d %d %d", ranking[i].name, &ranking[i].score, &ranking[i].timePlayed, &ranking[i].difficulty) != 4) {
                ranking[i].score = 0;
                ranking[i].timePlayed = 0;
                ranking[i].difficulty = 0;
                strcpy(ranking[i].name, "N/A");
            }
        }
        fclose(file);
    } else {
        for (int i = 0; i < MAX_RANKING; i++) {
            ranking[i].score = 0;
            ranking[i].timePlayed = 0;
            ranking[i].difficulty = 0;
            strcpy(ranking[i].name, "N/A");
        }
    }
}
void SaveRanking() {
    const char *RANKING_FILE;
    if (modo == 1) {
        RANKING_FILE = RANKING_FILE_SINGLE;
    } else {
        RANKING_FILE = RANKING_FILE_MULTI;
    }
    FILE *file = fopen(RANKING_FILE, "w");
    if (file) {
        for (int i = 0; i < MAX_RANKING; i++) {
            fprintf(file, "%s %d %d %d\n", ranking[i].name, ranking[i].score, ranking[i].timePlayed, ranking[i].difficulty);
        }
        fclose(file);
    }
}
void UpdateRanking() {
    Player newPlayer;
    if (modo == 1) {
        newPlayer = currentPlayer1;
    } else {
        newPlayer = (currentPlayer1.score >= currentPlayer2.score) ? currentPlayer1 : currentPlayer2;
    }
    for (int i = 0; i < MAX_RANKING; i++) {
        if (newPlayer.score > ranking[i].score) {
            for (int j = MAX_RANKING - 1; j > i; j--) {
                ranking[j] = ranking[j - 1];
            }
            ranking[i] = newPlayer;
            break;
        }
    }
}
void DisplayRanking() {
    printf("\nRanking:\n");
    for (int i = 0; i < MAX_RANKING; i++) {
        printf("%d. %s - %d pontos - Tempo: %d - Dificuldade: %d\n",
               i + 1, ranking[i].name, ranking[i].score, ranking[i].timePlayed, ranking[i].difficulty);
    }
}
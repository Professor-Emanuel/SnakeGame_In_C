#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#define nrRows 20
#define nrColumns 40

int i, j, Field[nrRows][nrColumns], x, y, Gy;
int Head, Tail, Game, Frogs, a, b, var, dir, score, HighScore, Speed;

FILE *f;

void snakeInitialization(){
    f = fopen("highscore.txt", "r");
    fscanf(f, "%d", &HighScore);
    fclose(f);

    for(i = 0; i<nrRows; i++){
        for(j = 0; j<nrColumns; j++){
            Field[i][j] = 0;
        }
    }

    x = nrRows/2;
    y = nrColumns/2;
    Gy = y;
    Head = 5;
    Tail = 1;
    Game = 0;
    Frogs = 0;
    dir = 'd';
    score = 0;
    Speed = 99;

    for(i = 0; i<Head; i++){
        Gy++;
        Field[x][Gy - Head] = i + 1;
    }
}

void print(){
    for(i = 0; i <= nrColumns + 1; i++){
        if(i==0){
            printf("%c", 201);
        }
        else if(i== nrColumns+1){
            printf("%c", 187);
        }
        else{
            printf("%c", 205);
        }
    }
    printf("    Current Score: %d  HighScore: %d", score, HighScore);
    printf("\n");

    for(i=0; i<nrRows; i++){
        printf("%c", 186);

        for(j=0; j<nrColumns; j++){
            if(Field[i][j] == 0){
                printf(" ");
            }
            if(Field[i][j] > 0 && Field[i][j] != Head){
                printf("%c", 176);
            }
            if(Field[i][j] == Head){
                printf("%c", 178);
            }
            if(Field[i][j] == -1){
                printf("%c", 15);
            }
            if(j == nrColumns-1){
                printf("%c\n", 186);
            }
        }
    }

    for(i = 0; i <= nrColumns + 1; i++){
        if(i==0){
            printf("%c", 200);
        }
        else if(i== nrColumns+1){
            printf("%c", 188);
        }
        else{
            printf("%c", 205);
        }
    }
}

void ResetScreenPosition(){
    HANDLE hOut;
    COORD Position;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    Position.X = 0;
    Position.Y = 0;

    SetConsoleCursorPosition(hOut, Position);
}

void Random(){
    srand(time(0));
    a = 1 + rand() % 18;
    b = 1 + rand() % 38;

    if(Frogs == 0 && Field[a][b] == 0){
        Field[a][b] = -1;
        Frogs = 1;

        if(Speed > 10 && score != 0){
            Speed = Speed - 5;
        }
    }
}

int getchNoblock(){
    if(_kbhit())
        return _getch();
    else
        return -1;
}

void Movement(){
    var = getchNoblock();
    var = tolower(var);

    if( ((var == 'd' || var == 'a') ||  (var == 'w' || var == 's')) && (abs(dir-var) >5) ){
        dir = var;
    }

    if(dir == 'd'){
        y++;
        if(Field[x][y] != 0 && Field[x][y] != -1){
            GameOver();
        }

        if(y == nrColumns - 1){
            y = 0;
        }

        if(Field[x][y] == -1){
            Frogs = 0;
            score += 5;
            Tail -= 2;
        }

        Head++;
        Field[x][y] = Head;
    }

    if(dir == 'a'){
        y--;
        if(Field[x][y] != 0 && Field[x][y] != -1){
            GameOver();
        }

        if(y == 0){
            y =nrColumns - 1;
        }

        if(Field[x][y] == -1){
            Frogs = 0;
            score += 5;
            Tail -= 2;
        }

        Head++;
        Field[x][y] = Head;
    }

    if(dir == 'w'){
        x--;
        if(Field[x][y] != 0 && Field[x][y] != -1){
            GameOver();
        }

        if( x == -1){
            x = nrRows - 1;
        }

        if(Field[x][y] == -1){
            Frogs = 0;
            score += 5;
            Tail -= 2;
        }

        Head++;
        Field[x][y] = Head;
    }

    if(dir == 's'){
        x++;
        if(Field[x][y] != 0 && Field[x][y] != -1){
            GameOver();
        }

        if(x == nrRows - 1){
            x = 0;
        }

        if(Field[x][y] == -1){
            Frogs = 0;
            score += 5;
            Tail -= 2;
        }

        Head++;
        Field[x][y] = Head;
    }

}

void TailRemove(){
    for(i = 0; i <nrRows; i++){
        for(j = 0; j<nrColumns; j++){
            if(Field[i][j] == Tail){
                Field[i][j] = 0;
            }
        }
    }
    Tail++;
}

void GameOver(){
    printf("\a");
    Sleep(1500);
    system("Cls");

    if(score >HighScore){
        printf("   New HighScore %d!!!!!!!\n\n", score);
        system("pause");
        f = fopen("highscore.txt", "w");
        fprintf(f, "%d", score);
        fclose(f);
    }
    system("Cls");
    printf("\n\n         Game Over !!!!!!");
    printf("             Score : %d \n\n", score);
    printf("             Press Enter to play again or ESC to exit ...\n");

    while(1){
        var = getchNoblock();
        if(var == 13){
            Game = 0;
            snakeInitialization();
            break;
        }
        else if(var == 27){
            Game = 1;
            break;
        }
    }

    system("Cls");

}

void main()
{
    /*
    printf("ascii of 201 gives: %c\n\n", 201);
    printf("ascii of 187 gives: %c\n\n", 187);
    printf("ascii of 205 gives: %c\n\n", 205);
    printf("ascii of 186 gives: %c\n\n", 186);
    printf("ascii of 200 gives: %c\n\n", 200);
    printf("ascii of 188 gives: %c\n\n", 188);
    */

    snakeInitialization();
    while(Game == 0){
        print();
        ResetScreenPosition();
        Random();
        Movement();
        TailRemove();
        Sleep(Speed);
    }

}

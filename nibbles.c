#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define WIDTH 40
#define HEIGHT 20
#define SNAKE_MAX_LENGTH 100

typedef struct {
    int x[SNAKE_MAX_LENGTH]; 
    int y[SNAKE_MAX_LENGTH];
    int comp;
    int directionX;
    int directionY;
} Snack;

Snack snack;
bool gameover = false;

char telaBuffer[HEIGHT][WIDTH];

void inicializer(){
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    start_color();
    
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);

    snack.comp = 1;
    snack.x[0] = WIDTH/2;
    snack.y[0] = HEIGHT/2;
    snack.directionX = 1;
    snack.directionY = 0;

    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            if(i == 0 || i == HEIGHT-1 || j == 0 || j == WIDTH-1){
                telaBuffer[i][j] = '#';
        }
        else{
                telaBuffer[i][j] = ' ';
            }
        }
    }
}

void draw(){
    for(int i = 0; i< HEIGHT; i++){
        for(int j=0; j<WIDTH; j++){
            mvaddch(i, j, telaBuffer[i][j]);
        }
    }

    refresh();
}



int main(){
    inicializer();
    draw();
    while(!gameover){
        
    }

}
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define WIDTH 40
#define HEIGHT 20
#define SNAKE_MAX_LENGTH 100
#define DEFAULT_WAIT 100

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
    nodelay(stdscr, TRUE);
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

    for(int i = 0; i < snack.comp; i++){
        int x = snack.x[i];
        int y = snack.y[i]; 
        telaBuffer[y][x] = '@';
    }

    for(int i = 0; i< HEIGHT; i++){
        for(int j=0; j<WIDTH; j++){
            mvaddch(i, j, telaBuffer[i][j]);
        }
    }

    refresh();
}

    void update(){
            int novoX = snack.x[0] + snack.directionX;
            int novoY = snack.y[0] + snack.directionY;

            if(novoX <= 0 || novoX >= WIDTH-1 || novoY <= 0 || novoY >= HEIGHT-1){
                gameover = true;
            }
            
            snack.x[0] = novoX;
            snack.y[0] = novoY;
    }

    void processInput(){
        int tecla = getch();

        switch(tecla){
            case KEY_UP:
                if(snack.directionY == 0){
                    snack.directionY = -1;
                    snack.directionX = 0;
                }
                
                break;
            case KEY_DOWN:
                if(snack.directionY == 0){
                    snack.directionY = 1;
                    snack.directionX = 0;
                }
                break;
            case KEY_LEFT:
                if(snack.directionX == 0){
                    snack.directionY = 0;
                    snack.directionX = -1;
                }
                break;
            case KEY_RIGHT:
                if(snack.directionX == 0){
                    snack.directionY = 0;
                    snack.directionX = 1;
                }
                break;

            case 'x':
            case 'q':
                gameover = true;
                break;
        }
    }


int main(){
    inicializer();
    while(!gameover){
        draw();
        update();
        processInput();

        napms(DEFAULT_WAIT);
    }

    endwin();

}
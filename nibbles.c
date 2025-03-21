#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define WIDTH 40
#define HEIGHT 20
#define SNAKE_MAX_LENGTH 100
#define DEFAULT_WAIT 100
#define WALL '*'
#define FOOD '+'
#define SNAKE '@'
#define WALL_COLOR 1
#define FOOD_COLOR 2
#define SNAKE_COLOR 3
typedef struct {
    int x[SNAKE_MAX_LENGTH]; 
    int y[SNAKE_MAX_LENGTH];
    int comp;
    int directionX;
    int directionY;
} Snack;

typedef struct {
    int x;
    int y;
} Food;

Food food;
Snack snack;
bool gameover = false;
char telaBuffer[HEIGHT][WIDTH];
int score = 0;

void inicializer();
void draw();
void update();
void processInput();
void foodTruck();

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

void inicializer(){
    initscr();
    cbreak();
    nodelay(stdscr, TRUE);
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    start_color();
    
    init_pair(SNAKE_COLOR, COLOR_GREEN, COLOR_BLACK);
    init_pair(FOOD_COLOR, COLOR_RED, COLOR_BLACK);
    init_pair(WALL_COLOR , COLOR_YELLOW, COLOR_BLACK);

    snack.comp = 1;
    snack.x[0] = WIDTH/2;
    snack.y[0] = HEIGHT/2;
    snack.directionX = 1;
    snack.directionY = 0;

    foodTruck();

    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            if(i == 0 || i == HEIGHT-1 || j == 0 || j == WIDTH-1){
                telaBuffer[i][j] = WALL;
        }
        else{
                telaBuffer[i][j] = ' ';
            }
        }
    }
}

void foodTruck(){
    food.x = 1 + rand() % (WIDTH - 2) + 1;
    food.y = 1 + rand() % (HEIGHT - 2) + 1;
}

void draw(){

    for(int i = 1; i < HEIGHT -1; i++){
        for(int j = 1; j < WIDTH -1; j++){
                telaBuffer[i][j] = ' ';
        }
    }

    telaBuffer[food.y][food.x] = FOOD;

    for(int i = 0; i < snack.comp; i++){
        int x = snack.x[i];
        int y = snack.y[i]; 
        telaBuffer[y][x] = SNAKE;
    }

    for(int i = 0; i< HEIGHT; i++){
        for(int j=0; j<WIDTH; j++){
            if(telaBuffer[i][j] == WALL){
                attron(COLOR_PAIR(WALL_COLOR));
                mvaddch(i, j, telaBuffer[i][j]);
                attroff(COLOR_PAIR(WALL_COLOR));
            }
            else if(telaBuffer[i][j] == FOOD){
                attron(COLOR_PAIR(FOOD_COLOR));
                mvaddch(i, j, telaBuffer[i][j]);
                attroff(COLOR_PAIR(FOOD_COLOR));
            }
            else if(telaBuffer[i][j] == SNAKE){
                attron(COLOR_PAIR(SNAKE_COLOR));
                mvaddch(i, j, telaBuffer[i][j]);
                attroff(COLOR_PAIR(SNAKE_COLOR));
            }
            else{
                mvaddch(i, j, telaBuffer[i][j]);
        }
    }
}

    mvprintw(HEIGHT, 0, "Score: %d", score);
    refresh();
}

    void update(){
            int novoX = snack.x[0] + snack.directionX;
            int novoY = snack.y[0] + snack.directionY;

            if(novoX < 0){
                novoX = WIDTH - 2;
            } else if(novoX >= WIDTH - 1){
                novoX = 1;
            } 

            if(novoY < 0){
                novoY = HEIGHT - 2;
            } else if(novoY >= HEIGHT - 1){
                novoY = 1;
            }

            if(novoX == food.x && novoY == food.y){
                snack.comp++;
                score += 10;
                foodTruck();
            }

            for(int i = 0; i < snack.comp; i++){
                if(novoX == snack.x[i] && novoY == snack.y[i]){
                    gameover = true;
                }
            }

            for(int i = snack.comp - 1; i > 0; i--){
                snack.x[i] = snack.x[i-1];
                snack.y[i] = snack.y[i-1];
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

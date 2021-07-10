#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <conio.h>
using namespace std;

bool gameOver;
const int width = 25;
const int height = 25;
int x, y, fruitX, fruitY, score, difficulty, speed;
int tailX[100], tailY[100];
int nTail;

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;


void Setup() {
    system("clear");
    gameOver = false;
    srand ( time(NULL) );
    fruitX = rand() % (width-1) + 1;
    fruitY = rand() % (height-1) + 1;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    score = 0;
    nTail = 0;

}

void Draw() {
    system("clear");
    cout<<"Score: "<<score<<endl;
    
    for (int i = 0; i < width+1; i ++) {
        cout<<'#';
    }
    cout<<endl;

    for (int i = 0; i < height+1; i++) {
        for (int j = 0; j < width+1; j++) {

            if(j == 0) {
                cout<<'#';
            }  
            
            else if (j == width) {
                cout<<'#';
                cout<<endl;
            }

            else if (i == y && j == x) {
                cout<<'O';
            } 
            
            else if ( i == fruitY && j == fruitX ) {
                cout<<'F';
            } 
            
            else {

                bool print = false;

                for (int k = 1; k <= nTail; k++) {

                    if(tailX[k] == j && tailY[k] == i) {
                        cout<<"o";
                        print = true;
                    }        
                }

                if(!print) {
                    cout<<' ';
                }
                
            }
        }
    } 

    for (int i = 0; i < width+1; i ++) {
        cout<<'#';
    }
    cout<<endl;

}

void Input() {
    
    if(kbhit()) {
        switch(getch()) {
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'w':
                dir = UP;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'q':
                gameOver = true;
                break;
        }
    }
}

void Logic() {

    tailX[0] = x;
    tailY[0] = y;

    for(int i = 1; i <= nTail; i++) {
        
        if( tailX[0] == tailX[i] && tailY[0] == tailY[i]) {
            gameOver = true;
        }
    }

    for(int i = nTail; i > 0; i--) {
        tailX[i] = tailX[i-1];
        tailY[i] = tailY[i-1];
    }

    switch (dir)
    {
    case LEFT:
        x--;
        break;

    case RIGHT:
        x++;
        break;

    case UP:
        y--;
        break;

    case DOWN:
        y++;
        break; 

    case STOP:
        break;

    default:
        break;
    }


    if(x > width || x < 0 || y > height || y < 0) {
        gameOver = true;
    } 

    if(x == fruitX && y == fruitY) {
        nTail++;  
        srand ( time(NULL) );
        fruitX = rand() % (width-1) + 1;
        fruitY = rand() % (height-1) + 1;
        score++;
    }
}

int main() {

    cout<<"Choose from difficulty: "<<endl;
    cout<<"Easy: 1."<<endl;
    cout<<"Medium: 2."<<endl;
    cout<<"Hard: 3."<<endl;
    cin>>difficulty;

    if(difficulty == 1) {
        speed = 150000;
    }
    else if(difficulty == 2) {
        speed = 100000;
    }
    else if(difficulty == 3) {
        speed = 50000;
    } else {
        speed = 150000;
    }

    Setup();

    while(!gameOver) {
        Draw();
        Input();
        Logic();
        usleep(speed);
    }  
    system("clear");
    cout<<"GAME OVER"<<endl;
}
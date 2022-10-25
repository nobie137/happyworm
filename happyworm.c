#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<sys/ioctl.h>

int target, fieldsize;
char worm[8] = "[      ]";
int totargpos = 0;

void wait(int input){
        clock_t start = clock();
        while(clock() < start + (1000 * input));
}
void drawsnek(int input){
    //printf("%d; %d", target, totargpos);
    for(int i = 0; i < input; i++){
        printf("%c", ' ');
    }
    printf("%s\n", worm);
}
void gentarget(){
    srand(time(0));
    target = rand() % fieldsize;
    if(target > fieldsize - (sizeof(worm) / sizeof(worm[0]))) gentarget();
}
void movetotarget(){
    if(totargpos < target){
        totargpos++;
    }
    if(totargpos > target){
        totargpos--;
    }
}
int main(){
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    fieldsize = w.ws_col;
    target = fieldsize / 2;
    gentarget();
    while(1){
        wait(10);
        if(target == totargpos){
            gentarget();
            ioctl(0, TIOCGWINSZ, &w);
            fieldsize = w.ws_col;
        }
        movetotarget();
        drawsnek(totargpos);
        //printf("W%d; %d | w%d\n", w.ws_col, fieldsize, (sizeof(worm) / sizeof(worm[0])));
    }
    return 0;
}

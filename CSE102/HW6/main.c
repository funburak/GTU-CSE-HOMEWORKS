#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define row_max 15
#define col_max 30

char raceMap[row_max][col_max];
int row1=1,col1=1; // starting points for player 1
int row2=3,col2=3; // starting points for player 2
char pos='u';
char pos2='u';

void printMap(char raceMap[row_max][col_max]);
int dice();
int startGame(int d1, int d2);
void printTrack();
int movep1(int d1);    // player 1 move 
int movep2(int d2);    // player 2 move 



int main(){
    int p1d,p2d,start,p1,p2;
    printTrack();
    srand(time(NULL));
    printf("To start the game players should decide who will start first\n");
    printf("\033[;33m"); // set color to yellow
    printf("PLAYER 1... Press ENTER to dice ");
    getchar();
    p1d=dice();
    printf("DICE: %d\n",p1d);
    printf("\033[0m"); // set color to default
    printf("\033[;34m"); // set color to blue
    printf("PLAYER 2... Press ENTER to dice ");
    getchar();
    p2d=dice();
    printf("DICE: %d\n",p2d);
    printf("\033[0m"); // set color to default
    start=startGame(p1d,p2d);
    if(start==p1d){
        printf("\033[;33m"); // set color to yellow
        printf("*** PLAYER 1 WILL START THE GAME ***\n");
        printf("\033[0m"); // set color to default
        while(1){
        printf("\033[;33m"); // set color to yellow
        printf("PLAYER 1... Press ENTER to dice ");
        getchar();
        p1d=dice();
        printf("DICE: %d\n",p1d);
        printf("\033[0m"); // set color to default
        printf("\033[;34m"); // set color to blue
        printf("PLAYER 2... Press ENTER to dice ");
        getchar();
        p2d=dice();
        printf("DICE: %d\n",p2d);
        printf("\033[0m"); // set color to default
        p1=movep1(p1d);
        p2=movep2(p2d);        
        printMap(raceMap);
        if(p1==0 || p2==0){
            break;
        }
        }
    }
    else if(start==p2d){
        printf("\033[;34m"); // set color to blue
        printf("*** PLAYER 2 WILL START THE GAME ***\n");
        printf("\033[0m"); // set color to default
        while(1){
        printf("\033[;34m"); // set color to blue
        printf("PLAYER 2... Press ENTER to dice ");
        getchar();
        p2d=dice();
        printf("DICE: %d\n",p2d);
        printf("\033[0m"); // set color to default
        printf("\033[;33m"); // set color to yellow
        printf("PLAYER 1... Press ENTER to dice ");
        getchar();
        p1d=dice();
        printf("DICE: %d\n",p1d);
        printf("\033[0m"); // set color to default
        p1=movep1(p1d);
        p2=movep2(p2d);
        printMap(raceMap);
        if(p1==0 || p2==0){
            break;
        }
        }
    }
    else if(start==0){
        while(start==0){
        printf("Same dice value. Please try again\n");
        printf("\033[;33m"); // set color to yellow
        printf("PLAYER 1... Press ENTER to dice");
        getchar();
        p1d=dice();
        printf("DICE: %d\n",p1d);
        printf("\033[;34m"); // set color to blue
        printf("PLAYER 2... Press ENTER to dice");
        getchar();
        p2d=dice();
        printf("DICE: %d\n",p2d);
        printf("\033[0m"); // set color to default
        start=startGame(p1d,p2d);
        }
        if(start==p1d){
        printf("\033[;33m"); // set color to yellow
        printf("*** PLAYER 1 WILL START THE GAME ***\n");
        printf("\033[0m"); // set color to default
        while(1){
        printf("\033[;33m"); // set color to yellow
        printf("PLAYER 1... Press ENTER to dice ");
        getchar();
        p1d=dice();
        printf("DICE: %d\n",p1d);
        printf("\033[0m"); // set color to default
        printf("\033[;34m"); // set color to blue
        printf("PLAYER 2... Press ENTER to dice ");
        getchar();
        p2d=dice();
        printf("DICE: %d\n",p2d);
        printf("\033[0m"); // set color to default
        p1=movep1(p1d);
        p2=movep2(p2d);
        printMap(raceMap);
        if(p1==0 || p2==0){
            break;
        }
        }
    }
    else if(start==p2d){
        printf("\033[;34m"); // set color to blue
        printf("*** PLAYER 2 WILL START THE GAME ***\n");
        while(1){
        printf("\033[;34m"); // set color to blue
        printf("PLAYER 2... Press ENTER to dice ");
        getchar();
        p2d=dice();
        printf("DICE: %d\n",p2d);
        printf("\033[0m"); // set color to default
        printf("\033[;33m"); // set color to yellow
        printf("PLAYER 1... Press ENTER to dice ");
        getchar();
        p1d=dice();
        printf("DICE: %d\n",p1d);
        printf("\033[0m"); // set color to default
        p1=movep1(p1d);
        p2=movep2(p2d);
        printMap(raceMap);
        if(p1==0 || p2==0){
            break;
        }
        }
    }
    }

    return 0;
} // end main


void printTrack(){
    for(int r=0;r<row_max;r++){
        for(int c=0;c<col_max;c++){
           if(r==0 || r==row_max-1){
               raceMap[r][c]='-';
            }
            else if(c==0 || c==col_max-1){
                    raceMap[r][c]='|';
            }
            else if((r>=2 && r<=row_max-3 && c>= 2 && c<=col_max-3) &&  (r==2 || r==row_max-3 ||  c==2 || c==col_max-3)){
               if(r==2 || r==row_max-3){
                   raceMap[r][c]='-';
                }
                else if(c==2 || c==col_max-3){
                       raceMap[r][c]='|';
                }
            }
            else if((r>=4 && r<=row_max-5 && c>=4 && c<=col_max-5) && (r==4 || r==row_max-5 || c==4 || c==col_max-5)){
                    if(r==4 || r==row_max-5){
                      raceMap[r][c]='-';
                    }
                    else if(c==4 || c==col_max-5){
                        raceMap[r][c]='|';
                    }
            }
            else if(r==1 && c==1){
                raceMap[r][c]='1'; // starting point of player 1
            }
            else if(r==3 && c==3){
                raceMap[r][c]='2'; // starting point of player 2
            }
            else if((r==1 && c==14) || (r==7 && c==28) || (r==13 && c==14) || (r==3 && c==10) || (r==3 && c==18) || (r==5 && c==26) || (r==10 && c==26) || (r==11 && c==10) || (r==11 && c==18)){
                raceMap[r][c]='X'; // penalty positions
            }
            else if(r==2 && c==1){
                raceMap[r][c]='_';; // end point for player 1
            }
            else if(r==4 && c==3){
                raceMap[r][c]='_'; // end point for player 2
            }
            else{
                
                raceMap[r][c]=' ';
            }
        printf("%c",raceMap[r][c]);
        }
        printf("\n");
    }
} // end printing the race track


int dice(){
    int roll;
    roll=rand()%6 + 1; //  returns random integer in range of [1,6]
    return roll;
} // end dice roll

int startGame(int d1, int d2){
    if(d1>d2){
        return d1;
    }
    else if(d1<d2){
        return d2;
    }
    else if(d1==d2){
        return 0;
    }
} // end deciding who to start

int movep1(int d1){
    raceMap[row1][col1]=' ';
    if(pos=='u'){ // when PLAYER 1 is at the upper side of the race track
        if(d1+col1<=col_max-2){
            col1=col1+d1;
        }
        else{
            d1=d1-(col_max-2-col1);
            row1=row1+d1;
            col1=28;
            pos='r';
        }
    }
    else if(pos=='r'){ // when PLAYER 1 is at the right side of the race track
        if(row1+d1<=row_max-2){
            row1=row1+d1;
        }
        else{
            d1=d1-(row_max-2-row1);
            col1=col1-d1;
            row1=13;
            pos='b';
        }
    }
    else if(pos=='b'){ // when PLAYER 1 is at the bottom side of the race track
        if(col1-d1>=1){
            col1=col1-d1;
        }
        else{
            d1=d1-(col1-1);
            row1=row1-d1;
            col1=1;
            pos='l';
        }
    }
    else if(pos=='l'){ // when PLAYER 1 is at the left side of the race track
        if(row1-d1>1){
            row1=row1-d1;
        }
        else{
            d1=d1-(row1-1);
            row1=1;
            col1=col1+d1;
            raceMap[row1][col1]='1';
            printf("\033[;33m"); // set color to yellow
            printf("PLAYER 1 WON\n");
            printf("\033[0m"); // set color to default
            return 0;
        }
    }
    if(raceMap[row1][col1]=='X'){
        printf("\033[;31m"); // set color to red
        printf("PENATLY FOR PLAYER 1\n");
        printf("\033[0m"); // set color to default
        if(row1==1){
            col1=col1-2;
        }
        else if(col1==col_max-2){
            row1=row1-2;
        }
        else if(row1==row_max-2){
            col1=col1+2;
        }
    }
    raceMap[row1][col1]='1';
} // end player 1 move

int movep2(int d2){
    raceMap[row2][col2]=' ';
    if(pos2=='u'){ // when PLAYER 2 is at the upper side of the race track
        if(col2+d2<=col_max-4){
            col2=col2+d2;
        }
        else{
            d2=d2-((col_max-4)-col2);
            row2=row2+d2;
            col2=col_max-4;
            pos2='r';
        }
    }
    else if(pos2=='r'){ // when PLAYER 2 is at the right side of the race track
        if(row2+d2<=(row_max-4)){
            row2=row2+d2;
        }
        else{
            d2=d2-((row_max-4)-row2);
            col2=col2-d2;
            row2=row_max-4;
            pos2='b';
        }
    }
    else if(pos2=='b'){ // when PLAYER 2 is at the bottom side of the race track
        if(col2-d2>=3){
            col2=col2-d2;
        }
        else{
            d2=d2-(col2-3);
            row2=row2-d2;
            col2=3;
            pos2='l';
        }
    }
    else if(pos2=='l'){ // when PLAYER 2 is at the left side of the race track
        if(row2-d2>3){
            row2=row2-d2;
        }
        else{
            d2=d2-(row2-3);
            row2=3;
            col2=col2+d2;
            raceMap[row2][col2]='2';
            printf("\033[;34m"); // set color to blue
            printf("PLAYER 2 WON\n");
            printf("\033[0m"); // set color to default
            return 0;
        }
    }
    if(raceMap[row2][col2]=='X'){
        printf("\033[;31m"); // set color to red
        printf("PENALTY FOR PLAYER 2\n");
        printf("\033[0m"); // set color to default
        if(row2==3){
            col2=col2-2;
        }
        else if(col2==col_max-4){
            row2=row2-2;
        }
        else if(row2==11){
            col2=col2+2;
        }
    }
    raceMap[row2][col2]='2';
}  // end player 2 move

void printMap(char raceMap[row_max][col_max]){
    for(int r=0;r<row_max;r++){
            for(int c=0;c<col_max;c++){
                if(raceMap[r][c]=='1'){
                	printf("\033[;33m"); // set color to yellow
                }
                else if(raceMap[r][c]=='2'){
                	printf("\033[;34m"); // set color to blue
                }
                else if(raceMap[r][c]=='X'){
                	printf("\033[;31m"); // set color to red
                }
                else if(raceMap[r][c]=='_'){
                	printf("\033[;32m"); // set color to green
                }
                printf("%c",raceMap[r][c]);
                printf("\033[0m"); // set color to default
            }
            printf("\n");
        }
} // end printing map

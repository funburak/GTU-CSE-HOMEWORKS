#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void readFile(char randoms[7][10]);
void fillPuzzle(char puzzle[15][15], char randoms[][10], int n);
void emptyPuzzle(char puzzle[15][15]);
void printPuzzle(char puzzle[15][15]);
void randomCharacters(char puzzle[15][15]);
int searchWord(int row, int column, char word[5], char puzzle[15][15], int length);
void printX(int row, int column,char puzzle[15][15], int direction, int length);

int main(){
    int i,point=0,mistake=3,exit=0,flag;
    int search;
    int row,column,length;
    char word[5];
    char randoms[7][10];
    char puzzle[15][15];
    srand(time(NULL));
    readFile(randoms);
    emptyPuzzle(puzzle);
    for(i=0;i<7;i++){
        fillPuzzle(puzzle,randoms,i);
    }
    randomCharacters(puzzle);
    printPuzzle(puzzle);
    while(1){
        flag=0;
        printf("Enter coordiantes and word\n");
        if(scanf("%d %d %s",&row,&column,word)==3){
                length=strlen(word);
                search=searchWord(row,column,word,puzzle,length);
                    if(search>=1){
                        for(int k=0;k<7;k++){
                            if(strcmp(word,randoms[k])==0){ // If the entered word is in the word list
                                flag=1;
                            }
                        }
                        if(flag==0){ // If the entered word cannot be found in the list, lose 1 life
                            mistake--;
                            printf("Wrong choice! You have only %d lefts\n",mistake);
                            printf("Wrong choice! The given word cannot be found in the wordlist.txt file\n");
                        }
                    }
                if(flag==1){ 
                switch(search){
                case 1:
                    point+=2;
                    printf("Founded! You got 2 points. Your total point is:%d\n",point);
                    printX(row,column,puzzle,search,length);
                    break;
                case 2:
                    point+=2;
                    printf("Founded! You got 2 points. Your total point is:%d\n",point);
                    printX(row,column,puzzle,search,length);
                    break;
                case 3:
                    point+=2;
                    printf("Founded! You got 2 points. Your total point is:%d\n",point);
                    printX(row,column,puzzle,search,length);
                    break;
                case 4:
                    point+=2;
                    printf("Founded! You got 2 points. Your total point is:%d\n",point);
                    printX(row,column,puzzle,search,length);
                    break;
                case 5:
                    point+=2;
                    printf("Founded! You got 2 points. Your total point is:%d\n",point);
                    printX(row,column,puzzle,search,length);
                    break;
                case 6:
                    point+=2;
                    printf("Founded! You got 2 points. Your total point is:%d\n",point);
                    printX(row,column,puzzle,search,length);
                    break;
                case 7:
                    point+=2;
                    printf("Founded! You got 2 points. Your total point is:%d\n",point);
                    printX(row,column,puzzle,search,length);
                    break;    
                case 8:
                    point+=2;
                    printf("Founded! You got 2 points. Your total point is:%d\n",point);
                    printX(row,column,puzzle,search,length);
                    break;
                case 0:
                    mistake--;
                    printf("Wrong choice! You have only %d lefts\n",mistake);
                    break;
                }
                }
        }
        else{
            scanf("%s",word);
            if(strcmp(word,":q")==0){
                printf("Exiting...\n");
                exit=1;
                break;
            }
        }
        if(point==14){
            printf("Congrats! You have found all the words\n");
        }
        if(point==14 || mistake==0 || exit==1){
            break;
        }
    }
    printf("Your total point is %d\n",point);

    return 0;
} // end main


// This function takes 7 random uniqie words from the text file
void readFile(char randoms[7][10]){
    FILE *read;
    int i,j,random,flag=1,counter=0;
    int randomNumbers[7];
    char words[50][10];
    read=fopen("wordlist.txt","r");
    if(read==NULL){
        printf("Cannot open file\n");
    }
    for(i=0;i<7;i++){
        do{
            flag=1;
            random=rand()%50+1; // Returns random integer in range of [1-50]
            for(j=0;j<i && flag==1;j++){
                if(randomNumbers[j]==random){
                    flag=0;
                }
            }
        }while(!flag);
        randomNumbers[i]=random;
    }
    for(i=0;i<7;i++){
        printf("%d ",randomNumbers[i]);
    }
    printf("\nRandom 7 words\n");
    while(!feof(read)){
        for(i=0;i<50;i++){
            fscanf(read,"%s",words[i]);
            counter++;
            for(j=0;j<7;j++){
                if(counter==randomNumbers[j]){
                    strcpy(randoms[j],words[i]);
                }
            }
        }
    }
    fclose(read);
    for(i=0;i<7;i++){
        printf("%s\n",randoms[i]);
    }
} // end of read file

void fillPuzzle(char puzzle[15][15], char randoms[][10], int n){
    int j,r,c,flag;
    int direction;
    direction=rand()%8+1; // Return random integer in range of [1-8]
    if(direction==1){ // Word is towards south
        do{
            flag=1;
            r=rand()%11;
            c=rand()%15;
            if(r+strlen(randoms[n])<15){
                for(j=0;j<strlen(randoms[n]);j++){
                    if(puzzle[r+j][c]!='-'){
                        flag=1;
                        break;
                    }
                    else{
                        flag=0;
                        puzzle[r+j][c]=randoms[n][j];
                    }
                }
            }
            else{
                flag=1;
            }
        }while(flag);
        printf("r:%d,c:%d,direction:%d,word:%s\n",r,c,direction,randoms[n]);
    }
    if(direction==2){ // Word is towards north
        do{
            flag=1;
            r=rand()%11+4;
            c=rand()%15;
            if(r-strlen(randoms[n])>=0){
                for(j=0;j<strlen(randoms[n]);j++){
                    if(puzzle[r-j][c]!='-'){
                        flag=1;
                        break;
                    }
                    else{
                        flag=0;
                        puzzle[r-j][c]=randoms[n][j];
                    }
                }
            }
            else{
                flag=1;
            }
        }while(flag);
        printf("r:%d,c:%d,direction:%d,word:%s\n",r,c,direction,randoms[n]);
    }
    if(direction==3){ // Word is towards east
        do{
            flag=1;
            r=rand()%15;
            c=rand()%11;
            if(c+strlen(randoms[n])<15){
                for(j=0;j<strlen(randoms[n]);j++){
                    if(puzzle[r][c+j]!='-'){
                        flag=1;
                        break;
                    }
                    else{
                        flag=0;
                        puzzle[r][c+j]=randoms[n][j];
                    }
                }
            }
            else{
                flag=1;
            }
        }while(flag);
        printf("r:%d,c:%d,direction:%d,word:%s\n",r,c,direction,randoms[n]);
    }
    if(direction==4){ // Word is towards west
        do{
            flag=1;
            r=rand()%15;
            c=rand()%11+4;
            if(c-strlen(randoms[n])>=0){
                for(j=0;j<strlen(randoms[n]);j++){
                    if(puzzle[r][c-j]!='-'){
                        flag=1;
                        break;
                    }
                    else{
                        flag=0;
                        puzzle[r][c-j]=randoms[n][j];
                    }
                }
            }
            else{
                flag=1;
            }
        }while(flag);
        printf("r:%d,c:%d,direction:%d,word:%s\n",r,c,direction,randoms[n]);
    }
    if(direction==5){ // Word is towards north-east
        do{
            flag=1;
            r=rand()%11+4;
            c=rand()%11;
            if(r-strlen(randoms[n])>=0 && c+strlen(randoms[n])<15){
                for(j=0;j<strlen(randoms[n]);j++){
                    if(puzzle[r-j][c+j]!='-'){
                        flag=1;
                        break;
                    }
                    else{
                        flag=0;
                        puzzle[r-j][c+j]=randoms[n][j];
                    }
                }
            }
            else{
                flag=1;
            }
        }while(flag);
        printf("r:%d,c:%d,direction:%d,word:%s\n",r,c,direction,randoms[n]);
    }
    if(direction==6){ // Word is towards south-west
        do{
            flag=1;
            r=rand()%11;
            c=rand()%11+4;
            if(r+strlen(randoms[n])<15 && c-strlen(randoms[n])>=0){
                for(j=0;j<strlen(randoms[n]);j++){
                    if(puzzle[r+j][c-j]!='-'){
                        flag=1;
                        break;
                    }
                    else{
                        flag=0;
                        puzzle[r+j][c-j]=randoms[n][j];
                    }
                }
            }
            else{
                flag=1;
            }
        }while(flag);
        printf("r:%d,c:%d,direction:%d,word:%s\n",r,c,direction,randoms[n]);
    }
    if(direction==7){ // Word is towards north-west
        do{
            flag=1;
            r=rand()%11+4;
            c=rand()%11+4;
            if(r-strlen(randoms[n])>=0 && c-strlen(randoms[n])>=0){
                for(j=0;j<strlen(randoms[n]);j++){
                    if(puzzle[r-j][c-j]!='-'){
                        flag=1;
                        break;
                    }
                    else{
                        flag=0;
                        puzzle[r-j][c-j]=randoms[n][j];
                    }
                }
            }
            else{
                flag=1;
            }
        }while(flag);
        printf("r:%d,c:%d,direction:%d,word:%s\n",r,c,direction,randoms[n]);
    }
    if(direction==8){ // Word is towards south-east
        do{
            flag=1;
            r=rand()%11;
            c=rand()%11;
            if(r+strlen(randoms[n])<15 && c+strlen(randoms[n])<15){
                for(j=0;j<strlen(randoms[n]);j++){
                    if(puzzle[r+j][c+j]!='-'){
                        flag=1;
                        break;
                    }
                    else{
                        flag=0;
                        puzzle[r+j][c+j]=randoms[n][j];
                    }
                }
            }
            else{
                flag=1;
            }
        }while(flag);
        printf("r:%d,c:%d,direction:%d,word:%s\n",r,c,direction,randoms[n]);
    }
} // end filling the puzzle with the words


// This function opens up a 15x15 puzzle map with '-' characters
void emptyPuzzle(char puzzle[15][15]){
    int r,c;
    for(r=0;r<15;r++){
        for(c=0;c<15;c++){
            puzzle[r][c]='-';
        }
    }
} // end emptying the puzzle


void printPuzzle(char puzzle[15][15]){
    int r,c;
    for(r=0;r<15;r++){
        for(c=0;c<15;c++){
            printf("%c ",puzzle[r][c]);
        }
        printf("\n");
    }
} // end printing the puzzle

void randomCharacters(char puzzle[15][15]){
    int r,c;
    for(r=0;r<15;r++){
        for(c=0;c<15;c++){
            if(puzzle[r][c]=='-'){
                puzzle[r][c]=rand()%26+97;
            }
        }
    }
} // end random characters

/* This function returns the direction of the word if the given word is found in the puzzle,
*  also it return 0 if the entered word cannot be found in the puzzle table
*/
int searchWord(int row, int column, char word[5], char puzzle[15][15], int length){
    int direction,k,flag;
    for(direction=1;direction<9;direction++){
        flag=1;
        if(direction==1){ // Checking towards south
                for(k=0;k<length;k++){
                    if(puzzle[row+k][column]!=word[k]){
                        flag=0;
                        break;
                    }
                }
                if(flag==1){
                    return 1;
                }
        }
        else if(direction==2){ // Checking towards north
                for(k=0;k<length;k++){
                    if(puzzle[row-k][column]!=word[k]){
                        flag=0;
                        break;
                    }
                }
                if(flag==1){
                    return 2;
                }
        }
        else if(direction==3){ // Checking towards east
            for(k=0;k<length;k++){
                if(puzzle[row][column+k]!=word[k]){
                    flag=0;
                    break;
                }
            }
            if(flag==1){
                return 3;
            }
        }
        else if(direction==4){ // Checking towards west
            for(k=0;k<length;k++){
                if(puzzle[row][column-k]!=word[k]){
                    flag=0;
                    break;
                }
            }
            if(flag==1){
                return 4;
            }
        }
        else if(direction==5){ // Checking towards north-east
            for(k=0;k<length;k++){
                if(puzzle[row-k][column+k]!=word[k]){
                    flag=0;
                    break;
                }
            }
            if(flag==1){
                return 5;
            }
        }
        else if(direction==6){ // Checking towards south-west
            for(k=0;k<length;k++){
                if(puzzle[row+k][column-k]!=word[k]){
                    flag=0;
                    break;
                }
            }
            if(flag==1){
                return 6;
            }
        }
        else if(direction==7){ // Checking towards north-west
            for(k=0;k<length;k++){
                if(puzzle[row-k][column-k]!=word[k]){
                    flag=0;
                    break;
                }
            }
            if(flag==1){
                return 7;
            }
        }
        else if(direction==8){ // Checking towards south-east
            for(k=0;k<length;k++){
                if(puzzle[row+k][column+k]!=word[k]){
                    flag=0;
                    break;
                }
            }
            if(flag==1){
                return 8;
            }
        }
    }
    return 0;
} // end search word


// This function prints X to the words if the word is found on the list and puzzle

void printX(int row,int column,char puzzle[15][15], int direction,int length){
    int r,c,k;
    switch(direction){
        case 1:
            for(k=0;k<length;k++){
                puzzle[row+k][column]='X';
            }
            break;
        case 2:
            for(k=0;k<length;k++){
                puzzle[row-k][column]='X';
            }
            break;
        case 3:
            for(k=0;k<length;k++){
                puzzle[row][column+k]='X';
            }
            break;
        case 4:
            for(k=0;k<length;k++){
                puzzle[row][column-k]='X';
            }
            break;
        case 5:
            for(k=0;k<length;k++){
                puzzle[row-k][column+k]='X';
            }
            break;
        case 6:
            for(k=0;k<length;k++){
                puzzle[row+k][column-k]='X';
            }
            break;
        case 7:
            for(k=0;k<length;k++){
                puzzle[row-k][column-k]='X';
            }
            break;
        case 8:
            for(k=0;k<length;k++){
                puzzle[row+k][column+k]='X';
            }
            break;
    }
    for(r=0;r<15;r++){
        for(c=0;c<15;c++){
            printf("%c ",puzzle[r][c]);
        }
        printf("\n");
    }
} // end printing X   

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

char portName[]="/dev/ttyUSB0";
int squareOfNumber(int number, FILE*ptr);
int buttonCount(FILE*arduino);
int data,number,check=1;
void button(FILE*arduino){
	int buttonCount;
	freopen(portName,"w+",arduino);
	fscanf(arduino,"%d",buttonCount);
	printf("Button has been pressed %d times.\n",buttonCount);
	
}
int main(){
FILE*arduino=fopen(portName,"w");
while(check==1){
	printf("%s","### WELCOME TO GTU ARDUINO LAB        ###\n");
	printf("%s","### STUDENT NAME: BURAK DEMİRKAYA     ###\n");
	printf("%s","### PLEASE SELECT FROM THE FOLLOWING  ###\n");
	printf("%s","### MENU:                             ###\n");
	printf("%s","(1) TURN ON LED ON ARDUINO\n");
	printf("%s","(2) TURN OFF LED ON ARDUINO\n");
	printf("%s","(3) FLASH ARDUINO LED 3 TIMES\n");
	printf("%s","(4) SEND A NUMBER TO ARDUINO TO COMPUTE SQUARE BY ARDUINO\n");
	printf("%s","(5) BUTTON PRESS COUNTER\n");
	printf("%s","(0) EXIT\n");
	
	printf("Choose one from the menu: ");
	scanf("%d",&data);
	if(data==1){
	fprintf(arduino,"%d",data);
	printf("Led is on.\n");
	}
	else if(data==2){
	fprintf(arduino,"%d",data);
	printf("Led is off.\n");
	}
	else if(data==3){
	fprintf(arduino,"%d",data);
	printf("Flashing led 3 times.\n");
	}
	else if(data==4){
	fprintf(arduino,"%d",data);
	printf("Enter a number: ");
	scanf("%d",&number);
	squareOfNumber(number,arduino);
	}
	else if(data==5){
	fprintf(arduino,"%d",data);
	printf("Measure the button press counter. \n");
	button(arduino);
	}
	else if(data==0){
	check=0;
	printf("Exiting...\n");
	}
	freopen(portName,"w+",arduino);

}
return 0;


}

int squareOfNumber(int number,FILE*arduino){
	int square = number*number;
	fprintf(arduino,"%d",square);
	printf("The square of entered value is %d and the led is on.\n",square); 
}






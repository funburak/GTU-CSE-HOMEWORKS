#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.14

int select_shape();
int select_calc();
int calculate(int select_shape(), int select_calc());
int calc_triangle(int select_calc());
int calc_quadrilateral(int select_calc());
int calc_circle(int select_calc());
int calc_pyramid(int select_calc());
int calc_cylinder(int select_calc());

enum Shapes {Triangle=1, Quadrilateral, Circle, Pyramid, Cylinder};
enum Calculators{Area=1, Perimeter, Volume};


int main(){
    int result=1;
    while(result){ // program continues until the user enters '0'
    result=calculate(select_shape,select_calc);
    	if(result==0){
    	break;
   	}
    }
    return 0;
} // end main

int select_shape(){
    int c,check=0;
    enum Shapes shape;
    do{
        printf("Welcome to the geometric calculator!\n");
        printf("Select a shape to calculate:\n");
        printf("-----------------------------\n");
        printf("1. Triangle\n");
        printf("2. Quadrilateral\n");
        printf("3. Circle\n");
        printf("4. Pyramid\n");
        printf("5. Cylinder\n");
        printf("0. Exit\n");
        printf("------------------------------\n");
        printf("Input: ");
        check=scanf("%u",&shape);
        if(check==1){
        return shape;
        }
        else{
        printf("Error! Please enter a valid entry.\n");
        while(c=getchar()!='\n' && c!=EOF){
        fflush(stdin); // delete the character 
        }
        } 
    }while(shape!=0 || !check);
    
} // end selecting the shape

int select_calc(){
    int check2=0;
    enum Calculators calc;
    do{
        printf("Select calculator:\n");
        printf("------------------------\n");
        printf("1. Area\n");
        printf("2. Perimeter\n");
        printf("3. Volume\n");
        printf("0. Exit\n");
        printf("------------------------\n");
        printf("Input: ");
        check2=scanf("%u",&calc);
        if(calc==0){
        printf("Exiting...\n");
        }
        if(check2==1){
        return calc;
        }
        else{
        while(getchar()!='\n'){
        fflush(stdin); // delete the character 
        }
        }
    }while(calc!=0 || !check2);   
} // end selecting calculation 

int calculate(int select_shape(), int select_calc()){
    int tri,quad,circle,pyramid,cylinder;
    switch(select_shape()){
        case Triangle:
            tri=calc_triangle(select_calc);
            return tri;
            break;

        case Quadrilateral:
            quad=calc_quadrilateral(select_calc);
            return quad;
            break;
        
        case Circle:
            circle=calc_circle(select_calc);
            return circle;
            break;
        
        case Pyramid:
            pyramid=calc_pyramid(select_calc);
            return pyramid;
            break;
        
        case Cylinder: 
            cylinder=calc_cylinder(select_calc);
            return cylinder;
            break;
        
        case 0:
            printf("Exiting...\n");
            return 0;
            break;
    }
} // end calculate

int calc_triangle(int select_calc()){
    int flag,flag2,flag3,check=0;
    float a,b,c;
    float s,area,perimeter;
    switch(select_calc()){
        case Area:
        printf("Please enter the three sides of a Triangle: \n");
    do{
        flag=scanf("%f",&a);
        if(flag==1){
            flag2=scanf("%f",&b);
                if(flag2==1){
                    flag3=scanf("%f",&c);
                    if(flag3==1){
                        if(a<0 || b<0 || c<0){
                            printf("Please enter a valid triangle.\n");
                            getc(stdin);
                            flag=0;
                        }
                        else{
                            s=(a+b+c)/2;
                            if(s>a && s>b && s>c){
                            area=sqrt(s*(s-a)*(s-b)*(s-c));
                            printf("Area of TRIANGLE: %.2f\n",area);
                            check=1; // If the calculation done successfully
                            }
                        else{
                            printf("ERROR! Please enter a valid triangle.\n");
                            getc(stdin);
                            flag=0;
                        }
                        }
                    }
                    else{
                        printf("ERROR! Please enter a valid entry.\n");
                        getc(stdin);
                        flag=0;
                    }
                }
                else{
                    getc(stdin);
                    flag2=0;
                    printf("ERROR! Please enter a valid entry.\n");
                }
        }
        else if(flag==0){
            getc(stdin);
            printf("ERROR! Please enter a valid entry.\n");
        }
    }while(!flag || !flag2 || !flag3); //continue until all of them is valid
        return check;
            break;

        case Perimeter:
        printf("Please enter the three sides of a Triangle: \n");
    do{
        flag=scanf("%f",&a);
        if(flag==1){
            flag2=scanf("%f",&b);
                if(flag2==1){
                    flag3=scanf("%f",&c);
                    if(flag3==1){
                        if(a<0 || b<0 || c<0){
                            printf("ERROR! Please enter a valid triangle.\n");
                            getc(stdin);
                            flag=0;
                        }
                        else{
                            s=(a+b+c)/2.0;
                            if(s>a && s>b && s>c){
                            perimeter=a+b+c;
                            printf("Perimeter of TRIANGLE: %.2f\n",perimeter);
                            check=1;           
                            }
                        else{
                            printf("ERROR! Please enter a valid triangle.\n");
                            getc(stdin);
                            flag=0;
                        }
                        }
                    }
                    else{
                        getc(stdin);
                        flag3=0;
                        printf("ERROR! Please enter a valid entry.\n");
                    }
                }
                else{
                    printf("ERROR! Please enter a valid entry.\n");
                    getc(stdin);
                    flag2=0;
                }
        }
        else if(flag==0){
            printf("ERROR! Please enter a valid entry.\n");
            getc(stdin);
        }
    }while(!flag || !flag2 || !flag3); //continue until all of them is valid
        return check;
            break;

        case Volume:
            printf("You cannot calculate the volume of a triangle.\n");
            check=1;
            return check;
            break;

        case 0:
        	check=0;
        	return check;
        	break;
        
        default:   
        	return check;
            break;


    }
} // end triangle calculations

int calc_quadrilateral(int select_calc()){
    int flag,flag2,flag3,flag4,check2=0;
    float a,b,c,d;
    float s,area,perimeter;
    switch(select_calc()){
        case Area:
        printf("Please enter the four sides of a Quadrilateral: \n");
    do{
        flag=scanf("%f",&a);
        if(flag==1){
            flag2=scanf("%f",&b);
                if(flag2==1){
                    flag3=scanf("%f",&c);
                    if(flag3==1){
                            flag4=scanf("%f",&d);
                                if(flag4==1){
                        if(a<0 || b<0 || c<0 || d<0){
                            printf("ERROR! Please enter a valid quadrilateral.\n");
                            getc(stdin);
                        }
                        else{
                            s=(a+b+c+d)/2.0;
                            area=sqrt((s-a)*(s-b)*(s-c)*(s-d));
                            printf("Area of QUADRILATERAL: %.2f\n",area);
                            check2=1;
                        }
                      	 }else{
                            	printf("ERROR! Please enter a valid quadrilateral.\n");
                            	getc(stdin);
                            	flag=0;
                        	}
                        }else{
                                    printf("ERROR! Please enter a valid entry.\n");
                                    getc(stdin);
                        }
                    }else{
                        getc(stdin);
                        flag=0;
                        printf("ERROR! Please enter a valid entry.\n");
                    }
        }else if(flag==0){
            getc(stdin);
            printf("ERROR! Please enter a valid entry.\n");
        }
    }while(!flag || !flag2 || !flag3 || !flag4); //continue until all of them is valid
        return check2;
        break;

        case Perimeter:
        printf("Please enter the four sides of a Quadrilateral: \n");
    do{
        flag=scanf("%f",&a);
        if(flag==1){
            flag2=scanf("%f",&b);
                if(flag2==1){
                    flag3=scanf("%f",&c);
                    if(flag3==1){
                            flag4=scanf("%f",&d);
                                if(flag4==1){
                        if(a<0 || b<0 || c<0 || d<0){
                            printf("ERROR! Please enter a valid quadrilateral.\n");
                            getc(stdin);
                            flag=0;
                        }
                        else{
                            perimeter=a+b+c+d;
                            printf("Perimeter of QUADRILATERAL: %.2f\n",perimeter);
                            check2=1;
                        }
                        }else{
                            printf("ERROR! Please enter a valid entry.\n");
                            getc(stdin);
                            flag=0;
                        }
                        }       
                        else{
                                    printf("ERROR! Please enter a valid entry.\n");
                                    getc(stdin);
                                    flag=0;
                                }
                    }else{
                        getc(stdin);
                        flag=0;
                        printf("ERROR! Please enter a valid entry.\n");
                    }
        }else if(flag==0){
            getc(stdin);
            printf("ERROR! Please enter a valid entry.\n");
        }
    }while(!flag || !flag2 || !flag3 || !flag4); //continue until all of them is valid
        return check2;
        break;

        case Volume:
            printf("You cannot calculate the volume of a quadrilateral.\n");
            break;

    }
} // end quadrilateral calculations

int calc_circle(int select_calc()){
    int flag,check3=0;
    float r,area,perimeter;
    switch(select_calc()){
        case Area:
        printf("Please enter the radius of a circle: ");
        do{
            flag=scanf("%f",&r);
                if(r<0){
                    flag=0;
                }
                if(flag==1){
                    area=PI*r*r;
                    printf("Area of Circle: %.2f\n",area);
                    check3=1;
                }
                else if(flag==0){
                    printf("ERROR! Please enter a valid entry.\n");
                    getc(stdin);
                }
        }while(!flag); //continue until it is valid
            return check3;
            break;

        case Perimeter:
            printf("Please enter the radius of a circle: ");
        do{
            flag=scanf("%f",&r);
                if(r<0){
                    flag=0;
                }
                if(flag==1){
                    perimeter=2*PI*r;
                    printf("Perimeter of Circle: %.2f\n",perimeter);
                    check3=1;
                }
                else if(flag==0){
                    printf("ERROR! Please enter a valid entry.\n");
                    getc(stdin);
                }
        }while(!flag); //continue until it is valid
            return check3;
            break;

        case Volume:
            printf("ERROR! You cannot calculate the volume of a circle. Please try again.\n");
            break;
            
    }
} // end circle calculations

int calc_pyramid(int select_calc()){
    int flag,flag2,check4=0;
    float a,h;
    float base_area, lateral_area, surface_area,volume,base_perimeter;
    switch(select_calc()){
        case Area:
            printf("Please enter the base side and height of a pyramid: ");
           do{
               flag=scanf("%f",&a);
                    if(flag==1){
                        flag2=scanf("%f",&h);
                            if(flag2==1){
                                if(a<0 || h<0){
                                    printf("ERROR! Please enter a valid entry.\n");
                                    getc(stdin);
                                    flag=0;
                                }
                                else{
                                base_area=a*a;
                                printf("Base Surface Area of a PYRAMID: %.2f\n",base_area);
                                lateral_area=2*a*h;
                                printf("Lateral Surface Area of a PYRAMID: %.2f\n",lateral_area);
                                surface_area=base_area + lateral_area;
                                printf("Surface Area of a PYRAMID: %.2f\n",surface_area);
                                check4=1;
                                }
                            }
                            else{
                                printf("ERROR! Please enter a valid entry.\n");
                                getc(stdin);
                            }
                    }
                    else{
                        printf("ERROR! Please enter a valid entry.\n");
                        getc(stdin);
                    }
           }while(!flag || !flag2); //continue until all of them is valid
           return check4;
           break;

        case Perimeter:
            printf("Please enter the base side and height of a pyramid: ");
           do{
               flag=scanf("%f",&a);
                    if(flag==1){
                        flag2=scanf("%f",&h);
                            if(flag2==1){
                                if(a<0 || h<0){
                                    printf("ERROR! Please enter a valid entry.\n");
                                    getc(stdin);
                                    flag=0;
                                }
                                else{
                                base_perimeter=4*a;
                                printf("Base Surface Perimeter of a PYRAMID: %.2f\n",base_perimeter);
                                check4=1;
                            }
                            }
                            else{
                                printf("ERROR! Please enter a valid entry.\n");
                                getc(stdin);
                            }
                    }
                    else{
                        printf("ERROR! Please enter a valid entry.\n");
                        getc(stdin);
                    }
           }while(!flag || !flag2); //continue until all of them is valid
           return check4;
           break;

        case Volume:
           printf("Please enter the base side and height of a pyramid: ");
           do{
               flag=scanf("%f",&a);
                    if(flag==1){
                        flag2=scanf("%f",&h);
                            if(flag2==1){
                                volume=(a*a*h)/3.0;
                                printf("Volume of PYRAMID: %.2f\n",volume);
                                check4=1;
                            }
                            else{
                                printf("ERROR! Please enter a valid entry.\n");
                                getc(stdin);
                            }
                    }
                    else{
                        printf("ERROR! Please enter a valid entry.\n");
                        getc(stdin);
                    }
           }while(!flag || !flag2); //continue until all of them is valid
           return check4;
           break;
    }
} // end pyramid calculations

int calc_cylinder(int select_calc()){
    int flag,flag2,check5=0;
    float r,h;
    float base_area, lateral_area, surface_area,volume,base_perimeter;
    switch(select_calc()){
        case Area:
             printf("Please enter the radius and height of a cylinder: ");
           do{
               flag=scanf("%f",&r);
                    if(flag==1){
                        flag2=scanf("%f",&h);
                            if(flag2==1){
                                if(r<0 || h<0){
                                    printf("ERROR! Please enter a valid entry.\n");
                                    getc(stdin);
                                    flag=0;
                                }
                                else{
                                base_area=PI*r*r;
                                printf("Base Surface Area of a CYLINDER: %.2f\n",base_area);
                                lateral_area=2*PI*r*h;
                                printf("Lateral Surface Area of a CYLINDER: %.2f\n",lateral_area);
                                surface_area=2*PI*r*(r+h);
                                printf("Surface Area of a CYLINDER: %.2f\n",surface_area);
                                check5=1;
                                }
                            }
                            else{
                                printf("ERROR! Please enter a valid entry.\n");
                                getc(stdin);
                            }
                    }
                    else{
                        printf("ERROR! Please enter a valid entry.\n");
                        getc(stdin);
                    }
           }while(!flag || !flag2); //continue until all of them is valid
           return check5;
           break;

        case Perimeter:
             printf("Please enter the radius and height of a cylinder: ");
           do{
               flag=scanf("%f",&r);
                    if(flag==1){
                        flag2=scanf("%f",&h);
                            if(flag2==1){
                                if(r<0 || h<0){
                                    printf("ERROR! Please enter a valid entry.\n");
                                    getc(stdin); 
                                    flag=0;
                                }
                                else{
                                base_perimeter=2*PI*r;
                                printf("Base Surface Perimeter of a CYLINDER: %.2f\n",base_perimeter);
                                check5=1;
                            }
                            }
                            else{
                                printf("ERROR! Please enter a valid entry.\n");
                                getc(stdin);
                            }
                    }
                    else{
                        printf("ERROR! Please enter a valid entry.\n");
                        getc(stdin);
                    }
           }while(!flag || !flag2); //continue until all of them is valid
           return check5;
           break;

        case Volume:
            printf("Please enter the radius and height of a cylinder: ");
           do{
               flag=scanf("%f",&r);
                    if(flag==1){
                        flag2=scanf("%f",&h);
                            if(flag2==1){
                                if(r<0 || h<0){
                                    printf("ERROR! Please enter a valid entry.\n");
                                    getc(stdin);
                                    flag=0;
                                }
                                else{
                                volume=PI*r*r*h;
                                printf("Volume of CYLINDER: %.2f\n",volume);
                                check5=1;
                                }
                            }
                            else{
                                printf("ERROR! Please enter a valid entry.\n");
                                getc(stdin);
                            }
                    }
                    else{
                        printf("ERROR! Please enter a valid entry.\n");
                        getc(stdin);
                    }
           }while(!flag || !flag2); //continue until all of them is valid
           return check5;
           break;
    }
} // end cylinder calculations

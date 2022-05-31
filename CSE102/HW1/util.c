#include <stdio.h>
#include <math.h>  /* for sqrt function */
#include "util.h"

/* Example decision tree - see the HW2 description */
int dt0(int t, double p, double h, char s, int w) {
    int r = 0;
    if (t>35 && w!=3) r = 1;
    else if (t<=35 && s==0) r = 1;
    return r;
}

char dt1a(double PL, double PW, double SL, double SW){
	if(PL<2.45){
	return 'S'; /* Setosa*/
	}
	else{
		if(PW<1.75){
			if(PL<4.95){
				if(PW<1.65){
					return 'c'; /* Versicolor */
					}
					else{
						return 'V'; /*Virginica */
					}
				}
				else{
					return 'V'; /* Virginica*/
				}
			}
			else{
				return 'V'; /* Virginica */
			}	
		
}
} /*end dt1a */
char dt1b(double PL, double PW, double SL, double SW){
	if(PL<2.55){
		return 'S'; /* Setosa */
	}
		else{
			if(PW<1.69){
				if(PL<4.85){
					return 'c'; /* Versicolor*/
				}
				else{
					return 'V'; /* Virginica */
				}
			}
			else{
				return 'V'; /* Virginica */
			}
		}
} /* end dt1b */

double dt2a(double x1, double x2, double x3, int x4, int x5){
	if(x1<31.5){
		if(x2>-2.5){
			return 5.0;
		}
		else{
			if((x2-0.1<=x1) && (x1<=x2+0.1)){
				return 2.1;
			}
			else{
				return -1.1;
			}
		}
	
	}
	else{ 	/* If x1 is not less than 31.5 */
		if((-1<=x3) && (x3<=2)){
			return 1.4;
		}
		else{
			if(x4 & x5){
				return -2.23;
			}
			else{
				return 11.0;
			}
		}
	}
} /* end dt2a */ 

double dt2b(double x1, double x2, double x3, int x4, int x5){
	if((12<x1) && (x1<22)){
		if(x3>(5.0/3.0)){
			return -2.0;
		}
		else{
			if((x1-0.1<=x3) && (x3<=x1+0.1)){
				return 1.01;
			}
			else{
				return -8;
			}
		}
	}
	else{ 	/* If x1 is not between 12 and 22 */
		if(x4 & x5){
			return -1;
		}
		else{
			if((-1<=x2) && (x2<=2)){
				return (-1.0/7.0);
			}
			else{
				return sqrt(2)/3;
			}
		}
	}
} /* end dt2b */

int dt3a(double agno, double grade, int year, int semester, int month){   /* Erasmus apply decision tree */
	if(grade>=70.0){
		if((year>=2) && (year<=4)){ /* If the student isn't a first-grader */
			if(semester==1){ /* If it is spring semester */
				if(agno>=3.00){
					if((month>=5) && (month<=12)){ /* If the months are from May till December */
						return 1;
					} else return 0;
				} else return 0;
			} else return 0;
		}
		else if(year==1){ /* If the student is first-grader */
			return 2;
		}
		else{
			return 0;
		}
	} else return 0;
 /* 0=cannot apply for Erasmus
    1=can apply for Erasmus
    2=try again next year */
    
}   /* end Erasmus apply */

int dt3b(double agno, double grade, int year, int semester, int month){   /* Erasmus donation decision tree */
	if((grade>80.0) && (grade<90.0)){
		if((year==2) || (year==3)){   /* If the student is 2nd or 3th class student */
			if(semester==1){   /* If it is spring semester */
				if(agno>=3.50){
					if((month>=5) && (month<=8)){   /* If the months are between May and August */
						return 1;
					}
					else{
						return 2;
					}
				} else if((agno>=3.00) && (agno<3.50)){
					return 3;
				} else return 0;
			} else return 0;
		} else return 0;
	} else return 0; 
 /* 0=no donation
    1=500€ donation per month
    2=250€ donation per month
    3=150€ donation per month */
  
}   /* end Erasmus donation */
 





/* Provide your implementations for all the requested functions here */

/*
   CENG 231 Assignment 4 Part 2
   Pi
   author: Jaccob Mau
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*function to find if in semi-circles*/
int inOut(float x, float y, float r){
        /*Variables*/
        int inout=0;
        float distance1, distance2, rad2;

        /*Calculations*/
        rad2=r*r;;
        distance1=((x-0)*(x-0))+((y-r)*(y-r));
        distance2=(((2*r)-x)*((2*r)-x))+((y-r)*(y-r));

        /*If in or out of circle*/
        if((rad2>distance1)&&(rad2>distance2)){
            inout=1;
        }
        else if((rad2<=distance1)&&(rad2<=distance2)){
            inout=0;
        }
	else{
	    inout=1;
	}

        return inout; 
}

int main(){
    /* initialize the random number generator with the current time */
    srand((unsigned) time(NULL));
    /*Variables*/
    int numPoint, inCount, outCount, i, check, count;
    float radius, radius2, x, y, pi;
    inCount=0;
    outCount=0;
    count=1;

    /*User Inputs*/
    printf("\nEnter the radius of circle:  ");
    scanf("%f",&radius);
    printf("\nEnter the number of points:  ");
    scanf("%d",&numPoint);
    
    radius2=2.0*radius;

    /*For loop to output all points*/
    for(i=0; i<numPoint; ++i){
        /*Random point generator*/
        x = ((float)rand()/ (float)RAND_MAX)*radius2;
        y = ((float)rand()/ (float)RAND_MAX)*radius2;

        /*Check if in or out*/
        check=inOut(x,y,radius);

        /*Output the necessary response*/
        if(check==1){
            printf("\nPoint No.%d(x=%.6f,y=%.6f):\tIN",count,x,y);
            inCount+=1;
        }
        else{
            printf("\nPoint No.%d(x=%.6f,y=%.6f):\tOUT",count,x,y);
            outCount+=1;
        }
        count+=1;
    }

    /*Calculate the pi value*/
    pi=4*(float)inCount/(float)numPoint;

    /*Output Summary*/
    printf("\n\n/******In Summary******/");
    printf("\nPoints within circle areas:\t%d",inCount);
    printf("\nPoints out of circle areas:\t%d",outCount);
    printf("\nPi=\t%.6f\n",pi);




    return 0;
}

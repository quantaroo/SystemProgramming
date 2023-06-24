/*
   CENG 231 Assignment 5
   Rational
   author: Jaccob Mau
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int currNum;
int currDen;
int newNum;
int newDen;

/* Find the greatest common divisor of two numbers */
int gcd(int a, int b) {
    if (b == 0) {
        return a;
    } else {
        return gcd(b, a % b);
    }
}

/* Input a new rational number */
void inputRational(){
    printf("\nPlease input a rational number.");
    printf("\nNumberator: ");
    scanf("%d", &newNum);
    printf("\nDenominator: ");
    scanf("%d", &newDen);
}
/* Print the current rational number */
void printRational(){
    if(currDen<0&&currNum<0){
      currDen=-1*currDen;
      currNum=-1*currNum;
    }
    if(currDen<0&&currNum>0){
      currDen=-1*currDen;
      currNum=-1*currNum;
    }
    if(currNum==0){
        printf("%d",currNum);
    }
    else if(currDen==1){
        printf("%d",currNum);
    }
    else{
        printf("%d/%d",currNum,currDen);
    }
}
/* Express the current rational number in its reduced format */
void reducedFormat(){
    int redNum;
    redNum=gcd(currNum,currDen);
    if(redNum<0){
      redNum=-1*redNum;
    }
    currNum = currNum/redNum;
    currDen = currDen/redNum;
    
}
/* Add two rational numbers */
void addRational(int num3, int num4){
    currNum=((currNum*num4)+(num3*currDen));
    currDen=currDen*num4;
    reducedFormat();
}
/* Subtract two rational numbers */
void subRational(int num5, int num6){
    currNum=(currNum*num6)-(num5*currDen);
    currDen=currDen*num6;
    reducedFormat();
}
/* Multiply two rational numbers */
void mulRational(int num7, int num8){
    currNum=currNum*num7;
    currDen=currDen*num8;
    reducedFormat();
}
/* Divide two rational numbers */
void divRational(int num9, int num10){
    if(num9==0){
      printf("\nERROR: Division by zero!");
      printf("\nTry again...");
    }
    else{
      mulRational(num10,num9);
    }
    
}
/* Calculate the reciprocal of a rational number */
void reciprocal(){
    newNum=currNum;
    newDen=currDen;
    currNum=newDen;
    currDen=newNum;
    reducedFormat();
}

int main(){
    int exit=0;
    int intro=0;
    int choice;
    printf("\nWelcome to my positive rational number calculator!");
    while(intro!=1){
      inputRational();
      if(newNum!=0){
	intro=1;
      }
      else{
	printf("\nERROR: Division by zero!");
        printf("\nTry again...");
      }
    }
    currDen=newDen;
    currNum=newNum;
    while(exit!=1){
        printf("\n------------------------------------------");
        printf("\nThe current result is: ");
        printRational();
        printf("\n1. Subtract a rational number from the current result;");
        printf("\n2. Add a rational number to the current result;");
        printf("\n3. Multiply the currecnt result by a rational number;");
        printf("\n4. Divide the current result by a rational number;");
        printf("\n5. Take the reciprocal of the current result;");
        printf("\n6. Quit");
        printf("\n\nPlease enter a selection:");
        scanf("%d",&choice);

        if(choice==1){
            inputRational();
	    if(newDen!=0){
	      subRational(newNum,newDen);
	    }
	    else{
	      printf("\nERROR: Division by zero!");
	      printf("\nTry again...");
	    }
        }
        else if(choice==2){
            inputRational();
	    if(newDen!=0){
	      addRational(newNum,newDen);
	    }
	    else{
	      printf("\nERROR: Division by zero!");
	      printf("\nTry again...");
	    }
        }
        else if(choice==3){
            inputRational();
	    if(newDen!=0){
	      mulRational(newNum,newDen);
	    }
	    else{
	      printf("\nERROR: Division by zero!");
	      printf("\nTry again...");
	    }
        }
        else if(choice==4){
	    inputRational();
	    if(newDen!=0){
	      divRational(newNum,newDen);
	    }
	    else{
	      printf("\nERROR: Division by zero!");
	      printf("\nTry again...");
	    }
        }
        else if(choice==5){
            reciprocal();
        }
        else{
            exit =1;
        }

    }
    return 0;
}

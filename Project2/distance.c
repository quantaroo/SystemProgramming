/* HW2 distance.c:             */
/*                             */
/* author: Jaccob Mau          */
/*                             */
/* modifications:              */
/* 23FEB2021  initial version  */

#include <stdio.h>
/* main function */
int main(void){
  /*State variables*/
  int m1, y1, f1, i1, m2, y2, f2, i2, mt, yt, ft, itot;

  /*Input Distance 1*/
  printf("\nPlease enter two distance values m1, y1, f1, i1, m2, y2, f2, and i2.");
  
  printf("\ni1: ");
  scanf("%d",&i1);
  printf("f1: ");
  scanf("%d",&f1);
  printf("y1: ");
  scanf("%d",&y1);
  printf("m1: ");
  scanf("%d",&m1);
  
  /*Calculate Distance 1*/
  f1=f1+(i1/12);
  i1=(i1%12);
  y1=y1+(f1/3);
  f1=(f1%3);
  m1=m1+(y1/1760);
  y1=(y1%1760);

  /*Output Distance 1*/
  printf("Distance 1 is %d miles, %d yards, %d feet, %d inches.", m1, y1, f1, i1);

  /*Input Distance 2*/
  printf("\ni2: ");
  scanf("%d",&i2);
  printf("f2: ");
  scanf("%d",&f2);
  printf("y2: ");
  scanf("%d",&y2);
  printf("m2: ");
  scanf("%d",&m2);
  
  /*Calculate Distance 2*/
  f2=f2+(i2/12);
  i2=(i2%12);
  y2=y2+(f2/3);
  f2=(f2%3);
  m2=m2+(y2/1760);
  y2=(y2%1760);

  /*Output Disntance 2*/
  printf("Distance 2 is %d miles, %d yards, %d feet, %d inches.", m2, y2, f2, i2);

  /*Calculate Sum*/
  mt=m1+m2;
  yt=y1+y2;
  ft=f1+f2;
  itot=i1+i2;
  ft=ft+(itot/12);
  itot=(itot%12);
  yt=yt+(ft/3);
  ft=(ft%3);
  mt=mt+(yt/1760);
  yt=(yt%1760);
  
  /*Output Sum*/
  printf("\nThe sum of the distances is %d miles, %d yards, %d feet, and %d inches.\n\n", mt, yt, ft, itot);
  
  return 0;
}

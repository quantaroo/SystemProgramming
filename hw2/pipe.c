/* HW2 pipe.c:                 */
/*                             */
/* author: Jaccob Mau          */
/*                             */
/* modifications:              */
/* 23FEB2021  initial version  */
#include <stdio.h>


int main(){

  double r,R,L,T,V,ip,op,rings,total;

  printf("Please enter the inner radius of the pipe (r): ");
  scanf("%lf",&r);
  printf("Please enter the outer radius of the pipe (R): ");
  scanf("%lf",&R);
  printf("Please enter the length of the pipe (L): ");
  scanf("%lf",&L);

  T = R-r;
  V = 3.14159*L*((R*R)-(r*r));
  ip = 2.0*3.14159*r*L;
  op = 2.0*3.14159*R*L;
  rings = 2*(3.14159*((R*R)-(r*r)));
  total = ip+op+rings;

  printf("The thickness of the pipe is: %f", T);
  printf("\nThe volume of the pipe is: %f", V);
  printf("\nSurface area of the inner pipe: %f", ip);
  printf("\nSurface area of the outer pipe: %f", op);
  printf("\nSurface are of the rings: %f", rings);
  printf("\nThe total surface area of the pipe: %f\n", total);
  return 0;

}

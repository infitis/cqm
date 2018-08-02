#include <stdlib.h>
#include <stdio.h>

/*
	Least Squares Method
	y = ax + b
	Ruslan Keba, 2005
*/

#define MAX_N 32

int main (void)
{
    /* Header */
	printf("Least Squares Method.\n");

	/* Variables */
	int n = 0;
	int i;
	float x[MAX_N];
	float y[MAX_N];
	float sx=0;
	float sy=0;
	float sxy=0;
	float sx2=0;
	float a, b;

	float q;
	
    /* input data */
    printf("n = ");
    fflush(NULL);
    scanf("%d", &n);

    for (i=0; i<n; i++)
    {
     	printf("x[%d] = ", i);
	    fflush(NULL);
     	scanf("%f", x+i);
    }
    for (i=0; i<n; i++)
    {
     	printf("y[%d] = ", i);
	    fflush(NULL);
     	scanf("%f", y+i);
    }


    /* Sums */
    for (i=0; i<n; i++)
    {
    	sx += x[i];
    }
    for (i=0; i<n; i++)
    {
    	sy += y[i];
    }
    for (i=0; i<n; i++)
    {
    	sxy += (x[i]*y[i]);
    }
    for (i=0; i<n; i++)
    {
    	sx2 += (x[i]*x[i]);
    }

    /* out sums */
  	//printf("sx = %f, sy = %f, sxy = %f, sx2 = %f\n", sx, sy, sxy, sx2);
    //fflush(NULL);


    /* a & b */
    a = (n*sxy - sx*sy) / (n*sx2 - sx*sx);
    b = (sy - a*sx) / n;

    /* out */ 
  	printf("a = %f , b = %f\n", a, b);
    fflush(NULL);
 
    system("pause");
	return 0;
}

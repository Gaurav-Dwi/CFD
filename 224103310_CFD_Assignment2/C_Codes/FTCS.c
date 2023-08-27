#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{

    int j,m = 101;

    float time;
    printf("Enter the value of t : ");
    scanf("%f",&time);

    float H,Re,U,dt,dy,t,gama,u[m+1],un[m+1];

    Re = 100;
    U = 1.0;
    H = 1.0;
    dt = 0.005;
    dy = H/(m-1);
    gama = dt/(Re*dy*dy) ;

    FILE *ptr = fopen("FTCS.dat","w");

    fprintf(ptr,"TITLE = VELOCITY\nVARIABLES = \"u\", \"y\"\nZone T = \"BLOCK1\", j=%d, F=POINT\n",m);


    un[1] = 0.0;
    un[m] = U;

    for(j=2; j<m; j++)
    {

        un[j] = 0.0;
    }



    int iteration = 0;

    for(t=0.0; t<=time; t=t+dt)
    {


        for(j=1; j<=m; j++)
        {

            u[j] = un[j] ;
        }

        for(j=2; j<m; j++)
        {

            un[j] = (1-2*gama)*u[j] + gama*(u[j+1] + u[j-1]) ;
        }

        iteration++;
    }


    for(j=1; j<=m; j++)
    {

        fprintf(ptr,"%f\t\t%f\n", un[j], (j-1)*dy);
    }

    fclose(ptr);


    printf("Number of itertions are = %d\n",iteration);

    printf("The data file has been created");

    return 0;
}


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include<time.h>
#define lp 1000
// liczba losowan w metodzie Monte Carlo
#define N 70000
// dokladnosc szacowania min i max w metodzie Monte Carlo
#define n 40000
double c_od,c_do;

double f3(double x)
{

 return pow(sin(x), 5)*cos(x);   
}      
double f4(double x) {

 return x*sin(2*x*x+1);
}

double prostokaty(double( *f)(double))
{
       double krok, p, suma=0;

       krok=(c_do-c_od)/lp;
// upewnij sie co z ta wartoscia bezwzgledna
       for(p=c_od; p<=c_do; p+=krok)
               suma+=(*f)(p);
       return suma*krok;      
}

double trapezy(double (*f)(double))
{
        double krok=(c_do-c_od)/lp; //wysokosć trapezów
	double suma = 0.5 * ((*f)(c_od) + (*f)(c_do)); // suma pol

	for(double i=c_od+krok; i < c_do ; i+=krok)
	{
		suma += (*f)(i);
	}
	return krok * suma ;

}
       
double mc(double(*f)(double))
{
        // inicjalizacja zmiennych
         double MAX = (*f)(c_od);
         double MIN = (*f)(c_od);
         double krok=(c_do-c_od)/n;
         double x, y;
         // wylosowane punkty ktore naleza do obszaru, ktorego pole liczymy
        int trafienia = 0;
        double wartosc; 

         // szukanie MAX i MIN w podanym przedziale
         for(double i=c_od; i<=c_do; i= i+krok)
         {
                wartosc = (*f)(i);
                if(MAX < wartosc)
                {
                        MAX = wartosc;
                }
                else if (wartosc < MIN)
                {
                        MIN = wartosc;
                }
         }
        // losujemy punkty
        for(int i=0; i< N; i++)
        {
                // losowanie wspolzednych punktu
                x = c_od + (c_do -c_od) * rand() / (float)RAND_MAX;
                y = MIN + (MAX - MIN) * rand() / (float)RAND_MAX;
                //printf("MIN: %lf\n", x );
                wartosc = (*f)(x);

                //sprawdzenie czy punkt nalezy do szukanego obszatu
                if (y <= wartosc)
                {
                        if (y >=0) trafienia++;
                }
                else
                {
                        if (y <= 0) trafienia--;
                }
        }
     
       return (MAX-MIN)*(c_do-c_od)*trafienia/N;
}
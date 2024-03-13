#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include<time.h>
#define lp 10000
// liczba losowan w metodzie Monte Carlo
#define N 10000
// dokladnosc szacowania min i max w metodzie Monte Carlo
#define n 1000
double c_od=1,c_do=6;

double f3(double x)
{
 return 1/(sqrt(pow(x,5)+8));      
}      
double f4(double x) {

 return 1;
}


double prostokaty(double( *f)(double))
{
       double krok, p, suma=0;
       krok=(c_do-c_od)/lp;
       for(p=c_od; p<c_do; p+=krok)
               suma+=abs((*f)(p));
       return suma*krok;      
}

double trapezy(double (*f)(double))
{
        double krok=(c_do-c_od)/lp; //wysokosć trapezów
	double suma = 0.0; // suma pol
	double podstawa_a = abs((*f)(c_od)), podstawa_b;
		
	for(int i=1;i<=lp;i++)
	{
		podstawa_b = abs((*f)(c_od+krok*i));
		suma += (podstawa_a+podstawa_b);
		podstawa_a = podstawa_b;
	}
	return suma*0.5*krok;
return 1;
}
       
double mc(double(*f)(double))
{
        // inicjailzacja generatora liczb pseudolosowych
         srand(time(0));

        // inicjalizacja zmiennych
         double MAX = 0;
         double MIN = 0;
         double krok=(c_do-c_od)/n;
         // wylosowane punkty ktore naleza do obszaru, ktorego pole liczymy
         int trafienia = 0;

         
         // szukanie MAX i MIN w podanym przedziale
         for(double i=c_od; i<c_do; i= i+krok)
         {
                double wartosc = (*f)(i);
                if(MAX <= wartosc)
                {
                        MAX = wartosc;
                }
                else
                {
                        MIN = wartosc;
                }
         }

        // Jesli funkcja przyjmuje wartosci ujemne, to poprzez przesuniecie jej wraz szukanyym polem o MIN wzdloz osi OY nie zmienia wyniku, a upraszcza obliczenia - cala funkcja znajduje sie nad osia OY
        MAX += abs(MIN);
        // losowanie punktow z prostokata ograniczonego przez proste y=max, y=min, x=od, x=do
        for(int i=0; i<N; i++)
        {
                // wylosuj punkt
                int x = c_od + rand() % 1;
                // DO UFNKCJI TERAZ TRZABA DODAC MIN
                int y = 0 + rand() % 6;

                if((*f)(x)+MIN >= y)
                {
                        trafienia++;
                }
        }
        printf("oo: %lf\n", MAX);
        printf("od: %lf\n", c_od);
        return MAX*(c_do-c_od)*trafienia/N;
}
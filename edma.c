#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define S_SIZE 3

double rho;
double s[S_SIZE] = {0.0};
double t = 0, tmax = 0;

//rho: Compute decay factor from half-life in seconds
//tau is the desired time at which an element loses half its weight (eg 15 seconds)
double determine_rho(double tau)
{
  return pow(2, -1/tau);
}


void element_arrives()
{
  double new_value = 20 + 10.0 * drand48(); //random value between 20 and 30, say instrument price

  double e = fmax(0, t - tmax);

  int i;
  for(i = 0; i < S_SIZE; i++)
  {
    s[i] = pow(rho,e) * s[i] + pow(new_value, i); //many optimizations remain
  }

  tmax = fmax(t,tmax);

  double count = pow(rho,e) * s[0];
  
  double mean  = s[1]/s[0]; 

  double var   = (s[2] - pow(s[1],2)/s[0]) / (s[0] - 1 / pow(rho,e)); 

  printf("t: %6.1f\tprice: %-5.2f\ts0: %-7.2f s1: %-7.2f s2: %-7.2f\t", t, new_value, s[0], s[1], s[2]);
  printf("count: %-7.2f\tmean: %-7.2f\tvar: %-7.2f", count, mean, var);
  printf("\n");
}


int main()
{
  int i;
  srand48(time(0));

  rho = determine_rho(15.0); //use half life of 15 seconds

  for(i = 0; i < 40; i++)
  {
    element_arrives();
    t = t + 8.0 * drand48(); //update time to random time between "now" and 8 seconds from now 
  }

  return 0;
}

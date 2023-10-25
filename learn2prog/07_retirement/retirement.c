#include <stdlib.h>
#include <stdio.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};

typedef struct _retire_info retire_info;

void retirement (int startAge,
		 double initial,
		 retire_info working,
		 retire_info retired)
{ 
  for (int i = 0; i < working.months + retired.months; i++)
    {
      printf("Age %3d month %2d you have $%.2lf\n", (startAge + i) / 12, (startAge + i) % 12, initial);
      if (i < working.months)
	{
	   double interest_earned = initial * working.rate_of_return;
	   initial += (working.contribution + interest_earned);
	}
      else
        {
	   double interest_earned = initial * retired.rate_of_return;
	   initial += (retired.contribution + interest_earned);
	}
    }
}

int main()
{
  retire_info work = {489, 1000, 0.045/12};
  retire_info retire = {384, -4000, 0.01/12};
  int start = 327;
  int saving = 21345;

  retirement(start, saving, work, retire);

  return 0;
}
  
  
 
  

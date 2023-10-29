#include<stdlib.h>

unsigned power(unsigned x,unsigned y);

void run_check(unsigned x, unsigned y, unsigned expected_ans){
	if(power(x,y) != expected_ans){
		exit(EXIT_FAILURE);
	}
}

int main(){
	run_check(0,0,1);
	run_check(0,100,0);
	run_check(1,1000,1);
	run_check(100,0,1);
	run_check(10024,1,10024);
	run_check(10,3,1000);
	run_check(2,31,2147483648);
	return 0;
}

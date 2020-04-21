#include <iostream>
#include <cstdlib>
#include <stdint.h>

typedef float rate_t;
typedef float number_t;

class myWorm
{
private:
	size_t vulnerable_num;
	rate_t beta;

public:
	myWorm(size_t N,rate_t B)
	:vulnerable_num(N),beta(B)
	{
		number_t inf = 0;

		for(int i = 0;inf < vulnerable_num - 1;++i)
			print(i,inf = infected(i));
	}

	number_t infected(size_t time)
	{
		if(time == 0)
			return 1;
		number_t I = infected(time - 1);
		return I + beta*I*(vulnerable_num - I);
	}

	number_t susceptible(size_t time)
	{
		return vulnerable_num - infected(time);
	}
private:
	void print(size_t i,number_t N)
	{
		std::cout << i << "\t: " << N << std::endl;
	}

};
int main(int argc,char **args)
{
	if(argc == 3)
		new myWorm(atoi(args[1]),atof(args[2]));
	else
		new myWorm(10000,0.000025);
}

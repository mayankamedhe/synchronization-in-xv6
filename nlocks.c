#include "types.h"
#include "stat.h"
#include "user.h"

int main()
{
	init_counters();
	int val[10];

	for(int j=0; j<10; j++)
	{
		int ret;
		int i;	
		ret = fork();
		for(i=0; i<1000; i++)
		{
			acquire_lock(j);
			set_var(j, get_var(j)+1);
			release_lock(j);
		}

		if(ret == 0)
		{
			exit();
		}
		else
		{
			wait();
			val[j] = get_var(j);
		}
	}

	for (int i = 0; i < 10; ++i)
	{
		printf(1, "data[%d] = %d\n", i, val[i]);
	}
	exit();
}
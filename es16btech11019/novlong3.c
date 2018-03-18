#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


int main()
{
	int t;
	scanf("%d",&t);

	while(t--)
	{
		unsigned int n,p;
		scanf("%d%d",&n,&p);
		
		if((n/p)==1&&p>2)
			{
				printf("a");
				for(j=0;j<p-2;j++)
					printf("b");
				printf("a\n");
			}
		else if((n/p)==1&&p==2)
			printf("impossible\n");


	}

	return 0;
}

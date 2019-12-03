#include <stdio.h>
#include <string.h>


int main(int argc,char **args)
{
	if(argc==2)
	{
		char *s="/test.tm";
		s=strcat(args[1],s);
		FILE *fp=fopen("w+",s);
		char buf[3000];
		printf("%s\n",s);
		while(!feof(fp))
    {
		printf("1\n");
        fgets(buf,10,fp);
		printf("%s\n",buf);
    }
	}
	else
	{
		return 0;
	}
}


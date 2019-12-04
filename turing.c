#include <stdio.h>
#include <string.h>
#include "turing.h"
struct Turing_machine* turing_machine;
void parse(char *buf);


int main(int argc,char **args)
{
	if(argc==2)
	{
		char *s="/test.tm";
		s=strcat(args[1],s);
		FILE *fp=fopen(s,"r+");
		char buf[5000];

		turing_machine=(struct Turing_machine*)malloc(sizeof(struct Turing_machine));
		while(!feof(fp))
    	{
        	fgets(buf,4900,fp);
			//parse

			parse(buf);
    	}
		
	}
	else
	{
		return 0;
	}
}

void parse(char *buf)
{
	if(buf[0]=='#')
	{
		//状态集
		if(buf[1]=='Q')
		{
			int l;
			for(l=2;buf[l]!='{';l++);
			int r1,r2=l;
			for(r1=l;;r1++)
			{
				if(buf[r1]==','||buf[r1]=='}')
				{
					int len=r1-r2;
					char *state=(char *)malloc(sizeof(char)*(len+5));
					for(int i=0;i<len-1;i++)
					{
						state[i]=buf[r2+i+1];
					}
					struct symbol_set *t=create_symbol(state);
					t->next=turing_machine->state_set;
					turing_machine->state_set=t;
					r2=r1;
					if(buf[r1]=='}')
					{
						break;
					}
				}
			}
		}
		//输出符号集
		if(buf[1]=='S')
		{
			int l;
			for(l=2;buf[l]!='{';l++);
			int r1,r2=l;
			for(r1=l;;r1++)
			{
				if(buf[r1]==','||buf[r1]=='}')
				{
					int len=r1-r2;
					char *state=(char *)malloc(sizeof(char)*(len+5));
					for(int i=0;i<len-1;i++)
					{
						state[i]=buf[r2+i+1];
					}
					struct symbol_set *t=create_symbol(state);
					t->next=turing_machine->input_symbol_set;
					turing_machine->input_symbol_set=t;
					r2=r1;
					if(buf[r1]=='}')
					{
						break;
					}
				}
			}
		}
		//纸带符号集
		if(buf[1]=='G')
		{
			int l;
			for(l=2;buf[l]!='{';l++);
			int r1,r2=l;
			for(r1=l;;r1++)
			{
				if(buf[r1]==','||buf[r1]=='}')
				{
					int len=r1-r2;
					char *state=(char *)malloc(sizeof(char)*(len+5));
					for(int i=0;i<len-1;i++)
					{
						state[i]=buf[r2+i+1];
					}
					struct symbol_set *t=create_symbol(state);
					t->next=turing_machine->tape_symbol_set;
					turing_machine->tape_symbol_set=t;
					r2=r1;
					if(buf[r1]=='}')
					{
						break;
					}
				}
			}
		}
		//终结状态集
		if(buf[1]=='F')
		{
			int l;
			for(l=2;buf[l]!='{';l++);
			int r1,r2=l;
			for(r1=l;;r1++)
			{
				if(buf[r1]==','||buf[r1]=='}')
				{
					int len=r1-r2;
					char *state=(char *)malloc(sizeof(char)*(len+5));
					for(int i=0;i<len-1;i++)
					{
						state[i]=buf[r2+i+1];
					}
					struct symbol_set *t=create_symbol(state);
					t->next=turing_machine->terminate_symbol_set;
					turing_machine->terminate_symbol_set=t;
					r2=r1;
					if(buf[r1]=='}')
					{
						break;
					}
				}
			}
		}
		if(buf[1]=='B')
		{
			char *space=(char *)malloc(sizeof(char)*3);
			space[0]=buf[5];
			turing_machine->space_symbol=space;
		}
		if(buf[1]=='q'&&buf[2]=='0')
		{
			int l=6,r;
			for(r=l;buf[r];r++);
			int len=r-l;
			char *init_s=(char *)malloc(sizeof(char)*len+5);
			for(int i=0;i<len-1;i++)
			{
				init_s[i]=buf[l+i];
			}
			turing_machine->init_state=init_s;
		}
		if(buf[1]=='N')
		{
			int l=5,r;
			for(r=l;buf[r];r++);
			int len=r-l;
			char *init_s=(char *)malloc(sizeof(char)*len+5);
			for(int i=0;i<len-1;i++)
			{
				init_s[i]=buf[l+i];
			}
			turing_machine->tape_number=atoi(init_s);
		}
	}
	else if(buf[0]!=';')
	{
		
	}
	
}
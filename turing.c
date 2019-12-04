#include <stdio.h>
#include <string.h>
#include "turing.h"
struct Turing_machine* turing_machine;
void parse(char *buf);
void process(char *buf);
struct transform_function *search_transform_function(char *current_state,char *current_symbol);
FILE *console_fp;


int main(int argc,char **args)
{
	if(argc==2)
	{
		char *cons=(char *)malloc(sizeof(char)*100);
		strcat(cons,args[1]);
		strcat(cons,"/console.txt");
		console_fp=fopen(cons,"w+");
		char *s=(char *)malloc(sizeof(char)*100);
		strcat(s,args[1]);
		strcat(s,"/test.tm");
		FILE *fp=fopen(s,"r+");
		char buf[5000];

		turing_machine=(struct Turing_machine*)malloc(sizeof(struct Turing_machine));
		while(!feof(fp))
    	{
        	fgets(buf,4900,fp);
			//parse
			parse(buf);
    	}
		
		char *input=(char *)malloc(sizeof(char)*100);
		strcat(input,args[1]);
		strcat(input,"/input.txt");
		FILE *inputfp=fopen(input,"r+");
		while(!feof(inputfp))
		{
			fgets(buf,4900,inputfp);
			process(buf);
		}
	}
	else
	{
		return 0;
	}
}

void process(char *buf)
{
	int tape_number=turing_machine->tape_number;	  									//纸带数
	struct symbol_set *state_set=turing_machine->state_set;                     		//状态集
    struct symbol_set *input_symbol_set=turing_machine->input_symbol_set;           	//输入符号集
    struct symbol_set *tape_symbol_set=turing_machine->tape_symbol_set;          	    //纸带符号集
    char *init_state=turing_machine->init_state;                                 		//初始状态
    char *space_symbol=turing_machine->space_symbol;                               		//空格符号
    struct symbol_set *terminate_symbol_set=turing_machine->terminate_symbol_set;       //终结状态集
    struct transform_function* transform_function=turing_machine->transform_function;   //转移函数


	struct Tape *tape[tape_number];
	for(int i=0;i<tape_number;i++)
	{
		tape[i]=(struct Tape *)malloc(sizeof(struct Tape));
		tape[i]->right=(struct Tape *)malloc(sizeof(struct Tape));
		tape[i]->right->index=0;
		tape[i]->right->ishead=1;
		tape[i]->right->symbol=space_symbol[0];
	}

	int step=0;
	char* state=init_state;

	int len=strlen(buf);
	for(int i=0;i<len;i++)
	{
		if(i==0)
		{
			tape[0]->right->index=0;

			tape[0]->right->symbol=buf[i];
		}
		else
		{
			add_right(tape[0],create_tape(buf[i]));
		}
		
	}
	while(1)
	{
		char *current_symbol=(char *)malloc(sizeof(char)*1000);
		fprintf(console_fp,"Step\t:\t%d\n",step++);

		for(int i=0;i<tape_number;i++)
		{
			struct Tape *t=tape[i];
			fprintf(console_fp,"Index%d\t:\t",i);
			while(t->right)
			{
				fprintf(console_fp,"%d",t->right->index);
				if(!t->right->right)
				{
					fprintf(console_fp,"\n");
					break;
				}
				fprintf(console_fp,"\t");
				t=t->right;
			}
			fprintf(console_fp,"Tape%d\t:\t",i);
			t=tape[i];
			while(t->right)
			{
				fprintf(console_fp,"%c",t->right->symbol);
				if(!t->right->right)
				{
					fprintf(console_fp,"\n");
					break;
				}
				fprintf(console_fp,"\t");
				t=t->right;
			}
			fprintf(console_fp,"Head%d\t:\t",i);
			t=tape[i];
			while(t->right)
			{
				if(t->right->ishead==1)
				{
					fprintf(console_fp,"^");
					current_symbol[i]=t->right->symbol;
				}
				if(!t->right->right)
				{
					fprintf(console_fp,"\n");
					break;
				}
				fprintf(console_fp,"\t");
				t=t->right;
			}
		}
		fprintf(console_fp,"State\t:\t%s\n",state);
		printf("%s\n%s\n",state,current_symbol);
		struct transform_function *tf=search_transform_function(state,current_symbol);
		if(!tf)
		{
			printf("aaaa\n");
			break;
		}
		printf("%s\n%s\n%s\n",tf->next_state,tf->next_symbol,tf->move_direction);
		break;
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
	else if(buf[0]!=';'&&buf[0]!='\n')
	{
		int l=0,r,len;
		for(r=l;buf[r]!=' ';r++);
		len=r-l+1;
		char *current_state=(char *)malloc(sizeof(char)*len+5);
		for(int i=0;i<len-1;i++)
		{
			current_state[i]=buf[l+i];
		}
		
		l=r+1;
		for(r=l;buf[r]!=' ';r++);
		len=r-l+1;
		char *current_symbol=(char *)malloc(sizeof(char)*len+5);
		for(int i=0;i<len-1;i++)
		{
			current_symbol[i]=buf[l+i];
		}

		l=r+1;
		for(r=l;buf[r]!=' ';r++);
		len=r-l+1;
		char *next_symbol=(char *)malloc(sizeof(char)*len+5);
		for(int i=0;i<len-1;i++)
		{
			next_symbol[i]=buf[l+i];
		}

		l=r+1;
		for(r=l;buf[r]!=' ';r++);
		len=r-l+1;
		char *move_direction=(char *)malloc(sizeof(char)*len+5);
		for(int i=0;i<len-1;i++)
		{
			move_direction[i]=buf[l+i];
		}

		l=r+1;
		for(r=l;buf[r]&&buf[r]!=';'&&buf[r]!='\n'&&buf[r]!=' '&&buf[r]!='\t'&&buf[r]!='\0';r++);
		len=r-l+1;
		char *next_state=(char *)malloc(sizeof(char)*len+5);
		for(int i=0;i<len-1;i++)
		{
			next_state[i]=buf[l+i];
		}

		struct transform_function* t=create_transform_function(current_state,current_symbol,next_symbol,move_direction,next_state);
		t->next=turing_machine->transform_function;
		turing_machine->transform_function=t;
	}
	
}

struct transform_function *search_transform_function(char *current_state,char *current_symbol)
{
	struct transform_function *t=turing_machine->transform_function;
	while (t)
	{
		if(!strcmp(current_state,t->current_state)&&!strcmp(current_symbol,t->current_symbol))//未考虑通配符
		{
			break;
		}
		t=t->next;
	}
	return t;
	//if t is null, the turing-machine must be terminated!
}
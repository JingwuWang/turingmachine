#include <stdlib.h>

struct symbol_set{
	char *element;
	struct symbol_set* next;
};

struct transform_function{
    char *current_state;
    char *next_state;
    char *current_symbol;
    char *move_direction;
    char *next_symbol;
    struct transform_function *next;
};

struct Turing_machine{
    struct symbol_set *state_set;                     //状态集
    struct symbol_set *input_symbol_set;              //输入符号集
    struct symbol_set *tape_symbol_set;               //纸带符号集
    char *init_state;                                 //初始状态
    char *space_symbol;                               //空格符号
    struct symbol_set *terminate_symbol_set;          //终结状态集
    int tape_number;                                  //纸带数
    struct transform_function* transform_function;    //转移函数
}  ;

struct transform_function* create_transform_function(char *current_state,char *current_symbol,char *next_symbol,char *move_direction,char *next_state)
{
    struct transform_function* tf=(struct transform_function*)malloc(sizeof(struct transform_function));
    tf->current_state=current_state;
    tf->current_symbol=current_symbol;
    tf->next_state=next_state;
    tf->next_symbol=next_symbol;
    tf->move_direction=move_direction;
    return tf;
}

struct symbol_set* create_symbol(char *s)
{
    struct symbol_set* ss=(struct symbol_set*)malloc(sizeof(struct symbol_set));
    ss->element=s;
    return ss;
}
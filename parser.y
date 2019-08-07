%{
	#include "stdio.h"
	#include <iostream>
	extern "C" void yyerror (char *);
	extern int yylex(void);
	extern int yylineno;
	Symbol_Table * global_symbol_table;	
	Symbol_Table * local_symbol_table;
	Symbol_Table * formal_symbol_table;
	// Symbol_Table * temp_symbol_table;
	// list<Ast *> * ast_list;
	list<Symbol_Table_Entry *> global_symbol_temp;
	list<Symbol_Table_Entry *> local_symbol_temp;
	string proc_name;
	int argcount = 0;

%}
%union  {
	int integer_value;
	double double_value;
	std::string * string_value;
	Ast * ast;
	Sequence_Ast * seq_ast;
	list<Ast *> * list_ast;
	Symbol_Table * symbol_table;
	Symbol_Table_Entry * symbol_entry;
	Basic_Block * basic_block;
	Procedure * procedure;
	Data_Type dt;

	}
%token <string_value> NAME
%token <integer_value> INTEGER_NUMBER
%token <double_value> DOUBLE_NUMBER
%token ASSIGN
%token INTEGER
%token FLOAT
%token VOID
%token DO
%token WHILE
%token IF
%token ELSE
%token NOT
%token EQUAL
%token NOT_EQUAL
%token LESS_THAN
%token LESS_THAN_EQUAL
%token GREATER_THAN
%token GREATER_THAN_EQUAL
%token AND
%token OR
%token PRINT
%token RETURN
%type<ast> expr
%type<ast> expr2
%type<ast> asgn
%type<list_ast> asgnlist
%type<list_ast> asgnlist1
%type<ast> body
%type<ast> body1
%type<ast> while
%type<ast> dowhile
%type<ast> if
%type<ast> ifelse
%type<ast> boolexpr
%type<ast> relexpr
%type<ast> arithif
%type<ast> printstmt
%type<dt> type
%type<symbol_entry> argtype
%type<symbol_table> typeargs
%type<symbol_table> args 
%type<symbol_entry> arg
%type<ast> return
%type<ast> fnasgn
%type<list_ast> callarglist

%left '?' ':'
%left OR
%left AND
%left EQUAL NOT_EQUAL
%left LESS_THAN LESS_THAN_EQUAL GREATER_THAN GREATER_THAN_EQUAL
%left '+' '-'
%left '*' '/'
%right NOT
%%

start
	:
	{
		
		global_symbol_table = new Symbol_Table();
			
		global_symbol_table->set_table_scope(global);
		
		
	}
	decllistglobal func
	{
		program_object.set_global_table(*global_symbol_table);
	}


decllistglobal
	:  decllistglobal declglobal
	| 

declglobal
	: type varlistglobal  ';'
	{
		if($1 == void_data_type){
			yyerror("cs316: Error - Variable cannot be void\n"); 
			exit(EXIT_FAILURE);
		}
		std::list<Symbol_Table_Entry *>::iterator it;
		for (it = global_symbol_temp.begin(); it != global_symbol_temp.end(); ++it){
			if((*it)->get_data_type() == void_data_type) {
				(*it)->set_data_type($1);
				Symbol_Table * temp = new Symbol_Table();
				temp->push_symbol(*it);
				global_symbol_table->append_list(*temp,yylineno);
				free(temp);
			}
		}
	}
	| type NAME '(' args ')'  ';'
	{
		Procedure* procedure = new Procedure($1,*$2,yylineno);
		procedure->set_formal_param_list(*$4);	
		program_object.set_proc_to_map(*$2,procedure);
	}
	| type NAME '(' typeargs ')'  ';'
	{
		Procedure* procedure = new Procedure($1,*$2,yylineno);
		procedure->set_formal_param_list(*$4);	
		program_object.set_proc_to_map(*$2,procedure);
	}

typeargs
	: typeargs ',' argtype
	{
		$1->push_symbol($3);
	}
	| argtype
	{
		Symbol_Table * st = new Symbol_Table();
		st->set_table_scope(formal);
		st->push_symbol($1);
		formal_symbol_table = st;
		$$ = st;
	}

argtype
	: INTEGER 
	{ 
		string name = to_string(argcount);
		Symbol_Table_Entry * t = new Symbol_Table_Entry(name,int_data_type,yylineno);  
		argcount += 1;
		t->set_symbol_scope(formal); 
		$$ = t;
	}
	| FLOAT
	{ 
		string name = to_string(argcount);
		Symbol_Table_Entry * t = new Symbol_Table_Entry(name,double_data_type,yylineno);  
		argcount += 1;
		t->set_symbol_scope(formal); 
		$$ = t;
	}
	| VOID
	{ 
		string name = to_string(argcount);
		Symbol_Table_Entry * t = new Symbol_Table_Entry(name,void_data_type,yylineno);  
		argcount += 1;
		t->set_symbol_scope(formal); 
		$$ = t;
	}


varlistglobal
	: varlistglobal ',' NAME 
	{ 
		Symbol_Table_Entry * t = new Symbol_Table_Entry(*$3,void_data_type,yylineno);  
		t->set_symbol_scope(global); 
		global_symbol_temp.push_back(t);  
	}
	| NAME 
	{ 
		Symbol_Table_Entry * t = new Symbol_Table_Entry(*$1,void_data_type,yylineno);  
		t->set_symbol_scope(global); 
		global_symbol_temp.push_back(t);  
	}

func
	:

	functions
	
functions
	: function functions
	| function


function
	: type NAME '(' args ')' 
	{

		if(program_object.is_procedure_exists(*$2)){
			Procedure * p = program_object.get_procedure_prototype(*$2);
			if(p->is_proc_defined()){
				yyerror("cs316: Error - Redefinition of a function\n"); 
				exit(EXIT_FAILURE);
			}
			if($1 != p->get_return_type()){
				yyerror("cs316: Error - Redeclaration of a function with different return type\n"); 
				exit(EXIT_FAILURE);
			}
		}

		if(*$2 == "main"){
			if($1 != void_data_type){
				yyerror("cs316: Error - main should be void\n"); 
				exit(EXIT_FAILURE);
			}
		}


		proc_name = *$2;
		Procedure* procedure = new Procedure($1,*$2,yylineno);

		procedure->set_formal_param_list(*$4);		
		program_object.set_proc_to_map(*$2,procedure);
	}
	'{' decllist asgnlist1'}'
	{
		Procedure* procedure = program_object.get_procedure_prototype(*$2);
		procedure->set_local_list(*local_symbol_table);		
		procedure->set_ast_list(*$9);
		procedure->set_proc_is_defined();
	}


type
	: INTEGER { $$ = int_data_type;}
	| FLOAT   { $$ = double_data_type;}
	| VOID   { $$ = void_data_type;}


args
	: args ',' arg
	{
		$1->push_symbol($3);
	}
	| arg
	{
		Symbol_Table * st = new Symbol_Table();
		st->set_table_scope(formal);
		st->push_symbol($1);
		formal_symbol_table = st;
		$$ = st;
	}
	| {
		Symbol_Table * st = new Symbol_Table();
		st->set_table_scope(formal);
		formal_symbol_table = st;
		$$ = st;
	}

arg 
	: type NAME
	{
		Symbol_Table_Entry * t = new Symbol_Table_Entry(*$2,$1,yylineno);  
		t->set_symbol_scope(formal); 
		$$ = t;
	}

return
	: RETURN expr
	{
		Procedure * p = program_object.get_procedure_prototype(proc_name);
		if($2->get_data_type() != p->get_return_type()){
			yyerror("cs316: Error - return type mismatch\n"); 
			exit(EXIT_FAILURE);
		}

		Return_Ast *r = new Return_Ast($2,proc_name,yylineno);
		$$ = r;
	}
	| RETURN
	{
		Return_Ast *r = new Return_Ast(NULL,proc_name,yylineno);

		$$ = r;
	}

decllist
	: decllist decl
	| {

		Symbol_Table * lst = new Symbol_Table();

		lst->set_table_scope(local);

		local_symbol_table = lst;

	}

decl
	: INTEGER varlist ';'
	{

		std::list<Symbol_Table_Entry *>::iterator it;
		for (it = local_symbol_temp.begin(); it != local_symbol_temp.end(); ++it){
			if((*it)->get_data_type() == void_data_type){
				(*it)->set_data_type(int_data_type);
				Symbol_Table * temp = new Symbol_Table();
				temp->push_symbol(*it);
				local_symbol_table->append_list(*temp,yylineno);
				free(temp);
			}
		}

	}

	| FLOAT varlist ';'
	{
		std::list<Symbol_Table_Entry *>::iterator it;
		for (it = local_symbol_temp.begin(); it != local_symbol_temp.end(); ++it){
			if((*it)->get_data_type() == void_data_type){
				(*it)->set_data_type(double_data_type);
				Symbol_Table temp = Symbol_Table();
				temp.push_symbol(*it);
				local_symbol_table->append_list(temp,yylineno);
			}
		}
	}

varlist
	: NAME ',' varlist 
	{ 
		Symbol_Table_Entry * t = new Symbol_Table_Entry(*$1,void_data_type,yylineno);  
		t->set_symbol_scope(local); 
		local_symbol_temp.push_front(t);  
	}
	| NAME 
	{ 
		Symbol_Table_Entry * t = new Symbol_Table_Entry(*$1,void_data_type,yylineno);  
		t->set_symbol_scope(local); 
		local_symbol_temp.push_front(t);  
	}


asgnlist1
	: asgnlist1 body1
	{
		$1->push_back($2);
		$$ = $1;
	}
	| {
		list<Ast *> * ast_list = new list<Ast *>();
		$$ = ast_list;
	}

body1
	: asgn ';' { $$ = $1;
	}
	| while { $$ = $1;
	}
	| dowhile { $$ = $1;
	}
	| if { $$ = $1;
	}
	| ifelse { $$ = $1;
	}
	| printstmt ';'{ $$ = $1;
	}
	| return ';' { $$ = $1;
	}
	| fnasgn ';' { 
		((Call_Ast*)($1))->set_register(new Register_Descriptor());
		$$ = $1;
	}
	| '{' asgnlist '}' 
		{
			if((*$2).empty()){
				yyerror("cs316: Error - Block of statements cannot be empty"); 
				exit(EXIT_FAILURE);
			}
			Sequence_Ast * s = new Sequence_Ast(yylineno);
			list<Ast *> :: iterator it;
			for(it = (*$2).begin(); it != (*$2).end();++it){
				s->ast_push_back((*it));
			}
			$$ = s;
		}


asgnlist
	: 
	asgnlist body
	{
		$1->push_back($2);
		$$ = $1;
	}
	|
	{
		list<Ast *> * s = new list<Ast *>();
		//Sequence_Ast * s = new Sequence_Ast(yylineno);
		$$ = s;
	}


body
	: asgn ';' { $$=$1; //ast_list->push_back($1);
	}
	| while { $$=$1; //ast_list->push_back($1);
	}
	| dowhile { $$=$1; //ast_list->push_back($1);
	}
	| if { $$=$1; //ast_list->push_back($1);
	}
	| ifelse { $$=$1; //ast_list->push_back($1);
	}
	| return ';' { $$ = $1;
	}
	| printstmt ';' { $$=$1; //ast_list->push_back($1);
	}
	| fnasgn ';' { 
		((Call_Ast*)($1))->set_register(new Register_Descriptor());
		$$ = $1;
	}
	| '{' asgnlist '}' 
		{
			if((*$2).empty()){
				yyerror("cs316: Error - Block of statements cannot be empty"); 
				exit(EXIT_FAILURE);
			}
			Sequence_Ast * s = new Sequence_Ast(yylineno);
			list<Ast *> :: iterator it;
			for(it = (*$2).begin(); it != (*$2).end();++it){
				s->ast_push_back((*it));
			}
			$$ = s;
		}

callarglist
	: callarglist ',' expr
	{
		$1->push_back($3);
		$$ = $1;
	}
	| expr 
	{
		list<Ast *> * s = new list<Ast *>();
		s->push_back($1);
		$$ = s;

	}
	| {
		list<Ast *> * s = new list<Ast *>();
		$$ = s;
	}

fnasgn
	: NAME '(' callarglist ')'
	{
		if(!program_object.is_procedure_exists(*$1)){
			yyerror("cs316: Error - Called function does not exist\n"); 
			exit(EXIT_FAILURE);
		}

		Call_Ast * c = new Call_Ast(*$1,yylineno);
		c->set_actual_param_list(*$3);
		Procedure * p = program_object.get_procedure_prototype(*$1);

		Assignment_Ast * a;
		
		c->check_actual_formal_param(p->get_formal_param_list());
		$$ = c;
	}

asgn
	: NAME ASSIGN expr 
	{
		Name_Ast * n;
		if(local_symbol_table->variable_in_symbol_list_check(*$1)) 
			n = new Name_Ast(*$1,local_symbol_table->get_symbol_table_entry(*$1),yylineno);
		else if(formal_symbol_table->variable_in_symbol_list_check(*$1))
			n = new Name_Ast(*$1,formal_symbol_table->get_symbol_table_entry(*$1),yylineno);
		else if(global_symbol_table->variable_in_symbol_list_check(*$1)) 
			n = new Name_Ast(*$1,global_symbol_table->get_symbol_table_entry(*$1),yylineno);
		else {
			yyerror("cs316: Error - Variable not declared"); 
			exit(EXIT_FAILURE);
		}
		Assignment_Ast * a = new Assignment_Ast(n,$3,yylineno);
		a->check_ast();
		$$ = a;
	}
	| NAME ASSIGN fnasgn
	{
		Name_Ast * n;
		if(local_symbol_table->variable_in_symbol_list_check(*$1)) 
			n = new Name_Ast(*$1,local_symbol_table->get_symbol_table_entry(*$1),yylineno);
		else if(formal_symbol_table->variable_in_symbol_list_check(*$1))
			n = new Name_Ast(*$1,formal_symbol_table->get_symbol_table_entry(*$1),yylineno);
		else if(global_symbol_table->variable_in_symbol_list_check(*$1)) 
			n = new Name_Ast(*$1,global_symbol_table->get_symbol_table_entry(*$1),yylineno);
		else {
			yyerror("cs316: Error - Variable not declared"); 
			exit(EXIT_FAILURE);
		}
		Assignment_Ast * a = new Assignment_Ast(n,$3,yylineno);
		a->check_ast();
		$$ = a;
	}

while
	: WHILE '(' boolexpr ')' body
	{
		Iteration_Statement_Ast * s = new Iteration_Statement_Ast($3,$5,yylineno,false);
		s->check_ast();
		$$ = s;
	}


dowhile
	: DO body WHILE '(' boolexpr ')' ';'
	{
		Iteration_Statement_Ast * s = new Iteration_Statement_Ast($5,$2,yylineno,true);
		s->check_ast();
		$$ = s;
	}	

if
	: IF '(' boolexpr ')' body 
	{
		Selection_Statement_Ast * s = new Selection_Statement_Ast($3,$5,NULL,yylineno);
		s -> check_ast();
		$$ = s;
	}

ifelse
	: IF '(' boolexpr ')' body ELSE body 
	{
		Selection_Statement_Ast * s = new Selection_Statement_Ast($3,$5,$7,yylineno);
		s -> check_ast();
		$$ = s;
	}

printstmt 
	: PRINT NAME
	{
		//todo

		Name_Ast * n;
		if(local_symbol_table->variable_in_symbol_list_check(*$2)) 
			n = new Name_Ast(*$2,local_symbol_table->get_symbol_table_entry(*$2),yylineno);
		else if(formal_symbol_table->variable_in_symbol_list_check(*$2))
			n = new Name_Ast(*$2,formal_symbol_table->get_symbol_table_entry(*$2),yylineno);
		else if(global_symbol_table->variable_in_symbol_list_check(*$2)) 
			n = new Name_Ast(*$2,global_symbol_table->get_symbol_table_entry(*$2),yylineno);
		else {
			yyerror("cs316: Error - Variable not declared"); 
			exit(EXIT_FAILURE);
		}

		Print_Ast * s = new Print_Ast(n,yylineno);
		s -> check_ast();
		$$ = s;
	}


boolexpr
	: boolexpr AND boolexpr
	{
		Logical_Expr_Ast * l = new Logical_Expr_Ast($1,_logical_and,$3,yylineno);
		l->check_ast();
		$$ = l;
	}
	| boolexpr OR boolexpr
	{
		Logical_Expr_Ast * l = new Logical_Expr_Ast($1,_logical_or,$3,yylineno);
		l->check_ast();
		$$ = l;
	}
	| NOT boolexpr
	{
		Logical_Expr_Ast * l = new Logical_Expr_Ast($2,_logical_not,$2,yylineno);
		l->check_ast();
		$$ = l;
	}
	| relexpr
	{
		$$ = $1;
	}
	| '(' boolexpr ')'
	{
		$$ = $2;
	}

relexpr
	: expr LESS_THAN expr
	{
		Relational_Expr_Ast * r = new Relational_Expr_Ast($1,less_than,$3,yylineno);
		r->check_ast();
		$$ = r;
	}
	| expr LESS_THAN_EQUAL expr
	{
		Relational_Expr_Ast * r = new Relational_Expr_Ast($1,less_equalto,$3,yylineno);
		r->check_ast();
		$$ = r;
	}
	| expr GREATER_THAN expr
	{
		Relational_Expr_Ast * r = new Relational_Expr_Ast($1,greater_than,$3,yylineno);
		r->check_ast();
		$$ = r;
	}
	| expr GREATER_THAN_EQUAL expr
	{
		Relational_Expr_Ast * r = new Relational_Expr_Ast($1,greater_equalto,$3,yylineno);
		r->check_ast();
		$$ = r;
	}
	| expr EQUAL expr
	{
		Relational_Expr_Ast * r = new Relational_Expr_Ast($1,equalto,$3,yylineno);
		r->check_ast();
		$$ = r;
	}
	| expr NOT_EQUAL expr
	{
		Relational_Expr_Ast * r = new Relational_Expr_Ast($1,not_equalto,$3,yylineno);
		r->check_ast();
		$$ = r;
	}
	| '(' relexpr ')'
	{
		$$ = $2;
	}

expr
	: expr '-' expr { Minus_Ast * m = new Minus_Ast($1,$3,yylineno);  m->set_data_type($1->get_data_type()); m->check_ast(); $$ = m;} 
	| expr '+' expr { Plus_Ast * m = new Plus_Ast($1,$3,yylineno); m->set_data_type($1->get_data_type()); m->check_ast(); $$ = m;} 
	| expr '*' expr { Mult_Ast * m = new Mult_Ast($1,$3,yylineno); m->set_data_type($1->get_data_type()); m->check_ast(); $$ = m;} 
	| expr '/' expr { Divide_Ast * m = new Divide_Ast($1,$3,yylineno); m->set_data_type($1->get_data_type()); m->check_ast(); $$ = m;} 
	| '-' expr %prec '*' { UMinus_Ast * m = new UMinus_Ast($2,NULL,yylineno); m->set_data_type($2->get_data_type()); $$ = m;}
	| arithif {$$ = $1;}
	| expr2 {$$ = $1;}
	
expr2
	: NAME {
		Name_Ast * n;
		if(local_symbol_table->variable_in_symbol_list_check(*$1)) 
			n = new Name_Ast(*$1,local_symbol_table->get_symbol_table_entry(*$1),yylineno);
		else if(formal_symbol_table->variable_in_symbol_list_check(*$1)){
			n = new Name_Ast(*$1,formal_symbol_table->get_symbol_table_entry(*$1),yylineno);
		}
		else if(global_symbol_table->variable_in_symbol_list_check(*$1)) 
			n = new Name_Ast(*$1,global_symbol_table->get_symbol_table_entry(*$1),yylineno);
		else {
			yyerror("cs316: Error - Variable not declared"); 
			exit(EXIT_FAILURE);
		}
		$$ = n;
	}
	| INTEGER_NUMBER {
		Number_Ast<int> * num = new Number_Ast<int>($1,int_data_type,yylineno);
		$$ = num;
	}
	| DOUBLE_NUMBER {
		Number_Ast<double> * num = new Number_Ast<double>($1,double_data_type,yylineno);
		$$ = num;
	}
	| '(' expr ')' { $$ = $2;}

arithif
	: boolexpr '?' expr ':' expr
	{
		Conditional_Expression_Ast * c = new Conditional_Expression_Ast($1,$3,$5,yylineno);
		c->check_ast();
		$$ = c;
	}


%%
// #include "symbol-table.hh"
#include<stdlib.h>

// Ast Class
int Ast::labelCounter;	
Ast::Ast(){
//printf("Inside ast constr\n");

}
Ast::~Ast(){

}

Data_Type Ast::get_data_type(){
	return node_data_type;
}

void Ast::set_data_type(Data_Type dt){
	node_data_type = dt;
}

bool Ast::is_value_zero(){
	return false;
}

bool Ast::check_ast(){
	return true;
}

Symbol_Table_Entry & Ast::get_symbol_entry(){

}

void Ast::print(ostream & file_buffer){
	if(!this->check_ast()) return;
}

//////////////////////////////////////////////////////////////////////
//Asssignment Ast Class

Assignment_Ast::Assignment_Ast(Ast * temp_lhs, Ast * temp_rhs, int line){
		//printf("Inside aasgn constr\n");
		ast_num_child = binary_arity;
		lineno = line;
		node_data_type = void_data_type;
		lhs = temp_lhs;
		rhs = temp_rhs;
		//printf("Inside aasgn constr222\n");
}


Assignment_Ast::~Assignment_Ast(){

}

// bool Assignment_Ast::check_ast(){
// 	if(lhs->check_ast() && rhs->check_ast()){
// 		if(lhs->get_data_type() == rhs->get_data_type())
// 			return true;
// 	}

// 	printf("cs316: Error - sclp error: Asssignment statement data type not compatible\n");
// 	//exit(-1);
// 	return false;
// }

bool Assignment_Ast::check_ast(){
	if(lhs->get_data_type() == rhs->get_data_type())
		return true;


	printf("cs316: Error - sclp error: Asssignment statement data type not compatible\n");
	//exit(-1);
	return false;
}
void Assignment_Ast::print(ostream & file_buffer){
	if(!this->check_ast()) return;
	file_buffer << "\n" << AST_SPACE << "Asgn:\n" << AST_NODE_SPACE << "LHS (";
	lhs->print(file_buffer);
	file_buffer << ")\n"<< AST_NODE_SPACE << "RHS (";
	rhs->print(file_buffer);
	file_buffer << ")";
}

//////////////////////////////////////////////////////////////////////
//Name Ast Class


Name_Ast::Name_Ast(string & name, Symbol_Table_Entry & var_entry, int line){
	// todo: how to use name?
	//printf("Inside name constr\n");
	variable_symbol_entry = & var_entry;
	node_data_type = var_entry.get_data_type();
	lineno = line;
	//printf("Inside name constr\n");
}

Name_Ast::~Name_Ast(){

}

Data_Type Name_Ast::get_data_type(){
	return variable_symbol_entry -> get_data_type();
}

Symbol_Table_Entry & Name_Ast::get_symbol_entry(){
	return *variable_symbol_entry;
}

void Name_Ast::set_data_type(Data_Type dt){
	variable_symbol_entry->set_data_type(dt);
	node_data_type = dt;
}

void Name_Ast::print(ostream & file_buffer){
	if(!this->check_ast()) return;
	file_buffer << "Name : " << variable_symbol_entry->get_variable_name();
}

//////////////////////////////////////////////////////////////////////
//Number Ast Class

template class Number_Ast<double>;
template class Number_Ast<int>;

template <class T>
Number_Ast<T>::Number_Ast(T number, Data_Type constant_data_type, int line){
	//printf("Inside num constr\n");
	this->constant = number;
	node_data_type = constant_data_type;
	lineno = line;
	//printf("Inside num constr\n");
}

template <class T>
Number_Ast<T>::~Number_Ast(){

}

template <class T>
Data_Type Number_Ast<T>::get_data_type(){
	return node_data_type;
}

template <class T>
void Number_Ast<T>::set_data_type(Data_Type dt){
	node_data_type = dt;
	if(dt == int_data_type){
		constant = (int) constant;
	}
	else if(dt == double_data_type){
		constant = (float) constant;
	}
}

template <class T>
bool Number_Ast<T>::is_value_zero(){
	return constant==0;
}

template <class T>
void Number_Ast<T>::print(ostream & file_buffer){
	if(!this->check_ast()) return;
	file_buffer << "Num : " << constant;
}

//////////////////////////////////////////////////////////////////////
//Arithmetic Expr Ast Class



Data_Type Arithmetic_Expr_Ast::get_data_type(){
	return node_data_type;
}

void Arithmetic_Expr_Ast::set_data_type(Data_Type dt){
	node_data_type = dt;
}

bool Arithmetic_Expr_Ast::check_ast(){
	if(!rhs){
		if(lhs->check_ast()){
			return true;
		}
		//exit(-1);
		printf("cs316: Error - sclp error: Arithmetic statement data type not compatible\n");
		return false;
	}
	if(lhs->check_ast() && rhs->check_ast()){
		if(lhs->get_data_type() == rhs->get_data_type())
			return true;
	}

	printf("cs316: Error - sclp error: Arithmetic statement data type not compatible\n");
	//exit(-1);
	return false;
} //todo:

// bool Arithmetic_Expr_Ast::check_ast(){
// 	if(lhs->get_data_type() == rhs->get_data_type())
// 		return true;
	

// 	printf("cs316: Error - sclp error: Arithmetic statement data type not compatible\n");
// 	//exit(-1);
// 	return false;
// } //todo:


void Arithmetic_Expr_Ast::print(ostream & file_buffer){

}
	
//////////////////////////////////////////////////////////////////////
//Plus Ast Class


Plus_Ast::Plus_Ast(Ast * l, Ast * r, int line){
	lhs = l;
	rhs = r;
	lineno = line;
	node_data_type = l->get_data_type();
	//todo: check ast l and r and assign to node_data_type
}


void Plus_Ast::print(ostream & file_buffer){
	if(!this->check_ast()) return;
	file_buffer << "\n" << AST_NODE_SPACE << "Arith: PLUS\n" << AST_SUB_NODE_SPACE << "LHS (";
	lhs->print(file_buffer);
	file_buffer << ")\n"<< AST_SUB_NODE_SPACE << "RHS (";
	rhs->print(file_buffer);
	file_buffer << ")";	
}

//////////////////////////////////////////////////////////////////////
//Minus Ast Class


Minus_Ast::Minus_Ast(Ast * l, Ast * r, int line){
	lhs = l;
	rhs = r;
	lineno = line;
	node_data_type = l->get_data_type();
	//todo: check ast l and r and assign to node_data_type	
}


void Minus_Ast::print(ostream & file_buffer){
	if(!this->check_ast()) return;
	file_buffer << "\n" << AST_NODE_SPACE << "Arith: MINUS\n" << AST_SUB_NODE_SPACE << "LHS (";
	lhs->print(file_buffer);
	file_buffer << ")\n"<< AST_SUB_NODE_SPACE << "RHS (";
	rhs->print(file_buffer);
	file_buffer << ")";		
}




//////////////////////////////////////////////////////////////////////
//Divide Ast Class


Divide_Ast::Divide_Ast(Ast * l, Ast * r, int line){
	lhs = l;
	rhs = r;
	lineno = line;
	node_data_type = l->get_data_type();
	//todo: check ast l and r and assign to node_data_type
}


void Divide_Ast::print(ostream & file_buffer){
	if(!this->check_ast()) return;
	file_buffer << "\n" << AST_NODE_SPACE << "Arith: DIV\n" << AST_SUB_NODE_SPACE << "LHS (";
	lhs->print(file_buffer);
	file_buffer << ")\n"<< AST_SUB_NODE_SPACE << "RHS (";
	rhs->print(file_buffer);
	file_buffer << ")";	
}


//////////////////////////////////////////////////////////////////////
//Mult Ast Class



Mult_Ast::Mult_Ast(Ast * l, Ast * r, int line){
	lhs = l;
	rhs = r;
	lineno = line;
	node_data_type = l->get_data_type();
	//todo: check ast l and r and assign to node_data_type
}


void Mult_Ast::print(ostream & file_buffer){
	if(!this->check_ast()) return;
	file_buffer << "\n" << AST_NODE_SPACE << "Arith: MULT\n" << AST_SUB_NODE_SPACE << "LHS (";
	lhs->print(file_buffer);
	file_buffer << ")\n"<< AST_SUB_NODE_SPACE << "RHS (";
	rhs->print(file_buffer);
	file_buffer << ")";		
}


//////////////////////////////////////////////////////////////////////
//Uminus Ast Class



UMinus_Ast::UMinus_Ast(Ast * l, Ast * r, int line){
	lhs = l;
	rhs = r;
	lineno = line;
	node_data_type = l->get_data_type();
	//todo: check ast l and r and assign to node_data_type
}

void UMinus_Ast::print(ostream & file_buffer){
	if(!this->check_ast()) return;
	file_buffer << "\n" << AST_NODE_SPACE << "Arith: UMINUS\n" << AST_SUB_NODE_SPACE << "LHS (";
	lhs->print(file_buffer);
	file_buffer << ")";			
}


//////////////////////////////////////////////////////////////////////
Conditional_Expression_Ast::Conditional_Expression_Ast(Ast* cond, Ast* l, Ast* r, int line){
	this->cond = cond;
	lhs = l;
	rhs = r;
	lineno = line;
	node_data_type = l->get_data_type();
}

Conditional_Expression_Ast::~Conditional_Expression_Ast(){

}

void Conditional_Expression_Ast::print(ostream & file_buffer){
	if(!this->check_ast()) return;
	file_buffer << "\n" << AST_SPACE << "Cond:\n";
	file_buffer << AST_NODE_SPACE << "IF_ELSE\n";
	cond->print(file_buffer);
	file_buffer <<"\n"<< AST_NODE_SPACE << "LHS (" ;
	lhs->print(file_buffer);
	file_buffer << ")\n";
	file_buffer << AST_NODE_SPACE << "RHS (" ;
	rhs->print(file_buffer);
	file_buffer << ")";

}

// Code_For_Ast & compile();
// Eval_Result & evaluate(Local_Environment & eval_env, ostream & file_buffer);
// Code_For_Ast & compile_and_optimize_ast(Lra_Outcome & lra){}






Relational_Expr_Ast::Relational_Expr_Ast(Ast * lhs, Relational_Op rop, Ast * rhs, int line){
	lhs_condition = lhs;
	rhs_condition = rhs;
	rel_op = rop;
	lineno = line;
	node_data_type = lhs->get_data_type();
}
Relational_Expr_Ast::~Relational_Expr_Ast(){

}

Data_Type Relational_Expr_Ast::get_data_type(){
	return node_data_type;
}
void Relational_Expr_Ast::set_data_type(Data_Type dt){
	node_data_type = dt;
}

bool Relational_Expr_Ast::check_ast(){

	if(this->lhs_condition->check_ast() && this->rhs_condition->check_ast()){
		if(this->lhs_condition->get_data_type() == this->rhs_condition->get_data_type())
			return true;
	}

	printf("cs316: Error - sclp error: Relational expression data type not compatible\n");
	//exit(-1);
	return false;
}

void Relational_Expr_Ast::print(ostream & file_buffer){
	if(rel_op == less_than)
		file_buffer << AST_NODE_SPACE << "Condition: LT\n";
	else if (rel_op == less_equalto)
		file_buffer << AST_NODE_SPACE << "Condition: LE\n";
	else if (rel_op == greater_than)
		file_buffer << AST_NODE_SPACE << "Condition: GT\n";
	else if (rel_op == greater_equalto)
		file_buffer << AST_NODE_SPACE << "Condition: GE\n";
	else if (rel_op == equalto)
		file_buffer << AST_NODE_SPACE << "Condition: EQ\n";
	else if (rel_op == not_equalto)
		file_buffer << AST_NODE_SPACE << "Condition: NE\n";

	file_buffer << AST_SUB_NODE_SPACE << "LHS (" ;
	lhs_condition->print(file_buffer) ;
	file_buffer << ")\n" << AST_SUB_NODE_SPACE << "RHS (" ;
	rhs_condition->print(file_buffer) ;
	file_buffer << ")";

}
// Code_For_Ast & compile();

// Eval_Result & evaluate(Local_Environment & eval_env, ostream & file_buffer);
// Code_For_Ast & compile_and_optimize_ast(Lra_Outcome & lra){}


Logical_Expr_Ast::Logical_Expr_Ast(Ast * lhs, Logical_Op bop, Ast * rhs, int line){
	lhs_op = lhs;
	rhs_op = rhs;
	bool_op = bop;
	lineno = line;
	node_data_type = void_data_type;
}

Logical_Expr_Ast::~Logical_Expr_Ast(){

}

Data_Type Logical_Expr_Ast::get_data_type(){
	return node_data_type;
}

void Logical_Expr_Ast::set_data_type(Data_Type dt){
	node_data_type = dt;
}

bool Logical_Expr_Ast::check_ast(){

	if(bool_op == _logical_not){
		if(this->rhs_op->get_data_type() != void_data_type) return false;
		return this->rhs_op->check_ast();
	}

	if(this->lhs_op->check_ast() && this->rhs_op->check_ast()){
		if(this->lhs_op->get_data_type() == this->rhs_op->get_data_type())
			return true;
	}

	printf("cs316: Error - sclp error: Relational expression data type not compatible\n");
	//exit(-1);
	return false;
}

void Logical_Expr_Ast::print(ostream & file_buffer){
	if(bool_op == _logical_and)
		file_buffer << AST_NODE_SPACE << "Condition: AND\n";
	else if (bool_op == _logical_or)
		file_buffer << AST_NODE_SPACE << "Condition: OR\n";
	else if (bool_op == _logical_not)
		file_buffer << AST_NODE_SPACE << "Condition: NOT\n";

	if(bool_op != _logical_not){
		file_buffer << AST_SUB_NODE_SPACE << "LHS (\n" ;
		lhs_op->print(file_buffer);
		file_buffer << ")\n";
	}
	

		file_buffer << AST_SUB_NODE_SPACE << "RHS (\n" ;
		rhs_op->print(file_buffer);
		file_buffer << ")";
	

}

// Code_For_Ast & compile();
// Eval_Result & evaluate(Local_Environment & eval_env, ostream & file_buffer);
// Code_For_Ast & compile_and_optimize_ast(Lra_Outcome & lra){}



Selection_Statement_Ast::Selection_Statement_Ast(Ast * cond,Ast* then_part, Ast* else_part, int line){
	this->cond = cond;
	this->then_part = then_part;
	this->else_part = else_part;
	lineno = line;
	node_data_type = void_data_type;
}
Selection_Statement_Ast::~Selection_Statement_Ast(){

}

Data_Type Selection_Statement_Ast::get_data_type(){
	return node_data_type;
}
void Selection_Statement_Ast::set_data_type(Data_Type dt){
	node_data_type = dt;
}

bool Selection_Statement_Ast::check_ast(){
	// if(this->lhs->check_ast() && this->rhs->check_ast()){
	// 	if(this->lhs->get_data_type() == this->rhs->get_data_type())
	// 		return true;
	// }
	if( this->cond->check_ast() && this->then_part->check_ast()){
		if(this->else_part) return this->else_part->check_ast();
		return 1;
	}
	printf("cs316: Error - sclp error: Relational expression data type not compatible\n");
	//exit(-1);
	return false;
}

void Selection_Statement_Ast::print(ostream & file_buffer){
	if(!this->check_ast()) return;
	file_buffer << "\n" << AST_SPACE << "IF : \n";
	file_buffer << AST_SPACE << "CONDITION (\n";
	cond->print(file_buffer);
	file_buffer << ")\n" << AST_SPACE << "THEN (";
	then_part->print(file_buffer);
	file_buffer << ")";

	if(else_part){
		file_buffer << "\n" << AST_SPACE << "ELSE (";
		else_part->print(file_buffer);
		file_buffer << ")";
	}

}

// Code_For_Ast & compile();
// Eval_Result & evaluate(Local_Environment & eval_env, ostream & file_buffer);
// Code_For_Ast & compile_and_optimize_ast(Lra_Outcome & lra){}



Iteration_Statement_Ast::Iteration_Statement_Ast(Ast * cond, Ast* body, int line, bool do_form){
	this->cond = cond;
	this->body = body;
	lineno = line;
	is_do_form = do_form;
	node_data_type = void_data_type;
}

Iteration_Statement_Ast::~Iteration_Statement_Ast(){

}

Data_Type Iteration_Statement_Ast::get_data_type(){
	return node_data_type;
}

void Iteration_Statement_Ast::set_data_type(Data_Type dt){
	node_data_type = dt;
}

bool Iteration_Statement_Ast::check_ast(){
	// if(lhs->check_ast() && rhs->check_ast()){
	// 	if(lhs->get_data_type() == rhs->get_data_type())
	// 		return true;
	// }

	if( this->cond->check_ast() && this->body->check_ast()){
		return 1;
	}

	printf("cs316: Error - sclp error: Relational expression data type not compatible\n");
	//exit(-1);
	return false;
}

void Iteration_Statement_Ast::print(ostream & file_buffer){
	if(!this->check_ast()) return;
	if(this->is_do_form){
		file_buffer << "\n" << AST_SPACE << "DO (";
		body->print(file_buffer);
		file_buffer << ")\n";
		file_buffer << AST_SPACE << "WHILE CONDITION (\n" ;
		cond->print(file_buffer);
		file_buffer << ")";

	}
	else{
		file_buffer << "\n" << AST_SPACE << "WHILE : \n";
		file_buffer << AST_SPACE << "CONDITION (\n" ;
		cond->print(file_buffer);
		file_buffer << ")\n" << AST_SPACE << "BODY (" ;
		body->print(file_buffer);
		file_buffer << ")";
	}
}

// Code_For_Ast & compile();
// Eval_Result & evaluate(Local_Environment & eval_env, ostream & file_buffer);
// Code_For_Ast & compile_and_optimize_ast(Lra_Outcome & lra){}



Sequence_Ast::Sequence_Ast(int line){
	lineno = line;
	node_data_type = void_data_type;
}

Sequence_Ast::~Sequence_Ast(){

}

void Sequence_Ast::ast_push_back(Ast * ast){
	statement_list.push_back(ast);
}

void Sequence_Ast::print(ostream & file_buffer){
	
	for (std::list<Ast *>::iterator it=statement_list.begin(); it != statement_list.end(); ++it){
		if(!(*it)->check_ast()) return;
		file_buffer  << "\n" << AST_NODE_SPACE;
		(*it)->print(file_buffer);
	}

}
// Code_For_Ast & compile();
// void print_assembly(ostream & file_buffer);
// void print_icode(ostream & file_buffer);

// Eval_Result & evaluate(Local_Environment & eval_env, ostream & file_buffer);
// Code_For_Ast & compile_and_optimize_ast(Lra_Outcome & lra){}




//Plus Ast Class


Print_Ast::Print_Ast(Ast *v, int line){
	var = v;
	lineno = line;
}
Print_Ast::~Print_Ast(){}

void Print_Ast::print(ostream & file_buffer){}





Return_Ast::Return_Ast(Ast * ret_val, string name, int line){
	return_value = ret_val;
	proc_name = name;
	lineno = line;
	if(ret_val)
		node_data_type = ret_val->get_data_type();
	else
		node_data_type = void_data_type;
}

Return_Ast::~Return_Ast(){

}

Data_Type Return_Ast::get_data_type(){
	return node_data_type;
}

void Return_Ast::print(ostream & file_buffer){

}





Call_Ast::Call_Ast(string name, int line){
	procedure_name = name;
	lineno = line;
	node_data_type = program_object.get_procedure_prototype(name)->get_return_type();

}

Call_Ast::~Call_Ast(){

}

Data_Type Call_Ast::get_data_type(){
	return node_data_type;
}

void Call_Ast::set_register(Register_Descriptor * reg){
	return_value_reg = reg;
}

void Call_Ast::check_actual_formal_param(Symbol_Table & formal_param_list){
	list<Symbol_Table_Entry *> l = formal_param_list.get_table();
	list<Ast *> :: iterator it1 =  actual_param_list.begin();
	list<Symbol_Table_Entry *> :: iterator it2 = l.begin();

	// while(it1!=actual_param_list.end() && it2!=l.end()){
	// 	printf("%d,%d\n",(*it1)->get_data_type() , (*it2)->get_data_type());

	// 	it1++;
	// 	it2++;

	// }

	while(it1!=actual_param_list.end() && it2!=l.end()){
		// printf("%d,%d\n",(*it1)->get_data_type() , (*it2)->get_data_type());
		if((*it1)->get_data_type() != (*it2)->get_data_type()){
			printf("cs316: Error - sclp error: Function parameters not compatible\n");
			//exit(-1);
			return;
		}

		it1++;
		it2++;

	}

	if(it1!=actual_param_list.end() || it2!=l.end() ){
		printf("cs316: Error - sclp error: Function parameters not compatible1\n");
		//exit(-1);
	}
}


void Call_Ast::set_actual_param_list(list<Ast *> & param_list){
	actual_param_list = param_list;
}

void Call_Ast::print(ostream & file_buffer){

}




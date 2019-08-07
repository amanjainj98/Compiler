#include<stdlib.h>




Eval_Result & Ast::get_value_of_evaluation(Local_Environment & eval_env){

}

void Ast::set_value_of_evaluation(Local_Environment & eval_env, Eval_Result & result){

}


void Ast::print_value(Local_Environment & eval_env, ostream & file_buffer){

}

Eval_Result & Assignment_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){
	if(!this->check_ast()){
		printf("cs316: Error");
		exit(0);		//todo
	}

	this->print(file_buffer);

	if(this->lhs->get_data_type() == int_data_type){
		Eval_Result *er = new Eval_Result_Value_Int();
		er = & this->rhs->evaluate(eval_env,file_buffer);
		if(this->lhs->get_symbol_entry().get_symbol_scope() == local) this->lhs->set_value_of_evaluation(eval_env,*er);
		else this->lhs->set_value_of_evaluation(interpreter_global_table,*er);
		file_buffer<<"\n"<<VAR_SPACE<<this->lhs->get_symbol_entry().get_variable_name()<<" : "<<er->get_int_value()<<"\n\n";
		return *er;
	}

	else if(this->lhs->get_data_type() == double_data_type){
		Eval_Result *er = new Eval_Result_Value_Double();
		er = & this->rhs->evaluate(eval_env,file_buffer);
		if(this->lhs->get_symbol_entry().get_symbol_scope() == local) this->lhs->set_value_of_evaluation(eval_env,*er);
		else this->lhs->set_value_of_evaluation(interpreter_global_table,*er);
		file_buffer<<"\n"<<VAR_SPACE<<this->lhs->get_symbol_entry().get_variable_name()<<" : "<<er->get_double_value()<<"\n\n";
		return *er;
	}

	else{
		//todo
		exit(0);
	}
	
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Name_Ast::print_value(Local_Environment & eval_env, ostream & file_buffer){
	//todo
}

Eval_Result & Name_Ast::get_value_of_evaluation(Local_Environment & eval_env){
	return * eval_env.get_variable_value(this->get_symbol_entry().get_variable_name());
}

void Name_Ast::set_value_of_evaluation(Local_Environment & eval_env, Eval_Result & result){
	eval_env.put_variable_value(result,this->get_symbol_entry().get_variable_name());
}

Eval_Result & Name_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){

	if(!this->check_ast()){
		printf("cs316: Error");
		exit(0);		//todo
	}

	if(this->get_data_type() == int_data_type){
		Eval_Result *er = new Eval_Result_Value_Int();
		if(this->get_symbol_entry().get_symbol_scope() == local) er = (eval_env.get_variable_value(this->get_symbol_entry().get_variable_name()));
		else er = (interpreter_global_table.get_variable_value(this->get_symbol_entry().get_variable_name()));
		return *er;
	}

	else if(this->get_data_type() == double_data_type){
		Eval_Result *er = new Eval_Result_Value_Double();
		if(this->get_symbol_entry().get_symbol_scope() == local) er =  eval_env.get_variable_value(this->get_symbol_entry().get_variable_name());
		else er = (interpreter_global_table.get_variable_value(this->get_symbol_entry().get_variable_name()));
		return *er;
	}

	else{
		//todo
		exit(0);
	}

}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////


template class Number_Ast<double>;
template class Number_Ast<int>;

template <class T>
Eval_Result & Number_Ast<T>::evaluate(Local_Environment & eval_env, ostream & file_buffer){

	if(!this->check_ast()){
		printf("cs316: Error");
		exit(0);		//todo
	}

	if(this->get_data_type() == int_data_type){
		Eval_Result *er = new Eval_Result_Value_Int();
		er->set_value(this->constant);
		er->set_result_enum(int_result);
		return *er;
	}

	else if(this->get_data_type() == double_data_type){
		Eval_Result *er = new Eval_Result_Value_Double();
		er->set_value(this->constant);
		er->set_result_enum(double_result);
		return *er;
	}

	else{
		//todo
		exit(0);
	}


}





Eval_Result & Plus_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){

	if(!this->check_ast()){
		printf("cs316: Error");
		exit(0);		//todo
	}

	if(this->lhs->get_data_type() == int_data_type){
		Eval_Result *er1 = new Eval_Result_Value_Int();
		Eval_Result *er2 = new Eval_Result_Value_Int();
		er1 = & this->lhs->evaluate(eval_env,file_buffer);
		er2 = & this->rhs->evaluate(eval_env,file_buffer);

		Eval_Result *er = new Eval_Result_Value_Int();
		er->set_value(er1->get_int_value() + er2->get_int_value());
		er->set_result_enum(int_result);
		return *er;
	}

	else if(this->lhs->get_data_type() == double_data_type){
		Eval_Result *er1 = new Eval_Result_Value_Double();
		Eval_Result *er2 = new Eval_Result_Value_Double();
		er1 = & this->lhs->evaluate(eval_env,file_buffer);
		er2 = & this->rhs->evaluate(eval_env,file_buffer);

		Eval_Result *er = new Eval_Result_Value_Double();
		er->set_value(er1->get_double_value() + er2->get_double_value());
		er->set_result_enum(double_result);
		return *er;
	}

	else{
		//todo
		exit(0);
	}

}




Eval_Result & Minus_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){
	if(!this->check_ast()){
		printf("cs316: Error");
		exit(0);		//todo
	}

	if(this->lhs->get_data_type() == int_data_type){
		Eval_Result *er1 = new Eval_Result_Value_Int();
		Eval_Result *er2 = new Eval_Result_Value_Int();
		er1 = & this->lhs->evaluate(eval_env,file_buffer);
		er2 = & this->rhs->evaluate(eval_env,file_buffer);

		Eval_Result *er = new Eval_Result_Value_Int();
		er->set_value(er1->get_int_value() - er2->get_int_value());
		er->set_result_enum(int_result);
		return *er;
	}

	else if(this->lhs->get_data_type() == double_data_type){
		Eval_Result *er1 = new Eval_Result_Value_Double();
		Eval_Result *er2 = new Eval_Result_Value_Double();
		er1 = & this->lhs->evaluate(eval_env,file_buffer);
		er2 = & this->rhs->evaluate(eval_env,file_buffer);

		Eval_Result *er = new Eval_Result_Value_Double();
		er->set_value(er1->get_double_value() - er2->get_double_value());
		er->set_result_enum(double_result);
		return *er;
	}

	else{
		//todo
		exit(0);
	}
}




Eval_Result & Divide_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){
	if(!this->check_ast()){
		printf("cs316: Error");
		exit(0);		//todo
	}

	if(this->lhs->get_data_type() == int_data_type){
		Eval_Result *er1 = new Eval_Result_Value_Int();
		Eval_Result *er2 = new Eval_Result_Value_Int();
		er1 = & this->lhs->evaluate(eval_env,file_buffer);
		er2 = & this->rhs->evaluate(eval_env,file_buffer);

		if(er2->get_int_value() == 0) {
			printf("cs316: Error - sclp error: Divide by 0\n");
			exit(-1);
		}

		Eval_Result *er = new Eval_Result_Value_Int();
		er->set_value(er1->get_int_value() / er2->get_int_value());
		er->set_result_enum(int_result);
		return *er;
	}

	else if(this->lhs->get_data_type() == double_data_type){
		Eval_Result *er1 = new Eval_Result_Value_Double();
		Eval_Result *er2 = new Eval_Result_Value_Double();
		er1 = & this->lhs->evaluate(eval_env,file_buffer);
		er2 = & this->rhs->evaluate(eval_env,file_buffer);

		if(er2->get_int_value() == 0.0) {
			printf("cs316: Error - sclp error: Divide by 0\n");
			exit(-1);
		}

		Eval_Result *er = new Eval_Result_Value_Double();
		er->set_value(er1->get_double_value() / er2->get_double_value());
		er->set_result_enum(double_result);
		return *er;
	}

	else{
		//todo
		exit(0);
	}
}





Eval_Result & Mult_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){
	if(!this->check_ast()){
		printf("cs316: Error");
		exit(0);		//todo
	}

	if(this->lhs->get_data_type() == int_data_type){
		Eval_Result *er1 = new Eval_Result_Value_Int();
		Eval_Result *er2 = new Eval_Result_Value_Int();
		er1 = & this->lhs->evaluate(eval_env,file_buffer);
		er2 = & this->rhs->evaluate(eval_env,file_buffer);

		Eval_Result *er = new Eval_Result_Value_Int();
		er->set_value(er1->get_int_value() * er2->get_int_value());
		er->set_result_enum(int_result);
		return *er;
	}

	else if(this->lhs->get_data_type() == double_data_type){
		Eval_Result *er1 = new Eval_Result_Value_Double();
		Eval_Result *er2 = new Eval_Result_Value_Double();
		er1 = & this->lhs->evaluate(eval_env,file_buffer);
		er2 = & this->rhs->evaluate(eval_env,file_buffer);

		Eval_Result *er = new Eval_Result_Value_Double();
		er->set_value(er1->get_double_value() * er2->get_double_value());
		er->set_result_enum(double_result);
		return *er;
	}

	else{
		//todo
		exit(0);
	}
}





Eval_Result & UMinus_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){
	if(!this->check_ast()){
		printf("cs316: Error");
		exit(0);		//todo
	}
	if(this->lhs->get_data_type() == int_data_type){
		Eval_Result *er1 = new Eval_Result_Value_Int();
		er1 = & this->lhs->evaluate(eval_env,file_buffer);


		Eval_Result *er = new Eval_Result_Value_Int();
		er->set_value(-1 * er1->get_int_value());
		er->set_result_enum(int_result);
		return *er;
	}

	else if(this->lhs->get_data_type() == double_data_type){

		Eval_Result *er1 = new Eval_Result_Value_Double();

		er1 = & this->lhs->evaluate(eval_env,file_buffer);
		Eval_Result *er = new Eval_Result_Value_Double();
		er->set_value(-1.0 * er1->get_double_value());
		er->set_result_enum(double_result);
		return *er;
	}

	else{
		//todo
		exit(0);
	}
}




Eval_Result & Conditional_Expression_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){

	if(!this->check_ast()){
		printf("cs316: Error");
		exit(0);		//todo
	}

	if(this->lhs->get_data_type() == int_data_type){
		Eval_Result *er1 = new Eval_Result_Value_Int();
		Eval_Result *er2 = new Eval_Result_Value_Int();
		er1 = & this->lhs->evaluate(eval_env,file_buffer);
		er2 = & this->rhs->evaluate(eval_env,file_buffer);

		Eval_Result *condition = new Eval_Result_Value_Int();
		condition = & this->cond->evaluate(eval_env,file_buffer);
		int t = condition->get_int_value();

		Eval_Result *er = new Eval_Result_Value_Int();

		if(t==1){
			er->set_value(er1->get_int_value());
			er->set_result_enum(int_result);
		}
		else{
			er->set_value(er2->get_int_value());
			er->set_result_enum(int_result);
		}

		return *er;

	}

	else if(this->lhs->get_data_type() == double_data_type){
		Eval_Result *er1 = new Eval_Result_Value_Double();
		Eval_Result *er2 = new Eval_Result_Value_Double();
		er1 = & this->lhs->evaluate(eval_env,file_buffer);
		er2 = & this->rhs->evaluate(eval_env,file_buffer);

		Eval_Result *condition = new Eval_Result_Value_Int();
		condition = & this->cond->evaluate(eval_env,file_buffer);
		int t = condition->get_int_value();

		Eval_Result *er = new Eval_Result_Value_Double();

		if(t==1){
			er->set_value(er1->get_double_value());
			er->set_result_enum(double_result);
		}
		else{
			er->set_value(er2->get_double_value());
			er->set_result_enum(double_result);
		}

		return *er;
	}

	else{
		//todo
		exit(0);
	}
}






Eval_Result & Relational_Expr_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){

	if(!this->check_ast()){
		printf("cs316: Error");
		exit(0);		//todo
	}

	if(this->lhs_condition->get_data_type() == int_data_type){
		Eval_Result *er1 = new Eval_Result_Value_Int();
		Eval_Result *er2 = new Eval_Result_Value_Int();
		er1 = & this->lhs_condition->evaluate(eval_env,file_buffer);
		er2 = & this->rhs_condition->evaluate(eval_env,file_buffer);


		Eval_Result *er = new Eval_Result_Value_Int();

		switch(this->rel_op){
			case less_equalto : 
				if(er1->get_int_value() <= er2->get_int_value()){
					er->set_value(1);
					er->set_result_enum(int_result);
				}
				else{
					er->set_value(0);
					er->set_result_enum(int_result);
				}
				break;
			
			case less_than : 
				if(er1->get_int_value() < er2->get_int_value()){
					er->set_value(1);
					er->set_result_enum(int_result);
				}
				else{
					er->set_value(0);
					er->set_result_enum(int_result);
				}
				break;
			
			case greater_than : 
				if(er1->get_int_value() > er2->get_int_value()){
					er->set_value(1);
					er->set_result_enum(int_result);
				}
				else{
					er->set_value(0);
					er->set_result_enum(int_result);
				}
				break;
			
			case greater_equalto : 
				if(er1->get_int_value() >= er2->get_int_value()){
					er->set_value(1);
					er->set_result_enum(int_result);
				}
				else{
					er->set_value(0);
					er->set_result_enum(int_result);
				}
				break;
			
			case equalto : 
				if(er1->get_int_value() == er2->get_int_value()){
					er->set_value(1);
					er->set_result_enum(int_result);
				}
				else{
					er->set_value(0);
					er->set_result_enum(int_result);
				}
				break;
			
			case not_equalto : 
				if(er1->get_int_value() != er2->get_int_value()){
					er->set_value(1);
					er->set_result_enum(int_result);
				}
				else{
					er->set_value(0);
					er->set_result_enum(int_result);
				}
				break;
		}


		return *er;

	}

	else if(this->lhs_condition->get_data_type() == double_data_type){
		Eval_Result *er1 = new Eval_Result_Value_Double();
		Eval_Result *er2 = new Eval_Result_Value_Double();
		er1 = & this->lhs_condition->evaluate(eval_env,file_buffer);
		er2 = & this->rhs_condition->evaluate(eval_env,file_buffer);

		Eval_Result *er = new Eval_Result_Value_Int();

		switch(this->rel_op){
			case less_equalto : 
				if(er1->get_double_value() <= er2->get_double_value()){
					er->set_value(1);
					er->set_result_enum(int_result);
				}
				else{
					er->set_value(0);
					er->set_result_enum(int_result);
				}
				break;
			
			case less_than : 
				if(er1->get_double_value() < er2->get_double_value()){
					er->set_value(1);
					er->set_result_enum(int_result);
				}
				else{
					er->set_value(0);
					er->set_result_enum(int_result);
				}
				break;
			
			case greater_than : 
				if(er1->get_double_value() > er2->get_double_value()){
					er->set_value(1);
					er->set_result_enum(int_result);
				}
				else{
					er->set_value(0);
					er->set_result_enum(int_result);
				}
				break;
			
			case greater_equalto : 
				if(er1->get_double_value() >= er2->get_double_value()){
					er->set_value(1);
					er->set_result_enum(int_result);
				}
				else{
					er->set_value(0);
					er->set_result_enum(int_result);
				}
				break;
			
			case equalto : 
				if(er1->get_double_value() == er2->get_double_value()){
					er->set_value(1);
					er->set_result_enum(int_result);
				}
				else{
					er->set_value(0);
					er->set_result_enum(int_result);
				}
				break;
			
			case not_equalto : 
				if(er1->get_double_value() != er2->get_double_value()){
					er->set_value(1);
					er->set_result_enum(int_result);
				}
				else{
					er->set_value(0);
					er->set_result_enum(int_result);
				}break;
		}

		return *er;
	}

	else{
		//todo
		exit(0);
	}

}



Eval_Result & Logical_Expr_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){

	if(!this->check_ast()){
		printf("cs316: Error");
		exit(0);		//todo
	}


	Eval_Result *er1 = new Eval_Result_Value_Int();
	Eval_Result *er2 = new Eval_Result_Value_Int();
	er1 = & this->lhs_op->evaluate(eval_env,file_buffer);
	er2 = & this->rhs_op->evaluate(eval_env,file_buffer);

	Eval_Result *er = new Eval_Result_Value_Int();

	switch(this->bool_op){
		case _logical_not :
			if(!er2->get_int_value()){
				er->set_value(1);
				er->set_result_enum(int_result);
			}
			else{
				er->set_value(0);
				er->set_result_enum(int_result);
			}
			break;
		
		case _logical_or :
			if(er1->get_int_value() || er2->get_int_value()){
				er->set_value(1);
				er->set_result_enum(int_result);
			}
			else{
				er->set_value(0);
				er->set_result_enum(int_result);
			}
			break;
		
		case _logical_and :
			if(er1->get_int_value() && er2->get_int_value()){
				er->set_value(1);
				er->set_result_enum(int_result);
			}
			else{
				er->set_value(0);
				er->set_result_enum(int_result);
			}
			break;

	}

	return *er;


}



Eval_Result & Selection_Statement_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){

	if(!this->check_ast()){
		printf("cs316: Error");
		exit(0);		//todo
	}

	Eval_Result *condition = new Eval_Result_Value_Int();
	condition = & this->cond->evaluate(eval_env,file_buffer);

	if(condition->get_int_value() == 1){
		this->then_part->evaluate(eval_env,file_buffer);
	}
	else{
		if(this->else_part)
			this->else_part->evaluate(eval_env,file_buffer);
	}

	Eval_Result *er = new Eval_Result_Value_Int();
	er->set_value(1);
	er->set_result_enum(int_result);
	return *er;

}




Eval_Result & Iteration_Statement_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){

	if(!this->check_ast()){
		//todo
		printf("cs316: Error");
		exit(0);
	}

	if(this->is_do_form){
		do{
			this->body->evaluate(eval_env,file_buffer);
		}while(this->cond->evaluate(eval_env,file_buffer).get_int_value() == 1);
	}
	else{
		while(this->cond->evaluate(eval_env,file_buffer).get_int_value() == 1){
			this->body->evaluate(eval_env,file_buffer);
		}
	}

	Eval_Result *er = new Eval_Result_Value_Int();
	er->set_value(1);
	er->set_result_enum(int_result);
	return *er;
}




Eval_Result & Sequence_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){
	if(!this->check_ast()){
		//todo
		printf("cs316: Error");
		exit(0);
	}
	//this->print(file_buffer);

	if(statement_list.empty()){
		printf("cs316: Error - sclp error: Block of statements cannot be empty\n");

	}

	std::list<Ast *>::iterator it;
	for (it = this->statement_list.begin(); it != this->statement_list.end(); ++it){
		(*it)->evaluate(eval_env,file_buffer);
	}

	Eval_Result *er = new Eval_Result_Value_Int();
	er->set_value(1);
	er->set_result_enum(int_result);
	return *er;

}



// Eval_Result & Print_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){
// 	// todo
// 	Eval_Result *er = new Eval_Result_Value_Int();
// 	er->set_value(1);
// 	er->set_result_enum(int_result);
// 	return *er;
// }


Eval_Result & Return_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){

}

Eval_Result & Call_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){

}
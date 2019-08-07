#include<stdlib.h>

Code_For_Ast & Ast::create_store_stmt(Register_Descriptor * store_register){

}

Code_For_Ast & Assignment_Ast::compile(){
	Code_For_Ast crhs = this->rhs->compile();
	Ics_Opd *orhs = new Register_Addr_Opd(crhs.get_reg());
	Ics_Opd *olhs = new Mem_Addr_Opd(this->lhs->get_symbol_entry());
	Icode_Stmt *i;
	if(this->rhs->get_data_type() == int_data_type)
		i =  new Move_IC_Stmt(store,orhs,olhs);
	else
		i =  new Move_IC_Stmt(store_d,orhs,olhs);

	Code_For_Ast *c = new Code_For_Ast();
	*c = crhs;
	c->append_ics(*i);

	crhs.get_reg()->reset_register_occupied();

	return *c;
}


Code_For_Ast & Assignment_Ast::compile_and_optimize_ast(Lra_Outcome & lra){

}

Code_For_Ast & Name_Ast::compile(){

	Register_Descriptor *r;
	if(this->get_data_type() == int_data_type)
		r = machine_desc_object.get_new_register<int_reg>();
	else
		r = machine_desc_object.get_new_register<float_reg>();

	Ics_Opd *orhs = new Register_Addr_Opd(r);
	Ics_Opd *olhs = new Mem_Addr_Opd(this->get_symbol_entry());	
	Icode_Stmt *i;
	if(this->get_data_type() == int_data_type)
		i = new Move_IC_Stmt(load,olhs,orhs);
	else
		i = new Move_IC_Stmt(load_d,olhs,orhs);

	Code_For_Ast *c = new Code_For_Ast();
	c->append_ics(*i);
	c->set_reg(r);

	return *c;
}

Code_For_Ast & Name_Ast::compile_and_optimize_ast(Lra_Outcome & lra){

}

Code_For_Ast & Name_Ast::create_store_stmt(Register_Descriptor * store_register){
	//todo
}

template class Number_Ast<double>;
template class Number_Ast<int>;

template <class T>

Code_For_Ast & Number_Ast<T>::compile(){
	Register_Descriptor *r;
	if(this->get_data_type() == int_data_type)
		r = machine_desc_object.get_new_register<int_reg>();
	else
		r = machine_desc_object.get_new_register<float_reg>();
	Ics_Opd *orhs = new Register_Addr_Opd(r);
	Ics_Opd *olhs = new Const_Opd<T>(this->constant);	
	Icode_Stmt *i;
	if(this->get_data_type() == int_data_type)
		i = new Move_IC_Stmt(imm_load,olhs,orhs);
	else
		i = new Move_IC_Stmt(imm_load_d,olhs,orhs);

	Code_For_Ast *c = new Code_For_Ast();
	c->append_ics(*i);
	c->set_reg(r);

	return *c;
}
template <class T>
Code_For_Ast & Number_Ast<T>::compile_and_optimize_ast(Lra_Outcome & lra){

}


Code_For_Ast & Plus_Ast::compile(){
	Code_For_Ast clhs = this->lhs->compile();
	Code_For_Ast crhs = this->rhs->compile();
	Register_Descriptor *r;
	if(this->get_data_type() == int_data_type)
		r = machine_desc_object.get_new_register<int_reg>();
	else
		r = machine_desc_object.get_new_register<float_reg>();
	Ics_Opd *ores = new Register_Addr_Opd(r);
	Ics_Opd *olhs = new Register_Addr_Opd(clhs.get_reg());
	Ics_Opd *orhs = new Register_Addr_Opd(crhs.get_reg());
	Code_For_Ast *c = new Code_For_Ast();
	*c = clhs;
	list<Icode_Stmt *>::iterator it = crhs.get_icode_list().begin();
	for(;it != crhs.get_icode_list().end();++it){
		c->append_ics(*(*it));
	}
	if(this->get_data_type() == int_data_type){
		Icode_Stmt *i = new Compute_IC_Stmt(add,olhs,orhs,ores);
		c->append_ics(*i);
	}
	else{
		Icode_Stmt *i = new Compute_IC_Stmt(add_d,olhs,orhs,ores);
		c->append_ics(*i);
	}

	c->set_reg(r);
	clhs.get_reg()->reset_register_occupied();
	crhs.get_reg()->reset_register_occupied();

	return *c;

}


Code_For_Ast & Plus_Ast::compile_and_optimize_ast(Lra_Outcome & lra){

}

Code_For_Ast & Minus_Ast::compile(){
	Code_For_Ast clhs = this->lhs->compile();
	Code_For_Ast crhs = this->rhs->compile();
	Register_Descriptor *r;
	if(this->get_data_type() == int_data_type)
		r = machine_desc_object.get_new_register<int_reg>();
	else
		r = machine_desc_object.get_new_register<float_reg>();
	Ics_Opd *ores = new Register_Addr_Opd(r);
	Ics_Opd *olhs = new Register_Addr_Opd(clhs.get_reg());
	Ics_Opd *orhs = new Register_Addr_Opd(crhs.get_reg());
	Code_For_Ast *c = new Code_For_Ast();
	*c = clhs;
	list<Icode_Stmt *>::iterator it = crhs.get_icode_list().begin();
	for(;it != crhs.get_icode_list().end();++it){
		c->append_ics(*(*it));
	}
	if(this->get_data_type() == int_data_type){
		Icode_Stmt *i = new Compute_IC_Stmt(sub,olhs,orhs,ores);
		c->append_ics(*i);
	}
	else{
		Icode_Stmt *i = new Compute_IC_Stmt(sub_d,olhs,orhs,ores);
		c->append_ics(*i);
	}

	c->set_reg(r);
	clhs.get_reg()->reset_register_occupied();
	crhs.get_reg()->reset_register_occupied();

	return *c;
}
Code_For_Ast & Minus_Ast::compile_and_optimize_ast(Lra_Outcome & lra){

}

Code_For_Ast & Divide_Ast::compile(){
	Code_For_Ast clhs = this->lhs->compile();
	Code_For_Ast crhs = this->rhs->compile();
	Register_Descriptor *r;
	if(this->get_data_type() == int_data_type)
		r = machine_desc_object.get_new_register<int_reg>();
	else
		r = machine_desc_object.get_new_register<float_reg>();
	Ics_Opd *ores = new Register_Addr_Opd(r);
	Ics_Opd *olhs = new Register_Addr_Opd(clhs.get_reg());
	Ics_Opd *orhs = new Register_Addr_Opd(crhs.get_reg());
	Code_For_Ast *c = new Code_For_Ast();
	*c = clhs;
	list<Icode_Stmt *>::iterator it = crhs.get_icode_list().begin();
	for(;it != crhs.get_icode_list().end();++it){
		c->append_ics(*(*it));
	}
	if(this->get_data_type() == int_data_type){
		Icode_Stmt *i = new Compute_IC_Stmt(divd,olhs,orhs,ores);
		c->append_ics(*i);
	}
	else{
		Icode_Stmt *i = new Compute_IC_Stmt(div_d,olhs,orhs,ores);
		c->append_ics(*i);
	}

	c->set_reg(r);
	clhs.get_reg()->reset_register_occupied();
	crhs.get_reg()->reset_register_occupied();

	return *c;
}
Code_For_Ast & Divide_Ast::compile_and_optimize_ast(Lra_Outcome & lra){

}

Code_For_Ast & Mult_Ast::compile(){
	Code_For_Ast clhs = this->lhs->compile();
	Code_For_Ast crhs = this->rhs->compile();
	Register_Descriptor *r;
	if(this->get_data_type() == int_data_type)
		r = machine_desc_object.get_new_register<int_reg>();
	else
		r = machine_desc_object.get_new_register<float_reg>();
	Ics_Opd *ores = new Register_Addr_Opd(r);
	Ics_Opd *olhs = new Register_Addr_Opd(clhs.get_reg());
	Ics_Opd *orhs = new Register_Addr_Opd(crhs.get_reg());
	Code_For_Ast *c = new Code_For_Ast();
	*c = clhs;
	list<Icode_Stmt *>::iterator it = crhs.get_icode_list().begin();
	for(;it != crhs.get_icode_list().end();++it){
		c->append_ics(*(*it));
	}
	if(this->get_data_type() == int_data_type){
		Icode_Stmt *i = new Compute_IC_Stmt(mult,olhs,orhs,ores);
		c->append_ics(*i);
	}
	else{
		Icode_Stmt *i = new Compute_IC_Stmt(mult_d,olhs,orhs,ores);
		c->append_ics(*i);
	}

	c->set_reg(r);
	clhs.get_reg()->reset_register_occupied();
	crhs.get_reg()->reset_register_occupied();

	return *c;
}
Code_For_Ast & Mult_Ast::compile_and_optimize_ast(Lra_Outcome & lra){

}

Code_For_Ast & UMinus_Ast::compile(){
	Code_For_Ast clhs = this->lhs->compile();
	Register_Descriptor *r;
	if(this->get_data_type() == int_data_type)
		r = machine_desc_object.get_new_register<int_reg>();
	else
		r = machine_desc_object.get_new_register<float_reg>();
	Ics_Opd *ores = new Register_Addr_Opd(r);
	Ics_Opd *olhs = new Register_Addr_Opd(clhs.get_reg());
	Code_For_Ast *c = new Code_For_Ast();
	*c = clhs;

	if(this->get_data_type() == int_data_type){
		Icode_Stmt *i = new Compute_IC_Stmt(uminus,olhs,NULL,ores);
		c->append_ics(*i);
	}
	else{
		Icode_Stmt *i = new Compute_IC_Stmt(uminus_d,olhs,NULL,ores);
		c->append_ics(*i);
	}

	c->set_reg(r);
	clhs.get_reg()->reset_register_occupied();

	return *c;
}
Code_For_Ast & UMinus_Ast::compile_and_optimize_ast(Lra_Outcome & lra){

}



Code_For_Ast & Conditional_Expression_Ast::compile(){
	Code_For_Ast ccond = this->cond->compile();
	Code_For_Ast *c = new Code_For_Ast();
	*c = ccond;


	Ics_Opd *o = new Register_Addr_Opd(ccond.get_reg());
	string label0 = get_new_label();
	Icode_Stmt *i =  new Control_Flow_IC_Stmt(beq,o,NULL,label0);
	c->append_ics(*i);


	Code_For_Ast cthen = this->lhs->compile();
	Code_For_Ast celse = this->rhs->compile();
	Register_Descriptor *r;

	if(this->lhs->get_data_type() == int_data_type)
		r = machine_desc_object.get_new_register<int_reg>();
	else
		r = machine_desc_object.get_new_register<float_reg>();

	Ics_Opd *ores = new Register_Addr_Opd(r);

	list<Icode_Stmt *>::iterator it = cthen.get_icode_list().begin();
	for(;it != cthen.get_icode_list().end();++it){
		c->append_ics(*(*it));
	}

	Register_Addr_Opd *zeroreg = new Register_Addr_Opd(machine_desc_object.spim_register_table[zero]);

	Ics_Opd *othen = new Register_Addr_Opd(cthen.get_reg());
	Icode_Stmt *i0 = new Compute_IC_Stmt(or_t,othen,zeroreg,ores);
	c->append_ics(*i0);


	string label1 = get_new_label();
	Icode_Stmt *i1 = new Label_IC_Stmt(j,label1);
	c->append_ics(*i1);

	// append the stmt label0: 
	Icode_Stmt *i2 = new Label_IC_Stmt(label,label0);
	c->append_ics(*i2);

	

	it = celse.get_icode_list().begin();
	for(;it != celse.get_icode_list().end();++it){
		c->append_ics(*(*it));
	}

	Ics_Opd *oelse = new Register_Addr_Opd(celse.get_reg());
	Icode_Stmt *i4 = new Compute_IC_Stmt(or_t,oelse,zeroreg,ores);
	c->append_ics(*i4);
	// append the stmt label1: 
	Icode_Stmt *i3 = new Label_IC_Stmt(label,label1);
	c->append_ics(*i3);
	ccond.get_reg()->reset_register_occupied();
	cthen.get_reg()->reset_register_occupied();
	celse.get_reg()->reset_register_occupied();

	c->set_reg(r);


	return *c;
}




int x = -1;

Code_For_Ast & Relational_Expr_Ast::compile(){
	Code_For_Ast clhs = this->lhs_condition->compile();
	Code_For_Ast crhs = this->rhs_condition->compile();
	Register_Descriptor *r;
	if(this->lhs_condition->get_data_type() == int_data_type)
		r = machine_desc_object.get_new_register<int_reg>();
	else
		r = machine_desc_object.get_new_register<float_reg>();
	Ics_Opd *ores = new Register_Addr_Opd(r);
	Ics_Opd *olhs = new Register_Addr_Opd(clhs.get_reg());
	Ics_Opd *orhs = new Register_Addr_Opd(crhs.get_reg());
	Code_For_Ast *c = new Code_For_Ast();
	*c = clhs;
	list<Icode_Stmt *>::iterator it = crhs.get_icode_list().begin();
	for(;it != crhs.get_icode_list().end();++it){
		c->append_ics(*(*it));
	}
	Icode_Stmt *i;
	switch(this->rel_op){
		case less_equalto : 
			if(this->lhs_condition->get_data_type() == int_data_type)
				i = new Compute_IC_Stmt(sle,olhs,orhs,ores);
			else
				i = new Compute_IC_Stmt(sle_d,olhs,orhs,NULL);

			x=2;

			c->append_ics(*i);
			break;
		
		case less_than : 
			if(this->lhs_condition->get_data_type() == int_data_type)
				i = new Compute_IC_Stmt(slt,olhs,orhs,ores);
			else
				i = new Compute_IC_Stmt(slt_d,olhs,orhs,NULL);

			x=1;

			c->append_ics(*i);
			break;
		
		case greater_than : 
			if(this->lhs_condition->get_data_type() == int_data_type)
				i = new Compute_IC_Stmt(sgt,olhs,orhs,ores);
			else
				i = new Compute_IC_Stmt(sgt_d,olhs,orhs,NULL);
			x=3;

			c->append_ics(*i);
			break;
		
		case greater_equalto : 
			if(this->lhs_condition->get_data_type() == int_data_type)
				i = new Compute_IC_Stmt(sge,olhs,orhs,ores);
			else
				i = new Compute_IC_Stmt(sge_d,olhs,orhs,NULL);
			x=4;

			c->append_ics(*i);
			break;
		
		case equalto : 
			if(this->lhs_condition->get_data_type() == int_data_type)
				i = new Compute_IC_Stmt(seq,olhs,orhs,ores);
			else
				i = new Compute_IC_Stmt(seq_d,olhs,orhs,NULL);
			x=5;

			c->append_ics(*i);
			break;
		
		case not_equalto : 
			if(this->lhs_condition->get_data_type() == int_data_type)
				i = new Compute_IC_Stmt(sne,olhs,orhs,ores);
			else
				i = new Compute_IC_Stmt(sne_d,olhs,orhs,NULL);

			x=6;

			c->append_ics(*i);
			break;
	}


	c->set_reg(r);
	clhs.get_reg()->reset_register_occupied();
	crhs.get_reg()->reset_register_occupied();

	return *c;	
}

Code_For_Ast & Logical_Expr_Ast::compile(){



	Register_Descriptor *r;

	Code_For_Ast clhs;
	Code_For_Ast crhs;
	Ics_Opd *olhs;
	Ics_Opd *orhs;
	
	Code_For_Ast *c = new Code_For_Ast();
	
	Icode_Stmt *i;
	Register_Descriptor * r1;
	Ics_Opd * one;
	Move_IC_Stmt * m1;
	Ics_Opd *ores;
	list<Icode_Stmt *>::iterator it;
	list<Icode_Stmt *>::iterator it1;
	switch(this->bool_op){
		case _logical_not :
			r1 = machine_desc_object.get_new_register<int_reg>();
			orhs = new Register_Addr_Opd(r1);
			one = new Const_Opd<int>(1);
			m1 = new Move_IC_Stmt(imm_load,one, orhs);
			c->append_ics(*m1);


			clhs = this->rhs_op->compile();
			olhs = new Register_Addr_Opd(clhs.get_reg());

			r = machine_desc_object.get_new_register<int_reg>();
			
			ores = new Register_Addr_Opd(r);
			
			i = new Compute_IC_Stmt(not_t,olhs,orhs,ores);


			it = clhs.get_icode_list().begin();
			for(;it != clhs.get_icode_list().end();++it){
				c->append_ics(*(*it));
			}


			c->append_ics(*i);

			c->set_reg(r);
			clhs.get_reg()->reset_register_occupied();

			r1->reset_register_occupied();
			break;
		
		case _logical_or :

			clhs = this->lhs_op->compile();
			crhs = this->rhs_op->compile();
			olhs = new Register_Addr_Opd(clhs.get_reg());
			orhs = new Register_Addr_Opd(crhs.get_reg());

			r = machine_desc_object.get_new_register<int_reg>();
			ores = new Register_Addr_Opd(r);
			i = new Compute_IC_Stmt(or_t,olhs,orhs,ores);

			it = clhs.get_icode_list().begin();
			for(;it != clhs.get_icode_list().end();++it){
				c->append_ics(*(*it));
			}

			it1 = crhs.get_icode_list().begin();
			for(;it1 != crhs.get_icode_list().end();++it1){
				c->append_ics(*(*it1));
			}


			c->append_ics(*i);

			c->set_reg(r);
			clhs.get_reg()->reset_register_occupied();

			crhs.get_reg()->reset_register_occupied();

			break;
		
		case _logical_and :
			clhs = this->lhs_op->compile();
			crhs = this->rhs_op->compile();
			olhs = new Register_Addr_Opd(clhs.get_reg());
			orhs = new Register_Addr_Opd(crhs.get_reg());

			r = machine_desc_object.get_new_register<int_reg>();		
			ores = new Register_Addr_Opd(r);
			i = new Compute_IC_Stmt(and_t,olhs,orhs,ores);

			it = clhs.get_icode_list().begin();
			for(;it != clhs.get_icode_list().end();++it){
				c->append_ics(*(*it));
			}

			it1 = crhs.get_icode_list().begin();
			for(;it1 != crhs.get_icode_list().end();++it1){
				c->append_ics(*(*it1));
			}

			c->append_ics(*i);

			c->set_reg(r);
			clhs.get_reg()->reset_register_occupied();

			crhs.get_reg()->reset_register_occupied();

			break;

	}


	return *c;
}

Code_For_Ast & Selection_Statement_Ast::compile(){
	Code_For_Ast ccond = this->cond->compile();
	// printf("aa\n");
	Code_For_Ast *c = new Code_For_Ast();
	*c = ccond;
	// printf("aa\n");
	Ics_Opd *o = new Register_Addr_Opd(ccond.get_reg());
	string label0 = get_new_label();
	// printf("aa\n");
	Icode_Stmt *i;
	if(this->cond->get_data_type() == double_data_type){
		if(x==1||x==2||x==5)
			i =  new Control_Flow_IC_Stmt(bc1f,NULL,NULL,label0);
		else 
			i =  new Control_Flow_IC_Stmt(bc1t,NULL,NULL,label0);
	}
	else
		i =  new Control_Flow_IC_Stmt(beq,o,NULL,label0);
	c->append_ics(*i);
	// printf("aa\n");
	Code_For_Ast cthen = this->then_part->compile();

	list<Icode_Stmt *>::iterator it = cthen.get_icode_list().begin();
	for(;it != cthen.get_icode_list().end();++it){
		c->append_ics(*(*it));
	}

	if(this->else_part){

		string label1 = get_new_label();
		// printf("aa\n");
		Icode_Stmt *i1 = new Label_IC_Stmt(j,label1);
		c->append_ics(*i1);


		// append the stmt label0:
		Icode_Stmt *i2 = new Label_IC_Stmt(label,label0);
		c->append_ics(*i2); 
		// printf("aa\n");

		Code_For_Ast celse = this->else_part->compile();
		// printf("aa\n");

		it = celse.get_icode_list().begin();
		for(;it != celse.get_icode_list().end();++it){
			c->append_ics(*(*it));
		}

		// append the stmt label1:
		Icode_Stmt *i3 = new Label_IC_Stmt(label,label1);
		c->append_ics(*i3); 
	}
	else{
		Icode_Stmt *i2 = new Label_IC_Stmt(label,label0);
		c->append_ics(*i2); 
	}
	// printf("aa\n");
	ccond.get_reg()->reset_register_occupied();
	return *c;

}

Code_For_Ast & Iteration_Statement_Ast::compile(){

	Code_For_Ast *c = new Code_For_Ast();

	string label0 = get_new_label();
	string label1 = get_new_label();
	if(this->is_do_form == 0){

		Icode_Stmt *i1 = new Label_IC_Stmt(j,label1);
		c->append_ics(*i1);
	}
	Code_For_Ast ccond = this->cond->compile();
	Code_For_Ast cbody = this->body->compile();

	// append the stmt label0: 
	Icode_Stmt *i2 = new Label_IC_Stmt(label,label0);
	c->append_ics(*i2); 

	list<Icode_Stmt *>::iterator it = cbody.get_icode_list().begin();
	for(;it != cbody.get_icode_list().end();++it){
		c->append_ics(*(*it));
	}

	// append the stmt label1: 
	Icode_Stmt *i3 = new Label_IC_Stmt(label,label1);
	c->append_ics(*i3);

	

	it = ccond.get_icode_list().begin();
	for(;it != ccond.get_icode_list().end();++it){
		c->append_ics(*(*it));
	}

	Ics_Opd *o = new Register_Addr_Opd(ccond.get_reg());
	Icode_Stmt *i;
	if(this->cond->get_data_type() == double_data_type){
		if(x==1 || x==2 || x==5)
			i =  new Control_Flow_IC_Stmt(bc1t,NULL,NULL,label0);
		else
			i =  new Control_Flow_IC_Stmt(bc1f,NULL,NULL,label0);
	}
	else
		i =  new Control_Flow_IC_Stmt(bne,o,NULL,label0);
	c->append_ics(*i);
		
	
	ccond.get_reg()->reset_register_occupied();

	return *c;

}





Code_For_Ast & Sequence_Ast::compile(){

	if(!this->check_ast()){
		//todo
		printf("cs316: Error");
		exit(0);
	}
	//this->print(file_buffer);

	Code_For_Ast *c = new Code_For_Ast();

	std::list<Ast *>::iterator it1;
	for (it1 = this->statement_list.begin(); it1 != this->statement_list.end(); ++it1){
		Code_For_Ast ci = (*it1)->compile();
		list<Icode_Stmt *>::iterator it = ci.get_icode_list().begin();
		for(;it != ci.get_icode_list().end();++it){
			c->append_ics(*(*it));
		}
	}
	return *c;
}


void Sequence_Ast::print_assembly(ostream & file_buffer){
	if(!this->check_ast()){
		//todo
		printf("cs316: Error");
		exit(0);
	}
	//this->print(file_buffer);

	Code_For_Ast c = this->compile();
	list<Icode_Stmt *>::iterator it = c.get_icode_list().begin();
	for(;it != c.get_icode_list().end();++it){
		(*it)->print_assembly(file_buffer);
	}

}


void Sequence_Ast::print_icode(ostream & file_buffer){
	if(!this->check_ast()){
		//todo
		printf("cs316: Error");
		exit(0);
	}
	//this->print(file_buffer);

	Code_For_Ast c = this->compile();
	list<Icode_Stmt *>::iterator it = c.get_icode_list().begin();
	for(;it != c.get_icode_list().end();++it){
		(*it)->print_icode(file_buffer);
	}

}




Code_For_Ast & Print_Ast::compile(){
	//todo
	Code_For_Ast *c = new Code_For_Ast();
	Register_Descriptor *r1;
	Ics_Opd *one;
	if(this->var->get_data_type() == int_data_type){
		r1 = machine_desc_object.spim_register_table[v0];
		one = new Const_Opd<int>(1);
	}
	else {
		r1 = machine_desc_object.spim_register_table[v0];
		one = new Const_Opd<int>(3);
	}

	Ics_Opd *orhs1 = new Register_Addr_Opd(r1);
	
	Icode_Stmt *m1 = new Move_IC_Stmt(imm_load,one, orhs1);
	c->append_ics(*m1);

	Register_Descriptor *r;
	if(this->var->get_data_type() == int_data_type){
		r = machine_desc_object.spim_register_table[a0];
	}
	else{
		r = machine_desc_object.spim_register_table[f12];
	}

	Ics_Opd *orhs = new Register_Addr_Opd(r);
	Ics_Opd *olhs = new Mem_Addr_Opd(this->var->get_symbol_entry());
	Icode_Stmt *i;	
	if(this->var->get_data_type() == int_data_type)
		i = new Move_IC_Stmt(load,olhs,orhs);
	else
		i = new Move_IC_Stmt(load_d,olhs,orhs);

	c->append_ics(*i);
	Icode_Stmt *i1 = new Print_IC_Stmt();
	c->append_ics(*i1);

	r1->reset_register_occupied();
	r->reset_register_occupied();
	return *c;

}





Code_For_Ast & Return_Ast::compile(){
	if(return_value == NULL){
		Code_For_Ast * c = new Code_For_Ast();
		string label1 = "epilogue_"+proc_name;
		Icode_Stmt *i1 = new Label_IC_Stmt(j,label1);
		c->append_ics(*i1);
		return *c;
	}
	Code_For_Ast cret = return_value->compile();
	Register_Descriptor * r1;
	if(return_value->get_data_type() == int_data_type)
		r1 = machine_desc_object.spim_register_table[v1];
	else
		r1 = machine_desc_object.spim_register_table[f0];

	Ics_Opd *orhs = new Register_Addr_Opd(cret.get_reg());
	Ics_Opd *olhs = new Register_Addr_Opd(r1);
	Icode_Stmt * i;
	if(return_value->get_data_type() == int_data_type)
		i =  new Move_IC_Stmt(mov,orhs,olhs);
	else
		i =  new Move_IC_Stmt(move_d,orhs,olhs);

	Code_For_Ast * c = new Code_For_Ast();
	*c = cret;
	c->append_ics(*i);
	string label1 = "epilogue_"+proc_name;
	Icode_Stmt *i1 = new Label_IC_Stmt(j,label1);
	c->append_ics(*i1);
	cret.get_reg()->reset_register_occupied();
	return *c;
}

Code_For_Ast & Return_Ast::compile_and_optimize_ast(Lra_Outcome & lra){

}






// compile
Code_For_Ast & Call_Ast::compile(){
	Code_For_Ast *c = new Code_For_Ast();

	Procedure * p = program_object.get_procedure_prototype(procedure_name);
	Symbol_Table s = p->get_local_list();

	list<Symbol_Table_Entry *> l = s.get_table();
	l.reverse();

	list<Ast *> params = actual_param_list;
	params.reverse();
	list<Ast *> :: iterator it = params.begin();
	list<Symbol_Table_Entry *> :: iterator it1 = l.begin();
	int n = 0;




	for(;it!=params.end();++it){
		Code_For_Ast c1 = (*it)->compile();


		list<Icode_Stmt *>::iterator it2 = c1.get_icode_list().begin();
		for(;it2 != c1.get_icode_list().end();++it2){
			c->append_ics(*(*it2));
		}


		Ics_Opd *orhs = new Register_Addr_Opd(c1.get_reg());



		string str = "aa"; //(*it1)->get_variable_name();

		Symbol_Table_Entry *ste = new Symbol_Table_Entry(str,int_data_type,0,sp_ref);

		ste->set_symbol_scope(formal);

		ste->set_start_offset(n);
		Ics_Opd *olhs = new Mem_Addr_Opd(*ste);


		Icode_Stmt *i;
		if((*it)->get_data_type() == int_data_type){
			n = n-4;
			i = new Move_IC_Stmt(store,orhs,olhs);
		}
		else{
			n = n-8;
			i = new Move_IC_Stmt(store_d,orhs,olhs);
		}

		
		c->append_ics(*i);

		c1.get_reg()->reset_register_occupied();

		it1++;
	}

	Icode_Stmt *i1 = new Control_Flow_IC_Stmt(jal,NULL,NULL,procedure_name,-1*n);

	c->append_ics(*i1);

	Register_Descriptor *r;
	Register_Descriptor *r1;

	Ics_Opd *olhs;
	Ics_Opd *orhs;

	Icode_Stmt *i2;
	if(this->get_data_type() == int_data_type){
		r = machine_desc_object.get_new_register<int_reg>();
		r1 = machine_desc_object.spim_register_table[v1];
		olhs = new Register_Addr_Opd(r);
		orhs = new Register_Addr_Opd(r1);
		i2 = new Move_IC_Stmt(mov,orhs,olhs);
		c->append_ics(*i2);
		c->set_reg(r);

		if(this->return_value_reg != NULL){
			c->get_reg()->reset_register_occupied();
		}
	}

	else if(this->get_data_type() == double_data_type){
		r = machine_desc_object.get_new_register<float_reg>();
		r1 = machine_desc_object.spim_register_table[f0];
		olhs = new Register_Addr_Opd(r);
		orhs = new Register_Addr_Opd(r1);
		i2 = new Move_IC_Stmt(move_d,orhs,olhs);
		c->append_ics(*i2);
		c->set_reg(r);

		if(this->return_value_reg != NULL){
			c->get_reg()->reset_register_occupied();
		}
	}
	

	
	return *c;
}

Code_For_Ast & Call_Ast::compile_and_optimize_ast(Lra_Outcome & lra){

}
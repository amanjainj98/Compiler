




int Eval_Result::get_int_value(){

}

void Eval_Result::set_value(int value){

}

double Eval_Result::get_double_value(){

}
void Eval_Result::set_value(double value){

}

bool Eval_Result::is_variable_defined(){

}
void Eval_Result::set_variable_status(bool def){

}




void Eval_Result_Value::set_value(int number){

}
void Eval_Result_Value::set_value(double number){

}
int Eval_Result_Value::get_int_value(){

}
double Eval_Result_Value::get_double_value(){

}





Eval_Result_Value_Int::Eval_Result_Value_Int(){
	this->result_type = int_result;
	this->defined = 0;
}
Eval_Result_Value_Int::~Eval_Result_Value_Int(){

}

void Eval_Result_Value_Int::set_value(int number){
	this->value = number;
	this->defined = 1;
}

void Eval_Result_Value_Int::set_value(double number){

}

int Eval_Result_Value_Int::get_int_value(){
	if(this->defined) return value;
	//todo 
	printf("cs316: Error - sclp error: Variable should be defined before its use\n");
	exit(0);
}

void Eval_Result_Value_Int::set_variable_status(bool def){
	this->defined = def;
}

bool Eval_Result_Value_Int::is_variable_defined(){
	return this->defined;
}

void Eval_Result_Value_Int::set_result_enum(Result_Enum res){
	result_type = res;
}
Result_Enum Eval_Result_Value_Int::get_result_enum(){
	return this->result_type;
}



Eval_Result_Value_Double::Eval_Result_Value_Double(){
	this->result_type = double_result;
	this->defined = 0;
}

Eval_Result_Value_Double::~Eval_Result_Value_Double(){

}

void Eval_Result_Value_Double::set_value(double number){
	this->value = number;
	this->defined = 1;
}
void Eval_Result_Value_Double::set_value(int number){

}
double Eval_Result_Value_Double::get_double_value(){
	if(this->defined) return this->value;
	//todo 
	printf("cs316: Error - sclp error: Variable should be defined before its use\n");
	exit(0);

}

void Eval_Result_Value_Double::set_variable_status(bool def){
	this->defined = def;
}
bool Eval_Result_Value_Double::is_variable_defined(){
	return this->defined;
}

void Eval_Result_Value_Double::set_result_enum(Result_Enum res){
	this->result_type = res;
}
Result_Enum Eval_Result_Value_Double::get_result_enum(){
	return this->result_type;
}



Local_Environment::Local_Environment(){

}
Local_Environment::~Local_Environment(){

}

void Local_Environment::print(ostream & file_buffer){
	map<string, Eval_Result *>::iterator it;
	for(it=variable_table.begin();it!=variable_table.end();++it){
		if(!it->second->is_variable_defined()){
			file_buffer << VAR_SPACE << it->first << " : " << "undefined" << "\n";
		}
		else if(it->second->get_result_enum() == int_result){
			file_buffer << VAR_SPACE << it->first << " : " << variable_table[it->first]->get_int_value() << "\n";
		}
		else if(it->second->get_result_enum() == double_result){
			file_buffer << VAR_SPACE << it->first << " : " << variable_table[it->first]->get_double_value() << "\n";
		}
	}
}

bool Local_Environment::is_variable_defined(string name){
	if(this->variable_table.find(name) == this->variable_table.end()) return 0;
	return (this->variable_table.find(name)->second)->is_variable_defined();
}

Eval_Result * Local_Environment::get_variable_value(string name){
	return this->variable_table[name];
}

void Local_Environment::put_variable_value(Eval_Result & value, string name){
	if(this->variable_table.find(name)==this->variable_table.end()){
		this->variable_table.insert({name, & value});		
	}
	else this->variable_table[name] = & value;
}
bool Local_Environment::does_variable_exist(string name){
	return this->variable_table.find(name) != this->variable_table.end();
}


void Symbol_Table::create(Local_Environment & local_global_variables_table){
	list<Symbol_Table_Entry *>::iterator it = this->variable_table.begin();
	for(;it!=this->variable_table.end();it++){
		if((*it)->get_symbol_scope() == global){
			if((*it)->get_data_type() == int_data_type){
				Eval_Result * er = new Eval_Result_Value_Int();
				er->set_value(0);
				er->set_result_enum(int_result);

				local_global_variables_table.put_variable_value(*er, (*it)->get_variable_name());
			}
			else if((*it)->get_data_type() == double_data_type){
				Eval_Result * er = new Eval_Result_Value_Double();
				er->set_value(0.0);
				er->set_result_enum(double_result);

				local_global_variables_table.put_variable_value(*er, (*it)->get_variable_name());
			}
		}
		else if((*it)->get_symbol_scope() == local){
			if((*it)->get_data_type() == int_data_type){
				Eval_Result * er = new Eval_Result_Value_Int();
				
				local_global_variables_table.put_variable_value(*er, (*it)->get_variable_name());
			}
			else if((*it)->get_data_type() == double_data_type){
				Eval_Result * er = new Eval_Result_Value_Double();
				
				local_global_variables_table.put_variable_value(*er, (*it)->get_variable_name());
			}
		}
	}
}

#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H

#include <iostream>
#include <fstream>
#include <string>
class MyException {
	private:
	int err_number_;
	std::string err_explain_;
	
	public:
	
	MyException():
	err_number_(0),
	err_explain_((std::string)"all right")
	{}
	
	MyException(int err):
	err_number_(err),
	err_explain_((std::string)"There's an error in the code.") //stub, must be if(err1)...elif(err2)...elif(err3)...
	{}
	
	MyException(int err,std::string explain):
	err_number_(err),
	err_explain_(explain)
	{}
	
	MyException(const MyException& other):
	err_number_(other.err_number_),
	err_explain_(other.err_explain_)
	{}
	
	~MyException()=default;
	
	const MyException& operator=(const MyException& y){
		err_number_=y.err_number_;
		err_explain_=y.err_explain_;
		return *this;
	}
	
	std::ostream& Print (std::ostream& err)const{
		err<<(*this).err_number_<<std::endl<<(*this).err_explain_<<std::endl;
		return err;
	}
	
};
namespace{
std::ostream& operator<<(std::ostream& err,const MyException& x){
	return x.Print(err);
}
void MyException_Info(std::ostream& out,std::string separator = "\n"){
	out<<"-----------------------------------------------------------------------------------"<<separator;
	out<<"-----------------------------------------------------------------------------------"<<separator;
	out<<"-----------------------------------------------------------------------------------"<<separator;
	out<<"--- MyException.h (Info) ---"<<separator;
	out<<"Was created and wroten by Pavel Chekalov in March 2020"<<separator;
	out<<"All rights reserved"<<separator;
	out<<"-----------------------------------------------------------------------------------"<<separator;
	out<<"--- Targets ---"<<separator;
	out<<"Catching errors by try-catch blocks"<<separator;
	out<<"--- Included libraries ---"<<separator;
	out<<"iostream ; fstream ; string"<<separator;
	out<<"-----------------------------------------------------------------------------------"<<separator;
	out<<"--- Types ---"<<separator;
	out<<"MyException{ int , std::string }"<<separator;
	out<<"--- Constructors ---"<<separator;
	out<<"() ; (int) ; (int,std::sting) ; (const MyException&)"<<separator<<"operator=(const MyException&)"<<separator;
	out<<"--- Destructors ---"<<separator;
	out<<"default"<<separator;
	out<<"-----------------------------------------------------------------------------------"<<separator;
	out<<"--- Print functions ---"<<separator;
	out<<"MyException.Print(std::ostream&)"<<separator<<"std::ostream& operator<< (std::ostream&, const MyException&)"<<separator;
	out<<"--- Scan functions ---"<<separator;
	out<<"no"<<separator;
	out<<"-----------------------------------------------------------------------------------"<<separator;
	out<<"-----------------------------------------------------------------------------------"<<separator;
	out<<"-----------------------------------------------------------------------------------"<<separator;
	return;
}

}
#endif
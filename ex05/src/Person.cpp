#include "Person.h"
#include <iostream>

namespace foo {
	Person::Person(std::string f, std::string l, int a) : first_name(f), last_name(l), age(a) {
		if(output)
			std::cout<<"Calling constructor of " << this << std::endl;
	}

	Person::Person(const Person& from): first_name(from.last_name), last_name(from.last_name), age(from.age){
		if(output)
			std::cout<<"Calling copy constructor of " << this << std::endl;

	}

	Person::Person(const Person&& from):first_name(std::move(from.first_name)), last_name(std::move(from.last_name)), age(std::move(from.age)){

		if(output)
			std::cout<<"Calling move constructor of " << this << std::endl;
	}

	Person& Person::operator=(const Person & from){
		if(output)
			std::cout<<"Calling copy assignment of " << this << std::endl;
		first_name=from.first_name;
		last_name=from.last_name;
		age=from.age;
		return *this;

	}

	Person& Person::operator=(const Person && from){
		if(output)
			std::cout<<"Calling move assignment of " << this << std::endl;
		first_name=std::move(from.first_name);
		last_name=std::move(from.last_name);
		age=std::move(from.age);
		return *this;
	}
	int Person::GetAge() const { return age; }
	std::string Person::GetFirstName() const { return first_name; }
	std::string Person::GetLastName() const { return last_name; }
	void Person::SetAge(int a) { age = a; }
	void Person::SetFirstName(std::string f) { first_name = f; }
	void Person::SetLastName(std::string l) { last_name = l; }

	bool Person::operator==(const Person& rhs) const {
		if(output)
			std::cout<<"Calling == operator of " << this << std::endl;
		return this->first_name == rhs.first_name && this->last_name == rhs.last_name && this->age == rhs.age;
	}
	bool Person::operator!=(const Person& rhs) const {
		if(output)
			std::cout<<"Calling != operator of " << this << std::endl;
		return !this->operator==(rhs);
	}
	bool Person::operator<(const Person& rhs) const {
		if(output)
			std::cout<<"Calling < operator of " << this << std::endl;
		if (this->first_name < rhs.first_name) return true;
		if (this->first_name == rhs.first_name) {
			if (this->last_name < rhs.last_name) return true;
			if (this->last_name == rhs.last_name) {
				if (this->age < rhs.age) return true;
			}
		}
		return false;
		//easier:
		//#include <tuple>
		//return std::tie(first_name,last_name,age) < std::tie(rhs.first_name,rhs.last_name,rhs.age);
	}


	bool Person::operator<=(const Person& rhs) const {
		if(output)
			std::cout<<"Calling <= operator of " << this << std::endl;
		return this->operator<(rhs) || this->operator==(rhs);
	}
	bool Person::operator>(const Person& rhs) const {
		if(output)
			std::cout<<"Calling > operator of " << this << std::endl;
		return rhs.operator<(*this);
	}
	bool Person::operator>=(const Person& rhs) const {
		if(output)
			std::cout<<"Calling >= operator of " << this << std::endl;
		return this->operator>(rhs) || this->operator==(rhs);
	}

	//we use a friend declaration to reduce 
	std::string to_string(const Person& p) {
		return p.first_name + " " + p.last_name + " age: " + std::to_string(p.age);
	}

	std::ostream& operator<<(std::ostream& out, const Person& o) {
		/*	Reson why this work copied from cpp reference
		Argument-dependent lookupC++  C++ language  Functions
		Argument-dependent lookup, also known as ADL, or Koenig lookup,
		is the set of rules for looking up the unqualified function
		names in function-call expressions, including implicit
		function calls to overloaded operators. These function
		names are looked up in the namespaces of their arguments in
		addition to the scopes and namespaces considered by the usual
		unqualified name lookup.
		*/
		return out << to_string(o);
	}



	int Person::compFirstName(const Person& lhs,const Person& rhs){
		return lhs.first_name.compare(rhs.first_name) < 0;
	}
	int Person::compLastName(const Person& lhs, const Person& rhs) {
		return lhs.last_name.compare(rhs.last_name) < 0;
	}
	//explicit coded everything to present the strict odred convention
	//return lhs.age < rhs.age would have all these properties already
	//We consider all cases to demonstrate the conventions
	int Person::compAge(const Person& lhs, const Person& rhs) {
		if (lhs.age == rhs.age) return 0;
		if (lhs.age < rhs.age) return 1;
		if (lhs.age > rhs.age) return 0;
		return 0;
	}

}
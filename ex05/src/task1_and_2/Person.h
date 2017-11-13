#ifndef ADVANCEDCPP_PERSON_H
#define ADVANCEDCPP_PERSON_H
#include <string>

namespace foo{
	class Person {
	private:
		std::string first_name;
		std::string last_name;
		int age;
	public:
		Person(std::string f, std::string l, int a);
		int GetAge() const;
		std::string GetFirstName() const;
		std::string GetLastName() const;
		void SetAge(int a);
		void SetFirstName(std::string f);
		void SetLastName(std::string l);
		bool operator==(const Person& rhs) const;
		bool operator!=(const Person& rhs) const;
		bool operator<(const Person& rhs) const;
		bool operator<=(const Person& rhs) const;
		bool operator>(const Person& rhs) const;
		bool operator>=(const Person& rhs) const;

		//comparison function, cpp reference convention used
		static int compFirstName(const Person& lhs, const Person& rhs);
		static int compLastName(const Person& lhs, const Person& rhs);
		static int compAge(const Person& lhs, const Person& rhs);
		//we use a friend declaration to reduce the size of the class
		//because we would need an aditional function pointer to the
		//member function. In addition friends allows us to directly access the members
		friend std::string to_string(const Person& p);
		friend std::ostream& operator<<(std::ostream& out, const Person& o);
	};

	class MyHash {
	public:
		size_t operator()(const Person& p) const { 
			auto f = p.GetFirstName();
			auto l = p.GetLastName();
			int age = p.GetAge();
			return std::hash<std::string>()(f) * std::hash<std::string>()(l) * std::hash<int>()(age); }
	};
}

#endif //ADVANCEDCPP_PERSON_H

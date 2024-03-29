#ifndef __LIBRARY_HH__
#define __LIBRARY_HH__
#include <iostream>
#include <vector>
#include <string>
#include "book.hh"
#include "magazine.hh"
#include "refernce.hh"
#include "professor.hh"
#include "student.hh"

class Library {
public:
	~Library();
	void add_student_member(std::string student_id, std::string student_name);
	void add_prof_member(std::string prof_name);
	void add_book(std::string book_title, int copies);
	void add_magazine(std::string magazine_title, int year, int number, int copies);
	void add_reference(std::string reference_title, int copies);
	void borrow(std::string member_name, std::string document_title);
	void extend(std::string member_name, std::string document_title);
	void return_document(std::string member_name, std::string document_title);
	int get_total_penalty(std::string member_name);
	std::vector<std::string> available_titles();
	void time_pass(int days);
private:
	Person* search_people(std::string) const;
	Document* search_document(std::string) const;
	void check_for_repetition_in_document(std::string) const;
	void check_for_repetition_in_people(std::string) const;
	std::vector<Document*> documents;
	std::vector<Person*> people;
	ErrorHandler* errorHandler;
};

#endif
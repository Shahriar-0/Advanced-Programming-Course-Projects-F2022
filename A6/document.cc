#include "document.hh"

Document::Document(std::string _title) : title(_title) {
    if (_title == EMPTY_STRING)
        errorHandler->show_error(EMPTY_FIELD);
    initialise();
}

void Document::time_pass(int days) { dayPassed += days; }

void Document::initialise() {
    isBorrowed = false;
    numOfExtension = 0; //we haven't extended our document yet
    dayPassed = 0; //this variable holds the value of the corresponding day in which we are
}

bool Document::can_be_extended() const { 
    if (dayPassed == 0)
        errorHandler->show_error(EXTENDING_ON_FIRST_DAY);
    if (dayPassed > maxDay)
        errorHandler->show_error(EXTENDING_AFTER_RECEIVING_PENALTY);
}

bool Document::operator ==(std::string _title) const { return title == _title; }
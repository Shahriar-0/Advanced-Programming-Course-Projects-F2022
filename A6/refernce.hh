#ifndef __REFERNCE_HH__
#define __REFERNCE_HH__
#include "document.hh"

constexpr int REFERNCE_RETURN_TIME_PERIOD = 10;
constexpr int REFERNCE_MAX_EXTENSION      = 2;
constexpr int FIRST_PENALTY_PERIOD        = 3;
constexpr int FIRST_PENALTY               = 5000;
constexpr int SECOND_PENALTY              = 7000;


class Reference : public Document {
public:
    Reference(std::string);
    virtual void extend();
    virtual int calculate_penalty() const;
protected:
    virtual bool can_be_extended() const;
};

#endif
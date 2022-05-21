#ifndef __IO_HANDLER_HPP__
#define __IO_HANDLER_HPP__

#include <iostream>
#include <cstring>
#include <fstream>
#include "../request/request.hpp"
#include "../data/database/database.hpp"

class IOHandler {
public:
    IOHandler(std::string filename);\
    void read_locations(DataBase& database);
private:
    std::string filename;
};

#endif
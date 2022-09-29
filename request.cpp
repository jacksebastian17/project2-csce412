#define REQUEST_CPP

#include <string>


struct request {
    std::string source;
    std::string destination;
    int processTime;
};
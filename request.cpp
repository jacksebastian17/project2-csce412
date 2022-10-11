#define REQUEST_CPP

#include <string>

/**
 * struct request class that holds a request
*/
struct request {
    std::string source;
    std::string destination;
    int processTime;
};
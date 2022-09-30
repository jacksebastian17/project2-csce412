#define LOADBALANCER_H

#ifndef REQUEST_CPP
#include "request.cpp"
#endif

#include <queue>


class loadbalancer {
    public:
        loadbalancer() { systemTime = 0; }
        int getTime();
        void incrementTime();
        request getRequest();
        void addRequest(request req);
        bool isRequestqueueEmpty();
    private:
        int systemTime;
        std::queue<request> requestqueue;
};
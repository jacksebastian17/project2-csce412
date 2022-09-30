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
        void addRequest(request req);
        request getRequest();
        bool isRequestqueueEmpty();
    private:
        int systemTime;
        std::queue<request> requestqueue;
};
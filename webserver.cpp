#ifndef REQUEST_CPP
#include "request.cpp"
#endif


class webserver {
    public:
        webserver() {
            requestStartTime = 0;
            serverName = ' ';
        }

        webserver(char c) {
            requestStartTime = 0;
            serverName = c;
        }

        request getRequest() {
            return req;
        }

        void addRequest(request r, int currTime) {
            req = r;
            requestStartTime = currTime;
        }

        char getServerName() {
            return serverName;
        }

        bool isRequestDone(int currTime) {
            return (currTime >= (requestStartTime + req.processTime));
        }
    private:
        request req;
        int requestStartTime;
        char serverName;
};
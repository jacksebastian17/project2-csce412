#ifndef REQUEST_CPP
#include "request.cpp"


class webserver {
    public:
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
            if (currTime > (requestStartTime + req.processTime)) {
                return true;
            }
            return false;
        }
    private:
        request req;
        int requestStartTime;
        char serverName;
};

#endif
#ifndef REQUEST_CPP
#include "request.cpp"
#endif

/**
 * webserver class used to create the number of webservers requested
*/
class webserver {
    public:
        /**
         * default constructor of webserver with requestStartTime set to 0 and serverName as empty character
        */
        webserver() {
            requestStartTime = 0;
            serverName = ' ';
        }
        /**
         * constructor of webserver with requestStartTime set to 0 and serverName as char parameter c
         * @param serverName identifier for the webserver
        */
        webserver(char c) {
            requestStartTime = 0;
            serverName = c;
        }
        /**
         * returns the private req member variable of webserver
         * @return req request member
        */
        request getRequest() {
            return req;
        }
        /**
         * sets/adds request with a given request object and request starting time
         * @param r sets req member to this when adding request
         * @param currTime sets requestStartTime member to this time when adding request
        */
        void addRequest(request r, int currTime) {
            req = r;
            requestStartTime = currTime;
        }
        /**
         * returns the private serverName meber variable of webserver
         * @return serverName name member
        */
        char getServerName() {
            return serverName;
        }
        /**
         * shows if the request for the webserver is completed given the current time
         * @param currTime used to check if given time has exceeded the request process time
         * @return boolean value of if the request has completed processing
        */
        bool isRequestDone(int currTime) {
            return (currTime >= (requestStartTime + req.processTime));
        }
    private:
        request req;
        int requestStartTime;
        char serverName;
};
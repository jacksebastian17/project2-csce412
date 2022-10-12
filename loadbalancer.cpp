#ifndef LOADBALANCER_H
#include "loadbalancer.h"
#endif

/**
 * retrieves private member systemTime of loadbalancer
 * @return systemTime
*/
int loadbalancer::getSystemTime() {
    return systemTime;
}

/**
 * increments the system time of loadbalancer
*/
void loadbalancer::incrementSystemTime() {
    systemTime++;
}

/**
 * returns a request object if the queue isn't empty
 * @return request object from loadbalancer
*/
request loadbalancer::getRequest() {
    incrementSystemTime();
    if (!requestqueue.empty()) {
        request r = requestqueue.front();
        requestqueue.pop();
        return r;
    }
}

/**
 * pushes request onto queue and increments system time for operation
 * @param req request object to be used to push onto request queue
*/
void loadbalancer::addRequest(request req) {
    requestqueue.push(req);
    incrementSystemTime();
}

/**
 * checks if the request queue is empty
 * @return boolean value that checks if the requestqueue is empty
*/
bool loadbalancer::isRequestqueueEmpty() {
    return requestqueue.empty();
}

/**
 * returns the size of the requestqueue
 * @return integer size of the private member requestqueue
*/
int loadbalancer::getRequestqueueSize() {
    return requestqueue.size();
}
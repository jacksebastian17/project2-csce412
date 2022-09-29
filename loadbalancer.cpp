#ifndef LOADBALANCER_H
#include "loadbalancer.h"
#endif

int loadbalancer::getTime() {
    return systemTime;
}

void loadbalancer::incrementTime() {
    systemTime++;
}

request loadbalancer::getRequest() {
    incrementTime();
    if (!requestqueue.empty()) {
        request r = requestqueue.front();
        requestqueue.pop();
        return r;
    }
}

void loadbalancer::addRequest(request req) {
    requestqueue.push(req);
    incrementTime();
}

bool loadbalancer::isRequestqueueEmpty() {
    return requestqueue.empty();
}
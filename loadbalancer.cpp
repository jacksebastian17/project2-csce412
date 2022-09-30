#ifndef LOADBALANCER_H
#include "loadbalancer.h"
#endif

int loadbalancer::getSystemTime() {
    return systemTime;
}

void loadbalancer::incrementSystemTime() {
    systemTime++;
}

request loadbalancer::getRequest() {
    incrementSystemTime();
    if (!requestqueue.empty()) {
        request r = requestqueue.front();
        requestqueue.pop();
        return r;
    }
}

void loadbalancer::addRequest(request req) {
    requestqueue.push(req);
    incrementSystemTime();
}

bool loadbalancer::isRequestqueueEmpty() {
    return requestqueue.empty();
}
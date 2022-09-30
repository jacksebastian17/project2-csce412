#include <iostream>
#include "request.cpp"
#include "webserver.cpp"
#include "loadbalancer.h"
#include <time.h>
#include <ctime>
#include <cstdlib>
#include <sstream>

using namespace std;

const int NUMWEBSERVERS = 5;

request createRequest() {
    stringstream ips, ipd;
    request r;
    ips << (rand() % 256) << "." << (rand() % 256) << "." << (rand() % 256) << "." << (rand() % 256);
    ipd << (rand() % 256) << "." << (rand() % 256) << "." << (rand() % 256) << "." << (rand() % 256);
    r.source = ips.str();
    r.destination = ipd.str();
    r.processTime = rand() % 500;
    return r;
}

int main() {

    srand(time(0));

    loadbalancer lb;
    webserver webservers[NUMWEBSERVERS];

    for (int i = 0; i < 10; i++) {
        request newRequest = (createRequest());
        lb.addRequest(newRequest);
    }

    for (int i = 0; i < NUMWEBSERVERS; i++) {
        webserver server((char)(i + 65));
        webservers[i] = server;
        webservers[i].addRequest(lb.getRequest(), lb.getTime());
    }
    
    // 10,000 clock cycles as per requirement of project
    while (lb.getTime() < 10000) {
        int currTime = lb.getTime();
        if (webservers[currTime % NUMWEBSERVERS].isRequestDone(currTime)) {
            request req = webservers[currTime % NUMWEBSERVERS].getRequest();
            cout << "At " << currTime << " " << webservers[currTime].getServerName() << " processed request from " << req.source << " to " << req.destination << endl;
            webservers[currTime % NUMWEBSERVERS].addRequest(lb.getRequest(), currTime);
        }
        if (rand() % 10 == 0) {
            request r = createRequest();
            lb.addRequest(r);
        }
        lb.incrementTime();
    }
}
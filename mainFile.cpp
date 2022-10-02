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
    stringstream ipaddress_source, ipaddress_dest;
    request r;
    ipaddress_source << (rand() % 256) << "." << (rand() % 256) << "." << (rand() % 256) << "." << (rand() % 256);
    ipaddress_dest << (rand() % 256) << "." << (rand() % 256) << "." << (rand() % 256) << "." << (rand() % 256);
    r.source = ipaddress_source.str();
    r.destination = ipaddress_dest.str();
    r.processTime = rand() % 500;
    return r;
}

int main() {

    srand(time(0));

    loadbalancer lb;
    webserver webservers[NUMWEBSERVERS];

    // generate full queue = NUMWEBSERVERS * 2
    for (int i = 0; i < NUMWEBSERVERS * 2; i++) {
        request newRequest = createRequest();
        lb.addRequest(newRequest);
    }

    for (int i = 0; i < NUMWEBSERVERS; i++) {
        webserver server((char)('A' + i));
        webservers[i] = server;
        webservers[i].addRequest(lb.getRequest(), lb.getSystemTime());
    }
    
    // 10,000 clock cycles as per requirement of project
    while (lb.getSystemTime() < 10000) {
        //cout << lb.getSystemTime() << ":  " << "empty?" << lb.isRequestqueueEmpty() << " -- ";
        int currTime = lb.getSystemTime();
        if (webservers[currTime % NUMWEBSERVERS].isRequestDone(currTime)) {
            request req = webservers[currTime % NUMWEBSERVERS].getRequest();
            cout << "At " << currTime << " " << webservers[currTime % NUMWEBSERVERS].getServerName() << " processed request from " << req.source << " to " << req.destination << endl;
            webservers[currTime % NUMWEBSERVERS].addRequest(lb.getRequest(), currTime);
        }
        if (rand() % 10 == 0) {
            lb.addRequest(createRequest());
        }
        lb.incrementSystemTime();
    }
}
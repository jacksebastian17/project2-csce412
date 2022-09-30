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
    r.processTime = rand() % 50;
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
        cout << lb.getSystemTime() << ":  " << "empty?" << lb.isRequestqueueEmpty() << " -- ";
        cout << "step1" << ", ";
        int currTime = lb.getSystemTime();
        if (webservers[currTime % NUMWEBSERVERS].isRequestDone(currTime)) {
            cout << "step2" << ", ";
            request req = webservers[currTime % NUMWEBSERVERS].getRequest();
            cout << "step3" << ", ";
            cout << "At " << currTime << " " << webservers[currTime].getServerName() << " processed request from " << req.source << " to " << req.destination << ", ";
            webservers[currTime % NUMWEBSERVERS].addRequest(lb.getRequest(), currTime);
        }
        cout << "step4" << ", ";
        if (rand() % 10 == 0) {
            request r = createRequest();
            lb.addRequest(r);
        }
        cout << "step5" << ", ";
        lb.incrementSystemTime();
        cout << "step6" << endl;
    }
}
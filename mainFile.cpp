#include <iostream>
#include "request.cpp"
#include "webserver.cpp"
#include "loadbalancer.h"
#include <time.h>
#include <ctime>
#include <cstdlib>
#include <sstream>

using namespace std;

request createRequest() {
    stringstream ips, ipd;
    request r;
    ips << (rand() % 256) << "." << (rand() % 256) << "." << (rand() % 256) << "." << (rand() % 256);
    ipd << (rand() % 256) << "." << (rand() % 256) << "." << (rand() % 256) << "." << (rand() % 256);
    r.source = ips.str();
    r.destination = ipd.str();
    r.processTime = rand() % 100;
    return r;
}

int main() {
    int numWebservers;
    int loadBalancerRuntime;

    cout << "Please enter the number of servers you wish to use: ";
    cin >> numWebservers;
    cout << "Please enter the time you want to run the load balancer: ";
    cin >> loadBalancerRuntime;

    srand(time(0));

    loadbalancer lb;
    webserver webservers[10];

    for (int i = 0; i < 10; i++) {
        request newRequest = createRequest();
        lb.addRequest(newRequest);
    }

    for (int i = 0; i < numWebservers; i++) {
        webserver server((char)('A' + i));
        webservers[i] = server;
        webservers[i].addRequest(lb.getRequest(), lb.getTime());
    }
    
    // 10,000 clock cycles as per requirement of project
    while (lb.getTime() < 10000) {
        int currTime = lb.getTime();
        if (webservers[currTime % numWebservers].isRequestDone(currTime)) {
            request req = webservers[currTime % numWebservers].getRequest();
            //cout << "currTime: " << currTime << ", " << webservers[currTime].getServerName() << "processed request from " << req.source << " to " << req.destination << endl;
            webservers[currTime % numWebservers].addRequest(lb.getRequest(), currTime);
        }
        lb.incrementTime();
    }
}
#include <iostream>
#include "request.cpp"
#include "webserver.cpp"
#include "loadbalancer.h"
#include <time.h>
#include <ctime>
#include <cstdlib>
#include <sstream>

#include <vector>

using namespace std;


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

    int numWebservers;
    int loadbalancerRuntime;

    loadbalancer lb;
    vector<webserver> webservers;

    cout << "Please enter the number of webservers you wish to use: ";
    cin >> numWebservers;
    webservers.resize(numWebservers);

    cout << "Please enter the amount of time you want the load balancer to run for (>= 10,000): ";
    cin >> loadbalancerRuntime;


    // generate full queue = NUMWEBSERVERS * 2
    for (int i = 0; i < numWebservers * 2; i++) {
        request newRequest = createRequest();
        lb.addRequest(newRequest);
    }
    cout << "Range of task times: 1 <= processTime << 500 seconds" << endl;
    cout << "Starting size of queue: " << lb.getRequestqueueSize() << endl;

    for (int i = 0; i < numWebservers; i++) {
        webserver server((char)('A' + i));
        webservers[i] = server;
        webservers[i].addRequest(lb.getRequest(), lb.getSystemTime());
    }
    
    // 10,000 clock cycles as per requirement of project
    while (lb.getSystemTime() < loadbalancerRuntime) {
        //cout << lb.getSystemTime() << ":  " << "empty?" << lb.isRequestqueueEmpty() << " -- ";
        int currTime = lb.getSystemTime();
        if (webservers[currTime % numWebservers].isRequestDone(currTime)) {
            request req = webservers[currTime % numWebservers].getRequest();
            cout << "At " << currTime << ", webserver " << webservers[currTime % numWebservers].getServerName() << " processed request (processTime = " << 
            req.processTime << ") from " << req.source << " to " << req.destination << endl;
            webservers[currTime % numWebservers].addRequest(lb.getRequest(), currTime);
        }
        if (rand() % 25 == 0) {
            lb.addRequest(createRequest());
        }
        lb.incrementSystemTime();
    }
    cout << "Ending size of queue: " << lb.getRequestqueueSize() << endl;
}
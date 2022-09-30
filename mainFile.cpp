#include <iostream>
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
}
#include <iostream>
#include "loadbalancer.h"
#include <time.h>

using namespace std;

int main() {
    int numWebservers;
    int loadBalancerRuntime;

    cout << "Please enter the number of servers you wish to use: ";
    cin >> numWebservers;
    cout << "Please enter the time you want to run the load balancer: ";
    cin >> loadBalancerRuntime;

    loadbalancer lb;
    webserver webservers[10];
    for (int i = 0; i < numWebservers; i++) {
        webserver server((char)('A' + i));
        webservers[i] = server;
    }
    for (int i = 0; i < 10; i++) {
        request newRequest;
        newRequest.processTime = rand() % 10; // request takes 10 seconds
        lb.addRequest(newRequest);
    }
}
#include <iostream>
#include <vector>
#include <chrono>
#include <mutex>
#include <thread>
#include "ostreamlock.h"

using std::cout;    using std::endl;
using std::vector;  using std::string;

const size_t kNumTickets = 100;
const size_t kNumAgents = 10;

int remainingTickets = kNumTickets;
std::mutex agentMutex;

void ticketAgent(size_t id) {
    while(true) {
        /*  We will let RAII deal with the locking and unlocking */
        std::lock_guard<std::mutex> l(agentMutex);

//        agentMutex.lock();
        if(remainingTickets <= 0) {
//            agentMutex.unlock();      // need to unlock here too in case we break
            return;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        remainingTickets--;
//        agentMutex.unlock();
        cout << oslock << "Agent #" << id << " sold a ticket! (" << remainingTickets
                                                            << " more to be sold)." << endl << osunlock;
    }
    cout << oslock
         << "Agent #" << id << " notices all tickets are sold and goes home." << endl
         << osunlock;
}

int main() {
    vector<std::thread> threads;

    for(size_t i = 0; i < kNumAgents; ++i) {
        threads.push_back(std::thread(ticketAgent, i));
    }

    for(std::thread& thr : threads) {
        thr.join();
    }

    cout << "All tickets sold!" << endl;
    cout << "Tickets remaining: " << remainingTickets << endl;


    return 0;
}


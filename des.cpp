//

//  eventsim.cpp
//
//
//  Created by Yeem Diallo on 9/30/16.
//
//

int min_w = 15;

#include <stdio.h>
#include <algorithm>   // for random_shuffle()
#include <iostream>    // for cout
#include <list>       // for queue
#include <vector>      // for vector
#include <time.h>

// Execution event in a descrete event driven simulation.
class event {
public:
    // Construct sets time of event.
    event (unsigned int n, unsigned int t) : numberOfNodes (n), time(t)
    { }
    
    // Execute event by invoking this method.
    //pure virtual function
    virtual void processEvent () = 0;
    
    const unsigned int numberOfNodes;
    const unsigned int time;
};




// returns a random integer between 0 and n with n <= 32767 <= INT_MAX
int irand (int n)
{
    static int seq[] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf
    };
    
    std::random_shuffle (seq, seq + sizeof seq / sizeof *seq);
    
    const int rnd =
    ((seq [0] << 11) | (seq [1] << 8) | (seq [2] << 4)) + seq [3];
    
    return rnd % n;
}

class Node{
    //private:
public:
    int numFrames;
    //int counterToSend;
    //int flowTime;
    //Number of frames left to send
    //Number of frames sent
    
    
    void setNumFrames(int maxNum){
        //srand(time(NULL));
        numFrames = rand() % 10 + 1;
    }
    
    int getNumFrames(){
        return numFrames;
    }
};

struct nodeComparator {
    bool operator() (const Node * left, const Node * right) const {
        return left->numFrames > right->numFrames;
    }
};

// Framework for discrete event-driven simulations.
class simulation {
public:
    simulation () : numberOfNodes(0), time(0), eventQueue (){}
    void run ();
    void scheduleEvent(event * newEvent) {
        eventQueue.push_back(newEvent);
    }
    unsigned int numberOfNodes;
    unsigned int time;
protected:
    std::list<event*> eventQueue;
    std::list<Node> activeNodes;
};

void simulation::run () {
    
    while (! eventQueue.empty ()) {
        event * nextEvent = eventQueue.front();
        eventQueue.pop_front();
        time = nextEvent->time;
        nextEvent->processEvent ();
        delete nextEvent;
    }
}

// Simulation
class mySimulation : public simulation {
public:
    mySimulation () : simulation (), numberOfNodes(2)
    { }
    void canSend (unsigned int numberOfFrames);
    // Data fields.
    unsigned int numberOfNodes;
} theSimulation;




int main () {
    srand(time(NULL));
    std::cout << "Wifi Discrete Event Simulator\n";
    
    Node n1;
    n1.setNumFrames(10);
    std::cout << "Number of frames for node 1: " << n1.numFrames << "\n";
    Node n2;
    n2.setNumFrames(10);
    std::cout << "Number of frames for node 2: " << n2.numFrames << "\n";
    
    int time = 0;
    //event newEvent(time);
    //simulation mySim;
    //mySim.run();
    //mySim.scheduleEvent(newEvent);
    // theSimulation.scheduleEvent (new arriveEvent (t, 1 + irand (4)));
    
    // Run the simulation.
    //theSimulation.run ();
    
    
    
    return 0;
}



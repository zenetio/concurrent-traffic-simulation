#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <mutex>
#include <deque>
#include <condition_variable>
#include "TrafficObject.h"

/// forward declarations to avoid include cycle
class Vehicle;

enum TrafficLightPhase {
    red,
    green,
};

/// FP.3: Define a class "MessageQueue" which has the public methods send and receive. 
/// Send should take an rvalue reference of type "TrafficLightPhase" whereas receive should return this type. 
/// Also, the class should define an "std::dequeue" called "_queue", which stores objects of type "TrafficLightPhase". 
/// Also, there should be an "std::condition_variable" as well as an "std::mutex" as private members. 

template <class T>
class MessageQueue
{
public:
    /// FP.4

    /// <summary>
    /// send(T &&msg)
    /// <param name="msg">rvalue reference of type TrafficLightPhase</param>
    /// </summary>
    void send(T &&msg);
    /// <returns>type TrafficLightPhase</returns>
    T receive();                                    

private:
    /// type TrafficLightPhase
    std::deque<T> _queue;
    /// std::condition_variable                      
    std::condition_variable _condition;
    /// std::mutex
    std::mutex _mutex;
};

/// FP.1: Define a class "TrafficLight" which is a child class of "TrafficObject". 
/// The class shall have the public methods "void waitForGreen()" and "void simulate()"" 
/// as well as "TrafficLightPhase getCurrentPhase()", where "TrafficLightPhase" is an enum that 
/// can be either "red" or "green". Also, add the private method "void cycleThroughPhases()". 
/// Furthermore, the private member "_currentPhase" which can take "red" or "green" as its value. 

class TrafficLight : public TrafficObject             // Make a child class of TrafficObject
{
public:
    // constructor / desctructor
    TrafficLight();
    ~TrafficLight();

    // getters / setters
    TrafficLightPhase getCurrentPhase(){return _currentPhase;};
    void setCurrentPhase(TrafficLightPhase phase){_currentPhase=phase;};

    // typical behaviour methods
    void waitForGreen();
    void simulate();

private:
    // typical behaviour methods
    void cycleThroughPhases();
    TrafficLightPhase _currentPhase;

    /// FP.4b: create a private member of type MessageQueue for messages of type TrafficLightPhase 
    /// and use it within the infinite loop to push each new TrafficLightPhase into it by calling 
    /// send in conjunction with move semantics.
    MessageQueue<TrafficLightPhase> _messages;
};

#endif
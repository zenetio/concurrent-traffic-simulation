#include <iostream>
#include <random>
#include "TrafficLight.h"

/*------------- Implementation of class "MessageQueue" ---------------*/

/*-------------------------------------------------------------------------------------------
 * FP.4a : send(T &&msg) use the mechanisms std::lock_guard<std::mutex> 
 * as well as _condition.notify_one() to add a new message to the queue and afterwards send a notification.
 *-------------------------------------------------------------------------------------------
 */
template <typename T>
void MessageQueue<T>::send(T &&msg)
{
    std::lock_guard<std::mutex> uLock(_mutex);
    _queue.push_back(std::move(msg));
    _condition.notify_one();
}

/*-------------------------------------------------------------------------------------------
 * FP.5a : receive() use std::unique_lock<std::mutex> and _condition.wait() 
 * to wait for and receive new messages and pull them from the queue using move semantics. 
 * Returns: The received object.
 *-------------------------------------------------------------------------------------------
 */
template <typename T>
T MessageQueue<T>::receive()
{
    std::unique_lock<std::mutex> uLock(_mutex);
    _condition.wait(uLock, [this]() { return !_queue.empty(); });

    T t = std::move(_queue.back());
    _queue.pop_back();
    return t;
}

/*---------------- Implementation of class "TrafficLight" -----------------*/
TrafficLight::TrafficLight()
{
    _currentPhase = TrafficLightPhase::red;
}

TrafficLight::~TrafficLight() {}

/*-------------------------------------------------------------------------------------------
 * FP.2a: cycleThroughPhases() implements an infinite loop that measures the time between two loop cycles 
 * and toggles the current phase of the traffic light between red and green and sends an update method 
 * to the message queue using move semantics. The cycle durationis a random value between 4 and 6 seconds. 
 * Also, the while-loop uses std::this_thread::sleep_for to wait 1ms between two cycles. 
 *-------------------------------------------------------------------------------------------
 */
void TrafficLight::cycleThroughPhases()
{
    // longer period and better statistical behavior
    std::random_device seed;                                    // create a seed for the random number engine
    std::mt19937 gen(seed());                                   // generate random number with seed & Mersenne Twister
    std::uniform_real_distribution<double> dis(4.0, 6.0);       // set between 4 and 6
    double duration = dis(gen);                                 // define and set duration
    duration = duration * 1000;                                 // turn it into seconds
        
    std::chrono::time_point<std::chrono::system_clock> lastUpdate;       // get the current system time
    lastUpdate = std::chrono::system_clock::now();                       // make lastUpdate now

    while (true) {                                                       // infinite loop
        std::this_thread::sleep_for(std::chrono::milliseconds(1));       // wait between cycles as per Task list
        int timeDifference = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - lastUpdate).count();
        if (timeDifference >= duration) {
            if (getCurrentPhase() == TrafficLightPhase::red) {           // from red to green
                _currentPhase = TrafficLightPhase::green;
            }
            else {
                _currentPhase = TrafficLightPhase::red;                  // or green to red
            }
            lastUpdate = std::chrono::system_clock::now();               // make lastUpdate now
            duration = (rand()%(6-4+1)) + 4;                             // generate a random number between 4 and 6
            duration = duration * 1000;                                  // turn it into seconds
            _messages.send(std::move(_currentPhase));                    // push message to queue
        }
    }
}

/*-------------------------------------------------------------------------------------------
 * FP.2b: simulate() starts the method cycleThroughPhases in a thread. 
 * To do this, use the thread queue in the base class. 
 * Runs and repeatedly calls the receive function on the message queue. 
 * Once it receives TrafficLightPhase::green, the method returns.
 *-------------------------------------------------------------------------------------------
 */
void TrafficLight::simulate()
{
    threads.emplace_back(std::thread(&TrafficLight::cycleThroughPhases, this));
}

/*-------------------------------------------------------------------------------------------
 * FP.5b: waitForGreen() has an infinite while-loop that
 * runs and repeatedly calls the receive function on the message queue. 
 * Once it receives TrafficLightPhase::green, the method returns.
 *-------------------------------------------------------------------------------------------
 */
void TrafficLight::waitForGreen()
{
    while (true) {
        TrafficLightPhase msg = _messages.receive();
        if (msg == TrafficLightPhase::green) {
            return;
        }
    }
}
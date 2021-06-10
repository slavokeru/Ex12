// Copyright 2021 GHA Test Team

#include "TimedDoor.h"
#include <time.h>
#include <string>

TimedDoor::TimedDoor(int time) {
    iTimeout = time;
    adapter = new DoorTimerAdapter(*this);
    opened = false;
}

void TimedDoor::unlock() {
    Timer timer;
    opened = true;
    timer.tregister(iTimeout, adapter);
}

void Timer::tregister(int sleepTime, TimerClient *adapter) {
    sleep(sleepTime);
    adapter->Timeout();
}

void Timer::sleep(int sleepTime) {
    time_t tic = clock();
    while (clock() < tic + sleepTime * CLOCKS_PER_SEC) {}
}

void DoorTimerAdapter::Timeout() {
    door.DoorTimeOut();
}

void TimedDoor::DoorTimeOut() {
    throw std::string("close the door!");
}

void TimedDoor::throwState() {
    if (isDoorOpened()) {
        throw std::string("the door is open!");
    } else {
        throw std::string("the door is closed!");
    }
}

bool TimedDoor::isDoorOpened() {
    return opened;
}

void TimedDoor::lock() {
    opened = false;
}

DoorTimerAdapter::DoorTimerAdapter(TimedDoor & timedDoor): door(timedDoor) {}

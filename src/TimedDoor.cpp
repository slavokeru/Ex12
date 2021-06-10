// Copyright 2021 GHA Test Team

#include "TimedDoor.h"
#include <ctime>
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
    time_t tic = time(0);
    time_t toc = time(0);
    while (tic != toc + sleepTime) {
        toc = time(0);
    }
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

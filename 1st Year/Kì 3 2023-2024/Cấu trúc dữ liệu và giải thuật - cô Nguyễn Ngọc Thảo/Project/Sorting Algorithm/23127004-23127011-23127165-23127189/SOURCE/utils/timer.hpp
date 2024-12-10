#pragma once
#include <iostream>
#include <chrono>
#include <ctime>
#include <cmath>

/*
Timer class
Source: https://gist.github.com/mcleary/b0bf4fa88830ff7c882d

*/

class Timer
{
public:
    void start();
    void stop();
    double elapsedMilliseconds();
    double elapsedSeconds();
private:
    std::chrono::time_point<std::chrono::system_clock> m_StartTime;
    std::chrono::time_point<std::chrono::system_clock> m_EndTime;
    bool                                               m_bRunning = false;
};

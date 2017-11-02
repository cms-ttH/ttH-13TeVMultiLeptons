#ifndef STOPWATCH_H_
#define STOPWATCH_H_

#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <chrono>

#include <sstream>  // std::ostringstream

struct TimerInfo {
    std::chrono::high_resolution_clock::time_point t_start;
    std::chrono::high_resolution_clock::time_point t_end;
    int counter;
    double total;
};

class Stopwatch
{
private:
    std::map<std::string,TimerInfo> tracked_timers;

    std::string padLeft(std::string str, const char pad_char, int pad_num);
    std::string padRight(std::string str, const char pad_char, int pad_num);

public:
    Stopwatch();
    ~Stopwatch();

    void startTimer(std::string timer_name);
    void updateTimer(std::string timer_name);

    void readLap(std::string timer_name);
    void readTimer(std::string timer_name,double norm=1.0);
    void readAvgTimer(std::string timer_name,double norm=1.0);

    void readAllTimers(bool use_avg=0,std::string norm_name="");
};

Stopwatch::Stopwatch()
{}

Stopwatch::~Stopwatch()
{}

/////////////// Private ///////////////

std::string Stopwatch::padLeft(std::string str,const char pad_char, int pad_num)
{
    int length = str.length();
    if (length >= pad_num) {
        return str;
    }

    std::string padded_str(pad_num - length,pad_char);
    padded_str = padded_str + str;
    return padded_str;
}

std::string Stopwatch::padRight(std::string str,const char pad_char, int pad_num)
{
    int length = str.length();
    if (length >= pad_num) {
        return str;
    }

    std::string padded_str(pad_num - length,pad_char);
    padded_str = str + padded_str;
    return padded_str;
}

/////////////// Public ///////////////

void Stopwatch::startTimer(std::string timer_name)
{
    if (tracked_timers.find(timer_name) == tracked_timers.end()) {
        // This is a new timer!
        TimerInfo new_tracked_timer;
        new_tracked_timer.total = 0;
        new_tracked_timer.counter = 0;
        new_tracked_timer.t_start = std::chrono::high_resolution_clock::now();
        tracked_timers[timer_name] = new_tracked_timer;
    } else {
        // This is an old timer!
        tracked_timers[timer_name].t_start = std::chrono::high_resolution_clock::now();
    }
    return;
}

void Stopwatch::updateTimer(std::string timer_name)
{
    if (tracked_timers.find(timer_name) != tracked_timers.end()) {
        // Only update the timer for known tracked timers
        tracked_timers[timer_name].total += std::chrono::duration<double,std::milli>(std::chrono::high_resolution_clock::now() - tracked_timers[timer_name].t_start).count();
        tracked_timers[timer_name].counter += 1;
    }
    return;
}

void Stopwatch::readLap(std::string timer_name)
{
    if (tracked_timers.find(timer_name) != tracked_timers.end()) {
        std::cout << std::fixed << std::setprecision(2)
            << "Wall clock lap (" << timer_name << "): "
            << std::chrono::duration<double,std::milli>(std::chrono::high_resolution_clock::now() - tracked_timers[timer_name].t_start).count()
            << " ms\n";
    }
    return;
}

void Stopwatch::readTimer(std::string timer_name,double norm)
{
    if (tracked_timers.find(timer_name) != tracked_timers.end()) {
        std::string format_str = "(" + timer_name + "):";
        format_str = padRight(format_str,' ',20);

        //std::string t_elapsed = std::to_string(tracked_timers[timer_name].total);

        std::ostringstream strs;
        strs << std::fixed << std::setprecision(2) << tracked_timers[timer_name].total/norm;
        std::string t_elapsed = strs.str();
        t_elapsed = padRight(t_elapsed,' ',9);

        std::cout << "Wall clock time " << format_str
            << t_elapsed
            << " ms\n";
    }
    return;
}

void Stopwatch::readAvgTimer(std::string timer_name,double norm)
{
    if (tracked_timers.find(timer_name) != tracked_timers.end()) {
        std::string format_str = "(" + timer_name + "):";
        format_str = padRight(format_str,' ',20);

        std::ostringstream strs;
        strs << std::fixed << std::setprecision(2) << tracked_timers[timer_name].total/(norm*tracked_timers[timer_name].counter);
        std::string t_elapsed = strs.str();
        t_elapsed = padRight(t_elapsed,' ',9);

        std::cout << "Wall clock time " << format_str
            << t_elapsed
            << " ms/counts\n";
    }
    return;
}

void Stopwatch::readAllTimers(bool use_avg,std::string norm_name)
{
    double norm = 1.0;
    if (tracked_timers.find(norm_name) != tracked_timers.end()) {
        if (use_avg) {
            norm = tracked_timers[norm_name].total/tracked_timers[norm_name].counter;
        } else {
            norm = tracked_timers[norm_name].total;
        }
    }

    for (auto it = tracked_timers.begin(); it != tracked_timers.end(); ++it) {
        if (use_avg) {
            readAvgTimer(it->first,norm);
        } else {
            readTimer(it->first,norm);
        }
    }

    return;
}

#endif
/* STOPWATCH */
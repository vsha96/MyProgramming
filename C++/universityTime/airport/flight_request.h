#ifndef FLIGHT_REQUEST_H
#define FLIGHT_REQUEST_H

#include <string>
#include <iostream>

// simulation time
struct SimTime {
    int min;
    int hour;
    int day;

    SimTime() {
        min=0;
        hour=0;
        day=0;
    }
    SimTime(int set_min, int set_hour, int set_day) {
        if ((set_min >= 60) || (set_min < 0) ||
                (set_hour >= 24) || (set_hour < 0) ||
                (set_day < 0)) {
            std::cout << "WARN: created simulation time is incorrect: "
                      << set_day << ":"
                      << set_hour << ":"
                      << set_min << std::endl;
        }
        min=set_min;
        hour=set_hour;
        day=set_day;
    }
    SimTime(const int mins) {
        int t = mins;
        // cout << t << endl;
        min = mins % 60;
        t -= min;
        // cout << t/60 << endl;
        hour = t / 60 % 24;
        t -= hour * 60;
        // cout << t/60/24 << endl;
        day = t / (24 * 60);
    }
    SimTime(std::string time) {
        size_t last = 0;
        size_t next = 0;
        std::string delimiter = ":";

        next = time.find(delimiter, last);
        std::string s_hour = time.substr(last, next-last);
//        std::cout << s_hour << std::endl;

        last = next + 1;
        std::string s_min = time.substr(last, next-last);
//        std::cout << s_min << std::endl;

        min = std::stoi(s_min);
        hour = std::stoi(s_hour);
        day = 0;
        if ((min >= 60) || (min < 0) ||
                (hour >= 24) || (hour < 0) ||
                (day < 0)) {
            std::cout << "WARN: created simulation time is incorrect: "
                      << day << ":"
                      << hour << ":"
                      << min << std::endl;
        }
    }

//    SimTime &operator=(const SimTime &) = default;
//    ~SimTime() = default;

    void tick() {
        min++;
        if (min == 60) {
            min = 0;
            hour++;
        }
        if (hour == 24) {
            hour = 0;
            day++;
        }
    }

    void tick(int n_min) {
        for (int i=0; i<n_min; i++)
            tick();
    }

    int mins() const {
        return
            day * 24 * 60
            + hour * 60
            + min;
    }

    void add(const SimTime other_time) {
        tick(
            other_time.day * 24 * 60
            + other_time.hour * 60
            + other_time.min
        );
    }
    bool operator==(const SimTime other_time) const {
        return  mins() == other_time.mins();
    }
    bool operator!=(const SimTime other_time) const {
        return  mins() != other_time.mins();
    }
    bool operator>(const SimTime other_time) const {
        return mins() > other_time.mins();
    }
    bool operator>=(const SimTime other_time) const {
        return mins() >= other_time.mins();
    }
    bool operator<(const SimTime other_time) const {
        return mins() < other_time.mins();
    }
    bool operator<=(const SimTime other_time) const {
        return mins() <= other_time.mins();
    }
    SimTime operator+(const SimTime other_time) const{
        return SimTime(mins() + other_time.mins());
    }
    SimTime operator-(const SimTime other_time) const{
        if (mins() > other_time.mins()) {
            return SimTime(mins() - other_time.mins());
        } else {
            return SimTime (0);
        }
    }
    void print() {
            std::cout << day  << " days "
                      << hour << " hours "
                      << min  << " mins"   << std::endl;
    }
    std::string toString() {
        if (min < 10) {
            return std::to_string(hour) + ":0" + std::to_string(min);
        } else {
            return std::to_string(hour) + ":" + std::to_string(min);
        }
    }
};

enum AirplaneType {
    airplane1,
    airplane2,
    airplane3
};

class FlightRequest
{
public:
    FlightRequest(
        std::string flight,
        AirplaneType airplane_type,
        std::string up_down,
        SimTime planned_time
    );

    const SimTime &planned_time() const;

    const std::string &flight() const;
    const SimTime aiplane_type_time();
    const std::string &up_down() const;

    void setRunway_id(int newRunway_id);

    void setDelayTime(const SimTime &newDelay_time);
    void setReadyTime(const SimTime &ready_time);
    void setOnRunwayTime(const SimTime &new_on_runway_time);
    void setTakeoffLandingTime(const SimTime &new_takeoff_landing_time);

    const SimTime &delay_time() const;
    const SimTime &ready_time() const;
    const SimTime &on_runway_time() const;
    const SimTime &takeoff_landing_time() const;

    void setHandled(bool newHandled);
    bool handled() const;

    void show();
    std::string getInfo();
private:
    std::string _flight;
    AirplaneType _airplane_type;
    std::string _up_down;

    // times
    struct SimTime _planned_time;
    struct SimTime _delay_time;
    struct SimTime _ready_time;
    struct SimTime _on_runway_time;
    struct SimTime _takeoff_landing_time;

    // for statistics
    int _runway_id = -1;
    bool _handled;
};

#endif // FLIGHT_REQUEST_H

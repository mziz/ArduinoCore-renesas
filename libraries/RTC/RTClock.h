#ifndef ARDUINO_REAL_TIME_CLOCK
#define ARDUINO_REAL_TIME_CLOCK

#include <ctime>

using stime_t = struct tm;
using rtc_cbk_t = void (*)();

enum class Month : uint8_t {
    JAN = 0,
    FEB,
    MAR,
    APR,
    MAY,
    JUN,
    JUL,
    AUG,
    SEP,
    OCT,
    NOV,
    DEC
};

enum class DayOfWeek : uint8_t {
    MONDAY = 1,
    TUESDAY = 2, 
    WEDNESDAY = 3, 
    THURSDAY = 4, 
    FRIDAY = 5, 
    SATURDAY = 6, 
    SUNDAY = 0
};

enum class SaveLight : uint8_t {
    SAVING_TIME_INACTIVE = 0,
    SAVING_TIME_ACTIVE

};

/*

  tm_sec	int	seconds after the minute	0-60*
tm_min	int	minutes after the hour	0-59
tm_hour	int	hours since midnight	0-23
tm_mday	int	day of the month	1-31
tm_mon	int	months since January	0-11
tm_year	int	years since 1900	
tm_wday	int	days since Sunday	0-6
tm_yday	int	days since January 1	0-365
tm_isdst	int	Daylight Saving Time flag	
*/


class RTCTime {
    private:
    stime_t stime;

    int day;
    Month month;
    int year;
    int hours;
    int minutes;
    int seconds;
    DayOfWeek day_of_week;
    SaveLight save_light;

    public:
    RTCTime();
    RTCTime(struct tm &t);
    RTCTime(int _day, Month _m, int _year, int _hours, int _minutes, int _seconds, DayOfWeek _dof, SaveLight _sl);
    ~RTCTime();
    
    /* setters */
    bool setDayOfMonth(int day); /* day from 1 to 31 */
    bool setMonthOfYear(Month m); /* month from 1 (January) to 12 (December) */
    bool setYear(int year); /* the year 1989 or 2022 */
    bool setHour(int hour); /* from 0 (midnight) to 23 */
    bool setMinute(int minute); /* from 0 to 59 */
    bool setSecond(int second); /* from 0 to 59 */
    bool setDayOfWeek(DayOfWeek d);
    bool setSaveLight(SaveLight sl);

    void setTM(struct tm &t);
    /* getters */
    int getDayOfMonth();
    Month getMont();
    int getYear();
    int getHour();
    int getMinutes();
    int getSeconds();
    DayOfWeek getDayOfWeek();
    
    time_t getUnixTime();
    struct tm getTmTime();
};



enum class Period {
    ONCE_EVERY_2_SEC,
    ONCE_EVERY_1_SEC,
    N2_TIMES_EVERY_SEC,
    N4_TIMES_EVERY_SEC,
    N8_TIMES_EVERY_SEC,
    N16_TIMES_EVERY_SEC,
    N32_TIMES_EVERY_SEC,
    N64_TIMES_EVERY_SEC,
    N128_TIMES_EVERY_SEC,
    N256_TIMES_EVERY_SEC
};

class AlarmMatch {
    private:
    unsigned int match;

    public:
    AlarmMatch();
    ~AlarmMatch();    
    void addMatchSecond();
    void addMatchMinute();
    void addMatchHour();
    void addMatchDay();
    void addMatchMonth();
    void addMatchYear();
    void addMatchDayOfWeek();
    void removeMatchSecond();
    void removeMatchMinute();
    void removeMatchHour();
    void removeMatchDay();
    void removeMatchMonth();
    void removeMatchYear();
    void removeMatchDayOfWeek();
    bool isMatchingSecond();
    bool isMatchingMinute();
    bool isMatchingHour();
    bool isMatchingDay();
    bool isMatchingMonth();
    bool isMatchingYear();
    bool isMatchingDayOfWeek();
    
};

class RTClock {
    private:
    bool is_initialized;
    
    public:
    RTClock();
    ~RTClock();

    bool begin();
    
    bool getTime(RTCTime &t);

    bool setPeriodicCallback(rtc_cbk_t fnc, Period p);
    bool setAlarmCallback(rtc_cbk_t fnc, RTCTime &t, AlarmMatch &m);
    bool isRunning();
    bool setTime(RTCTime &t); 
    bool setTimeIfNotRunning(RTCTime &t);

};



#endif
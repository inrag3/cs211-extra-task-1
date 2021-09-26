#include <iostream>
#include <assert.h>
using namespace std;

double seconds_difference(double time_1, double time_2)
{
    return time_2 - time_1;
}

double hours_difference(double time_1, double time_2)
{
    return (time_2 - time_1) / 3600;
}

double to_float_hours(int hours, int minutes, int seconds)
{
    assert(minutes >= 0 && minutes < 60);
    assert(seconds >= 0 && seconds < 60);
    return hours + minutes / 60.0 + seconds / 3600.0;
}

double to_24_hour_clock(double hours)
{
    assert(hours >= 0);
    auto integer{ int(hours) };
    auto fractional{ hours - integer };
    return integer % 24 + fractional;
}

int get_hours(int time_in_seconds)
{
    assert(time_in_seconds >= 0);
    return time_in_seconds / 3600 % 24;
}

int get_minutes(int time_in_seconds)
{
    assert(time_in_seconds >= 0);
    return (time_in_seconds % 3600) / 60;
}

int get_seconds(int time_in_seconds)
{
    assert(time_in_seconds >= 0);
    return (time_in_seconds % 3600) % 60;
}

double time_to_utc(int utc_offset, double time)
{
    return to_24_hour_clock(time - utc_offset + 24);;
}

double time_from_utc(int utc_offset, double time)
{
    return to_24_hour_clock(time + utc_offset + 24);
}

int main()
{
    //seconds_difference
    assert(fabs(seconds_difference(1800.0, 3600.0) - 1800.0) < DBL_EPSILON);
    assert(fabs(seconds_difference(3600.0, 1800.0) + 1800.0) < DBL_EPSILON);
    assert(fabs(seconds_difference(1800.0, 2160.0) - 360.0) < DBL_EPSILON);
    assert(fabs(seconds_difference(1800.0, 1800.0) - 0.0) < DBL_EPSILON);

    //hours_difference
    assert(fabs(hours_difference(1800.0, 3600.0) - 0.5) < DBL_EPSILON);
    assert(fabs(hours_difference(3600.0, 1800.0) + 0.5) < DBL_EPSILON);
    assert(fabs(hours_difference(1800.0, 2160.0) - 0.1) < DBL_EPSILON);
    assert(fabs(hours_difference(1800.0, 1800.0)) < DBL_EPSILON);

    //to_float_hours
    assert(fabs(to_float_hours(0, 15, 0) - 0.25) < DBL_EPSILON);
    assert(fabs(to_float_hours(2, 45, 9) - 2.7525) < DBL_EPSILON);
    assert(fabs(to_float_hours(1, 0, 36) - 1.01) < DBL_EPSILON);

    //to_24_hour_clock
    assert(fabs(to_24_hour_clock(24)) < DBL_EPSILON);
    assert(fabs(to_24_hour_clock(48)) < DBL_EPSILON);
    assert(fabs(to_24_hour_clock(25) - 1) < DBL_EPSILON);
    assert(fabs(to_24_hour_clock(4) - 4) < DBL_EPSILON);
    assert(fabs(to_24_hour_clock(28.5) - 4.5) < DBL_EPSILON);

    //get_hours
    assert(fabs(get_hours(3800) - 1) < DBL_EPSILON);
    assert(fabs(get_minutes(3800) - 3) < DBL_EPSILON);
    assert(fabs(get_seconds(3800) - 20) < DBL_EPSILON);

    //time_to_utc
    assert(fabs(time_to_utc(0, 12.0) - 12.0) < DBL_EPSILON);
    assert(fabs(time_to_utc(1, 12.0) - 11.0) < DBL_EPSILON);
    assert(fabs(time_to_utc(-1, 12.0) - 13.0) < DBL_EPSILON);
    assert(fabs(time_to_utc(-11, 18.0) - 5.0) < DBL_EPSILON);
    assert(fabs(time_to_utc(-1, 0.0) - 1.0) < DBL_EPSILON);
    assert(fabs(time_to_utc(-1, 23.0)) < DBL_EPSILON);

    //time_from_utc
    assert(fabs(time_from_utc(0, 12.0) - 12.0) < DBL_EPSILON);
    assert(fabs(time_from_utc(1, 12.0) - 13.0) < DBL_EPSILON);
    assert(fabs(time_from_utc(-1, 12.0) - 11.0) < DBL_EPSILON);
    assert(fabs(time_from_utc(6, 6.0) - 12.0) < DBL_EPSILON);
    assert(fabs(time_from_utc(-7, 6.0) - 23.0) < DBL_EPSILON);
    assert(fabs(time_from_utc(-1, 0.0) - 23.0) < DBL_EPSILON);
    assert(fabs(time_from_utc(-1, 23.0) - 22.0) < DBL_EPSILON);
    assert(fabs(time_from_utc(1, 23.0) - 0.0) < DBL_EPSILON);
}
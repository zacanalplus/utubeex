#include <stdio.h>

enum Weekdays {Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday};

int leap_year(int year);
enum Weekdays weekday(int year, int month, int day);

int main(int argc, char *argv[]) {
    for(int year = 1900; year < 2200; year++){
        if(weekday(year, 12, 25) == Sunday){
            printf("%d-12-25 is Sunday and year %d is %s.\n", year, year, leap_year(year) ? "leap year" : "not leap year");
        }
    }
    return 0;
}

int leap_year(int year){
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

/* Sunday = 0, Monday = 1,.., Saturday = 6 */
enum Weekdays weekday(int year, int month, int day){
    int adjustment, mm, yy;
    adjustment = (14 - month) / 12;
    mm = month + 12 * adjustment - 2;
    yy = year - adjustment;
    return (day + (13 * mm - 1) / 5 + yy + yy / 4 - yy / 100 + yy / 400) % 7;
}

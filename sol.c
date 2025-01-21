/*
Q19: You are given the following information, but you may prefer to do some research for yourself.

1 Jan 1900 was a Monday.
Thirty days has September,
April, June and November.
All the rest have thirty-one,
Saving February alone,
Which has twenty-eight, rain or shine.
And on leap years, twenty-nine.
A leap year occurs on any year evenly divisible by 4, but not on a century unless it is divisible by 400.
How many Sundays fell on the first of the month during the twentieth century (1 Jan 1901 to 31 Dec 2000)?*/


//Normal year has 365 days. Since 365 mod 7 = 1, 1 Jan 1901 is a Tuesday. Thus we will start from 6 Jan 1901

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isLeap(int year) {
    if (year % 4 != 0) return false;
    if (year % 100 == 0 && year % 400 != 0) return false;
    return true;
}

int main() {
    int day = 6;
    int month = 0; // for index purposes, we start month from 0.
    int year = 1901;

    int monthdays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    int sundays = 0;

    while (true) {
        day += 7;
        if (day > monthdays[month]) {
            day -= monthdays[month];
            month++;
        }
        if (month > 11) {
            year++; month = 0;
            monthdays[1] = isLeap(year) ? 29 : 28;
            if (year == 2001) break;
        }
        if (day == 1) sundays++;
    }

    printf("%d\n", sundays);
    return 0;
}
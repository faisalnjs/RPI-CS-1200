#include "time.h"

#include <iostream>
#include <vector>

Time::Time() {
  hour = 0;
  minute = 0;
  second = 0;
}

Time::Time(const int& setHour, const int& setMinute, const int& setSecond) {
  hour = setHour;
  minute = setMinute;
  second = setSecond;
}

int Time::getHour() const {
  return hour;
}

int Time::getMinute() const {
  return minute;
}

int Time::getSecond() const {
  return second;
}

void Time::setHour(int setHour) {
  hour = setHour;
}

void Time::setMinute(int setMinute) {
  minute = setMinute;
}

void Time::setSecond(int setSecond) {
  second = setSecond;
}

void Time::PrintAMPM() const {
  std::string AmPm = "am";
  int displayHour = hour;
  int displayMinute = minute;
  int displaySecond = second;
  if (displayHour >= 12) {
    AmPm = "pm";
    displayHour = displayHour - 12;
  }
  if (displayHour == 0) displayHour = 12;
  std::string displayHour2 = std::to_string(displayHour);
  std::string displayMinute2 = std::to_string(displayMinute);
  std::string displaySecond2 = std::to_string(displaySecond);
  if (displayHour < 10) displayHour2 = '0' + displayHour2;
  if (displayMinute < 10) displayMinute2 = '0' + displayMinute2;
  if (displaySecond < 10) displaySecond2 = '0' + displaySecond2;
  std::cout << displayHour2 << ":" << displayMinute2 << ":" << displaySecond2 << " " << AmPm << std::endl;
}
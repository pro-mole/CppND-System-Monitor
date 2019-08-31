#include <string>

#include "format.h"

using std::string;

const int DAY_IN_SECONDS = 24 * 60 * 60;
const int HOUR_IN_SECONDS = 60 * 60;

// DONE: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
  std::string timeString = "";

  long remaining_seconds = seconds;

  // [IMPROVE] Add Days to the format
  /*
  int days = seconds / DAY_IN_SECONDS;

  if (days > 0) {
      timeString += std::to_string(days);
      if (days > 1) {
          timeString += " days, ";
      }
      else {
          timeString += " day, ";
      }
  }

  remaining_seconds = remaining_seconds % DAY_IN_SECONDS;
  */
  int hours = remaining_seconds / HOUR_IN_SECONDS;
  timeString += std::to_string(hours) + ":";

  remaining_seconds = remaining_seconds % HOUR_IN_SECONDS;
  int minutes = remaining_seconds / 60;
  timeString += std::to_string(minutes) + ":";

  remaining_seconds = remaining_seconds % 60;
  timeString += std::to_string(remaining_seconds);

  return timeString;
}
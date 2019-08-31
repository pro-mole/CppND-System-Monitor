#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"
#include "process.h"

using std::string;
using std::to_string;
using std::vector;

// DONE
// Create a Process instance and initialize the data for its PID
Process::Process(int pid)
    : pID(pid),
      user(LinuxParser::User(pid)),
      command(LinuxParser::Command(pid)),
      ram(LinuxParser::Ram(pid)),
      uptime(LinuxParser::UpTime(pid)) {
  // Parse data from the /proc file to figure the CPU usage
  vector<std::string> procData = LinuxParser::CpuUtilization(pid);

  double processTime = std::stol(procData[LinuxParser::kUTime]) + std::stol(procData[LinuxParser::kSTime]);
  
  this->cpu = (processTime / sysconf(_SC_CLK_TCK) / this->uptime);
}

// DONE: Return this process's ID
int Process::Pid() { return this->pID; }

// DONE: Return this process's CPU utilization
float Process::CpuUtilization() { return this->cpu; }

// DONE: Return the command that generated this process
string Process::Command() { return this->command; }

// DONE: Return this process's memory utilization
string Process::Ram() { return this->ram; }

// DONE: Return the user (name) that generated this process
string Process::User() { return this->user; }

// DONE: Return the age of this process (in seconds)
long int Process::UpTime() { return this->uptime; }

// DOING: Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& a) const { return this->cpu < a.cpu; }
#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "linux_parser.h"
#include "process.h"
#include "processor.h"
#include "system.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// DOING: Return a container composed of the system's processes
vector<Process>& System::Processes() {
  // Remake the process vector
  processes_.clear();

  for (int pid : LinuxParser::Pids()) {
    Process P(pid);
    processes_.push_back(P);
  }

  return processes_;
}

// DOING: Return the system's kernel identifier (string)
std::string System::Kernel() { return LinuxParser::Kernel(); }

// DONE: Return the system's memory utilization
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

// DOING: Return the operating system name
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// DOING: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// DOING: Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// DOING: Return the number of seconds since the system started running
long int System::UpTime() { return LinuxParser::UpTime(); }
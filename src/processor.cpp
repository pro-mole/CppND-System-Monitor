#include "processor.h"
#include "linux_parser.h"

// Return the aggregate CPU utilization
// TODO - Optimize the code
float Processor::Utilization() {
  // Retrieve Aggregate CPU data
  std::vector<std::string> cpuStats = LinuxParser::CpuUtilization();

  // Split CPU data
  int user = std::stoi(cpuStats[LinuxParser::CPUStates::kUser_]),
  nice = std::stoi(cpuStats[LinuxParser::CPUStates::kNice_]),
  system = std::stoi(cpuStats[LinuxParser::CPUStates::kSystem_]),
  idle = std::stoi(cpuStats[LinuxParser::CPUStates::kIdle_]),
  iowait = std::stoi(cpuStats[LinuxParser::CPUStates::kIOwait_]),
  irq = std::stoi(cpuStats[LinuxParser::CPUStates::kIRQ_]),
  softirq = std::stoi(cpuStats[LinuxParser::CPUStates::kSoftIRQ_]),
  steal = std::stoi(cpuStats[LinuxParser::CPUStates::kSteal_]);
  
  int currentCpuTime =
      user + nice + system + idle + iowait + irq + softirq + steal;
  int currentIdleTime = idle + iowait;

  int diffCpuTime = currentCpuTime - totalCpuTime;
  int diffIdleTime = currentIdleTime - totalIdleTime;
  float usageTime = (diffCpuTime - diffIdleTime) / (float)diffCpuTime;

  this->totalCpuTime = currentCpuTime;
  this->totalIdleTime = currentIdleTime;

  return usageTime;
}
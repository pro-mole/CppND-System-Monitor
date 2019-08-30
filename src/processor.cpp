#include "processor.h"
#include "linux_parser.h"

// Return the aggregate CPU utilization
// TODO - Optimize the code
float Processor::Utilization() {
    // Retrieve Aggregate CPU data
    std::vector<std::string> cpuStats = LinuxParser::CpuUtilization();
    
    // Split CPU data
    int user = std::stoi(cpuStats[0]),
        nice = std::stoi(cpuStats[1]),
        system = std::stoi(cpuStats[2]),
        idle = std::stoi(cpuStats[3]),
        iowait = std::stoi(cpuStats[4]),
        irq = std::stoi(cpuStats[5]),
        softirq = std::stoi(cpuStats[6]),
        steal = std::stoi(cpuStats[7]),
        guest = std::stoi(cpuStats[8]),
        guest_nice = std::stoi(cpuStats[9]);

    int currentCpuTime = user + nice + system + idle + iowait + irq + softirq + steal;
    int currentIdleTime = idle + iowait;

    int diffCpuTime = currentCpuTime - totalCpuTime;
    int diffIdleTime = currentIdleTime - totalIdleTime;
    float usageTime = (diffCpuTime - diffIdleTime) / (float) diffCpuTime;

    this->totalCpuTime = currentCpuTime;
    this->totalIdleTime = currentIdleTime;

    return usageTime;
}
#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// DONE: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  string line;
  string header;

  float memTotal, memFree;

  std::ifstream memFile(kProcDirectory + kMeminfoFilename);
  if (memFile.is_open()) {
    while (std::getline(memFile, line)) {
      std::istringstream lineStream(line);
      lineStream >> header;

      if (header == "MemTotal:") {
        lineStream >> memTotal;
      }

      if (header == "MemFree:") {
        lineStream >> memFree;
      }
    }
  }

  return (memTotal - memFree) / memTotal;
}

// DONE: Read and return the system uptime
long LinuxParser::UpTime() {
  long uptime = 0;

  std::ifstream uptimeFile(kProcDirectory + kUptimeFilename);

  if (uptimeFile.is_open()) {
    std::string line;
    if (std::getline(uptimeFile, line)) {
      std::istringstream lineStream(line);
      lineStream >> uptime;
    }
  }

  return uptime;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// Read and return CPU utilization
// Returns a vector of 10 numbers, representing the CPU time components
vector<string> LinuxParser::CpuUtilization() {
  vector<string> cpuInfo{};
  string line;
  string header;

  std::ifstream cpuFile(kProcDirectory + kStatFilename);
  if (cpuFile.is_open()) {
    while (std::getline(cpuFile, line)) {
      std::istringstream lineStream(line);
      lineStream >> header;
      if (header == "cpu")  // Match CPU line
      {
        string value;
        while (!lineStream.eof()) {
          lineStream >> value;
          cpuInfo.push_back(value);
        }

        break;
      }
    }
  }

  cpuFile.close();
  return cpuInfo;
}

// Returns a number identified by a header in the stat file
int RetrieveFromStatFile(std::string header_id) {
  std::string line, header;

  std::ifstream statFile(LinuxParser::kProcDirectory +
                         LinuxParser::kStatFilename);
  if (statFile.is_open()) {
    while (std::getline(statFile, line)) {
      std::istringstream lineStream(line);
      lineStream >> header;

      if (header == header_id) {
        int value;
        lineStream >> value;
        return value;
      }
    }
  }

  return -1;
}

// DONE: Read and return the total number of processes
int LinuxParser::TotalProcesses() { return RetrieveFromStatFile("processes"); }

// DONE: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  return RetrieveFromStatFile("procs_running");
}

// DONE: Read and return the command associated with a process
string LinuxParser::Command(int pid) {
  std::string cmdLine;

  std::ifstream commandFile(kProcDirectory + std::to_string(pid) + kCmdlineFilename);
  if (commandFile.is_open()) {
    std::getline(commandFile, cmdLine);
    return cmdLine;
  }
  return string();
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid[[maybe_unused]]) { return string(); }

// DONE: Read and return the user ID associated with a process
string LinuxParser::Uid(int pid) {
  std::string line, header, uID;

  std::ifstream statusFile(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (statusFile.is_open()) {
    while (std::getline(statusFile, line)) {
      std::istringstream lineStream(line);

      lineStream >> header;
      if (header == "Uid:") {
        lineStream >> uID;
        return uID;
      }
    }
  }
  return string();
}

// DONE: Read and return the user associated with a process
string LinuxParser::User(int pid) {
  std::string userLine;
  std::string username, userpasswd, userid;
  std::string uid = LinuxParser::Uid(pid);

  std::ifstream passwdFile(kPasswordPath);
  if (passwdFile.is_open()) {
    while (std::getline(passwdFile, userLine)) {
      std::replace(userLine.begin(), userLine.end(), ':', ' ');

      std::istringstream userStream(userLine);
      userStream >> username;
      userStream >> userpasswd; // Throw away
      userStream >> userid;
      if (userid == uid) {
        return username;
      }
    }
  }
  return string();
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }
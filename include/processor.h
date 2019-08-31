#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // DOING: Declare any necessary private members
 private:
  int totalCpuTime{0};   // Total System CPU Time
  int totalIdleTime{0};  // Total System Idle CPU Time
};

#endif
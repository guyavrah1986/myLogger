#pragma once

#include <vector>

#include "../utils/utils.h"
#include "specificDestinationLoggerWriteInterface.h"

/* 
The purpose of this interface is to be able to add (if desired) some "extra"
logic that should be taken into account when writing log messages to the main
memory (RAM).
*/
class MemoryLoggerInterface
{
  public:
    /*
    This API dicates when and if it is possible to write log messages to the 
    main memory.
    */
    virtual bool MemoryLoggerIsAbleWriteToMemory(IN const std::string& logMsg) const = 0;
    
    /*
    This API "clears" the main memory from ALL messages written so far.
    */
    virtual void MemoryLoggerFlushMemory() = 0;
};

/*
This is a very simple implementation of the MemoryLoggerInterface. If you wish
to add more sophsticated mechanism to enforce when writting log messages to main
memory, you probably want to create your own implementation to the MemoryLoggerInterface.
*/
class BasicMemoryLogger : public MemoryLoggerInterface, public ILogMessageObserver
{
  public:
    BasicMemoryLogger();
    virtual ~BasicMemoryLogger();

    // Non copyable class
    BasicMemoryLogger(const BasicMemoryLogger& other) = delete;
    BasicMemoryLogger& operator=(const BasicMemoryLogger& rhs) = delete;

    virtual void WriteLogMessage(IN const std::string& logMsg) override;
    virtual bool MemoryLoggerIsAbleWriteToMemory(IN const std::string& logMsg) const override;
    virtual void MemoryLoggerFlushMemory() override;

  private:
    std::vector<char> m_memBuff;
    const size_t MAX_BUFF_SIZE = 1024;
};
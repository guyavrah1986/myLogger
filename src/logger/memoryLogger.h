#pragma once

#include <string>

#include "../utils/utils.h"

/* 
The purpose of this interface is to be able to add (if desired) some "extra"
logic that should be taken into account when writing log messages to the main
memory (RAM).
*/
class MemoryLoggerInterface
{
  public:
    /*
    This API actually writes the log message to the main memory.
    It does so, only it is possible.
    */
    virtual void MemoryLoggerWriteToMemory(IN const std::string& logMsg) = 0;
    
    /*
    This API dicates when and if it is possible to write log messages to the 
    main memory.
    */
    virtual bool MemoryLoggerIsAbleWriteToMemory() const = 0;
    
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
class BasicMemoryLogger : public MemoryLoggerInterface
{
    public:
        BasicMemoryLogger();
        virtual ~BasicMemoryLogger();

        virtual void MemoryLoggerWriteToMemory(IN const std::string& logMsg) override;
        virtual bool MemoryLoggerIsAbleWriteToMemory() const override;
        virtual void MemoryLoggerFlushMemory() override;
};
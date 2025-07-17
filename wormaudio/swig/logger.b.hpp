
// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include "bindings.h"


namespace binding
{
    class LoggerAdaptor : WrapperBase, public juce::Logger
    {
    public:
        LoggerAdaptor() = default;
        ~LoggerAdaptor() override
        {
            // Hopefully this class's lifetime will be managed by the target language
            juce::Logger::setCurrentLogger(nullptr);
        }

        virtual void logMessage(const std::string& message) = 0;

    protected:
        void logMessage(const juce::String &message) override
        {
            logMessage(message.toStdString());
        }
    };

    inline void setLogger(LoggerAdaptor* logger)
    {
        juce::Logger::setCurrentLogger(logger);
    }
}

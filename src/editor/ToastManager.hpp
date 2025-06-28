#pragma once

#include <string>

namespace ui
{
    class ToastManager
    {
    public:
        enum MessageType
        {
            INFO,
            WARNING,
            ERROR
        };

        static ToastManager& getInstance()
        {
            static ToastManager instance;

            return instance;
        }

        void addMessage(std::string, MessageType type);
    };
}

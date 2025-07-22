// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once
#include <memory>

#include "ListenerBase.hpp"

#define DISABLE_COPY(ClassName)\
    ClassName(const ClassName&) = delete;\
    ClassName& operator=(const ClassName&) = delete;

#define DISABLE_MOVE(ClassName)\
    ClassName(ClassName&&) = delete;\
    ClassName& operator=(ClassName&&) = delete;

#define ENABLE_DEFAULT_MOVE(ClassName)\
    ClassName(ClassName&&) = default;\
    ClassName& operator=(ClassName&&) = default;\

namespace signal_event
{
    /**
     * Provides an automatically deleted connection to a @link SignalType.
     * The listener will keep track of the target signal and will unregister itself on destruction.
     * Can be extended by a class or instantiated as a field.
     * @tparam Args Parameters of the callback function
     */
    template <typename... Args>
    class ListenerType
    {
        using SignalCallback = std::function<void(Args...)>;

        class UniqueListener : public ListenerBase<Args...>
        {
            friend class ListenerType;

        public:
            // Prevent moving or copying to ensure that the pointer held by a Signal remains valid (until destruction)
            DISABLE_COPY(UniqueListener)
            DISABLE_MOVE(UniqueListener)

            UniqueListener() = default;

            ~UniqueListener() override
            {
                if (target)
                {
                    target->unReg(this);
                    target = nullptr;
                }
            }

            void listen(UniqueSignal<Args...>* target_)
            {
                // Do nothing if they are the same
                if (target_ != target)
                {
                    if (target)
                        unListen(target);

                    target = target_;
                    target->reg(this);
                }
            }

            void unListen(UniqueSignal<Args...>* target_)
            {
                if (target && target_ == target)
                {
                    target->unReg(this);
                    target = nullptr;
                }
            }

            void unListen()
            {
                if (target)
                {
                    target->unReg(this);
                    target = nullptr;
                }
            }

        protected:
            void targetDestroyed(const UniqueSignal<Args...> *target_) override
            {
                if (target == target_)
                    target = nullptr;
            }

        private:
            UniqueSignal<Args...>* target;
        };

    public:
        ListenerType(): ptr(std::make_unique<UniqueListener>()) {}

        ListenerType(ListenerType&&) = default;
        ListenerType& operator=(ListenerType&&) = default;

        void listen(UniqueSignal<Args...>* target)
        {
            ptr->listen(target);
        }

        void listen(SignalType<Args...>& target)
        {
            ptr->listen(target.get());
        }

        void listen(SignalType<Args...>& target, SignalCallback callback_)
        {
            ptr->listen(target.get());
            setCallback(callback_);
        }

        void unListen()
        {
            ptr->unListen();
        }

        void setCallback(SignalCallback callback_)
        {
            ptr->listenerCallback = callback_;
        }

        UniqueListener* get()
        {
            return ptr.get();
        }

    private:
        std::unique_ptr<UniqueListener> ptr;
    };

    /**
     * Provides an automatically deleted connection to a @link SignalType.
     * The listener will keep track of the target signal and will unregister itself on destruction.
     * This version can listen to multiple signals.
     * Can be extended by a class or instantiated as a field.
     * @tparam Args Parameters of the callback function
     */
    template <typename... Args>
    class MultiListenerType
    {
        using SignalCallback = std::function<void(Args...)>;

        class UniqueMultiListener : public ListenerBase<Args...>
        {
            friend class MultiListenerType;

        public:
            DISABLE_COPY(UniqueMultiListener)
            DISABLE_MOVE(UniqueMultiListener)

            UniqueMultiListener() = default;

            ~UniqueMultiListener() override
            {
                for (auto& target : targets)
                {
                    target->unReg(this);
                }
            }

            void listen(UniqueSignal<Args...>* target)
            {
                // TODO: remove duplicates
                targets.push_back(target);
                target->reg(this);
            }

            void unListen(UniqueSignal<Args...>* target)
            {
                targets.erase(std::remove(targets.begin(), targets.end(), target->get()), targets.end());
                target->unReg(this);
            }

        protected:
            void targetDestroyed(const UniqueSignal<Args...> *target) override
            {
                targets.erase(std::remove(targets.begin(), targets.end(), target), targets.end());
            }

        private:
            std::vector<UniqueSignal<Args...>*> targets;
        };

    public:
        MultiListenerType(): ptr(std::make_unique<UniqueMultiListener>()) { }

        void listen(UniqueSignal<Args...>* target)
        {
            ptr->listen(target);
        }

        void listen(SignalType<Args...>& target)
        {
            ptr->listen(target.get());
        }

        void unListen(SignalType<Args...>& target)
        {
            ptr->unListen(target.get());
        }

        void setCallback(SignalCallback callback_)
        {
            ptr->listenerCallback = callback_;
        }

        UniqueMultiListener* get()
        {
            return ptr.get();
        }

    private:
        std::unique_ptr<UniqueMultiListener> ptr;
    };
}

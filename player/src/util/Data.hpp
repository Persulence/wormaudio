#pragma once

#include <memory>

#include "cereal/cereal.hpp"
#include "cereal/types/string.hpp"

#include "serialization_util.hpp"
#include "../signal/Signal.hpp"

namespace util
{
    template <typename T>
    struct ValueAdaptor;

    /**
     * Like juce::Value except type-safe and worse.
     * Listeners are attached to the reference-counted object, rather than the reference.
     * This allows them to be persistent when the parent object is moved.
     * @tparam T Value type to reference.
     */
    template <typename T>
    class Data
    {
    public:
        using OnChanged = signal_event::Callback<T&>;
        using Listener = typename OnChanged::Listener;
        using MultiListener = typename OnChanged::MultiListener;

        struct DataContainer
        {
            friend class Data;
            typename OnChanged::Signal onChange;
            T object;

            explicit DataContainer(T object_): object(object_)
            {

            }

            void notify()
            {
                onChange.emit(object);
            }

            ~DataContainer() = default;

        // private:
            PRIVATE_SERIALIZE(DataContainer)

            INTERNAL_SERIALIZE
            {
                ar(cereal::make_nvp("object", object));
            }
        };

        Data(): ptr(std::make_shared<DataContainer>(T{})) { }

        Data(T t): ptr(std::make_shared<DataContainer>(t)) { }

        void setupListener(typename OnChanged::Listener* listener, typename OnChanged::Signal::Callback callback)
        {
            ptr->onChange.setup(listener, callback);
        }

        void setupListener(typename OnChanged::Listener* listener)
        {
            ptr->onChange.setup(listener);
        }

        void setupListener(typename OnChanged::MultiListener* listener)
        {
            ptr->onChange.setup(listener);
        }

        void removeListener(typename OnChanged::Listener* listener)
        {
            ptr->onChange.unReg(listener);
        }

        void removeListener(typename OnChanged::MultiListener* listener)
        {
            ptr->onChange.unReg(listener);
        }

        T getValue() const
        {
            return ptr->object;
        }

        const T& operator*() const
        {
            return ptr->object;
        }

        void setValue(const T& other)
        {
            ptr->object = other;
            notify();
        }

        Data& operator=(const T& other)
        {
            setValue(other);
            return *this;
        }

        void notify()
        {
            // bool success = juce::MessageManager::callAsync([weak = std::weak_ptr{ptr}]
            // {
                // if (auto shared = weak.lock())
                // {
                    ptr->notify();
                // }
            // });

            // if (!success)
            // {
            //     ptr->notify();
            // }

            // assert(success && "Is JUCE message thread running?");
        }


    private:
        std::shared_ptr<DataContainer> ptr;

        FRIEND_CEREAL

        INTERNAL_SERIALIZE
        {
            ar(CEREAL_NVP(ptr));
        }
    };

    template <typename T>
    void setValue(juce::Value& value, const T& t)
    {
        value.getValueSource().setValue(t);
    }

    template <typename T>
    T getValue(const juce::Value& value)
    {
        return static_cast<T>(value.getValue());
    }

    // /**
    //  * Bridges juce::Value and Data.
    //  * Allows JUCE UI elements to be connected to objects that require the persistent callbacks of Data.
    //  * Maintains a reference to the Data data and the Value value.
    //  * Updates the other when one changes.
    //  * Must not be moved, otherwise the value listeners will be cleared.
    //  * @tparam T Value type to reference.
    //  */
    // template <typename T>
    // struct ValueAdaptor : juce::Value::Listener, Data<T>::Listener
    // {
    //     juce::Value value;
    //     Data<T> data;
    //
    //     /// Causes allocation of a new Data that will either be unused or replaced later.
    //     /// This is inefficient but convenient.
    //     explicit ValueAdaptor(): data(T{})
    //     {
    //     }
    //
    //     explicit ValueAdaptor(Data<T> data_):
    //         data(std::move(data_))
    //     {
    //         value.addListener(this);
    //         data.setupListener(this, [this](auto& t){ dataChanged(t); });
    //     }
    //
    //     void setData(Data<T> data_)
    //     {
    //         data.removeListener(this);
    //         data = data_;
    //         data.setupListener(this, [this](auto& t){ dataChanged(t); });
    //
    //         dataChanged(*data);
    //     }
    //
    //     void valueChanged(juce::Value &value) override
    //     {
    //         data = getValue<T>(value);
    //     }
    //
    //     void dataChanged(const T& newValue)
    //     {
    //         setValue<T>(value, newValue);
    //     }
    // };

    template<>
    inline std::string getValue<std::string>(const juce::Value& value)
    {
        return static_cast<juce::String>(value.getValue()).toStdString();
    }

    template<>
    inline void setValue<std::string>(juce::Value& value, const std::string& t)
    {
        value.setValue(juce::String{t});
    }

}

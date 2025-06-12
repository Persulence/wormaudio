#include "ElementBrowserPanel.hpp"

#include "FileDragSource.hpp"
#include "runtime/Runtime.hpp"

import Resource;
import ElementTypes;

// #define MEMFN(fn) std::bind(&fn, this)
// #define MEMFN(fn, arg1) [this](auto arg1){ fn(arg1); };

// auto thingy(auto fn, auto self)
// {
//     return std::bind(fn, self);
// }

// template <typename... Args>
// struct S
// {
//     static std::function<void(Args...)> thing(std::function<void(Args...)> fn)
//     {
//         const int size = sizeof...(Args);
//         return [](int i){};
//         Args...[0] arg0;
//         return []((Args...[0] a1){};
//     }
// };

ui::ElementBrowserPanel::ElementBrowserPanel(event::Event::Ptr event_):
    event(std::move(event_))
{
    addAndMakeVisible(listPanel);

    // std::function<void(int)> fn = MEMFN(ElementBrowserPanel::thing, igg);

    // auto f = &ElementBrowserPanel::thing;
    // f(this, 1);

    // S<int>::thing([](int i){});

    event->getElements().onChange.setup(this, [this]()
    {
        refreshElements();
    });
}

void ui::ElementBrowserPanel::paint(juce::Graphics &g)
{
    paintBackground(g);
}

void ui::ElementBrowserPanel::resized()
{
    listPanel.setBounds(getLocalBounds().withHeight(listPanel.getExpectedHeight()));
    listPanel.updateVisibilities();
}

void ui::ElementBrowserPanel::refreshElements()
{
    listPanel.refresh(event->getElements());
}

bool ui::ElementBrowserPanel::isInterestedInDragSource(const SourceDetails &dragSourceDetails)
{
    const auto source = dragSourceDetails.sourceComponent.get();

    if (dynamic_cast<FileDragSource*>(source))
        return true;

    return false;
}

void ui::ElementBrowserPanel::itemDropped(const SourceDetails &dragSourceDetails)
{
    auto source = dragSourceDetails.sourceComponent.get();
    if (auto other = dynamic_cast<FileDragSource*>(source))
    {
        // Create and register a new clip element
        auto resource = runtime::createResource(other->getFile());
        auto element = std::make_shared<element::ClipElement>(resource);
        auto handle = event->getElements().reg(element);
    }
}

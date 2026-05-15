#pragma once

#include "event.h"

#include <functional>
#include <vector>

class EventBus {
    std::vector<std::reference_wrapper<EventVisitor>> visitors;
    EventBus() = default;
public:
    static EventBus& instance();

    EventBus(const EventBus&) = delete;
    EventBus& operator=(const EventBus&) = delete;

    void subscribe(EventVisitor& visitor);
    void publish(const Event& event);
};

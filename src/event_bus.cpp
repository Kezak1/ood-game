#include "event_bus.h"
#include "event.h"

#include <functional>

EventBus& EventBus::instance() {
    static EventBus bus;
    return bus;
}

void EventBus::subscribe(EventVisitor& v) {
    visitors.push_back(v);
}

void EventBus::unsubscribe(EventVisitor& v) {
    std::erase_if(visitors, [&v](const std::reference_wrapper<EventVisitor>& ev) {
        return &ev.get() == &v;
    });
}

void EventBus::publish(const Event& event) {
    for(EventVisitor& v : visitors) {
        event.accept(v);
    }
}

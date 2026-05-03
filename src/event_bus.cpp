#include "event_bus.h"
#include "event.h"

EventBus& EventBus::instance() {
    static EventBus bus;
    return bus;
}

void EventBus::subscribe(EventVisitor& v) {
    visitors.push_back(v);
}

void EventBus::publish(const Event& event) {
    for(EventVisitor& v : visitors) {
        event.accept(v);
    }
}

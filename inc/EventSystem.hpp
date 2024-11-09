#pragma once

#ifndef _EVENT_SYSTEM_HPP_
#define _EVENT_SYSTEM_HPP_

#include <queue>
#include <unordered_map>
#include <functional>
#include "EventConfig.hpp"

template <class T>
using EventHandler = std::function<void(T&)>;

class EventSystem
{
public:
    template <class T>
    void subscribe(EventType eventType, EventHandler<T> handler)
    {
        subscribers[eventType].push_back([handler](Event& event) {
            handler(static_cast<T&>(event));
        });
    }

    template <class T>
    void unsubscribe(EventType eventType, EventHandler<T> handler)
    {
        auto& handlers = subscribers[eventType];
        handlers.erase(
            std::remove_if(handlers.begin(), handlers.end(),
                           [&handler](const std::function<void(Event&)>& h) {
                               // 比较两个函数是否相同
                               return h.target<void(T&)>() == handler.target<void(T&)>();
                           }),
            handlers.end());
    }

    void publish(Event& event)
    {
        for (const auto& handler : subscribers[event.getType()])
        {
            handler(event);
        }
    }

private:
    std::unordered_map<EventType, std::vector<std::function<void(Event&)>>> subscribers;
};
#endif // _EVENT_SYSTEM_HPP_

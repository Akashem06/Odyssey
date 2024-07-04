#ifndef STATE_MACHINE_TPP
#define STATE_MACHINE_TPP

#include "state_machine.hpp"
#include <iostream>

template <typename State>
void StateMachine<State>::add_transition(State from, State to, std::function<void()> action) {
    transitions[static_cast<size_t>(from)][static_cast<size_t>(to)] = { to, action };
}

template <typename State>
void StateMachine<State>::add_state(State current_state, std::function<void(StateMachine&)> action) {
    state_actions[static_cast<size_t>(current_state)] = action;
}

template <typename State>
void StateMachine<State>::transition_to(State to) {
    Transition transition = transitions[static_cast<size_t>(current_state)][static_cast<size_t>(to)];

    // Run the transition action
    if (transition.action) {
        transition.action();
    }
    current_state = transition.next_state;
}

template <typename State>
State StateMachine<State>::get_current_state() const {
    return current_state;
}

template <typename State>
void StateMachine<State>::run() {
    std::function<void(StateMachine&)> action;
    {
        std::lock_guard<std::mutex> lock(mtx);
        action = state_actions[current_state];
        if (action) {
            action(*this);
        }
    }
    // Unlock mutex and notify
    cv.notify_one();
}

template <typename State>
void StateMachine<State>::wait_task() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [this] { return true; });
}

#endif
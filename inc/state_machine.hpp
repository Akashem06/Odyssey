#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP

#include <mutex>
#include <vector>
#include <condition_variable>
#include <string>
#include <functional>

template <typename State>
class StateMachine {
    private:
        State current_state;

        std::mutex mtx;
        std::condition_variable cv;

        struct Transition {
            State next_state;
            std::function<void()> action;
        };

        // Matrix of Transitions (From -> To)
        std::vector<std::vector<Transition>> transitions;
        std::vector<std::function<void(StateMachine&)>> state_actions;

    public:
        StateMachine(State initial_state, size_t num_states) 
        :   current_state(initial_state),
            transitions(num_states, std::vector<Transition>(num_states)),
            state_actions(num_states) {};
        
        void add_transition(State from, State to, std::function<void()> action);

        void add_state(State current_state, std::function<void(StateMachine&)> action);

        void transition_to(State to);        

        void run();

        State get_current_state() const;

        void wait_task();
};

#include "state_machine.tpp"

#endif
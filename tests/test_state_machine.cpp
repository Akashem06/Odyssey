#include <chrono>
#include <thread>

#include "gtest/gtest.h"
#include "state_machine.hpp"

using namespace ::testing;

enum test_states { DRIVE_STATE, NEUTRAL_STATE, REVERSE_STATE, NUM_STATES };

test_states sample_vehicle_message = NEUTRAL_STATE;

void test_neutral_transition() { std::cout << "TRANSITIONED TO NEUTRAL" << std::endl; }

void test_neutral_input(StateMachine<test_states>& state_machine) {
    std::cout << "INSIDE NEUTRAL" << std::endl;
    if (sample_vehicle_message == DRIVE_STATE) {
        state_machine.transition_to(DRIVE_STATE);
    } else if (sample_vehicle_message == REVERSE_STATE) {
        state_machine.transition_to(REVERSE_STATE);
    }
}

void test_drive_transition() { std::cout << "TRANSITIONED TO DRIVE" << std::endl; }

void test_drive_input(StateMachine<test_states>& state_machine) {
    std::cout << "INSIDE DRIVE" << std::endl;
    if (sample_vehicle_message == NEUTRAL_STATE) {
        state_machine.transition_to(NEUTRAL_STATE);
    }
}

void test_reverse_transition() { std::cout << "TRANSITIONED TO REVERSE" << std::endl; }

void test_reverse_input(StateMachine<test_states>& state_machine) {
    std::cout << "INSIDE REVERSE" << std::endl;
    if (sample_vehicle_message == NEUTRAL_STATE) {
        state_machine.transition_to(NEUTRAL_STATE);
    }
}

TEST(StateMachineTest, state_transition) {
    StateMachine<test_states> test_machine(NEUTRAL_STATE, NUM_STATES);

    test_machine.add_state(NEUTRAL_STATE, test_neutral_input);
    test_machine.add_state(DRIVE_STATE, test_drive_input);
    test_machine.add_state(REVERSE_STATE, test_reverse_input);

    test_machine.add_transition(NEUTRAL_STATE, DRIVE_STATE, test_drive_transition);
    test_machine.add_transition(NEUTRAL_STATE, REVERSE_STATE, test_reverse_transition);
    test_machine.add_transition(DRIVE_STATE, NEUTRAL_STATE, test_neutral_transition);
    test_machine.add_transition(REVERSE_STATE, NEUTRAL_STATE, test_neutral_transition);

    sample_vehicle_message = NEUTRAL_STATE;
    test_machine.run();
    ASSERT_EQ(test_machine.get_current_state(), NEUTRAL_STATE);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    sample_vehicle_message = DRIVE_STATE;
    test_machine.run();
    test_machine.wait_task();
    ASSERT_EQ(test_machine.get_current_state(), DRIVE_STATE);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    test_machine.run();
    ASSERT_EQ(test_machine.get_current_state(), DRIVE_STATE);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    sample_vehicle_message = NEUTRAL_STATE;
    test_machine.run();
    test_machine.wait_task();
    ASSERT_EQ(test_machine.get_current_state(), NEUTRAL_STATE);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    sample_vehicle_message = REVERSE_STATE;
    test_machine.run();
    ASSERT_EQ(test_machine.get_current_state(), REVERSE_STATE);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    sample_vehicle_message = DRIVE_STATE;
    test_machine.run();
    ASSERT_EQ(test_machine.get_current_state(), REVERSE_STATE);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
};

#include <chrono>
#include <thread>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "mock/mock_sensor.hpp"
#include "sensor_aggregator.hpp"
#include "sensor_lib.hpp"

using namespace ::testing;

TEST(SensorDataAggregatorTest, add_sensor_and_process) {
    MOCK_Sensor sensor1;
    EXPECT_CALL(sensor1, read_data()).Times(5).WillRepeatedly(Return(69.0));

    MOCK_Sensor sensor2;
    EXPECT_CALL(sensor2, read_data()).Times(5).WillRepeatedly(Return(420.0));

    SensorDataAggregator aggregator(5);

    aggregator.add_sensor(&sensor1);
    aggregator.add_sensor(&sensor2);
    aggregator.start();

    std::this_thread::sleep_for(std::chrono::milliseconds(2500));

    aggregator.stop();
    ASSERT_TRUE(true);
}
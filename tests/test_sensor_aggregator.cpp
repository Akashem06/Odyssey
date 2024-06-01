#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <chrono>
#include <thread>

#include "mock/mock_sensor.hpp"
#include "sensor_aggregator.hpp"
#include "sensor_lib.hpp"

using namespace ::testing;

TEST(SensorDataAggregatorTest, add_sensor_and_process) {
    MOCK_Sensor sensor1;
    EXPECT_CALL(sensor1, read_data())
        .Times(5)
        .WillRepeatedly(Return(42.0));

    SensorDataAggregator aggregator(5);


    aggregator.add_sensor(&sensor1);
    aggregator.start();

    std::this_thread::sleep_for(std::chrono::milliseconds(2500));

    aggregator.stop();
    ASSERT_TRUE(true);
}
#ifndef MOCK_SENSOR_HPP
#define MOCK_SENSOR_HPP

#include "sensor_lib.hpp"
#include "gmock/gmock.h"

class MOCK_Sensor : public Sensor {
    public:
        MOCK_METHOD(float, read_data, (), (override));
};

#endif
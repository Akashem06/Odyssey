#ifndef SENSOR_LIB_HPP
#define SENSOR_LIB_HPP

class Sensor {
    public:
        Sensor() = default;
        virtual float read_data() = 0;
};

class TemperatureSensor : public Sensor {
    public:
        float read_data() override;
};

class HumiditySensor : public Sensor {
    public:
        float read_data() override;
};

class Accelerometer : public Sensor {
    public:
        float read_data() override;
};

class Gyroscope : public Sensor {
    public:
        float read_data() override;
};

class Magnetometer : public Sensor {
    public:
        float read_data() override;
};


#endif
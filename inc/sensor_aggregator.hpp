#ifndef SENSOR_AGGREGATOR_HPP
#define SENSOR_AGGREGATOR_HPP

#include "circular_buffer.hpp"
#include "sensor_lib.hpp"

#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <chrono>

class SensorDataAggregator {
    private:
        CircularBuffer<float> data_queue;
        std::vector <std::thread> threads_queue;
        std::thread processing_thread;
        std::mutex mtx;
        std::condition_variable cv;
        bool stop_flag;

        void sensor_task(Sensor *sensor);
        void process_data_task();
    
    public:
        explicit SensorDataAggregator(size_t num_sensors) : data_queue(num_sensors), stop_flag(false) {};

        void add_sensor(Sensor* sensor);

        void start();

        void stop();
};

#endif
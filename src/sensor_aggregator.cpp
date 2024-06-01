#include "sensor_aggregator.hpp"

void SensorDataAggregator::sensor_task(Sensor *sensor) {
    while (!stop_flag) {
        float data = sensor->read_data();
        try {
            data_queue.enqueue(data);
        } catch (const std::runtime_error& e) {
            break;
        }
        // Simulate Thread delay. Typically would be done through the RTOS
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void SensorDataAggregator::process_data_task() {
    while (!stop_flag) {
        try {
            float data = data_queue.dequeue();
            // Processing data task (Send OTA/Logging)
            std::cout << "Processed data: " << data << std::endl;
        } catch (const std::runtime_error& e) {
            if (data_queue.is_stopped() && data_queue.is_empty()) {
                break;
            }
        }
    }
}

void SensorDataAggregator::add_sensor(Sensor* sensor) {
    threads_queue.emplace_back(&SensorDataAggregator::sensor_task, this, sensor);
}

void SensorDataAggregator::start() {
    processing_thread = std::thread(&SensorDataAggregator::process_data_task, this);
}
    
void SensorDataAggregator::stop() {
    stop_flag = true;
    data_queue.stop();
    for (std::thread &thread : threads_queue) {
        if (thread.joinable()) {
            thread.join();
        }
    }

    if (processing_thread.joinable()) {
        processing_thread.join();
    }
}

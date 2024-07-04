#include "fir.hpp"

namespace DSP {

FIR_Filter::FIR_Filter(float *buffer, float *coeff, const uint8_t order) {
    this->output = 0.0f;
    this->buffer_index = 0;
    this->buffer = buffer;
    this->coeff = coeff;
    this->order = order;

    for (uint8_t i = 0; i < order; i++) {
        this->buffer[i] = 0.0f;
    }
}

float FIR_Filter::update(float input) {
    // Store latest input into the buffer
    buffer[buffer_index] = input;
    if (++buffer_index == order) {
        buffer_index = 0;
    }

    // Compute the new output signal via convulation
    // This is taking 2 signals and transforming it into 1
    output = 0;
    uint8_t sum_index = buffer_index;

    for (uint8_t i = 0; i < order; i++) {
        output += coeff[i] * buffer[sum_index];

        if (sum_index > 0) {
            sum_index--;
        } else {
            sum_index = order - 1;
        }
    }

    return output;
}

}  // namespace DSP
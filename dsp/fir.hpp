#ifndef FIR_HPP
#define FIR_HPP
#include <stdint.h>

namespace DSP {

class FIR_Filter {
    private:
        // This points to a buffer of stored measurements
        float *buffer;

        // This points to an array that holds the impulse response coefficents
        // FIR Filter uses weighted sums based on the impulse response coefficents
        // The coefficent is baesd on the sampling frequency, desired frequency response, and window function
        float *coeff;
        float output;
        uint8_t order;
        uint8_t buffer_index;
    public:
        FIR_Filter(float *buffer, float *coeff, const uint8_t order);

        float update(float input);
};

}

#endif
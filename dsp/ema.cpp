#include "ema.hpp"

namespace DSP {

void EMA_LowPassFilter::update_alpha(float alpha) {
    // Alpha clamping
    if (alpha >= 1.0f) {
        alpha = 1.0f;
    } else if (alpha <= 0.0f) {
        alpha = 0.0f;
    }
    this->alpha = alpha;
}

float EMA_LowPassFilter::filter(float input) {
    output = alpha * input + (1.0f - alpha) * output;
    return output;
}

EMA_LowPassFilter::EMA_LowPassFilter(float alpha) {
    update_alpha(alpha);
    this->output = 0;
}

void EMA_HighPassFilter::update_beta(float beta) {
    // Beta clamping
    if (beta >= 1.0f) {
        beta = 1.0f;
    } else if (beta <= 0.0f) {
        beta = 0.0f;
    }
    this->beta = beta;
}

float EMA_HighPassFilter::filter(float input) {
    output = (0.5) * (2 - beta) * (input - prev_input) + (1 - beta) * output;
    prev_input = input;
    return output;
}

EMA_HighPassFilter::EMA_HighPassFilter(float beta) {
    update_beta(beta);
    this->output = 0;
    this->prev_input = 0;
}

}  // namespace DSP

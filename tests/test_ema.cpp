#include "ema.hpp"
#include "gtest/gtest.h"

TEST(EMATest, Low_Pass) {
    DSP::EMA_LowPassFilter low_pass_filter(0.5f);

    ASSERT_EQ(low_pass_filter.filter(1.0f), 0.5f);
    ASSERT_EQ(low_pass_filter.filter(1.0f), 0.75f);
    ASSERT_EQ(low_pass_filter.filter(1.0f), 0.875f);

    ASSERT_EQ(low_pass_filter.filter(0.5f), 0.6875f);
    
    // Test clamping
    low_pass_filter.update_alpha(1.25);
    ASSERT_EQ(low_pass_filter.filter(1.0f), 1.0f);

    low_pass_filter.update_alpha(-5.65);
    ASSERT_EQ(low_pass_filter.filter(0.0f), 1.0f);
}

TEST(EMATest, High_Pass) {

}
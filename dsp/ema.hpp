#ifndef EMA_HPP
#define EMA_HPP

namespace DSP {

class EMA_LowPassFilter {
    private:
        /**
         * This controls the strength of the filtering
         * A high alpha results in a low filter strength
         * A low alpha increases filter strength
         */
        float alpha;
        float output;
    public:
        explicit EMA_LowPassFilter(float alpha);
        void update_alpha(float alpha);
        float filter(float input);
};

class EMA_HighPassFilter {
    private:
        /**
         * This controls the strength of the filtering
         * A high alpha results in a low filter strength
         * A low alpha increases filter strength
         */
        float beta;
        float prev_input;
        float output;
    public:
        explicit EMA_HighPassFilter(float beta);

        void update_beta(float beta);
        float filter(float input);
};

}

#endif
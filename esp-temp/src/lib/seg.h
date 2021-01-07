#pragma once
#define COMMON_CATHODE 1 
#define COMMON_ANODE 0

class FourDigitSevenSegment {
    private:
        const uint8_t* digit;
        const uint8_t* segment;
        uint8_t d_on;
        uint8_t d_off;
        uint8_t s_on; 
        uint8_t s_off;

        void s_zero();
        void s_one();
        void s_two();
        void s_three();
        void s_four();
        void s_five();
        void s_six();
        void s_seven();
        void s_eight();
        void s_nine();
        void s_c();
        void s_f();
    public:
        FourDigitSevenSegment(const uint8_t* d, const uint8_t* s, bool common);
        // return 0 if error in init, else return 1
        bool init();

        void d_all();
        void d_clear();
        void d(uint8_t n);
        
        void s_clear();
        void s(char n);
        
        void s_dot_on();
        void s_dot_off();
};

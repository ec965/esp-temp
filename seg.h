#pragma once
#define COMMON_CATHODE 1 
#define COMMON_ANODE 0

class FourDigitSevenSegment {
    private:
        const int* digit;
        const int* segment;
        int d_on;
        int d_off;
        int s_on; 
        int s_off;

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
    public:
        FourDigitSevenSegment(const int* d, const int* s, bool common);
        // return 0 if error in init, else return 1
        bool init();

        void d_all();
        void d_clear();
        void d(int n);
        
        void s_clear();
        void s(int n);
        void s_c();
        void s_f();
        
        void s_dot_on();
        void s_dot_off();
};

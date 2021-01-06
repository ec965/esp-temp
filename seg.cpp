#include <Arduino.h>
#include "seg.h"

FourDigitSevenSegment::FourDigitSevenSegment(const int* d, const int* s, bool common){
    digit = d;
    segment = s;
    switch (common){
        case COMMON_CATHODE:
            d_on=HIGH;
            d_off=LOW;
            s_on=LOW;
            s_off=HIGH;
            break;
        case COMMON_ANODE:
            d_on=LOW;
            d_off=HIGH;
            s_on=HIGH;
            s_off=LOW;
            break;
        default:
            d_on=-1;
            d_off=-1;
            s_on=-1;
            s_off=-1;
    }
}
        // return 0 if error in init, else return 1
bool FourDigitSevenSegment::init(){
    if (d_on==-1 || d_off==-1 || s_on==-1 || s_off==-1){
        return 0;
    }
    int i;
    for(i=0; i<4; i++){
        pinMode(digit[i], OUTPUT);
    }
    for(i=0; i<8; i++){
        pinMode(segment[i], OUTPUT);
    }
    return 1;
}

//-----DIGIT-----
void FourDigitSevenSegment::d_all(){
    int i;
    for(i=0; i<4; i++){
        digitalWrite(digit[i], d_on);
    }
}
void FourDigitSevenSegment::d_clear(){
    int i;
    for(i=0; i<4; i++){
        digitalWrite(digit[i], d_off);
    }
}
void FourDigitSevenSegment::d(int n){
    for(int i=0; i<4; i++){
        if (i == n){
            digitalWrite(digit[n], d_on);
        } else {
            digitalWrite(digit[i], d_off);
        }
    }
}

//------SEGMENT-----

void FourDigitSevenSegment::s_clear(){
    int i;
    for(i=0; i<8; i++){
        digitalWrite(segment[i], s_off);
    }
}

void FourDigitSevenSegment::s(int n){
    switch(n){
        case 0: 
            s_zero();
            break;
        case 1: 
            s_one();
            break;
        case 2: 
            s_two();
            break;
        case 3: 
            s_three();
            break;
        case 4: 
            s_four();
            break;
        case 5: 
            s_five();
            break;
        case 6: 
            s_six();
            break;
        case 7: 
            s_seven();
            break;
        case 8: 
            s_eight();
            break;
        case 9: 
            s_nine();
            break;
    }
}

void FourDigitSevenSegment::s_f(){
    digitalWrite(segment[0], s_on);
    digitalWrite(segment[1], s_off);
    digitalWrite(segment[2], s_off);
    digitalWrite(segment[3], s_on);
    digitalWrite(segment[4], s_on);
    digitalWrite(segment[5], s_on);
    digitalWrite(segment[6], s_off);
}
void FourDigitSevenSegment::s_c(){
    digitalWrite(segment[0], s_on);
    digitalWrite(segment[1], s_off);
    digitalWrite(segment[2], s_off);
    digitalWrite(segment[3], s_on);
    digitalWrite(segment[4], s_on);
    digitalWrite(segment[5], s_on);
    digitalWrite(segment[6], s_off);
}

void FourDigitSevenSegment::s_zero(){
    digitalWrite(segment[0], s_on);
    digitalWrite(segment[1], s_on);
    digitalWrite(segment[2], s_on);
    digitalWrite(segment[3], s_on);
    digitalWrite(segment[4], s_on);
    digitalWrite(segment[5], s_on);
    digitalWrite(segment[6], s_off);
}
void FourDigitSevenSegment::s_one(){
    digitalWrite(segment[0], s_off);
    digitalWrite(segment[1], s_on);
    digitalWrite(segment[2], s_on);
    digitalWrite(segment[3], s_off);
    digitalWrite(segment[4], s_off);
    digitalWrite(segment[5], s_off);
    digitalWrite(segment[6], s_off);
}
void FourDigitSevenSegment::s_two(){
    digitalWrite(segment[0], s_on);
    digitalWrite(segment[1], s_on);
    digitalWrite(segment[2], s_off);
    digitalWrite(segment[3], s_on);
    digitalWrite(segment[4], s_on);
    digitalWrite(segment[5], s_off);
    digitalWrite(segment[6], s_on);
}
void FourDigitSevenSegment::s_three(){
    digitalWrite(segment[0], s_on);
    digitalWrite(segment[1], s_on);
    digitalWrite(segment[2], s_on);
    digitalWrite(segment[3], s_on);
    digitalWrite(segment[4], s_off);
    digitalWrite(segment[5], s_off);
    digitalWrite(segment[6], s_on);
}
void FourDigitSevenSegment::s_four(){
    digitalWrite(segment[0], s_off);
    digitalWrite(segment[1], s_on);
    digitalWrite(segment[2], s_on);
    digitalWrite(segment[3], s_off);
    digitalWrite(segment[4], s_off);
    digitalWrite(segment[5], s_on);
    digitalWrite(segment[6], s_on);
}
void FourDigitSevenSegment::s_five(){
    digitalWrite(segment[0], s_on);
    digitalWrite(segment[1], s_off);
    digitalWrite(segment[2], s_on);
    digitalWrite(segment[3], s_on);
    digitalWrite(segment[4], s_off);
    digitalWrite(segment[5], s_on);
    digitalWrite(segment[6], s_on);
}
void FourDigitSevenSegment::s_six(){
    digitalWrite(segment[0], s_on);
    digitalWrite(segment[1], s_off);
    digitalWrite(segment[2], s_on);
    digitalWrite(segment[3], s_on);
    digitalWrite(segment[4], s_on);
    digitalWrite(segment[5], s_on);
    digitalWrite(segment[6], s_on);
}
void FourDigitSevenSegment::s_seven(){
    digitalWrite(segment[0], s_on);
    digitalWrite(segment[1], s_on);
    digitalWrite(segment[2], s_on);
    digitalWrite(segment[3], s_off);
    digitalWrite(segment[4], s_off);
    digitalWrite(segment[5], s_off);
    digitalWrite(segment[6], s_off);
}
void FourDigitSevenSegment::s_eight(){
    digitalWrite(segment[0], s_on);
    digitalWrite(segment[1], s_on);
    digitalWrite(segment[2], s_on);
    digitalWrite(segment[3], s_on);
    digitalWrite(segment[4], s_on);
    digitalWrite(segment[5], s_on);
    digitalWrite(segment[6], s_on);
}
void FourDigitSevenSegment::s_nine(){
    digitalWrite(segment[0], s_on);
    digitalWrite(segment[1], s_on);
    digitalWrite(segment[2], s_on);
    digitalWrite(segment[3], s_on);
    digitalWrite(segment[4], s_off);
    digitalWrite(segment[5], s_on);
    digitalWrite(segment[6], s_on);
}

void FourDigitSevenSegment::s_dot_on(){
    digitalWrite(segment[7], s_on);
}
void FourDigitSevenSegment::s_dot_off(){
    digitalWrite(segment[7], s_off);
}

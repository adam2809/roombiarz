#include "prox_sensor.h"

class prox_sensor{
    public:
        prox_sensor(prox_sensor_pin_t pin){
            _pin = pin;
        }

        int get_prox(){
            float volts = analogRead(_pin)*0.0048828125;
            int distance = 13*pow(volts, -1); 
            return distance <= MAX_PROX_VALUE ? distance : -1;
        }
        
        // int get_prox_filtered(){
        //     int prox=get_prox();
        //     if (get_prox() == -1){
        //         in_range_prox_repeates = 0;
        //         in_range_prox_sum = 0;
        //         return -1;
        //     }else{
        //         in_range_prox_repeates++;
        //         in_range_prox_sum 
        //         if (in_range_prox_repeates < FILTER_SIZE){
        //             return -1;
        //         }
                
        //     }
        // }
    private:
        prox_sensor_pin_t _pin;
        int in_range_prox_repeates = 0;
        int in_range_prox_sum = 0;
}; 
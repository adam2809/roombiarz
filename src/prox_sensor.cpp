#include "prox_sensor.h"

class prox_sensor{
    public:
        prox_sensor(prox_sensor_pin_t pin){
            _pin = pin;
            for (int i = 0; i < FILTER_SIZE; i++){
                filter.push_front(-1);
            }
            
        }

        int get_prox(){
            float volts = analogRead(_pin)*0.0048828125;
            int distance = 13*pow(volts, -1); 
            return distance <= MAX_PROX_VALUE ? distance : -1;
        }
        
        int get_prox_filtered(){
            filter.push_front(get_prox());
            filter.pop_back();
        
            int sum = 0;
            for (int val : filter){
                if (val == -1){
                    return -1;
                }else{
                    sum+=val;
                }
                
            }
            return sum/FILTER_SIZE;
        }

        bool is_wall_in_prox(){
            int prox = get_prox_filtered();
            return prox < 20 && prox != -1;
        }
    private:
        prox_sensor_pin_t _pin;
        std::deque<int> filter;
}; 
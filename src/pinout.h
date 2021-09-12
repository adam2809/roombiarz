enum driver_pin_t{
    IN1_DRIVER_PIN = 6,
    IN2_DRIVER_PIN = 5,
    IN3_DRIVER_PIN = 4,
    IN4_DRIVER_PIN = 3,

    ENA_DRIVER_PIN = 7,
    ENB_DRIVER_PIN = 2
};

#define MAX_PROX_VALUE 30
#define PROX_SENSOR_COUNT 3
enum prox_sensor_pin_t{
    PROX_SENSOR_CENTER = A0,
    PROX_SENSOR_RIGHT = A1,
    PROX_SENSOR_LEFT = A2
};

enum prox_sensor_led_pin_t{
    PROX_SENSOR_LED_CENTER = 8,
    PROX_SENSOR_LED_RIGHT = 9,
    PROX_SENSOR_LED_LEFT = 10
};

prox_sensor_led_pin_t all_led_pins[] = {
    PROX_SENSOR_LED_CENTER,
    PROX_SENSOR_LED_RIGHT,
    PROX_SENSOR_LED_LEFT
};

prox_sensor_pin_t all_prox_sensors[] = {
    PROX_SENSOR_CENTER,
    PROX_SENSOR_RIGHT,
    PROX_SENSOR_LEFT
};


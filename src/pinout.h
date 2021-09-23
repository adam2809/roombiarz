#ifndef PINOUT_H
#define PINOUT_H

enum driver_pin_t{
    IN1_DRIVER_PIN = 6,
    IN2_DRIVER_PIN = 5,
    IN3_DRIVER_PIN = 4,
    IN4_DRIVER_PIN = 3,

    ENA_DRIVER_PIN = 10,
    ENB_DRIVER_PIN = 9
};

#define MAX_PROX_VALUE 30
#define PROX_SENSOR_COUNT 3
enum prox_sensor_pin_t{
    PROX_SENSOR_CENTER = A2,
    PROX_SENSOR_RIGHT = A1,
    PROX_SENSOR_LEFT = A0
};

enum bumper_button_pin_t{
    BUMPER_BUTTON_LEFT = 12,
    BUMPER_BUTTON_RIGHT = 13
};

enum prox_sensor_led_pin_t{
    PROX_SENSOR_LED_CENTER = 9,
    // PROX_SENSOR_LED_CENTER_LEFT = 10,
    PROX_SENSOR_LED_RIGHT = 8,
    PROX_SENSOR_LED_LEFT = 11
};

enum joystick_pin{
    X_AXIS = A3,
    Y_AXIS = A4
};
#endif


/*
 * main.c
 *
 * Created: 13/2/2024
 *  Author: Miczki
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdint.h>


#define DIR_PORT PORTC
#define DIR_DDR DDRC
#define DIR_PIN PC0

#define SLEEP_PORT PORTC
#define SLEEP_DDR DDRC
#define SLEEP_PIN PC1

#define PWM_PORT PORTB
#define PWM_DDR DDRB
#define PWM_PIN PB3

#define SENSOR_DDR DDRC
#define SENSOR_PIN PINC
#define SENSOR_PIN PC2




//////////////////////////////////////////////////////// <-- initialize transporter

void transporter_speed_init() {
  
  TCCR2 |= (0x01 << WGM20) | (0x01 << WGM21); // fast pwm mode
  TCCR2 |= (0x01 << COM20) | (0x01 << COM21); // inverting mode
  TCCR2 |= (0x01 << CS20);                    // without prescaller

  OCR2 = 0;
}

void init_transporter() {
  DIR_DDR |= (0x01 << DIR_PIN);
  SLEEP_DDR |= (0x01 << SLEEP_PIN);
  SENSOR_DDR &= ~(0x01 << SENSOR_PIN);
  
  PWM_DDR |= (0x01 << PWM_PIN);

  transporter_speed_init();
}

////////////////////////////////////////////////////////




//////////////////////////////////////////////////////// <-- transporter operations

void setDirection(const uint8_t dir) {
  switch (dir) {
    case 0:
      DIR_PORT &= ~(0x01 << DIR_PIN);
      break;
    case 1:
      DIR_PORT |= (0x01 << DIR_PIN);
      break;
    default:
      break;
  }
}

void setSpeed(const uint8_t s) {
  if (s >= 0 && s <= 255) {
    OCR2 = s;
  }
}

void start() {
  SLEEP_PORT |= (0x01 << SLEEP_PIN);
}

void stop() {
  SLEEP_PORT &= ~(0x01 << SLEEP_PIN);
}

///////////////////////////////////////////////////////




/////////////////////////////////////////////////////// <-- uart



///////////////////////////////////////////////////////




int main() {

  DDRC |= (0x01 << PC0);
  PORTC |= (0x01 << PC0);

  while(1) {
    _delay_ms(500);
    PORTC ^= (0x01 << PC0);
  }

  return 0x00;
}

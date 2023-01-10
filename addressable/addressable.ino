#define PIN_NEO_PIXEL 2
#define NUM_PIXELS 100 // TODO

#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
#include <avr/power.h>
#endif

uint32_t color_array[NUM_PIXELS];
uint8_t bar_heights[NUM_PIXELS];
uint8_t hue = 0;

Adafruit_NeoPixel NeoPixel(NUM_PIXELS, PIN_NEO_PIXEL, NEO_GRB + NEO_KHZ800);

void update_strip()
{
	for (int i = 0; i < NUM_PIXELS; i++)
	{
		NeoPixel.setPixelColor(i, color_array[i]);
	}
	NeoPixel.show();
}

void ready_flash() {

	for (int i = 0; i < NUM_PIXELS; i++)
	{
		NeoPixel.setPixelColor(i, Adafruit_NeoPixel::ColorHSV(0, 255, 100));
	}
	NeoPixel.show();
	delay(1000);
	for (int i = 0; i < NUM_PIXELS; i++)
	{
		NeoPixel.setPixelColor(i, Adafruit_NeoPixel::ColorHSV(0, 255, 0));
	}
	NeoPixel.show();
}

void setup()
{
	NeoPixel.begin();
	Serial.begin(115200);
	while(!Serial);
	ready_flash();
}

void loop()
{
}

void serialEvent()
{
	Serial.readBytes(bar_heights, NUM_PIXELS);
	for(int i = 0; i < NUM_PIXELS; i++) {
		color_array[i] = Adafruit_NeoPixel::ColorHSV(hue, 255, bar_heights[i]);
	}
	hue += 20;
	update_strip();
}

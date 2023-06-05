#include <Arduino.h>
#include <BasicEncoder.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_NeoMatrix.h>

const int8_t WIDTH = 13;
const int8_t HEIGHT = 9;

const int PIN_MATRIX = 10;

const int ENCODER_LEFT_CLK = 6;
const int ENCODER_LEFT_DT = 5;
const int ENCODER_LEFT_SW = 4;

const int ENCODER_RIGHT_CLK = 9;
const int ENCODER_RIGHT_DT = 8;
const int ENCODER_RIGHT_SW = 7;

const uint16_t colors[] = {
	Adafruit_NeoMatrix::Color(255, 0, 0),
	Adafruit_NeoMatrix::Color(255, 255, 0),
	Adafruit_NeoMatrix::Color(0, 255, 0),
	Adafruit_NeoMatrix::Color(0, 255, 255),
	Adafruit_NeoMatrix::Color(0, 0, 255),
	Adafruit_NeoMatrix::Color(255, 0, 255),
};
const size_t NUM_COLORS = 6;

BasicEncoder encoderLeft(ENCODER_LEFT_DT, ENCODER_LEFT_CLK);
BasicEncoder encoderRight(ENCODER_RIGHT_DT, ENCODER_RIGHT_CLK);

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(
	WIDTH,
	HEIGHT,
	PIN_MATRIX,
	NEO_MATRIX_BOTTOM + NEO_MATRIX_RIGHT + NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
	NEO_GRB + NEO_KHZ800);

void setup()
{
	pinMode(LED_BUILTIN, OUTPUT);
	Serial.begin(9600);
	Serial.println();

	matrix.begin();
	matrix.setBrightness(50);
	matrix.show();

	// matrix_setup(mqttBri);

	// well, hope we are OK, let's draw some colors first :)
	// testMatrix();

	// matrix_fill(0, 0, 0);
	// matrix_update();

	Serial.println("Setup done...");
}

uint8_t currentColor = 0;

void loop()
{
	encoderLeft.service();
	encoderRight.service();

	uint8_t x = encoderLeft.get_count();
	uint8_t y = encoderRight.get_count();
	x %= WIDTH;
	y %= HEIGHT;

	bool pointChanged = false;

	if (encoderLeft.get_change() || encoderRight.get_change())
	{
		pointChanged = true;
		Serial.print("X: ");
		Serial.print(x);
		Serial.print(" Y: ");
		Serial.println(y);
	}

	bool colorChange = false;

	if (!digitalRead(ENCODER_LEFT_SW))
	{
		currentColor--;
		colorChange = true;
	}

	if (!digitalRead(ENCODER_RIGHT_SW))
	{
		currentColor++;
		colorChange = true;
	}

	if (colorChange)
	{
		currentColor %= NUM_COLORS;
		Serial.print("Color: ");
		Serial.println(currentColor);
		delay(100);
	}

	if (colorChange || pointChanged)
	{
		matrix.writePixel(x, y, colors[currentColor]);
		matrix.show();
	}
}

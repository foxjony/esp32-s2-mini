// ESP32-S2 Mini Board
// Test Led, Button and UART 1, 2.

/*
=== Board GPIO ===
	GPIO15 - LED (Blue)
	GPIO0  - Button PROG (BOOT)

=== platformio.ini ===
	[env:lolin_s2_mini]
	platform = espressif32
	board = lolin_s2_mini
	framework = arduino
	monitor_speed = 115200

=== Program ===
	1. Connect to USB.
	2. Press Button [Reset]+[Boot].
	3. Unpress Button [Reset].
	4. Unpress Button [Boot].
	5. PlatformIO: Select COM Port.
	6. PlatformIO: Upload.

RAM:   [=         ]   8.1% (used 26644 bytes from 327680 bytes)
Flash: [==        ]  21.2% (used 277802 bytes from 1310720 bytes)
*/

#include <Arduino.h>

#define LED_PIN	15		// Boadr Blue Led (1 => On)
#define BTN_PIN 0		// Board Button (Press => 0)

uint32_t tik = 0;
uint32_t tim = 0;

void led_Flash(uint16_t t1, uint16_t t2, uint16_t n) {
	while (n) {
		n--;
		digitalWrite(LED_PIN, HIGH);
		delay(t1);
		digitalWrite(LED_PIN, LOW);
		delay(t2);
	}
}

void test_Button() {
	while (digitalRead(BTN_PIN) == LOW) {
		Serial.println("BTN USB");
		Serial1.println("BTN UART1");
		led_Flash(10, 100, 1);
	}
	tik = 0;
}

void test_Tim() {
	tim = 0;
	tik++;
	Serial.print("TIK USB: "); Serial.println(tik);
	Serial1.print("TIK UART1: "); Serial1.println(tik);
	led_Flash(10, 1000, 1);
}

void test_Uart() {
	char data[250];
	uint8_t m;

	// USB
	if (Serial.available()) {
		m = Serial.readBytesUntil('\n', data, sizeof (data)-1);
		data[m] = '\0';
		Serial.println(data);		// Send Eho
		led_Flash(10, 10, 1);
	}

	// UART1
	if (Serial1.available()) {
		m = Serial1.readBytesUntil('\n', data, sizeof (data)-1);
		data[m] = '\0';
		Serial1.println(data);		// Send Eho
		led_Flash(10, 10, 1);
	}
}

void setup() {
	pinMode(BTN_PIN, INPUT_PULLUP);
	pinMode(LED_PIN, OUTPUT);
	digitalWrite(LED_PIN, LOW);

	led_Flash(100, 400, 2);               		// Delay for start USB

	Serial.begin(115200);						// USB
	while(!Serial);
	Serial.println("START USB");

	Serial1.begin(115200, SERIAL_8N1, 18, 17);	// RX: GP18,  TX: GP17
	while(!Serial1);
	Serial1.println("START UART1");
}

void loop() {
	if (digitalRead(BTN_PIN) == LOW) {test_Button();}
	if (tim >= 1000) {test_Tim();} else {tim++; delay(1);}
	test_Uart();
}

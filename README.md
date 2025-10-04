# esp32-s2-mini
'''
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
'''

# ESP8266 Switch

A simple sketch that allows an ESP8266 GPIO pin to be toggled on and off over HTTP, _e.g._ for turning a set of lights on and off.

## Features

- WiFi SSID and PSK are set from environment variables.
- The ESP is sent into deep sleep mode if either the SSID or PSK are not provided.

## Getting Started

1. Make sure your board has an appropriate listing in the `platformio.ini` file. PRs are welcome if your board isn't supported yet!
2. Change the value of the `LED_GPIO` preprocessor token in `main.cpp` to something that is compatible with your board.
3. Export the following enviroment variables for the SSID and password of the network you want the ESP to connect to:

   ```Bash
   export WIFI_SSID='\"my\ ssid\ name\"'
   export WIFI_PASS='\"my\ password\"'
   ```

   Refer to the [PlatformIO documentation](https://docs.platformio.org/en/latest/projectconf/dynamic_variables.html) for more information about escaped characters.

4. Use the plafrotmio CLI to upload the sketch, _e.g._ for a NodeMCU v2 board, run:
   ```Bash
   pio run -e nodemcuv2 -t upload
   ```

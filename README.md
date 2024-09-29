# Weather Monitoring System Using IoT

This project is a weather and air quality monitoring system built using NodeMCU, DHT11, MQ135 sensors, and ThingSpeak for remote data logging. The system displays environmental parameters such as temperature, humidity, and air quality on an LCD screen and sends the data to the Blynk app and ThingSpeak for real-time monitoring.

## Features

- **Weather Monitoring**: Monitors temperature and humidity using the DHT11 sensor.
- **Air Quality Monitoring**: Uses the MQ135 gas sensor to measure air quality (AQI).
- **LCD Display**: Displays temperature, humidity, and air quality data in real-time on a 16x2 LCD.
- **ThingSpeak Integration**: Sends collected data to the ThingSpeak platform for remote monitoring.
- **WiFi Connectivity**: NodeMCU connects to WiFi for data transmission to the cloud.
- **Data Logging**: Real-time weather data is updated and logged on ThingSpeak every 20 seconds.

## Components

- **NodeMCU**: Microcontroller for WiFi-based IoT functionality.
- **DHT11**: Sensor for measuring temperature and humidity.
- **MQ135**: Sensor for detecting air quality (CO2 levels, etc.).
- **16x2 LCD Display**: Visualizes data locally.
- **ThingSpeak**: Platform for logging and analyzing environmental data.
- **Blynk App**: Mobile application to monitor weather conditions in real-time.

## Setup Instructions

1. Clone the repository to your local machine.
2. Connect NodeMCU to DHT11 and MQ135 sensors as per the pin configurations in the code.
3. Set up a ThingSpeak account and create a channel to receive temperature, humidity, and air quality data.
4. Create a `secrets.h` file with the following contents:

    #define SECRET_SSID "Your_SSID"         // Your WiFi network name
    #define SECRET_PASS "Your_PASSWORD"     // Your WiFi network password
    #define SECRET_CH_ID Your_Channel_ID    // ThingSpeak channel ID
    #define SECRET_WRITE_APIKEY "Your_API_Key" // ThingSpeak Write API Key

5. Upload the code to your NodeMCU using the Arduino IDE.
6. Monitor the real-time data on the LCD and ThingSpeak dashboard.

## How it Works

- The **DHT11 sensor** measures the temperature and humidity in the environment.
- The **MQ135 sensor** detects air quality and outputs an air quality index (AQI) value.
- The NodeMCU reads data from these sensors and displays it on a 16x2 LCD screen.
- Simultaneously, the system sends the data to ThingSpeak at regular intervals (every 20 seconds), where users can visualize trends and patterns.
- The LCD screen updates in real-time, alternating between displaying air quality and temperature/humidity data.

## Libraries Used

- **DHT Sensor Library** for reading temperature and humidity data.
- **LiquidCrystal** for interfacing with the 16x2 LCD.
- **ThingSpeak** for sending sensor data to the cloud.
- **ESP8266WiFi** for WiFi communication.

## Future Improvements

- Integrating additional sensors (e.g., rain, wind speed) for more comprehensive weather data.
- Improving the UI for the mobile app (Blynk) to provide better data visualization.
- Adding offline data storage to log data locally when WiFi is not available.

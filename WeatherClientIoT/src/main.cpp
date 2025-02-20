#include <ESP8266WiFi.h>
#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <TimeLib.h>
#include <nlohmann/json.hpp>
#include <ArduinoJson.h>
#include "./dto/Location.h"
#include "./dto/WeatherRequest.h"
#include "./dto/Notification.h"
#include "./dto/WeatherResponse.h"
#include "./dto/InfoRequest.h"
#include "./dto/Device.h"
#include "./dto/Control.h"

// WiFi credentials
// const char *ssid = "SLT-LTE-WiFi";
// const char *password = "2JG78T5HRHQ";
const char *ssid = "rasiphone";
const char *password = "playwithheart";

// Server endpoint
// This will change
const String baseUrl = "http://172.20.10.3:8000/api/v0";
WiFiClient client;
WiFiUDP udp;
NTPClient timeClient(udp, "pool.ntp.org", 0, 3600000);

void setup()
{

	// wifi setting
	Serial.begin(115200);
	Serial.println();

	WiFi.begin(ssid, password);

	Serial.print("Connecting");
	while (WiFi.status() != WL_CONNECTED)
	{
		delay(500);
		Serial.print(".");
	}
	Serial.println("Connected to WiFi!");
	randomSeed(analogRead(0));
	timeClient.begin();
	timeClient.update();
}

void exitFromMain(String err)
{
	int i = 0;
	while (true)
	{
		if (i == 5)
			ESP.restart();
		Serial.print(err);
		delay(1000);
		i++;
	};
};

String dateTimeNow()
{
	timeClient.update();
	unsigned long currentEpoch = timeClient.getEpochTime();
	setTime(currentEpoch);
	String timestamp = String(year()) + "-" + String(month()) + "-" + String(day()) + "T" +
					   String(hour()) + ":" + String(minute()) + ":" + String(second());
	Serial.println("Date and Time is: " + timestamp);
	return timestamp;
};

String randWeatherRequest()
{
	Location deviceLocation("234/c, Gampaha, Sri Lanka", "7.1000", "80.2167");
	WeatherRequest request(dateTimeNow(), deviceLocation);
	String jsonPayload = request.toJson();
	Serial.println("random weather request:");
	Serial.println(jsonPayload);
	return jsonPayload;
};

String createInfoRequest()
{
	Location deviceLocation("234/c, Gampaha, Sri Lanka", "7.1000", "80.2167");
	Device device("Id0001", "IoT", "huawei", "fire_sensor", "v1.0.0", "hv_0022", "2024-08-10 10:1000", "13hr", deviceLocation);

	ConnectedDevice cd1("100", "sensor1", "tem_sensor", "huawei", "192.168.0.1", "e80::f1c7:548d:b29e:8ced");
	ConnectedDevice cd2("101", "sensor2", "hum_sensor", "huawei", "192.168.0.2", "e80::f1c7:548d:b29e:8cef");

	std::vector<ConnectedDevice> connected_devices;
	connected_devices.push_back(cd1);
	connected_devices.push_back(cd2);

	Network network("134.12.0.9", "fe80::f1c7:548d:b29e:8cbc", "myWifi", "0.78", connected_devices);

	InfoRequest inforReq(dateTimeNow(), deviceLocation, network);

	String jsonPayload = inforReq.toJson();
	Serial.println("create info request:");
	Serial.println(jsonPayload);

	return jsonPayload;
};

void deserializeSubscribers(const String &response, std::vector<String> &subscribers)
{
	JsonDocument doc;
	DeserializationError error = deserializeJson(doc, response);
	if (error)
	{
		Serial.print("JSON deserialization failed: ");
		Serial.println(error.f_str());
		exitFromMain("JSON deserialization failed");
	}

	if (!doc.is<JsonArray>())
	{
		Serial.println("JSON is not an array");
		exitFromMain("JSON deserialization failed: Not an array");
	}

	for (JsonVariant value : doc.as<JsonArray>())
	{
		if (value.is<String>())
		{
			subscribers.push_back(value.as<String>());
		}
		else
		{
			Serial.println("Non-string value found in the array, skipping...");
		}
	}
};

void createWeatherResponse(const String &response, WeatherResponse &weatherResponse)
{
	JsonDocument doc;
	DeserializationError error = deserializeJson(doc, response);
	if (error)
	{
		Serial.print("JSON deserialization failed: ");
		Serial.println(error.f_str());
		exitFromMain("JSON deserialization failed");
	}

	double temCurrentValue = doc["temperature"]["current_value"];
	double temMaxValue = doc["temperature"]["max_value"];
	double temMinValue = doc["temperature"]["min_value"];
	String temUnit = doc["temperature"]["unit"];

	Serial.println("temperature");
	Serial.println(temCurrentValue);
	const Temperature temperature = Temperature(temCurrentValue, temMaxValue, temMinValue, temUnit);

	const Humidity humidity = Humidity(doc["humidity"]["current_value"],
									   doc["humidity"]["unit"]);

	const Motion motion = Motion(doc["motion"]["last_detected"],
								 doc["motion"]["motion_detected"]);

	const String Desc = doc["description"];

	weatherResponse = WeatherResponse(temperature, humidity, motion, Desc);
};

Notification createNotification(std::vector<String> &subscribers, const WeatherResponse &weatherResponse)
{
	return Notification(subscribers, weatherResponse);
};

void loop()
{
	if (WiFi.status() == WL_CONNECTED)
	{
		String weatherInfo = createInfoRequest();
		std::vector<String> subscribers;
		WeatherResponse weatherResponse;

		HTTPClient http;

		http.begin(client, baseUrl + "/random-generated-number");
		http.addHeader("Content-Type", "application/json");
		int httpRes_rgn = http.GET();
		if (httpRes_rgn > 0)
		{
			String response = http.getString();
			Serial.println("Response from the /random-generated-number");
			Serial.println(response);
		}
		else
		{
			exitFromMain("Error in /random-generated-number");
		}
		http.end();

		http.begin(client, baseUrl + "/weather-info");
		http.addHeader("Content-Type", "application/json");
		int httpRes_weather = http.POST(weatherInfo);
		if (httpRes_weather > 0)
		{
			String response = http.getString();
			Serial.println("Response from the /weather-info");
			Serial.println(response);
			createWeatherResponse(response, weatherResponse);
		}
		else
		{
			exitFromMain("Error in /weather-info");
		}
		http.end();

		http.begin(client, baseUrl + "/subscribers");
		http.addHeader("Content-Type", "application/json");
		int httpRes_subscribers = http.GET();
		if (httpRes_subscribers > 0)
		{
			String response = http.getString();
			Serial.println("Response from the /subscribers");
			Serial.println(response);
			deserializeSubscribers(response, subscribers);
			for (size_t i = 0; i < subscribers.size(); ++i)
			{
				Serial.print("Subscriber ");
				Serial.print(i + 1);
				Serial.print(": ");
				Serial.println(subscribers[i]);
			}
		}
		else
		{
			exitFromMain("Error in /weather-info");
		}
		http.end();

		http.begin(client, baseUrl + "/notification");
		http.addHeader("Content-Type", "application/json");
		String notification = createNotification(subscribers, weatherResponse).toJson();
		int httpRes_notification = http.POST(notification);
		if (httpRes_notification > 0)
		{
			String response = http.getString();
			Serial.println("Response from the /notification");
			Serial.println(response);
		}
		else
		{
			exitFromMain("Error in /notification");
		}
		http.end();
	}
	else
	{
		Serial.println("WiFi not connected");
	}
}

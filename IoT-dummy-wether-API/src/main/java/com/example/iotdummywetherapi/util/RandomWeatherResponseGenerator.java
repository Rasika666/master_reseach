package com.example.iotdummywetherapi.util;

import com.example.iotdummywetherapi.config.ApplicationConfig;
import com.example.iotdummywetherapi.dto.WeatherResponse;
import org.apache.commons.math3.random.RandomDataGenerator;

import java.time.LocalDateTime;

public class RandomWeatherResponseGenerator {

    private final int tempCurrentValueMin;
    private final int tempCurrentValueMax;
    private final int tempMaxValueMin;
    private final int tempMaxValueMax;
    private final int tempMinValueMin;
    private final int tempMinValueMax;
    private final String tempUnit;

    private final int humidityCurrentValueMin;
    private final int humidityCurrentValueMax;
    private final String humidityUnit;

    public RandomWeatherResponseGenerator(ApplicationConfig config) {
        this.tempCurrentValueMin = config.getTemperature().getCurrentValueRange()[0];
        this.tempCurrentValueMax = config.getTemperature().getCurrentValueRange()[1];
        this.tempMaxValueMin = config.getTemperature().getMaxValueRange()[0];
        this.tempMaxValueMax = config.getTemperature().getMaxValueRange()[1];
        this.tempMinValueMin = config.getTemperature().getMinValueRange()[0];
        this.tempMinValueMax = config.getTemperature().getMinValueRange()[1];
        this.tempUnit = config.getTemperature().getUnit();

        this.humidityCurrentValueMin = config.getHumidity().getCurrentValueRange()[0];
        this.humidityCurrentValueMax = config.getHumidity().getCurrentValueRange()[1];
        this.humidityUnit = config.getHumidity().getUnit();
    }

    private WeatherResponse.Temperature temperature() {
        WeatherResponse.Temperature temperature = new WeatherResponse.Temperature();
        temperature.setUnit(tempUnit);
        temperature.setCurrent_value(RandomGeneratorUtil.getRandomDoubleNumber(tempCurrentValueMin, tempCurrentValueMax));
        temperature.setMax_value(RandomGeneratorUtil.getRandomDoubleNumber(tempMaxValueMin, tempMaxValueMax));
        temperature.setMin_value(RandomGeneratorUtil.getRandomDoubleNumber(tempMinValueMin, tempMinValueMax));
        return temperature;
    }

    private WeatherResponse.Humidity humidity() {
        WeatherResponse.Humidity humidity = new WeatherResponse.Humidity();
        humidity.setUnit(humidityUnit);
        humidity.setCurrent_value(RandomGeneratorUtil.getRandomDoubleNumber(humidityCurrentValueMin, humidityCurrentValueMax));
        return humidity;
    }

    private WeatherResponse.Motion motion() {
        WeatherResponse.Motion motion = new WeatherResponse.Motion();
        motion.setMotion_detected(RandomGeneratorUtil.getRandomTrueOrFalse());
        motion.setLast_detected(LocalDateTime.now());
        return motion;
    }

    private String description() {
        String[] temperatures = {"chilly", "mild", "warm", "hot", "freezing", "cool"};
        String[] conditions = {"clear", "cloudy", "sunny", "rainy", "stormy", "foggy", "windy"};
        String[] descriptors = {"with occasional gusts", "with scattered showers", "under clear skies", "with heavy downpours", "with high humidity", "and a calm breeze", "with thunder rumbling"};

        RandomDataGenerator randomDataGenerator = new RandomDataGenerator();
        String temperature = temperatures[randomDataGenerator.nextInt(0, temperatures.length - 1)];
        String condition = conditions[randomDataGenerator.nextInt(0, conditions.length - 1)];
        String descriptor = descriptors[randomDataGenerator.nextInt(0, descriptors.length - 1)];

        return String.format("The weather is %s and %s %s.", temperature, condition, descriptor);
    }

    public WeatherResponse execute() {
        WeatherResponse weatherResponse = new WeatherResponse();
        weatherResponse.setTemperature(temperature());
        weatherResponse.setHumidity(humidity());
        weatherResponse.setMotion(motion());
        weatherResponse.setDescription(description());
        return weatherResponse;
    }
}

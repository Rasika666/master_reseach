package com.example.iotdummywetherapi.config;

import lombok.Data;
import org.springframework.boot.context.properties.ConfigurationProperties;
import org.springframework.stereotype.Component;

@Component
@ConfigurationProperties(prefix = "app")
@Data
public class ApplicationConfig {

    private int randomNumberMin;
    private int randomNumberMax;
    private int delay;
    private Temperature temperature;
    private Humidity humidity;
    private String[] subscriptions;

    @Data
    public static  class Temperature {
        private int[] currentValueRange;
        private int[] maxValueRange;
        private int[] minValueRange;
        private String unit;
    }

    @Data
    public static class Humidity {
        private int[] currentValueRange;
        private String unit;
    }
}

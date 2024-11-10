package com.example.iotdummywetherapi.dto;

import lombok.Data;
import lombok.NoArgsConstructor;

import java.time.LocalDateTime;

@Data
@NoArgsConstructor
public class WeatherResponse {
    private Temperature temperature;
    @Data
    @NoArgsConstructor
    public static class Temperature {
        private double current_value;
        private double max_value;
        private double min_value;
        private String unit;
    }
    private Humidity humidity;
    @Data
    @NoArgsConstructor
    public static class Humidity {
        private double current_value;
        private String unit;
    }
    private Motion motion;
    @Data
    @NoArgsConstructor
    public static class Motion {
        private LocalDateTime last_detected;
        private boolean motion_detected;
    }

    private String description;
}

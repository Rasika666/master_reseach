package com.example.iotdummywetherapi.dto;

import jakarta.annotation.Nonnull;
import lombok.Data;
import lombok.NoArgsConstructor;
import java.time.LocalDateTime;
import java.util.List;

@Data
@NoArgsConstructor
public class WeatherRequest {
    @Nonnull
    private String timeStamp;

    private Location location;

    @Data
    @NoArgsConstructor
    public static class Location {
        private String address;
        @Nonnull
        private String latitude;
        @Nonnull
        private String longitude;
    }

    private Device device;

    @Data
    @NoArgsConstructor
    public static class Device {
        private String device_id;
        private String type;
        private String manufacturer;
        private String model;
        private String firmware_version;
        private String hardware_version;
        private String last_reboot;
        private String uptime;
        private Location location;

        @Data
        @NoArgsConstructor
        public static class Location {
            private String address;
            @Nonnull
            private String latitude;
            @Nonnull
            private String longitude;
        }
    }

}

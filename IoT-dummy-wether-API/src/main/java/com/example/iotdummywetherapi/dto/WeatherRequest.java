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

    private Network network;
    @Data
    @NoArgsConstructor
    public static class Network {
        private String ip_address;
        private String mac_address;
        private String ssid;
        private String signal_strength;
        private List<ConnectedDevice> connected_devices;
        @Data
        @NoArgsConstructor
        public static class ConnectedDevice {
            private String device_id;
            private String device_name;
            private String device_type;
            private String device_manufacturer;
            private String ip_address;
            private String mac_address;
        }
    }

    private Log logs;
    @Data
    @NoArgsConstructor
    public static class Log {
        private  List<EventLog> event_log;
        @Data
        @NoArgsConstructor
        public static class EventLog {
            private String timestamp;
            private String event;
        }
    }

}

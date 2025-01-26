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
    private SystemSettings systemSettings;
    @Data
    @NoArgsConstructor
    public static class SystemSettings {
        private AdminUser admin_user;
        @Data
        @NoArgsConstructor
        public static class AdminUser {
            private String username;
            private String password;
        }
        private Security security;
        @Data
        @NoArgsConstructor
        public static class Security {
            private String firewall_status;
            private String encryption;
            private List<String> open_ports;
        }
        private Policy policy;
        @Data
        @NoArgsConstructor
        public static class Policy {
            private boolean auto_updates;
            private String last_update_check;
            private String update_channel;
        }
    }
    private Control control;
    @Data
    @NoArgsConstructor
    public static class Control {
        private List<ActiveCommand> active_commands;
        @Data
        @NoArgsConstructor
        public static class ActiveCommand {
            private String command;
            private String status;
            private String timestamp;
        }
    }
}

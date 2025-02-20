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
}

package com.example.iotdummywetherapi.dto;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.util.List;

@Data
@AllArgsConstructor
@NoArgsConstructor
public class Notification {
    private List<String> subscribers;
    private WeatherResponse weather;
}

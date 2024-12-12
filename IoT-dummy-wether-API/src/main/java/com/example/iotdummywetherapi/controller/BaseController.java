package com.example.iotdummywetherapi.controller;

import com.example.iotdummywetherapi.config.ApplicationConfig;
import com.example.iotdummywetherapi.dto.Notification;
import com.example.iotdummywetherapi.dto.WeatherRequest;
import com.example.iotdummywetherapi.dto.WeatherResponse;
import com.example.iotdummywetherapi.util.RandomWeatherResponseGenerator;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;

import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardCopyOption;
import java.util.List;
import java.util.Objects;

import static com.example.iotdummywetherapi.util.RandomGeneratorUtil.getRandomIntNumber;

@RestController
@RequestMapping("api/v0")
public class BaseController {

    private static final Logger LOGGER = LoggerFactory.getLogger(BaseController.class);
    private static final String UPLOAD_DIR = "/tmp/upload";
    private final ApplicationConfig config;

    public BaseController(ApplicationConfig applicationConfig) {
        this.config = applicationConfig;
    }

    @GetMapping("random-generated-number")
    public ResponseEntity<Integer> randomNumber() {
        int randomIntNumber = getRandomIntNumber(config.getRandomNumberMin(), config.getRandomNumberMax());
        LOGGER.info("Generated random number: [{}]", randomIntNumber);
        return ResponseEntity.ok().body(randomIntNumber);
    }


    @PostMapping("weather-info")
    public ResponseEntity<WeatherResponse> weatherInfo(@RequestBody WeatherRequest weatherRequest) {
        WeatherResponse response = new RandomWeatherResponseGenerator(config).execute();
        LOGGER.info("Generated weather response: [{}]", response);
        return ResponseEntity.ok().body(response);
    }

    @GetMapping("/ping")
    public String ping() {
        LOGGER.info("Ping endpoint was called");
        return "pong";
    }

    @GetMapping("/subscribers")
    public ResponseEntity<List<String>> getSubscribers() {
        List<String> subscribers = List.of(config.getSubscriptions());
        LOGGER.info("Subscriber [{}]", subscribers);
        return ResponseEntity.ok().body(subscribers);
    }

    @PostMapping("/notification")
    public ResponseEntity<String> notification(@RequestBody Notification notification) {
        LOGGER.info("Notification is received [{}]", notification);
        return ResponseEntity.ok().body("notification received");
    }

    @PutMapping("/log")
    public ResponseEntity<String> logFile(@RequestParam("file") MultipartFile file) {
        LOGGER.info("File update endpoint called with file: {}", file.getOriginalFilename());

        try {
            Path uploadPath = Path.of(UPLOAD_DIR);
            if (!Files.exists(uploadPath)) {
                Files.createDirectories(uploadPath);
            }
            Path targetPath = uploadPath.resolve(Objects.requireNonNull(file.getOriginalFilename()));
            Files.copy(file.getInputStream(), targetPath, StandardCopyOption.REPLACE_EXISTING);

            LOGGER.info("File updated successfully: {}", file.getOriginalFilename());
            return ResponseEntity.ok("File updated successfully.");
        } catch (Exception e) {
            LOGGER.error("Error updating file: {}", file.getOriginalFilename(), e);
            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).body("Error updating file.");
        }
    }

}

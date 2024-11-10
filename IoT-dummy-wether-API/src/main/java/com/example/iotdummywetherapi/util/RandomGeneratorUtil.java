package com.example.iotdummywetherapi.util;

import org.apache.commons.math3.random.RandomDataGenerator;

public class RandomGeneratorUtil {

    public static int getRandomIntNumber(int lowerBound, int upperBound) {
        RandomDataGenerator randomGen = new RandomDataGenerator();
        return randomGen.nextInt(lowerBound, upperBound);
    }

    public static double getRandomDoubleNumber(int lowerBound, int upperBound) {
        RandomDataGenerator randomGen = new RandomDataGenerator();
        return randomGen.nextUniform(lowerBound, upperBound);
    }

    public static boolean getRandomTrueOrFalse() {
        RandomDataGenerator randomGen = new RandomDataGenerator();
        return randomGen.nextInt(0, 1) == 1;
    }

}

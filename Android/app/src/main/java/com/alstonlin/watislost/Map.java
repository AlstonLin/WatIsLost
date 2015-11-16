package com.alstonlin.watislost;

public class Map {

    private int id;
    private Building building;
    private String name, filename;
    private double topLeftLat, topLeftLong, botRightLat, botRightLong;

    public Map(int id, Building building, String name, String filename, double topLeftLat, double topLeftLong, double botRightLat, double botRightLong) {
        this.id = id;
        this.building = building;
        this.name = name;
        this.filename = filename;
        this.topLeftLat = topLeftLat;
        this.topLeftLong = topLeftLong;
        this.botRightLat = botRightLat;
        this.botRightLong = botRightLong;
    }

    public int getId() {
        return id;
    }

    public Building getBuilding() {
        return building;
    }

    public String getName() {
        return name;
    }

    public String getFilename() {
        return filename;
    }

    public double getTopLeftLat() {
        return topLeftLat;
    }

    public double getTopLeftLong() {
        return topLeftLong;
    }

    public double getBotRightLat() {
        return botRightLat;
    }

    public double getBotRightLong() {
        return botRightLong;
    }
}

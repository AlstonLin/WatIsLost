package com.alstonlin.watislost;

/**
 * Created by Alston on 11/15/2015.
 */
public class Node {
    private Map map;
    private Building building;
    private String name;
    private boolean visible;
    private double longitude, latitude, xPos, yPos;

    public Node(int id, Map map, boolean visible, Building building, String name, double longitude, double latitude, double xPos, double yPos) {
        this.id = id;
        this.map = map;
        this.visible = visible;
        this.building = building;
        this.name = name;
        this.longitude = longitude;
        this.latitude = latitude;
        this.xPos = xPos;
        this.yPos = yPos;
    }
    private int id;

    public int getId() {
        return id;
    }

    public Map getMap() {
        return map;
    }

    public Building getBuilding() {
        return building;
    }

    public String getName() {
        return name;
    }

    public double getLongitude() {
        return longitude;
    }

    public double getLatitude() {
        return latitude;
    }

    public double getxPos() {
        return xPos;
    }

    public double getyPos() {
        return yPos;
    }

    public boolean isVisible() {
        return visible;
    }
}

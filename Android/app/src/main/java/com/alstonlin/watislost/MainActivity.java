package com.alstonlin.watislost;

import android.app.Activity;
import android.content.Intent;
import android.content.res.AssetManager;
import android.graphics.Path;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.Spinner;
import android.widget.Toast;

import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.HashMap;

public class MainActivity extends Activity {

    public static final String FILENAME = "graph.json";
    private HashMap<Integer, Node> nodes;
    private HashMap<Integer, Map> maps;
    private HashMap<Integer, Building> buildings;

    private HashMap<String, Node> temp = new HashMap<>(); //TODO: Do this properly

    /**
     * Loads the given json file to the graph that will be used
     * for pathfinding. Shold be called before any other function is.
     *
     * @params json The json file, represented as a string, containing the graph info
     */
    private native void loadGraph(String json);
    /**
     * Uses Dijkstra's Algorithm to find a path between the two given
     * node's id. Use getNodeInfo() to get the ids.
     *
     * @params nodeFromId The id of the starting node
     * @params nodeToId The id of the ending node
     * @return An Array of integers representing the IDs of the Nodes to travel to for the path
     */
    private native int[] findPath(int nodeFromId, int nodeToId);
    /**
     * Use this to get information of all the Nodes on the graph.
     * @return An array of strings containing information of each node.
     * The first index is the node ID. The second index will have size
     * 3, with
     * [0] - node id,
     * [1] - map Id,
     * [2] - if the node should appear on the map (0 - false, 1 - true),
     * [3] - building id,
     * [4] - node name,
     * [5] - latitude of the location,
     * [6] - longitude of the location,
     * [7] - x location of the node on the map as a percentage of width,
     * [8] - y location as a percentage of height.
     */
    private native String[][] getNodeInfo();
    /**
     * Use this to get information of all the maps.
     * @return An array of strings containing information of each map.
     * The first index the information of each map. The second index contains
     * the individual pieces of information of each map. Indexes are
     * [0] - ID,
     * [1] - Name,
     * [2] - Building ID,
     * [3] - latitude of the top left corner,
     * [4] - longitude of the top left corner,
     * [5] - latitude of the bottom right corner,
     * [6] - longitude of the bottom right corner,
     * [7] - The filename of the image of the map
     */
    private native String[][] getMapInfo();
    /**
     * Use this to get information of all the buildings.
     * @Return an array of building information (2d). The first index
     * is for each building. The second is the information, in the format
     * [0] - Index,
     * [1] - Name
     */
    private native String[][] getBuildingInfo();

    static {
        System.loadLibrary("graph");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.selection_screen);
        buildings = new HashMap<>();
        nodes = new HashMap<>();
        maps = new HashMap<>();
        try {
            setupGraph();
            getGraphInfo();
            setupSpinners();
            setupSubmit();
        } catch (IOException e) {
            e.printStackTrace();
            Toast.makeText(this, "Something went wrong when loading the map :(", Toast.LENGTH_LONG).show();
        }
    }


    private void setupGraph() throws IOException{
        //Gets the File from Assets
        AssetManager manager = getApplicationContext().getAssets();
        InputStream stream = manager.open(FILENAME);
        //Reads the Stream
        int size = stream.available();
        byte[] buffer = new byte[size];
        stream.read(buffer);
        stream.close();
        //Loads Graph
        loadGraph(new String(buffer));
    }

    private void getGraphInfo(){
        String[][] nodeInfo = getNodeInfo();
        String[][] mapInfo = getMapInfo();
        String[][] buildingInfo = getBuildingInfo();
        setupBuildings(buildingInfo);
        setupMaps(mapInfo);
        setupNodes(nodeInfo);
    }

    private void setupNodes(String[][] nodeInfo){
        //TODO: Validation; e.g. No repeat of IDs
        for (int i = 0; i < nodeInfo.length; i++){
            int id = Integer.parseInt(nodeInfo[i][0]);
            int mapId = Integer.parseInt(nodeInfo[i][1]);
            boolean visible = Integer.parseInt(nodeInfo[i][2]) == 1;
            int buildingId = Integer.parseInt(nodeInfo[i][3]);
            String name = nodeInfo[i][4];
            double lat = Double.parseDouble(nodeInfo[i][5]);
            double lon = Double.parseDouble(nodeInfo[i][6]);
            double xPos = Double.parseDouble(nodeInfo[i][7]);
            double yPos = Double.parseDouble(nodeInfo[i][8]);
            Node node = new Node(id, maps.get(mapId), visible, buildings.get(buildingId), name, lon, lat, xPos, yPos);
            nodes.put(id, node);
            temp.put(node.getName(), node);
        }
    }

    private void setupMaps(String[][] mapInfo){
        for (int i = 0; i < mapInfo.length; i++){
            int id = Integer.parseInt(mapInfo[i][0]);
            String name = mapInfo[i][1];
            int buildingId = Integer.parseInt(mapInfo[i][2]);
            double longLeft = Double.parseDouble(mapInfo[i][3]);
            double latLeft = Double.parseDouble(mapInfo[i][4]);
            double longRight = Double.parseDouble(mapInfo[i][5]);
            double latRight = Double.parseDouble(mapInfo[i][6]);
            String filename = mapInfo[i][7];
            Map map = new Map(id, buildings.get(buildingId), name, filename, latLeft, longLeft, latRight, longRight);
            maps.put(id, map);
        }
    }

    private void setupBuildings(String[][] buildingInfo){
        for (int i = 0; i < buildingInfo.length; i++){
            int id = Integer.parseInt(buildingInfo[i][0]);
            String name = buildingInfo[i][1];
            Building building = new Building(id, name);
            buildings.put(id, building);
        }
    }

    /**
     * Opens the main map.
     * @param path The path taken
     */
    private void openMainWindow(ArrayList<Node> path){
        //TODO: Have a better way of doing this; This is hackathon code
        double[][] draws = new double[path.size()][2];
        for (int i = 0; i < path.size(); i++){
            draws[i][0] = path.get(i).getxPos(); //TODO: Fix this method name
            draws[i][1] = path.get(i).getyPos();
        }
        setContentView(R.layout.activity_main);
        PathView pv = (PathView) findViewById(R.id.map);
        pv.setPath(draws);
        ((Button)findViewById(R.id.back)).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = getIntent();
                finish();
                startActivity(intent);
            }
        });
    }

    private void setupSpinners(){
        //Spinner Declarations
        Spinner buildingStart = (Spinner) findViewById(R.id.buildingStart);
        Spinner nodeStart = (Spinner) findViewById(R.id.nodeStart);
        Spinner nodeEnd = (Spinner) findViewById(R.id.nodeEnd);
        Spinner buildingEnd = (Spinner) findViewById(R.id.buildingEnd);

        ArrayAdapter<String> bStartAdapter = new ArrayAdapter<String>(this, R.layout.element);
        ArrayAdapter<String> bEndAdapter = new ArrayAdapter<String>(MainActivity.this, R.layout.element);
        final ArrayAdapter<String> nStartAdapter = new ArrayAdapter<String>(this, R.layout.element);
        final ArrayAdapter<String> nEndAdapter = new ArrayAdapter<String>(this, R.layout.element);

        buildingStart.setAdapter(bStartAdapter);
        buildingEnd.setAdapter(bEndAdapter);
        nodeStart.setAdapter(nStartAdapter);
        nodeEnd.setAdapter(nEndAdapter);

        for (int key : buildings.keySet()){
            String name = buildings.get(key).getName();
            bStartAdapter.add(name);
            bEndAdapter.add(name);
        }

        buildingStart.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
                nStartAdapter.clear();
                for (int key : nodes.keySet()){
                    Node node = nodes.get(key);
                    if (node.isVisible() && node.getBuilding().getId() == position){
                        nStartAdapter.add(node.getName());
                    }
                }
            }

            @Override
            public void onNothingSelected(AdapterView<?> parent) {
                ArrayAdapter<String> bEndAdapter = (ArrayAdapter<String>) parent.getAdapter();
                bEndAdapter.clear();
            }
        });

        buildingEnd.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
                nEndAdapter.clear();
                for (int key : nodes.keySet()){
                    Node node = nodes.get(key);
                    if (node.isVisible() && node.getBuilding().getId() == position){
                        nEndAdapter.add(node.getName());
                    }
                }
            }

            @Override
            public void onNothingSelected(AdapterView<?> parent) {
                ArrayAdapter<String> nEndAdapter = (ArrayAdapter<String>) parent.getAdapter();
                nEndAdapter.clear();
            }
        });

    }

    private void setupSubmit(){
        Button submit = (Button) findViewById(R.id.submit);
        submit.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Spinner nodeStart = (Spinner) findViewById(R.id.nodeStart);
                Spinner nodeEnd = (Spinner) findViewById(R.id.nodeEnd);
                Node nodeFrom = temp.get(nodeStart.getSelectedItem().toString());
                Node nodeTo = temp.get(nodeEnd.getSelectedItem().toString());
                int[] path = findPath(nodeFrom.getId(), nodeTo.getId());
                ArrayList<Node> nodesPath = new ArrayList<Node>();
                for (int i = 0; i < path.length; i++){
                    nodesPath.add(nodes.get(path[i]));
                }
                openMainWindow(nodesPath);
            }
        });
    }

}


/*
 * FOR TESTING PURPOSES.
 */

#include "engine.h" 

int main(void) {

    // CURRENT: Implement GUI.

    int w = 800;
    int h = 800;
    int cellSize = 4;
    int numCells = w / cellSize;

    Engine TestEngine;

    TestEngine.createWindow(w, h, "Ants");
    TestEngine.setFPS(60);
    TestEngine.createMap(cellSize);
    TestEngine.createNest(numCells/2-10, numCells/2-10, 20);
    TestEngine.createFood(numCells-40, numCells-40, 20);
    TestEngine.createFood(20, 20, 20);
    TestEngine.createColony();

    TestEngine.runSimulation();
    
    return 0;
}

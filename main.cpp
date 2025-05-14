#include "BoomEditWindow.h"
#include "include/AppState.h"

#include <QApplication>

std::shared_ptr<Level> createInitialLevel() {
    auto level = std::make_shared<Level>();

    // Vertices
    // Initial Room
    auto v1 = std::make_shared<Vertex>(-4.0f, -4.0f);
    auto v2 = std::make_shared<Vertex>(-4.0f,  4.0f);
    auto v3 = std::make_shared<Vertex>( 4.0f,  4.0f);
    auto v4 = std::make_shared<Vertex>( 4.0f, -4.0f);

    // Corridor
    auto v5 = std::make_shared<Vertex>(-1.0f,  4.0f);
    auto v6 = std::make_shared<Vertex>(-1.0f, 16.0f);
    auto v7 = std::make_shared<Vertex>( 1.0f, 16.0f);
    auto v8 = std::make_shared<Vertex>( 1.0f,  4.0f);

    // Second Room
    auto v9  = std::make_shared<Vertex>(-4.0f, 16.0f);
    auto v10 = std::make_shared<Vertex>(-4.0f, 24.0f);
    auto v11 = std::make_shared<Vertex>( 4.0f, 24.0f);
    auto v12 = std::make_shared<Vertex>( 4.0f, 16.0f);

    // Sectors
    auto room1 = std::make_shared<Sector>();
    auto corridor = std::make_shared<Sector>();
    auto room2 = std::make_shared<Sector>();

    // Walls for room1
    auto w1 = std::make_shared<Wall>(v1, v2); // west
    auto w2 = std::make_shared<Wall>(v2, v5); // north-left
    auto w3 = std::make_shared<Wall>(v5, v8, true, corridor); // portal
    auto w4 = std::make_shared<Wall>(v8, v3); // north-right
    auto w5 = std::make_shared<Wall>(v3, v4); // east
    auto w6 = std::make_shared<Wall>(v4, v1); // south

    room1->walls = { w1, w2, w3, w4, w5, w6 };
    room1->floorHeight = 0.0f;
    room1->ceilingHeight = 2.5f;

    // Walls for corridor
    auto w7 = std::make_shared<Wall>(v5, v6); // west
    auto w8 = std::make_shared<Wall>(v6, v7, true, room2); // north
    auto w9 = std::make_shared<Wall>(v7, v8); // east
    auto w10 = std::make_shared<Wall>(v8, v5, true, room1); // portal back to room1

    auto w11 = std::make_shared<Wall>(v6, v9); // connection to room2 (west portal split)
    auto w12 = std::make_shared<Wall>(v9, v10); // north-west room2
    auto w13 = std::make_shared<Wall>(v10, v11); // north
    auto w14 = std::make_shared<Wall>(v11, v12); // east
    auto w15 = std::make_shared<Wall>(v12, v7); // south-right
    auto w16 = std::make_shared<Wall>(v7, v6, true, corridor); // portal back to corridor

    corridor->walls = { w7, w8, w9, w10 };
    corridor->floorHeight = 0.0f;
    corridor->ceilingHeight = 2.5f;

    // Walls for room2
    auto w17 = std::make_shared<Wall>(v9, v10); // west
    auto w18 = std::make_shared<Wall>(v10, v11); // north
    auto w19 = std::make_shared<Wall>(v11, v12); // east
    auto w20 = std::make_shared<Wall>(v12, v7); // south portal
    auto w21 = std::make_shared<Wall>(v7, v6, true, corridor); // south-left
    auto w22 = std::make_shared<Wall>(v6, v9); // connect to west

    room2->walls = { w17, w18, w19, w20, w21, w22 };
    room2->floorHeight = 0.0f;
    room2->ceilingHeight = 2.5f;

    // Add sectors to level
    level->sectors = { room1, corridor, room2 };

    return level;
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    auto initialLevel = createInitialLevel();
    auto *appState = new AppState(initialLevel, &a);

    BoomEditWindow w(appState);
    w.show();
    return a.exec();
}

#include "BoomEditWindow.h"
#include "include/AppState.h"

#include <QApplication>
#include <QFile>

std::shared_ptr<Level> createInitialLevel() {
    auto level = std::make_shared<Level>();

    auto room = std::make_shared<Sector>(0.0f, 2.5f);

    // these shared_ptr<Vertex> can be re-used across walls so corners stay shared
    auto v1 = std::make_shared<Vertex>(-4, -4);
    auto v2 = std::make_shared<Vertex>(-4,  4);
    auto v3 = std::make_shared<Vertex>( 4,  4);
    auto v4 = std::make_shared<Vertex>( 4, -4);

    // this returns a Wall* you can later splice or split in O(1)
    room->createWall(v1, v2);
    room->createWall(v2, v3);
    room->createWall(v3, v4);
    room->createWall(v4, v1);

    // Add sectors to level
    level->sectors = { room };

    return level;
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile f(":/styles/assets/styles/boom.qss");
    if (f.open(QFile::ReadOnly)) {
        QString style = QLatin1String(f.readAll());
        a.setStyleSheet(style);
    }

    auto initialLevel = createInitialLevel();
    auto *appState = new AppState(initialLevel, &a);

    BoomEditWindow w(appState);
    w.show();
    return a.exec();
}

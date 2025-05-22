#include "include/LevelDocument.h"

LevelDocument::LevelDocument(QObject* parent)
    : QObject{parent},
    m_undoStack(this) {}

void LevelDocument::addSector(std::shared_ptr<Sector> sector) {

}

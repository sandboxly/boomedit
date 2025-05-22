#include "include/LevelDocument.h"

LevelDocument::LevelDocument(QObject* parent)
    : QObject{parent},
    m_undoStack(this) {}

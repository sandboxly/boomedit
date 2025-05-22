#ifndef LEVELDOCUMENT_H
#define LEVELDOCUMENT_H

#include <QObject>
#include <QUndoStack>

#include "models/Level.h"

class LevelDocument : public QObject
{
    Q_OBJECT
public:
    LevelDocument(QObject* parent = nullptr);
public slots:
    void addSector(std::shared_ptr<Sector> sector);
private:
    Level m_level;
    QUndoStack m_undoStack;
};

#endif // LEVELDOCUMENT_H

#ifndef ADDSECTORCOMMAND_H
#define ADDSECTORCOMMAND_H

#include <QUndoCommand>
#include "models/Level.h"
#include "models/Sector.h"

class AddSectorCommand : public QUndoCommand {
public:
    AddSectorCommand(std::shared_ptr<Level> level,
                     std::shared_ptr<Sector> newSector,
                     QUndoCommand* parent = nullptr)
        : QUndoCommand(parent),
        m_level(level),
        m_sector(std::move(newSector)) {
        setText("Add Sector");
    }

    void undo() override {
        auto &sectors = m_level->sectors;
        sectors.erase(std::remove(sectors.begin(), sectors.end(), m_sector), sectors.end());
    }

    void redo() override {
        m_level->sectors.push_back(m_sector);
    }
private:
    std::shared_ptr<Level> m_level;
    std::shared_ptr<Sector> m_sector;
};

#endif // ADDSECTORCOMMAND_H

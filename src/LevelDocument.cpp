#include "LevelDocument.h"
#include <QUndoCommand>

LevelDocument::LevelDocument(std::shared_ptr<Level> level, QObject *parent)
    : QObject(parent),
      m_currentLevel(std::move(level)) {}

std::shared_ptr<Level> LevelDocument::currentLevel() const {
    return m_currentLevel;
}

void LevelDocument::setCurrentLevel(std::shared_ptr<Level> level) {
    if (m_currentLevel != level) {
        m_currentLevel = level;
        emit levelChanged(m_currentLevel);
    }
}

void LevelDocument::onSectorShapeCompleted(const QRectF& worldRect) {
    // Create a new sector based on the rectangle
    auto sector = std::make_shared<Sector>(0.0f, 2.5f);

    auto v1 = std::make_shared<Vertex>(worldRect.topLeft().x(), worldRect.topLeft().y());
    auto v2 = std::make_shared<Vertex>(worldRect.bottomLeft().x(), worldRect.bottomLeft().y());
    auto v3 = std::make_shared<Vertex>(worldRect.bottomRight().x(), worldRect.bottomRight().y());
    auto v4 = std::make_shared<Vertex>(worldRect.topRight().x(), worldRect.topRight().y());

    sector->createWall(v1, v2);
    sector->createWall(v2, v3);
    sector->createWall(v3, v4);
    sector->createWall(v4, v1);

    // Create a QUndoCommand to add the sector to the level
    class AddSectorCommand : public QUndoCommand {
    public:
        AddSectorCommand(std::shared_ptr<Level> level, std::shared_ptr<Sector> sector)
            : m_level(std::move(level)), m_sector(std::move(sector)) {}

        void undo() override {
            auto it = std::find(m_level->sectors.begin(), m_level->sectors.end(), m_sector);
            if (it != m_level->sectors.end()) {
                m_level->sectors.erase(it);
            }
        }

        void redo() override {
            m_level->sectors.push_back(m_sector);
        }

    private:
        std::shared_ptr<Level> m_level;
        std::shared_ptr<Sector> m_sector;
    };

    auto command = new AddSectorCommand(m_currentLevel, sector);
    m_undoStack.push(command);

    // Emit the levelChanged signal
    emit levelChanged(m_currentLevel);
}

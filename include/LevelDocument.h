#ifndef LEVELDOCUMENT_H
#define LEVELDOCUMENT_H

#include <QObject>
#include <QUndoStack>
#include <memory>
#include "models/Level.h"

class LevelDocument : public QObject {
    Q_OBJECT

public:
    explicit LevelDocument(std::shared_ptr<Level> level, QObject *parent = nullptr);

    std::shared_ptr<Level> currentLevel() const;
    void setCurrentLevel(std::shared_ptr<Level> level);

signals:
    void levelChanged(std::shared_ptr<Level> newLevel);

public slots:
    void onSectorShapeCompleted(const QRectF& worldRect);

private:
    std::shared_ptr<Level> m_currentLevel;
    QUndoStack m_undoStack;
};

#endif // LEVELDOCUMENT_H

#ifndef APPSTATE_H
#define APPSTATE_H

#include <QObject>
#include <QVector2D>
#include <memory>
#include "models/Level.h"

class AppState : public QObject {
    Q_OBJECT

public:
    explicit AppState(std::shared_ptr<Level> level, QObject *parent = nullptr);

    std::shared_ptr<Level> currentLevel() const;
    void setCurrentLevel(std::shared_ptr<Level> level);

    QVector2D cameraPosition() const;
    void setCameraPosition(const QVector2D &position);

    QVector2D cameraLookAt() const;
    void setCameraLookAt(const QVector2D &lookAt);

signals:
    void currentLevelChanged(std::shared_ptr<Level> newLevel);
    void cameraPositionChanged(const QVector2D &newPosition);
    void cameraLookAtChanged(const QVector2D &newLookAt);

private:
    std::shared_ptr<Level> m_currentLevel;
    QVector2D m_cameraPosition;
    QVector2D m_cameraLookAt;
};

#endif // APPSTATE_H

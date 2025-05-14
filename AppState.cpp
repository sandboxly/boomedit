#include <QObject>
#include "include/AppState.h"

AppState::AppState(
    std::shared_ptr<Level> level,
    QObject *parent
) : QObject(parent),
    m_currentLevel(std::move(level)),
    m_cameraPosition(0.0f, 0.0f),
    m_cameraLookAt(0.0f, -1.0f) {}

std::shared_ptr<Level> AppState::currentLevel() const {
    return m_currentLevel;
}

void AppState::setCurrentLevel(std::shared_ptr<Level> level) {
    if (m_currentLevel != level) {
        m_currentLevel = level;
        emit currentLevelChanged(m_currentLevel);
    }
}

QVector2D AppState::cameraPosition() const {
    return m_cameraPosition;
}

void AppState::setCameraPosition(const QVector2D &position) {
    if (m_cameraPosition != position) {
        m_cameraPosition = position;
        emit cameraPositionChanged(m_cameraPosition);
    }
}

QVector2D AppState::cameraLookAt() const {
    return m_cameraLookAt;
}

void AppState::setCameraLookAt(const QVector2D &lookAt) {
    if (m_cameraLookAt != lookAt) {
        m_cameraLookAt = lookAt;
        emit cameraLookAtChanged(m_cameraLookAt);
    }
}

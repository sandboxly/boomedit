#ifndef APPSTATE_H
#define APPSTATE_H

#include <QObject>
#include <QVector2D>
#include <memory>
#include "models/Level.h"
#include "LevelDocument.h"

class AppState : public QObject {
    Q_OBJECT

public:
    explicit AppState(std::shared_ptr<LevelDocument> levelDocument, QObject *parent = nullptr);

    std::shared_ptr<LevelDocument> currentLevelDocument() const;
    void setCurrentLevelDocument(std::shared_ptr<LevelDocument> levelDocument);

    QVector2D cameraPosition() const;
    void setCameraPosition(const QVector2D &position);

    QVector2D cameraLookAt() const;
    void setCameraLookAt(const QVector2D &lookAt);

signals:
    void currentLevelDocumentChanged(std::shared_ptr<LevelDocument> newLevelDocument);
    void cameraPositionChanged(const QVector2D &newPosition);
    void cameraLookAtChanged(const QVector2D &newLookAt);

private:
    std::shared_ptr<LevelDocument> m_currentLevelDocument;
    QVector2D m_cameraPosition;
    QVector2D m_cameraLookAt;
};

#endif // APPSTATE_H

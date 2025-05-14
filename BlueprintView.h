#ifndef BLUEPRINTVIEW_H
#define BLUEPRINTVIEW_H

#include <QWidget>
#include <QVector2D>
#include "include/AppState.h"

class BlueprintView : public QWidget {
    Q_OBJECT
public:
    explicit BlueprintView(AppState &appState, QWidget *parent = nullptr);

    QVector2D viewportCenter() const;
    void setViewportCenter(const QVector2D &center);

    float zoomLevel() const;
    void setZoomLevel(const float zoom);

    float gridResolution() const;
    void setGridResolution(const float resolution);

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    // private fields
    AppState &m_appState;
    QVector2D m_viewportCenter {0.0f, 0.0f};
    float m_zoomLevel {25.0};
    float m_gridResolution {1.0f};
    float m_wheelDeltaAccumulator = 0.0f;
    bool m_isPanning = false;
    bool m_spaceHeld = false;
    QPoint m_lastMousePos;

    // private methods
    QPointF worldToScreen(const QVector2D& world, const QSize& widgetSize) const;
    void drawGrid(QPainter &painter);
    void drawWalls(QPainter &painter);
    void drawCorners(QPainter &painter);
};



#endif // BLUEPRINTVIEW_H

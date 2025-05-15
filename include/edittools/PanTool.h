#ifndef PANTOOL_H
#define PANTOOL_H

#pragma once

#include "IEditTool.h"
#include "views/blueprint/BlueprintCanvas.h"

class PanTool : public IEditTool {
    Q_OBJECT
public:
    explicit PanTool(
        BlueprintCanvas* canvas,
        QObject* parent = nullptr
        ) : IEditTool(parent), m_canvas(canvas) {}

    void onActivate() override {
        m_canvas->setCursor(Qt::OpenHandCursor);
    }

    void onDeactivate() override {}

    void mousePressEvent(QMouseEvent* event) override {
        if (!m_isPanning && event->button() == Qt::LeftButton) {
            m_isPanning = true;
            m_lastMousePos = event->pos();
            m_canvas->setCursor(Qt::ClosedHandCursor);
        }
    }

    void mouseReleaseEvent(QMouseEvent* event) override {
        if (m_isPanning && event->button() == Qt::LeftButton) {
            m_isPanning = false;
            m_canvas->setCursor(Qt::OpenHandCursor);
        }
    }

    void mouseMoveEvent(QMouseEvent* event) override {
        if (m_isPanning) {
            auto delta = event->pos() - m_lastMousePos;
            m_lastMousePos = event->pos();

            QVector2D offset(-delta.x() / m_canvas->zoomLevel(), delta.y() / m_canvas->zoomLevel());
            auto newViewportCenter = m_canvas->viewportCenter() + offset;
            m_canvas->setViewportCenter(newViewportCenter);
            m_canvas->update();
        }
    }

    void keyPressEvent(QKeyEvent* event) override {}
    void keyReleaseEvent(QKeyEvent* event) override {}
    void wheelEvent(QWheelEvent* event) override {}
    void paintOverlay(QPainter& p) override {}
private:
    BlueprintCanvas* m_canvas;
    bool m_isPanning {false};
    QPointF m_lastMousePos;
};



#endif // PANTOOL_H

#ifndef RECTANGLETOOL_H
#define RECTANGLETOOL_H

#include <QRectF>
#include <QPointF>
#include <QKeyEvent>
#include <cmath>                    // for std::round
#include "IEditTool.h"
#include "views/blueprint/BlueprintCanvas.h"

class RectangleTool : public IEditTool {
    Q_OBJECT
public:
    explicit RectangleTool(BlueprintCanvas* canvas)
        : IEditTool(canvas),
        m_canvas(canvas)
    {}

    EditToolType type() override { return EditToolType::Rectangle; }

    void onActivate() override {
        m_canvas->setCursor(Qt::CrossCursor);
    }

    void onDeactivate() override {}

    // ──────── mouse down ────────
    void mousePressEvent(QMouseEvent* event) override {
        if (event->button() == Qt::LeftButton) {
            m_drawing     = true;
            m_startScreen = event->pos();

            // world‐space anchor
            QPointF w = m_canvas->screenToWorld(m_startScreen);
            if (m_snapToGrid)  w = snapToGrid(w);

            m_rect.setTopLeft(    w );
            m_rect.setBottomRight(w );
            m_canvas->update();
        }
        else if (m_drawing && event->button() == Qt::RightButton) {
            m_drawing = false;
            m_canvas->update();
            emit cancelled();
        }
    }

    // ──────── drag ────────
    void mouseMoveEvent(QMouseEvent* event) override {
        if (!m_drawing) return;

        // live corner in world space
        QPointF nowW   = m_canvas->screenToWorld(event->pos());
        QPointF startW = m_canvas->screenToWorld(m_startScreen);

        if (m_snapToGrid) {
            nowW   = snapToGrid(nowW);
            startW = snapToGrid(startW);
        }

        m_rect = QRectF(startW, nowW).normalized();
        m_canvas->update();
        emit updated();
    }

    // ──────── mouse up ────────
    void mouseReleaseEvent(QMouseEvent* event) override {
        if (!m_drawing || event->button() != Qt::LeftButton) return;
        m_drawing = false;
        QRectF finalRect = m_rect.normalized();
        emit rectangleCreated(finalRect);
        emit SectorShapeCompleted(finalRect);
    }

    // ──────── key down ────────
    void keyPressEvent(QKeyEvent* event) override {
        // cancel on Esc
        if (m_drawing && event->key() == Qt::Key_Escape) {
            m_drawing = false;
            m_canvas->update();
            emit cancelled();
            return;
        }
    }

    void keyReleaseEvent(QKeyEvent*) override {}
    void wheelEvent     (QWheelEvent*) override {}

    // ──────── overlay paint ────────
    void paintOverlay(QPainter& p) override {
        if (!m_drawing) return;
        p.setPen(QPen(Qt::yellow,2,Qt::DashLine));
        QPointF tl = m_canvas->worldToScreen(m_rect.topLeft());
        QPointF br = m_canvas->worldToScreen(m_rect.bottomRight());
        p.drawRect(QRectF(tl, br).normalized());
    }

    void setSnapToGrid(bool enabled) {
        m_snapToGrid = enabled;
    }

signals:
    void updated();
    void rectangleCreated(const QRectF& worldRect);
    void cancelled();
    void SectorShapeCompleted(const QRectF& worldRect);

private:
    BlueprintCanvas* m_canvas;
    bool             m_drawing    = false;
    bool             m_snapToGrid = true;
    QPointF          m_startScreen;
    QRectF           m_rect;

    // helper: snap a world‐space point to the nearest grid‐intersection
    QPointF snapToGrid(const QPointF& w) const {
        float res = m_canvas->gridResolution();
        if (res <= 0.0f) return w;
        float x = std::round(w.x()*res)/res;
        float y = std::round(w.y()*res)/res;
        return { x, y };
    }
};

#endif // RECTANGLETOOL_H

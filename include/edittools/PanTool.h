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
        ) : IEditTool(parent), m_canvas(canvas){}
    void mousePressEvent(QMouseEvent* event) override {}
    void mouseReleaseEvent(QMouseEvent* event) override {}
    void mouseMoveEvent(QMouseEvent* event) override {}
    void keyPressEvent(QKeyEvent* event) override {}
    void keyReleaseEvent(QKeyEvent* event) override {}
    void wheelEvent(QWheelEvent* event) override {}
    void paintOverlay(QPainter& p) override {}
private:
    BlueprintCanvas* m_canvas;
};



#endif // PANTOOL_H

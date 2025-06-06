#ifndef SELECTTOOL_H
#define SELECTTOOL_H

#include "IEditTool.h"
#include "views/blueprint/BlueprintCanvas.h"

class SelectTool : public IEditTool {
    Q_OBJECT
public:
    explicit SelectTool(
        BlueprintCanvas* canvas
        ) : IEditTool(canvas), m_canvas(canvas){}

    EditToolType type() override { return EditToolType::Select; }

    void onActivate() override {
        m_canvas->setCursor(Qt::CrossCursor);
    }
    void onDeactivate() override {}
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

#endif // SELECTTOOL_H

#ifndef BLUEPRINTCANVASCONTROLLER_H
#define BLUEPRINTCANVASCONTROLLER_H

#include <QKeyEvent>
#include <QMouseEvent>
#include "IEditTool.h"

class BlueprintCanvas;

class BlueprintCanvasController : public QObject {
    Q_OBJECT
public:
    explicit BlueprintCanvasController(BlueprintCanvas* canvas);

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
private:
    BlueprintCanvas* m_canvas;
    IEditTool* m_previousTool {nullptr};
    bool m_spaceHeld;
    float m_wheelDeltaAccumulator = 0.0f;
};

#endif // BLUEPRINTCANVASCONTROLLER_H

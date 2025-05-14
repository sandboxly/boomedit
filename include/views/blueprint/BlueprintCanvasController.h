#ifndef BLUEPRINTCANVASCONTROLLER_H
#define BLUEPRINTCANVASCONTROLLER_H

#include <QKeyEvent>
#include <QMouseEvent>

class BlueprintCanvas;

class BlueprintCanvasController
{
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
    float m_wheelDeltaAccumulator = 0.0f;
    bool m_isPanning = false;
    bool m_spaceHeld = false;
    QPoint m_lastMousePos;
};

#endif // BLUEPRINTCANVASCONTROLLER_H

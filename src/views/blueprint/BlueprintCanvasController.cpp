#include <QKeyEvent>
#include <QMouseEvent>
#include "views/blueprint/BlueprintCanvas.h"
#include "views/blueprint/BlueprintCanvasController.h"
#include "edittools/PanTool.h"

BlueprintCanvasController::BlueprintCanvasController(BlueprintCanvas* canvas)
    : QObject(canvas),
    m_canvas(canvas),
    m_previousTool(canvas->activeTool()) {}


void BlueprintCanvasController::keyPressEvent(QKeyEvent* event) {
    if (!event->isAutoRepeat() && event->key() == Qt::Key_Space && !m_spaceHeld) {
        m_spaceHeld = true;
        m_previousTool = m_canvas->activeTool();
        PanTool* tool = new PanTool(m_canvas, this);
        tool->onActivate();
        m_canvas->setActiveTool(tool);
    }
}

void BlueprintCanvasController::keyReleaseEvent(QKeyEvent* event) {
    if (!event->isAutoRepeat() && event->key() == Qt::Key_Space && m_spaceHeld) {
        m_spaceHeld = false;
        if (m_previousTool) {
            m_previousTool->onActivate();
            m_canvas->setActiveTool(m_previousTool);
        }
    }
}

void BlueprintCanvasController::wheelEvent(QWheelEvent* event)
{
    constexpr float minZoom = 1.0f;
    constexpr float maxZoom = 100.0f;
    constexpr float zoomFactor = 1.1f; // Each step is ~10% zoom in/out

    if (event->angleDelta().y() > 0) {
        float newZoomLevel = std::min(maxZoom, m_canvas->zoomLevel() * zoomFactor);
        m_canvas->setZoomLevel(newZoomLevel);
    } else if (event->angleDelta().y() < 0) {
        float newZoomLevel = std::max(minZoom, m_canvas->zoomLevel() / zoomFactor);
        m_canvas->setZoomLevel(newZoomLevel);
    }

    m_canvas->update();
    event->accept();
}

void BlueprintCanvasController::mousePressEvent(QMouseEvent *event) {}
void BlueprintCanvasController::mouseMoveEvent(QMouseEvent *event) {}
void BlueprintCanvasController::mouseReleaseEvent(QMouseEvent *event) {}

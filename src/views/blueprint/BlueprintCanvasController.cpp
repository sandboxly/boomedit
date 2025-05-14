#include <QKeyEvent>
#include <QMouseEvent>
#include "../../../include/views/blueprint/BlueprintCanvas.h"
#include "../../../include/views/blueprint/BlueprintCanvasController.h"

BlueprintCanvasController::BlueprintCanvasController(BlueprintCanvas *canvas) : m_canvas(canvas) {}

void BlueprintCanvasController::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Space && !m_spaceHeld) {
        m_spaceHeld = true;
        m_canvas->setCursor(Qt::OpenHandCursor);
    } else if (event->key() == Qt::Key_G) {
        static const std::array<float, 6> gridResolutions = {0.0f, 0.25f, 0.5f, 1.0f, 2.0f, 4.0f};

        // Find the current index in the list
        auto it = std::find(gridResolutions.begin(), gridResolutions.end(), m_canvas->gridResolution());
        size_t index = (it != gridResolutions.end()) ? std::distance(gridResolutions.begin(), it) : 0;

        // Cycle to the next index
        m_canvas->setGridResolution(gridResolutions[(index + 1) % gridResolutions.size()]);

        m_canvas->update(); // trigger repaint
    }
}

void BlueprintCanvasController::keyReleaseEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Space) {
        m_spaceHeld = false;
        if (!m_isPanning) {
            m_canvas->setCursor(Qt::CrossCursor);
        }
    }
}

void BlueprintCanvasController::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && m_spaceHeld) {
        m_isPanning = true;
        m_lastMousePos = event->pos();
        m_canvas->setCursor(Qt::ClosedHandCursor);
    }
}

void BlueprintCanvasController::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isPanning) {
        QPoint delta = event->pos() - m_lastMousePos;
        m_lastMousePos = event->pos();

        // Adjust viewport center opposite to mouse drag, scaled by zoom
        QVector2D offset(-delta.x() / m_canvas->zoomLevel(), delta.y() / m_canvas->zoomLevel());
        auto newViewportCenter = m_canvas->viewportCenter() + offset;
        m_canvas->setViewportCenter(newViewportCenter);
        m_canvas->update();
    }
}

void BlueprintCanvasController::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && m_isPanning) {
        m_isPanning = false;
        if (m_spaceHeld)
            m_canvas->setCursor(Qt::OpenHandCursor);
        else
            m_canvas->unsetCursor();
    }
}

void BlueprintCanvasController::wheelEvent(QWheelEvent *event)
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

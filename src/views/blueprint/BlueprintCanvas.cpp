#include "../../../include/views/blueprint/BlueprintCanvas.h"
#include <QPainter>
#include <QColor>
#include <QKeyEvent>
#include <QPainterPath>

BlueprintCanvas::BlueprintCanvas(BlueprintModel& model, QWidget* parent) : QWidget(parent),
    m_model(model)
{
    m_controller = std::make_unique<BlueprintCanvasController>(this);
    m_renderer   = std::make_unique<BlueprintCanvasRenderer>(this);

    setMinimumSize(400, 400); // Optional: for testing layout
    setAutoFillBackground(false); // We paint manually
    setFocusPolicy(Qt::StrongFocus);
    setCursor(Qt::CrossCursor);
}

BlueprintModel BlueprintCanvas::model() const {
    return m_model;
}

QVector2D BlueprintCanvas::viewportCenter() const {
    return m_viewportCenter;
}

void BlueprintCanvas::setViewportCenter(const QVector2D &center) {
    m_viewportCenter = center;
    update();
}

float BlueprintCanvas::zoomLevel() const {
    return m_zoomLevel;
}

void BlueprintCanvas::setZoomLevel(const float zoom) {
    m_zoomLevel = zoom;
}

float BlueprintCanvas::gridResolution() const {
    return m_gridResolution;
}

void BlueprintCanvas::setGridResolution(const float resolution) {
    m_gridResolution = resolution;
}

void BlueprintCanvas::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QColor blueprintBlue(4, 87, 160); // Deep blueprint background
    painter.fillRect(rect(), blueprintBlue);

    m_renderer->draw(painter);
}

void BlueprintCanvas::keyPressEvent(QKeyEvent *event)
{
    m_controller->keyPressEvent(event);
}

void BlueprintCanvas::keyReleaseEvent(QKeyEvent *event)
{
    m_controller->keyReleaseEvent(event);
}

void BlueprintCanvas::mousePressEvent(QMouseEvent *event)
{
    m_controller->mousePressEvent(event);
}

void BlueprintCanvas::mouseMoveEvent(QMouseEvent *event)
{
    m_controller->mouseMoveEvent(event);
}

void BlueprintCanvas::mouseReleaseEvent(QMouseEvent *event)
{
    m_controller->mouseReleaseEvent(event);
}

void BlueprintCanvas::wheelEvent(QWheelEvent *event)
{
    m_controller->wheelEvent(event);
}

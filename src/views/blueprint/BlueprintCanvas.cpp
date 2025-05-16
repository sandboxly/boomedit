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

    m_activeTool->paintOverlay(painter);
}

void BlueprintCanvas::keyPressEvent(QKeyEvent *event)
{
    m_activeTool->keyPressEvent(event);
    m_controller->keyPressEvent(event);
}

void BlueprintCanvas::keyReleaseEvent(QKeyEvent *event)
{
    m_activeTool->keyReleaseEvent(event);
    m_controller->keyReleaseEvent(event);
}

void BlueprintCanvas::mousePressEvent(QMouseEvent *event)
{
    m_activeTool->mousePressEvent(event);
    m_controller->mousePressEvent(event);
}

void BlueprintCanvas::mouseMoveEvent(QMouseEvent *event)
{
    m_activeTool->mouseMoveEvent(event);
    m_controller->mouseMoveEvent(event);
}

void BlueprintCanvas::mouseReleaseEvent(QMouseEvent *event)
{
    m_activeTool->mouseReleaseEvent(event);
    m_controller->mouseReleaseEvent(event);
}

void BlueprintCanvas::wheelEvent(QWheelEvent *event)
{
    m_controller->wheelEvent(event);
}


IEditTool* BlueprintCanvas::activeTool() const {
    return m_activeTool;
}

void BlueprintCanvas::setActiveTool(IEditTool* tool) {
    if (tool && (!m_activeTool || tool != m_activeTool)) {
        m_activeTool = tool;
        update();
    }
}

QPointF BlueprintCanvas::screenToWorld(const QPointF& screen) {
    // Translate screen coords so that (0,0) is at widget center
    const float halfW = width()  * 0.5f;
    const float halfH = height() * 0.5f;

    // Undo the center translation
    float dx = screen.x() - halfW;
    float dy = screen.y() - halfH;

    // Undo the zoom scaling (and flip Y back)
    float worldX = dx / m_zoomLevel + m_viewportCenter.x();
    float worldY = -dy / m_zoomLevel + m_viewportCenter.y();

    return { worldX, worldY };
}

QPointF BlueprintCanvas::worldToScreen(const QPointF& world) {
    // Calculate offset from viewport center
    QPointF offset = {world.x() - m_viewportCenter.x(), world.y() - m_viewportCenter.y()};

    // Apply zoom (world units to pixels)
    QPointF scaled(offset.x() * m_zoomLevel, -offset.y() * m_zoomLevel); // Y-axis flipped

    // Translate to screen center
    return QPointF(size().width() * .5, size().height() *.5) + scaled;
}

void BlueprintCanvas::cycleGridResolution() {
    static const std::array<float, 6> gridResolutions = {0.0f, 0.25f, 0.5f, 1.0f, 2.0f, 4.0f};

    // Find the current index in the list
    auto it = std::find(gridResolutions.begin(), gridResolutions.end(), m_gridResolution);
    size_t index = (it != gridResolutions.end()) ? std::distance(gridResolutions.begin(), it) : 0;

    // Cycle to the next index
    m_gridResolution = gridResolutions[(index + 1) % gridResolutions.size()];
    update(); // trigger repaint
}

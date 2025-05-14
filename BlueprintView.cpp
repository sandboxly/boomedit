#include "BlueprintView.h"
#include <QPainter>
#include <QColor>
#include <QKeyEvent>
#include <array>
#include <QPainterPath>

BlueprintView::BlueprintView(AppState &appState, QWidget *parent) : QWidget(parent),
    m_appState(appState)
{
    setMinimumSize(400, 400); // Optional: for testing layout
    setAutoFillBackground(false); // We paint manually
    setFocusPolicy(Qt::StrongFocus);
    setCursor(Qt::CrossCursor);
}

QVector2D BlueprintView::viewportCenter() const {
    return m_viewportCenter;
}

void BlueprintView::setViewportCenter(const QVector2D &center) {
    m_viewportCenter = center;
    update();
}

float BlueprintView::zoomLevel() const {
    return m_zoomLevel;
}

void BlueprintView::setZoomLevel(const float zoom) {
    m_zoomLevel = zoom;
}

float BlueprintView::gridResolution() const {
    return m_gridResolution;
}

void BlueprintView::setGridResolution(const float resolution) {
    m_gridResolution = resolution;
}

QPointF BlueprintView::worldToScreen(const QVector2D& world, const QSize& widgetSize) const {
    // Calculate offset from viewport center
    QVector2D offset = world - m_viewportCenter;

    // Apply zoom (world units to pixels)
    QPointF scaled(offset.x() * m_zoomLevel, -offset.y() * m_zoomLevel); // Y-axis flipped

    // Translate to screen center
    return QPointF(widgetSize.width() / 2.0, widgetSize.height() / 2.0) + scaled;
}

void BlueprintView::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QColor blueprintBlue(4, 87, 160); // Deep blueprint background
    painter.fillRect(rect(), blueprintBlue);

    drawGrid(painter);
    drawWalls(painter);
    drawCorners(painter);
}

void BlueprintView::drawGrid(QPainter &painter) {
    if (m_gridResolution <= 0.0f) return;

    QPen gridPen(QColor(200, 200, 200, 60));
    gridPen.setWidth(0);
    painter.setPen(gridPen);

    QSize sizePx = size();
    float halfWidth = sizePx.width() / 2.0f;
    float halfHeight = sizePx.height() / 2.0f;

    float viewHalfWidthWorld = halfWidth / m_zoomLevel;
    float viewHalfHeightWorld = halfHeight / m_zoomLevel;

    float left = m_viewportCenter.x() - viewHalfWidthWorld;
    float right = m_viewportCenter.x() + viewHalfWidthWorld;
    float bottom = m_viewportCenter.y() - viewHalfHeightWorld;
    float top = m_viewportCenter.y() + viewHalfHeightWorld;

    float spacing = 1.0f / m_gridResolution;

    int xStart = std::floor(left / spacing);
    int xEnd = std::ceil(right / spacing);
    int yStart = std::floor(bottom / spacing);
    int yEnd = std::ceil(top / spacing);

    for (int i = xStart; i <= xEnd; ++i) {
        float x = i * spacing;
        QPointF p1 = worldToScreen(QVector2D(x, bottom), size());
        QPointF p2 = worldToScreen(QVector2D(x, top), size());
        painter.drawLine(p1, p2);
    }

    for (int j = yStart; j <= yEnd; ++j) {
        float y = j * spacing;
        QPointF p1 = worldToScreen(QVector2D(left, y), size());
        QPointF p2 = worldToScreen(QVector2D(right, y), size());
        painter.drawLine(p1, p2);
    }
}

void BlueprintView::drawWalls(QPainter &painter) {
    auto level = m_appState.currentLevel();
    if (!level) return;

    for (const auto &sector : level->sectors) {
        for (const auto &wall : sector->walls) {
            QPointF p1 = worldToScreen({wall->startVertex->x, wall->startVertex->y}, size());
            QPointF p2 = worldToScreen({wall->endVertex->x, wall->endVertex->y}, size());

            if (wall->isPortal) {
                painter.setPen(QPen(QColor(255, 100, 100), 2));  // light red
            } else {
                painter.setPen(QPen(Qt::white, 2));  // solid white
            }

            painter.drawLine(p1, p2);
        }
    }

    // Fill sector with 25% opacity white
    QPainterPath sectorPath;
    for (const auto& sector : level->sectors) {
        if (sector->walls.empty()) continue;

        sectorPath = QPainterPath();
        const auto& firstWall = sector->walls.front();
        QPointF firstPoint = worldToScreen({firstWall->startVertex->x, firstWall->startVertex->y}, size());
        sectorPath.moveTo(firstPoint);

        for (const auto& wall : sector->walls) {
            QPointF point = worldToScreen({wall->endVertex->x, wall->endVertex->y}, size());
            sectorPath.lineTo(point);
        }
        sectorPath.closeSubpath();

        QBrush fillBrush(QColor(255, 255, 255, 64)); // 25% opacity white
        painter.fillPath(sectorPath, fillBrush);
    }
}

void BlueprintView::drawCorners(QPainter &painter) {
    auto level = m_appState.currentLevel();
    if (!level) return;

    constexpr float sizePx = 6.0f; // half-size of square is 3px

    QPen pen(Qt::green);
    pen.setWidth(1);
    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush);

    for (const auto& sector : level->sectors) {
        for (const auto& wall : sector->walls) {
            for (const auto& vertex : {wall->startVertex, wall->endVertex}) {
                QPointF screenPt = worldToScreen({vertex->x, vertex->y}, size());
                QRectF rect(screenPt.x() - sizePx / 2, screenPt.y() - sizePx / 2, sizePx, sizePx);
                painter.drawRect(rect);
            }
        }
    }
}

void BlueprintView::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space && !m_spaceHeld) {
        m_spaceHeld = true;
        setCursor(Qt::OpenHandCursor);
    } else if (event->key() == Qt::Key_G) {
        static const std::array<float, 6> gridResolutions = {0.0f, 0.25f, 0.5f, 1.0f, 2.0f, 4.0f};

        // Find the current index in the list
        auto it = std::find(gridResolutions.begin(), gridResolutions.end(), m_gridResolution);
        size_t index = (it != gridResolutions.end()) ? std::distance(gridResolutions.begin(), it) : 0;

        // Cycle to the next index
        m_gridResolution = gridResolutions[(index + 1) % gridResolutions.size()];

        update(); // trigger repaint
    } else {
        QWidget::keyPressEvent(event); // default behavior
    }
}

void BlueprintView::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space) {
        m_spaceHeld = false;
        if (!m_isPanning) {
            setCursor(Qt::CrossCursor);
        }
    } else {
        QWidget::keyReleaseEvent(event);
    }
}

void BlueprintView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && m_spaceHeld) {
        m_isPanning = true;
        m_lastMousePos = event->pos();
        setCursor(Qt::ClosedHandCursor);
    }
    QWidget::mousePressEvent(event);
}

void BlueprintView::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isPanning) {
        QPoint delta = event->pos() - m_lastMousePos;
        m_lastMousePos = event->pos();

        // Adjust viewport center opposite to mouse drag, scaled by zoom
        QVector2D offset(-delta.x() / m_zoomLevel, delta.y() / m_zoomLevel);
        m_viewportCenter += offset;
        update();
    }
    QWidget::mouseMoveEvent(event);
}

void BlueprintView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && m_isPanning) {
        m_isPanning = false;
        if (m_spaceHeld)
            setCursor(Qt::OpenHandCursor);
        else
            unsetCursor();
    }
    QWidget::mouseReleaseEvent(event);
}

void BlueprintView::wheelEvent(QWheelEvent *event)
{
    constexpr float minZoom = 1.0f;
    constexpr float maxZoom = 100.0f;
    constexpr float zoomFactor = 1.1f; // Each step is ~10% zoom in/out

    if (event->angleDelta().y() > 0) {
        m_zoomLevel = std::min(maxZoom, m_zoomLevel * zoomFactor);
    } else if (event->angleDelta().y() < 0) {
        m_zoomLevel = std::max(minZoom, m_zoomLevel / zoomFactor);
    }

    update();
    event->accept();
}

#include <QPainterPath>
#include "../../../include/views/blueprint/BlueprintCanvas.h"
#include "../../../include/views/blueprint/BlueprintCanvasRenderer.h"

BlueprintCanvasRenderer::BlueprintCanvasRenderer(BlueprintCanvas *canvas) : m_canvas(canvas) {}

void BlueprintCanvasRenderer::draw(QPainter &painter) {
    painter.setRenderHint(QPainter::Antialiasing);

    QColor blueprintBlue(4, 87, 160); // Deep blueprint background
    painter.fillRect(*new QRect(), blueprintBlue);

    drawGrid(painter);
    drawWalls(painter);
    drawCorners(painter);
}

void BlueprintCanvasRenderer::drawGrid(QPainter &painter) {
    if (m_canvas->gridResolution() <= 0.0f) return;

    QPen gridPen(QColor(200, 200, 200, 60));
    gridPen.setWidth(0);
    painter.setPen(gridPen);

    QSize sizePx = m_canvas->size();
    float halfWidth = sizePx.width() / 2.0f;
    float halfHeight = sizePx.height() / 2.0f;

    float viewHalfWidthWorld = halfWidth / m_canvas->zoomLevel();
    float viewHalfHeightWorld = halfHeight / m_canvas->zoomLevel();

    float left = m_canvas->viewportCenter().x() - viewHalfWidthWorld;
    float right = m_canvas->viewportCenter().x() + viewHalfWidthWorld;
    float bottom = m_canvas->viewportCenter().y() - viewHalfHeightWorld;
    float top = m_canvas->viewportCenter().y() + viewHalfHeightWorld;

    float spacing = 1.0f / m_canvas->gridResolution();

    int xStart = std::floor(left / spacing);
    int xEnd = std::ceil(right / spacing);
    int yStart = std::floor(bottom / spacing);
    int yEnd = std::ceil(top / spacing);

    for (int i = xStart; i <= xEnd; ++i) {
        float x = i * spacing;
        QPointF p1 = worldToScreen(QVector2D(x, bottom), m_canvas->size());
        QPointF p2 = worldToScreen(QVector2D(x, top), m_canvas->size());
        painter.drawLine(p1, p2);
    }

    for (int j = yStart; j <= yEnd; ++j) {
        float y = j * spacing;
        QPointF p1 = worldToScreen(QVector2D(left, y), m_canvas->size());
        QPointF p2 = worldToScreen(QVector2D(right, y), m_canvas->size());
        painter.drawLine(p1, p2);
    }
}

void BlueprintCanvasRenderer::drawWalls(QPainter &painter) {
    auto level = m_canvas->model().level();
    if (!level) return;

    for (const auto &sector : level->sectors) {
        for (const auto &wall : sector->around()) {
            QPointF p1 = worldToScreen({wall->startVertex->x, wall->startVertex->y}, m_canvas->size());
            QPointF p2 = worldToScreen({wall->endVertex->x, wall->endVertex->y}, m_canvas->size());

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
        if (sector->walls_.empty()) continue;

        sectorPath = QPainterPath();
        const auto& firstWall = sector->anyWall;
        QPointF firstPoint = worldToScreen({firstWall->startVertex->x, firstWall->startVertex->y}, m_canvas->size());
        sectorPath.moveTo(firstPoint);

        for (const auto& wall : sector->around()) {
            QPointF point = worldToScreen({wall->endVertex->x, wall->endVertex->y}, m_canvas->size());
            sectorPath.lineTo(point);
        }
        sectorPath.closeSubpath();

        QBrush fillBrush(QColor(255, 255, 255, 64)); // 25% opacity white
        painter.fillPath(sectorPath, fillBrush);
    }
}

void BlueprintCanvasRenderer::drawCorners(QPainter &painter) {
    auto level = m_canvas->model().level();
    if (!level) return;

    constexpr float sizePx = 6.0f; // half-size of square is 3px

    QPen pen(Qt::green);
    pen.setWidth(1);
    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush);

    for (const auto& sector : level->sectors) {
        for (const auto& wall : sector->around()) {
            for (const auto& vertex : {wall->startVertex, wall->endVertex}) {
                QPointF screenPt = worldToScreen({vertex->x, vertex->y}, m_canvas->size());
                QRectF rect(screenPt.x() - sizePx / 2, screenPt.y() - sizePx / 2, sizePx, sizePx);
                painter.drawRect(rect);
            }
        }
    }
}

QPointF BlueprintCanvasRenderer::worldToScreen(const QVector2D& world, const QSize& widgetSize) const {
    // Calculate offset from viewport center
    QVector2D offset = world - m_canvas->viewportCenter();

    // Apply zoom (world units to pixels)
    QPointF scaled(offset.x() * m_canvas->zoomLevel(), -offset.y() * m_canvas->zoomLevel()); // Y-axis flipped

    // Translate to screen center
    return QPointF(widgetSize.width() / 2.0, widgetSize.height() / 2.0) + scaled;
}

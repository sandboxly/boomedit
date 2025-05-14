#ifndef BLUEPRINTCANVASRENDERER_H
#define BLUEPRINTCANVASRENDERER_H

#include <QPainter>

class BlueprintCanvas;

class BlueprintCanvasRenderer
{
public:
    explicit BlueprintCanvasRenderer(BlueprintCanvas* canvas);

    void draw(QPainter &painter);

private:
    BlueprintCanvas *m_canvas;
    void drawGrid(QPainter &painter);
    void drawWalls(QPainter &painter);
    void drawCorners(QPainter &painter);
    QPointF worldToScreen(const QVector2D& world, const QSize& widgetSize) const;
};

#endif // BLUEPRINTCANVASRENDERER_H

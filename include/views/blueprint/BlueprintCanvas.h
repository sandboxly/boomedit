#ifndef BLUEPRINTCANVAS_H
#define BLUEPRINTCANVAS_H

#include <memory>
#include <QWidget>
#include <QVector2D>
#include <QRectF>
#include "BlueprintModel.h"
#include "BlueprintCanvasController.h"
#include "BlueprintCanvasRenderer.h"
#include "IEditTool.h"

class PanTool;
class RectangleTool;
class SelectTool;

class BlueprintCanvas : public QWidget {
    Q_OBJECT
public:
    explicit BlueprintCanvas(BlueprintModel& model, QWidget* parent = nullptr);

    BlueprintModel model() const;

    QVector2D viewportCenter() const;
    void setViewportCenter(const QVector2D &center);

    float zoomLevel() const;
    void setZoomLevel(const float zoom);

    float gridResolution() const;
    void setGridResolution(const float resolution);

    IEditTool* activeTool() const;
    void setActiveTool(EditToolType toolType);

    QPointF screenToWorld(const QPointF& screen);
    QPointF worldToScreen(const QPointF& world);

    void cycleGridResolution();

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    // private fields
    BlueprintModel& m_model;
    std::unique_ptr<BlueprintCanvasController> m_controller;
    std::unique_ptr<BlueprintCanvasRenderer> m_renderer;
    QVector2D m_viewportCenter {0.0f, 0.0f};
    float m_zoomLevel {25.0};
    float m_gridResolution {1.0f};

    IEditTool* m_activeTool;
    SelectTool* m_selectTool;
    PanTool* m_panTool;
    RectangleTool* m_rectangleTool;
private Q_SLOTS:
    void onRectangleCreated(const QRectF& worldRect);
};



#endif // BLUEPRINTCANVAS_H

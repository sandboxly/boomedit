#ifndef BLUEPRINTTOOLBAR_H
#define BLUEPRINTTOOLBAR_H

#include <QWidget>
#include <QToolButton>

class BlueprintToolBar : public QWidget {
    Q_OBJECT
public:
    explicit BlueprintToolBar(QWidget *parent);
private:
    QToolButton m_toolSelect;
    QToolButton m_toolPan;
    QToolButton m_toolButtonZoom;
    QToolButton m_toolButtonDrawRectangle;
    QToolButton m_toolButtonDrawPolygon;
    QToolButton m_toolButtonDrawPolygonPath;
};

#endif // BLUEPRINTTOOLBAR_H

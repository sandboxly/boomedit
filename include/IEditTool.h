#ifndef IEDITTOOL_H
#define IEDITTOOL_H

#pragma once

#include <QMouseEvent>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QPainter>
#include <QObject>

class IEditTool : public QObject {
    Q_OBJECT
public:
    explicit IEditTool(QObject* parent = nullptr)
        : QObject(parent)
    {}
    virtual ~IEditTool() = default;

    virtual void onActivate() = 0;
    virtual void onDeactivate() = 0;
    virtual void mousePressEvent(QMouseEvent* event) = 0;
    virtual void mouseMoveEvent(QMouseEvent* event) = 0;
    virtual void mouseReleaseEvent(QMouseEvent* event) = 0;
    virtual void keyPressEvent(QKeyEvent* event) = 0;
    virtual void keyReleaseEvent(QKeyEvent* event) = 0;
    virtual void wheelEvent(QWheelEvent* event) = 0;

    virtual void paintOverlay(QPainter& painter) = 0;
};

#endif // IEDITTOOL_H

#ifndef BLUEPRINTTOOLBAR_H
#define BLUEPRINTTOOLBAR_H

#include <QWidget>
#include <QToolButton>

class BlueprintToolBar : public QWidget {
    Q_OBJECT
public:
    explicit BlueprintToolBar(QWidget* parent);
    void setActions(const QList<QAction*>& actions);
};

#endif // BLUEPRINTTOOLBAR_H

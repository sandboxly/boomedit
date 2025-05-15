#ifndef BLUEPRINTTOOLBAR_H
#define BLUEPRINTTOOLBAR_H

#include <QWidget>
#include <QToolButton>
#include <QVBoxLayout>

class BlueprintToolBar : public QWidget {
    Q_OBJECT
public:
    explicit BlueprintToolBar(QWidget* parent);
    void setActions(const QList<QAction*>& actions);
private:
    QVBoxLayout* m_layout;
};

#endif // BLUEPRINTTOOLBAR_H

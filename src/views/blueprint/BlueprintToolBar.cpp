#include <QToolButton>
#include <QVBoxLayout>
#include "views/blueprint/BlueprintToolBar.h"

BlueprintToolBar::BlueprintToolBar(QWidget* parent)
    : QWidget(parent)
{
    auto *lay = new QVBoxLayout(this);
}

void BlueprintToolBar::setActions(const QList<QAction*>& actions) {
    for (auto *a : actions) {
        auto *btn = new QToolButton(this);
        btn->setDefaultAction(a);
        btn->setCheckable(true);
        layout()->addWidget(btn);
    }
}

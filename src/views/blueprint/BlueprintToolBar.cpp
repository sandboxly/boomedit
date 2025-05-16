#include <QToolButton>
#include <QVBoxLayout>
#include <QStyle>
#include "views/blueprint/BlueprintToolBar.h"

BlueprintToolBar::BlueprintToolBar(QWidget* parent)
    : QWidget(parent)
{
    m_layout = new QVBoxLayout(this);
    m_layout->setAlignment(Qt::AlignTop);
    m_layout->setContentsMargins(2, 2, 2, 2);
    m_layout->setSpacing(0);
}

void BlueprintToolBar::setActions(const QList<QAction*>& actions) {
    for (auto *a : actions) {
        auto *btn = new QToolButton(this);
        btn->setDefaultAction(a);
        btn->setCheckable(true);
        btn->setToolButtonStyle(Qt::ToolButtonIconOnly);
        btn->setIconSize(QSize(20,20));
        btn->setContentsMargins(0, 0, 0, 0);
        m_layout->addWidget(btn);
    }
}

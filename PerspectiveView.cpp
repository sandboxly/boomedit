#include "PerspectiveView.h"
#include <QLabel>
#include <QVBoxLayout>

PerspectiveView::PerspectiveView(QWidget *parent) : QWidget(parent) {
    auto *label = new QLabel("Perspective", this);
    label->setAlignment(Qt::AlignCenter);
    auto *layout = new QVBoxLayout(this);
    layout->addWidget(label);
    setLayout(layout);
}

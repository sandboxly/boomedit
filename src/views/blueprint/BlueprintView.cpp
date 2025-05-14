#include <QHBoxLayout>
#include <QSplitter>
#include "views/blueprint/BlueprintView.h"

BlueprintView::BlueprintView(BlueprintModel* model, QWidget* parent)
    : QWidget(parent),
    m_model(model),
    m_toolBar(std::make_unique<BlueprintToolBar>(this)),
    m_canvas(std::make_unique<BlueprintCanvas>(*model, this)),
    m_inspector(std::make_unique<BlueprintInspector>(this))
{
    // Splitter for canvas and inspector
    auto* splitter = new QSplitter(Qt::Horizontal, this);
    splitter->addWidget(m_canvas.get());
    splitter->addWidget(m_inspector.get());
    splitter->setStretchFactor(0, 1); // Canvas grows more
    splitter->setStretchFactor(1, 0); // Inspector grows less
    splitter->setHandleWidth(6);

    // Layout with toolbar and splitter
    auto* layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_toolBar.get());
    layout->addWidget(splitter);

    setLayout(layout);
}

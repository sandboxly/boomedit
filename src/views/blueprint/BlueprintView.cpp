#include <QActionGroup>
#include <QHBoxLayout>
#include <QSplitter>
#include "views/blueprint/BlueprintView.h"
#include "IEditTool.h"
#include "edittools/RectangleTool.h"

BlueprintView::BlueprintView(AppState* appState, BlueprintModel* model, QWidget* parent)
    : QWidget(parent),
    m_appState(appState),
    m_model(model),
    m_toolBar(std::make_unique<BlueprintToolBar>(this)),
    m_canvas(std::make_unique<BlueprintCanvas>(*appState, *model, this)),
    m_inspector(std::make_unique<BlueprintInspector>(this))
{
    // Set up tool actions
    m_actSelect = new QAction(QIcon(":/icons/assets/icons/tool_select.png"), tr("Select"), this);
    m_actSelect->setShortcut(QKeySequence(Qt::Key_S));

    m_actPan = new QAction(QIcon(":/icons/assets/icons/tool_pan.png"), tr("Pan"),  this);
    m_actPan->setShortcut(QKeySequence(Qt::Key_P));

    m_actRectangle = new QAction(QIcon(":/icons/assets/icons/tool_rect.png"), tr("Rectangle"), this);
    m_actRectangle->setShortcut(QKeySequence(Qt::Key_R));

    m_toolActionGroup = new QActionGroup(this);
    m_toolActionGroup->setExclusive(true);
    m_toolActionGroup->addAction(m_actSelect);
    m_toolActionGroup->addAction(m_actPan);
    m_toolActionGroup->addAction(m_actRectangle);

    m_toolBar->setActions({m_actSelect, m_actPan, m_actRectangle});

    connect(m_toolActionGroup,  &QActionGroup::triggered,
            this,               &BlueprintView::onToolTriggered);

    addAction(m_actSelect);
    addAction(m_actPan);
    addAction(m_actRectangle);

    // Set up other actions
    m_actToggleSnapToGrid = new QAction(tr("Snap to Grid"), this);
    m_actToggleSnapToGrid->setCheckable(true);
    m_actToggleSnapToGrid->setChecked(true);
    m_actToggleSnapToGrid->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_G));

    connect(m_actToggleSnapToGrid,  &QAction::toggled,
            this,                   &BlueprintView::onToggleSnapToGrid);


    addAction(m_actToggleSnapToGrid);

    m_actCycleGridResolution = new QAction(tr("Cycle Grid Resolution"), this);
    m_actCycleGridResolution->setShortcut(QKeySequence(Qt::ALT | Qt::Key_G));

    connect(m_actCycleGridResolution,   &QAction::triggered,
            this,                       &BlueprintView::onCycleGridResolution);

    addAction(m_actCycleGridResolution);


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
    layout->setSpacing(0);
    layout->addWidget(m_toolBar.get());
    layout->addWidget(splitter);
    setLayout(layout);

    m_actSelect->setCheckable(true);
    m_actPan->setCheckable(true);
    m_actRectangle->setCheckable(true);

    m_actSelect->setChecked(true);
    onToolTriggered(m_actSelect);
}

void BlueprintView::onToolTriggered(QAction* act) {
    if (act == m_actSelect) {
        m_canvas->setActiveTool(EditToolType::Select);
    }
    else if (act == m_actPan) {
        m_canvas->setActiveTool(EditToolType::Pan);
    }
    else if (act == m_actRectangle) {
        m_canvas->setActiveTool(EditToolType::Rectangle);
    }
}

void BlueprintView::onToggleSnapToGrid(bool enabled) {
    if ( auto rectTool = dynamic_cast<RectangleTool*>(m_canvas->activeTool()) ) {
        rectTool->setSnapToGrid(enabled);
    }
}

void BlueprintView::onCycleGridResolution() {
    m_canvas->cycleGridResolution();
}

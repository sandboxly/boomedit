#include "BoomEditWindow.h"
#include "ui_boomeditwindow.h"
#include "AppState.h"
#include "views/blueprint/BlueprintView.h"
#include "ui_boomeditwindow.h"

#include <QAction>
#include <QActionGroup>
#include <QToolBar>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QLabel>

BoomEditWindow::BoomEditWindow(AppState *appState, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BoomEditWindow)
{
    ui->setupUi(this);

    // Use BlueprintView instead of dummy
    BlueprintModel *blueprintCanvasModel = new BlueprintModel(appState->currentLevel());
    blueprintView = new BlueprintView(appState, blueprintCanvasModel, this);

    // Keep dummy for perspective for now
    perspectiveView = new QWidget(this);
    auto *perspectiveLabel = new QLabel("Perspective", perspectiveView);
    perspectiveLabel->setAlignment(Qt::AlignCenter);
    auto *perspectiveLayout = new QVBoxLayout(perspectiveView);
    perspectiveLayout->addWidget(perspectiveLabel);
    perspectiveView->setLayout(perspectiveLayout);

    // Common Actions
    m_undoAction = new QAction(tr("&Undo"), this);
    m_undoAction->setShortcut(QKeySequence::Undo);
    m_undoAction->setEnabled(true);
    // connect(m_undoAction,   &QAction::triggered,
    //        this,           &BoomEditWindow::undo);

    // View Mode Actions
    blueprintAction = new QAction("Blueprint", this);
    blueprintAction->setCheckable(true);

    perspectiveAction = new QAction("Perspective", this);
    perspectiveAction->setCheckable(true);

    auto *viewModeGroup = new QActionGroup(this);
    viewModeGroup->addAction(blueprintAction);
    viewModeGroup->addAction(perspectiveAction);
    viewModeGroup->setExclusive(true);

    ui->mainToolBar->addAction(blueprintAction);
    ui->mainToolBar->addAction(perspectiveAction);

    connect(blueprintAction, &QAction::triggered, this, &BoomEditWindow::switchToBlueprint);
    connect(perspectiveAction, &QAction::triggered, this, &BoomEditWindow::switchToPerspective);

    // Set up stacked widget
    stackedWidget = new QStackedWidget(this);
    stackedWidget->addWidget(blueprintView);    // index 0
    stackedWidget->addWidget(perspectiveView);  // index 1
    setCentralWidget(stackedWidget);

    // Start with blueprint view
    blueprintAction->setChecked(true);
    stackedWidget->setCurrentIndex(0);
}

BoomEditWindow::~BoomEditWindow()
{
    delete ui;
}

void BoomEditWindow::switchToBlueprint()
{
    stackedWidget->setCurrentIndex(0);
}

void BoomEditWindow::switchToPerspective()
{
    stackedWidget->setCurrentIndex(1);
}

void BoomEditWindow::onLevelChanged(std::shared_ptr<Level> level) {}
void BoomEditWindow::onCameraPositionChanged(const QVector2D position) {}
void BoomEditWindow::onCameraLookAtChanged(const QVector2D lookAt) {}

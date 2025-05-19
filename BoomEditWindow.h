#ifndef BOOMEDITWINDOW_H
#define BOOMEDITWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QAction>
#include <QStackedWidget>
#include "include/AppState.h"
#include "include/LevelDocument.h"

QT_BEGIN_NAMESPACE
namespace Ui { class BoomEditWindow; }
QT_END_NAMESPACE

class BoomEditWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BoomEditWindow(AppState *appState, QWidget *parent = nullptr);
    ~BoomEditWindow();

private slots:
    void switchToBlueprint();
    void switchToPerspective();
    void onLevelChanged(std::shared_ptr<Level> level);
    void onCameraPositionChanged(const QVector2D position);
    void onCameraLookAtChanged(const QVector2D lookAt);

private:
    AppState *m_appState;
    Ui::BoomEditWindow *ui;
    QWidget *blueprintView;
    QWidget *perspectiveView;
    QStackedWidget *stackedWidget;
    QAction *blueprintAction;
    QAction *perspectiveAction;
    std::shared_ptr<LevelDocument> m_levelDocument;
};

#endif // BOOMEDITWINDOW_H

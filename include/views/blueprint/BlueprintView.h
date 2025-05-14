#ifndef BLUEPRINTVIEW_H
#define BLUEPRINTVIEW_H

#include <memory>
#include <QWidget>
#include "BlueprintToolBar.h"
#include "BlueprintCanvas.h"
#include "BlueprintInspector.h"

class BlueprintModel;

class BlueprintView : public QWidget {
    Q_OBJECT
public:
    explicit BlueprintView(BlueprintModel* model, QWidget *parent = nullptr);
private:
    BlueprintModel* m_model;
    std::unique_ptr<BlueprintToolBar> m_toolBar;
    std::unique_ptr<BlueprintCanvas> m_canvas;
    std::unique_ptr<BlueprintInspector> m_inspector;
};

#endif // BLUEPRINTVIEW_H

#include <QButtonGroup>
#include <QStyle>
#include <QVBoxLayout>
#include "../../../include/views/blueprint/BlueprintToolBar.h"

BlueprintToolBar::BlueprintToolBar(QWidget *parent) : QWidget(parent) {
    // Create button group for mutual exclusivity
    auto *toolGroup = new QButtonGroup(this);
    toolGroup->setExclusive(true);

    // Configure tool buttons
    m_toolSelect.setText("Select");
    m_toolPan.setText("Pan");
    m_toolButtonZoom.setText("Zoom");
    m_toolButtonDrawRectangle.setText("Draw Rect");
    m_toolButtonDrawPolygon.setText("Draw Poly");
    m_toolButtonDrawPolygonPath.setText("Draw Path");

    // Set checkable and add to button group
    for (QToolButton* button : {
             &m_toolSelect,
             &m_toolPan,
             &m_toolButtonZoom,
             &m_toolButtonDrawRectangle,
             &m_toolButtonDrawPolygon,
             &m_toolButtonDrawPolygonPath
         }) {
        button->setCheckable(true);
        toolGroup->addButton(button);
    }

    // Layout
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(4, 4, 4, 4);
    layout->setSpacing(4);

    layout->addWidget(&m_toolSelect);
    layout->addWidget(&m_toolPan);
    layout->addWidget(&m_toolButtonZoom);
    layout->addWidget(&m_toolButtonDrawRectangle);
    layout->addWidget(&m_toolButtonDrawPolygon);
    layout->addWidget(&m_toolButtonDrawPolygonPath);
    layout->addStretch();

    setLayout(layout);

    // Default selected tool
    m_toolSelect.setChecked(true);

}

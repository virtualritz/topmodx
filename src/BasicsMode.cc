
#include <QtGui>

#include "BasicsMode.h"

BasicsMode::BasicsMode(QWidget *parent) :
  QWidget(parent) {

  setParent(0);
  parent_ = parent;
  insert_edge_tool_ = new InsertEdgeTool(parent);
  cubical_extrude_tool = new CubicalExtrudeTool(parent);

}

QMenu* BasicsMode::getMenu() {
  mBasicsMenu = new QMenu(tr("Basics"));
  mBasicsMenu->addAction(insert_edge_tool_->action_);
  mBasicsMenu->addAction(cubical_extrude_tool->action_);
  return mBasicsMenu;
}

void BasicsMode::addActions(QActionGroup *actionGroup, QToolBar *toolBar,
                            QStackedWidget *stackedWidget) {

  actionGroup->addAction(insert_edge_tool_->action_);
  actionGroup->addAction(cubical_extrude_tool->action_);

  toolBar->addAction(insert_edge_tool_->action_);
  toolBar->addAction(cubical_extrude_tool->action_);

  stackedWidget->addWidget(insert_edge_tool_->widget_);
  stackedWidget->addWidget(cubical_extrude_tool->widget_);

}

void BasicsMode::retranslateUi() {
  mBasicsMenu->setTitle(tr("Basics"));
}

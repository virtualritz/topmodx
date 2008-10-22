/*
 * cubical_extrude_tool.cc
 *
 *  Created on: Sep 12, 2008
 *      Author: david.morris
 */

#include "cubical_extrude_tool.h"
#include "../MainWindow.h"
class MainWindow;

// Implementation of the class CubicalExtrudeTool.
// Constructor.
CubicalExtrudeTool::CubicalExtrudeTool(QWidget *parent) {
  parent_ = parent;
  layout_ = new QGridLayout;
  layout_->setVerticalSpacing(1);
  layout_->setHorizontalSpacing(1);

  QLabel *noOptionsInsertEdgeLabel =
      new QLabel(tr("No Options for this tool."));
  layout_->addWidget(noOptionsInsertEdgeLabel, 0, 0);

  layout_->setRowStretch(1, 1);
  layout_->setColumnStretch(1, 1);
  widget_ = new QWidget;
  widget_->setWindowTitle(tr("Insert Edge"));
  widget_->setLayout(layout_);

  action_ = new QAction(tr("Insert Edge"), parent_);
  action_->setIcon(QIcon(":/images/cubical_extrude.png"));
  action_->setCheckable(true);
  action_->setStatusTip(tr("Insert Edge"));
  action_->setToolTip(tr("Insert Edge"));
  connect(action_, SIGNAL(triggered()), this, SLOT(Activate()));
}

void CubicalExtrudeTool::Activate() {
  ((MainWindow*) parent_)->setToolOptions(widget_);
  ((MainWindow*) parent_)->setMode(MainWindow::InsertEdge);
}

void CubicalExtrudeTool::RetranslateUi(){

}

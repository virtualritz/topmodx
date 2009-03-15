/*
 * convex_hull_tool.cc
 *
 *  Created on: Sep 15, 2008
 *      Author: david.morris
 */

#include "convex_hull_tool.h"
#include "../MainWindow.h"
class MainWindow;

ConvexHullTool::ConvexHullTool(QWidget *parent) {
  parent_ = parent;
  layout_ = new QGridLayout;
  layout_->setVerticalSpacing(1);
  layout_->setHorizontalSpacing(1);

  convex_hull_button_ = new QPushButton(tr("Create Convex Hull"), this);
  connect(convex_hull_button_, SIGNAL(clicked()), ((MainWindow*) mParent), SLOT(createConvexHull()) );
  layout_->addWidget(convex_hull_button_, 0, 0, 1, 2);

  dual_convex_hull_button_ = new QPushButton(tr("Create Dual Convex Hull"), this);
  connect(dual_convex_hull_button_, SIGNAL(clicked()), ((MainWindow*) mParent), SLOT(createDualConvexHull()));
  layout_->addWidget(dual_convex_hull_button_, 1, 0, 1, 2);

  layout_->setRowStretch(1, 1);
  layout_->setColumnStretch(1, 1);
  widget_ = new QWidget;
  widget_->setWindowTitle(tr("Convex Hull"));
  widget_->setLayout(layout_);

  action_ = new QAction(tr("Convex Hull"), parent_);
  action_->setIcon(QIcon(":/images/conical-convexhull.png"));
  action_->setCheckable(true);
  action_->setStatusTip(tr("Convex Hull"));
  action_->setToolTip(tr("Convex Hull"));
  connect(action_, SIGNAL(triggered()), this, SLOT(Activate()));
}

void ConvexHullTool::Activate() {
  ((MainWindow*) parent_)->setToolOptions(widget_);
  ((MainWindow*) parent_)->setMode(MainWindow::ConvexHullMode);
}

void ConvexHullTool::RetranslateUi() {

}

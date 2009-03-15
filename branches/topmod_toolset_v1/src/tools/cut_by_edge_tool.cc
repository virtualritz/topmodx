/*
 * cut_by_edge_tool.cc
 *
 *  Created on: Sep 15, 2008
 *      Author: david.morris
 */

#include "cut_by_edge_tool.h"
#include "../MainWindow.h"
class MainWindow;

CutByEdgeTool::CutByEdgeTool(QWidget *parent) {
  parent_ = parent;
  layout_ = new QGridLayout;
  layout_->setVerticalSpacing(1);
  layout_->setHorizontalSpacing(1);

  //offset
  QLabel *offest_label = new QLabel(this);
  offset_spin_ = createDoubleSpinBox(layout_, offest_label, tr("Offset:"), 0.0,
      2.0, 0.01, 0.25, 3, 0, 0);
  connect(offset_spin_, SIGNAL(valueChanged(double)), this, SLOT(changeCutOffsetE(double)));

  global_check_ = new QCheckBox(tr("Global Cut"), this);
  global_check_->setChecked(Qt::Unchecked);
  connect(global_check_, SIGNAL(stateChanged(int)), this, SLOT(toggleGlobalCut(int)));
  layout_->addWidget(global_check_, 1, 0, 1, 2);

  perform_cutting_button_ = new QPushButton(tr("Perform Cutting"), this);
  connect(perform_cutting_button_, SIGNAL(clicked()), ((MainWindow*) mParent), SLOT(performCutting()) );
  layout_->addWidget(perform_cutting_button_, 2, 0, 1, 2);

  layout_->setRowStretch(1, 1);
  layout_->setColumnStretch(1, 1);
  widget_ = new QWidget;
  widget_->setWindowTitle(tr("Cut By Edge"));
  widget_->setLayout(layout_);

  action_ = new QAction(tr("Cut By Edge"), parent_);
  action_->setIcon(QIcon(":/images/sculpting-cutedges.png"));
  action_->setCheckable(true);
  action_->setStatusTip(tr("Cut By Edge"));
  action_->setToolTip(tr("Cut By Edge"));
  connect(action_, SIGNAL(triggered()), this, SLOT(Activate()));
}

void CutByEdgeTool::toggleGlobalCut(int state) {
  global_check_->setChecked(state);
  ((MainWindow*) mParent)->toggleGlobalCut(state);
}

void CutByEdgeTool::changeCutOffsetE(double value) {
  offset_spin_->setValue(value);
  ((MainWindow*) mParent)->changeCutOffsetE(value);
}

void CutByEdgeTool::Activate() {
  ((MainWindow*) parent_)->setToolOptions(widget_);
  ((MainWindow*) parent_)->setMode(MainWindow::CutEdge);
}

void CutByEdgeTool::RetranslateUi() {

}


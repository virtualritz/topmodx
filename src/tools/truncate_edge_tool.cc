/*
 * truncate_edge_tool.cc
 *
 *  Created on: Sep 15, 2008
 *      Author: david.morris
 */

#include "truncate_edge_tool.h"
#include "../MainWindow.h"
class MainWindow;

TruncateEdgeTool::TruncateEdgeTool(QWidget *parent) {
  parent_ = parent;
  layout_ = new QGridLayout;
  layout_->setVerticalSpacing(1);
  layout_->setHorizontalSpacing(1);

  // mTruncateEdgeLayout = new QBoxLayout(QBoxLayout::LeftToRight);
  // mTruncateEdgeLayout->setMargin(0);
  //
  // QLabel *truncateEdgeOffsetLabel = new QLabel(tr("Offset:"));
  // truncateEdgeOffsetSpinBox = new QDoubleSpinBox;
  // truncateEdgeOffsetSpinBox->setRange(0, 1);
  // truncateEdgeOffsetSpinBox->setSingleStep(0.01);
  // truncateEdgeOffsetSpinBox->setValue(0.25);
  // truncateEdgeOffsetSpinBox->setMaximumSize(75,25);
  // connect(truncateEdgeOffsetSpinBox, SIGNAL(valueChanged(double)),
  //           this, SLOT(changeCutOffsetE(double)));
  //
  // mTruncateEdgeLayout->addWidget(truncateEdgeOffsetLabel);
  //   mTruncateEdgeLayout->addWidget(truncateEdgeOffsetSpinBox);
  //
  // truncateEdgeGlobalCheckBox = new QCheckBox(tr("global cut"),this);
  // truncateEdgeGlobalCheckBox->setChecked(Qt::Unchecked);
  // connect(truncateEdgeGlobalCheckBox, SIGNAL(stateChanged(int)),
  //           this, SLOT(toggleGlobalCut(int)));
  //
  // mTruncateEdgeLayout->addWidget(truncateEdgeGlobalCheckBox);
  //
  // truncateEdgeCutSelectedCheckBox = new QCheckBox(tr("cut selected vertices"),this);
  // truncateEdgeCutSelectedCheckBox->setChecked(Qt::Checked);
  // connect(truncateEdgeCutSelectedCheckBox, SIGNAL(stateChanged(int)),
  //           this, SLOT(toggleSelectedCut(int)));
  //
  // mTruncateEdgeLayout->addWidget(truncateEdgeCutSelectedCheckBox);
  //
  // QPushButton *performCuttingButton = new QPushButton(tr("Perform Cutting"), this);
  // connect(performCuttingButton, SIGNAL(clicked()),
  //           ((MainWindow*)mParent), SLOT(performCutting()));
  //
  // mTruncateEdgeLayout->addWidget(performCuttingButton);
  // mTruncateEdgeLayout->addStretch(1);
  // mTruncateEdgeWidget->setWindowTitle("Truncate Edge");
  // mTruncateEdgeWidget->setLayout(mTruncateEdgeLayout);

  layout_->setRowStretch(1, 1);
  layout_->setColumnStretch(1, 1);
  widget_ = new QWidget;
  widget_->setWindowTitle(tr("Truncate Edge"));
  widget_->setLayout(layout_);

  action_ = new QAction(tr("Truncate Edge"), parent_);
  action_->setIcon(QIcon(":/images/sculpting-cutedges.png"));
  action_->setCheckable(true);
  action_->setStatusTip(tr("Truncate Edge"));
  action_->setToolTip(tr("Truncate Edge"));
  connect(action_, SIGNAL(triggered()), this, SLOT(Activate()));
}

void TruncateEdgeTool::Activate() {
  ((MainWindow*) parent_)->setToolOptions(widget_);
  ((MainWindow*) parent_)->setMode(MainWindow::TruncateEdge);
}

void TruncateEdgeTool::RetranslateUi() {

}

/*
 * truncate_vertex_tool.cc
 *
 *  Created on: Sep 15, 2008
 *      Author: david.morris
 */

#include "truncate_vertex_tool.h"
#include "../MainWindow.h"
class MainWindow;

TruncateVertexTool::TruncateVertexTool(QWidget *parent) {
  parent_ = parent;
  layout_ = new QGridLayout;
  layout_->setVerticalSpacing(1);
  layout_->setHorizontalSpacing(1);

  // mTruncateVertexLayout = new QBoxLayout(QBoxLayout::LeftToRight);
  // mTruncateVertexLayout->setMargin(0);
  //
  // QLabel *truncateVertexOffsetLabel = new QLabel(tr("Offset:"));
  // truncateVertexOffsetSpinBox = new QDoubleSpinBox;
  // truncateVertexOffsetSpinBox->setRange(0, 1);
  // truncateVertexOffsetSpinBox->setSingleStep(0.01);
  // truncateVertexOffsetSpinBox->setValue(0.25);
  // truncateVertexOffsetSpinBox->setMaximumSize(75,25);
  // connect(truncateVertexOffsetSpinBox, SIGNAL(valueChanged(double)),
  //           this, SLOT(changeCutOffsetE(double)));
  //
  // mTruncateVertexLayout->addWidget(truncateVertexOffsetLabel);
  //   mTruncateVertexLayout->addWidget(truncateVertexOffsetSpinBox);
  //
  // truncateVertexGlobalCheckBox = new QCheckBox(tr("global cut"),this);
  // truncateVertexGlobalCheckBox->setChecked(Qt::Unchecked);
  // connect(truncateVertexGlobalCheckBox, SIGNAL(stateChanged(int)),
  //           this, SLOT(toggleGlobalCut(int)));
  //
  // mTruncateVertexLayout->addWidget(truncateVertexGlobalCheckBox);
  //
  // truncateVertexCutSelectedCheckBox = new QCheckBox(tr("cut selected vertices"),this);
  // truncateVertexCutSelectedCheckBox->setChecked(Qt::Checked);
  // connect(truncateVertexCutSelectedCheckBox, SIGNAL(stateChanged(int)),
  //           this, SLOT(toggleSelectedCut(int)));
  //
  // mTruncateVertexLayout->addWidget(truncateVertexCutSelectedCheckBox);
  //
  // QPushButton *performCuttingButton = new QPushButton(tr("Perform Cutting"), this);
  // connect(performCuttingButton, SIGNAL(clicked()),
  //           ((MainWindow*)mParent), SLOT(performCutting()));
  //
  // mTruncateVertexLayout->addWidget(performCuttingButton);
  // mTruncateVertexLayout->addStretch(1);
  // mTruncateVertexWidget->setWindowTitle("Truncate Vertex");
  // mTruncateVertexWidget->setLayout(mTruncateVertexLayout);

  layout_->setRowStretch(1, 1);
  layout_->setColumnStretch(1, 1);
  widget_ = new QWidget;
  widget_->setWindowTitle(tr("Truncate Vertex"));
  widget_->setLayout(layout_);

  action_ = new QAction(tr("Truncate Vertex"), parent_);
  action_->setIcon(QIcon(":/images/sculpting-cutvertices.png"));
  action_->setCheckable(true);
  action_->setStatusTip(tr("Truncate Vertex"));
  action_->setToolTip(tr("Truncate Vertex"));
  connect(action_, SIGNAL(triggered()), this, SLOT(Activate()));
}

void TruncateVertexTool::Activate() {
  ((MainWindow*) parent_)->setToolOptions(widget_);
  ((MainWindow*) parent_)->setMode(MainWindow::TruncateVertex);
}

void TruncateVertexTool::RetranslateUi() {

}

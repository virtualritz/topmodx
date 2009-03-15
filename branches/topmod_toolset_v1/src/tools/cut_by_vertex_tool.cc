/*
 * cut_by_vertex_tool.cc
 *
 *  Created on: Sep 15, 2008
 *      Author: david.morris
 */

#include "cut_by_edge_tool.h"
#include "../MainWindow.h"
class MainWindow;

CutByVertexTool::CutByVertexTool(QWidget *parent) {
  parent_ = parent;
  layout_ = new QGridLayout;
  layout_->setVerticalSpacing(1);
  layout_->setHorizontalSpacing(1);

  //offset
  QLabel *offest_label = new QLabel(this);
  offset_spin_ = createDoubleSpinBox(layout_, offest_label, tr("Offset:"), 0.0,
      2.0, 0.01, 0.25, 3, 0, 0);
  connect(offset_spin_, SIGNAL(valueChanged(double)), this, SLOT(changeCutOffsetV(double)));

  global_check_ = new QCheckBox(tr("Global Cut"), this);
  global_check_->setChecked(Qt::Unchecked);
  connect(global_check_, SIGNAL(stateChanged(int)), this, SLOT(toggleGlobalCut(int)));
  layout_->addWidget(global_check_, 1, 0, 1, 2);

  perform_cutting_button_ = new QPushButton(tr("Perform Cutting"), this);
  connect(perform_cutting_button_, SIGNAL(clicked()), ((MainWindow*) mParent), SLOT(performCutting()) );
  layout_->addWidget(perform_cutting_button_, 2, 0, 1, 2);

  // mCutbyVertexLayout = new QBoxLayout(QBoxLayout::LeftToRight);
  // mCutbyVertexLayout->setMargin(0);

  // QLabel *cutbyVertexOffsetLabel = new QLabel(tr("Offset:"));
  // cutbyVertexOffsetSpinBox = new QDoubleSpinBox;
  // cutbyVertexOffsetSpinBox->setRange(0, 1);
  // cutbyVertexOffsetSpinBox->setSingleStep(0.01);
  // cutbyVertexOffsetSpinBox->setValue(0.25);
  // cutbyVertexOffsetSpinBox->setMaximumSize(75,25);
  // connect(cutbyVertexOffsetSpinBox, SIGNAL(valueChanged(double)),
  //           this, SLOT(changeCutOffsetV(double)));
  //
  // mCutbyVertexLayout->addWidget(cutbyVertexOffsetLabel);
  //   mCutbyVertexLayout->addWidget(cutbyVertexOffsetSpinBox);
  //
  // cutbyVertexGlobalCheckBox = new QCheckBox(tr("global cut"),this);
  // cutbyVertexGlobalCheckBox->setChecked(Qt::Unchecked);
  // connect(cutbyVertexGlobalCheckBox, SIGNAL(stateChanged(int)),
  //           this, SLOT(toggleGlobalCut(int)));
  //
  // mCutbyVertexLayout->addWidget(cutbyVertexGlobalCheckBox);
  //
  // cutbyVertexCutSelectedCheckBox = new QCheckBox(tr("cut selected edges"),this);
  // cutbyVertexCutSelectedCheckBox->setChecked(Qt::Checked);
  // connect(cutbyVertexCutSelectedCheckBox, SIGNAL(stateChanged(int)),
  //           this, SLOT(toggleSelectedCut(int)));
  //
  // mCutbyVertexLayout->addWidget(cutbyVertexCutSelectedCheckBox);
  //
  // QPushButton *performCuttingButton = new QPushButton(tr("Perform Cutting"), this);
  // connect(performCuttingButton, SIGNAL(clicked()),
  //           ((MainWindow*)mParent), SLOT(performCutting()));
  //
  // mCutbyVertexLayout->addWidget(performCuttingButton);
  // mCutbyVertexLayout->addStretch(1);
  // mCutbyVertexWidget->setWindowTitle("Cut by Vertex");
  // mCutbyVertexWidget->setLayout(mCutbyVertexLayout);
  layout_->setRowStretch(3, 1);
  layout_->setColumnStretch(1, 1);
  widget_ = new QWidget;
  widget_->setWindowTitle(tr("Cut By Vertex"));
  widget_->setLayout(layout_);

  action_ = new QAction(tr("Cut By Vertex"), parent_);
  action_->setIcon(QIcon(":/images/sculpting-cutvertices.png"));
  action_->setCheckable(true);
  action_->setStatusTip(tr("Cut By Vertex"));
  action_->setToolTip(tr("Cut By Vertex"));
  connect(action_, SIGNAL(triggered()), this, SLOT(Activate()));
}

void CutByVertexTool::changeCutOffsetV(double value) {
  offset_spin_->setValue(value);
  ((MainWindow*) mParent)->changeCutOffsetV(value);
}

void CutByVertexTool::toggleGlobalCut(int state) {
  global_check_->setChecked(state);
  ((MainWindow*) mParent)->toggleGlobalCut(state);
}

void CutByVertexTool::Activate() {
  ((MainWindow*) parent_)->setToolOptions(widget_);
  ((MainWindow*) parent_)->setMode(MainWindow::CutVertex);
}

void CutByVertexTool::RetranslateUi() {

}

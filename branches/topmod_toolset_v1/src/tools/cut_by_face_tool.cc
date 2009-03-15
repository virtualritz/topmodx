/*
 * cut_by_face_tool.cc
 *
 *  Created on: Sep 15, 2008
 *      Author: david.morris
 */

#include "cut_by_face_tool.h"
#include "../MainWindow.h"
class MainWindow;

CutByFaceTool::CutByFaceTool(QWidget *parent) {
  parent_ = parent;
  layout_ = new QGridLayout;
  layout_->setVerticalSpacing(1);
  layout_->setHorizontalSpacing(1);

  //offset
  QLabel *offest_label = new QLabel(this);
  offset_spin_ = createDoubleSpinBox(layout_,
      offest_label, tr("Offset:"), 0.0, 2.0, 0.01, 0.25, 3, 0, 0);
  connect(offset_spin_, SIGNAL(valueChanged(double)), this, SLOT(changeCutOffsetE(double)));

  global_check_ = new QCheckBox(tr("Global Cut"), this);
  global_check_->setChecked(Qt::Unchecked);
  connect(global_check_, SIGNAL(stateChanged(int)), this, SLOT(toggleGlobalCut(int)));
  layout_->addWidget(global_check_, 1, 0, 1, 2);

  perform_cutting_button_ = new QPushButton(tr("Perform Cutting"), this);
  connect(perform_cutting_button_, SIGNAL(clicked()), ((MainWindow*) mParent), SLOT(performCutting()) );
  layout_->addWidget(perform_cutting_button_, 2, 0, 1, 2);

  // mCutbyFaceLayout = new QBoxLayout(QBoxLayout::LeftToRight);
  // mCutbyFaceLayout->setMargin(0);
  //
  // QLabel *cutbyFaceOffsetLabel = new QLabel(tr("Offset:"));
  // cutbyFaceOffsetSpinBox = new QDoubleSpinBox;
  // cutbyFaceOffsetSpinBox->setRange(0, 1);
  // cutbyFaceOffsetSpinBox->setSingleStep(0.01);
  // cutbyFaceOffsetSpinBox->setValue(0.25);
  // cutbyFaceOffsetSpinBox->setMaximumSize(75,25);
  // connect(cutbyFaceOffsetSpinBox, SIGNAL(valueChanged(double)),
  //           this, SLOT(changeCutOffsetE(double)));
  //
  // mCutbyFaceLayout->addWidget(cutbyFaceOffsetLabel);
  //   mCutbyFaceLayout->addWidget(cutbyFaceOffsetSpinBox);
  //
  // cutbyFaceGlobalCheckBox = new QCheckBox(tr("global cut"),this);
  // cutbyFaceGlobalCheckBox->setChecked(Qt::Unchecked);
  // connect(cutbyFaceGlobalCheckBox, SIGNAL(stateChanged(int)),
  //           this, SLOT(toggleGlobalCut(int)));
  //
  // mCutbyFaceLayout->addWidget(cutbyFaceGlobalCheckBox);
  //
  // cutbyFaceCutSelectedCheckBox = new QCheckBox(tr("cut selected faces"),this);
  // cutbyFaceCutSelectedCheckBox->setChecked(Qt::Checked);
  // connect(cutbyFaceCutSelectedCheckBox, SIGNAL(stateChanged(int)),
  //           this, SLOT(toggleSelectedCut(int)));
  //
  // mCutbyFaceLayout->addWidget(cutbyFaceCutSelectedCheckBox);
  //
  // QPushButton *performCuttingButton = new QPushButton(tr("Perform Cutting"), this);
  // connect(performCuttingButton, SIGNAL(clicked()),
  //           ((MainWindow*)mParent), SLOT(performCutting()));

  layout_->setRowStretch(3, 1);
  layout_->setColumnStretch(1, 1);
  widget_ = new QWidget;
  widget_->setWindowTitle(tr("Cut By Face"));
  widget_->setLayout(layout_);

  action_ = new QAction(tr("Cut By Face"), parent_);
  action_->setIcon(QIcon(":/images/sculpting-cutfaces.png"));
  action_->setCheckable(true);
  action_->setStatusTip(tr("Cut By Face"));
  action_->setToolTip(tr("Cut By Face"));
  connect(action_, SIGNAL(triggered()), this, SLOT(Activate()));
}

void CutByFaceTool::changeCutOffsetE(double value){
  offset_spin_->setValue(value);
  ((MainWindow*)mParent)->changeCutOffsetE(value);
}

void CutByFaceTool::toggleGlobalCut(int state){
  global_check_->setChecked(state);
  ((MainWindow*)mParent)->toggleGlobalCut(state);
}

void CutByFaceTool::Activate() {
  ((MainWindow*) parent_)->setToolOptions(widget_);
  ((MainWindow*) parent_)->setMode(MainWindow::CutFace);
}

void CutByFaceTool::RetranslateUi() {

}

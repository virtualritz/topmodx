/*
 * rind_modeling_scaling_tool.cc
 *
 *  Created on: Sep 12, 2008
 *      Author: david.morris
 */

#include "rind_modeling_scaling_tool.h"
#include "../MainWindow.h"
class MainWindow;

RindModelingScalingTool::RindModelingScalingTool(QWidget *parent) {
  parent_ = parent;
  layout_ = new QGridLayout;
  layout_->setVerticalSpacing(1);
  layout_->setHorizontalSpacing(1);
  //scale factor - 0.00-10.00
  scale_label_ = new QLabel(this);
  scale_spin_ = createDoubleSpinBox(layout_, scale_label_, tr("Scale"), 0,
      10.0, 0.01, 0.9, 3, 0, 0);
  connect(scale_spin_, SIGNAL(valueChanged(double)), ((MainWindow*) parent_), SLOT(changeCrustScaleFactor(double)));
  //symmetric weights checkbox
  cleanup_check_ = new QCheckBox(tr("Cleanup when peeling"), this);
  cleanup_check_->setChecked(Qt::Unchecked);
  connect(cleanup_check_, SIGNAL(stateChanged(int)), ((MainWindow*) parent_), SLOT(toggleCrustCleanupFlag(int)));
  layout_->addWidget(cleanup_check_, 1, 0, 1, 2);
  //create crust button
  create_button_
      = new QPushButton(tr("Create Crust"), this);
  connect(create_button_, SIGNAL(clicked()), ((MainWindow*) parent_), SLOT(crustModeling4())); // ((MainWindow*)parent_), SLOT(crust_modeling1())); //crust_modeling3
  layout_->addWidget(create_button_, 2, 0, 1, 2);

  layout_->setRowStretch(3, 1);
  layout_->setColumnStretch(2, 1);
  widget_ = new QWidget;
  widget_->setWindowTitle(tr("Rind Modeling Scaling"));
  widget_->setLayout(layout_);

  action_ = new QAction(tr("Rind Modeling Scaling"), parent_);
  action_->setIcon(QIcon(":/images/highgenus_rindscaling.png"));
  action_->setCheckable(true);
  action_->setStatusTip(tr("Rind Modeling Scaling"));
  action_->setToolTip(tr("Rind Modeling Scaling"));
  connect(action_, SIGNAL(triggered()), this, SLOT(Activate()));
}

void RindModelingScalingTool::Activate() {
  ((MainWindow*) parent_)->setToolOptions(widget_);
  ((MainWindow*) parent_)->setMode(MainWindow::SelectFaceLoop);
}

void RindModelingScalingTool::RetranslateUi() {

}

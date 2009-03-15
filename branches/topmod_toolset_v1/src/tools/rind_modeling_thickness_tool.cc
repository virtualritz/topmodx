/*
 * rind_modeling_thickness_tool.cc
 *
 *  Created on: Sep 12, 2008
 *      Author: david.morris
 */

#include "rind_modeling_thickness_tool.h"
#include "../MainWindow.h"
class MainWindow;

RindModelingThicknessTool::RindModelingThicknessTool(QWidget *parent) {
  parent_ = parent;
  layout_ = new QGridLayout;
  layout_->setVerticalSpacing(1);
  layout_->setHorizontalSpacing(1);
  //thickness
  thickness_label_ = new QLabel(this);
  thickness_spin_ = createDoubleSpinBox(layout_, thickness_label_, tr(
      "Thickness:"), -1.0, 1.0, 0.01, 0.5, 3, 0, 0);
  connect(thickness_spin_, SIGNAL(valueChanged(double)), ((MainWindow*) parent_), SLOT(changeCrustThickness(double)));
  //cleanup checkbox
  cleanup_check_ = new QCheckBox(tr("Cleanup when peeling"), this);
  cleanup_check_->setChecked(Qt::Unchecked);
  connect(cleanup_check_, SIGNAL(stateChanged(int)), ((MainWindow*) parent_), SLOT(toggleCrustCleanupFlag(int)));
  layout_->addWidget(cleanup_check_, 1, 0, 1, 2);
  //create crust button
  create_button_ = new QPushButton(tr("Create Crust"), this);
  connect(create_button_, SIGNAL(clicked()), ((MainWindow*) parent_), SLOT(crustModeling3()));
  layout_->addWidget(create_button_, 2, 0, 1, 2);
  //set layout and add stretch
  layout_->setRowStretch(3, 1);
  layout_->setColumnStretch(2, 1);
  widget_ = new QWidget;
  widget_->setWindowTitle(tr("Rind Modeling Thickness"));
  widget_->setLayout(layout_);

  action_ = new QAction(tr("Rind Modeling Thickness"), parent_);
  action_->setIcon(QIcon(":/images/highgenus_rindthickness.png"));
  action_->setCheckable(true);
  action_->setStatusTip(tr("Rind Modeling Thickness"));
  action_->setToolTip(tr("Rind Modeling Thickness"));
  connect(action_, SIGNAL(triggered()), this, SLOT(Activate()));
}

void RindModelingThicknessTool::Activate() {
  ((MainWindow*) parent_)->setToolOptions(widget_);
  ((MainWindow*) parent_)->setMode(MainWindow::SelectFaceLoop);
}

void RindModelingThicknessTool::RetranslateUi() {

}

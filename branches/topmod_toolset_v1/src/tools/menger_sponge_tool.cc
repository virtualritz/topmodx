/*
 * menger_sponge_tool.cc
 *
 *  Created on: Sep 12, 2008
 *      Author: david.morris
 */

#include "menger_sponge_tool.h"
#include "../MainWindow.h"
class MainWindow;

MengerSpongeTool::MengerSpongeTool(QWidget *parent) {
  parent_ = parent;
  layout_ = new QGridLayout;
  layout_->setVerticalSpacing(1);
  layout_->setHorizontalSpacing(1);
  //thickness
  thickness_label_ = new QLabel(this);
  thickness_spin_ = createDoubleSpinBox(layout_, thickness_label_, tr(
      "Thickness:"), 0.01, 1.0, 0.01, 0.67, 3, 0, 0);
  connect(thickness_spin_, SIGNAL(valueChanged(double)), ((MainWindow*) mParent), SLOT(changeMengerSpongeThickness(double)));
  //threshold
  threshold_label_ = new QLabel(this);
  threshold_spin_ = createDoubleSpinBox(layout_, threshold_label_, tr(
      "Edge Collapse\nThreshold Factor:"), 0.0, 10.0, 0.1, 0.0, 3, 1, 0);
  connect(threshold_spin_, SIGNAL(valueChanged(double)), ((MainWindow*) mParent), SLOT(changeMengerSpongeCollapseThreshold(double)));
  //fractional thickness checkbox
  fractional_thickness_check_ = new QCheckBox(tr("Fractional Thickness"), this);
  connect(fractional_thickness_check_, SIGNAL(stateChanged(int)), ((MainWindow*) mParent), SLOT(toggleMengerSpongeFractionalThicknessFlag(int)));
  layout_->addWidget(fractional_thickness_check_, 2, 0, 1, 2);
  //create menger sponge button
  create_sponge_button_ = new QPushButton(tr("Create Menger Sponge"), this);
  connect(create_sponge_button_, SIGNAL(clicked()), ((MainWindow*) mParent), SLOT(createSponge()));
  layout_->addWidget(create_sponge_button_, 3, 0, 1, 2);

  layout_->setRowStretch(4, 1);
  layout_->setColumnStretch(2, 1);
  widget_ = new QWidget;
  widget_->setWindowTitle(tr("Menger Sponge"));
  widget_->setLayout(layout_);

  action_ = new QAction(tr("Menger Sponge"), parent_);
  action_->setIcon(QIcon(":/images/highgenus_mengersponge.png"));
  action_->setCheckable(true);
  action_->setStatusTip(tr("Menger Sponge"));
  action_->setToolTip(tr("Menger Sponge"));
  connect(action_, SIGNAL(triggered()), this, SLOT(Activate()));
}

void MengerSpongeTool::Activate() {
  ((MainWindow*) parent_)->setToolOptions(widget_);
  ((MainWindow*) parent_)->setMode(MainWindow::NormalMode);
}

void MengerSpongeTool::RetranslateUi() {

}

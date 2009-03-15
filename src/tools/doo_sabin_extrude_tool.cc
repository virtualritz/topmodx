/*
 * doo_sabin_extrude_tool.cc
 *
 *  Created on: Sep 15, 2008
 *      Author: david.morris
 */

#include "doo_sabin_extrude_tool.h"
#include "../MainWindow.h"
class MainWindow;

DooSabinExtrudeTool::DooSabinExtrudeTool(QWidget *parent) {
  parent_ = parent;
  layout_ = new QGridLayout;
  layout_->setVerticalSpacing(1);
  layout_->setHorizontalSpacing(1);
  //length
  QLabel *length_label = new QLabel(this);
  length_spin_ = createDoubleSpinBox(layout_, length_label, tr("Length"),
      -100.0, 100.0, 0.1, 2.0, 3, 0, 0);
  connect(length_spin_, SIGNAL(valueChanged(double)), (MainWindow*) parent_), SLOT(changeExtrudeLength(double)));
  //rotation
  QLabel *twist_label = new QLabel(this);
  twist_spin_ = createDoubleSpinBox(layout_, twist_label, tr("Twist"), -5, 5,
      .01, 0.0, 3, 1, 0);
  connect(twist_spin_, SIGNAL( valueChanged(double)), ((MainWindow*) parent_), SLOT( changeDooSabinExtrudeTwist(double)));
  //scale
  QLabel *scale_label = new QLabel(this);
  scale_spin_ = createDoubleSpinBox(layout_, scale_label, tr("Scale"), 0.0,
      10.0, 0.01, 1.0, 3, 2, 0);
  connect(scale_spin_, SIGNAL(valueChanged(double)), ((MainWindow*) parent_), SLOT(changeExtrudeScale(double)));
  //segments
  QLabel *segments_label = new QLabel(this);
  segments_spin_ = createDoubleSpinBox(layout_, segments_label, tr("Segments"),
      1, 50, 1, 1, 0, 3, 0);
  connect(segments_spin_, SIGNAL(valueChanged(double)), ((MainWindow*) parent_), SLOT(changeNumExtrusions(int)));

  perform_extrusion_button_
      = new QPushButton(tr("Extrude Selected Faces"), this);
  connect(perform_extrusion_button_, SIGNAL(clicked()), ((MainWindow*) parent_), SLOT(performExtrusion()));
  layout_->addWidget(perform_extrusion_button_, 4, 0, 1, 2);

  layout_->setRowStretch(5, 1);
  layout_->setColumnStretch(2, 1);
  widget_ = new QWidget;
  widget_->setWindowTitle(tr("Doo Sabin Extrude"));
  widget_->setLayout(layout_);

  action_ = new QAction(tr("Doo Sabin Extrude"), parent_);
  action_->setIcon(QIcon(":/images/extrude_doosabin.png"));
  action_->setCheckable(true);
  action_->setStatusTip(tr("Doo Sabin Extrude"));
  action_->setToolTip(tr("Doo Sabin Extrude"));
  connect(action_, SIGNAL(triggered()), this, SLOT(Activate()));
}

void DooSabinExtrudeTool::Activate() {
  ((MainWindow*) parent_)->setToolOptions(widget_);
  ((MainWindow*) parent_)->setMode(MainWindow::ExtrudeFaceDS);
  ((MainWindow*) parent_)->setExtrusionMode(MainWindow::DooSabinExtrude);
  ((MainWindow*) parent_)->setSpinBoxes(dooSabinLengthSpinBox,
      dooSabinTwistSpinBox, dooSabinScaleSpinBox, dooSabinSegmentsSpinBox);

}

void DooSabinExtrudeTool::RetranslateUi() {
  action_->setStatusTip(tr("Doo Sabin Extrude"));
  action_->setToolTip(tr("Doo Sabin Extrude"));
  action_->setText(tr("Doo Sabin Extrude"));
  widget_->setWindowTitle(tr("Doo Sabin Extrude"));
}

/*
 * icosahedral_extrude_tool.cc
 *
 *  Created on: Sep 15, 2008
 *      Author: david.morris
 */

#include "icosahedral_extrude_tool.h"
#include "../MainWindow.h"
class MainWindow;

IcosahedralExtrudeTool::IcosahedralExtrudeTool(QWidget *parent) {
  parent_ = parent;
  layout_ = new QGridLayout;
  layout_->setVerticalSpacing(1);
  layout_->setHorizontalSpacing(1);
  //length1
  length1_label_ = new QLabel(this);
  length1_spin_ = createDoubleSpinBox(layout_, length1_label_, tr("Length 1"),
      0.0, 100.0, 0.1, 0.5, 3, 0, 0);
  connect(length1_label_, SIGNAL(valueChanged(double)), ((MainWindow*) parent_), SLOT(changeExtrudeLength1Icosa(double)));
  //length2
  length2_label_ = new QLabel(this);
  length2_spin_ = createDoubleSpinBox(layout_, length2_label_, tr("Length 2"),
      0.0, 100.0, 0.1, 0.7, 3, 1, 0);
  connect(length2_spin_, SIGNAL(valueChanged(double)), ((MainWindow*) parent_), SLOT(changeExtrudeLength2Icosa(double)));
  //length3
  length3_label_ = new QLabel(this);
  length3_spin_ = createDoubleSpinBox(layout_, length3_label_, tr("Length 3"),
      0.0, 100.0, 0.1, 0.8, 3, 2, 0);
  connect(length3_spin_, SIGNAL(valueChanged(double)), ((MainWindow*) parent_), SLOT(changeExtrudeLength3Icosa(double)));
  //angle
  angle_label_ = new QLabel(this);
  angle_spin_ = createDoubleSpinBox(layout_, angle_label_, tr("Angle"), 0.0,
      180.0, 0.1, 50.0, 3, 3, 0);
  connect(angle_spin_, SIGNAL(valueChanged(double)), ((MainWindow*) parent_), SLOT(changeExtrudeAngleIcosa(double)));
  //segments
  segments_label_ = new QLabel(this);
  segments_spin_ = createDoubleSpinBox(layout_,
      segments_label_, tr("Segments"), 1, 50, 1, 1, 0, 4, 0);
  connect(segments_spin_, SIGNAL(valueChanged(double)), ((MainWindow*) parent_), SLOT(changeNumExtrusions(double)));

  perform_extrusion_button_ = new QPushButton(tr(
      "Extrude Selected Faces"), this);
  connect(perform_extrusion_button_, SIGNAL(clicked()), ((MainWindow*) parent_), SLOT(performExtrusion()));
  layout_->addWidget(perform_extrusion_button_, 5, 0, 1, 2);

  layout_->setRowStretch(6, 1);
  layout_->setColumnStretch(2, 1);
  widget_ = new QWidget;
  widget_->setWindowTitle(tr("Icosahedral Extrude"));
  widget_->setLayout(layout_);

  action_ = new QAction(tr("Icosahedral Extrude"), parent_);
  action_->setIcon(QIcon(":/images/extrude_icosahedral.png"));
  action_->setCheckable(true);
  action_->setStatusTip(tr("Icosahedral Extrude"));
  action_->setToolTip(tr("Icosahedral Extrude"));
  connect(action_, SIGNAL(triggered()), this, SLOT(Activate()));
}

void IcosahedralExtrudeTool::Activate() {
  ((MainWindow*) parent_)->setToolOptions(widget_);
  ((MainWindow*) parent_)->setMode(MainWindow::ExtrudeFaceIcosa);
  ((MainWindow*) parent_)->setExtrusionMode(MainWindow::IcosahedralExtrude);
  //  ((MainWindow*) parent_)->setSpinBoxes(dooSabinLengthSpinBox,
  //      dooSabinTwistSpinBox, dooSabinScaleSpinBox, dooSabinSegmentsSpinBox);
}

void IcosahedralExtrudeTool::RetranslateUi() {
  action_->setStatusTip(tr("Icosahedral Extrude"));
  action_->setToolTip(tr("Icosahedral Extrude"));
  action_->setText(tr("Icosahedral Extrude"));
  widget_->setWindowTitle(tr("Icosahedral Extrude"));
}

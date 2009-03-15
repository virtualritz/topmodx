/*
 * dodecahedral_extrude_tool.cc
 *
 *  Created on: Sep 15, 2008
 *      Author: david.morris
 */

#include "dodecahedral_extrude_tool.h"
#include "../MainWindow.h"
class MainWindow;

DodecahedralExtrudeTool::DodecahedralExtrudeTool(QWidget *parent) {
  parent_ = parent;
  layout_ = new QGridLayout;
  layout_->setVerticalSpacing(1);
  layout_->setHorizontalSpacing(1);
  //length1
  length1_label_ = new QLabel(this);
  length1_spin_ = createDoubleSpinBox(layout_, length1_label_, tr("Length 1"),
      0.0, 100.0, 0.1, 0.5, 3, 0, 0);
  connect(length1_spin_, SIGNAL(valueChanged(double)), ((MainWindow*) parent_), SLOT(changeExtrudeLength1(double)));
  //length2
  length2_label_ = new QLabel(this);
  length2_spin_ = createDoubleSpinBox(layout_, length2_label_, tr("Length 2"),
      0.0, 100.0, 0.1, 1.0, 3, 1, 0);
  connect(length2_spin_, SIGNAL(valueChanged(double)), ((MainWindow*) parent_), SLOT(changeExtrudeLength2(double)));
  //length3
  length3_label_ = new QLabel(this);
  length3_spin_ = createDoubleSpinBox(layout_, length3_label_, tr("Length 3"),
      0.0, 100.0, 0.1, 1.0, 3, 2, 0);
  connect(length3_spin_, SIGNAL(valueChanged(double)), ((MainWindow*) parent_), SLOT(changeExtrudeLength3(double)));
  //angle
  angle_label_ = new QLabel(this);
  angle_spin_ = createDoubleSpinBox(layout_, angle_label_, tr("Angle"), 0.0,
      180.0, 0.1, 40.0, 3, 3, 0);
  connect(angle_spin_, SIGNAL(valueChanged(double)), ((MainWindow*) parent_), SLOT(changeExtrudeAngle(double)));
  //segments
  segments_label_ = new QLabel(this);
  segments_spin_ = createDoubleSpinBox(layout_, segments_label_,
      tr("Segments"), 1, 50, 1, 1, 0, 4, 0);
  connect(segments_spin_, SIGNAL(valueChanged(double)), ((MainWindow*) parent_), SLOT(changeNumExtrusions(double)));
  //mesh flat edges checkbox
  hexagonalize_check_ = new QCheckBox(tr("Hexagonalize"), this);
  connect(hexagonalize_check_, SIGNAL( stateChanged(int)), ((MainWindow*) parent_), SLOT( toggleHexagonalizeDodecaExtrudeFlag(int)));
  layout_->addWidget(hexagonalizeCheckBox, 5, 1);
  //button
  perform_extrusion_button_
      = new QPushButton(tr("Extrude Selected Faces"), this);
  connect(perform_extrusion_button_, SIGNAL(clicked()), ((MainWindow*) parent_), SLOT(performExtrusion()));
  layout_->addWidget(perform_extrusion_button_, 6, 0, 1, 2);

  layout_->setRowStretch(7, 1);
  layout_->setColumnStretch(2, 1);
  widget_ = new QWidget;
  widget_->setWindowTitle(tr("Dodecahedral Extrude"));
  widget_->setLayout(layout_);

  action_ = new QAction(tr("Dodecahedral Extrude"), parent_);
  action_->setIcon(QIcon(":/images/extrude_dodecahedral.png"));
  action_->setCheckable(true);
  action_->setStatusTip(tr("Dodecahedral Extrude"));
  action_->setToolTip(tr("Dodecahedral Extrude"));
  connect(action_, SIGNAL(triggered()), this, SLOT(Activate()));
}

void DodecahedralExtrudeTool::Activate() {
  ((MainWindow*) parent_)->setToolOptions(widget_);
  ((MainWindow*) parent_)->setMode(MainWindow::ExtrudeFaceDodeca);
  ((MainWindow*) parent_)->setExtrusionMode(MainWindow::DodecahedralExtrude);
  //  ((MainWindow*) parent_)->setSpinBoxes(dooSabinLengthSpinBox,
  //      dooSabinTwistSpinBox, dooSabinScaleSpinBox, dooSabinSegmentsSpinBox);
}

void DodecahedralExtrudeTool::RetranslateUi() {
  action_->setStatusTip(tr("Dodecahedral Extrude"));
  action_->setToolTip(tr("Dodecahedral Extrude"));
  action_->setText(tr("Dodecahedral Extrude"));
  widget_->setWindowTitle(tr("Dodecahedral Extrude"));
}

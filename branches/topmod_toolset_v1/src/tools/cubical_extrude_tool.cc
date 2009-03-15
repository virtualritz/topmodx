/*
 * cubical_extrude_tool.cc
 *
 *  Created on: Sep 15, 2008
 *      Author: david.morris
 */

#include "cubical_extrude_tool.h"
#include "../MainWindow.h"
class MainWindow;

CubicalExtrudeTool::CubicalExtrudeTool(QWidget *parent) {
  parent_ = parent;
  layout_ = new QGridLayout;
  layout_->setVerticalSpacing(1);
  layout_->setHorizontalSpacing(1);
  //length
  length_label_ = new QLabel(this);
  length_spin_ = createDoubleSpinBox(layout_, length_label_, tr("Length"),
      -100.0, 100.0, 0.1, 2.0, 3, 0, 0);
  connect(length_spin_, SIGNAL(valueChanged(double)), (MainWindow*) parent_), SLOT(changeExtrudeLength(double)));
  //rotation
  rotation_label_ = new QLabel(this);
  rotation_spin_ = createDoubleSpinBox(layout_, rotation_label_, tr("Rotation"), 0,
      360, 1, 0.0, 3, 1, 0);
  connect(rotation_spin_, SIGNAL( valueChanged(double)), ((MainWindow*) parent_), SLOT( setRotation(double)));
  //scale
  scale_label_ = new QLabel(this);
  scale_spin_ = createDoubleSpinBox(layout_, scale_label_, tr("Scale"), 0.0,
      10.0, 0.01, 1.0, 3, 2, 0);
  connect(scale_spin_, SIGNAL(valueChanged(double)), ((MainWindow*) parent_), SLOT(changeExtrudeScale(double)));
  //segments
  QLabel *segments_label_ = new QLabel(this);
  segments_spin_ = createDoubleSpinBox(layout_, segments_label_, tr("Segments"),
      1, 50, 1, 1, 0, 3, 0);
  connect(segments_spin_, SIGNAL(valueChanged(double)), ((MainWindow*) parent_), SLOT(changeNumExtrusions(int)));

  triangulate_new_faces_check_
      = new QCheckBox(tr("Triangulate New Faces"), this);
  connect(triangulate_new_faces_check_, SIGNAL(stateChanged(int)), ((MainWindow*) parent_), SLOT(toggleCubicalTriangulateFace(int)));
  layout_->addWidget(triangulate_new_faces_check_, 5, 0, 1, 2);

  scherk_collins_check_ = new QCheckBox(tr("Scherk Collins"), this);
  connect(scherk_collins_check_, SIGNAL(stateChanged(int)), this, SLOT(toggleCubicalScherkCollins(int)));
  layout_->addWidget(scherk_collins_check_, 6, 0, 1, 2);

  pinch_label_ = new QLabel(this);
  cubicalPinchSpinBox = createDoubleSpinBox(layout_, pinch_label_, tr("Pinch"),
      -1, 10, 0.1, 1.0, 2, 7, 0);
  connect(cubicalPinchSpinBox, SIGNAL(valueChanged(double)), ((MainWindow*) parent_), SLOT(ChangeScherkCollinsPinch(double)));

  pinch_center_label_ = new QLabel(this);
  pinch_center_spin_ = createDoubleSpinBox(layout_, pinch_center_label_, tr(
      "Pinch Center"), 0.1, 1, 0.1, 0.5, 3, 8, 0);
  connect(pinch_center_spin_, SIGNAL(valueChanged(double)), ((MainWindow*) parent_), SLOT(ChangeScherkCollinsPinchCenter(double)));

  pinch_width_label_ = new QLabel(this);
  cubicalPinchWidthSpinBox = createDoubleSpinBox(layout_, pinch_width_label_,
      tr("Pinch Width"), 0.001, 10, 0.1, 1.0, 3, 9, 0);
  connect(cubicalPinchWidthSpinBox, SIGNAL(valueChanged(double)), ((MainWindow*) parent_), SLOT(ChangeScherkCollinsPinchWidth(double)));

  perform_extrusion_button_
      = new QPushButton(tr("Extrude Selected Faces"), this);
  connect(perform_extrusion_button_, SIGNAL(clicked()), ((MainWindow*) parent_), SLOT(performExtrusion()));
  layout_->addWidget(perform_extrusion_button_, 10, 0, 1, 2);

  layout_->setRowStretch(11, 1);
  layout_->setColumnStretch(2, 1);
  widget_ = new QWidget;
  widget_->setWindowTitle(tr("Cubical Extrude"));
  widget_->setLayout(layout_);

  action_ = new QAction(tr("Cubical Extrude"), parent_);
  action_->setIcon(QIcon(":/images/extrude_cubical.png"));
  action_->setCheckable(true);
  action_->setStatusTip(tr("Cubical Extrude"));
  action_->setToolTip(tr("Cubical Extrude"));
  connect(action_, SIGNAL(triggered()), this, SLOT(Activate()));
}

void CubicalExtrudeTool::toggleCubicalScherkCollins(int state) {
  ((MainWindow*) parent_)->toggleScherkCollins(state);
  if ((bool) state) {
    triangulate_new_faces_check_->setChecked(Qt::Unchecked);
    pinch_spin_->setEnabled(true);
    pinch_center_spin_->setEnabled(true);
    pinch_width_spin_->setEnabled(true);
  } else {
    pinch_spin_->setEnabled(false);
    pinch_center_spin_->setEnabled(false);
    pinch_width_spin_->setEnabled(false);
  }
}

void CubicalExtrudeTool::Activate() {
  ((MainWindow*) parent_)->setToolOptions(widget_);
  ((MainWindow*) parent_)->setMode(MainWindow::ExtrudeFace);
  ((MainWindow*) parent_)->setExtrusionMode(MainWindow::DooSabinExtrude);
  ((MainWindow*) parent_)->setSpinBoxes(dooSabinLengthSpinBox,
      dooSabinTwistSpinBox, dooSabinScaleSpinBox, dooSabinSegmentsSpinBox);
}

void CubicalExtrudeTool::RetranslateUi() {
  action_->setStatusTip(tr("Cubical Extrude"));
  action_->setToolTip(tr("Cubical Extrude"));
  action_->setText(tr("Cubical Extrude"));
  widget_->setWindowTitle(tr("Cubical Extrude"));
}

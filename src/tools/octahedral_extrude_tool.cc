/*
 * octahedral_extrude_tool.cc
 *
 *  Created on: Sep 15, 2008
 *      Author: david.morris
 */

#include "octahedral_extrude_tool.h"
#include "../MainWindow.h"
class MainWindow;

OctahedralExtrudeTool::OctahedralExtrudeTool(QWidget *parent) {
  parent_ = parent;
  layout_ = new QGridLayout;
  layout_->setVerticalSpacing(1);
  layout_->setHorizontalSpacing(1);
  //length
  length_label_ = new QLabel(this);
  length_spin_ = createDoubleSpinBox(layout_, length_label_, tr(
      "Length"), -100.0, 100.0, 0.1, 2.0, 3, 0, 0);
  connect(length_spin_, SIGNAL(valueChanged(double)), ((MainWindow*) parent_), SLOT(changeExtrudeLength(double)));
  //rotation
  rotation_label_ = new QLabel(this);
  rotation_spin_ = createDoubleSpinBox(layout_, rotation_label_, tr(
      "Rotation"), 0, 360, 1, 0.0, 3, 1, 0);
  connect(rotation_spin_, SIGNAL(valueChanged(double)), ((MainWindow*) parent_), SLOT(changeExtrudeRotation(double)));
  //scale
  scale_label_ = new QLabel(this);
  scale_spin_ = createDoubleSpinBox(layout_, scale_label_, tr("Scale"),
      0.0, 10.0, 0.01, 1.0, 3, 2, 0);
  connect(scale_spin_, SIGNAL(valueChanged(double)), ((MainWindow*) parent_), SLOT(changeExtrudeScale(double)));
  //segments
  segments_label_ = new QLabel(this);
  segments_spin_ = createDoubleSpinBox(layout_, segments_label_, tr(
      "Segments"), 1, 50, 1, 1, 0, 3, 0);
  connect(segments_spin_, SIGNAL(valueChanged(double)), ((MainWindow*) parent_), SLOT(changeNumExtrusions(double)));
  //mesh flat edges checkbox
  mesh_flat_edges_check_ = new QCheckBox(tr("Mesh Flat Edges"), this);
  connect(mesh_flat_edges_check_, SIGNAL( stateChanged(int)), ((MainWindow*) parent_), SLOT( toggleDualMeshEdgesFlag(int)));
  layout_->addWidget(mesh_flat_edges_check_, 4, 1);

  perform_extrusion_button_
      = new QPushButton(tr("Extrude Selected Faces"), this);
  connect(perform_extrusion_button_, SIGNAL(clicked()), ((MainWindow*) parent_), SLOT(performExtrusion()));
  layout_->addWidget(perform_extrusion_button_, 5, 0, 1, 2);

  layout_->setRowStretch(6, 1);
  layout_->setColumnStretch(2, 1);
  widget_ = new QWidget;
  widget_->setWindowTitle(tr("Octahedral Extrude"));
  widget_->setLayout(layout_);

  action_ = new QAction(tr("Octahedral Extrude"), parent_);
  action_->setIcon(QIcon(":/images/extrude_doosabin.png"));
  action_->setCheckable(true);
  action_->setStatusTip(tr("Octahedral Extrude"));
  action_->setToolTip(tr("Octahedral Extrude"));
  connect(action_, SIGNAL(triggered()), this, SLOT(Activate()));
}

void OctahedralExtrudeTool::Activate() {
  ((MainWindow*) parent_)->setToolOptions(widget_);
  ((MainWindow*) parent_)->setMode(MainWindow::ExtrudeDualFace);
  ((MainWindow*) parent_)->setExtrusionMode(MainWindow::OctahedralExtrude);
  //  ((MainWindow*) parent_)->setSpinBoxes(dooSabinLengthSpinBox,
  //      dooSabinTwistSpinBox, dooSabinScaleSpinBox, dooSabinSegmentsSpinBox);

}

void OctahedralExtrudeTool::RetranslateUi() {
  action_->setStatusTip(tr("Octahedral Extrude"));
  action_->setToolTip(tr("Octahedral Extrude"));
  action_->setText(tr("Octahedral Extrude"));
  widget_->setWindowTitle(tr("Octahedral Extrude"));
}

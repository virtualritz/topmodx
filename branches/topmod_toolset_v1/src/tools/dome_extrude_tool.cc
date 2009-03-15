/*
 * dome_extrude_tool.cc
 *
 *  Created on: Sep 15, 2008
 *      Author: david.morris
 */

#include "dome_extrude_tool.h"
#include "../MainWindow.h"
class MainWindow;

DomeExtrudeTool::DomeExtrudeTool(QWidget *parent) {
  parent_ = parent;
  layout_ = new QGridLayout;
  layout_->setVerticalSpacing(1);
  layout_->setHorizontalSpacing(1);
  //length
  height_label_ = new QLabel(this);
  height_spin_ = createDoubleSpinBox(layout_, height_label_, tr("Height:"),
      -10.0, 100.0, 0.01, 1.0, 3, 0, 0);
  connect(height_spin_, SIGNAL( valueChanged(double)), ((MainWindow*) parent_), SLOT( changeDomeExtrudeLength(double)));
  rotation_label_ = new QLabel(this);
  rotation_spin_ = createDoubleSpinBox(layout_, rotation_label_,
      tr("Rotation:"), -1.0, 1.0, 0.01, 0.0, 3, 1, 0);
  connect(rotation_spin_, SIGNAL( valueChanged(double)), ((MainWindow*) parent_), SLOT( changeDomeExtrudeRotation(double)));
  scale_label_ = new QLabel(this);
  scale_spin_ = createDoubleSpinBox(layout_, scale_label_, tr("Scale:"), 0.0,
      10.0, 0.01, 1.0, 3, 2, 0);
  connect(scale_spin_, SIGNAL( valueChanged(double)), ((MainWindow*) parent_), SLOT( changeDomeExtrudeScale(double)));

  perform_extrusion_button_
      = new QPushButton(tr("Extrude Selected Faces"), this);
  connect(perform_extrusion_button_, SIGNAL(clicked()), ((MainWindow*) parent_), SLOT(performExtrusion()));
  layout_->addWidget(perform_extrusion_button_, 3, 0, 1, 2);

  layout_->setRowStretch(4, 1);
  layout_->setColumnStretch(2, 1);
  widget_ = new QWidget;
  widget_->setWindowTitle(tr("Dome Extrude"));
  widget_->setLayout(layout_);

  action_ = new QAction(tr("Dome Extrude"), parent_);
  action_->setIcon(QIcon(":/images/extrude_dome.png"));
  action_->setCheckable(true);
  action_->setStatusTip(tr("Dome Extrude"));
  action_->setToolTip(tr("Dome Extrude"));
  connect(action_, SIGNAL(triggered()), this, SLOT(Activate()));
}

void DomeExtrudeTool::Activate() {
  ((MainWindow*) parent_)->setToolOptions(widget_);
  ((MainWindow*) parent_)->setMode(MainWindow::ExtrudeFaceDome);
  ((MainWindow*) parent_)->setExtrusionMode(MainWindow::DomeExtrude);
  //  ((MainWindow*) parent_)->setSpinBoxes(dooSabinLengthSpinBox,
  //      dooSabinTwistSpinBox, dooSabinScaleSpinBox, dooSabinSegmentsSpinBox);

}

void DomeExtrudeTool::RetranslateUi() {
  action_->setStatusTip(tr("Dome Extrude"));
  action_->setToolTip(tr("Dome Extrude"));
  action_->setText(tr("Dome Extrude"));
  widget_->setWindowTitle(tr("Dome Extrude"));
}

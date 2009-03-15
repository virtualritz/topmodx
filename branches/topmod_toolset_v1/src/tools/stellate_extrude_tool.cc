/*
 * stellate_extrude_tool.cc
 *
 *  Created on: Sep 15, 2008
 *      Author: david.morris
 */

#include "stellate_extrude_tool.h"
#include "../MainWindow.h"
class MainWindow;

StellateExtrudeTool::StellateExtrudeTool(QWidget *parent) {
  parent_ = parent;
  layout_ = new QGridLayout;
  layout_->setVerticalSpacing(1);
  layout_->setHorizontalSpacing(1);
  //length
  length_label_ = new QLabel(this);
  length_spin_ = createDoubleSpinBox(layout_, length_label_, tr("Length"),
      -100.0, 100.0, 0.1, 2.0, 3, 0, 0);
  connect(length_spin_, SIGNAL(valueChanged(double)), ((MainWindow*) parent_), SLOT(changeExtrudeLength(double)));
  //button
  perform_extrusion_button_
      = new QPushButton(tr("Extrude Selected Faces"), this);
  connect(perform_extrusion_button_, SIGNAL(clicked()), ((MainWindow*) parent_), SLOT(performExtrusion()));
  layout_->addWidget(perform_extrusion_button_, 1, 0, 1, 2);

  layout_->setRowStretch(2, 1);
  layout_->setColumnStretch(2, 1);
  widget_ = new QWidget;
  widget_->setWindowTitle(tr("Stellate Extrude"));
  widget_->setLayout(layout_);

  action_ = new QAction(tr("Stellate Extrude"), parent_);
  action_->setIcon(QIcon(":/images/extrude_stellate.png"));
  action_->setCheckable(true);
  action_->setStatusTip(tr("Stellate Extrude"));
  action_->setToolTip(tr("Stellate Extrude"));
  connect(action_, SIGNAL(triggered()), this, SLOT(Activate()));
}

void StellateExtrudeTool::Activate() {
  ((MainWindow*) parent_)->setToolOptions(widget_);
  ((MainWindow*) parent_)->setMode(MainWindow::StellateFace);
  ((MainWindow*) parent_)->setExtrusionMode(MainWindow::StellateExtrude);
//  ((MainWindow*) parent_)->setSpinBoxes(dooSabinLengthSpinBox,
//      dooSabinTwistSpinBox, dooSabinScaleSpinBox, dooSabinSegmentsSpinBox);

}

void StellateExtrudeTool::RetranslateUi() {
  action_->setStatusTip(tr("Stellate Extrude"));
  action_->setToolTip(tr("Stellate Extrude"));
  action_->setText(tr("Stellate Extrude"));
  widget_->setWindowTitle(tr("Stellate Extrude"));
}

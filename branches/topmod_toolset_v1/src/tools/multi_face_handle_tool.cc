/*
 * multi_face_handle_tool.cc
 *
 *  Created on: Sep 12, 2008
 *      Author: david.morris
 */

#include "multi_face_handle_tool.h"
#include "../MainWindow.h"
class MainWindow;

MultiFaceHandleTool::MultiFaceHandleTool(QWidget *parent) {
  parent_ = parent;
  layout_ = new QGridLayout;
  layout_->setVerticalSpacing(1);
  layout_->setHorizontalSpacing(1);

  algorithm_group_ = new QGroupBox(tr("Use Convex Hull\nAlgorithm"));
  algorithm_group_->setCheckable(true);
  algorithm_group_->setChecked(false);

  algorithm_layout_ = new QGridLayout;
  algorithm_layout_->setVerticalSpacing(2);
  algorithm_layout_->setHorizontalSpacing(2);
  algorithm_group_->setAlignment(Qt::AlignLeft);
  connect(algorithm_group_, SIGNAL(toggled(bool)), this, SLOT(changeMultiFaceAlgorithm(bool)));

  //scaling
  scale_label_ = new QLabel(this);
  scale_spin_ = createDoubleSpinBox(algorithm_layout_, scale_label_, tr(
      "Thickness:"), 0.0, 5.0, 0.01, 1.0, 2, 0, 0);
  connect(scale_spin_, SIGNAL(valueChanged(double)), ((MainWindow*) mParent), SLOT(changeMultiFaceHandleScaleFactor(double)));

  //extrude distance
  extrude_distance_label_ = new QLabel(this);
  extrude_distance_spin_ = createDoubleSpinBox(algorithm_layout_,
      extrude_distance_label_, tr("Extrude Dist.\nFactor:"), -2.0, 2.0, 0.1,
      0.5, 3, 1, 0);
  connect(extrude_distance_spin_, SIGNAL(valueChanged(double)), ((MainWindow*) mParent), SLOT(changeMultiFaceHandleExtrudeDist(double)));

  //use max. offsets
  max_offsets_check_ = new QCheckBox(tr("Use max offsets"), this);
  connect(max_offsets_check_, SIGNAL(stateChanged(int)), this, SLOT(toggleMultiFaceHandleUseMaxOffsetFlag(int)));
  algorithm_layout_->addWidget(max_offsets_check_, 2, 0, 1, 2);
  algorithm_group_->setLayout(algorithm_layout_);

  //add the groupbox to the multiface layout
  layout_->addWidget(algorithm_group_, 0, 0);
  create_button_ = new QPushButton(tr("Connect Selected Faces"), this);
  connect(create_button_, SIGNAL(clicked()), ((MainWindow*) mParent), SLOT(createMultiFaceHandle()));
  layout_->addWidget(create_button_, 1, 0, 1, 2);

  layout_->setRowStretch(3, 1);
  layout_->setColumnStretch(2, 1);
  widget_ = new QWidget;
  widget_->setWindowTitle(tr("Multi-Face Handle"));
  widget_->setLayout(layout_);

  action_ = new QAction(tr("Multi-Face Handle"), parent_);
  action_->setIcon(QIcon(":/images/highgenus_multifacehandle.png"));
  action_->setCheckable(true);
  action_->setStatusTip(tr("Multi-Face Handle"));
  action_->setToolTip(tr("Multi-Face Handle"));
  connect(action_, SIGNAL(triggered()), this, SLOT(Activate()));
}

void MultiFaceHandleTool::toggleMultiFaceHandleUseMaxOffsetFlag(int state) {

  ((MainWindow*) mParent)->toggleMultiFaceHandleUseMaxOffsetFlag(state);

  if (state) {
    extrude_distance_spin_->setEnabled(false);
    extrude_distance_label_->setEnabled(false);
  } else {
    extrude_distance_label_->setEnabled(true);
    extrude_distance_spin_->setEnabled(true);
  }
}

void MultiFaceHandleTool::changeMultiFaceAlgorithm(bool on) {

  if (!on) {
    ((MainWindow*) mParent)->mfh_use_closest_edge_algo();
    //set all three widgets to be disabled
    scale_label_->setEnabled(false);
    scale_spin_->setEnabled(false);
    extrude_distance_label_->setEnabled(false);
    extrude_distance_spin_->setEnabled(false);
    max_offsets_check_->setEnabled(false);
  } else {
    ((MainWindow*) mParent)->mfh_use_convex_hull_algo();
    //set widgets to be enabled...
    scale_label_->setEnabled(true);
    scale_spin_->setEnabled(true);
    max_offsets_check_->setEnabled(true);
    //check if the checkbox is checked first or not, then enable widgets accordingly
    if (max_offsets_check_->checkState() == Qt::Checked) {
      extrude_distance_label_->setEnabled(true);
      extrude_distance_spin_->setEnabled(true);
    }
  }
}

void MultiFaceHandleTool::Activate() {
  ((MainWindow*) parent_)->setToolOptions(widget_);
  ((MainWindow*) parent_)->setMode(MainWindow::MultiSelectFace);
}

void MultiFaceHandleTool::RetranslateUi() {

}

/*
 * wireframe_modeling_tool.cc
 *
 *  Created on: Sep 12, 2008
 *      Author: david.morris
 */

#include "wireframe_modeling_tool.h"
#include "../MainWindow.h"
class MainWindow;

WireframeModelingTool::WireframeModelingTool(QWidget *parent) {
  parent_ = parent;
  layout_ = new QGridLayout;
  layout_->setVerticalSpacing(1);
  layout_->setHorizontalSpacing(1);
  //thickness
  thickness_label_ = new QLabel(this);
  thickness_spin_ = createDoubleSpinBox(layout_, thickness_label_, tr(
      "Thickness:"), 0.0, 1.0, 0.01, 0.25, 3, 0, 0);
  connect(thickness_spin_, SIGNAL(valueChanged(double)), ((MainWindow*) parent_), SLOT(changeWireframeThickness(double)));
  width_label_ = new QLabel(this);
  width_spin_ = createDoubleSpinBox(layout_, width_label_, tr("Width:"), 0.0,
      1.0, 0.01, 0.25, 3, 1, 0);
  connect(width_label_, SIGNAL(valueChanged(double)), ((MainWindow*) parent_), SLOT(changeWireframeWidth(double)));
  //set disabled by default
  width_label_->setEnabled(false);
  width_spin_->setEnabled(false);

  //square/rectangular cross section checkbox
  square_cross_section_check_ = new QCheckBox(tr("Square Cross Section"), this);
  square_cross_section_check_->setChecked(Qt::Checked);
  connect(square_cross_section_check_, SIGNAL(stateChanged(int)), this, SLOT(toggleSquareCrossSection(int)));
  layout_->addWidget(square_cross_section_check_, 2, 0, 1, 2);

  //split 2 valence checkbox
  split_2_valence_vertices_check_ = new QCheckBox(tr("Split Valence-2 Vertices"), this);
  split_2_valence_vertices_check_->setChecked(Qt::Checked);
  connect(split_2_valence_vertices_check_, SIGNAL(stateChanged(int)), ((MainWindow*) parent_), SLOT(toggleWireframeSplit(int)));
  layout_->addWidget(split_2_valence_vertices_check_, 3, 0, 1, 2);

  //create wireframe button
  wireframeModeling2CreateButton
      = new QPushButton(tr("Create Wireframe"), this);
  connect(wireframeModeling2CreateButton, SIGNAL(clicked()), this, SLOT(createWireframe()));
  layout_->addWidget(wireframeModeling2CreateButton, 4, 0, 1, 2);

  layout_->setRowStretch(5, 1);
  layout_->setColumnStretch(2, 1);
  widget_ = new QWidget;
  widget_->setWindowTitle(tr("Wireframe Modeling"));
  widget_->setLayout(layout_);

  action_ = new QAction(tr("Wireframe Modeling"), parent_);
  action_->setIcon(QIcon(":/images/highgenus_wireframe.png"));
  action_->setCheckable(true);
  action_->setStatusTip(tr("Wireframe Modeling"));
  action_->setToolTip(tr("Wireframe Modeling"));
  connect(action_, SIGNAL(triggered()), this, SLOT(Activate()));
}

void WireframeModelingTool::toggleSquareCrossSection(int state){
  if ((bool)state){
    width_label_->setEnabled(false);
    width_spin_->setEnabled(false);
  } else {
    width_label_->setEnabled(true);
    width_spin_->setEnabled(true);
  }
}

void createWireframe(){
  if (square_cross_section_check_->isChecked()){
    ((MainWindow*) parent_)->makeWireframe();
  } else {
    ((MainWindow*) parent_)->makeWireframe2();
  }
}
void WireframeModelingTool::Activate() {
  ((MainWindow*) parent_)->setToolOptions(widget_);
  ((MainWindow*) parent_)->setMode(MainWindow::NormalMode);
}

void WireframeModelingTool::RetranslateUi() {

}

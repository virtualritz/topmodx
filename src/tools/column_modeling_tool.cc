/*
 * column_modeling_tool.cc
 *
 *  Created on: Sep 12, 2008
 *      Author: david.morris
 */

#include "column_modeling_tool.h"
#include "../MainWindow.h"
class MainWindow;

ColumnModelingTool::ColumnModelingTool(QWidget *parent) {
  parent_ = parent;
  layout_ = new QGridLayout;
  layout_->setVerticalSpacing(1);
  layout_->setHorizontalSpacing(1);
  //thickness
  thickness_label_ = new QLabel(this);
  thickness_spin_ = createDoubleSpinBox(layout_, thickness_label_, tr(
      "Thickness:"), 0.0, 1.0, 0.01, 0.25, 3, 0, 0);
  connect(thickness_spin_, SIGNAL(valueChanged(double)), ((MainWindow*) mParent), SLOT(changeColumnThickness(double)));
  //number of segments
  segments_label_ = new QLabel(this);
  segments_spin_ = createDoubleSpinBox(layout_, segments_label_, tr(
      "# Segments:"), 4.0, 100, 1, 4, 0, 1, 0);
  connect(segments_spin_, SIGNAL(valueChanged(double)), ((MainWindow*) mParent), SLOT(changeColumnSegments(double)));
  //create column button
  create_button_ = new QPushButton(tr("Create Columns"), this);
  connect(create_button_, SIGNAL(clicked()), ((MainWindow*) mParent), SLOT(makeWireframeWithColumns()));
  layout_->addWidget(create_button_, 2, 0, 1, 2);

  layout_->setRowStretch(3, 1);
  layout_->setColumnStretch(2, 1);
  widget_ = new QWidget;
  widget_->setWindowTitle(tr("Column Modeling"));
  widget_->setLayout(layout_);

  action_ = new QAction(tr("Column Modeling"), parent_);
  action_->setIcon(QIcon(":/images/highgenus_column.png"));
  action_->setCheckable(true);
  action_->setStatusTip(tr("Column Modeling"));
  action_->setToolTip(tr("Column Modeling"));
  connect(action_, SIGNAL(triggered()), this, SLOT(Activate()));
}

void ColumnModelingTool::Activate() {
  ((MainWindow*) parent_)->setToolOptions(widget_);
  ((MainWindow*) parent_)->setMode(MainWindow::NormalMode);
}

void ColumnModelingTool::RetranslateUi() {

}

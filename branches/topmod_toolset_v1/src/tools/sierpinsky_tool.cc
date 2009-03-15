/*
 * sierpinsky_tool.cc
 *
 *  Created on: Sep 12, 2008
 *      Author: david.morris
 */

#include "sierpinsky_tool.h"
#include "../MainWindow.h"
class MainWindow;

SierpinskyTool::SierpinskyTool(QWidget *parent) {
  parent_ = parent;
  layout_ = new QGridLayout;
  layout_->setVerticalSpacing(1);
  layout_->setHorizontalSpacing(1);
  //create column button
  create_button_ = new QPushButton(tr("Create Sierpinsky\nTetrahedra"), this);
  connect(create_button_, SIGNAL(clicked()), ((MainWindow*) mParent), SLOT(multiConnectMidpoints()));
  layout_->addWidget(create_button_, 0, 0);

  layout_->setRowStretch(1, 1);
  layout_->setColumnStretch(1, 1);
  widget_ = new QWidget;
  widget_->setWindowTitle(tr("Sierpinsky Tetrahedra"));
  widget_->setLayout(layout_);

  action_ = new QAction(tr("Sierpinsky Tetrahedra"), parent_);
  action_->setIcon(QIcon(":/images/highgenus_sierpinsky.png"));
  action_->setCheckable(true);
  action_->setStatusTip(tr("Sierpinsky Tetrahedra"));
  action_->setToolTip(tr("Sierpinsky Tetrahedra"));
  connect(action_, SIGNAL(triggered()), this, SLOT(Activate()));
}

void SierpinskyTool::Activate() {
  ((MainWindow*) parent_)->setToolOptions(widget_);
  ((MainWindow*) parent_)->setMode(MainWindow::NormalMode);
}

void SierpinskyTool::RetranslateUi() {

}

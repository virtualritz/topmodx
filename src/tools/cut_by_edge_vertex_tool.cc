/*
 * cut_by_edge_vertex_tool.cc
 *
 *  Created on: Sep 15, 2008
 *      Author: david.morris
 */

#include "cut_by_edge_vertex_tool.h"
#include "../MainWindow.h"
class MainWindow;

CutByEdgeVertexTool::CutByEdgeVertexTool(QWidget *parent) {
  parent_ = parent;
  layout_ = new QGridLayout;
  layout_->setVerticalSpacing(1);
  layout_->setHorizontalSpacing(1);

//  QLabel *no_options_label_ =
//      new QLabel(tr("No Options for this tool."));
//  layout_->addWidget(no_options_label_, 0, 0);

  // mCutbyEdgeVertexLayout = new QBoxLayout(QBoxLayout::LeftToRight);
    // mCutbyEdgeVertexLayout->setMargin(0);
    //
    // QLabel *cutbyEdgeVertexOffsetELabel = new QLabel(tr("Offset (Edge):"));
    // cutbyEdgeVertexOffsetESpinBox = new QDoubleSpinBox;
    // cutbyEdgeVertexOffsetESpinBox->setRange(0, 1);
    // cutbyEdgeVertexOffsetESpinBox->setSingleStep(0.01);
    // cutbyEdgeVertexOffsetESpinBox->setValue(0.25);
    // cutbyEdgeVertexOffsetESpinBox->setMaximumSize(65,25);
    // connect(cutbyEdgeVertexOffsetESpinBox, SIGNAL(valueChanged(double)),
    //           this, SLOT(changeCutOffsetE(double)));
    //
    // mCutbyEdgeVertexLayout->addWidget(cutbyEdgeVertexOffsetELabel);
    //   mCutbyEdgeVertexLayout->addWidget(cutbyEdgeVertexOffsetESpinBox);
    //
    // QLabel *cutbyEdgeVertexOffsetVLabel = new QLabel(tr("Offset (Vertex):"));
    // cutbyEdgeVertexOffsetVSpinBox = new QDoubleSpinBox;
    // cutbyEdgeVertexOffsetVSpinBox->setRange(0, 1);
    // cutbyEdgeVertexOffsetVSpinBox->setSingleStep(0.01);
    // cutbyEdgeVertexOffsetVSpinBox->setValue(0.25);
    // cutbyEdgeVertexOffsetVSpinBox->setMaximumSize(65,25);
    // connect(cutbyEdgeVertexOffsetVSpinBox, SIGNAL(valueChanged(double)),
    //           this, SLOT(changeCutOffsetV(double)));
    //
    // mCutbyEdgeVertexLayout->addWidget(cutbyEdgeVertexOffsetVLabel);
    //   mCutbyEdgeVertexLayout->addWidget(cutbyEdgeVertexOffsetVSpinBox);
    //
    // QLabel *cutbyEdgeVertexTiltPlane1Label = new QLabel(tr("Tilt plane:"));
    // cutbyEdgeVertexTiltPlane1SpinBox = new QDoubleSpinBox;
    // cutbyEdgeVertexTiltPlane1SpinBox->setRange(-1, 1);
    // cutbyEdgeVertexTiltPlane1SpinBox->setSingleStep(.01);
    // cutbyEdgeVertexTiltPlane1SpinBox->setValue(0);
    // cutbyEdgeVertexTiltPlane1SpinBox->setMaximumSize(65,25);
    // connect(cutbyEdgeVertexTiltPlane1SpinBox, SIGNAL(valueChanged(double)),
    //           this, SLOT(changeTiltPlane1(double)));
    //
    // mCutbyEdgeVertexLayout->addWidget(cutbyEdgeVertexTiltPlane1Label);
    //   mCutbyEdgeVertexLayout->addWidget(cutbyEdgeVertexTiltPlane1SpinBox);
    //
    // QLabel *cutbyEdgeVertexTiltPlane2Label = new QLabel(tr("Tilt plane:"));
    // cutbyEdgeVertexTiltPlane2SpinBox = new QDoubleSpinBox;
    // cutbyEdgeVertexTiltPlane2SpinBox->setRange(-1, 1);
    // cutbyEdgeVertexTiltPlane2SpinBox->setSingleStep(0.01);
    // cutbyEdgeVertexTiltPlane2SpinBox->setValue(0);
    // cutbyEdgeVertexTiltPlane2SpinBox->setMaximumSize(65,25);
    // connect(cutbyEdgeVertexTiltPlane2SpinBox, SIGNAL(valueChanged(double)),
    //           this, SLOT(changeTiltPlane2(double)));
    //
    // mCutbyEdgeVertexLayout->addWidget(cutbyEdgeVertexTiltPlane2Label);
    //   mCutbyEdgeVertexLayout->addWidget(cutbyEdgeVertexTiltPlane2SpinBox);
    //
    // cutbyEdgeVertexGlobalCheckBox = new QCheckBox(tr("global cut"),this);
    // cutbyEdgeVertexGlobalCheckBox->setChecked(Qt::Unchecked);
    // connect(cutbyEdgeVertexGlobalCheckBox, SIGNAL(stateChanged(int)),
    //           this, SLOT(toggleGlobalCut(int)));
    //
    // mCutbyEdgeVertexLayout->addWidget(cutbyEdgeVertexGlobalCheckBox);
    //
    // cutbyEdgeVertexCutSelectedCheckBox = new QCheckBox(tr("cut selected edges"),this);
    // cutbyEdgeVertexCutSelectedCheckBox->setChecked(Qt::Checked);
    // connect(cutbyEdgeVertexCutSelectedCheckBox, SIGNAL(stateChanged(int)),
    //           this, SLOT(toggleSelectedCut(int)));
    //
    // mCutbyEdgeVertexLayout->addWidget(cutbyEdgeVertexCutSelectedCheckBox);
    //
    // QPushButton *performCuttingButton = new QPushButton(tr("Perform Cutting"), this);
    // connect(performCuttingButton, SIGNAL(clicked()),
    //           ((MainWindow*)mParent), SLOT(performCutting()));
    //
    // mCutbyEdgeVertexLayout->addWidget(performCuttingButton);
    // mCutbyEdgeVertexLayout->addStretch(1);
    // mCutbyEdgeVertexWidget->setWindowTitle("Cut by Edge/Vertex");
    // mCutbyEdgeVertexWidget->setLayout(mCutbyEdgeVertexLayout);

  layout_->setRowStretch(1, 1);
  layout_->setColumnStretch(1, 1);
  widget_ = new QWidget;
  widget_->setWindowTitle(tr("Cut By Edge and Vertex"));
  widget_->setLayout(layout_);

  action_ = new QAction(tr("Cut By Edge and Vertex"), parent_);
  action_->setIcon(QIcon(":/images/splice_corners.png"));
  action_->setCheckable(true);
  action_->setStatusTip(tr("Cut By Edge and Vertex"));
  action_->setToolTip(tr("Cut By Edge and Vertex"));
  connect(action_, SIGNAL(triggered()), this, SLOT(Activate()));
}

void CutByEdgeVertexTool::Activate() {
  ((MainWindow*) parent_)->setToolOptions(widget_);
  ((MainWindow*) parent_)->setMode(MainWindow::CutEdgeandVertex);
}

void CutByEdgeVertexTool::RetranslateUi(){

}

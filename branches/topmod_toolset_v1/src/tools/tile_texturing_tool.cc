/*
 * tile_texturing_tool.cc
 *
 *  Created on: Sep 15, 2008
 *      Author: david.morris
 */

#include "tile_texturing_tool.h"
#include "../MainWindow.h"
class MainWindow;

TileTexturingTool::TileTexturingTool(QWidget *parent) {
  parent_ = parent;
  layout_ = new QGridLayout;
  layout_->setVerticalSpacing(1);
  layout_->setHorizontalSpacing(1);

  QLabel *num_tiles_label = new QLabel(this);
  num_tiles_spin_ = createDoubleSpinBox(layout_, num_tiles_label,
      tr("Tiling Number"), 2, 8, 1, 2, 0, 0, 0);
  connect(num_tiles_spin_, SIGNAL(valueChanged(double)), ((MainWindow*) parent_), SLOT(changeTileTexNum(double)));

  assign_button_ = new QPushButton(tr("Assign Texture\nCoordinates"), this);
  connect(assign_button_, SIGNAL(clicked()), ((MainWindow*) parent_), SLOT(assignTileTexCoords()));
  layout_->addWidget(assign_button_, 1, 0, 1, 2);

  layout_->setRowStretch(2, 1);
  layout_->setColumnStretch(1, 1);
  widget_ = new QWidget;
  widget_->setWindowTitle(tr("Tile Texturing"));
  widget_->setLayout(layout_);

  action_ = new QAction(tr("Tile Texturing"), parent_);
  action_->setIcon(QIcon(":/images/mode_texturing.png"));
  action_->setCheckable(true);
  action_->setStatusTip(tr("Tile Texturing"));
  action_->setToolTip(tr("Tile Texturing"));
  connect(action_, SIGNAL(triggered()), this, SLOT(Activate()));
}

void TileTexturingTool::Activate() {
  ((MainWindow*) parent_)->setToolOptions(widget_);
}

void TileTexturingTool::RetranslateUi() {

}

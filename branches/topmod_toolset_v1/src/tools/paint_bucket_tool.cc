/*
 * paint_bucket_tool.cc
 *
 *  Created on: Sep 15, 2008
 *      Author: david.morris
 */

#include "paint_bucket_tool.h"
#include "../MainWindow.h"
class MainWindow;

PaintBucketTool::PaintBucketTool(QWidget *parent) {
  parent_ = parent;
  layout_ = new QGridLayout;
  layout_->setVerticalSpacing(1);
  layout_->setHorizontalSpacing(1);

  color_picker_style_ = new QPlastiqueStyle;
  //viewport background color
  QLabel *paint_bucket_label = new QLabel;
  paint_bucket_color_button_ = addColorPreference(paint_bucket_label, tr(
      "Paint Bucket\nColor:"), paint_bucket_color_, layout_,
      color_picker_style_, 0, 0);
  connect(paint_bucket_color_button_, SIGNAL(clicked()), this, SLOT(setPaintBucketColor()));

  //paint selcted faces
  paint_select_faces_button_
      = new QPushButton(tr("Paint Selected Faces"), this);
  connect(paint_select_faces_button_, SIGNAL(clicked()), ((MainWindow*) parent_), SLOT(paintSelectedFaces()));
  layout_->addWidget(paint_select_faces_button_, 1, 0);

  //paint selcted faces
  reset_materials_button_ = new QPushButton(tr("Reset Materials"), this);
  connect(reset_materials_button_, SIGNAL(clicked()), ((MainWindow*) parent_), SLOT(clearMaterials()));
  layout_->addWidget(reset_materials_button_, 2, 0);

  layout_->setRowStretch(3, 1);
  layout_->setColumnStretch(2, 1);
  widget_ = new QWidget;
  widget_->setWindowTitle(tr("Paint Bucket"));
  widget_->setLayout(layout_);

  action_ = new QAction(tr("Paint Bucket"), parent_);
  action_->setIcon(QIcon(":/images/color-fill.png"));
  action_->setCheckable(true);
  action_->setStatusTip(tr("Paint Bucket"));
  action_->setToolTip(tr("Paint Bucket"));
  connect(action_, SIGNAL(triggered()), this, SLOT(Activate()));
}

QPushButton* PaintBucketTool::addColorPreference(QLabel *label, QString text,
                                                 QColor color,
                                                 QGridLayout *layout,
                                                 QStyle *style, int row,
                                                 int col) {
  label->setText(text);
  QPushButton *button = new QPushButton(this);
  button->setMaximumSize(QSize(100, 25));
  button->setAutoFillBackground(true);
  button->setStyle(style);
  QPalette p = button->palette();
  p.setColor(button->backgroundRole(), color);
  button->setPalette(p);
  layout->addWidget(label, row, col);
  layout->addWidget(button, row, col + 1);
  return button;
}

void PaintBucketTool::setPaintBucketColor() {
  paint_bucket_color_.setRgba(QColorDialog::getRgba(paint_bucket_color_.rgba()));
  if (paint_bucket_color_.isValid()) {
    ((MainWindow*) mParent)->setPaintBucketColor(paint_bucket_color_);
    setButtonColor(paint_bucket_color_, paint_bucket_color_button_);
  }
}
void PaintBucketTool::setPaintBucketColor(QColor c) {
  mPaintBucketColor = c;
  setButtonColor(paint_bucket_color_, paint_bucket_color_button_);
}

void PaintBucketTool::setButtonColor(QColor color, QPushButton *button) {
  p = button->palette();
  p.setColor(QPalette::Button, color);
  button->setPalette(p);
}

void PaintBucketTool::Activate() {
  ((MainWindow*) parent_)->setToolOptions(widget_);
  ((MainWindow*) parent_)->setMode(MainWindow::PaintFace);
}

void PaintBucketTool::RetranslateUi() {
  action_->setStatusTip(tr("Paint Bucket"));
  action_->setToolTip(tr("Paint Bucket"));
  action_->setText(tr("Paint Bucket"));
  widget_->setWindowTitle(tr("Paint Bucket"));
}

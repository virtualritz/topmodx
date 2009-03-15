/*
 * paint_bucket_tool.h
 *
 *  Created on: Sep 15, 2008
 *      Author: david.morris
 */

#ifndef PAINT_BUCKET_TOOL_H_
#define PAINT_BUCKET_TOOL_H_

#include <QtGui>
#include <QWidget>

#include "topmod_tool.h"

class PaintBucketTool : public TopModTool {
Q_OBJECT
  // does it have to be a Q_OBJECT?

public:
  PaintBucketTool(QWidget *parent);
  void RetranslateUi();

public slots:
  void Activate();

private:
  QPushButton *paint_bucket_color_button_;
  QPushButton *paint_select_faces_button_;
  QPushButton *reset_materials_button_;
  QColor *paint_bucket_color_,paint_bucket_color_default_;
  QStyle *color_picker_style_;
  QPalette p;

};

#endif /* PAINT_BUCKET_TOOL_H_ */

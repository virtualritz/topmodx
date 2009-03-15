/*
 * column_modeling_tool.h
 *
 *  Created on: Sep 12, 2008
 *      Author: david.morris
 */

#ifndef COLUMN_MODELING_TOOL_H_
#define COLUMN_MODELING_TOOL_H_

#include <QtGui>
#include <QWidget>

#include "topmod_tool.h"

// Declaration of the class ColumnModelingTool.
class ColumnModelingTool: public TopModTool {
  Q_OBJECT // does it have to be a Q_OBJECT?

public:
  ColumnModelingTool(QWidget *parent);
  void RetranslateUi();

public slots:
  void Activate();

private:
  QLabel *thickness_label_,*segments_label_;
  QDoubleSpinBox *thickness_spin_,*segments_spin_;
  QPushButton *create_button_;
};

#endif /* COLUMN_MODELING_TOOL_H_ */

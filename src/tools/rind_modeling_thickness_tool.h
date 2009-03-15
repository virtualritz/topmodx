/*
 * rind_modeling_thickness_tool.h
 *
 *  Created on: Sep 12, 2008
 *      Author: david.morris
 */

#ifndef RIND_MODELING_THICKNESS_TOOL_H_
#define RIND_MODELING_THICKNESS_TOOL_H_

#include <QtGui>
#include <QWidget>

#include "topmod_tool.h"

class RindModelingThicknessTool: public TopModTool {
  Q_OBJECT // does it have to be a Q_OBJECT?

public:
  RindModelingThicknessTool(QWidget *parent);
  void RetranslateUi();

public slots:
  void Activate();

private:
  QLabel *thickness_label_,scale_label_;
  QDoubleSpinBox *thickness_spin_,*scale_spin_;
  QCheckBox *cleanup_check_;
  QPushButton *create_button_;

};

#endif /* RIND_MODELING_THICKNESS_TOOL_H_ */

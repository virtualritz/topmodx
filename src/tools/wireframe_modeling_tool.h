/*
 * wireframe_modeling_tool.h
 *
 *  Created on: Sep 12, 2008
 *      Author: david.morris
 */

#ifndef WIREFRAME_MODELING_TOOL_H_
#define WIREFRAME_MODELING_TOOL_H_

#include <QtGui>
#include <QWidget>

#include "topmod_tool.h"

class WireframeModelingTool: public TopModTool {
  Q_OBJECT // does it have to be a Q_OBJECT?

public:
  WireframeModelingTool(QWidget *parent);
  void RetranslateUi();

public slots:
  void Activate();
  void toggleSquareCrossSection(int state);

private:
  QLabel *thickness_label_,*width_label_;
  QDoubleSpinBox *thickness_spin_, *width_spin_;
  QCheckBox *split_check_, *square_cross_section_check_;
  QPushButton *create_button_;

};

#endif /* WIREFRAME_MODELING_TOOL_H_ */

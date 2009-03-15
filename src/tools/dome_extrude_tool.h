/*
 * dome_extrude_tool.h
 *
 *  Created on: Sep 15, 2008
 *      Author: david.morris
 */

#ifndef DOME_EXTRUDE_TOOL_H_
#define DOME_EXTRUDE_TOOL_H_

#include <QtGui>
#include <QWidget>

#include "topmod_tool.h"

class DomeExtrudeTool: public TopModTool {
Q_OBJECT
  // does it have to be a Q_OBJECT?

public:
  DomeExtrudeTool(QWidget *parent);
  void RetranslateUi();

protected:
  QDoubleSpinBox *height_spin_, *rotation_spin_, *scale_spin_;
  QLabel *height_label_, *rotation_label_, *scale_label_;
  QPushButton *perform_extrusion_button_;

public slots:
  void Activate();

};

#endif /* DOME_EXTRUDE_TOOL_H_ */

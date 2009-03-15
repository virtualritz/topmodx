/*
 * stellate_extrude_tool.h
 *
 *  Created on: Sep 15, 2008
 *      Author: david.morris
 */

#ifndef STELLATE_EXTRUDE_TOOL_H_
#define STELLATE_EXTRUDE_TOOL_H_

#include <QtGui>
#include <QWidget>

#include "topmod_tool.h"

class StellateExtrudeTool: public TopModTool {
Q_OBJECT
  // does it have to be a Q_OBJECT?

public:
  StellateExtrudeTool(QWidget *parent);
  void RetranslateUi();

protected:
  QDoubleSpinBox *length_spin_;
  QLabel *length_label_;
  QPushButton *perform_extrusion_button_;

public slots:
  void Activate();

};

#endif /* STELLATE_EXTRUDE_TOOL_H_ */

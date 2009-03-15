/*
 * icosahedral_extrude_tool.h
 *
 *  Created on: Sep 15, 2008
 *      Author: david.morris
 */

#ifndef ICOSAHEDRAL_EXTRUDE_TOOL_H_
#define ICOSAHEDRAL_EXTRUDE_TOOL_H_

#include <QtGui>
#include <QWidget>

#include "topmod_tool.h"

class IcosahedralExtrudeTool: public TopModTool {
Q_OBJECT
  // does it have to be a Q_OBJECT?

public:
  IcosahedralExtrudeTool(QWidget *parent);
  void RetranslateUi();

protected:
  QDoubleSpinBox *length1_spin_, *length2_spin_,
  *length3_spin_, *segments_spin_, *angle_spin_;
  QLabel *length1_label_, *length2_label_,
  *length3_label_, *segments_label_, *angle_label_;
  QPushButton *perform_extrusion_button_;

public slots:
  void Activate();

};

#endif /* ICOSAHEDRAL_EXTRUDE_TOOL_H_ */

/*
 * dodecahedral_extrude_tool.h
 *
 *  Created on: Sep 15, 2008
 *      Author: david.morris
 */

#ifndef DODECAHEDRAL_EXTRUDE_TOOL_H_
#define DODECAHEDRAL_EXTRUDE_TOOL_H_

#include <QtGui>
#include <QWidget>

#include "topmod_tool.h"

class DodecahedralExtrudeTool: public TopModTool {
Q_OBJECT
  // does it have to be a Q_OBJECT?

public:
  DodecahedralExtrudeTool(QWidget *parent);
  void RetranslateUi();

protected:
  QDoubleSpinBox *length1_spin_, *length2_spin_, *length3_spin_,
    *angle_spin_,*segments_spin_;
  QLabel *length1_label_, *length2_label_, *length3_label_,
    *angle_label_,*segments_label_;
  QCheckBox *hexagonalize_check_;
  QPushButton *perform_extrusion_button_;

public slots:
  void Activate();

};

#endif /* DODECAHEDRAL_EXTRUDE_TOOL_H_ */

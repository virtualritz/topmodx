/*
 * octahedral_extrude_tool.h
 *
 *  Created on: Sep 15, 2008
 *      Author: david.morris
 */

#ifndef OCTAHEDRAL_EXTRUDE_TOOL_H_
#define OCTAHEDRAL_EXTRUDE_TOOL_H_

#include <QtGui>
#include <QWidget>

#include "topmod_tool.h"

class OctahedralExtrudeTool: public TopModTool {
Q_OBJECT
  // does it have to be a Q_OBJECT?

public:
  OctahedralExtrudeTool(QWidget *parent);
  void RetranslateUi();

protected:
  QDoubleSpinBox *length_spin_, *scale_spin_, *segments_spin_, *rotation_spin_;
  QLabel *length_label_, *scale_label_, *segments_label_, *rotation_label_;
  QCheckBox *mesh_flat_edges_check_;
  QPushButton *perform_extrusion_button_;

public slots:
  void Activate();

};

#endif /* OCTAHEDRAL_EXTRUDE_TOOL_H_ */

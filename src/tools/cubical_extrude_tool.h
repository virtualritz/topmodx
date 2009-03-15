/*
 * doo_sabin_extrude_tool.h
 *
 *  Created on: Sep 15, 2008
 *      Author: david.morris
 */

#ifndef CUBICAL_EXTRUDE_TOOL_H_
#define CUBICAL_EXTRUDE_TOOL_H_

#include <QtGui>
#include <QWidget>

#include "topmod_tool.h"

class CubicalExtrudeTool : public TopModTool {
Q_OBJECT
  // does it have to be a Q_OBJECT?

public:
  CubicalExtrudeTool(QWidget *parent);
  void RetranslateUi();

protected:
  QDoubleSpinBox *length_spin_, *scale_spin_,
  *segments_spin_, *rotation_spin_,
  *pinch_spin_,*pinch_center_spin_,*pinch_width_spin_;
  QLabel *length_label_,*rotation_label_,
  *scale_label_,*segments_label_,
  *pinch_label_, *pinch_center_label_, *pinch_width_label_;
  QCheckBox *triangulate_new_faces_check_,*scherk_collins_check_;
  QPushButton *perform_extrusion_button_;

public slots:
  void Activate();
  void toggleCubicalScherkCollins(int state);

};

#endif /* CUBICAL_EXTRUDE_TOOL_H_ */

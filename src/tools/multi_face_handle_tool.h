/*
 * multi_face_handle_tool.h
 *
 *  Created on: Sep 12, 2008
 *      Author: david.morris
 */

#ifndef MULTI_FACE_HANDLE_TOOL_H_
#define MULTI_FACE_HANDLE_TOOL_H_

#include <QtGui>
#include <QWidget>

#include "topmod_tool.h"

class MultiFaceHandleTool: public TopModTool {
  Q_OBJECT // does it have to be a Q_OBJECT?

public:
  MultiFaceHandleTool(QWidget *parent);
  void RetranslateUi();
  void changeMultiFaceAlgorithm(bool on);
  void toggleMultiFaceHandleUseMaxOffsetFlag(int state);

public slots:
  void Activate();

private:
  QGroupBox *algorithm_group_;
  QGridLayout *algorithm_layout_;
  QLabel *scale_label_, *extrude_distance_label_;
  QDoubleSpinBox *scale_spin_,*extrude_distance_spin_;
  QCheckBox *max_offsets_check_;

};

#endif /* MULTI_FACE_HANDLE_TOOL_H_ */

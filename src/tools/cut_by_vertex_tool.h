/*
 * cut_by_vertex_tool.h
 *
 *  Created on: Sep 15, 2008
 *      Author: david.morris
 */

#ifndef CUT_BY_VERTEX_TOOL_H_
#define CUT_BY_VERTEX_TOOL_H_

#include <QtGui>
#include <QWidget>

#include "topmod_tool.h"

class CutByVertexTool: public TopModTool {
  Q_OBJECT // does it have to be a Q_OBJECT?

public:

  CutByVertexTool(QWidget *parent);
  void RetranslateUi();
protected:

  QCheckBox *global_check_;
  QDoubleSpinBox *offset_spin_;
  QPushButton *perform_cutting_button_;

public slots:

  void changeCutOffsetV(double value);
  void toggleGlobalCut(int state);
  void Activate();
};

#endif /* CUT_BY_VERTEX_TOOL_H_ */

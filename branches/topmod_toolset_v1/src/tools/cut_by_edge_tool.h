/*
 * cut_by_edge_tool.h
 *
 *  Created on: Sep 15, 2008
 *      Author: david.morris
 */

#ifndef CUT_BY_EDGE_TOOL_H_
#define CUT_BY_EDGE_TOOL_H_

#include <QtGui>
#include <QWidget>

#include "topmod_tool.h"

class CutByEdgeTool: public TopModTool {
  Q_OBJECT // does it have to be a Q_OBJECT?

public:
  CutByEdgeTool(QWidget *parent);
  void RetranslateUi();

protected:
  QCheckBox *global_check_;
  QDoubleSpinBox *offset_spin_;
  QPushButton *perform_cutting_button_;

public slots:
  void changeCutOffsetE(double value);
  void toggleGlobalCut(int state);
  void Activate();
};

#endif /* CUT_BY_EDGE_TOOL_H_ */

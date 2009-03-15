/*
 * menger_sponge_tool.h
 *
 *  Created on: Sep 12, 2008
 *      Author: david.morris
 */

#ifndef MENGER_SPONGE_TOOL_H_
#define MENGER_SPONGE_TOOL_H_

#include <QtGui>
#include <QWidget>

#include "topmod_tool.h"

class MengerSpongeTool: public TopModTool {
  Q_OBJECT // does it have to be a Q_OBJECT?

public:
  MengerSpongeTool(QWidget *parent);
  void RetranslateUi();

public slots:
  void Activate();

private:
  QLabel *thickness_label_,*threshold_label_;
  QDoubleSpinBox *thickness_spin_, *threshold_spin_;
  QCheckBox *fractional_thickness_check_;
  QPushButton *create_sponge_button_;
};

#endif /* MENGER_SPONGE_TOOL_H_ */

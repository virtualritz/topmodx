/*
 * doo_sabin_extrude_tool.h
 *
 *  Created on: Sep 15, 2008
 *      Author: david.morris
 */

#ifndef DOO_SABIN_EXTRUDE_TOOL_H_
#define DOO_SABIN_EXTRUDE_TOOL_H_

#include <QtGui>
#include <QWidget>

#include "topmod_tool.h"

class DooSabinExtrudeTool: public TopModTool {
Q_OBJECT
  // does it have to be a Q_OBJECT?

public:
  DooSabinExtrudeTool(QWidget *parent);
  void RetranslateUi();

protected:
  QDoubleSpinBox *length_spin_, *scale_spin_, *segments_spin_, *twist_spin_;
  QPushButton *perform_extrusion_button_;

public slots:
  void Activate();

};

#endif /* DOO_SABIN_EXTRUDE_TOOL_H_ */

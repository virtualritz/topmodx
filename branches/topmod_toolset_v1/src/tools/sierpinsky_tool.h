/*
 * sierpinsky_tool.h
 *
 *  Created on: Sep 12, 2008
 *      Author: david.morris
 */

#ifndef SIERPINSKY_TOOL_H_
#define SIERPINSKY_TOOL_H_

#include <QtGui>
#include <QWidget>

#include "topmod_tool.h"

class SierpinskyTool: public TopModTool {
  Q_OBJECT // does it have to be a Q_OBJECT?

public:
  SierpinskyTool(QWidget *parent);
  void RetranslateUi();

public slots:
  void Activate();

private:
  QPushButton *create_button_;
};

#endif /* SIERPINSKY_TOOL_H_ */

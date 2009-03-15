/*
 * convex_hull_tool.h
 *
 *  Created on: Sep 15, 2008
 *      Author: david.morris
 */

#ifndef CONVEX_HULL_TOOL_H_
#define CONVEX_HULL_TOOL_H_

#include <QtGui>
#include <QWidget>

#include "topmod_tool.h"

class ConvexHullTool : public TopModTool {
Q_OBJECT
  // does it have to be a Q_OBJECT?

public:
  ConvexHullTool(QWidget *parent)  ;
void  RetranslateUi();

protected:
  QPushButton *convex_hull_button_,*dual_convex_hull_button_;

public slots:
  void Activate();

};

#endif /* CONVEX_HULL_TOOL_H_ */

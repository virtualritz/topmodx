/*
 * CUBICAL_EXTRUDE_TOOL.h
 *
 *  Created on: Sep 12, 2008
 *      Author: david.morris
 */

#ifndef CUBICAL_EXTRUDE_TOOL_H_
#define CUBICAL_EXTRUDE_TOOL_H_

#include <QtGui>
#include <QWidget>

#include "topmod_tool.h"

// Declaration of the class InsertEdgeTool.
class CubicalExtrudeTool: public TopModTool {
  Q_OBJECT // does it have to be a Q_OBJECT?

public:

  CubicalExtrudeTool(QWidget *parent);
  void RetranslateUi();
protected:

public slots:

  void Activate();
};

#endif /* CUBICAL_EXTRUDE_TOOL_H_ */

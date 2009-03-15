/*
 * truncate_vertex_tool.h
 *
 *  Created on: Sep 15, 2008
 *      Author: david.morris
 */

#ifndef TRUNCATE_VERTEX_TOOL_H_
#define TRUNCATE_VERTEX_TOOL_H_

#include <QtGui>
#include <QWidget>

#include "topmod_tool.h"

class TruncateVertexTool: public TopModTool {
  Q_OBJECT // does it have to be a Q_OBJECT?

public:
  TruncateVertexTool(QWidget *parent);
  void RetranslateUi();

protected:

public slots:
  void Activate();

};

#endif /* TRUNCATE_VERTEX_TOOL_H_ */

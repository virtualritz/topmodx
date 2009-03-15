/*
 * cut_by_edge_vertex_tool.h
 *
 *  Created on: Sep 15, 2008
 *      Author: david.morris
 */

#ifndef CUT_BY_EDGE_VERTEX_TOOL_H_
#define CUT_BY_EDGE_VERTEX_TOOL_H_

#include <QtGui>
#include <QWidget>

#include "topmod_tool.h"

class CutByEdgeVertexTool: public TopModTool {
  Q_OBJECT // does it have to be a Q_OBJECT?

public:

  CutByEdgeVertexTool(QWidget *parent);
  void RetranslateUi();
protected:

public slots:

  void Activate();
};

#endif /* CUT_BY_EDGE_VERTEX_TOOL_H_ */

/*
 * tile_texturing_tool.h
 *
 *  Created on: Sep 15, 2008
 *      Author: david.morris
 */

#ifndef TILE_TEXTURING_TOOL_H_
#define TILE_TEXTURING_TOOL_H_

#include <QtGui>
#include <QWidget>

#include "topmod_tool.h"

class TileTexturingTool: public TopModTool {
Q_OBJECT
  // does it have to be a Q_OBJECT?

public:
  TileTexturingTool(QWidget *parent)  ;
void  RetranslateUi();

protected:
  QDoubleSpinBox *num_tiles_spin_;
  QPushButton *assign_button_;

public slots:
  void Activate();

};

#endif /* TILE_TEXTURING_TOOL_H_ */

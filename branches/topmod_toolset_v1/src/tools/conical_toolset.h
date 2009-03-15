/*!
 \file conical_toolset.h
 \brief Definition of the ConicalToolset class

 \see ConicalToolset
 */

#ifndef CONICALTOOLSET_H
#define CONICALTOOLSET_H

#include <QWidget>

#include <QGridLayout>
#include <QStackedWidget>
#include <QComboBox>

#include "../MainWindow.h"
#include "cut_by_edge_tool.h"
#include "cut_by_vertex_tool.h"
#include "cut_by_edge_vertex_tool.h"
#include "cut_by_face_tool.h"
#include "truncate_edge_tool.h"
#include "truncate_vertex_tool.h"
#include "convex_hull_tool.h"

class MainWindow;
class CutByEdgeTool;
class CutByVertexTool;
class CutByEdgeVertexTool;
class CutByFaceTool;
class TruncateEdgeTool;
class TruncateVertexTool;
class ConvexHullTool;

class ConicalToolset : public QWidget {

public:
  ConicalToolset(QWidget *parent, QShortcutManager *shortcut_manager,
                 QWidget *action_list, QActionGroup *action_group,
                 QStackedWidget *stacked_widget);
  void retranslateUi();

  QToolBar *toolbar_;
  QMenu *menu_;
  QAction *show_toolbar_action_; //QAction to show/hide the toolbar

protected:

public slots:

private:
  QWidget *parent_;
  CutByEdgeTool *cut_by_edge_tool_;
  CutByVertexTool *cut_by_vertex_tool_;
  CutByEdgeVertexTool *cut_by_edge_vertex_tool_;
  CutByFaceTool *cut_by_face_tool_;
  TruncateEdgeTool *truncate_edge_tool_;
  TruncateVertexTool *truncate_vertex_tool_;
  ConvexHullTool *convex_hull_tool_;

};

#endif

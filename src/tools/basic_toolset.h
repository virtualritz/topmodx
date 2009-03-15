/*!
 \file basic_toolset.h
 \brief Definition of the BasicToolset class

 \see BasicToolset
 */

#ifndef BASICTOOLSET_H
#define BASICTOOLSET_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>

#include "../MainWindow.h"
#include "insert_edge_tool.h"
#include "delete_edge_tool.h"
#include "collapse_edge_tool.h"
#include "connect_edges_tool.h"
#include "subdivide_edge_tool.h"
#include "splice_corners_tool.h"
#include "dup_component_tool.h"
#include "geometric_tool.h"

class MainWindow;
class InsertEdgeTool;
class DeleteEdgeTool;
class CollapseEdgeTool;
class ConnectEdgesTool;
class SubdivideEdgeTool;
class SpliceCornersTool;
class DupComponentTool;
class GeometricTool;

class QPushButton;
class QCheckBox;
class QLabel;

class BasicToolset : public QWidget {

public:
  BasicToolset(QWidget *parent, QShortcutManager *shortcut_manager,
               QWidget *action_list, QActionGroup *action_group,
               QStackedWidget *stacked_widget);
  void retranslateUi();

  QToolBar *toolbar_; //QToolBar to store the icon/button of each tool in this toolset
  QMenu *menu_; //QMenu to store the QActions of each tool in this toolset
  QAction *show_toolbar_action_; //QAction to show/hide the toolbar

protected:

private:

  QWidget *parent_;
  GeometricTool *geometric_tool_;
  DupComponentTool *dup_component_tool_;
  InsertEdgeTool *insert_edge_tool_;
  DeleteEdgeTool *delete_edge_tool_;
  CollapseEdgeTool *collapse_edge_tool_;
  ConnectEdgesTool *connect_edges_tool_;
  SubdivideEdgeTool *subdivide_edge_tool_;
  SpliceCornersTool *splice_corners_tool_;
};

#endif

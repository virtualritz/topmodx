/*!
 \ingroup gui
 @{

 \class ConicalToolset
 \brief Conical Operations

 \note

 \see ConicalToolset
 */

#include <QtGui>

#include "conical_toolset.h"

ConicalToolset::ConicalToolset(QWidget *parent,
                               QShortcutManager *shortcut_manager,
                               QWidget *action_list,
                               QActionGroup *action_group,
                               QStackedWidget *stacked_widget) :
  QWidget(parent) {
  setParent(0);
  parent_ = parent;

  //add the tools to the toolset
  cut_by_edge_tool_ = new InsertEdgeTool(parent);
  cut_by_vertex_tool_ = new DeleteEdgeTool(parent);
  cut_by_edge_vertex_tool_ = new CollapseEdgeTool(parent);
  cut_by_face_tool_ = new SubdivideEdgeTool(parent);
  truncate_edge_tool_ = new ConnectEdgesTool(parent);
  truncate_vertex_tool_ = new SpliceCornersTool(parent);
  convex_hull_tool_ = GeometricTool::GetInstance(parent);

  //setup the toolbar
  toolbar_ = new QToolBar(tr("Conical Toolset"), this);
  toolbar_->setFloatable(true);
  toolbar_->setIconSize(QSize(32, 32));

  //add each action to the toolbar
  toolbar_->addAction(cut_by_edge_tool_->action_);
  toolbar_->addAction(cut_by_vertex_tool_->action_);
  toolbar_->addAction(cut_by_edge_vertex_tool_->action_);
  toolbar_->addAction(cut_by_face_tool_->action_);
  toolbar_->addAction(truncate_edge_tool_->action_);
  toolbar_->addAction(truncate_vertex_tool_->action_);
  toolbar_->addAction(convex_hull_tool_->action_);

  ((MainWindow*) parent_)->addToolBar(Qt::TopToolBarArea, toolbar_);
  ((MainWindow*) parent_)->addToolBarBreak();
  show_toolbar_action_ = toolbar_->toggleViewAction();

  //add each action to the mainwindow action_list
  action_list->addAction(cut_by_edge_tool_->action_);
  action_list->addAction(cut_by_vertex_tool_->action_);
  action_list->addAction(cut_by_edge_vertex_tool_->action_);
  action_list->addAction(cut_by_face_tool_->action_);
  action_list->addAction(truncate_edge_tool_->action_);
  action_list->addAction(truncate_vertex_tool_->action_);
  action_list->addAction(convex_hull_tool_->action_);

  //add each action to the mainwindow action_group
  action_group->addAction(cut_by_edge_tool_->action_);
  action_group->addAction(cut_by_vertex_tool_->action_);
  action_group->addAction(cut_by_edge_vertex_tool_->action_);
  action_group->addAction(cut_by_face_tool_->action_);
  action_group->addAction(truncate_edge_tool_->action_);
  action_group->addAction(truncate_vertex_tool_->action_);
  action_group->addAction(convex_hull_tool_->action_);

  //add each widget to the mainwindow stacked_widget
  stacked_widget->addWidget(cut_by_edge_->widget_);
  stacked_widget->addWidget(cut_by_vertex_tool_->widget_);
  stacked_widget->addWidget(cut_by_edge_vertex_tool_->widget_);
  stacked_widget->addWidget(cut_by_face_tool_->widget_);
  stacked_widget->addWidget(truncate_edge_tool_->widget_);
  stacked_widget->addWidget(truncate_vertex_tool_->widget_);
  stacked_widget->addWidget(convex_hull_tool_->widget_);

  //create the QMenu for this toolset
  menu_ = new QMenu(tr("Conical"));
  menu_->addAction(cut_by_edge_tool_->action_);
  menu_->addAction(cut_by_vertex_tool_->action_);
  menu_->addAction(cut_by_edge_vertex_tool_->action_);
  menu_->addAction(cut_by_face_tool_->action_);
  menu_->addAction(truncate_edge_tool_->action_);
  menu_->addAction(truncate_vertex_tool_->action_);
  menu_->addAction(convex_hull_tool_->action_);
}

void ConicalToolset::retranslateUi() {
  menu_->setTitle(tr("Conical"));
  toolbar_->setWindowTitle(tr("Conical Toolset"));
  cut_by_edge_tool_->RetranslateUi();
  cut_by_vertex_tool_->RetranslateUi();
  cut_by_edge_vertex_tool_->RetranslateUi();
  cut_by_face_tool_->RetranslateUi();
  truncate_edge_tool_->RetranslateUi();
  truncate_vertex_tool_->RetranslateUi();
  convex_hull_tool_->RetranslateUi();
}

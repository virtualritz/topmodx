/*!
 \ingroup gui
 @{

 \class BasicToolset
 \brief Basics Operations including insert-edge and delete-edge.

 \note

 \see BasicToolset
 */

#include <QtGui>

#include "basic_toolset.h"

/*!
 * \brief Constructor
 *
 * @param parent the MainWindow widget
 * @param shortcut_manager the shortcut manager class for adding a custom shortcut to each menu action or icon
 * @param action_list the master list of actions for use with the CommandCompleter class
 *
 */
BasicToolset::BasicToolset(QWidget *parent, QShortcutManager *shortcut_manager,
                           QWidget *action_list, QActionGroup *action_group,
                           QStackedWidget *stacked_widget) :
  QWidget(parent) {

  setParent(0);
  parent_ = parent;

  //add the tools to the toolset
  insert_edge_tool_ = new InsertEdgeTool(parent);
  delete_edge_tool_ = new DeleteEdgeTool(parent);
  collapse_edge_tool_ = new CollapseEdgeTool(parent);
  subdivide_edge_tool_ = new SubdivideEdgeTool(parent);
  connect_edges_tool_ = new ConnectEdgesTool(parent);
  splice_corners_tool_ = new SpliceCornersTool(parent);
  geometric_tool_ = GeometricTool::GetInstance(parent);
  dup_component_tool_ = new DupComponentTool(parent);

  //setup the toolbar
  toolbar_ = new QToolBar(tr("Tools"), this);
  toolbar_->setFloatable(true);
  toolbar_->setIconSize(QSize(32, 32));

  //add each action to the toolbar
  toolbar_->addAction(insert_edge_tool_->action_);
  toolbar_->addAction(delete_edge_tool_->action_);
  toolbar_->addAction(collapse_edge_tool_->action_);
  toolbar_->addAction(subdivide_edge_tool_->action_);
  toolbar_->addAction(connect_edges_tool_->action_);
  toolbar_->addAction(splice_corners_tool_->action_);
  toolbar_->addAction(geometric_tool_->action_);
  toolbar_->addAction(dup_component_tool_->action_);

  ((MainWindow*) parent_)->addToolBar(Qt::TopToolBarArea, toolbar_);
  ((MainWindow*) parent_)->addToolBarBreak();
  show_toolbar_action_ = toolbar_->toggleViewAction();

  //add each action to the mainwindow action_list
  action_list->addAction(insert_edge_tool_->action_);
  action_list->addAction(delete_edge_tool_->action_);
  action_list->addAction(collapse_edge_tool_->action_);
  action_list->addAction(subdivide_edge_tool_->action_);
  action_list->addAction(connect_edges_tool_->action_);
  action_list->addAction(splice_corners_tool_->action_);
  action_list->addAction(geometric_tool_->action_);
  action_list->addAction(dup_component_tool_->action_);

  //add each action to the mainwindow action_group
  action_group->addAction(insert_edge_tool_->action_);
  action_group->addAction(delete_edge_tool_->action_);
  action_group->addAction(collapse_edge_tool_->action_);
  action_group->addAction(subdivide_edge_tool_->action_);
  action_group->addAction(connect_edges_tool_->action_);
  action_group->addAction(splice_corners_tool_->action_);
  action_group->addAction(geometric_tool_->action_);
  action_group->addAction(dup_component_tool_->action_);

  //add each widget to the mainwindow stacked_widget
  stacked_widget->addWidget(insert_edge_tool_->widget_);
  stacked_widget->addWidget(delete_edge_tool_->widget_);
  stacked_widget->addWidget(collapse_edge_tool_->widget_);
  stacked_widget->addWidget(subdivide_edge_tool_->widget_);
  stacked_widget->addWidget(connect_edges_tool_->widget_);
  stacked_widget->addWidget(splice_corners_tool_->widget_);
  stacked_widget->addWidget(geometric_tool_->widget_);
  stacked_widget->addWidget(dup_component_tool_->widget_);

  //create the QMenu for this toolset
  menu_ = new QMenu(tr("Basics"));
  menu_->addAction(insert_edge_tool_->action_);
  menu_->addAction(delete_edge_tool_->action_);
  menu_->addAction(collapse_edge_tool_->action_);
  menu_->addAction(subdivide_edge_tool_->action_);
  menu_->addAction(connect_edges_tool_->action_);
  menu_->addAction(splice_corners_tool_->action_);
  menu_->addAction(geometric_tool_->action_);
  menu_->addAction(dup_component_tool_->action_);
}

void BasicToolset::retranslateUi() {
  menu_->setTitle(tr("Basics"));
  toolbar_->setWindowTitle(tr("Tools"));
  insert_edge_tool_->RetranslateUi();
  delete_edge_tool_->RetranslateUi();
  collapse_edge_tool_->RetranslateUi();
  subdivide_edge_tool_->RetranslateUi();
  connect_edges_tool_->RetranslateUi();
  splice_corners_tool_->RetranslateUi();
  geometric_tool_->RetranslateUi();
  dup_component_tool_->RetranslateUi();
}

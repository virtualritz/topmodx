/*** ***/

#include <QtGui>

#include "extrusion_toolset.h"

/*!
 \ingroup gui
 @{

 \class ExtrusionToolset
 \brief Extrusion Operations GUI elements.

 \note

 \see ExtrusionToolset
 */

ExtrusionToolset::ExtrusionToolset(QWidget *parent,
                                   QShortcutManager *shortcut_manager,
                                   QWidget *action_list,
                                   QActionGroup *action_group,
                                   QStackedWidget *stacked_widget) :
  QWidget(parent) {
  setParent(0);
  parent_ = parent;

  //add the tools to the toolset
  doo_sabin_extrude_tool_ = new DooSabinExtrudeTool(parent);
  cubical_extrude_tool_ = new CubicalExtrudeTool(parent);
  dodecahedral_extrude_tool_ = new DodecahedralExtrudeTool(parent);
  icosahedral_extrude_tool_ = new IcosahedralExtrudeTool(parent);
  octahedral_extrude_tool_ = new OctahedralExtrudeTool(parent);
  stellate_extrude_tool_ = new StellateExtrudeTool(parent);
  double_stellate_extrude_tool_ = new DoubleStellateExtrudeTool(parent);
  dome_extrude_tool_ = new DomeExtrudeTool(parent);

  //setup the toolbar
  toolbar_ = new QToolBar(tr("Tools"), this);
  toolbar_->setFloatable(true);
  toolbar_->setIconSize(QSize(32, 32));

  //add each action to the toolbar
  toolbar_->addAction(doo_sabin_extrude_tool_->action_);
  toolbar_->addAction(cubical_extrude_tool_->action_);
  toolbar_->addAction(dodecahedral_extrude_tool_->action_);
  toolbar_->addAction(icosahedral_extrude_tool_->action_);
  toolbar_->addAction(octahedral_extrude_tool_->action_);
  toolbar_->addAction(stellate_extrude_tool_->action_);
  toolbar_->addAction(double_stellate_extrude_tool_->action_);
  toolbar_->addAction(dome_extrude_tool_->action_);

  ((MainWindow*) parent_)->addToolBar(Qt::TopToolBarArea, toolbar_);
  ((MainWindow*) parent_)->addToolBarBreak();
  show_toolbar_action_ = toolbar_->toggleViewAction();

  //add each action to the mainwindow action_list
  action_list->addAction(doo_sabin_extrude_tool_->action_);
  action_list->addAction(cubical_extrude_tool_->action_);
  action_list->addAction(dodecahedral_extrude_tool_->action_);
  action_list->addAction(icosahedral_extrude_tool_->action_);
  action_list->addAction(octahedral_extrude_tool_->action_);
  action_list->addAction(stellate_extrude_tool_->action_);
  action_list->addAction(double_stellate_extrude_tool_->action_);
  action_list->addAction(dome_extrude_tool_->action_);

  //add each action to the mainwindow action_group
  action_group->addAction(doo_sabin_extrude_tool_->action_);
  action_group->addAction(cubical_extrude_tool_->action_);
  action_group->addAction(dodecahedral_extrude_tool_->action_);
  action_group->addAction(icosahedral_extrude_tool_->action_);
  action_group->addAction(octahedral_extrude_tool_->action_);
  action_group->addAction(stellate_extrude_tool_->action_);
  action_group->addAction(double_stellate_extrude_tool_->action_);
  action_group->addAction(dome_extrude_tool_->action_);

  //add each widget to the mainwindow stacked_widget
  stacked_widget->addWidget(doo_sabin_extrude_tool_->widget_);
  stacked_widget->addWidget(cubical_extrude_tool_->widget_);
  stacked_widget->addWidget(dodecahedral_extrude_tool_->widget_);
  stacked_widget->addWidget(icosahedral_extrude_tool_->widget_);
  stacked_widget->addWidget(octahedral_extrude_tool_->widget_);
  stacked_widget->addWidget(stellate_extrude_tool_->widget_);
  stacked_widget->addWidget(double_stellate_extrude_tool_->widget_);
  stacked_widget->addWidget(dome_extrude_tool_->widget_);

  //create the QMenu for this toolset
  menu_ = new QMenu(tr("Extrusions"));
  menu_->addAction(doo_sabin_extrude_tool_->action_);
  menu_->addAction(cubical_extrude_tool_->action_);
  menu_->addAction(dodecahedral_extrude_tool_->action_);
  menu_->addAction(icosahedral_extrude_tool_->action_);
  menu_->addAction(octahedral_extrude_tool_->action_);
  menu_->addAction(stellate_extrude_tool_->action_);
  menu_->addAction(double_stellate_extrude_tool_->action_);
  menu_->addAction(dome_extrude_tool_->action_);
}

void ExtrusionToolset::retranslateUi() {

}

/*** ***/

#include <QtGui>

#include "ExperimentalModes.h"

/*!
 \ingroup gui
 @{

 \class ExperimentalMode
 \brief experimental stuff like paint bucket

 \note

 \see PaintBucket
 */

ExperimentalToolset::ExperimentalToolset(QWidget *parent,
                                   QShortcutManager *shortcut_manager,
                                   QWidget *action_list,
                                   QActionGroup *action_group,
                                   QStackedWidget *stacked_widget) :
  QWidget(parent) {

  setParent(0);
  parent_ = parent;

  //add the tools to the toolset
  paint_bucket_tool_ = new PainBucketTool(parent);

  //setup the toolbar
  toolbar_ = new QToolBar(tr("Experimental"), this);
  toolbar_->setFloatable(true);
  toolbar_->setIconSize(QSize(32, 32));

  //add each action to the toolbar
  toolbar_->addAction(paint_bucket_tool_->action_);

  ((MainWindow*) parent_)->addToolBar(Qt::TopToolBarArea, toolbar_);
  ((MainWindow*) parent_)->addToolBarBreak();
  show_toolbar_action_ = toolbar_->toggleViewAction();

  //add each action to the mainwindow action_list
  action_list->addAction(paint_bucket_tool_->action_);

  //add each action to the mainwindow action_group
  action_group->addAction(paint_bucket_tool_->action_);

  //add each widget to the mainwindow stacked_widget
  stacked_widget->addWidget(paint_bucket_tool_->widget_);

  //create the QMenu for this toolset
  menu_ = new QMenu(tr("Experimental"));
  menu_->addAction(paint_bucket_tool_->action_);
}

void ExperimentalToolset::retranslateUi() {

}

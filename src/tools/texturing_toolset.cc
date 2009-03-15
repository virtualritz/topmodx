#include <QtGui>

#include "texturing_toolset.h"

/*!
 \ingroup gui
 @{

 \class TexturingToolset
 \brief Texturing Operations GUI elements.

 \note

 \see TexturingToolset
 */

TexturingToolset::TexturingToolset(QWidget *parent,
                                   QShortcutManager *shortcut_manager,
                                   QWidget *action_list,
                                   QActionGroup *action_group,
                                   QStackedWidget *stacked_widget) :
  QWidget(parent) {

  setParent(0);
  parent_ = parent;

  //add the tools to the toolset
  tile_texturing_tool_ = new InsertEdgeTool(parent);

  //setup the toolbar
  toolbar_ = new QToolBar(tr("Texturing"), this);
  toolbar_->setFloatable(true);
  toolbar_->setIconSize(QSize(32, 32));

  //add each action to the toolbar
  toolbar_->addAction(tile_texturing_tool_->action_);

  ((MainWindow*) parent_)->addToolBar(Qt::TopToolBarArea, toolbar_);
  ((MainWindow*) parent_)->addToolBarBreak();
  show_toolbar_action_ = toolbar_->toggleViewAction();

  //add each action to the mainwindow action_list
  action_list->addAction(tile_texturing_tool_->action_);

  //add each action to the mainwindow action_group
  action_group->addAction(tile_texturing_tool_->action_);

  //add each widget to the mainwindow stacked_widget
  stacked_widget->addWidget(tile_texturing_tool_->widget_);

  //create the QMenu for this toolset
  menu_ = new QMenu(tr("Texturing"));
  menu_->addAction(tile_texturing_tool_->action_);

}

void TexturingToolset::retranslateUi() {
  menu_->setTitle(tr("Texturing"));
}

/*!
 \file texturing_toolset.h
 \brief Definition of the TexturingToolset class

 \see TexturingToolset
 */

#ifndef TEXTURING_TOOLSET_H
#define TEXTURING_TOOLSET_H

#include <QWidget>

#include <QBoxLayout>
#include <QStackedWidget>
#include <QComboBox>

#include "../MainWindow.h"
#include "tile_texturing_tool.h"

class MainWindow;
class QPushButton;
class QLabel;

class TileTexturingTool;

class TexturingToolset: public QWidget {

public:
  TexturingToolset(QWidget *parent, QShortcutManager *shortcut_manager,
                   QWidget *action_list, QActionGroup *action_group,
                   QStackedWidget *stacked_widget);
  void retranslateUi();

  QToolBar *toolbar_; //QToolBar to store the icon/button of each tool in this toolset
  QMenu *menu_; //QMenu to store the QActions of each tool in this toolset
  QAction *show_toolbar_action_; //QAction to show/hide the toolbar

protected:

public slots:

private:
  QWidget *parent_;
  TileTexturingTool *tile_texturing_tool_;

};

#endif /* TEXTURING_TOOLSET_H */

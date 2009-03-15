#ifndef EXPERIMENTAL_TOOLSET_H_
#define EXPERIMENTAL_TOOLSET_H_

#include <QWidget>

#include <QGridLayout>
#include <QStackedWidget>
#include <QComboBox>

#include "../MainWindow.h"
#include "paint_bucket_tool.h"


class MainWindow;
class PaintBucketTool;

class ExperimentalToolset : public QWidget {

public:
  ExperimentalToolset(QWidget *parent, QShortcutManager *shortcut_manager,
                      QWidget *action_list, QActionGroup *action_group,
                      QStackedWidget *stacked_widget);
  void retranslateUi();

  QToolBar *toolbar_; //QToolBar to store the icon/button of each tool in this toolset
  QMenu *menu_; //QMenu to store the QActions of each tool in this toolset
  QAction *show_toolbar_action_; //QAction to show/hide the toolbar

protected:

private:
  QWidget *parent_;
  PaintBucketTool *paint_bucket_tool_;

};
#endif /* EXPERIMENTAL_TOOLSET_H_ */

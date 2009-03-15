#ifndef EXTRUSION_TOOLSET_H_
#define EXTRUSION_TOOLSET_H_

#include <QWidget>

/*!
 \file ExtrusionToolset.h
 \brief Definition of the ExtrusionToolset class

 \see ExtrusionToolset
 */

#include "../MainWindow.h"
#include "cubical_extrude_tool.h"
#include "doo_sabin_extrude_tool.h"
#include "dodecahedral_extrude_tool.h"
#include "icosahedral_extrude_tool.h"
#include "octahedral_extrude_tool.h"
#include "stellate_extrude_tool.h"
#include "double_stellate_extrude_tool.h"
#include "dome_extrude_tool.h"

class MainWindow;
class CubicalExtrudeTool;
class DooSabinExtrudeTool;
class DodecahedralExtrudeTool;
class IcosahedralExtrudeTool;
class OctahedralExtrudeTool;
class StellateExtrudeTool;
class DoubleStellateExtrudeTool;
class DomeExtrudeTool;

class MainWindow;

class ExtrusionToolset: public QWidget {

public:
  ExtrusionToolset(QWidget *parent, QShortcutManager *shortcut_manager,
                   QWidget *action_list, QActionGroup *action_group,
                   QStackedWidget *stacked_widget);
  void retranslateUi();

  QToolBar *toolbar_; //QToolBar to store the icon/button of each tool in this toolset
  QMenu *menu_; //QMenu to store the QActions of each tool in this toolset
  QAction *show_toolbar_action_; //QAction to show/hide the toolbar

private:
  QWidget *parent_;
  CubicalExtrudeTool *cubical_extrude_tool_;
  DooSabinExtrudeTool *doo_sabin_extrude_tool_;
  DodecahedralExtrudeTool *dodecahedral_extrude_tool_;
  IcosahedralExtrudeTool *icosahedral_extrude_tool_;
  OctahedralExtrudeTool *octahedral_extrude_tool_;
  StellateExtrudeTool *stellate_extrude_tool_;
  DoubleStellateExtrudeTool *double_stellate_extrude_tool_;
  DomeExtrudeTool *dome_extrude_tool_;

};

#endif /* EXTRUSION_TOOLSET_H_ */

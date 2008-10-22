/*!
 \file BasicsMode.h
 \brief Definition of the BasicsMode class

 \see BasicsMode
 */

#ifndef BASICSMODE_H
#define BASICSMODE_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>

#include "MainWindow.h"
#include "tools/insert_edge_tool.h"
#include "tools/cubical_extrude_tool.h"

class MainWindow;
class InsertEdgeTool;
class CubicalExtrudeTool;

class QComboBox;
class QPushButton;
class QGroupBox;
class QCheckBox;
class QLabel;

class BasicsMode : public QWidget {
Q_OBJECT

public:
	BasicsMode(QWidget *parent)  ;
	void  addActions(QActionGroup *actionGroup, QToolBar *toolBar, QStackedWidget *stackedWidget);
	QMenu* getMenu();
	void retranslateUi();
protected:

private:

	QWidget *parent_;
	QMenu *mBasicsMenu;
  InsertEdgeTool *insert_edge_tool_;
  CubicalExtrudeTool *cubical_extrude_tool;
public slots:

};

#endif

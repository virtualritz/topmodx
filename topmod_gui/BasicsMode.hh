/*** ***/

/****************************************************************************
 **
 **
 ****************************************************************************/

#ifndef BASICSMODE_H
#define BASICSMODE_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>

/*!
	\file BasicsMode.hh
	\brief Definition of the BasicsMode class
	
	\see BasicsMode
*/

#include "MainWindow.hh"

class MainWindow;

class QComboBox;
class QPushButton;
class QGroupBox;
class QCheckBox;
class QLabel;

// Declarition of the class DupComponentTool.
// We should move it to a file named dup_component_tool.hh later.
// I will create a super class for all the tools. -- Fenghui
class DupComponentTool : public QWidget {
  Q_OBJECT // does it have to be a Q_OBJECT?

 public:
  QAction *action_;
  QWidget *widget_;
  QGridLayout *layout_;

  DupComponentTool(QWidget *parent);

 protected:
  QWidget *parent_;

  QLabel *translation_x_label_;
  QLabel *translation_y_label_;
  QLabel *translation_z_label_;
  QLabel *rotation_x_label_;
  QLabel *rotation_y_label_;
  QLabel *rotation_z_label_;
  QLabel *scaling_x_label_;
  QLabel *scaling_y_label_;
  QLabel *scaling_z_label_;

	QDoubleSpinBox *translation_x_spin_;
	QDoubleSpinBox *translation_y_spin_;
	QDoubleSpinBox *translation_z_spin_;
	QDoubleSpinBox *rotation_x_spin_;
	QDoubleSpinBox *rotation_y_spin_;
	QDoubleSpinBox *rotation_z_spin_;
	QDoubleSpinBox *scaling_x_spin_;
	QDoubleSpinBox *scaling_y_spin_;
	QDoubleSpinBox *scaling_z_spin_;

  QPushButton *apply_button_;

 public slots:
  // We might not need a parameter for DoAction since it will grab parameters
  // from the controls directly.
  void Apply();
  void Activate();
};

// Declarition of the class GeometricTool.
// We should move it to a file named geometric_tool.hh later.
// I will create a super class for all the tools. -- Fenghui
class GeometricTool : public QWidget {
  Q_OBJECT // does it have to be a Q_OBJECT?

 public:
  QAction *action_;
  QWidget *widget_;
  QGridLayout *layout_;

  GeometricTool(QWidget *parent);

 protected:
  QWidget *parent_;
    
  QLabel *translation_x_label_;
  QLabel *translation_y_label_;
  QLabel *translation_z_label_;
  QLabel *rotation_x_label_;
  QLabel *rotation_y_label_;
  QLabel *rotation_z_label_;
  QLabel *scaling_x_label_;
  QLabel *scaling_y_label_;
  QLabel *scaling_z_label_;

	QDoubleSpinBox *translation_x_spin_;
	QDoubleSpinBox *translation_y_spin_;
	QDoubleSpinBox *translation_z_spin_;
	QDoubleSpinBox *rotation_x_spin_;
	QDoubleSpinBox *rotation_y_spin_;
	QDoubleSpinBox *rotation_z_spin_;
	QDoubleSpinBox *scaling_x_spin_;
	QDoubleSpinBox *scaling_y_spin_;
	QDoubleSpinBox *scaling_z_spin_;

  QPushButton *reset_button_;
  QPushButton *apply_button_;

  map<DLFLVertexPtr, Vector3d> init_positions_;
  bool active_;
 public slots:
  // We might not need a parameter for DoAction since it will grab parameters
  // from the controls directly.
  void DoAction(double);
  void Apply();
  void Reset();
  void Activate();
};

class BasicsMode : public QWidget {
	Q_OBJECT
	
public:
	BasicsMode(QWidget *parent, QShortcutManager *sm, QWidget *actionList);
	void addActions(QActionGroup *actionGroup, QToolBar *toolBar, QStackedWidget *stackedWidget);
	QMenu* getMenu();
	void retranslateUi();
	
	QAction *mInsertEdgeAction;
	QAction *mDeleteEdgeAction;	
	QAction *mCollapseEdgeAction;	
	QAction *mSubdivideEdgeAction;	
	QAction *mConnectEdgesAction;	
	QAction *mSpliceCornersAction;
	// QAction *mTransformsAction;
	QAction *mSelectionOptionsAction;
	
	QWidget *mInsertEdgeWidget;
	QWidget *mDeleteEdgeWidget;
	QWidget *mCollapseEdgeWidget;
	QWidget *mSubdivideEdgeWidget; 
	QWidget *mConnectEdgesWidget;
	QWidget *mSpliceCornersWidget; 
	// QWidget *mTransformsWidget;	
	QWidget *mSelectionOptionsWidget;	
	
	QGridLayout *mInsertEdgeLayout;
	QGridLayout *mDeleteEdgeLayout;
	QGridLayout *mCollapseEdgeLayout;
	QGridLayout *mSubdivideEdgeLayout; 
	QGridLayout *mConnectEdgesLayout;
	QGridLayout *mSpliceCornersLayout; 
	// QGridLayout *mTransformsLayout;
	QGridLayout *mSelectionOptionsLayout;

protected:
	void setupInsertEdge();
	void setupDeleteEdge();
	void setupCollapseEdge();
	void setupSubdivideEdge();
	void setupConnectEdges();
	void setupSpliceCorners();
	// void setupTransforms();
	void setupSelectionOptions();
	QDoubleSpinBox *createDoubleSpinBox(QGridLayout *layout, QLabel *label, QString s, double low, double high, double step, double value, double decimals, int row, int col);
	

private:
	
	QWidget *mParent;
	QMenu *mBasicsMenu;	
  GeometricTool *geometric_tool_;
  DupComponentTool *dup_component_tool_;
	
	QLabel *numSubdivsLabel;
	QDoubleSpinBox *numSubdivsSpinBox;
  /*
	QLabel *transformLabel;
	QLabel *xPosLabel;
	QLabel *yPosLabel;
	QLabel *zPosLabel;	
	QLabel *scaleLabel;
	QLabel *xScaleLabel;
	QLabel *yScaleLabel;
	QLabel *zScaleLabel;
  */
	
	QLabel *noOptionsInsertEdgeLabel;
	QCheckBox *cleanupDeleteEdgeCheckBox;
	QLabel *noOptionsCollapseEdgeLabel;
	QLabel *noOptionsConnectEdgesLabel;
	QLabel *noOptionsSpliceCornersLabel;
	
	// QPushButton *freezeTransformsButton;
	
	//transform spinboxes
  /*
	QDoubleSpinBox *xScaleSpinBox;
	QDoubleSpinBox *yScaleSpinBox;
	QDoubleSpinBox *zScaleSpinBox;
	QDoubleSpinBox *xPosSpinBox;
	QDoubleSpinBox *yPosSpinBox;
	QDoubleSpinBox *zPosSpinBox;
  */
	
	QLabel *mFaceAreaToleranceLabel;
	QDoubleSpinBox *mFaceAreaToleranceSpinBox;

	QLabel *mSplit2ValenceVertexOffsetLabel;
	QDoubleSpinBox *mSplit2ValenceVertexOffsetSpinBox;
	
public slots:
	// void freezeTransforms();
		
	void triggerInsertEdge();
	void triggerDeleteEdge();
	void triggerCollapseEdge();
	void triggerSubdivideEdge();
	void triggerConnectEdges();
	void triggerSpliceCorners();
	// void triggerTransforms();
	void triggerSelectionOptions();
};

#endif

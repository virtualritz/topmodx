/*!
 \ingroup gui
 @{

 \class BasicsMode
 \brief Basics Operations including insert-edge and delete-edge.

 \note

 \see BasicsMode
 */

#include <QtGui>

#include "BasicsMode.h"

/*!
 * \brief Constructor
 *
 * @param parent the MainWindow widget
 * @param sm the shortcut manager class for adding a custom shortcut to each menu action or icon
 * @param actionList the master list of actions for use with the CommandCompleter class
 *
 */
BasicsMode::BasicsMode(QWidget *parent, QShortcutManager *sm,
                       QWidget *actionList) :
  QWidget(parent) {

  setParent(0);
  parent_ = parent;
  insert_edge_tool_ = new InsertEdgeTool(parent);
  delete_edge_tool_ = new DeleteEdgeTool(parent);
  collapse_edge_tool_ = new CollapseEdgeTool(parent);
  subdivide_edge_tool_ = new SubdivideEdgeTool(parent);
  connect_edges_tool_ = new ConnectEdgesTool(parent);
  splice_corners_tool_ = new SpliceCornersTool(parent);
  geometric_tool_ = GeometricTool::GetInstance(parent);
  // geometric_tool_ = new GeometricTool(parent);
  dup_component_tool_ = new DupComponentTool(parent);

  actionList->addAction(insert_edge_tool_->action_);
  actionList->addAction(delete_edge_tool_->action_);
  actionList->addAction(collapse_edge_tool_->action_);
  actionList->addAction(subdivide_edge_tool_->action_);
  actionList->addAction(connect_edges_tool_->action_);
  actionList->addAction(splice_corners_tool_->action_);
  actionList->addAction(geometric_tool_->action_);
  actionList->addAction(dup_component_tool_->action_);
}

QMenu* BasicsMode::getMenu() {
  mBasicsMenu = new QMenu(tr("Basics"));

  mBasicsMenu->addAction(insert_edge_tool_->action_);
  mBasicsMenu->addAction(delete_edge_tool_->action_);
  mBasicsMenu->addAction(collapse_edge_tool_->action_);
  mBasicsMenu->addAction(subdivide_edge_tool_->action_);
  mBasicsMenu->addAction(connect_edges_tool_->action_);
  mBasicsMenu->addAction(splice_corners_tool_->action_);
  mBasicsMenu->addAction(geometric_tool_->action_);
  mBasicsMenu->addAction(dup_component_tool_->action_);
//  mBasicsMenu->addAction(mSelectionOptionsAction);

  return mBasicsMenu;
}

//void BasicsMode::triggerSelectionOptions() {
//  ((MainWindow*) parent_)->setToolOptions(mSelectionOptionsWidget);
//}

void BasicsMode::addActions(QActionGroup *actionGroup, QToolBar *toolBar,
                            QStackedWidget *stackedWidget) {

  actionGroup->addAction(insert_edge_tool_->action_);
  actionGroup->addAction(delete_edge_tool_->action_);
  actionGroup->addAction(collapse_edge_tool_->action_);
  actionGroup->addAction(subdivide_edge_tool_->action_);
  actionGroup->addAction(connect_edges_tool_->action_);
  actionGroup->addAction(splice_corners_tool_->action_);
//  actionGroup->addAction(mSelectionOptionsAction);
  actionGroup->addAction(geometric_tool_->action_);
  actionGroup->addAction(dup_component_tool_->action_);

  toolBar->addAction(insert_edge_tool_->action_);
  toolBar->addAction(delete_edge_tool_->action_);
  toolBar->addAction(collapse_edge_tool_->action_);
  toolBar->addAction(subdivide_edge_tool_->action_);
  toolBar->addAction(connect_edges_tool_->action_);
  toolBar->addAction(splice_corners_tool_->action_);
//  toolBar->addAction(mSelectionOptionsAction);
  toolBar->addAction(geometric_tool_->action_);
  toolBar->addAction(dup_component_tool_->action_);

  stackedWidget->addWidget(insert_edge_tool_->widget_);
  stackedWidget->addWidget(delete_edge_tool_->widget_);
  stackedWidget->addWidget(collapse_edge_tool_->widget_);
  stackedWidget->addWidget(subdivide_edge_tool_->widget_);
  stackedWidget->addWidget(connect_edges_tool_->widget_);
  stackedWidget->addWidget(splice_corners_tool_->widget_);
//  stackedWidget->addWidget(mSelectionOptionsWidget);
  stackedWidget->addWidget(geometric_tool_->widget_);
  stackedWidget->addWidget(dup_component_tool_->widget_);

}

//void BasicsMode::setupSelectionOptions() {
//
//  mSelectionOptionsLayout = new QGridLayout;
//  mSelectionOptionsLayout->setVerticalSpacing(1);
//  mSelectionOptionsLayout->setHorizontalSpacing(1);
//
//  mFaceAreaToleranceLabel = new QLabel(this);
//  mFaceAreaToleranceSpinBox = createDoubleSpinBox(mSelectionOptionsLayout,
//      mFaceAreaToleranceLabel, tr("Face Area Sel.\nTolerance"), 0.0, 5.0,
//      0.001, 0.05, 3, 0, 0);
//  connect(mFaceAreaToleranceSpinBox, SIGNAL(valueChanged(double)), ((MainWindow*) parent_), SLOT(changeFaceAreaTolerance(double)));
//
//  mSplit2ValenceVertexOffsetLabel = new QLabel(this);
//  mSplit2ValenceVertexOffsetSpinBox = createDoubleSpinBox(
//      mSelectionOptionsLayout, mSplit2ValenceVertexOffsetLabel, tr(
//          "Valence-2 Split\nOffset"), -0.1, 5.0, 0.001, -0.1, 3, 1, 0);
//  connect(mSplit2ValenceVertexOffsetSpinBox, SIGNAL(valueChanged(double)), ((MainWindow*) parent_), SLOT(changeValence2SplitOffset(double)));
//
//  mSelectionOptionsLayout->setRowStretch(2, 1);
//  mSelectionOptionsLayout->setColumnStretch(2, 1);
//  mSelectionOptionsWidget->setWindowTitle(tr("Selection Options Mode"));
//  mSelectionOptionsWidget->setLayout(mSelectionOptionsLayout);
//}

void BasicsMode::retranslateUi() {
  //mInsertEdgeAction->setText(tr("Insert Edge"));
  //mInsertEdgeAction->setStatusTip(tr("Enter Insert Edge Mode"));
  //mInsertEdgeAction->setToolTip(tr("Insert Edge Mode"));
  //mDeleteEdgeAction->setText(tr("Delete Edge"));
  //mDeleteEdgeAction->setStatusTip(tr("Enter Delete Edge Mode"));
  //	mDeleteEdgeAction->setToolTip(tr("Delete Edge Mode"));
  //	mCollapseEdgeAction->setText(tr("Collapse Edge"));
  //	mCollapseEdgeAction->setStatusTip(tr("Enter Collapse Edge Mode"));
  //	mCollapseEdgeAction->setToolTip(tr("Collapse Edge Mode"));
  //	mSubdivideEdgeAction->setText(tr("Subdivide Edge"));
  //	mSubdivideEdgeAction->setStatusTip(tr("Enter Subdivide Edge Mode"));
  //	mSubdivideEdgeAction->setToolTip(tr("Subdivide Edge Mode"));
  //	mConnectEdgesAction->setText(tr("Connect Edges"));
  //	mConnectEdgesAction->setStatusTip(tr("Enter Connect Edges Mode"));
  //	mConnectEdgesAction->setToolTip(tr("Connect Edges Mode"));
  //	mSpliceCornersAction->setText(tr("Splice Corners"));
  //	mSpliceCornersAction->setStatusTip(tr("Enter Splice Corners Mode"));
  //	mSpliceCornersAction->setToolTip(tr("Splice Corners Mode"));
  /*
   mTransformsAction->setText(tr("Transforms"));
   mTransformsAction->setStatusTip(tr("Enter Transforms Mode"));
   mTransformsAction->setToolTip(tr("Transforms Mode"));
   */
//  mSelectionOptionsAction->setText(tr("Selection Options"));
//  mSelectionOptionsAction->setStatusTip(tr("Enter Selection Options Mode"));
//  mSelectionOptionsAction->setToolTip(tr("Selection Options Mode"));
//  mFaceAreaToleranceLabel->setText(tr("Face Area Sel.\nTolerance"));
//  mSplit2ValenceVertexOffsetLabel->setText(tr("Valence-2 Split\nOffset"));
  mBasicsMenu->setTitle(tr("Basics"));

  //mode spinbox labels etc...
  //noOptionsInsertEdgeLabel->setText(tr("No Options for this tool."));
  //mInsertEdgeWidget->setWindowTitle(tr("Insert Edge"));
  //	cleanupDeleteEdgeCheckBox->setText(tr("Cleanup"));
  //	mDeleteEdgeWidget->setWindowTitle(tr("Delete Edge Mode"));
  //	noOptionsCollapseEdgeLabel->setText(tr("No Options for this tool."));
  //	mCollapseEdgeWidget->setWindowTitle(tr("Collapse Edge"));
  //	numSubdivsLabel->setText(tr("# Subdivisions"));
  //	mSubdivideEdgeWidget->setWindowTitle(tr("Subdivide Edge Mode"));
  //	noOptionsConnectEdgesLabel->setText(tr("No Options for this tool."));
  //	mConnectEdgesWidget->setWindowTitle(tr("Connect Edges"));
  //	noOptionsSpliceCornersLabel->setText(tr("No Options for this tool."));
  //	mSpliceCornersWidget->setWindowTitle(tr("Splice Corners"));
  /*
   xPosLabel->setText(tr("X-translate"));
   yPosLabel->setText(tr("Y-translate"));
   zPosLabel->setText(tr("Z-translate"));
   xScaleLabel->setText(tr("X-scale"));
   yScaleLabel->setText(tr("Y-scale"));
   zScaleLabel->setText(tr("Z-scale"));
   freezeTransformsButton->setText(tr("&Freeze Transforms"));
   mTransformsWidget->setWindowTitle(tr("Transforms Mode"));
   */

}

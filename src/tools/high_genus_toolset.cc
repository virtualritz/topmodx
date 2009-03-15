/*** ***/

#include <QtGui>

#include "HighGenusToolset.h"

/*!
	\ingroup gui
	@{

	\class HighGenusToolset
	\brief High Genus Operations GUI elements.

	\note

	\see HighGenusToolset
*/

/*!
* \brief Constructor
*
* @param parent the MainWindow widget
* @param sm the shortcut manager class for adding a custom shortcut to each menu action or icon
* @param actionList the master list of actions for use with the CommandCompleter class
*
*/


// The implementation of HighGenusToolset starts here.

HighGenusToolset::HighGenusToolset(QWidget *parent, QShortcutManager *sm, QWidget *actionList)
		: QWidget(parent)
{
	setParent(0);
	parent_ = parent;
  create_torus_tool_ = new CreateTorusTool(parent);
  actionList->addAction(create_torus_tool_->action_);

	mAddHoleHandleWidget = new QWidget;
  mAddHoleHandleCVWidget = new QWidget;
  mAddHandleSIWidget = new QWidget;
  mRindModelingScalingWidget = new QWidget;
  mRindModelingThicknessWidget = new QWidget;
  mWireframeModelingWidget = new QWidget;
  mWireframeModeling2Widget = new QWidget;
  mColumnModelingWidget = new QWidget;
	mSierpinskyWidget = new QWidget;
	mMultiFaceHandleWidget = new QWidget;
	mMengerSpongeWidget = new QWidget;

	setupAddHoleHandle();
	setupAddHoleHandleCV();
	setupAddHandleSI();
	setupRindModelingScaling();
	setupRindModelingThickness();
	setupWireframeModeling();
	setupWireframeModeling2();
	setupColumnModeling();
	setupSierpinsky();
	setupMultiFaceHandle();
	setupMengerSponge();

	//setup the 10 modes for high genus modeling
	mAddHoleHandleAction = new QAction(QIcon(":images/highgenus_addholehandle.png"),tr("Add Hole/Handle"),this);
	mAddHoleHandleAction->setCheckable(true);
	sm->registerAction(mAddHoleHandleAction, "High Genus Operations", "");
	mAddHoleHandleAction->setStatusTip(tr("Enter Add Hole/Handle Mode"));
	mAddHoleHandleAction->setToolTip(tr("Add Hole/Handle Mode"));
	connect(mAddHoleHandleAction, SIGNAL(triggered()), this, SLOT(triggerAddHoleHandle()));
	actionList->addAction(mAddHoleHandleAction);

	mAddHoleHandleCVAction = new QAction(QIcon(":images/highgenus_addholehandlecv.png"),tr("Add Hole/Handle CV"),this);
	mAddHoleHandleCVAction->setCheckable(true);
	sm->registerAction(mAddHoleHandleCVAction, "High Genus Operations", "");
	mAddHoleHandleCVAction->setStatusTip(tr("Enter Add Hole/Handle CV Mode"));
	mAddHoleHandleCVAction->setToolTip(tr("Add Hole/Handle CV Mode"));
	connect(mAddHoleHandleCVAction, SIGNAL(triggered()), this, SLOT(triggerAddHoleHandleCV()));
	actionList->addAction(mAddHoleHandleCVAction);

	mAddHandleSIAction = new QAction(QIcon(":images/highgenus_addhandlesi.png"),tr("Add Handle SI"),this);
	mAddHandleSIAction->setCheckable(true);
	sm->registerAction(mAddHandleSIAction, "High Genus Operations", "");
	mAddHandleSIAction->setStatusTip(tr("Enter Add Handle (Shape Interpolation) Mode"));
	mAddHandleSIAction->setToolTip(tr("Add Handle (Shape Interpolation) Mode"));
	connect(mAddHandleSIAction, SIGNAL(triggered()), this, SLOT(triggerAddHandleSI()));
	actionList->addAction(mAddHandleSIAction);

	mRindModelingScalingAction = new QAction(QIcon(":images/highgenus_rindscaling.png"),tr("Rind Modeling Scaling"),this);
	mRindModelingScalingAction->setCheckable(true);
	sm->registerAction(mRindModelingScalingAction, "High Genus Operations", "");
	mRindModelingScalingAction->setStatusTip(tr("Enter Rind Modeling Scaling Mode"));
	mRindModelingScalingAction->setToolTip(tr("Rind Modeling Scaling Mode"));
	connect(mRindModelingScalingAction, SIGNAL(triggered()), this, SLOT(triggerRindModelingScaling()));
	actionList->addAction(mRindModelingScalingAction);

	mRindModelingThicknessAction = new QAction(QIcon(":images/highgenus_rindthickness.png"),tr("Rind Modeling Thickness"),this);
	mRindModelingThicknessAction->setCheckable(true);
	sm->registerAction(mRindModelingThicknessAction, "High Genus Operations", "");
	mRindModelingThicknessAction->setStatusTip(tr("Enter Rind Modeling Thickness Mode"));
	mRindModelingThicknessAction->setToolTip(tr("Rind Modeling Thickness Mode"));
	connect(mRindModelingThicknessAction, SIGNAL(triggered()), this, SLOT(triggerRindModelingThickness()));
	actionList->addAction(mRindModelingThicknessAction);

	mWireframeModelingAction = new QAction(QIcon(":images/highgenus_wireframe.png"),tr("Wireframe Modeling"),this);
	mWireframeModelingAction->setCheckable(true);
	sm->registerAction(mWireframeModelingAction, "High Genus Operations", "");
	mWireframeModelingAction->setStatusTip(tr("Enter Wireframe Modeling Mode"));
	mWireframeModelingAction->setToolTip(tr("Wireframe Modeling Mode"));
	connect(mWireframeModelingAction, SIGNAL(triggered()), this, SLOT(triggerWireframeModeling()));
	actionList->addAction(mWireframeModelingAction);

	mWireframeModeling2Action = new QAction(QIcon(":images/highgenus_wireframe.png"),tr("Wireframe Modeling 2"),this);
	mWireframeModeling2Action->setCheckable(true);
	sm->registerAction(mWireframeModeling2Action, "High Genus Operations", "");
	mWireframeModeling2Action->setStatusTip(tr("Enter Wireframe Modeling 2 Mode"));
	mWireframeModeling2Action->setToolTip(tr("Wireframe Modeling 2 Mode"));
	connect(mWireframeModeling2Action, SIGNAL(triggered()), this, SLOT(triggerWireframeModeling2()));
	actionList->addAction(mWireframeModeling2Action);

	mColumnModelingAction = new QAction(QIcon(":images/highgenus_column.png"),tr("Column Modeling"),this);
	mColumnModelingAction->setCheckable(true);
	sm->registerAction(mColumnModelingAction, "High Genus Operations", "");
	mColumnModelingAction->setStatusTip(tr("Enter Column Modeling Mode"));
	mColumnModelingAction->setToolTip(tr("Column Modeling Mode"));
	connect(mColumnModelingAction, SIGNAL(triggered()), this, SLOT(triggerColumnModeling()));
	actionList->addAction(mColumnModelingAction);

	mSierpinskyAction = new QAction(QIcon(":images/highgenus_sierpinsky.png"),tr("Sierpinsky"),this);
	mSierpinskyAction->setCheckable(true);
	sm->registerAction(mSierpinskyAction, "High Genus Operations", "");
	mSierpinskyAction->setStatusTip(tr("Enter Sierpinsky Mode"));
	mSierpinskyAction->setToolTip(tr("Sierpinsky Mode"));
	connect(mSierpinskyAction, SIGNAL(triggered()), this, SLOT(triggerSierpinsky()));
	actionList->addAction(mSierpinskyAction);

	mMultiFaceHandleAction = new QAction(QIcon(":images/highgenus_multifacehandle.png"),tr("Multi-face Handle"),this);
	mMultiFaceHandleAction->setCheckable(true);
	sm->registerAction(mMultiFaceHandleAction, "High Genus Operations", "");
	mMultiFaceHandleAction->setStatusTip(tr("Enter Multi-face Handle Mode"));
	mMultiFaceHandleAction->setToolTip(tr("Multi-face Handle Mode"));
	connect(mMultiFaceHandleAction, SIGNAL(triggered()), this, SLOT(triggerMultiFaceHandle()));
	actionList->addAction(mMultiFaceHandleAction);

	mMengerSpongeAction = new QAction(QIcon(":images/highgenus_mengersponge.png"),tr("Menger Sponge"),this);
	mMengerSpongeAction->setCheckable(true);
	sm->registerAction(mMengerSpongeAction, "High Genus Operations", "");
	mMengerSpongeAction->setStatusTip(tr("Enter Menger Sponge Mode"));
	mMengerSpongeAction->setToolTip(tr("Menger Sponge Mode"));
	connect(mMengerSpongeAction, SIGNAL(triggered()), this, SLOT(triggerMengerSponge()));
	actionList->addAction(mMengerSpongeAction);
}

QMenu* HighGenusToolset::getMenu(){
	mHighgenusMenu = new QMenu(tr("High Genus"));

	mHighgenusMenu->addAction(create_torus_tool_->action_);
	mHighgenusMenu->addAction(mAddHoleHandleAction);
	mHighgenusMenu->addAction(mAddHoleHandleCVAction);
	mHighgenusMenu->addAction(mAddHandleSIAction);
	mHighgenusMenu->addAction(mRindModelingScalingAction);
	mHighgenusMenu->addAction(mRindModelingThicknessAction);
	mHighgenusMenu->addAction(mWireframeModelingAction);
	mHighgenusMenu->addAction(mWireframeModeling2Action);
	mHighgenusMenu->addAction(mColumnModelingAction);
	mHighgenusMenu->addAction(mSierpinskyAction);
	mHighgenusMenu->addAction(mMultiFaceHandleAction);
	mHighgenusMenu->addAction(mMengerSpongeAction);

	return mHighgenusMenu;

}

void HighGenusToolset::addActions(QActionGroup *actionGroup, QToolBar *toolBar, QStackedWidget *stackedWidget){

	actionGroup->addAction(create_torus_tool_->action_);
	actionGroup->addAction(mAddHoleHandleAction);
	actionGroup->addAction(mAddHoleHandleCVAction);
	actionGroup->addAction(mAddHandleSIAction);
	actionGroup->addAction(mRindModelingScalingAction);
	actionGroup->addAction(mRindModelingThicknessAction);
	actionGroup->addAction(mWireframeModelingAction);
	actionGroup->addAction(mWireframeModeling2Action);
	actionGroup->addAction(mColumnModelingAction);
	actionGroup->addAction(mSierpinskyAction);
	actionGroup->addAction(mMultiFaceHandleAction);
	actionGroup->addAction(mMengerSpongeAction);

	toolBar->addAction(create_torus_tool_->action_);
	toolBar->addAction(mAddHoleHandleAction);
	toolBar->addAction(mAddHoleHandleCVAction);
	toolBar->addAction(mAddHandleSIAction);
	toolBar->addAction(mRindModelingScalingAction);
	toolBar->addAction(mRindModelingThicknessAction);
	toolBar->addAction(mWireframeModelingAction);
	toolBar->addAction(mWireframeModeling2Action);
	toolBar->addAction(mColumnModelingAction);
	toolBar->addAction(mSierpinskyAction);
	toolBar->addAction(mMultiFaceHandleAction);
	toolBar->addAction(mMengerSpongeAction);

	stackedWidget->addWidget(create_torus_tool_->widget_);
	stackedWidget->addWidget(mAddHoleHandleWidget);
	stackedWidget->addWidget(mAddHoleHandleCVWidget);
	stackedWidget->addWidget(mAddHandleSIWidget);
	stackedWidget->addWidget(mRindModelingScalingWidget);
	stackedWidget->addWidget(mRindModelingThicknessWidget);
	stackedWidget->addWidget(mWireframeModelingWidget);
	stackedWidget->addWidget(mWireframeModeling2Widget);
	stackedWidget->addWidget(mColumnModelingWidget);
	stackedWidget->addWidget(mSierpinskyWidget);
	stackedWidget->addWidget(mMultiFaceHandleWidget);
	stackedWidget->addWidget(mMengerSpongeWidget);

}

void HighGenusToolset::triggerAddHoleHandle(){

	((MainWindow*)parent_)->setToolOptions(mAddHoleHandleWidget);
	((MainWindow*)parent_)->setMode(MainWindow::ConnectFaceVertices);
}

void HighGenusToolset::triggerAddHoleHandleCV() {
	((MainWindow*)parent_)->setToolOptions(mAddHoleHandleCVWidget);
	((MainWindow*)parent_)->setMode(MainWindow::ConnectFaces);
}

void HighGenusToolset::triggerAddHandleSI(){

	((MainWindow*)parent_)->setToolOptions(mAddHandleSIWidget);
	((MainWindow*)parent_)->setMode(MainWindow::HermiteConnectFaces);
}

void HighGenusToolset::triggerRindModelingScaling(){

	((MainWindow*)parent_)->setToolOptions(mRindModelingScalingWidget);
	((MainWindow*)parent_)->setMode(MainWindow::SelectFaceLoop);
	// ((MainWindow*)parent_)->setMode(MainWindow::NormalMode);
}

void HighGenusToolset::triggerRindModelingThickness(){

	((MainWindow*)parent_)->setToolOptions(mRindModelingThicknessWidget);
	((MainWindow*)parent_)->setMode(MainWindow::SelectFaceLoop);
}

void HighGenusToolset::triggerWireframeModeling(){

	((MainWindow*)parent_)->setToolOptions(mWireframeModelingWidget);
	((MainWindow*)parent_)->setMode(MainWindow::NormalMode);
}

void HighGenusToolset::triggerWireframeModeling2(){

	((MainWindow*)parent_)->setToolOptions(mWireframeModeling2Widget);
	((MainWindow*)parent_)->setMode(MainWindow::NormalMode);
}

void HighGenusToolset::triggerColumnModeling(){

	((MainWindow*)parent_)->setToolOptions(mColumnModelingWidget);
	((MainWindow*)parent_)->setMode(MainWindow::NormalMode);
}

void HighGenusToolset::triggerSierpinsky(){

	((MainWindow*)parent_)->setToolOptions(mSierpinskyWidget);
	((MainWindow*)parent_)->setMode(MainWindow::NormalMode);
}

void HighGenusToolset::triggerMultiFaceHandle(){

	((MainWindow*)parent_)->setToolOptions(mMultiFaceHandleWidget);
	((MainWindow*)parent_)->setMode(MainWindow::MultiSelectFace);
}

void HighGenusToolset::triggerMengerSponge(){

	((MainWindow*)parent_)->setToolOptions(mMengerSpongeWidget);
	((MainWindow*)parent_)->setMode(MainWindow::NormalMode);
}

void HighGenusToolset::toggleCrustCleanupFlag(int state)
{
	rindModelingThicknessCleanupCheckBox->setChecked(state);
	rindModelingScalingCleanupCheckBox->setChecked(state);

	((MainWindow*)parent_)->toggleCrustCleanupFlag(state);
}

void HighGenusToolset::toggleWireframeSplit(int state){
	wireframeSplitCheckBox->setChecked(state);
	wireframe2SplitCheckBox->setChecked(state);

	((MainWindow*)parent_)->toggleWireframeSplit(state);
}

void HighGenusToolset::setupAddHoleHandle(){

	mAddHoleHandleLayout = new QGridLayout;
	mAddHoleHandleLayout->setVerticalSpacing(1);
	mAddHoleHandleLayout->setHorizontalSpacing(1);
	// mAddHoleHandleLayout->setMargin(0);
	addHoleHandleNumSegmentsLabel = new QLabel(this);
	addHoleHandleNumSegmentsSpinBox = createDoubleSpinBox(mAddHoleHandleLayout, addHoleHandleNumSegmentsLabel, tr("# Segments"), 1, 100, 1, 10, 0, 0,0);
	connect(addHoleHandleNumSegmentsSpinBox, SIGNAL(valueChanged(double)), this, SLOT(numSegmentsValueChanged(double)));

	//addHoleHandleNumSegmentsConnectLabel = new QLabel(this);
	//addHoleHandleNumSegmentsConnectSpinBox = createDoubleSpinBox(mAddHoleHandleLayout, addHoleHandleNumSegmentsConnectLabel, tr("# Segments to\nConnect (-1=all)"), -1, 10, 1, -1, 0, 1,0);
	//connect(addHoleHandleNumSegmentsConnectSpinBox, SIGNAL(valueChanged(double)), this, SLOT(numSegmentsConnectValueChanged(double)));

	addHoleHandlePinching = new QLabel(this);
	addHoleHandlePinchingConnectSpinBox = createDoubleSpinBox(mAddHoleHandleLayout, addHoleHandlePinching, tr("Pinching"), -1, 10, 0.1, 1.0, 3, 2,0);
	connect(addHoleHandlePinchingConnectSpinBox, SIGNAL(valueChanged(double)), this, SLOT(changeHoleHandlePinch(double)));

	addHoleHandlePinchingCenter = new QLabel(this);
	addHoleHandlePinchingCenterConnectSpinBox = createDoubleSpinBox(mAddHoleHandleLayout, addHoleHandlePinchingCenter, tr("Pinch Center"), 0.1, 1, 0.1, 0.5, 3, 3,0);
	connect(addHoleHandlePinchingCenterConnectSpinBox, SIGNAL(valueChanged(double)), this, SLOT(changeHoleHandlePinchCenter(double)));

	addHoleHandlePinchingWidth = new QLabel(this);
	addHoleHandlePinchingWidthConnectSpinBox = createDoubleSpinBox(mAddHoleHandleLayout, addHoleHandlePinchingWidth, tr("Pinch Width"), 0.001, 10, 0.1, 1.0, 3, 4,0);
	connect(addHoleHandlePinchingWidthConnectSpinBox, SIGNAL(valueChanged(double)), this, SLOT(changeHoleHandlePinchWidth(double)));

	mAddHoleHandleLayout->setRowStretch(6,1);
	mAddHoleHandleLayout->setColumnStretch(2,1);
	mAddHoleHandleWidget->setWindowTitle(tr("Add Hole/Handle"));
	mAddHoleHandleWidget->setLayout(mAddHoleHandleLayout);
}

//slot for num segments to reset the max segments range
void HighGenusToolset::numSegmentsValueChanged(double value){

	((MainWindow*)parent_)->changeNumSegments(value);

	addHoleHandleNumSegmentsSpinBox->setValue(value);
	addHoleHandleCVNumSegmentsSpinBox->setValue(value);
	addHandleSINumSegmentsSpinBox->setValue(value);

	//set the # segments to connect range on all three hole/handle panels
	//addHoleHandleNumSegmentsConnectSpinBox->setRange(0,value);
	//addHoleHandleCVNumSegmentsConnectSpinBox->setRange(0,value);
	//addHandleSINumSegmentsConnectSpinBox->setRange(0,value);

	//if (addHoleHandleNumSegmentsConnectSpinBox->value() > value ||
			//addHoleHandleCVNumSegmentsConnectSpinBox->value() > value) {// ||
			//addHandleSINumSegmentsConnectSpinBox->value() > value) {

		// addHoleHandleNumSegmentsConnectSpinBox->setValue(value);
		//addHoleHandleCVNumSegmentsConnectSpinBox->setValue(value);
		//addHandleSINumSegmentsConnectSpinBox->setValue(value);
	//}
}

void HighGenusToolset::ChangeScherkCollinsPinch(double value) {
	((MainWindow*)parent_)->changeScherkCollinsPinch(value);
}
void HighGenusToolset::ChangeScherkCollinsPinchCenter(double value) {
	((MainWindow*)parent_)->changeScherkCollinsPinchCenter(value);
}
void HighGenusToolset::ChangeScherkCollinsPinchWidth(double value) {
	((MainWindow*)parent_)->changeScherkCollinsPinchWidth(value);
}
void HighGenusToolset::ChangeScherkCollinsHoleNumSegments(double value) {
	((MainWindow*)parent_)->changeScherkCollinsHoleNumSegments(value);
}

void HighGenusToolset::ChangeScherkCollinsHoleInitSkip(double value) {
	((MainWindow*)parent_)->changeScherkCollinsHoleInitSkip(value);
}

void HighGenusToolset::ChangeScherkCollinsHoleSkip(double value) {
	((MainWindow*)parent_)->changeScherkCollinsHoleSkip(value);
}

void HighGenusToolset::ChangeScherkCollinsHoleTwist(double value) {
	((MainWindow*)parent_)->changeScherkCollinsHoleTwist(value);
}

void HighGenusToolset::ChangeScherkCollinsHoleSegSkip(double value) {
	((MainWindow*)parent_)->changeScherkCollinsHoleSegSkip(value);
}


//slot for num segments to set the max segments
void HighGenusToolset::numSegmentsConnectValueChanged(double value){

	((MainWindow*)parent_)->changeMaxSegments(value);

	// addHoleHandleNumSegmentsConnectSpinBox->setValue(value);
	//addHoleHandleCVNumSegmentsConnectSpinBox->setValue(value);
	//addHandleSINumSegmentsConnectSpinBox->setValue(value);
}

//slot for change hold/handle pinch amount
void HighGenusToolset::changeHoleHandlePinch(double value){
	((MainWindow*)parent_)->changeHoleHandlePinchValue(value);
}
//slot for change hold/handle pinch amount
void HighGenusToolset::changeHoleHandlePinchCenter(double value){

	((MainWindow*)parent_)->changeHoleHandlePinchCenterValue(value);
}
//slot for change hold/handle pinch amount
void HighGenusToolset::changeHoleHandlePinchWidth(double value){

	((MainWindow*)parent_)->changeHoleHandlePinchWidthValue(value);
}

void HighGenusToolset::setupAddHoleHandleCV(){

	mAddHoleHandleCVLayout = new QGridLayout;
	// mAddHoleHandleCVLayout->setMargin(0);
	mAddHoleHandleCVLayout->setVerticalSpacing(1);
	mAddHoleHandleCVLayout->setHorizontalSpacing(1);

	addHoleHandleCVNumSegmentsLabel = new QLabel(this);
	addHoleHandleCVNumSegmentsSpinBox = createDoubleSpinBox(mAddHoleHandleCVLayout, addHoleHandleCVNumSegmentsLabel, tr("# Segments"), 1, 100, 1, 10, 0, 0,0);
	connect(addHoleHandleCVNumSegmentsSpinBox, SIGNAL(valueChanged(double)), this, SLOT(numSegmentsValueChanged(double)));

	//addHoleHandleCVNumSegmentsConnectLabel = new QLabel(this);
	//addHoleHandleCVNumSegmentsConnectSpinBox = createDoubleSpinBox(mAddHoleHandleCVLayout, addHoleHandleCVNumSegmentsConnectLabel, tr("# Segments to\nConnect (-1=all)"), 0, 10, 1, -1, 0, 1,0);
	//connect(addHoleHandleCVNumSegmentsConnectSpinBox, SIGNAL(valueChanged(double)), this, SLOT(numSegmentsConnectValueChanged(double)));

	mAddHoleHandleCVLayout->setRowStretch(4,1);
	mAddHoleHandleCVLayout->setColumnStretch(2,1);
	mAddHoleHandleCVWidget->setWindowTitle(tr("Add Hole/Handle (Closest Vertex)"));
	mAddHoleHandleCVWidget->setLayout(mAddHoleHandleCVLayout);
}

void HighGenusToolset::setupAddHandleSI(){

	mAddHandleSILayout = new QGridLayout;
	// mAddHandleSILayout->setMargin(0);
	mAddHandleSILayout->setVerticalSpacing(1);
	mAddHandleSILayout->setHorizontalSpacing(1);

	//number of segments
	addHandleSINumSegmentsLabel = new QLabel(this);
	addHandleSINumSegmentsSpinBox = createDoubleSpinBox(mAddHandleSILayout, addHandleSINumSegmentsLabel, tr("# Segments"), 1, 100, 1, 10, 0, 0,0);
	connect(addHandleSINumSegmentsSpinBox, SIGNAL(valueChanged(double)), this, SLOT(numSegmentsValueChanged(double)));

	//number of segments to connect
  /*
	addHandleSINumSegmentsConnectLabel = new QLabel(this);
	addHandleSINumSegmentsConnectSpinBox = createDoubleSpinBox(mAddHandleSILayout, addHandleSINumSegmentsConnectLabel, tr("# Segments to\nConnect (-1=all)"), 0, 10, 1, -1, 0, 1,0);
	connect(addHoleHandleNumSegmentsConnectSpinBox, SIGNAL(valueChanged(double)), this, SLOT(numSegmentsConnectValueChanged(double)));
  */
	//weight 1
	addHandleSIWeight1Label = new QLabel(this);
	addHandleSIWeight1SpinBox = createDoubleSpinBox(mAddHandleSILayout, addHandleSIWeight1Label, tr("Weight 1"), -100, 100, 0.1, 25.0, 3, 2,0);
	connect(addHandleSIWeight1SpinBox, SIGNAL(valueChanged(double)), ((MainWindow*)parent_), SLOT(changeWeight1(double)));
	//symmetric weights checkbox
	addHandleSISymmetricWeightsCheckBox = new QCheckBox(tr("Symmetric Weights"),this);
	addHandleSISymmetricWeightsCheckBox->setChecked(Qt::Checked);
	connect(addHandleSISymmetricWeightsCheckBox, SIGNAL(stateChanged(int)), this, SLOT(toggleSymmetricWeightsFlag(int)));
	mAddHandleSILayout->addWidget(addHandleSISymmetricWeightsCheckBox,3,0,1,2);
	//weight 2 - must be disabled when the checkbox is unchecked...
	addHandleSIWeight2Label = new QLabel(this);
	addHandleSIWeight2SpinBox = createDoubleSpinBox(mAddHandleSILayout, addHandleSIWeight2Label, tr("Weight 2"), -100, 100, 0.1, 25.0, 3, 4,0);
	addHandleSIWeight2SpinBox->setEnabled(false);
	connect(addHandleSIWeight2SpinBox, SIGNAL(valueChanged(double)), ((MainWindow*)parent_), SLOT(changeWeight2(double)));

	//add twists?
	addHandleSITwistsConnectLabel = new QLabel(this);
	addHandleSITwistsConnectSpinBox = createDoubleSpinBox(mAddHandleSILayout, addHandleSITwistsConnectLabel, tr("Extra Twists"), 0, 100, 1, 0, 0, 5,0);
	connect(addHandleSITwistsConnectSpinBox, SIGNAL(valueChanged(double)), ((MainWindow*)parent_), SLOT(changeExtraTwists(double)));

	//pinching controls
	addHandleSIPinchConnectLabel = new QLabel(this);
	addHandleSIPinchConnectSpinBox = createDoubleSpinBox(mAddHandleSILayout, addHandleSIPinchConnectLabel, tr("Pinching"), -1, 10, 0.1, 1.0, 3, 6,0);
	connect(addHandleSIPinchConnectSpinBox, SIGNAL(valueChanged(double)), ((MainWindow*)parent_), SLOT(changePinch(double)));

	//pinching center
	addHandleSIPinchCenterConnectLabel = new QLabel(this);
	addHandleSIPinchCenterConnectSpinBox = createDoubleSpinBox(mAddHandleSILayout, addHandleSIPinchCenterConnectLabel, tr("Pinch Center"), 0.001, 0.999, 0.05, 0.5, 3, 7,0);
	connect(addHandleSIPinchCenterConnectSpinBox, SIGNAL(valueChanged(double)), ((MainWindow*)parent_), SLOT(changePinchCenter(double)));

	//bubble controls
	addHandleSIBubbleConnectLabel = new QLabel(this);
	addHandleSIBubbleConnectSpinBox = createDoubleSpinBox(mAddHandleSILayout, addHandleSIBubbleConnectLabel, tr("Pinch Width"), 0.001, 10.0, 0.1, 1.0, 3, 8,0);
	connect(addHandleSIBubbleConnectSpinBox, SIGNAL(valueChanged(double)), ((MainWindow*)parent_), SLOT(changeBubble(double)));

	addHandleTriangulateNewFacesCheckBox = new QCheckBox(tr("Triangulate New Faces"), this);
	connect(addHandleTriangulateNewFacesCheckBox, SIGNAL(stateChanged(int)), this,
          SLOT(toggleTriangulateFace(int)));
	mAddHandleSILayout->addWidget(addHandleTriangulateNewFacesCheckBox, 9, 0, 1, 2);

	addHandleSIScherkCollinsCheckBox = new QCheckBox(tr("Scherk Collins"), this);
	connect(addHandleSIScherkCollinsCheckBox, SIGNAL(stateChanged(int)), this,
          SLOT(toggleScherkCollins(int)));
	mAddHandleSILayout->addWidget(addHandleSIScherkCollinsCheckBox, 10, 0, 1, 2);

	QLabel *addHandleSIPinchLabel = new QLabel(this);
	addHandleSIPinchSpinBox = createDoubleSpinBox(
      mAddHandleSILayout, addHandleSIPinchLabel,
      tr("Pinch"), -1, 10, 0.1, 1.0, 2, 11, 0);
	connect(addHandleSIPinchSpinBox, SIGNAL(valueChanged(double)),
          this, SLOT(ChangeScherkCollinsPinch(double)));

	QLabel *addHandleSIPinchCenterLabel = new QLabel(this);
	addHandleSIPinchCenterSpinBox = createDoubleSpinBox(
      mAddHandleSILayout, addHandleSIPinchCenterLabel,
      tr("Pinch Center"), 0.1, 1, 0.1, 0.5, 3, 12, 0);
	connect(addHandleSIPinchCenterSpinBox, SIGNAL(valueChanged(double)),
          this, SLOT(ChangeScherkCollinsPinchCenter(double)));

	QLabel *addHandleSIPinchWidthLabel = new QLabel(this);
	addHandleSIPinchWidthSpinBox = createDoubleSpinBox(
      mAddHandleSILayout, addHandleSIPinchWidthLabel,
      tr("Pinch Width"), 0.001, 10, 0.1, 1.0, 3, 13, 0);
	connect(addHandleSIPinchWidthSpinBox, SIGNAL(valueChanged(double)),
          this, SLOT(ChangeScherkCollinsPinchWidth(double)));

	QLabel *addHandleSIHoleNumSegmentsLabel = new QLabel(this);
	addHandleSIHoleNumSegmentsSpinBox = createDoubleSpinBox(
      mAddHandleSILayout, addHandleSIHoleNumSegmentsLabel,
      tr("#segs in holes"), 1, 10, 1, 2.0, 0, 14, 0);
	connect(addHandleSIHoleNumSegmentsSpinBox, SIGNAL(valueChanged(double)),
          this, SLOT(ChangeScherkCollinsHoleNumSegments(double)));

	QLabel *addHandleSIHoleInitSkipLabel = new QLabel(this);
	addHandleSIHoleInitSkipSpinBox = createDoubleSpinBox(
      mAddHandleSILayout, addHandleSIHoleInitSkipLabel,
      tr("Init skip"), 0, 10, 1, 1.0, 0, 15, 0);
	connect(addHandleSIHoleInitSkipSpinBox, SIGNAL(valueChanged(double)),
          this, SLOT(ChangeScherkCollinsHoleInitSkip(double)));

	QLabel *addHandleSIHoleSkipLabel = new QLabel(this);
	addHandleSIHoleSkipSpinBox = createDoubleSpinBox(
      mAddHandleSILayout, addHandleSIHoleSkipLabel,
      tr("Skip"), 0, 10, 1, 0.0, 0, 16, 0);
	connect(addHandleSIHoleSkipSpinBox, SIGNAL(valueChanged(double)),
          this, SLOT(ChangeScherkCollinsHoleSkip(double)));

	QLabel *addHandleSIHoleTwistLabel = new QLabel(this);
	addHandleSIHoleTwistSpinBox = createDoubleSpinBox(
      mAddHandleSILayout, addHandleSIHoleTwistLabel,
      tr("Twist of holes"), 0, 10, 1, 1.0, 0, 17, 0);
	connect(addHandleSIHoleTwistSpinBox, SIGNAL(valueChanged(double)),
          this, SLOT(ChangeScherkCollinsHoleTwist(double)));

	QLabel *addHandleSIHoleSegSkipLabel = new QLabel(this);
	addHandleSIHoleSegSkipSpinBox = createDoubleSpinBox(
      mAddHandleSILayout, addHandleSIHoleSegSkipLabel,
      tr("Skip in segments"), 0, 10, 1, 0.0, 0, 18, 0);
	connect(addHandleSIHoleSegSkipSpinBox, SIGNAL(valueChanged(double)),
          this, SLOT(ChangeScherkCollinsHoleSegSkip(double)));


	mAddHandleSILayout->setRowStretch(18,1);
	mAddHandleSILayout->setColumnStretch(2,1);
	mAddHandleSIWidget->setWindowTitle(tr("Add Handle (Shape Interpolation)"));
	mAddHandleSIWidget->setLayout(mAddHandleSILayout);

}
void HighGenusToolset::toggleTriangulateFace(int state){
	((MainWindow*)parent_)->toggleTriangulateNewFaces(state);
  if ((bool)state) {
    addHandleSIScherkCollinsCheckBox->setChecked(Qt::Unchecked);
  }
}

void HighGenusToolset::toggleScherkCollins(int state){
	((MainWindow*)parent_)->toggleScherkCollins(state);
  if ((bool)state) {
    addHandleTriangulateNewFacesCheckBox->setChecked(Qt::Unchecked);
  }
}
void HighGenusToolset::toggleSymmetricWeightsFlag(int state){

	((MainWindow*)parent_)->toggleSymmetricWeightsFlag(state);

	if (state) addHandleSIWeight2SpinBox->setEnabled(false);
	else addHandleSIWeight2SpinBox->setEnabled(true);
}

void HighGenusToolset::retranslateUi(){

}



#ifndef REMESHING_TOOLSET_H_
#define REMESHING_TOOLSET_H_

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>

#include "../MainWindow.h"

class MainWindow;

/*!
	\file RemeshingToolset.h
	\brief Definition of the RemeshingToolset class

	\see RemeshingToolset
*/

class RemeshingToolset: public QWidget {
	Q_OBJECT

public:
	RemeshingMode(QWidget *parent, QShortcutManager *sm, QWidget *actionList);
	void addActions(QActionGroup *actionGroup, QToolBar *toolBar, QStackedWidget *stackedWidget);
	QMenu *getMenu();
	void retranslateUi();

		//dual
	QGridLayout *mDualLayout;
	QWidget *mDualWidget;
	QAction *mDualAction;

	//three conversion
	QWidget *mRootThreeWidget;
	QWidget *mTriangulateWidget;
	QWidget *mDualVertexTruncationWidget;
	QWidget *mStellationWidget;
	QWidget *mDoubleStellationWidget;
	QWidget *mTwelveSixFourWidget;
	QWidget *mHoneycombWidget;
	QWidget *mVertexTruncationWidget;
	QWidget *mDualTwelveSixFourWidget;

	QGridLayout *mRootThreeLayout;
	QGridLayout *mTriangulateLayout;
	QGridLayout *mDualVertexTruncationLayout;
	QGridLayout *mStellationLayout;
	QGridLayout *mDoubleStellationLayout;
	QGridLayout *mTwelveSixFourLayout;
	QGridLayout *mHoneycombLayout;
	QGridLayout *mVertexTruncationLayout;
	QGridLayout *mDualTwelveSixFourLayout;

	QAction *mRootThreeAction;
	QAction *mTriangulateAction;
	QAction *mDualVertexTruncationAction;
	QAction *mStellationAction;
	QAction *mDoubleStellationAction;
	QAction *mTwelveSixFourAction;
	QAction *mHoneycombAction;
	QAction *mVertexTruncationAction;
	QAction *mDualTwelveSixFourAction;

	//four conversion
	QWidget *mLinearVertexWidget;
	QWidget *mCatmullClarkWidget;
	QWidget *mStellateEdgeRemovalWidget;
	QWidget *mDooSabinWidget;
	QWidget *mCornerCuttingWidget;
	QWidget *mModifiedCornerCuttingWidget;
	QWidget *mSimplestWidget;

	QGridLayout *mLinearVertexLayout;
	QGridLayout *mCatmullClarkLayout;
	QGridLayout *mStellateEdgeRemovalLayout;
	QGridLayout *mDooSabinLayout;
	QGridLayout *mCornerCuttingLayout;
	QGridLayout *mModifiedCornerCuttingLayout;
	QGridLayout *mSimplestLayout;

	QAction *mLinearVertexAction;
	QAction *mCatmullClarkAction;
	QAction *mStellateEdgeRemovalAction;
	QAction *mDooSabinAction;
	QAction *mCornerCuttingAction;
	QAction *mModifiedCornerCuttingAction;
	QAction *mSimplestAction;


	//five conversion
	QWidget *mPentagonalizationWidget;
  QWidget *mCubicPentagonalizationWidget;
  QWidget *mDualPentagonalizationWidget;

	QGridLayout *mPentagonalizationLayout;
  QGridLayout *mCubicPentagonalizationLayout;
  QGridLayout *mDualPentagonalizationLayout;

	QAction *mPentagonalizationAction;
  QAction *mCubicPentagonalizationAction;
  QAction *mDualPentagonalizationAction;

	//three preservation
	QWidget *mLoopStyleRemeshingWidget;
  QWidget *mLoopSubdivisionWidget;
  QWidget *mDualLoopStyleRemeshingWidget;
  QWidget *mDualLoopSubdivisionWidget;

	QGridLayout *mLoopStyleRemeshingLayout;
  QGridLayout *mLoopSubdivisionLayout;
  QGridLayout *mDualLoopStyleRemeshingLayout;
  QGridLayout *mDualLoopSubdivisionLayout;

	QAction *mLoopStyleRemeshingAction;
  QAction *mLoopSubdivisionAction;
  QAction *mDualLoopStyleRemeshingAction;
  QAction *mDualLoopSubdivisionAction;

	//four preservation
  QWidget *mGlobalExtrudeWidget;
  QWidget *mCheckerboardWidget;
  QWidget *mDualGlobalExtrudeWidget;
  QWidget *mDualCheckerboardWidget;

  QGridLayout *mGlobalExtrudeLayout;
  QGridLayout *mCheckerboardLayout;
  QGridLayout *mDualGlobalExtrudeLayout;
  QGridLayout *mDualCheckerboardLayout;

  QAction *mGlobalExtrudeAction;
  QAction *mCheckerboardAction;
  QAction *mDualGlobalExtrudeAction;
  QAction *mDualCheckerboardAction;

	//five preservation
	QWidget *mPentagonPreservingWidget;
  QWidget *mDualPentagonPreservingWidget;

	QGridLayout *mPentagonPreservingLayout;
  QGridLayout *mDualPentagonPreservingLayout;

	QAction *mPentagonPreservingAction;
  QAction *mDualPentagonPreservingAction;

	//six preservation
	QWidget *mDualLoopStyleRemeshingSixWidget;
  QWidget *mLoopStyleRemeshingSixWidget;

	QGridLayout *mDualLoopStyleRemeshingSixLayout;
  QGridLayout *mLoopStyleRemeshingSixLayout;

	QAction *mDualLoopStyleRemeshingSixAction;
  QAction *mLoopStyleRemeshingSixAction;

	//miscellaneous
	QWidget *mFractalWidget;
  QWidget *mDoubleStellateMiscWidget;
  QWidget *mDooSabinBCWidget;
  QWidget *mDooSabinBCNewWidget;
  QWidget *mDomeWidget;
  QWidget *mSubdivideFaceWidget;

	QGridLayout *mFractalLayout;
  QGridLayout *mDoubleStellateMiscLayout;
  QGridLayout *mDooSabinBCLayout;
  QGridLayout *mDooSabinBCNewLayout;
  QGridLayout *mDomeLayout;
  QGridLayout *mSubdivideFaceLayout;

	QAction *mFractalAction;
  QAction *mDoubleStellateMiscAction;
  QAction *mDooSabinBCAction;
  QAction *mDooSabinBCNewAction;
  QAction *mDomeAction;
  QAction *mSubdivideFaceAction;

protected:
	void setupDual();
	void setupThreeConversion();
	void setupFourConversion();
	void setupFiveConversion();
	void setupThreePreservation();
	void setupFourPreservation();
	void setupFivePreservation();
	void setupSixPreservation();
	void setupMiscellaneous();

	QDoubleSpinBox *createDoubleSpinBox(QGridLayout *layout, QLabel *label, QString s, double low, double high, double step, double value, double decimals, int row, int col);

public slots:

	void triggerDual();

	void triggerRootThree();
	void triggerTriangulate();
	void triggerDualVertexTruncation();
	void triggerStellation();
	void triggerDoubleStellation();
	void triggerTwelveSixFour();
	void triggerHoneycomb();
	void triggerVertexTruncation();
	void triggerDualTwelveSixFour();

	void triggerLinearVertex();
	void triggerCatmullClark();
	void triggerStellateEdgeRemoval();
	void triggerDooSabin();
	void triggerCornerCutting();
	void triggerModifiedCornerCutting();
	void triggerSimplest();

	void triggerPentagonalization();
	void triggerCubicPentagonalization();
	void triggerDualPentagonalization();

	void triggerLoopStyleRemeshing();
	void triggerLoopSubdivision();
	void triggerDualLoopStyleRemeshing();
	void triggerDualLoopSubdivision();

	void triggerGlobalExtrude();
	void triggerCheckerboard();
	void triggerDualGlobalExtrude();
	void triggerDualCheckerboard();

	void triggerPentagonPreserving();
	void triggerDualPentagonPreserving();

	void triggerDualLoopStyleRemeshingSix();
	void triggerLoopStyleRemeshingSix();

	void triggerFractal();
	void triggerDoubleStellateMisc();
	void triggerDooSabinBC();
	void triggerDooSabinBCNew();
	void triggerDome();
	void triggerSubdivideFace();

private:

	QWidget *parent_;

	QMenu *mRemeshingMenu;
	QMenu *mThreeConversionMenu;
	QMenu *mFourConversionMenu;
	QMenu *mFiveConversionMenu;
	QMenu *mThreePreservationMenu;
	QMenu *mFourPreservationMenu;
	QMenu *mFivePreservationMenu;
	QMenu *mSixPreservationMenu;
	QMenu *mMiscellaneousMenu;

	QDoubleSpinBox *starSpinBox;
	QDoubleSpinBox *twelveSixFourSpinBox;
	QDoubleSpinBox *vertexTruncationSpinBox;
	QDoubleSpinBox *dualTwelveSixFourSpinBox;
	QDoubleSpinBox *pentagonalizationSpinBox;
	QDoubleSpinBox *modifiedCornerCuttingSpinBox;
	QDoubleSpinBox *cubicPentagonalizationSpinBox;
	QDoubleSpinBox *loopStyleRemeshingSpinBox;
	QDoubleSpinBox *dualLoopStyleRemeshingTwistSpinBox;
	QDoubleSpinBox *dualLoopStyleRemeshingWeightSpinBox;
	QDoubleSpinBox *pentagonPreservingSpinBox;
	QDoubleSpinBox *dualLoopStyleRemeshingSixTwistSpinBox;
	QDoubleSpinBox *dualLoopStyleRemeshingSixWeightSpinBox;
	QDoubleSpinBox *loopStyleRemeshingSixSpinBox;
	QDoubleSpinBox *fractalMultiplierSpinBox;
	QDoubleSpinBox *doubleStellateMiscHeightSpinBox;
	QDoubleSpinBox *doubleStellateMiscCurveSpinBox;
	QDoubleSpinBox *dooSabinBCNewScaleSpinBox;
	QDoubleSpinBox *dooSabinBCNewLengthSpinBox;
	QDoubleSpinBox *domeHeightSpinBox;
	QDoubleSpinBox *domeScaleSpinBox;
	QDoubleSpinBox *cornerCuttingAlphaSpinBox;

	QLabel *cornerCuttingAlphaLabel;
	QLabel *starLabel;
	QLabel *twelveSixFourLabel;
	QLabel *vertexTruncationLabel;
	QLabel *dualTwelveSixFourLabel;
	QLabel *pentagonalizationLabel;
	QLabel *modifiedCornerCuttingLabel;
	QLabel *cubicPentagonalizationLabel;
	QLabel *loopStyleRemeshingLabel;
	QLabel *dualLoopStyleRemeshingTwistLabel;
	QLabel *dualLoopStyleRemeshingWeightLabel;
	QLabel *pentagonPreservingLabel;
	QLabel *dualLoopStyleRemeshingSixTwistLabel;
	QLabel *dualLoopStyleRemeshingSixWeightLabel;
	QLabel *loopStyleRemeshingSixLabel;
	QLabel *fractalMultiplierLabel;
	QLabel *doubleStellateMiscHeightLabel;
	QLabel *doubleStellateMiscCurveLabel;
	QLabel *dooSabinBCNewLengthLabel;
	QLabel *dooSabinBCNewScaleLabel;
	QLabel *domeHeightLabel;
	QLabel *domeScaleLabel;

	QCheckBox *dualFasterCheckBox;
	QPushButton *dualCreateButton;
	QPushButton *rootThreeCreateButton;
	QPushButton *triangulateCreateButton;
	QPushButton *dualVertexTruncationButton;
	QPushButton *stellationButton;
	QPushButton *starButton;
	QPushButton *twelveSixFourButton;
	QPushButton *honeycombButton;
	QPushButton *vertexTruncationButton;
	QPushButton *dualTwelveSixFourButton;
	QPushButton *linearVertexCreateButton;
	QPushButton *catmullClarkCreateButton;
	QPushButton *stellateEdgeRemovalCreateButton;
	QCheckBox *dooSabinCheckBox;
	QPushButton *dooSabinCreateButton;
	QPushButton *cornerCuttingCreateButton;
	QPushButton *modifiedCornerCuttingCreateButton;
	QPushButton *simplestCreateButton;
	QPushButton *pentagonalizationCreateButton;
	QPushButton *cubicPentagonalizationCreateButton;
	QPushButton *dualPentagonalizationCreateButton;
	QPushButton *loopStyleRemeshingButton;
	QPushButton *loopSubdivisionCreateButton;
	QPushButton *dualLoopStyleRemeshingButton;
	QPushButton *dualLoopSubdivisionCreateButton;
	QPushButton *globalExtrudeButton;
	QPushButton *checkerboardCreateButton;
	QPushButton *dualGlobalExtrudeButton;
	QPushButton *dualCheckerboardCreateButton;
	QPushButton *pentagonPreservingButton;
	QPushButton *dualPentagonPreservingCreateButton;
	QPushButton *dualLoopStyleRemeshingSixButton;
	QPushButton *loopStyleRemeshingSixButton;
	QPushButton *fractalButton;
	QPushButton *doubleStellateMiscButton;
	QPushButton *dooSabinBCButton;
	QPushButton *dooSabinBCNewButton;
	QPushButton *domeButton;
	QCheckBox *subdivideFaceCheckBox;
	QPushButton *subdivideFaceButton;

};

#endif /* REMESHING_TOOLSET_H_ */

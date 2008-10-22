#include <ctime>
#include <QtGui>
#include <QtOpenGL>
#include "MainWindow.h"

WireframeRendererPtr MainWindow::wired;              	//!< WireframeRenderer Pointer
NormalRendererPtr MainWindow::normal;                	//!< NormalRenderer Pointer
LitRendererPtr MainWindow::lit;                       //!< LitRenderer Pointer
TexturedRendererPtr MainWindow::textured;          		//!< TexturedRenderer Pointer
TexturedLitRendererPtr MainWindow::texturedlit; 			//!< TexturedLitRenderer Pointer
ColorableRendererPtr MainWindow::colorable;		       					//!< ColorableRenderer Pointer

//-- Parameters used in various operations on the DLFL object --//
//-- See header file for explanations --//

// Extrusions
double MainWindow::extrude_dist = 2.0;
double MainWindow::extrude_rot = 0.0;
double MainWindow::extrude_scale = 1.0;
int MainWindow::num_extrusions = 1;
double MainWindow::ds_ex_twist= 0.0;

bool MainWindow::triangulate_new_faces = false;
bool MainWindow::scherk_collins = false;

double MainWindow::scherk_collins_pinch = 1.0;
double MainWindow::scherk_collins_pinch_center = 0.5;
double MainWindow::scherk_collins_pinch_width = 1.0;
int MainWindow::scherk_collins_hole_num_segs = 2;
int MainWindow::scherk_collins_hole_init_skip = 1;
int MainWindow::scherk_collins_hole_skip = 0;
int MainWindow::scherk_collins_hole_twist = 1;
int MainWindow::scherk_collins_hole_seg_skip = 0;



//-- Selection count, used as index into selection lists --//
int MainWindow::num_sel_verts = 0;
int MainWindow::num_sel_edges = 0;
int MainWindow::num_sel_faces = 0;
int MainWindow::num_sel_faceverts = 0;

bool MainWindow::deselect_verts = false;
bool MainWindow::deselect_edges = false;
bool MainWindow::deselect_faces = false;
bool MainWindow::deselect_faceverts = false;

// for face loop selection
DLFLEdgePtr MainWindow::face_loop_start_edge = NULL;
DLFLEdgePtr MainWindow::edge_ring_start_edge = NULL;

//paint bucket static color:
QColor MainWindow::paint_bucket_color = QColor(0.5,0.5,0.5);

MainWindow::MainWindow(char *filename) : object(), mode(NormalMode), undoList(), undoMtlList(), redoList(), redoMtlList(),
																				 undolimit(20), useUndo(true), mIsModified(false), mIsPrimitive(false), mWasPrimitive(false) {

	this->setWindowIcon(QIcon(":/images/topmod.png"));
	//initialize the OpenGL Window GLWidget
	QGLFormat fmt;
	//initialize renderer
	createRenderers();
	setMouseTracking(true);

	active = new GLWidget(500,600, lit, QColor(255,255,255,255),QColor(255,255,255,255) , &object, fmt, this);
	// active->switchTo(VPPersp);
	setRenderer(lit);
	active->redraw();
	active->setMinimumSize(400,400);
	active->setFocusPolicy(Qt::StrongFocus);
	setFocusPolicy(Qt::StrongFocus);
	// active->setResizeEnabled(true);
	//status bar
	mStatusBar = new QStatusBar(this);
	//statusbar is not working!!! it throws off glwidget's pick coordinates.... :(
	setStatusBar(mStatusBar);
	setAttribute(Qt::WA_AcceptDrops, true);
	setWindowFlags(Qt::Window);
	setWindowTitle(tr("newfile[*] - TopMod"));
	setCurrentFile("untitled");
	setCentralWidget( active);
	//store user's desktop size
	QWidget *d = QApplication::desktop();
	int w=d->width();  // returns screen width
	int h=d->height(); // returns screen height

	//Tool options dockwidget must be initialized before setting up the actions
	//the main tool options DockWidget
	mToolOptionsDockWidget = new QDockWidget(tr("Tool Options - Insert Edge"),this);
	// mToolOptionsDockWidget->setFeatures(QDockWidget::DockWidgetFloatable | QDockWidget::DockWidgetMovable /* | QDockWidget::DockWidgetClosable*/);

	mToolOptionsDockWidget->setAllowedAreas(Qt::NoDockWidgetArea);
	mToolOptionsStackedWidget = new QStackedWidget();
	// mToolOptionsDockWidget->hide();
	mToolOptionsDockWidget->setWidget(mToolOptionsStackedWidget);
	mToolOptionsDockWidget->setFloating(true);

	createActions();

	//instantiate toolbars
	mBasicsMode = new BasicsMode(this);
	createToolBars();
	createMenus();

	setExtrusionMode(CubicalExtrude);
	setMode(MainWindow::NormalMode);
}

void MainWindow::createActions() {

	//File Menu Actions
	mNewFileAct = new QAction(/*QIcon(":images/folder.png"),*/tr("&New File..."), this);
	//sm->registerAction(mNewFileAct, "File Menu", "CTRL+N");
	mNewFileAct->setStatusTip(tr("Open a blank file and clear the undo list"));
	connect(mNewFileAct, SIGNAL(triggered()), this, SLOT(newFile()));
	//mActionListWidget->addAction(mNewFileAct);

	mOpenAct = new QAction(QIcon(":images/folder.png"),tr("&Open..."), this);
	//sm->registerAction(mOpenAct, "File Menu", "CTRL+O");
	mOpenAct->setStatusTip(tr("Open an existing file"));
	connect(mOpenAct, SIGNAL(triggered()), this, SLOT(openFile()));
	//mActionListWidget->addAction(mOpenAct);

	mSaveAct = new QAction(QIcon(":images/document-save.png"),tr("&Save"), this);
	//sm->registerAction(mSaveAct, "File Menu", "CTRL+S");
	mSaveAct->setStatusTip(tr("Save the document to disk"));
	connect(mSaveAct, SIGNAL(triggered()), this, SLOT(saveFile()));
	//mActionListWidget->addAction(mSaveAct);

	mSaveAsAct = new QAction(QIcon(":images/document-save-as.png"),tr("Save &As..."), this);
	//sm->registerAction(mSaveAsAct, "File Menu", "CTRL+SHIFT+S");
	mSaveAsAct->setStatusTip(tr("Save the document under a new name"));
	connect(mSaveAsAct, SIGNAL(triggered()), this, SLOT(saveFileAs()));
	//mActionListWidget->addAction(mSaveAsAct);

	mScreenshotViewportAct = new QAction(QIcon(":images/camera-photo.png"),tr("Save Viewport Screenshot..."), this);
	//sm->registerAction(mScreenshotViewportAct, "File Menu", "0");
	mScreenshotViewportAct->setStatusTip(tr("Save a screenshot of the contents of the OpenGL viewport (*.png)"));
	connect(mScreenshotViewportAct, SIGNAL(triggered()), this, SLOT(viewportScreenshot()));
	//mActionListWidget->addAction(mScreenshotViewportAct);

	loadTextureAct = new QAction(tr("Load &Texture..."), this);
	//sm->registerAction(loadTextureAct, "File Menu", "CTRL+L");
	loadTextureAct->setStatusTip(tr("Load Texture from file"));
	connect(loadTextureAct, SIGNAL(triggered()), this, SLOT(load_texture()));
	//mActionListWidget->addAction(loadTextureAct);


	mExitAct = new QAction(tr("E&xit"), this);
	//sm->registerAction(mExitAct, "File Menu", "CTRL+Q");
	mExitAct->setStatusTip(tr("Exit the application"));
	connect(mExitAct, SIGNAL(triggered()), this, SLOT(close()));
	// //mActionListWidget->addAction(mExitAct);

	//Edit Menu Actions
	mDeleteSelectedAct = new QAction(/*QIcon(":images/edit-undo.png"),*/ tr("&Delete Selected"), this);
	//sm->registerAction(mDeleteSelectedAct, "Edit Menu", "Del");
	mDeleteSelectedAct->setStatusTip(tr("Delete Selected"));
	connect(mDeleteSelectedAct, SIGNAL(triggered()), this, SLOT(deleteSelected()));
	//mActionListWidget->addAction(mDeleteSelectedAct);

	mUndoAct = new QAction(QIcon(":images/edit-undo.png"), tr("&Undo"), this);
	//sm->registerAction(mUndoAct, "Edit Menu", "CTRL+Z");
	mUndoAct->setStatusTip(tr("Undo the last operation"));
	connect(mUndoAct, SIGNAL(triggered()), this, SLOT(undo()));
	//mActionListWidget->addAction(mUndoAct);

	mRedoAct = new QAction(QIcon(":images/edit-redo.png"), tr("&Redo"), this);
	//sm->registerAction(mRedoAct, "Edit Menu", "CTRL+SHIFT+Z");
	mRedoAct->setStatusTip(tr("Redo the last operation"));
	connect(mRedoAct, SIGNAL(triggered()), this, SLOT(redo()));
	//mActionListWidget->addAction(mRedoAct);

	mClearUndoListAct = new QAction(tr("&Clear Undo List"), this);
	//sm->registerAction(mClearUndoListAct, "Edit Menu", "CTRL+SHIFT+Z");
	mClearUndoListAct->setStatusTip(tr("Clear the Undo List to free up some memory"));
	connect(mClearUndoListAct, SIGNAL(triggered()), this, SLOT(clearUndoList()));
	//mActionListWidget->addAction(mClearUndoListAct);

	mZoomInAct = new QAction( tr("Zoom In"), this);
	//sm->registerAction(mZoomInAct, "Display", "ALT+=");
	mZoomInAct->setStatusTip(tr("Zoom in on the Model"));
	connect(mZoomInAct, SIGNAL(triggered()), active, SLOT(zoomIn()));
	// //mActionListWidget->addAction(mZoomInAct);

	mZoomOutAct = new QAction( tr("Zoom Out"), this);
	//sm->registerAction(mZoomOutAct, "Display", "ALT+-");
	mZoomOutAct->setStatusTip(tr("Zoom in on the Model"));
	connect(mZoomOutAct, SIGNAL(triggered()), active, SLOT(zoomOut()));

	//Display Menu Actions
	mFullscreenAct = new QAction(QIcon(":images/view-fullscreen.png"),tr("&Full Screen"), this);
	mFullscreenAct->setCheckable(true);
	//sm->registerAction( mFullscreenAct, "Display Menu", "ALT+F");
	mFullscreenAct->setStatusTip(tr("Toggle Full Screen"));
	connect(mFullscreenAct, SIGNAL(triggered()), this, SLOT(toggleFullScreen()) );
	//mActionListWidget->addAction(mFullscreenAct);

	showVerticesAct = new QAction(tr("Show &Vertices"), this);
	showVerticesAct->setCheckable(true);
	//sm->registerAction(showVerticesAct, "Display Menu", "V");
	connect(showVerticesAct, SIGNAL(triggered()), this->getActive(), SLOT(toggleVertices()));
	//mActionListWidget->addAction(showVerticesAct);

	mShowFaceIDsAct = new QAction(tr("Show &Face IDs"), this);
	mShowFaceIDsAct->setCheckable(true);
	//sm->registerAction(mShowFaceIDsAct, "Display Menu", "CTRL+F");
	connect(mShowFaceIDsAct, SIGNAL(triggered()), this->getActive(), SLOT(toggleFaceIDs()));
	//mActionListWidget->addAction(mShowFaceIDsAct);

	mShowEdgeIDsAct = new QAction(tr("Show &Edge IDs"), this);
	mShowEdgeIDsAct->setCheckable(true);
	//sm->registerAction(mShowEdgeIDsAct, "Display Menu", "CTRL+E");
	connect(mShowEdgeIDsAct, SIGNAL(triggered()), this->getActive(), SLOT(toggleEdgeIDs()));
	//mActionListWidget->addAction(mShowEdgeIDsAct);

	mShowVertexIDsAct = new QAction(tr("Show &Vertex IDs"), this);
	mShowVertexIDsAct->setCheckable(true);
	//sm->registerAction(mShowVertexIDsAct, "Display Menu", "CTRL+V");
	connect(mShowVertexIDsAct, SIGNAL(triggered()), this->getActive(), SLOT(toggleVertexIDs()));
	//mActionListWidget->addAction(mShowVertexIDsAct);

	mShowSelectedIDsAct = new QAction(tr("Show &Selected IDs"), this);
	mShowSelectedIDsAct->setCheckable(true);
	//sm->registerAction(mShowSelectedIDsAct, "Display Menu", "SHIFT+D");
	connect(mShowSelectedIDsAct, SIGNAL(triggered()), this->getActive(), SLOT(toggleSelectedIDs()));
	//mActionListWidget->addAction(mShowSelectedIDsAct);

	showSilhouetteAct = new QAction(tr("Show &Silhouette"), this);
	showSilhouetteAct->setCheckable(true);
	//sm->registerAction(showSilhouetteAct, "Display Menu", "S" );
	connect(showSilhouetteAct, SIGNAL(triggered()), this->getActive(), SLOT(toggleSilhouette()));
	//mActionListWidget->addAction(showSilhouetteAct);

	showWireframeAct = new QAction(tr("Show &Wireframe"), this);
	showWireframeAct->setCheckable(true);
	showWireframeAct->setChecked(true);
	//sm->registerAction(showWireframeAct, "Display Menu", "W");
	connect(showWireframeAct, SIGNAL(triggered()), this->getActive(), SLOT(toggleWireframe()));
	//mActionListWidget->addAction(showWireframeAct);

	showCoordinateAxesAct = new QAction(tr("Show &Coordinate Axes"), this);
	showCoordinateAxesAct->setCheckable(true);
	//sm->registerAction(showCoordinateAxesAct, "Display Menu", "X");
	connect(showCoordinateAxesAct, SIGNAL(triggered()), this->getActive(), SLOT(toggleAxes()));
	//mActionListWidget->addAction(showCoordinateAxesAct);

	objectOrientationAct = new QAction(tr("Reverse Object"), this);
	objectOrientationAct->setCheckable(true);
	//sm->registerAction(objectOrientationAct, "Display Menu", "R");
	connect(objectOrientationAct, SIGNAL(triggered()), this->getActive(), SLOT(toggleObjectOrientation()));
	//mActionListWidget->addAction(objectOrientationAct);

	mShowNormalsAct = new QAction(tr("Show &Normals"), this);
	mShowNormalsAct->setCheckable(true);
	//sm->registerAction(mShowNormalsAct, "Display Menu", "N");
	connect(mShowNormalsAct, SIGNAL(triggered()), this->getActive(), SLOT(toggleNormals()));
	//mActionListWidget->addAction(mShowNormalsAct);

	mShowFaceCentroidsAct = new QAction(tr("Show &Face Centroids"), this);
	mShowFaceCentroidsAct->setCheckable(true);
	//sm->registerAction(mShowFaceCentroidsAct, "Display Menu", "C");
	// objectOrienationAct->setStatusTip(tr("Copy the current selection's contents to the "
	connect(mShowFaceCentroidsAct, SIGNAL(triggered()), this->getActive(), SLOT(toggleFaceCentroids()));
	//mActionListWidget->addAction(mShowFaceCentroidsAct);

	showGridAct = new QAction(tr("Show &Grid"), this);
	showGridAct->setCheckable(true);
	showGridAct->setEnabled(false);
	//sm->registerAction(showGridAct, "Display Menu", "G");
	// showGridAct->setStatusTip(tr("Copy the current selection's contents to the "
	connect(showGridAct, SIGNAL(triggered()), getActive(), SLOT(toggleGrid()));
	//mActionListWidget->addAction(showGridAct);

	showHUDAct = new QAction(tr("Show &Heads Up Display"), this);
	showHUDAct->setCheckable(true);
	//sm->registerAction(showHUDAct, "Display Menu", "H");
	showHUDAct->setStatusTip(tr("Show the Heads Up Display"));
	connect(showHUDAct, SIGNAL(triggered()), this->getActive(), SLOT(toggleHUD()));
	//mActionListWidget->addAction(showHUDAct);

	mAntialiasingAct = new QAction(tr("Toggle &Antialiasing"), this);
	mAntialiasingAct->setCheckable(true);
	mAntialiasingAct->setChecked(false);
	//sm->registerAction(mAntialiasingAct, "Display Menu", "K");
	mAntialiasingAct->setStatusTip(tr("Toggle Antialiasing"));
	connect(mAntialiasingAct, SIGNAL(triggered()), this->getActive(), SLOT(toggleAntialiasing()));
	//mActionListWidget->addAction(mAntialiasingAct);
	
	mShowToolOptionsAct = mToolOptionsDockWidget->toggleViewAction();
	mShowToolOptionsAct->setStatusTip( tr("Show the tool options window") );
	//sm->registerAction(mShowToolOptionsAct, "Window Menu", "O");
	//mActionListWidget->addAction(mShowToolOptionsAct);
	
		//Renderer Menu Actions
	wireframeRendererAct = new QAction(tr("&Wireframe Renderer"), this);
	wireframeRendererAct->setCheckable(true);
	//sm->registerAction(wireframeRendererAct, "Renderer Menu", "1");
	wireframeRendererAct->setStatusTip(tr("Switch the current renderer to Wireframe"));
	connect(wireframeRendererAct, SIGNAL(triggered()), this, SLOT(useWireframeRenderer()));
	//mActionListWidget->addAction(wireframeRendererAct);

	normalRendererAct = new QAction(tr("&Normal Renderer"), this);
	normalRendererAct->setCheckable(true);
	//sm->registerAction(normalRendererAct, "Renderer Menu", "2");
	normalRendererAct->setStatusTip(tr("Switch the current renderer to Normal"));
	connect(normalRendererAct, SIGNAL(triggered()), this, SLOT(useNormalRenderer()));
	//mActionListWidget->addAction(normalRendererAct);

	lightedRendererAct = new QAction(tr("&Lighted Renderer"), this);
	lightedRendererAct->setCheckable(true);
	//sm->registerAction(lightedRendererAct, "Renderer Menu", "3");
	lightedRendererAct->setStatusTip(tr("Switch the current renderer to Lighted"));
	connect(lightedRendererAct, SIGNAL(triggered()), this, SLOT(useLightedRenderer()));
	//mActionListWidget->addAction(lightedRendererAct);

	texturedRendererAct = new QAction(tr("&Textured Renderer"), this);
	texturedRendererAct->setCheckable(true);
	//sm->registerAction(texturedRendererAct, "Renderer Menu", "4");
	texturedRendererAct->setStatusTip(tr("Switch the current renderer to Textured"));
	connect(texturedRendererAct, SIGNAL(triggered()), this, SLOT(useTexturedRenderer()));
	//mActionListWidget->addAction(texturedRendererAct);

	texturedLightedAct = new QAction(tr("Te&xtured Lighted Renderer"), this);
	texturedLightedAct->setCheckable(true);
	//sm->registerAction(texturedLightedAct, "Renderer Menu", "5");
	texturedLightedAct->setStatusTip(tr("Switch the current renderer to Textured Lit"));
	connect(texturedLightedAct, SIGNAL(triggered()), this, SLOT(useTexturedLitRenderer()));
	//mActionListWidget->addAction(texturedLightedAct);

	colorableRendererAct = new QAction(tr("&Colorable Renderer"), this);
	colorableRendererAct->setCheckable(true);
	//sm->registerAction(colorableRendererAct, "Renderer Menu", "6");
	colorableRendererAct->setStatusTip(tr("Switch the current renderer to Colorable"));
	connect(colorableRendererAct, SIGNAL(triggered()), this, SLOT(useColorableRenderer()));
	//mActionListWidget->addAction(colorableRendererAct);

	mRendererActionGroup = new QActionGroup(this);
	mRendererActionGroup->setExclusive(true);
	mRendererActionGroup->addAction(wireframeRendererAct);
	mRendererActionGroup->addAction(normalRendererAct);
	mRendererActionGroup->addAction(lightedRendererAct);
	mRendererActionGroup->addAction(texturedRendererAct);
	mRendererActionGroup->addAction(texturedLightedAct);
	mRendererActionGroup->addAction(colorableRendererAct);
	lightedRendererAct->setChecked(true);

	pCubeAct = new QAction(QIcon(":/images/prim_cube.png"), tr("&Cube"), this);
	//sm->registerAction(pCubeAct, "Primitives Menu", "CTRL+1");
	pCubeAct->setStatusTip(tr("Load a Cube"));
	connect(pCubeAct, SIGNAL(triggered()), this, SLOT(loadCube()));
	//mActionListWidget->addAction(pCubeAct);

	pOctahedronAct = new QAction(QIcon(":/images/prim_octahedron.png"), tr("&Octahedron"), this);
	//sm->registerAction(pOctahedronAct, "Primitives Menu", "CTRL+2");
	pOctahedronAct->setStatusTip(tr("Load an octahedron"));
	connect(pOctahedronAct, SIGNAL(triggered()), this, SLOT(loadOctahedron()));
	//mActionListWidget->addAction(pOctahedronAct);

	pTetrahedronAct = new QAction(QIcon(":/images/prim_tetrahedron.png"), tr("&Tetrahedron"), this);
	//sm->registerAction(pTetrahedronAct, "Primitives Menu", "CTRL+3");
	pTetrahedronAct->setStatusTip(tr("Load a tetrahedron"));
	connect(pTetrahedronAct, SIGNAL(triggered()), this, SLOT(loadTetrahedron()));
	//mActionListWidget->addAction(pTetrahedronAct);

	pDodecahedronAct = new QAction(QIcon(":/images/prim_dodecahedron.png"), tr("&Dodecahedron"), this);
	//sm->registerAction(pDodecahedronAct, "Primitives Menu", "CTRL+4");
	pDodecahedronAct->setStatusTip(tr("Load a dodecahedron"));
	connect(pDodecahedronAct, SIGNAL(triggered()), this, SLOT(loadDodecahedron()));
	//mActionListWidget->addAction(pDodecahedronAct);

	pIcosahedronAct = new QAction(QIcon(":/images/prim_icosahedron.png"), tr("&Icosahedron"), this);
	//sm->registerAction(pIcosahedronAct, "Primitives Menu", "CTRL+5");
	pIcosahedronAct->setStatusTip(tr("Load an icosahedron"));
	connect(pIcosahedronAct, SIGNAL(triggered()), this, SLOT(loadIcosahedron()));
	//mActionListWidget->addAction(pIcosahedronAct);

	pSoccerBallAct = new QAction(QIcon(":/images/prim_soccerball.png"), tr("&Soccer ball"), this);
	//sm->registerAction(pSoccerBallAct, "Primitives Menu", "CTRL+6");
	pSoccerBallAct->setStatusTip(tr("Load a soccer ball"));
	connect(pSoccerBallAct, SIGNAL(triggered()), this, SLOT(loadSoccerball()));
	//mActionListWidget->addAction(pSoccerBallAct);

	pGeodesicAct = new QAction(QIcon(":/images/prim_geodesic.png"), tr("&Geodesic Dome"), this);
	//sm->registerAction(pGeodesicAct, "Primitives Menu", "CTRL+7");
	pGeodesicAct->setStatusTip(tr("Load a geodesic dome"));
	connect(pGeodesicAct, SIGNAL(triggered()), this, SLOT(loadGeodesic()));
	//mActionListWidget->addAction(pGeodesicAct);

	// //SELECTION MENU ACTIONS
	mSelectionWindowAct = new QAction(tr("Selection Window"), this);
	//sm->registerAction(mSelectionWindowAct, "Selection", "SHIFT+W");
	connect( mSelectionWindowAct , SIGNAL( triggered() ), this, SLOT( selection_window() ) );
	//mActionListWidget->addAction(mSelectionWindowAct);

	selectVertexAct = new QAction(tr("Select &Vertex"), this);
	//sm->registerAction(selectVertexAct, "Selection", "");
	selectVertexAct->setStatusTip(tr("Select a Vertex"));
	connect(selectVertexAct, SIGNAL(triggered()), this, SLOT(select_vertex()));
	//mActionListWidget->addAction(selectVertexAct);

	selectMultipleVerticesAct = new QAction(tr("Select Multiple Vertices"), this);
	//sm->registerAction(selectMultipleVerticesAct, "Selection", "");
	selectMultipleVerticesAct->setStatusTip(tr("Select multiple vertices"));
	connect(selectMultipleVerticesAct, SIGNAL(triggered()), this, SLOT(select_multiple_vertices()));
	//mActionListWidget->addAction(selectMultipleVerticesAct);

	mSelectMultipleAct = new QAction(tr("Select Multiple"), this);
	//sm->registerAction(mSelectMultipleAct, "Selection", "SHIFT+M");
	mSelectMultipleAct->setStatusTip(tr("Select multiple"));
	connect(mSelectMultipleAct, SIGNAL(triggered()), this, SLOT(select_multiple()));
	//mActionListWidget->addAction(mSelectMultipleAct);

	mEditVertexAct = new QAction(tr("Edit Verte&x"), this);
	//sm->registerAction(mEditVertexAct, "Selection", "");
	mEditVertexAct->setStatusTip(tr("Select and Move Vertices one at a time."));
	connect(mEditVertexAct, SIGNAL(triggered()), this, SLOT(edit_vertex()));
	//mActionListWidget->addAction(mEditVertexAct);

	selectFaceAct = new QAction(tr("Select &Face"), this);
	//sm->registerAction(selectFaceAct, "Selection", "");
	selectFaceAct->setStatusTip(tr("Select a single Face."));
	connect(selectFaceAct, SIGNAL(triggered()), this, SLOT(select_face() ) );
	//mActionListWidget->addAction(selectFaceAct);

	selectFaceLoopAct = new QAction(tr("Select Face Loo&p"), this);
	//sm->registerAction(selectFaceLoopAct, "Selection", "SHIFT+P");
	selectFaceLoopAct->setStatusTip(tr("Select a Face Loop."));
	connect(selectFaceLoopAct, SIGNAL(triggered()), this, SLOT(select_face_loop() ) );
	//mActionListWidget->addAction(selectFaceLoopAct);

	selectMultipleFacesAct = new QAction(tr("Select &Multiple Faces"), this);
	//sm->registerAction(selectMultipleFacesAct, "Selection", "");
	connect( selectMultipleFacesAct , SIGNAL( triggered() ), this, SLOT( select_multiple_faces() ) );
	//mActionListWidget->addAction(selectMultipleFacesAct);

	selectSimilarFacesAct = new QAction(tr("Select &Similar Faces"), this);
	//sm->registerAction(selectSimilarFacesAct, "Selection", "SHIFT+G");
	connect( selectSimilarFacesAct , SIGNAL( triggered() ), this, SLOT( select_similar_faces() ) );
	//mActionListWidget->addAction(selectSimilarFacesAct);

	mSelectSimilarAct = new QAction(tr("Select Similar"), this);
	//sm->registerAction(mSelectSimilarAct, "Selection", "SHIFT+S");
	connect( mSelectSimilarAct , SIGNAL( triggered() ), this, SLOT( select_similar() ) );
	//mActionListWidget->addAction(mSelectSimilarAct);

	selectFacesByAreaAct = new QAction(tr("Select Faces By Surf. Area"), this);
	//sm->registerAction(selectFacesByAreaAct, "Selection", "CTRL+SHIFT+A");
	connect( selectFacesByAreaAct , SIGNAL( triggered() ), this, SLOT( select_faces_by_area() ) );
	//mActionListWidget->addAction(selectFacesByAreaAct);

	selectFacesByColorAct = new QAction(tr("Select Faces By Color"), this);
	//sm->registerAction(selectFacesByColorAct, "Selection", "CTRL+SHIFT+C");
	connect( selectFacesByColorAct , SIGNAL( triggered() ), this, SLOT( select_faces_by_color() ) );
	//mActionListWidget->addAction(selectFacesByColorAct);

	selectCheckerboardFacesAct = new QAction(tr("C&heckerboard Select Faces"), this);
	//sm->registerAction(selectCheckerboardFacesAct, "Selection", "SHIFT+K");
	connect( selectCheckerboardFacesAct , SIGNAL( triggered() ), this, SLOT( select_checkerboard_faces() ) );
	//mActionListWidget->addAction(selectCheckerboardFacesAct);

	selectAllAct = new QAction(tr("Select &All"), this);
	//sm->registerAction(selectAllAct, "Selection", "CTRL+A");
	connect( selectAllAct , SIGNAL( triggered() ), this, SLOT( selectAll() ) );
	//mActionListWidget->addAction(selectAllAct);

	mSelectComponentAct = new QAction(tr("Select Connected Component"), this);
	//sm->registerAction(mSelectComponentAct, "Selection", "*");
	connect( mSelectComponentAct , SIGNAL( triggered() ), this, SLOT( selectComponent() ) );
	//mActionListWidget->addAction(mSelectComponentAct);

	mGrowSelectionAct = new QAction(tr("Grow Selection"), this);
	//sm->registerAction(mGrowSelectionAct, "Selection", "=");
	connect( mGrowSelectionAct , SIGNAL( triggered() ), this, SLOT( growSelection() ) );
	//mActionListWidget->addAction(mGrowSelectionAct);

	mShrinkSelectionAct = new QAction(tr("Shrink Selection"), this);
	//sm->registerAction(mShrinkSelectionAct, "Selection", "-");
	connect( mShrinkSelectionAct , SIGNAL( triggered() ), this, SLOT( shrinkSelection() ) );
	//mActionListWidget->addAction(mShrinkSelectionAct);

	selectInverseAct = new QAction(tr("Select &Inverse"), this);
	//sm->registerAction(selectInverseAct, "Selection", "CTRL+I");
	connect( selectInverseAct , SIGNAL( triggered() ), this, SLOT( selectInverse() ) );
	//mActionListWidget->addAction(selectInverseAct);

	selectEdgeAct = new QAction(tr("Select &Edge"), this);
	//sm->registerAction(selectEdgeAct, "Selection", "");
	selectEdgeAct->setStatusTip(tr("Select one Edge"));
	connect( selectEdgeAct , SIGNAL( triggered() ), this,SLOT( select_edge() ) );
	//mActionListWidget->addAction(selectEdgeAct);

	selectMultipleEdgesAct = new QAction(tr("Select Multiple Edges"), this);
	//sm->registerAction(selectMultipleEdgesAct, "Selection", "");
	selectMultipleEdgesAct->setStatusTip(tr("Select multiple edges"));
	connect( selectMultipleEdgesAct , SIGNAL( triggered() ), this,SLOT( select_multiple_edges() ) );
	//mActionListWidget->addAction(selectMultipleEdgesAct);

	mCollapseSelectedEdgesAct = new QAction(tr("Collapse Selected Edges"), this);
	//sm->registerAction(mCollapseSelectedEdgesAct, "Edit Menu", "ALT+C");
	mCollapseSelectedEdgesAct->setStatusTip(tr("Collapse Selected Edges"));
	connect(mCollapseSelectedEdgesAct, SIGNAL(triggered()), this, SLOT(collapseSelectedEdges()));
	//mActionListWidget->addAction(mCollapseSelectedEdgesAct);

	selectEdgeLoopAct = new QAction(tr("Select Edge &Loop"), this);
	//sm->registerAction(selectEdgeLoopAct, "Selection", "SHIFT+L");
	selectEdgeLoopAct->setStatusTip(tr("Select an Edge Loop"));
	connect( selectEdgeLoopAct , SIGNAL( triggered() ), this,SLOT( select_edge_loop() ) );
	//mActionListWidget->addAction(selectEdgeLoopAct);

	selectEdgeRingAct = new QAction(tr("Select Edge &Ring"), this);
	//sm->registerAction(selectEdgeRingAct, "Selection", "SHIFT+R");
	selectEdgeRingAct->setStatusTip(tr("Select an edge ring."));
	connect(selectEdgeRingAct, SIGNAL(triggered()), this, SLOT(select_edge_ring() ) );
	//mActionListWidget->addAction(selectEdgeRingAct);

	selectCornerAct = new QAction(tr("Select &Corner"), this);
	//sm->registerAction(selectCornerAct, "Selection", "SHIFT+C");
	selectCornerAct->setStatusTip(tr("Select a Corner"));
	connect( selectCornerAct , SIGNAL( triggered() ), this, SLOT( select_corner() ) );
	//mActionListWidget->addAction(selectCornerAct);

	exitSelectionModeAct = new QAction(tr("E&xit Selection Mode"), this);
	//sm->registerAction(exitSelectionModeAct, "Selection", "SHIFT+X");
	connect( exitSelectionModeAct , SIGNAL( triggered() ), this, SLOT( exit_selection_mode() ) );
	//mActionListWidget->addAction(exitSelectionModeAct);

	clearSelectedModeAct = new QAction(tr("&Clear Selected"), this);
	//sm->registerAction(clearSelectedModeAct, "Selection", "Escape");
	connect( clearSelectedModeAct , SIGNAL( triggered() ), this, SLOT( clear_selected() ) );
	//mActionListWidget->addAction(clearSelectedModeAct);

	selectEdgesFromFacesAct = new QAction(tr("Select Edges from Faces"), this);
	//sm->registerAction(selectEdgesFromFacesAct, "Selection", "");
	connect( selectEdgesFromFacesAct , SIGNAL( triggered() ), this, SLOT( selectEdgesFromFaces() ) );
	//mActionListWidget->addAction(selectEdgesFromFacesAct);

	selectEdgesFromVerticesAct = new QAction(tr("Select Edges from Vertices"), this);
	//sm->registerAction(selectEdgesFromVerticesAct, "Selection", "");
	connect( selectEdgesFromVerticesAct , SIGNAL( triggered() ), this, SLOT( selectEdgesFromVertices() ) );
	//mActionListWidget->addAction(selectEdgesFromVerticesAct);

	selectFacesFromEdgesAct = new QAction(tr("Select Faces from Edges"), this);
	//sm->registerAction(selectFacesFromEdgesAct, "Selection", "");
	connect( selectFacesFromEdgesAct , SIGNAL( triggered() ), this, SLOT( selectFacesFromEdges() ) );
	//mActionListWidget->addAction(selectFacesFromEdgesAct);

	selectFacesFromVerticesAct = new QAction(tr("Select Faces from Vertices"), this);
	//sm->registerAction(selectFacesFromVerticesAct, "Selection", "");
	connect( selectFacesFromVerticesAct , SIGNAL( triggered() ), this, SLOT( selectFacesFromVertices() ) );
	//mActionListWidget->addAction(selectFacesFromVerticesAct);

	selectVerticesFromEdgesAct = new QAction(tr("Select Vertices from Edges"), this);
	//sm->registerAction(selectVerticesFromEdgesAct, "Selection", "");
	connect( selectVerticesFromEdgesAct , SIGNAL( triggered() ), this, SLOT( selectVerticesFromEdges() ) );
	//mActionListWidget->addAction(selectVerticesFromEdgesAct);

	selectVerticesFromFacesAct = new QAction(tr("Select Vertices from Faces"), this);
	//sm->registerAction(selectVerticesFromFacesAct, "Selection", "");
	connect( selectVerticesFromFacesAct , SIGNAL( triggered() ), this, SLOT( selectVerticesFromFaces() ) );
	//mActionListWidget->addAction(selectVerticesFromFacesAct);

	//selection masks
	mSelectVerticesMaskAct = new QAction(QIcon(":images/selection-mask-vertices.png"), tr("Select &Vertices"), this);
	mSelectVerticesMaskAct->setCheckable(true);
	//sm->registerAction(mSelectVerticesMaskAct, "Selection", "SHIFT+V");
	mSelectVerticesMaskAct->setStatusTip(tr("Select by Component type: Vertices"));
	connect( mSelectVerticesMaskAct , SIGNAL( triggered() ), this, SLOT( selectionMaskVertices() ) );
	//mActionListWidget->addAction(mSelectVerticesMaskAct);

	mSelectEdgesMaskAct = new QAction(QIcon(":images/selection-mask-edges.png"), tr("Select &Edges"), this);
	mSelectEdgesMaskAct->setCheckable(true);
	//sm->registerAction(mSelectEdgesMaskAct, "Selection", "SHIFT+E");
	mSelectEdgesMaskAct->setStatusTip(tr("Select by Component type: Edges"));
	connect( mSelectEdgesMaskAct , SIGNAL( triggered() ), this, SLOT( selectionMaskEdges() ) );
	//mActionListWidget->addAction(mSelectEdgesMaskAct);

	mSelectFacesMaskAct = new QAction(QIcon(":images/selection-mask-faces.png"), tr("Select &Faces"), this);
	mSelectFacesMaskAct->setCheckable(true);
	//sm->registerAction(mSelectFacesMaskAct, "Selection", "SHIFT+F");
	mSelectFacesMaskAct->setStatusTip(tr("Select by Component type: Faces"));
	connect( mSelectFacesMaskAct , SIGNAL( triggered() ), this, SLOT( selectionMaskFaces() ) );
	//mActionListWidget->addAction(mSelectFacesMaskAct);

	mSelectCornersMaskAct = new QAction(QIcon(":images/selection-mask-corners.png"), tr("Select &Corner"), this);
	mSelectCornersMaskAct->setCheckable(true);
	//sm->registerAction(mSelectCornersMaskAct, "Selection", "");
	mSelectCornersMaskAct->setStatusTip(tr("Select by Component type: Corners"));
	connect( mSelectCornersMaskAct , SIGNAL( triggered() ), this, SLOT( selectionMaskCorners() ) );
	//mActionListWidget->addAction(mSelectCornersMaskAct);

	mSelectionMaskActionGroup = new QActionGroup(this);
	mSelectionMaskActionGroup->setExclusive(true);
	mSelectionMaskActionGroup->addAction(mSelectVerticesMaskAct);
	mSelectionMaskActionGroup->addAction(mSelectFacesMaskAct);
	mSelectionMaskActionGroup->addAction(mSelectEdgesMaskAct);
	mSelectionMaskActionGroup->addAction(mSelectCornersMaskAct);
	// mSelectCornersMaskAct->setChecked(true);

	mPaintSelectedFacesAct = new QAction(tr("Paint Selected Faces"), this);
	mPaintSelectedFacesAct->setStatusTip( tr("Paint all Selected Faces") );
	connect(mPaintSelectedFacesAct, SIGNAL(triggered()), this, SLOT(paintSelectedFaces()));
	//sm->registerAction(mPaintSelectedFacesAct, "Tools Menu", "CTRL+SHIFT+B");
	//mActionListWidget->addAction(mPaintSelectedFacesAct);

	mClearMaterialsAct = new QAction(tr("Clear Materials"), this);
	mClearMaterialsAct->setStatusTip( tr("Clear Materials") );
	connect(mClearMaterialsAct, SIGNAL(triggered()), this, SLOT(clearMaterials()));
	//sm->registerAction(mClearMaterialsAct, "Tools Menu", "CTRL+SHIFT+X");
	//mActionListWidget->addAction(mClearMaterialsAct);

	mSubdivideSelectedFacesAct = new QAction(tr("Subdivide Selected Faces"), this);
	mSubdivideSelectedFacesAct->setStatusTip( tr("Subdivide all Selected Faces") );
	connect(mSubdivideSelectedFacesAct, SIGNAL(triggered()), this, SLOT(subdivideSelectedFaces()));
	//sm->registerAction(mSubdivideSelectedFacesAct, "Tools Menu", "CTRL+B");
	//mActionListWidget->addAction(mSubdivideSelectedFacesAct);

	mSubdivideSelectedEdgesAct = new QAction(tr("Subdivide Selected Edges"), this);
	mSubdivideSelectedEdgesAct->setStatusTip( tr("Subdivide all Selected Edges") );
	connect(mSubdivideSelectedEdgesAct, SIGNAL(triggered()), this, SLOT(subdivideSelectedEdges()));
	//sm->registerAction(mSubdivideSelectedEdgesAct, "Tools Menu", "CTRL+SHIFT+E");
	//mActionListWidget->addAction(mSubdivideSelectedEdgesAct);

	mPerformRemeshingAct = new QAction(tr("Perform Remeshing"), this);
	mPerformRemeshingAct->setStatusTip( tr("Perform the current remeshing scheme") );
	connect(mPerformRemeshingAct, SIGNAL(triggered()), this, SLOT(performRemeshing()));
	//sm->registerAction(mPerformRemeshingAct, "Remeshing Menu", "CTRL+R");
	//mActionListWidget->addAction(mPerformRemeshingAct);

	mPerformExtrusionAct = new QAction(tr("Perform Extrusion"), this);
	mPerformExtrusionAct->setStatusTip( tr("Perform the current extrusion operator on the selected faces") );
	connect(mPerformExtrusionAct, SIGNAL(triggered()), this, SLOT(performExtrusion()));
	//sm->registerAction(mPerformExtrusionAct, "Tools Menu", "CTRL+X");
	//mActionListWidget->addAction(mPerformExtrusionAct);

	mExtrudeMultipleAct = new QAction(tr("Extrude Multiple Faces"), this);
	mExtrudeMultipleAct->setCheckable(true);
	mExtrudeMultipleAct->setChecked(false);
	mExtrudeMultipleAct->setStatusTip( tr("Check this if you want to be able to select multiple faces and then hit CTRL+X to extrude the selected faces") );
	// connect(mExtrudeMultipleAct, SIGNAL(triggered()), this, SLOT(performExtrusion()));
	//sm->registerAction(mExtrudeMultipleAct, "Tools Menu", "M");
	//mActionListWidget->addAction(mExtrudeMultipleAct);

	mAboutAct = new QAction(tr("&About TopMod"), this);
	mAboutAct->setStatusTip( tr("About TopMod") );
	connect(mAboutAct, SIGNAL(triggered()), this, SLOT(about()));
	//sm->registerAction(mAboutAct, "Help Menu", "");
	//mActionListWidget->addAction(mAboutAct);

	mHideToolBarsAct = new QAction(tr("Hide All ToolBars"), this);
	mHideToolBarsAct->setStatusTip( tr("Hide All ToolBars") );
	connect(mHideToolBarsAct, SIGNAL(triggered()), this, SLOT(hideAllToolBars()));
	//sm->registerAction(mHideToolBarsAct, "Window Menu", "T");
	//mActionListWidget->addAction(mHideToolBarsAct);

	mShowToolBarsAct = new QAction(tr("Show All ToolBars"), this);
	mShowToolBarsAct->setStatusTip( tr("Show All ToolBars") );
	connect(mShowToolBarsAct, SIGNAL(triggered()), this, SLOT(showAllToolBars()));
	//sm->registerAction(mShowToolBarsAct, "Window Menu", "SHIFT+T");
	//mActionListWidget->addAction(mShowToolBarsAct);

}

void MainWindow::createMenus(){
#ifdef __APPLE__
	menuBar = new QMenuBar(0);
	setMenuBar(menuBar);
	// setUnifiedTitleAndToolBarOnMac(true);
#else
	menuBar = new QMenuBar(this);
	setMenuBar(menuBar);
#endif

	mFileMenu = new QMenu(tr("&File"));
	menuBar->addMenu(mFileMenu);
	mFileMenu->setTearOffEnabled(true);

	mNewMenu = new QMenu(tr("&New"));
	mNewMenu->setTearOffEnabled(true);
	mFileMenu->addMenu(mNewMenu);
	mNewMenu->addAction(mNewFileAct);
	mNewMenu->addAction(pCubeAct);
	mNewMenu->addAction(pOctahedronAct);
	mNewMenu->addAction(pTetrahedronAct);
	mNewMenu->addAction(pDodecahedronAct);
	mNewMenu->addAction(pIcosahedronAct);
	mNewMenu->addAction(pSoccerBallAct);
	mNewMenu->addAction(pGeodesicAct);
	// mFileMenu->addAction(mNewFileAct);
	mFileMenu->addAction(mOpenAct);
	mFileMenu->addAction(mSaveAct);
	mFileMenu->addAction(mSaveAsAct);
	mFileMenu->addAction(mScreenshotViewportAct);
	mFileMenu->addSeparator();
	mFileMenu->addAction(loadTextureAct);
	// mFileMenu->addAction(printInfoAct);
	// mFileMenu->addAction(printFaceListAct);
	// mFileMenu->addAction(printVertexListAct);
	// mFileMenu->addAction(printEdgeListAct);
	// mFileMenu->addAction(mPrintCVListAct);
	mFileMenu->addSeparator();
	mFileMenu->addAction(mExitAct);

	mEditMenu = new QMenu(tr("&Edit"));
	menuBar->addMenu(mEditMenu);
	mEditMenu->addAction(mDeleteSelectedAct);
	mEditMenu->addSeparator();
	mEditMenu->addAction(mUndoAct);
	mEditMenu->addAction(mRedoAct);
	mEditMenu->setTearOffEnabled(true);
	mEditMenu->addSeparator();
	mEditMenu->addAction(mClearUndoListAct);
	mEditMenu->addSeparator();
	//mEditMenu->addAction(mPreferencesAct);

	mDisplayMenu = new QMenu(tr("&Display"));
	mDisplayMenu->setTearOffEnabled(true);
	menuBar->addMenu(mDisplayMenu);

	mRendererMenu = new QMenu(tr("&Renderer"));
	mRendererMenu->setTearOffEnabled(true);
	// mRendererMenu->addAction(planarModelingAct);
	// mRendererMenu->addAction(polygonalModelingAct);
	// menuBar->addMenu(rendererMenu);
	mDisplayMenu->addMenu(mRendererMenu);
	mRendererMenu->addAction(wireframeRendererAct);
	mRendererMenu->addAction(normalRendererAct);
	mRendererMenu->addAction(lightedRendererAct);
	mRendererMenu->addAction(texturedRendererAct);
	// texturedRendererAct->setEnabled(false);
	mRendererMenu->addAction(texturedLightedAct);
	// texturedLightedAct->setEnabled(false);
	mRendererMenu->addSeparator()->setText(tr("Special Mode??"));
	mRendererMenu->addAction(colorableRendererAct);

	//mDisplayMenu->addAction(mPerspViewAct);
	mDisplayMenu->addAction(showVerticesAct);
	//ID display submenu
	mShowIDsMenu = new QMenu(tr("&Show IDs"));
	mDisplayMenu->addMenu(mShowIDsMenu);
	mShowIDsMenu->setTearOffEnabled(true);
	mShowIDsMenu->addAction(mShowFaceIDsAct);
	mShowIDsMenu->addAction(mShowEdgeIDsAct);
	mShowIDsMenu->addAction(mShowVertexIDsAct);
	mShowIDsMenu->addAction(mShowSelectedIDsAct);
	//more view options
	mDisplayMenu->addAction(showSilhouetteAct);
	mDisplayMenu->addAction(showWireframeAct);
	mDisplayMenu->addAction(showCoordinateAxesAct);
	// mDisplayMenu->addAction(showGridAct); //removed for now
	mDisplayMenu->addAction(showHUDAct);
	mDisplayMenu->addAction(mAntialiasingAct);
	mDisplayMenu->addAction(objectOrientationAct);
	mDisplayMenu->addAction(mShowNormalsAct);
	mDisplayMenu->addAction(mShowFaceCentroidsAct);
	mDisplayMenu->addAction(mFullscreenAct);
	mDisplayMenu->addAction(mZoomInAct);
	mDisplayMenu->addAction(mZoomOutAct);

	mPrimitivesMenu = new QMenu(tr("&Primitives"));
	mPrimitivesMenu->setTearOffEnabled(true);
	menuBar->addMenu(mPrimitivesMenu);
	mPrimitivesMenu->addAction(pCubeAct);
	mPrimitivesMenu->addAction(pOctahedronAct);
	mPrimitivesMenu->addAction(pTetrahedronAct);
	mPrimitivesMenu->addAction(pDodecahedronAct);
	mPrimitivesMenu->addAction(pIcosahedronAct);
	mPrimitivesMenu->addAction(pSoccerBallAct);
	mPrimitivesMenu->addAction(pGeodesicAct);

	mSelectionMenu = new QMenu(tr("&Selection"));
	menuBar->addMenu(mSelectionMenu);
	mSelectionMenu->addAction(selectAllAct);
	mSelectionMenu->addAction(selectInverseAct);
	mSelectionMenu->addAction(mSelectMultipleAct);
	mSelectionMenu->addAction(mSelectSimilarAct);
	mSelectionMenu->addAction(mSelectionWindowAct);
	mSelectionMenu->addAction(mSelectComponentAct);
	mSelectionMenu->addAction(mGrowSelectionAct);
	mSelectionMenu->addAction(mShrinkSelectionAct);
	// mSelectionMenu->addAction(exitSelectionModeAct);
	mSelectionMenu->addAction(clearSelectedModeAct);
	mSelectionMenu->addSeparator();
	// mSelectionMenu->addAction(selectEdgeAct);
	// mSelectionMenu->addAction(selectMultipleEdgesAct);
	mSelectionMenu->addAction(selectEdgeLoopAct);
	mSelectionMenu->addAction(selectEdgeRingAct);
	// mSelectionMenu->addAction(mCollapseSelectedEdgesAct);
	// mSelectionMenu->addAction(mSubdivideSelectedEdgesAct);
	mSelectionMenu->addAction(selectEdgesFromFacesAct);
	mSelectionMenu->addAction(selectEdgesFromVerticesAct);
	mSelectionMenu->addSeparator();
	mSelectionMenu->addAction(selectFaceAct);
	mSelectionMenu->addAction(selectFaceLoopAct);
	// mSelectionMenu->addAction(selectMultipleFacesAct);
	// mSelectionMenu->addAction(selectSimilarFacesAct);
	mSelectionMenu->addAction(selectFacesByAreaAct);
	mSelectionMenu->addAction(selectFacesByColorAct);
	mSelectionMenu->addAction(selectCheckerboardFacesAct);
	mSelectionMenu->addAction(selectFacesFromEdgesAct);
	mSelectionMenu->addAction(selectFacesFromVerticesAct);
	mSelectionMenu->addSeparator();
	// mSelectionMenu->addAction(selectVertexAct);
	// mSelectionMenu->addAction(selectMultipleVerticesAct);
	mSelectionMenu->addAction(mEditVertexAct);
	mSelectionMenu->addAction(selectVerticesFromFacesAct);
	mSelectionMenu->addAction(selectVerticesFromEdgesAct);
	// mSelectionMenu->addAction(selectCornerAct);
	// mSelectionMenu->addSeparator();

	mToolsMenu = new QMenu(tr("&Tools"));
	mToolsMenu->setTearOffEnabled(true);
	mToolsMenu->addMenu(mBasicsMode->getMenu());
	mToolsMenu->addAction(mPerformExtrusionAct);
	mToolsMenu->addAction(mPaintSelectedFacesAct);
	menuBar->addMenu(mToolsMenu);

	//selection Masks (vertices / edges / faces / face-vertices)
	mSelectionMaskMenu = new QMenu(tr("Selection &Masks"));
	mSelectionMenu->addMenu(mSelectionMaskMenu);
	mSelectionMaskMenu->addAction(mSelectVerticesMaskAct);
	mSelectionMaskMenu->addAction(mSelectFacesMaskAct);
	mSelectionMaskMenu->addAction(mSelectEdgesMaskAct);
	mSelectionMaskMenu->addAction(mSelectCornersMaskAct);

	mWindowMenu = new QMenu(tr("&Window"));
	menuBar->addMenu(mWindowMenu);
	mWindowMenu->addAction(mShowToolOptionsAct);
	mWindowMenu->addSeparator();
	mWindowMenu->addAction(mEditToolBarAct);
	mWindowMenu->addAction(mSelectionMaskToolBarAct);
	mWindowMenu->addAction(mPrimitivesToolBarAct);
	mWindowMenu->addAction(mToolsToolBarAct);

	mHelpMenu = new QMenu(tr("&Help"));
	menuBar->addMenu(mHelpMenu);
	mHelpMenu->addAction(mAboutAct);

	mRightClickMenu = new QMenu();

}

void MainWindow::createToolBars() {

	//selection masks toolbar
	mSelectionMaskToolBar = new QToolBar(tr("Selection Masks"));
	// mSelectionMaskToolBar->hide();
	//mSelectionMaskToolBar->setFloatable(true);
	addToolBar(Qt::TopToolBarArea,mSelectionMaskToolBar);
	mSelectionMaskToolBar->addAction(mSelectVerticesMaskAct);
	mSelectionMaskToolBar->addAction(mSelectFacesMaskAct);
	mSelectionMaskToolBar->addAction(mSelectEdgesMaskAct);
	mSelectionMaskToolBar->addAction(mSelectCornersMaskAct);
	// mSelectionMaskToolBar->setOrientation(Qt::Vertical);

	mPrimitivesToolBar = new QToolBar(tr("Primitives"),this);
	//mPrimitivesToolBar->setFloatable(true);
	addToolBar(Qt::TopToolBarArea,mPrimitivesToolBar);
	mPrimitivesToolBar->setIconSize(QSize(64,64));
	mPrimitivesToolBar->addAction(pCubeAct);
	mPrimitivesToolBar->addAction(pOctahedronAct);
	mPrimitivesToolBar->addAction(pTetrahedronAct);
	mPrimitivesToolBar->addAction(pDodecahedronAct);
	mPrimitivesToolBar->addAction(pIcosahedronAct);
	mPrimitivesToolBar->addAction(pSoccerBallAct);
	mPrimitivesToolBar->addAction(pGeodesicAct);

	//basic tools - six buttons
	mToolsToolBar = new QToolBar(tr("Tools"),this);
	//mToolsToolBar->setFloatable(true);
	addToolBar(Qt::TopToolBarArea,mToolsToolBar);
	mToolsToolBar->setIconSize(QSize(64,64));

	addToolBarBreak();


	//tools ction group initialization
	mToolsActionGroup = new QActionGroup(this);
	mToolsActionGroup->setExclusive(true);

	mBasicsMode->addActions(mToolsActionGroup, mToolsToolBar, mToolOptionsStackedWidget);

	//window menu toolbar display actions
	mSelectionMaskToolBarAct 	= mSelectionMaskToolBar->toggleViewAction();
	mPrimitivesToolBarAct     = mPrimitivesToolBar->toggleViewAction();
	mToolsToolBarAct				 	= mToolsToolBar->toggleViewAction();

}

void MainWindow::showAllToolBars(){
	mSelectionMaskToolBar->show();
	mPrimitivesToolBar->show();
	mToolsToolBar->show();
}

void MainWindow::hideAllToolBars(){
	mSelectionMaskToolBar->hide();
	mPrimitivesToolBar->hide();
	mToolsToolBar->hide();
}

void MainWindow::setToolOptions(QWidget *optionsWidget) {
	mToolOptionsDockWidget->setWindowTitle(tr("Tool Options - ") + optionsWidget->windowTitle());
	mToolOptionsStackedWidget->setCurrentWidget(optionsWidget);
	mToolOptionsStackedWidget->updateGeometry();
}

void MainWindow::createStatusBar() {
	statusBar()->showMessage(tr("Welcome to TopMod"));
}

void MainWindow::closeEvent(QCloseEvent *event) {

	if (maybeSave()) {
		event->accept();
	}
	else event->ignore();
}

void MainWindow::newFile(){
	if (maybeSave()){
		clearUndoList();
		object.destroy();
		active->redraw();
  	}
	else return;
}

bool MainWindow::maybeSave() {
	if (this->isModified()) {
		int ret = QMessageBox::warning(this, tr("TopMod"),
																	 tr("The document has been modified.\n"
																			"Do you want to save your changes?"),
																	 QMessageBox::Yes | QMessageBox::Default,
																	 QMessageBox::No,
																	 QMessageBox::Cancel | QMessageBox::Escape);
		if (ret == QMessageBox::Yes)
			return this->saveFile();
		else if (ret == QMessageBox::Cancel)
			return false;
	}
	return true;
}

void MainWindow::loadFile(QString fileName) {
	openFile(fileName);
	this->setCurrentFile(fileName);
	statusBar()->showMessage(tr("File loaded"), 2000);
}

bool MainWindow::saveFile(QString fileName) {
	this->setCurrentFile(fileName);
	statusBar()->showMessage(tr("File saved"), 2000);
	return true;
}

void MainWindow::openFile(QString fileName){
	QFile file(fileName);
	file.open(QIODevice::ReadOnly);
	QFileInfo info(file);
	QByteArray ba = info.absoluteFilePath().toLatin1();
	const char *filename = ba.data();
	mWasPrimitive = false;
	mIsPrimitive = false;
	if (!curFile.isEmpty()){
		undoPush();
		setModified(false);
	}

	readObject(filename);
	active->recomputeNormals();
	setCurrentFile(fileName);
	active->redraw();
}

void MainWindow::about() {
  //QString s = QString("TopMod Topological Mesh Modeler v%1 <br /><a href=\"http://www.topmod3d.org/\">TopMod Home Page</a><br /><a href=\"http://code.google.com/p/topmod/downloads/list\">Check for Updates.</a>").arg(VER);
	 QString s = QString("TopMod Topological Mesh Modeler v2.444 <br /><a href=\"http://www.topmod3d.org/\">TopMod Home Page</a><br /><a href=\"http://code.google.com/p/topmod/downloads/list\">Check for Updates.</a>");
	QMessageBox::about(this, tr("About TopMod"), s);
}

void MainWindow::documentWasModified() {
	setWindowModified(this->isModified());
}

void MainWindow::createRenderers(){
	wired = new WireframeRenderer();
	// wired->setRenderFlags(DLFLRenderer::ShowWireframe);
	normal = new NormalRenderer();
	// normal->setRenderFlags(DLFLRenderer::ShowWireframe);

	lit = new LitRenderer();
	// lit->setRenderFlags(DLFLRenderer::ShowWireframe);

	textured = new TexturedRenderer();
	// textured->setRenderFlags(DLFLRenderer::ShowWireframe);

	texturedlit = new TexturedLitRenderer();
	// texturedlit->setRenderFlags(DLFLRenderer::ShowWireframe);

	colorable = new ColorableRenderer();
}

void MainWindow::destroyRenderers(){
	delete wired;
	delete normal;
	delete lit;
	delete textured;
	delete texturedlit;
	delete colorable;
};

void MainWindow::setUndoLimit(int limit) {
	undolimit = limit;
}

void MainWindow::toggleUndo(void) {
	if ( useUndo ) useUndo = false;
	else useUndo = true;
}

// Do selection of various entities depending on current mode
void MainWindow::doSelection(int x, int y) {
	DLFLVertexPtr svptr = NULL;
	DLFLEdgePtr septr = NULL;
	DLFLFacePtr sfptr = NULL;
	DLFLFaceVertexPtr sfvptr = NULL;

	DLFLEdgePtrArray septrarr;
	DLFLEdgePtrArray::iterator eit;
	DLFLEdgePtrArray svptrarr;
	DLFLEdgePtrArray::iterator vit;
	DLFLFacePtrArray sfptrarr;
	DLFLFacePtrArray::iterator first, last;

	switch ( mode ) {
	case SelectVertex:
	case MarkVertex:
	case CutVertex://ozgur
		if (QApplication::keyboardModifiers() != Qt::ShiftModifier){
			active->clearSelectedVertices();
		}
		svptr = active->selectVertex(x,y);
		active->setSelectedVertex(svptr);
		break;
	case MultiSelectVertex :
		svptr = active->selectVertex(x,y);
		if ( QApplication::keyboardModifiers() == Qt::ControlModifier) {
			if ( active->isSelected(svptr)){
				active->clearSelectedVertex(svptr);
				num_sel_verts--;
			}
			active->redraw();
			svptrarr.clear();
		}
		else {
			svptr = active->selectVertex(x,y);
			if ( !active->isSelected(svptr)){
				active->setSelectedVertex(svptr);
				num_sel_verts++;
			}
			active->redraw();
			svptrarr.clear();
		}
		// svptr = active->selectVertex(x,y);
		// if ( !active->isSelected(svptr) )
		// 	active->setSelectedVertex(num_sel_verts,svptr);
		break;
	case DeleteEdge :
	case SubdivideEdge :
	case CollapseEdge :
	case SelectEdge :
	case CutEdge :
	case TruncateEdge :
	case MarkEdge ://ozgur
		if (QApplication::keyboardModifiers() != Qt::ShiftModifier){
			active->clearSelectedEdges();
		}
		septr = active->selectEdge(x,y);
		active->setSelectedEdge(septr);
		// cout << "x = " << x << "\t\ty = " << y << "\n";
		break;
	case CutEdgeandVertex://ozgur
		septr = active->selectEdge(x,y);
		svptr = active->selectVertex(x,y);
		active->setSelectedEdge(septr);
		active->setSelectedVertex(svptr);
		break;
	case MultiSelectEdge :
		septr = active->selectEdge(x,y);
		if ( QApplication::keyboardModifiers() == Qt::ControlModifier) {
			if ( active->isSelected(septr)){
				active->clearSelectedEdge(septr);
				num_sel_edges--;
			}
			active->redraw();
			septrarr.clear();
		}
		else {
			septr = active->selectEdge(x,y);
			if ( !active->isSelected(septr)){
				active->setSelectedEdge(septr);
				num_sel_edges++;
			}
			active->redraw();
			septrarr.clear();
		}
		// septr = active->selectEdge(x,y);
		// if ( !active->isSelected(septr) )
		// 	active->setSelectedEdge(num_sel_edges,septr);
		break;
	case SelectEdgeLoop:
		if (QApplication::keyboardModifiers() != Qt::ShiftModifier){
			active->clearSelectedEdges();
		}
		septr = active->selectEdge(x,y);
		if (septr && QApplication::keyboardModifiers() == Qt::ControlModifier && active->isSelected(septr)){
			deselect_edges = true;
			active->clearSelectedEdge(septr);
			num_sel_edges--;
			getEdgeLoopSelection(septr);
			deselect_edges = false;
		}
		else if ( septr && !active->isSelected(septr)){
			// active->setSelectedEdge(num_sel_edges,septr);
			active->setSelectedEdge(septr);
			num_sel_edges++;
			getEdgeLoopSelection(septr);
		}
		active->redraw();
		break;
	case SelectFace :
	case CrustModeling :
	case ConnectFaces :
	case CutFace://ozgur
	case PaintFace://dave
	case EyeDropper://dave
		if (QApplication::keyboardModifiers() != Qt::ShiftModifier){
			active->clearSelectedFaces();
		}
      sfptr = active->selectFace(x, y, 10, 10);
		// active->setSelectedFace(num_sel_faces,sfptr);
		active->setSelectedFace(sfptr);
		break;
	// case SelectSimilarFaces :
	// 	//clear selection if shift isn't down
	// 	if (QApplication::keyboardModifiers() != Qt::ShiftModifier)
	// 		active->clearSelectedFaces();
	// 	sfptr = active->selectFace(x,y);
	// 	if (sfptr){
	// 		if (!active->isSelected(sfptr)){
	// 			// active->setSelectedFace(num_sel_faces,sfptr);
	// 			active->setSelectedFace(sfptr);
	// 			num_sel_faces++;
	// 		}
	// 		DLFLFacePtrArray sfptrarray;
	// 		vector<DLFLFacePtr>::iterator it;
	// 		DLFL::selectMatchingFaces(&object, sfptr, sfptrarray);
	// 		for (it = sfptrarray.begin(); it != sfptrarray.end(); it++){
	// 			if (!active->isSelected(*it)){
	// 				active->setSelectedFace(*it);
	// 				num_sel_faces++;
	// 			}
	// 		}
	// 	}
	// 	active->redraw();
	// 	break;
		case SelectSimilar:
		// std::cout << active->getSelectionMaskString() << " = select similar\n";

			switch (selectionmask){
				case MaskFaces:
				// std::cout<< "Mask faces select sim\n";
				//clear selection if shift isn't down
				if (QApplication::keyboardModifiers() != Qt::ShiftModifier)
					active->clearSelectedFaces();
				sfptr = active->selectFace(x,y);
				if (sfptr){
					if (!active->isSelected(sfptr)){
						// active->setSelectedFace(num_sel_faces,sfptr);
						active->setSelectedFace(sfptr);
						num_sel_faces++;
					}
					DLFLFacePtrArray sfptrarray;
					vector<DLFLFacePtr>::iterator it;
					DLFL::selectMatchingFaces(&object, sfptr, sfptrarray);
					for (it = sfptrarray.begin(); it != sfptrarray.end(); it++){
						if (!active->isSelected(*it)){
							active->setSelectedFace(*it);
							num_sel_faces++;
						}
					}
				}
				break;
				case MaskEdges:
			// } else if (selectionmask == MainWindow::MaskEdges){
				//clear selection if shift isn't down
				if (QApplication::keyboardModifiers() != Qt::ShiftModifier)
					active->clearSelectedEdges();
				septr = active->selectEdge(x,y);
				if (septr){
					if (!active->isSelected(septr)){
						active->setSelectedEdge(septr);
						num_sel_edges++;
					}
					DLFLEdgePtrArray septrarray;
					vector<DLFLEdgePtr>::iterator eit;
					DLFL::selectMatchingEdges(&object, septr, septrarray);
					for (eit = septrarray.begin(); eit != septrarray.end(); eit++){
						if (!active->isSelected(*eit)){
							active->setSelectedEdge(*eit);
							num_sel_edges++;
						}
					}
				}
				break;
			// } else if (selectionmask == MainWindow::MaskVertices){
				case MaskVertices:
				//clear selection if shift isn't down
				if (QApplication::keyboardModifiers() != Qt::ShiftModifier)
					active->clearSelectedVertices();
				svptr = active->selectVertex(x,y);
				if (svptr){
					if (!active->isSelected(svptr)){
						active->setSelectedVertex(svptr);
						num_sel_verts++;
					}
					DLFLVertexPtrArray svptrarray;
					vector<DLFLVertexPtr>::iterator vit;
					DLFL::selectMatchingVertices(&object, svptr, svptrarray);
					for (vit = svptrarray.begin(); vit != svptrarray.end(); vit++){
						if (!active->isSelected(*vit)){
							active->setSelectedVertex(*vit);
							num_sel_verts++;
						}
					}
				}
			// }
			active->redraw();
			break;
			default:
			break;
		};
			break;
		case SelectFaceLoop:
		if (QApplication::keyboardModifiers() != Qt::ShiftModifier){
			active->clearSelectedFaces();
		}
		septr = active->selectEdge(x,y);
		active->setSelectedEdge(septr);
		if ( septr ){
			if (QApplication::keyboardModifiers() == Qt::ControlModifier){ // deselect
				face_loop_start_edge = septr;
				getFaceLoopSelection(septr, true, NULL, false);
			}
			else { //select
				face_loop_start_edge = septr;
				getFaceLoopSelection(septr, true, NULL, true);
			}
		}
		active->redraw();
		break;
	case SelectEdgeRing:
		if (QApplication::keyboardModifiers() != Qt::ShiftModifier){
			active->clearSelectedEdges();
		}
		septr = active->selectEdge(x,y);
		active->setSelectedEdge(septr);
		if ( septr ){
			if (QApplication::keyboardModifiers() == Qt::ControlModifier){ // deselect
				edge_ring_start_edge = septr;
				getEdgeRingSelection(septr, true, NULL, false);
			}
			else { //select
				edge_ring_start_edge = septr;
				getEdgeRingSelection(septr, true, NULL, true);
			}
		}
		active->redraw();
		break;
	case ExtrudeFace :
	case ExtrudeFaceDS :
	case ExtrudeDualFace :
	case ExtrudeFaceDodeca :
	case ExtrudeFaceIcosa :
	case StellateFace :
	case DoubleStellateFace :
	case ExtrudeFaceDome :
	case ExtrudeMultipleFaces :
	case MultiSelectFace :
	case SubdivideFace :
		sfptr = active->selectFace(x,y);
		if ( QApplication::keyboardModifiers() == Qt::ControlModifier) {
			if ( active->isSelected(sfptr)){
				active->clearSelectedFace(sfptr);
				num_sel_faces--;
			}
			active->redraw();
			sfptrarr.clear();
		}
		else {
			sfptr = active->selectFace(x,y);
			if ( !active->isSelected(sfptr)){
				active->setSelectedFace(num_sel_faces,sfptr);
				num_sel_faces++;
			}
			active->redraw();
			sfptrarr.clear();
		}
	break;
	case SelectCheckerboard :
		if (QApplication::keyboardModifiers() != Qt::ShiftModifier){
			active->clearSelectedFaces();
		}
		//get one selected face
		sfptr = active->selectFace(x,y);
		if (sfptr && active->isSelected(sfptr) && QApplication::keyboardModifiers() == Qt::ControlModifier){
			active->clearSelectedFace(sfptr);
			num_sel_faces--;
			getCheckerboardSelection(sfptr);
		}
		else if (sfptr && !active->isSelected(sfptr) ){
			active->setSelectedFace(sfptr);
			num_sel_faces++;
			getCheckerboardSelection(sfptr);
		}
		active->redraw();
		sfptrarr.clear();
		break;
	case SelectCorner :
	case ReorderFace :
	case InsertEdge :
	case SpliceCorners :
	case ConnectFaceVertices :
	case BezierConnectFaces :
	case HermiteConnectFaces :
		sfptr = active->selectFace(x,y);
		active->setSelectedFace(num_sel_faces,sfptr);
		if ( sfptr )
			{
				sfvptr = active->selectFaceVertex(sfptr,x,y);
				active->setSelectedFaceVertex(num_sel_faceverts,sfvptr);
			}
		break;

	case MultiSelectCorner :
		sfptr = active->selectFace(x,y);
		active->setSelectedFace(sfptr);
		if ( sfptr )
			{
				sfvptr = active->selectFaceVertex(sfptr,x,y);
				if ( !active->isSelected(sfvptr) )
					active->setSelectedFaceVertex(sfvptr);
			}
		break;

	case ConnectEdges :
		sfptr = active->selectFace(x,y);
		active->setSelectedFace(num_sel_faces,sfptr);
		if ( sfptr )
			{
				septr = active->selectEdge(x,y);
				active->setSelectedEdge(num_sel_edges,septr);
			}
		break;
	case SelectionWindow:
		if (QApplication::keyboardModifiers() != Qt::ShiftModifier){
			active->clearSelectedEdges();
			active->clearSelectedVertices();
			active->clearSelectedFaces();
		}
		break;
	};
	redraw();
	// if ( svptr != NULL || septr != NULL || sfptr != NULL ) redraw();
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event) {
	// QMessageBox::about(this,tr("mimetype"),tr("%1").arg(event->mimeData()->formats().join(",")));
	// if (event->mimeData()->hasFormat("text/uri-list"))
	event->acceptProposedAction();
}

void MainWindow::dropEvent(QDropEvent *event) {
    //QMessageBox::about(this, tr("Drop Event"), QFileInfo(event->mimeData()->urls()[0].toLocalFile()).absoluteFilePath());
    loadFile(QFileInfo(event->mimeData()->urls()[0].toLocalFile()).absoluteFilePath());
	event->acceptProposedAction();
}

// Handle keyboard and mouse events
void MainWindow::mousePressEvent(QMouseEvent *event) {

	//experimental for crossing window selection
	// if (event->buttons() == Qt::LeftButton && mode == SelectionWindow){

	// }
	if ( event->buttons() == Qt::LeftButton && mode != NormalMode ){
		doSelection(event->x(),height()-mStatusBar->height()-event->y());
	}
	// else if ( event->buttons() == Qt::RightButton && QApplication::keyboardModifiers() == Qt::ShiftModifier){
	// 	// event->ignore();
	// 	if (!active->isBrushVisible()) active->showBrush();
	// 	mBrushStartX = event->x();
	// 	// mBrushStartY = event->y();
	// }
	else if (event->buttons() == Qt::RightButton){
		getRightClickMenu();
		mRightClickMenu->popup(mapToGlobal(event->pos()));
	}
	else event->ignore();
}

void MainWindow::getRightClickMenu(){
	mRightClickMenu->clear();
	//add generic items for now to test it out

	switch (mode){
		NormalMode :
		// mRightClickMenu->addAction(createWireframeAct);
		break;
		SelectVertex :
		break;
		SelectEdge :
		mRightClickMenu->addAction(mSubdivideSelectedEdgesAct);
		break;
		SelectFace :
		mRightClickMenu->addAction(mSubdivideSelectedFacesAct);
		mRightClickMenu->addAction(mPaintSelectedFacesAct);
		break;
		SelectCorner :
		break;
		MultiSelectVertex :
		break;
		MultiSelectEdge :
		mRightClickMenu->addAction(mSubdivideSelectedEdgesAct);
		break;
		MultiSelectFace :
		mRightClickMenu->addAction(mSubdivideSelectedFacesAct);
		mRightClickMenu->addAction(mPaintSelectedFacesAct);
		break;
		MultiSelectCorner :
		break;
		InsertEdge :
		break;
		DeleteEdge :
		break;
		SubdivideEdge :
		break;
		CollapseEdge :
		mRightClickMenu->addAction(mSubdivideSelectedEdgesAct);
		mRightClickMenu->addAction(mCollapseSelectedEdgesAct);
		break;
		SpliceCorners :
		break;
		ConnectEdges :
		mRightClickMenu->addAction(mSubdivideSelectedEdgesAct);
		mRightClickMenu->addAction(mCollapseSelectedEdgesAct);
		break;
		ExtrudeFace :
		ExtrudeFaceDS :
		ExtrudeDualFace :
		ExtrudeFaceDodeca :
		ExtrudeFaceIcosa :
		ExtrudeMultipleFaces :
		StellateFace :
		DoubleStellateFace  :
		ExtrudeFaceDome :
		mRightClickMenu->addAction(mPerformExtrusionAct);
		mRightClickMenu->addAction(mSubdivideSelectedFacesAct);
		mRightClickMenu->addAction(mPaintSelectedFacesAct);
		break;
		ReorderFace :
		break;
		SubdivideFace :
		mRightClickMenu->addAction(mSubdivideSelectedFacesAct);
		break;
		SelectEdgeLoop :
		SelectEdgeRing :
		mRightClickMenu->addAction(mSubdivideSelectedEdgesAct);
		mRightClickMenu->addAction(mCollapseSelectedEdgesAct);
		// mRightClickMenu->addAction(mDeleteSelectedAct);
		break;
		SelectFaceLoop :
		// SelectSimilarFaces :
		SelectFacesByArea:
		SelectFacesByColor:
		SelectCheckerboard :
		mRightClickMenu->addAction(mSubdivideSelectedFacesAct);
		mRightClickMenu->addAction(mPaintSelectedFacesAct);
		break;

		default:
		break;
	};

	mRightClickMenu->addSeparator();
	mRightClickMenu->addAction(selectAllAct);
	mRightClickMenu->addAction(selectInverseAct);
	mRightClickMenu->addAction(mSelectMultipleAct);
	mRightClickMenu->addAction(mSelectSimilarAct);
	mRightClickMenu->addAction(mSelectionWindowAct);
	mRightClickMenu->addAction(mSelectComponentAct);
	mRightClickMenu->addAction(mGrowSelectionAct);
	mRightClickMenu->addAction(mShrinkSelectionAct);
	mRightClickMenu->addAction(clearSelectedModeAct);
	mRightClickMenu->addSeparator();

	switch (selectionmask){
		case MaskVertices:
			mRightClickMenu->addAction(mDeleteSelectedAct);
			// mRightClickMenu->addAction(selectVertexAct);
			// mRightClickMenu->addAction(selectMultipleVerticesAct);
			mRightClickMenu->addAction(mEditVertexAct);
			// mRightClickMenu->addAction(mEditVertexAct);
			mRightClickMenu->addAction(selectEdgesFromVerticesAct);
			mRightClickMenu->addAction(selectFacesFromVerticesAct);
		break;
		case MaskEdges:
			mRightClickMenu->addAction(mDeleteSelectedAct);
			mRightClickMenu->addAction(mCollapseSelectedEdgesAct);
			mRightClickMenu->addSeparator();
			// mRightClickMenu->addAction(selectEdgeAct);
			// mRightClickMenu->addAction(selectMultipleEdgesAct);
			mRightClickMenu->addAction(selectEdgeLoopAct);
			mRightClickMenu->addAction(selectEdgeRingAct);
			mRightClickMenu->addAction(selectVerticesFromEdgesAct);
			mRightClickMenu->addAction(selectFacesFromEdgesAct);
		break;
		case MaskFaces://face stuff
			// mRightClickMenu->addAction(mDeleteSelectedAct);
			mRightClickMenu->addAction(selectFaceAct);
			mRightClickMenu->addAction(selectFaceLoopAct);
			// mRightClickMenu->addAction(selectMultipleFacesAct);
			// mRightClickMenu->addAction(selectSimilarFacesAct);
			mRightClickMenu->addAction(selectFacesByAreaAct);
			mRightClickMenu->addAction(selectFacesByColorAct);
			mRightClickMenu->addAction(selectCheckerboardFacesAct);
			mRightClickMenu->addAction(selectEdgesFromFacesAct);
			mRightClickMenu->addAction(selectVerticesFromFacesAct);
		break;
		case MaskCorners:
			// mRightClickMenu->addAction(mDeleteSelectedAct);
			// mRightClickMenu->addAction(// selectCornerAct);
		break;
		default:
		break;
	};

	// mRightClickMenu->addSeparator();
	// mRightClickMenu->addAction(mEditVertexAct);
	mRightClickMenu->addSeparator();
	mRightClickMenu->addMenu(mToolsMenu);
	mRightClickMenu->addMenu(mRemeshingMenu);
	mRightClickMenu->addMenu(mSelectionMaskMenu);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
	// if (active->isBrushVisible()) active->redraw();
	//if ( mode != NormalMode && event->buttons() == Qt::LeftButton)
		// doSelection(event->x(),this->size().height()-event->y() );
		//doDrag(event->x(),this->size().height()-mStatusBar->height()-event->y() );
	//else event->ignore();
}

//if the user holds down certain keys, allow them to
//change various properties in the scene
void MainWindow::keyPressEvent(QKeyEvent *event){

}

void MainWindow::keyReleaseEvent(QKeyEvent *event){

}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)  {
	QString cmd;
	// The mouse was dragged or released
	// Send this event to the subroutine handling the current event, if any
	// If we are not currently doing anything, nothing will happen
	// If ALT key is pressed we are mainpulating the view which is handled by the viewport
	if ( mode != NormalMode )
		{
			switch ( mode )
				{
				case SelectVertex :

					if ( active->numSelectedVertices() >= 1 )
						{
							// DLFLVertexPtr vp = active->getSelectedVertex(0);
							// vp->print();
							// active->clearSelectedVertices();
							// num_sel_verts = 0;
							// redraw();
						}
					break;
				case SelectEdge :
				case CutEdge:
					// if ( active->numSelectedEdges() >= 1 ) {
						// DLFLEdgePtr septr = active->getSelectedEdge(0);
						// if (septr) {
							//septr->print();
							//num_sel_edges = 0;
						// }
						// active->clearSelectedEdges();
						// redraw();
					// }
					break;
				case SelectEdgeLoop:
					if ( active->numSelectedEdges() >= 1 ){
						DLFLEdgePtr septr = active->getSelectedEdge(0);
						if (septr)
							getEdgeLoopSelection(septr);
					}
					// active->clearSelectedEdges();
					active->redraw();
					break;
				case SelectEdgeRing:
					if ( active->numSelectedEdges() >= 1 ){
						DLFLEdgePtr septr = active->getSelectedEdge(0);
						if (septr){
							if (QApplication::keyboardModifiers() == Qt::ControlModifier){ // deselect
								edge_ring_start_edge = septr;
								getEdgeRingSelection(septr, true, NULL, false);
							}
							else { //select
								edge_ring_start_edge = septr;
								getEdgeRingSelection(septr, true, NULL, true);
							}
						}
					}
					active->redraw();
					break;
				case SelectFaceLoop:
					if ( active->numSelectedEdges() >= 1 ){
						DLFLEdgePtr septr = active->getSelectedEdge(0);
						if (septr){
							if (QApplication::keyboardModifiers() == Qt::ControlModifier){ // deselect
								face_loop_start_edge = septr;
								getFaceLoopSelection(septr, true, NULL, false);
							}
							else { //select
								face_loop_start_edge = septr;
								getFaceLoopSelection(septr, true, NULL, true);
							}
						}
					}
					active->clearSelectedEdges();
					active->redraw();
					break;
				case SelectFace :

					break;
					case PaintFace:
					if ( active->numSelectedFaces() >= 1 ) {
						DLFLFacePtr fp = active->getSelectedFace(0);
						// first search for the material in the existing list
						// DLFLMaterialPtr m = object.findMaterial(RGBColor(paint_bucket_color.redF(),paint_bucket_color.greenF(),paint_bucket_color.blueF() ));
						fp->setMaterial(object.addMaterial(RGBColor(paint_bucket_color.redF(),paint_bucket_color.greenF(),paint_bucket_color.blueF())) );
						// if ( m ){
						//
						// }
						// else {
						//
						// }
						active->clearSelectedFaces();
						redraw();
					}
					break;
                case SelectSimilar :
                    if (selectionmask == MainWindow::MaskFaces){
                        // cout << "select similar faces mouse release\n";
                        if ( active->numSelectedFaces() >= 1 ){
                            DLFLFacePtr sfptr = active->getSelectedFace(0);
                            if (sfptr){
                                DLFLFacePtrArray sfptrarray;
                                vector<DLFLFacePtr>::iterator it;
                                DLFL::selectMatchingFaces(&object, sfptr, sfptrarray);
                                for (it = sfptrarray.begin(); it != sfptrarray.end(); it++){
                                    if (!active->isSelected(*it)){
                                        active->setSelectedFace(*it);
                                        num_sel_faces++;
                                    }
                                }
                            }
                        }
                    } else if (selectionmask == MainWindow::MaskEdges){
                        if ( active->numSelectedEdges() >= 1 ){
                            DLFLEdgePtr septr = active->getSelectedEdge(0);
                            if (septr){
                                DLFLEdgePtrArray septrarray;
                                vector<DLFLEdgePtr>::iterator eit;
                                DLFL::selectMatchingEdges(&object, septr, septrarray);
                                for (eit = septrarray.begin(); eit != septrarray.end(); eit++){
                                    if (!active->isSelected(*eit)){
                                        active->setSelectedEdge(*eit);
                                        num_sel_edges++;
                                    }
                                }
                            }
                        }
                    } else if (selectionmask == MainWindow::MaskVertices){
                        if ( active->numSelectedVertices() >= 1 ){
                            DLFLVertexPtr svptr = active->getSelectedVertex(0);
                            if (svptr){
                                if (!active->isSelected(svptr)){
                                    active->setSelectedVertex(svptr);
                                    num_sel_verts++;
                                }
                                DLFLVertexPtrArray svptrarray;
                                vector<DLFLVertexPtr>::iterator vit;
                                DLFL::selectMatchingVertices(&object, svptr, svptrarray);
                                for (vit = svptrarray.begin(); vit != svptrarray.end(); vit++){
                                    if (!active->isSelected(*vit)){
                                        active->setSelectedVertex(*vit);
                                        num_sel_verts++;
                                    }
                                }
                            }
                        }
                    }
                    redraw();
                    break;
                
				case SelectCorner :
					if ( active->numSelectedCorners() >= 1 )
						{
							DLFLFaceVertexPtr fvp = active->getSelectedFaceVertex(0);
							fvp->print();
							active->clearSelectedCorners();
							active->clearSelectedFaces();
							num_sel_faceverts = 0; // num_sel_faces = 0;
							redraw();
						}
					break;
				case InsertEdge :
					if ( active->numSelectedCorners() >= 2 )
						{
							DLFLFaceVertexPtr sfvptr1, sfvptr2;
							sfvptr1 = active->getSelectedFaceVertex(0);
							sfvptr2 = active->getSelectedFaceVertex(1);
							if ( sfvptr1 && sfvptr2 )
								{
									DLFLMaterialPtr mptr = sfvptr1->getFacePtr()->material();
									undoPush();
									setModified(true);
									DLFL::insertEdge(&object,sfvptr1,sfvptr2,false,mptr);
									active->clearSelectedFaces();
									active->clearSelectedCorners();
									num_sel_faceverts = 0; // num_sel_faces = 0;
                                    sfvptr1->getVertexPtr()->updateNormal();
                                    sfvptr2->getVertexPtr()->updateNormal();
									redraw();
								}
						}
					else if ( active->numSelectedCorners() == 1 )
						{
							num_sel_faceverts=1; num_sel_faces=1;
						}
					break;
				case ExtrudeFace :
				if (mSingleClickExtrude){
					if ( active->numSelectedFaces() >= 1 )
						{
							DLFLFacePtr sfptr = active->getSelectedFace(0);
							if ( sfptr )
								{
									undoPush();
									setModified(true);
									DLFL::extrudeFace(&object,sfptr,extrude_dist,num_extrusions,extrude_rot,extrude_scale);
									active->recomputeNormals();
								}
							active->clearSelectedFaces();
							redraw();
						}
					}
					break;
				case ExtrudeMultipleFaces ://todo: this isn't used anymore.
					break;
				}//end switch (mode)

		}//end if (mode != NormalMode)
	else event->ignore();
}//end function mousereleaseevent

void MainWindow::performExtrusion(){
	if ( active->numSelectedFaces() >= 1 ) {
		DLFLFacePtrArray sfptrarr = active->getSelectedFaces();
		if ( sfptrarr[0] ) {
      // Fenghui's simple profiler for Extrusion operation.
      std::clock_t start = std::clock();
      std::clock_t op = std::clock();
      std::clock_t recompute_normals = std::clock();
			undoPush();
			setModified(true);
			vector<DLFLFacePtr>::iterator it;
			for (it = sfptrarr.begin(); it != sfptrarr.end(); it++) {
				switch (extrusionmode){
					case CubicalExtrude:
            /*DLFL::extrudeFace(&object, *it, extrude_dist, num_extrusions,
                              extrude_rot, extrude_scale, triangulate_new_faces,
                              scherk_collins, scherk_collins_pinch,
                              scherk_collins_pinch_center,
                              scherk_collins_pinch_width);*/
            DLFL::extrudeFaceScherkCollins(&object, *it, extrude_dist, num_extrusions,
                              extrude_rot, extrude_scale, triangulate_new_faces,
                              scherk_collins, scherk_collins_pinch,
                              scherk_collins_pinch_center,
                              scherk_collins_pinch_width);
						break;
						// case IcosahedralExtrude: DLFL::extrudeFaceIcosa(&object,*it,extrude_dist,num_extrusions, ds_ex_twist,extrude_scale);
					
							default: DLFL::extrudeFace(&object,*it,extrude_dist,num_extrusions,extrude_rot,extrude_scale);
							break;
						};
					}
          //Fenghui, record the time after the operation
          op = std::clock();



					active->recomputeNormals();
          recompute_normals = std::clock();
          // Fenghui, output the time taken to perform each steps.
          cout << "Extrusion:" << (op - start) / (double)CLOCKS_PER_SEC
               << ":" << (std::clock() - recompute_normals) / (double)CLOCKS_PER_SEC
               << endl;
          // Fenghui's simple profiler for Extrusion, end!
				}
			active->clearSelectedFaces();
			redraw();
		}
}

// Change the renderer for all viewports
void MainWindow::setRenderer(DLFLRendererPtr rp) {
	active->setRenderer(rp);
}

// Return pointer to the active GLWidget
GLWidget *MainWindow::getActive() {
	return active;
}

// Override redraw() method to mark subwindows also for redraw
void MainWindow::redraw() {
	active->redraw();
}

//--- Methods to perform various operations ---//

// Switch to specified operating mode
void MainWindow::setMode(Mode m) {
	mode = m;

	switch ( mode )	{
	case SelectVertex :
	case MultiSelectVertex :
	case SelectEdge :
	case SelectEdgeLoop :
	case SelectEdgeRing :
	case MultiSelectEdge :
	case DeleteEdge :
	case SubdivideEdge :
	case CollapseEdge :
	case ConnectEdges :
	case CutEdge :
	case TruncateEdge :
	case MarkEdge :
		setSelectionMask(MainWindow::MaskEdges);
		// MainWindow::num_sel_edges = 0;
		break;
	case SelectFace :
	case SelectFaceLoop :
	case MultiSelectFace :
	case SelectCheckerboard :
	case ExtrudeFace :
	case SelectFacesByArea:
	case SelectFacesByColor:
	case PaintFace:
	case EyeDropper:
		// printf("mode is Select Face or something\n");
		setSelectionMask(MainWindow::MaskFaces);
		// MainWindow::num_sel_faces = 0;
		break;
	case SelectSimilar:
	//do nothing...
	break;
	case SelectCorner :
	case MultiSelectCorner :
	case InsertEdge :
	case SelectionWindow:
	break;
	case NormalMode:
		setSelectionMask(MainWindow::MaskNone);
	default :
		// Nothing to be done for other modes except clearing selection lists
		setSelectionMask(MainWindow::MaskNone);
		// MainWindow::clearSelected();
		break;
	}
	QString s;
	//this switch statement is for setting the string for the Heads up display
	switch (mode){
		case NormalMode: s = tr("Normal Mode");
		break;
		case SelectVertex: s = tr("Select Vertex");
		break;
		case SelectEdge: s = tr("Select Edge");
		break;
		case SelectFace: s = tr("Select Face");
		break;
		case SelectCorner: s = tr("Select Corner");
		break;
		case MultiSelectVertex: s = tr("Multi-Select Vertex");
		break;
		case MultiSelectEdge: s = tr("Multi-Select Edge");
		break;
		case MultiSelectFace: s = tr("Multi-Select Face");
		break;
		case MultiSelectCorner: s = tr("Multi-Select Corner");
		break;
		case SelectCheckerboard: s = tr("Select Checkerboard");
		break;
		case InsertEdge: s = tr("Insert Edge");
		break;
		case ExtrudeFace: s = tr("Cubical Extrusion");
		break;
		case SelectEdgeLoop: s = tr("Select Edge Loop");
		break;
		case SelectEdgeRing: s = tr("Select Edge Ring");
		break;
		case SelectFaceLoop: s = tr("Select Face Loop");
		break;
		case SelectSimilar: s = tr("Select Similar");
		break;
		case SelectFacesByArea: s = tr("Select Faces By Surf. Area");
		break;
		case SelectionWindow: s = tr("Selection Window");
		break;
		default:	s = tr("-");
		break;
	};
	active->setModeString(s);
	redraw();
}

void MainWindow::setExtrusionMode(ExtrusionMode m){
	extrusionmode = m;
	QString s;
	switch(m){
		case CubicalExtrude: s = "Cubical";
		break;
		default:
		break;
	};
	active->setExtrusionModeString(s);
}

void MainWindow::setSelectionMask(SelectionMask m){
	if (selectionmask != m){
		selectionmask = m;

		// active->clearSelected();
		active->repaint();
		//make sure we clear all other selected objects here...
		switch(selectionmask){
		case MaskVertices :
		active->clearSelectedEdges();
		active->clearSelectedFaces();
		active->clearSelectedCorners();
		// mSelectVerticesMaskAct->activate(QAction::Trigger);
		mSelectVerticesMaskAct->setChecked(true);
		mSelectEdgesMaskAct->setChecked(false);
		mSelectFacesMaskAct->setChecked(false);
		mSelectCornersMaskAct->setChecked(false);
		active->setSelectionMaskString(tr("Vertices"));
		break;
		case MaskEdges :
		active->clearSelectedVertices();
		active->clearSelectedFaces();
		active->clearSelectedCorners();
		// mSelectEdgesMaskAct->activate(QAction::Trigger);
		mSelectVerticesMaskAct->setChecked(false);
		mSelectEdgesMaskAct->setChecked(true);
		mSelectFacesMaskAct->setChecked(false);
		mSelectCornersMaskAct->setChecked(false);
		active->setSelectionMaskString(tr("Edges"));
		break;
		case MaskFaces :
		active->clearSelectedEdges();
		active->clearSelectedVertices();
		active->clearSelectedCorners();
		// mSelectFacesMaskAct->activate(QAction::Trigger);
		mSelectVerticesMaskAct->setChecked(false);
		mSelectEdgesMaskAct->setChecked(false);
		mSelectFacesMaskAct->setChecked(true);
		mSelectCornersMaskAct->setChecked(false);
		active->setSelectionMaskString(tr("Faces"));
		break;
		case MaskCorners :
		active->clearSelectedEdges();
		active->clearSelectedFaces();
		active->clearSelectedVertices();
		// mSelectCornersMaskAct->activate(QAction::Trigger);
		mSelectVerticesMaskAct->setChecked(false);
		mSelectEdgesMaskAct->setChecked(false);
		mSelectFacesMaskAct->setChecked(false);
		mSelectCornersMaskAct->setChecked(true);
		active->setSelectionMaskString(tr("Corners"));
		break;
		default:
		active->clearSelectedEdges();
		active->clearSelectedVertices();
		active->clearSelectedCorners();
		active->clearSelectedFaces();
		mSelectVerticesMaskAct->setChecked(false);
		mSelectEdgesMaskAct->setChecked(false);
		mSelectFacesMaskAct->setChecked(false);
		mSelectCornersMaskAct->setChecked(false);
		active->setSelectionMaskString(tr("None"));

		break;
		}
	}
	else {
	}
}

// Read the DLFL object from a file
void MainWindow::readObject(const char * filename, const char *mtlfilename) {
	active->clearSelected();
	ifstream file, mtlfile;
	file.open(filename);
	mtlfile.open(mtlfilename);

	if ( strstr(filename,".dlfl") || strstr(filename,".DLFL") )
		object.readDLFL(file, mtlfile);
	else if ( strstr(filename,".obj") || strstr(filename,".OBJ") )
		object.readObject(file, mtlfile);
	file.close();
}

// Read the DLFL object from a file
void MainWindow::readObjectQFile(QString filename) {
	active->clearSelected();
	QFile file(filename);
	file.open(QIODevice::ReadOnly);

	QByteArray ba = file.readAll();
	const char *filecontents = ba.data();
	string str(filecontents);
	istringstream filestring(str);

	ifstream mtlfile;
	// mtlfile = 0;

	if ( filename.indexOf(".dlfl") == filename.length()-4 || filename.indexOf(".dlfl") == filename.length()-4 )
		object.readDLFL(filestring, mtlfile);
	else if ( filename.indexOf(".OBJ") == filename.length()-4 || filename.indexOf(".obj") == filename.length()-4 )
		object.readObject(filestring, mtlfile);
	file.close();
}

// Write the DLFL object to a file
void MainWindow::writeObject(const char * filename, const char* mtlfilename, bool with_normals, bool with_tex_coords) {
	ofstream file;
	ofstream mtlfile;
	file.open(filename);
	mtlfile.open(mtlfilename);

	std::cout << mtlfilename << " = mtlfilename in writeObject function\n";

	if ( strstr(filename,".dlfl") || strstr(filename,".DLFL") )
		object.writeDLFL(file, mtlfile);
	else if ( strstr(filename,".obj") || strstr(filename,".OBJ") ){
		object.writeObject(file, mtlfile, with_normals,with_tex_coords);
	}
	file.close();
	mtlfile.close();
}

// Write the DLFL object to a file
void MainWindow::writeMTL(const char * filename) {
	ofstream file;
	file.open(filename);
	object.writeMTL(file);
	file.close();
}

// File handling
void MainWindow::openFile(void) {
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File..."),
																									mSaveDirectory, tr("All Supported Files (*.obj *.dlfl);;Wavefront OBJ Files (*.obj);;DLFL Files (*.dlfl);;All Files (*)"),
																									0, QFileDialog::DontUseSheet);
	if (!fileName.isEmpty()){
		if (!curFile.isEmpty()){
			undoPush();
			setModified(false);
		}
		QByteArray ba = fileName.toLatin1();
		const char *filename = ba.data();
		mWasPrimitive = false;
		mIsPrimitive = false;

		mSaveDirectory = QFileInfo(fileName).absoluteDir().absolutePath();
		QByteArray ba2 = mSaveDirectory.toLatin1();
		const char *dirname = ba2.data();
		object.setDirname( dirname );

		QString mtlfile = mSaveDirectory + "/" + QFileInfo(fileName).baseName() + ".mtl";
		QByteArray ba3 = mtlfile.toLatin1();
		const char *mtlfilename = ba3.data();

		setCurrentFile(fileName);
		std::cout << "filename for DLFL reading = " << filename << endl;
		readObject(filename, mtlfilename);

		active->recomputeNormals();
		active->redraw();
	}
}

bool MainWindow::saveFile(bool with_normals, bool with_tex_coords) {
	if (curFile != "untitled"){
		statusBar()->showMessage(tr("Saving File..."),3000);
		QString curFileTemp(curFile);

		if (!curFile.isEmpty() ){
			
			//add in the directory name
			QString fullpath = mSaveDirectory + "/" + curFileTemp;
			QByteArray ba = fullpath.toLatin1();
			const char *filename = ba.data();

			//materials test dave 11.07
			QString mtlFileName = fullpath;
			mtlFileName.replace(QString(".obj"),QString(".mtl"),Qt::CaseInsensitive);
			mtlFileName.replace(QString(".dlfl"),QString(".mtl"),Qt::CaseInsensitive);
			QByteArray ba2 = mtlFileName.toLatin1();
			const char *mtlfilename = ba2.data();
			// writeMTL(mtlfilename);

			writeObject(filename, mtlfilename, with_normals, with_tex_coords);


			setModified(false);
			// statusBar()->clearMessage();
			return true;
		}
		else {
			QString fileName = QFileDialog::getSaveFileName(this,
																											tr("Save File As..."),
																											mSaveDirectory + "/" + curFileTemp,
																											tr("All Supported Files (*.obj *.dlfl);;Wavefront OBJ Files (*.obj);;DLFL Files (*.dlfl);;All Files (*)"),
																											0, QFileDialog::DontUseSheet);
			if (!fileName.isEmpty()){
				//for incremental save test - dave
				//incremental_save_count = 0;
				

				if (!fileName.indexOf(".obj") || !fileName.indexOf(".dlfl") || !fileName.indexOf(".OBJ") || !fileName.indexOf(".DLFL"))
					fileName.append(".obj");
				setCurrentFile(fileName);

				mSaveDirectory = QFileInfo(fileName).absoluteDir().absolutePath();
				//mPreferencesDialog->setSaveDirectory(mSaveDirectory);

				QByteArray ba = fileName.toLatin1();
				const char *filename = ba.data();

				//materials test dave 11.07
				QString mtlFileName = fileName;
				mtlFileName.replace(QString(".obj"),QString(".mtl"),Qt::CaseInsensitive);
				mtlFileName.replace(QString(".dlfl"),QString(".mtl"),Qt::CaseInsensitive);
				QByteArray ba2 = mtlFileName.toLatin1();
				const char *mtlfilename = ba2.data();
				// writeMTL(mtlfilename);

				writeObject(filename, mtlfilename, with_normals,with_tex_coords);


				setModified(false);
				// statusBar()->clearMessage();
				return true;
			}
		}
	}
	// statusBar()->clearMessage();
	return false;
}

bool MainWindow::saveFileAs(bool with_normals, bool with_tex_coords) {

	statusBar()->showMessage(tr("Saving File..."));

	QString fileName = QFileDialog::getSaveFileName(this,
																									tr("Save File As..."),
																									mSaveDirectory + "/" + curFile,
																									tr("All Supported Files (*.obj *.dlfl);;Wavefront OBJ Files (*.obj);;DLFL Files (*.dlfl);;All Files (*)"),
																									0, QFileDialog::DontUseSheet );
	if (!fileName.isEmpty()){
		//reset the incremental save count no matter what...?
		//incremental_save_count = 0;
		
		if (!fileName.indexOf(".obj") || !fileName.indexOf(".dlfl") || !fileName.indexOf(".OBJ") || !fileName.indexOf(".DLFL"))
			fileName.append(".dlfl");
		setCurrentFile(fileName);

		mSaveDirectory = QFileInfo(fileName).absoluteDir().absolutePath();
		//mPreferencesDialog->setSaveDirectory(mSaveDirectory);

		QByteArray ba = fileName.toLatin1();
		const char *filename = ba.data();

		//materials test dave 11.07
		QString mtlFileName = fileName;
		mtlFileName.replace(QString(".obj"),QString(".mtl"),Qt::CaseInsensitive);
		mtlFileName.replace(QString(".dlfl"),QString(".mtl"),Qt::CaseInsensitive);
		QByteArray ba2 = mtlFileName.toLatin1();
		const char *mtlfilename = ba2.data();
		// writeMTL(mtlfilename);

		writeObject(filename, mtlfilename, with_normals,with_tex_coords);

	
		statusBar()->clearMessage();
		return true;
	}
	statusBar()->clearMessage();
	return false;
}

void MainWindow::setCurrentFile(QString fileName) {

	curFile = QFileInfo(fileName).fileName();

	//dir name for mtl loading...??? dave 11.07
	QString dirName = QFileInfo(fileName).absolutePath();
	QByteArray ba2 = dirName.toLatin1();
	const char *dirname = ba2.data();
	object.setDirname(dirname);

	//base file name for the mtllib thing...
	QString baseName = QFileInfo(fileName).baseName();
	QByteArray ba = baseName.toLatin1();
	const char *filename = ba.data();
	object.setFilename(filename);

	QString shownName;
	if (curFile.isEmpty())
		shownName = "untitled.obj";
	else
		shownName = curFile;

	setWindowTitle( tr("%1[*] - %2").arg(shownName).arg(tr("TopMod")));
	setModified(false);
}

/* dave - png opengl viewport screenshot export */
bool MainWindow::viewportScreenshot( ) {

	// viewportPixmap = QPixmap::grabWidget(active,0,0,active->width(),active->height());
	// viewportPixmap = QPixmap::grabWindow(active->winId(),/*mapToGlobal(active->pos()).x()*/0,/*mapToGlobal(active->pos()).y()*/0,active->width(),active->height());
	QImage image = active->grabFrameBuffer(true);
	QString format = "png";
	QString initialPath = mSaveDirectory + tr("/untitled.") + format;

	QString fileName = QFileDialog::getSaveFileName(this, tr("Save Viewport Screenshot As"),
																									initialPath,
																									tr("%1 Files (*.%2);;All Files (*)")
																									.arg(format.toUpper())
																									.arg(format),
																									0, QFileDialog::DontUseSheet);
	if (!fileName.isEmpty()){
		image.save(fileName, format.toAscii());
		return true;
	}
	return false;
}

void MainWindow::loadCube(){
	if (isModified())
		undoPush();
	setModified(false);
	mIsPrimitive = true;
	mWasPrimitive = true;
	setCurrentFile(tr("cube.obj"));
	readObjectQFile(":/cube.obj");

	active->recomputeNormals();
	active->redraw();
}

void MainWindow::loadOctahedron(){
	if (isModified())
		undoPush();
	setModified(false);
	mIsPrimitive = true;
	mWasPrimitive = true;
	setCurrentFile(tr("octahedron.obj"));
	readObjectQFile(":/octahedron.obj");

	active->recomputeNormals();
	active->redraw();
}

void MainWindow::loadTetrahedron(){
	if (isModified())
		undoPush();
	setModified(false);
	mIsPrimitive = true;
	mWasPrimitive = true;
	setCurrentFile(tr("tetrahedron.obj"));
	readObjectQFile(":/tetrahedron.obj");

	active->recomputeNormals();
	active->redraw();
}

void MainWindow::loadDodecahedron(){
	if (isModified())
		undoPush();
	setModified(false);
	mIsPrimitive = true;
	mWasPrimitive = true;
	setCurrentFile(tr("dodecahedron.obj"));
	readObjectQFile(":/dodecahedron.obj");

	active->recomputeNormals();
	active->redraw();
}

void MainWindow::loadIcosahedron(){
	if (isModified())
		undoPush();
	setModified(false);
	mIsPrimitive = true;
	mWasPrimitive = true;
	setCurrentFile(tr("icosahedron.obj"));
	readObjectQFile(":/icosahedron.obj");

	active->recomputeNormals();
	active->redraw();
}

void MainWindow::loadSoccerball(){
	if (isModified())
		undoPush();
	setModified(false);
	mIsPrimitive = true;
	mWasPrimitive = true;
	setCurrentFile(tr("soccerball.obj"));
	readObjectQFile(":/soccerball.obj");

	active->recomputeNormals();
	active->redraw();
}

void MainWindow::loadGeodesic(){
	if (isModified())
		undoPush();
	setModified(false);
	mIsPrimitive = true;
	mWasPrimitive = true;
	setCurrentFile(tr("geodesic.obj"));
	readObjectQFile(":/geodesic.obj");

	active->recomputeNormals();
	active->redraw();
}

bool MainWindow::isModified(){
	return mIsModified;
}

void MainWindow::setModified(bool isModified){
	mIsModified = isModified;
	setWindowModified(mIsModified);
}

void MainWindow::switchPerspView(){
	active->resetCamera();
	// active->switchTo(VPPersp);
	active->redraw();
}

//recurse through selected faces to get a list of checkerboard selection for the entire object
void MainWindow::getCheckerboardSelection(DLFLFacePtr fptr) {
	if (fptr){
		int numShared = 0;
		DLFLFacePtrArray fparray;
		vector<DLFLFacePtr>::iterator it;
		fptr->getNeighboringFaces(fparray);
		for ( it = fparray.begin(); it != fparray.end(); it++){
			if (fptr->sharesOneVertex((*it)) && !active->isSelected(*it)){
				numShared++;
				if (deselect_edges){
					active->clearSelectedFace(*it);
					num_sel_faces--;
				}
				else {
					active->setSelectedFace(*it);
					num_sel_faces++;
				}
				getCheckerboardSelection((*it));
			}
		}//end for loop
		if (numShared == 0) return; //break out of recursive loop is there are no one vertex sharing faces
	}
}

//recurse through selected edge to get a list of
void MainWindow::getEdgeLoopSelection(DLFLEdgePtr eptr) {
	if (eptr){
		//first check to see if edge only connects to only three other edges
		DLFLVertexPtr vp1, vp2;
		DLFLEdgePtrArray eparray;
		vector<DLFLEdgePtr>::iterator it;
		eptr->getVertexPointers(vp1,vp2);
		if (vp1->valence() == 4 && vp2->valence() == 4){
			//get edges conected to vertex 1
			eparray.clear();
			vp1->getEdges(eparray);
			//loop through them to find the one that doesn't share a face
			for (it = eparray.begin(); it != eparray.end(); it++){
				if ( !coFacial(*it,eptr) ){
					if (deselect_edges){
						active->clearSelectedEdge(*it);
						num_sel_edges--;
						getEdgeLoopSelection(*it);
					}
					else if (!active->isSelected(*it)){
						active->setSelectedEdge(*it);
						num_sel_edges++;
						getEdgeLoopSelection(*it);
					}
				}
			}//end for loop
			//get edges conected to vertex 2
			eparray.clear();
			vp2->getEdges(eparray);
			//loop through them to find the one that doesn't share a face
			for (it = eparray.begin(); it != eparray.end(); it++){
				if ( !coFacial(*it,eptr) ){
					if (deselect_edges){
						active->clearSelectedEdge(*it);
						num_sel_edges--;
						getEdgeLoopSelection(*it);
					}
					else if (!active->isSelected(*it)){
						active->setSelectedEdge(*it);
						num_sel_edges++;
						getEdgeLoopSelection(*it);
					}
				}
			}//end for loop
			return;
		}//end if vp->valence
		return;
	}
}

//recurse through selected edge to get a list of
void MainWindow::getFaceLoopSelection(DLFLEdgePtr eptr, bool start, DLFLFacePtr face_loop_marker, bool select_face_loop) {
	if ( (eptr == face_loop_start_edge) && !start)
		return;

	int idx = 0;
	DLFLEdgePtrArray edges;
	vector<DLFLEdgePtr>::iterator it;
	DLFLFacePtr fptr1, fptr2;
	//get the two faces corresponding to this edge ptr
	eptr->getFacePointers(fptr1,fptr2);
	//check if the two faces are quads
	if (fptr1 && fptr1->numFaceVertexes() == 4 && !(fptr1 == face_loop_marker) ){
		if (!active->isSelected(fptr1)){
			active->setSelectedFace(num_sel_faces,fptr1);
			num_sel_faces++;
		}
		fptr1->getEdges(edges);
		idx =0;
		for (it = edges.begin(); it != edges.end(); it++){
			if (*it == eptr){
				getFaceLoopSelection(edges[(idx+2)%4],false,fptr1, select_face_loop);
			}
			idx++;
		}//end for loop
	}
	if (fptr2 && fptr2->numFaceVertexes() == 4 && !(fptr2 == face_loop_marker) ){
		if (!active->isSelected(fptr2)){
			active->setSelectedFace(num_sel_faces,fptr2);
			num_sel_faces++;
		}
		fptr2->getEdges(edges);
		idx =0;
		for (it = edges.begin(); it != edges.end(); it++){
			if (*it == eptr){
				getFaceLoopSelection(edges[(idx+2)%4], false, fptr2, select_face_loop);
				// return;
			}
			idx++;
		}//end for loop
	}
}

//recurse through selected edge to get a list of
void MainWindow::getEdgeRingSelection(DLFLEdgePtr eptr, bool start, DLFLFacePtr face_loop_marker, bool select_face_loop) {
	if ( (eptr == edge_ring_start_edge) && !start)
		return;

	int idx = 0;
	DLFLEdgePtrArray edges;
	vector<DLFLEdgePtr>::iterator it;
	DLFLFacePtr fptr1, fptr2;
	if (!active->isSelected(eptr)){
		active->setSelectedEdge(eptr);
		num_sel_edges++;
	}
	//get the two faces corresponding to this edge ptr
	eptr->getFacePointers(fptr1,fptr2);
	//check if the two faces are quads
	if (fptr1 && fptr1->numFaceVertexes() == 4 && !(fptr1 == face_loop_marker) ){
		fptr1->getEdges(edges);
		idx =0;
		for (it = edges.begin(); it != edges.end(); it++){
			if (*it == eptr){
				getEdgeRingSelection(edges[(idx+2)%4],false,fptr1, select_face_loop);
			}
			idx++;
		}//end for loop
	}
	if (fptr2 && fptr2->numFaceVertexes() == 4 && !(fptr2 == face_loop_marker) ){
		fptr2->getEdges(edges);
		idx =0;
		for (it = edges.begin(); it != edges.end(); it++){
			if (*it == eptr){
				getEdgeRingSelection(edges[(idx+2)%4], false, fptr2, select_face_loop);
				// return;
			}
			idx++;
		}//end for loop
	}
}

void MainWindow::setPolygonalMode() {
  cout << "Switching to polygonal mode." << endl;
	mToolsToolBar->show();
	lightedRendererAct->setEnabled(true);
  wireframeRendererAct->setEnabled(true);
  texturedLightedAct->setEnabled(true);
  colorableRendererAct->setEnabled(true);
  texturedRendererAct->setEnabled(true);
  normalRendererAct->setEnabled(true);
}

void MainWindow::setPlanarMode() {
  cout << "Switching to planar mode." << endl;
	mToolsToolBar->hide();

	lightedRendererAct->setEnabled(true);
  wireframeRendererAct->setEnabled(true);
  texturedLightedAct->setEnabled(true);
  colorableRendererAct->setEnabled(true);
  texturedRendererAct->setEnabled(true);
  normalRendererAct->setEnabled(true);
}

DLFLObjectPtr MainWindow::GetObject() {
  return &object;
}

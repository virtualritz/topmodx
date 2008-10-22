/*** ***/

/******************************************
 * include.h
 *
 ******************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <QMainWindow>
#include <QWidget>
#include <QComboBox>
#include <QKeyEvent>
#include <QMenuBar>
#include <QMenu>
#include <QStyleOptionMenuItem>
//#include <QAssistantClient>
#include <QPen>
#include "GLWidget.h"

//the six modes are now separated into separate classes
#include "BasicsMode.h"

//#include "DLFLLighting.h"
#include <DLFLObject.h>
#include <DLFLConvexHull.h>

#include "include/WireframeRenderer.h"
#include "include/NormalRenderer.h"
#include "include/LitRenderer.h"
#include "include/TexturedRenderer.h"
#include "include/TexturedLitRenderer.h"
#include "include/ColorableRenderer.h"

// DLFLAux Library includes
#include <DLFLCast.h>
#include <DLFLConnect.h>
#include <DLFLConvexHull.h>
#include <DLFLCrust.h>
#include <DLFLDual.h>
#include <DLFLExtrude.h>
#include <DLFLMeshSmooth.h>
#include <DLFLMultiConnect.h>
#include <DLFLSculpting.h>
#include <DLFLSubdiv.h>

typedef StringStream * StringStreamPtr;
typedef list<StringStreamPtr> StringStreamPtrList;

class TopModPreferences;

class BasicsMode;
class ExtrusionsMode;
class RemeshingMode;
class ConicalMode;
class HighgenusMode;
class TexturingMode;
class ExperimentalMode;
class QAction;
class QMenu;
class GLWidget;
class QBoxLayout;
class QComboBox;
class QMenuBar;

using namespace DLFL;

class MainWindow : public QMainWindow {
	Q_OBJECT

	public:

		enum Mode	{
				NormalMode=0, 					/**< normal mode. does not allow any selection in the viewport. */
				SelectVertex=1, 				/**< select one vertex. */
				SelectEdge=2, 					/**< select one edge. */
				SelectFace=3, 					/**< select one face. */
				SelectCorner=4, 		/**< select one corner, which requires selection of a face and a vertex. */
				MultiSelectVertex=5,		/**< select multiple vertices. */
				MultiSelectEdge=6,			/**< select multiple edges. */
				MultiSelectFace=7,			/**< . */
				MultiSelectCorner=8,/**< . */
				SelectCheckerboard=9, 	/**< select alternating faces forming a checkerboard pattern. works well after Doo Sabin Remeshing. */
				SelectionWindow=10, 		/**< crossing window selection  - dave. */
				InsertEdge=11,					/**< insert edge. */
				DeleteEdge=12,					/**< delete an edge. */
				SubdivideEdge=13,				/**< subdivide an edge into n segments. */
				CollapseEdge=14,				/**< collapse an edge. */
				SpliceCorners=15,				/**< select two corners and collapse the face in between. */
				ConnectEdges=21,				/**< connect two half-edges. */
				ExtrudeFace=31,					/**< cubical extrusion. */
				ExtrudeFaceDS=32,				/**< doo sabin extrusion. */
				ExtrudeDualFace=33,			/**< dual of cubical extrusion. */
				ExtrudeFaceDodeca=34,		/**< dodecahedral extrusion. */
				ExtrudeFaceIcosa=35,		/**< icosahedral extrusion. */
				ExtrudeMultipleFaces=36,/**< cubical extrusion for multiple faces at once. */
				StellateFace=41,				/**< stellate extrusion. */
				DoubleStellateFace = 42,/**< double stellate extrusion. */
				ExtrudeFaceDome = 43,   /**< dome extrusion. dave */
				ConnectFaceVertices=51,	/**< add . */
				ConnectFaces=52,				/**< add hole/handle operation. */
				BezierConnectFaces=53,	/**< add handle operation. */
				HermiteConnectFaces=54,	/**< add handle operation. */
				ReorderFace=61,					/**< reorders the corners of a face. */
				SubdivideFace=62,				/**< subdivides a face into n faces. */
				CrustModeling=71,				/**< create a crust of the current model and poke holes in it. */
				CutEdge=200,						/**< // ozgur. */
				CutVertex=201,					/**< // ozgur. */
				CutEdgeandVertex = 202,	/**< // ozgur. */
				CutFace = 203,					/**< // ozgur. */
				TruncateEdge=204,				/**< // ozgur. */
				MarkEdge=206,						/**< // ozgur. */
				MarkVertex=207,					/**< // ozgur. */
				ConvexHullMode=301,			/**< create a convex hull or dual convex hull // ozgur. */
				EditVertex=81,					/**< select and move individual vertices // brianb. */
				SelectEdgeLoop=82,			/**< select an edge loop. shift select for multiple. */
				SelectEdgeRing=85,			/**< select an edge ring. shift select for multiple. */
				SelectFaceLoop=83,			/**< allows user to select one edge in the viewport and selects the corresponding face loop. shift select for multiple. */
				SelectSimilar=84, 			/**< select all sub objects with the same number of verts edges or faces whatever... . */
				SelectFacesByArea=856,	/**< select all faces with the a similar surface area. */
				SelectFacesByColor=857,	/**< select all faces with the same color material. */
				PaintFace=858,		 			/**< paint a face as you click. */
				EyeDropper=859		 			/**< grab the color of the selected face. */

			};

			enum SelectionMask {
				MaskObject=0,
				MaskVertices,
				MaskEdges,
				MaskFaces,
				MaskCorners,
				MaskNone
			};

			enum ExtrusionMode {
				CubicalExtrude,
				DooSabinExtrude,
				DodecahedralExtrude,
				IcosahedralExtrude,
				OctahedralExtrude, //!< also called dual
				StellateExtrude,
				DoubleStellateExtrude,
				DomeExtrude
			};

			enum ModelingMode {
				PlanarMode,
				PolygonalMode
			};

			enum RenderingMode {
				Wireframe,
				Normal,
				Lit,
				Textured,
				TexturedLit,
				Colorable
			};

	//!< Extrusions
	static double extrude_dist;            //!< Distance for an extrude
	static double extrude_rot;             //!< Rotation for an extrude
	static double extrude_scale;            //!< Scaling for an extrude
	static int num_extrusions;      //!< No. of segments for an extrude
	static double ds_ex_twist;
		static bool delete_edge_cleanup; //!< Flag for point-sphere cleanup after edge deletion

	static bool triangulate_new_faces;
	static bool scherk_collins;    //!< Use symmetric weight factors
  static double scherk_collins_pinch;
  static double scherk_collins_pinch_center;
  static double scherk_collins_pinch_width;

  static int scherk_collins_hole_num_segs;
  static int scherk_collins_hole_init_skip;
  static int scherk_collins_hole_skip;
  static int scherk_collins_hole_twist;
  static int scherk_collins_hole_seg_skip;
	//dave paint bucket tool - exp. 11.07
	static QColor paint_bucket_color;

	QString curFile;
	//document modified
	bool isModified();
	void setModified(bool isModified);

protected :

	//-- Selection count, used as index into selection lists --//
	static int num_sel_verts;        								    //!< No. of selected vertices
	static int num_sel_edges;         						      //!< No. of selected edges
	static int num_sel_faces;             						  //!< No. of selected faces
	static int num_sel_faceverts;												//!< No. of selected face vertices

	//-- should we deselect or select the current faces? --//
	static bool deselect_verts;
	static bool deselect_edges;
	static bool deselect_faces;
	static bool deselect_faceverts;

	static DLFLEdgePtr face_loop_start_edge; 						//!< face loop edge pointer
	static DLFLEdgePtr edge_ring_start_edge; 						//!< edge ring edge pointer
	static bool face_loop_start;												//!< face loop start

	GLWidget *active;															     	//!< Active viewport to handle events

	DLFLObject object;                            //!< The DLFL object
	Mode mode;																		//!< Current operating mode
	ExtrusionMode extrusionmode;														//!< Current operating mode
	SelectionMask selectionmask;            			//!< Current selection mask
	PointLight plight;														//!< Light used to compute lighting

	StringStreamPtrList undoList;                 //!< List for Undo
	StringStreamPtrList redoList;                 //!< List for Redo
	StringStreamPtrList undoMtlList;                 //!< Mtl List for Undo
	StringStreamPtrList redoMtlList;                 //!< Mtl List for Redo
	int undolimit;                                //!< Limit for undo
	bool useUndo;            											//!< Flag to indicate if undo will be used

	void initialize(int x, int y, int w, int h, DLFLRendererPtr rp);	//!< Initialize the viewports, etc.

public :

	MainWindow(char *filename = NULL);
	~MainWindow() {
		clearUndoList();
		clearRedoList();
		delete active;
	}

	DLFLObjectPtr GetObject();

	void clearSelected()	{
		active->clearSelected();
		MainWindow::clearNumSelected();
	}

	static void clearNumSelected() {
		num_sel_verts = 0;
		num_sel_edges = 0;
		num_sel_faces = 0;
		num_sel_faceverts = 0;
	}

	void getCheckerboardSelection(DLFLFacePtr fptr);		//!< \todo  needs to be moved to DLFL namespace
	void getEdgeLoopSelection(DLFLEdgePtr eptr);				//!< \todo  needs to be moved to DLFL namespace
	void getFaceLoopSelection(DLFLEdgePtr eptr, bool start, DLFLFacePtr face_loop_marker, bool select_face_loop);	//!< \todo  needs to be moved to DLFL namespace
	void getEdgeRingSelection(DLFLEdgePtr eptr, bool start, DLFLFacePtr face_loop_marker, bool select_face_loop);	//!< \todo  needs to be moved to DLFL namespace

	void createRenderers();															//!< allocate memory for the renderer pointers
	void destroyRenderers();														//!< delete memory allcated for the renderer pointers

	void setMode(Mode m);																//!< Switch to specified operating mode
	void setExtrusionMode(ExtrusionMode m);							//!< Switch to specified operating mode
	Mode getMode(){ return mode; };											//!< returns the current operation mode enum... this needs to return a string eventually. don't know how to do that yet
	void setSelectionMask(SelectionMask m);							//!< set the current selection mask (verts, edges, faces, multiple?)
	void setToolOptions(QWidget *optionsWidget);				//!< set the current tool option widget to be displayed in mToolOptionsDockWidget
	void loadFile(QString fileName);										//!< load an OBJ or a DLFL file

	QDockWidget *mToolOptionsDockWidget;					//!< the floating window that displays the current tool's options (spinboxes, checkboxes, etc...)
	QStackedWidget *mToolOptionsStackedWidget;		//!< the widget that references each tool option widget and handles switching the display

	QDockWidget *mStartupDialogDockWidget;
	QWidget *mStartupDialogWidget;
	QGridLayout *mStartupDialogLayout;
	bool mShowStartupDialogAtStartup;
	QLabel *quicktimeLabel;
	QLabel *downloadQuicktimeLabel;

protected:
	void closeEvent( QCloseEvent *event );				//!< what will execute when the main window is closed (on application exit/quit)

	// Renderers
	static WireframeRendererPtr wired;            //!< WireframeRenderer
	static NormalRendererPtr normal;              //!< Normal Renderer - white color - like a "hidden line" view
	static LitRendererPtr lit;                    //!< Lit Renderer
	static TexturedRendererPtr textured;          //!< Textured Renderer
	static TexturedLitRendererPtr texturedlit; 		//!< Textured and Lit Renderer
	static ColorableRendererPtr colorable;				//!< face colors... new ... by dave... 11/07

	BasicsMode *mBasicsMode;											//!< widget that holds all displayable option widgets for basic operating modes (InsertEdge, DeleteEdge, CollapseEdge, ConnectEdges, etc...)

private:
	//document modified
	bool mIsModified;															//!< bool to stop program from exiting if file has been edited but not saved
	bool mIsPrimitive;														//!< bool to stop program from exiting if file has been edited but not saved
	bool mWasPrimitive;														//!< bool to stop program from exiting if file has been edited but not saved, used in DLFLUndo.cc
  QString mSaveDirectory;
  QString mTextureSaveDirectory;
	bool mSingleClickExtrude;

	void createActions();													//!< create all MainWindow actions for menu's and icons, also create operating mode actions in subclasses
	void createMenus();														//!< create top-level QMenuBar and add actions to each QMenu
	void createToolBars();												//!< create toolbars with large icons for one-click operations
	void createStatusBar();												//!< status bar will display extra info about what different operations or buttons do in TopMod interface
	bool maybeSave();															//!< save before exit?

	//top level and sublevel menus
	QMenuBar *menuBar;														//!< the main menubar pointer to which all qmenu's will be added
	QMenu *mFileMenu;															//!< the file menu which contains save, save as, quit etc...
	QMenu *mExportMenu;
	QMenu *mEditMenu;															//!< undo, redo, clear undo list, and also preferences (except on os/x)
	QMenu *mDisplayMenu;													//!< all viewport display functionality (HUD, IDs, renderer, verts, faces, normals, etc...)
	QMenu *mViewMenu;															//!< probably going to remove... but could contain choices for which view to use (persp or left / right /top/ bottom etc...)
	QMenu *mShowIDsMenu;													//!< submenu of mDisplayMenu
	QMenu *mRendererMenu;													//!< now a submenu of mDisplayMenu
	QMenu *mModeMenu;													//!< now a submenu of mDisplayMenu
	QMenu *mPrimitivesMenu;												//!< stores actions for one-click loading of primitive objects
	QMenu *mNewMenu;															//!< stores same actions as the primitives menu plus a "new file" command that loads a blank object
	QMenu *mObjectMenu;														//!< \todo  needs to be removed. not necessary
	QMenu *mSelectionMenu;												//!< all different selection options
	QMenu *mSelectionMaskMenu;										//!< \todo  figure out how to integrate a selection mask functionality into the current implementation of mode switching in TopMod
	QMenu *mWindowMenu;														//!< menu choices for hiding and showing all floating windows and toolbars / also fullscreen mode
	QMenu *mHelpMenu;
	
	QMenu *mRightClickMenu;

	QMenu *mRemeshingMenu;
	QMenu *mToolsMenu;

	//File Menu Actions
	QAction *mNewFileAct;
	QAction *mOpenAct;
	QAction *mSaveAct;
	QAction *mScreenshotViewportAct;
	QAction *mSaveAsAct;
	QAction *loadTextureAct;
	QAction *printInfoAct;
	QAction *printFaceListAct;
	QAction *printVertexListAct;
	QAction *printEdgeListAct;
	QAction *mExitAct;

	QAction *mFullscreenAct;
	QAction *mPerformRemeshingAct;
	QAction *mPerformExtrusionAct;
	QAction *mSubdivideSelectedFacesAct;
	QAction *mPaintSelectedFacesAct;
	QAction *mClearMaterialsAct;
	QAction *mExtrudeMultipleAct; 					//!< temporary for now... not sure how to handle this in the future...
	QAction *mQuickCommandAct;

	//Edit Menu Actions
	QAction *mDeleteSelectedAct;						//!< delete the selected objects.
	QAction *mUndoAct;											//!< pop the previous model state off the undo stack
	QAction *mRedoAct;											//!< push the model back onto the undo stack
	QAction *mClearUndoListAct;							//!< clear the undo list to free up memory

	QAction *mZoomInAct;
	QAction *mZoomOutAct;

	//Display Menu Actions
	QAction *showVerticesAct;
	QAction *mShowFaceIDsAct;
	QAction *mShowEdgeIDsAct;
	QAction *mShowVertexIDsAct;
	QAction *mShowSelectedIDsAct;
	QAction *showSilhouetteAct;
	QAction *showWireframeAct;
	QAction *objectOrientationAct;
	QAction *mShowNormalsAct;
	QAction *showGridAct;
	QAction *showHUDAct;
	QAction *showCoordinateAxesAct;
	QAction *mAntialiasingAct;

	QAction *mShowFaceCentroidsAct;

	//Mode Menu Actions
	QAction *planarModelingAct;
	QAction *polygonalModelingAct;

	//Renderer Menu Actions
	QAction *wireframeRendererAct;
	QAction *normalRendererAct;
	QAction *shadedRendererAct;
	QAction *lightedRendererAct;
	QAction *texturedRendererAct;
	QAction *texturedLightedAct;
	QAction *colorableRendererAct;

	//Primitives Menu Actions
	QAction *pCubeAct;
	QAction *pDodecahedronAct;
	QAction *pIcosahedronAct;
	QAction *pTetrahedronAct;
	QAction *pSoccerBallAct;
	QAction *pOctahedronAct;
	QAction *pGeodesicAct;

	//Selection Menu Actions
	QAction *selectVertexAct;
	QAction *selectMultipleVerticesAct;
	QAction *mSelectMultipleAct;
	QAction *mEditVertexAct;
	QAction *selectFaceAct;
	QAction *selectFaceLoopAct;
	QAction *selectEdgeRingAct;
	QAction *mSubdivideSelectedEdgesAct;					//!< subdivide the selected edges.
	QAction *mCollapseSelectedEdgesAct;						//!< collapse the selected edges.
	QAction *selectMultipleFacesAct;
	QAction *selectSimilarFacesAct;
	QAction *mSelectSimilarAct;
	QAction *selectFacesByAreaAct;
	QAction *selectFacesByColorAct;
	QAction *mSelectionWindowAct;
	QAction *selectCheckerboardFacesAct;
	QAction *selectAllAct;
	QAction *mGrowSelectionAct;
	QAction *mSelectComponentAct;
	QAction *mShrinkSelectionAct;
	QAction *selectInverseAct;
	QAction *selectEdgeAct;
	QAction *selectMultipleEdgesAct;
	QAction *selectEdgeLoopAct;
	QAction *selectCornerAct;
	QAction *clearSelectedModeAct;
	QAction *exitSelectionModeAct;
	QAction *selectEdgesFromFacesAct;
	QAction *selectEdgesFromVerticesAct;
	QAction *selectFacesFromEdgesAct;
	QAction *selectFacesFromVerticesAct;
	QAction *selectVerticesFromFacesAct;
	QAction *selectVerticesFromEdgesAct;

	//selection mask actions
	QAction *mSelectVerticesMaskAct;
	QAction *mSelectFacesMaskAct;
	QAction *mSelectEdgesMaskAct;
	QAction *mSelectCornersMaskAct;

	//help menu
	QAction *mAboutAct;

	//Window Menu - toolbar display
	QAction *mEditToolBarAct;
	QAction *mSelectionMaskToolBarAct;
	QAction *mPrimitivesToolBarAct;
	QAction *mToolsToolBarAct;
	QAction *mHideToolBarsAct;
	QAction *mShowToolBarsAct;

	QWidget *mToolOptionsTitleBarWidget;
	QBoxLayout *mToolOptionsTitleBarLayout;

	//QToolbars
	QToolBar *mEditToolBar;
	QToolBar *mSelectionMaskToolBar;
	QToolBar *mPrimitivesToolBar;
	QToolBar *mToolsToolBar;


	//QActionGroups
	QActionGroup *mToolsActionGroup;
	QActionGroup *mModeActionGroup;
	QActionGroup *mRendererActionGroup;
	QActionGroup *mSelectionMaskActionGroup;

	//the status bar
	QStatusBar *mStatusBar;

	QAction *mShowToolOptionsAct;
	QAction *mShowStartupDialogAct;

	//for screenshots
	QPixmap viewportPixmap;
	QPixmap appPixmap;

public slots:

	bool viewportScreenshot(); //!< take a screenshot of just the opengl viewport

	// i18n stuff
	void about(); 												//!< \todo  topmod developer credits
	void documentWasModified();
	void toggleFullScreen();							//!< fullscreen mode in the mainwindow class... this is a test...

	void showAllToolBars();
	void hideAllToolBars();

	void load_texture();
	//renderers
	void useWireframeRenderer();
	void useNormalRenderer();
	void useLightedRenderer();
	void useTexturedRenderer();
	void useTexturedLitRenderer();
	void useColorableRenderer();

	void select_vertex();
	void select_multiple_vertices();
	void select_multiple();
	void edit_vertex();
	void select_face();
	void select_face_loop();
	void select_edge_ring();
	void select_multiple_faces();
	void select_similar_faces();
	void select_similar();
	void select_faces_by_area();
	void select_faces_by_color();
	void selection_window();
	void select_checkerboard_faces();
	void select_edge();
	void select_multiple_edges();
	void select_edge_loop();
	void select_corner();
	void exit_selection_mode();
	void clear_selected();
	void selectionMaskVertices();
	void selectionMaskFaces();
	void selectionMaskEdges();
	void selectionMaskCorners();
	void selectAll();
	void growSelection();
	void selectComponent();
	void selectVertex(DLFLVertexPtr vp);
	void shrinkSelection();
	void selectInverse();
	void selectEdgesFromFaces();
	void selectEdgesFromVertices();
	void selectFacesFromEdges();
	void selectFacesFromVertices();
	void selectVerticesFromFaces();
	void selectVerticesFromEdges();
	void reorderSelectedFaces();

	void clearMaterials();

	void deleteSelected();																						//!< delete selected objects

	// Extrusion
	void changeExtrudeLength(double value);
	void changeExtrudeRotation(double value);
	void changeExtrudeScale(double value);
	void changeNumExtrusions(double value);
void changeScherkCollinsPinch(double value);
  void changeScherkCollinsPinchCenter(double value);
  void changeScherkCollinsPinchWidth(double value);

  void changeScherkCollinsHoleNumSegments(double value);
  void changeScherkCollinsHoleInitSkip(double value);
  void changeScherkCollinsHoleSkip(double value);
  void changeScherkCollinsHoleTwist(double value);
  void changeScherkCollinsHoleSegSkip(double value);

  	void toggleTriangulateNewFaces(int state);
	void toggleScherkCollins(int state);
void deleteEdge(DLFLEdgePtr edgeptr);
	void edgeCleanup();
	//right click menu support coming soon...
	void mousePressEvent(QMouseEvent * event);
	void mouseReleaseEvent(QMouseEvent * event);
	void mouseMoveEvent(QMouseEvent * event);

	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);

	void dragEnterEvent(QDragEnterEvent *event);
	void dropEvent(QDropEvent *event);

	void getRightClickMenu();

	void switchPerspView();

	void setUndoLimit(int limit);
	void toggleUndo();

	void clearUndoList();      // Erase all elements on Undo list
	void clearRedoList();      // Erase all elements on Redo list
	void undoPush();         // Put current object onto undo list
	void undo();                           // Undo last operation
	void redo();              // Redo previously undone operation

	void setPlanarMode();
    void setPolygonalMode();
	void setRenderer(DLFLRendererPtr rp);

	void doSelection(int x, int y);
	// Return pointer to the active GLWidget
	GLWidget *getActive();

	void redraw();				//!< Override redraw() method to mark subwindows also for redraw
		// Geometric transformations
	void translatex(double x);
	void translatey(double y);
	void translatez(double z);
	void scalex(double x);
	void scaley(double y);
	void scalez(double z);
	void freezeTransforms();
	void performExtrusion(); //!< Generic method for all extrusion schemes on multiple faces
	void setSingleClickExtrude(int value);
	// File handling
	void openFile();
	void openFile(QString fileName);
	bool saveFile(QString fileName);
	void newFile();
	bool saveFile(bool with_normals=true, bool with_tex_coords=true);
	bool saveFileAs(bool with_normals=true, bool with_tex_coords=true);
	void setCurrentFile(QString fileName);

	// Read the DLFL object from a file
	void readObject(const char * filename, const char *mtlfilename = NULL);
	void readObjectQFile(QString file);
	// Write the DLFL object to a file
	void writeObject(const char * filename, const char *mtlfilename = NULL, bool with_normals=true, bool with_tex_coords=true);
	void writeMTL(const char * filename);

	//primitive slot functions finally work
	void loadCube();
	void loadOctahedron();
	void loadTetrahedron();
	void loadDodecahedron();
	void loadIcosahedron();
	void loadSoccerball();
	void loadGeodesic();

};

#endif

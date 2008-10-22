/*** ***/

#include "GLWidget.h"
#include "DLFLSelection.h"

GLWidget::GLWidget(int w, int h, DLFLRendererPtr rp, QColor color, QColor vcolor, DLFLObjectPtr op, const QGLFormat & format, QWidget * parent ) 
 : 	QGLWidget(format, parent, NULL), /*viewport(w,h,v),*/ object(op), renderer(rp), renderObject(true),
	mRenderColor(color), mViewportColor(vcolor),/*grid(ZX,20.0,10),*/ showgrid(false), showaxes(false), mUseGPU(false), mAntialiasing(true) { 
	
    mParent = parent;
    
    //accept file drop events
	setAcceptDrops(true);

    // Vector3d neweye = eye - center;
	// double eyedist = norm(neweye);
	// Matrix4x4 lmat = Transformation::lookat(neweye,Vector3d(0,0,0),up);
	// transform = lmat;
	// transform.translate(-center);
	// camera.setEye(Vector3d(0,0,eyedist));
	
	
	//take cross product of lookat and up vector - and you're given one that looks right...
	//then cross that with the lookat and you get the real up
	Vector3d Aim(0,0,0);
	Vector3d Pos(10,10,10);
	Vector3d Up(-0.40824829046,0.81649658093,-0.40824829046);
	mCamera = new PerspCamera( Vector3d(10,10,10), Vector3d(0,0,0), Vector3d(0,1,0));

	//set color defaults
	setViewportColor(QColor(67, 68, 88));
	setRenderColor(QColor(255, 151, 92));
	setCoolLightColor(QColor(27, 26, 23));
	setWarmLightColor(QColor(255, 250, 226));
	setWireframeColor(QColor(0, 0, 0, 255));
	setSilhouetteColor(QColor(0, 0, 0, 255));
	setSelectedVertexColor(QColor(0, 255, 0, 127));
	setSelectedEdgeColor(QColor(255, 0, 0, 127));
	setSelectedFaceColor(QColor(247, 0, 229, 127));
	setVertexIDBgColor(QColor(127, 0, 0, 127));
	setNormalColor(QColor(127, 0, 127));
	setFaceCentroidColor(QColor(127, 0, 127));
	setFaceIDBgColor(QColor(0, 0, 127, 127));
	setEdgeIDBgColor(QColor(0, 127, 0, 127));
}

GLWidget::~GLWidget(){ 
}

void GLWidget::redraw() {
	repaint();
}

void GLWidget::initializeGL( ) {
		
	
	setAutoBufferSwap( true );
	glClearColor(mViewportColor.redF(),mViewportColor.greenF(),mViewportColor.blueF(),mViewportColor.alphaF());
	mCamera->SetProjection(width(),height());
	// viewport.resize(this->size().width(),this->size().height());
	if (mAntialiasing){
    glEnable( GL_LINE_SMOOTH );
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);									// Set Line Antialiasing
	}
	else {
    glDisable( GL_LINE_SMOOTH );
	}

	glShadeModel(GL_SMOOTH);
	glEnable(GL_BLEND);																			// Enable Blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);			// Type Of Blending To Use
	
	//initialize light position and color
	plight.position.set(50,25,0);
	plight.warmcolor.set(1,.95,0.886);
	plight.coolcolor.set(0.11,.11,0.09);
	plight.intensity = 2.0;

	mGlobalAmbient = QColor(0,0,0);
	
	mShowVertexIDs = false;
	mShowEdgeIDs   = false;
	mShowFaceIDs   = false;
	mShowFaceVertexIDs = false;
	mShowSelectedIDs = false;
	mShowHUD = false;
	mBrushSize = 2.5;
	mShowBrush = false;
	mShowSelectionWindow = false;
	setMouseTracking(true);
	
}

void GLWidget::paintEvent(QPaintEvent *event){
	
	//clear to a white background
	//   glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
	// glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	//   glLoadIdentity();
	//   glMatrixMode(GL_MODELVIEW);
	//   glViewport(0,0, width(), height() );	
	//   glLoadIdentity();
	// //transform the camera
	//   mCamera->SetProjection(width(),height());

	QPainter painter;
	painter.begin(this);
	painter.setRenderHint(QPainter::Antialiasing);
	
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	// viewport.resize(width(),height());
	// mCamera->SetProjection(width(),height());

	if( renderer ){
		renderer->initialize();	
	}
	
	glClearColor(mViewportColor.redF(),mViewportColor.greenF(),mViewportColor.blueF(),mViewportColor.alphaF());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// setupViewport(width(), height());
	glEnable(GL_DEPTH_TEST);
	// Multiply by the transformation matrix. dave and stuart*
	// glMatrixMode(GL_PROJECTION);
	//   glLoadIdentity();
	//   if ( pickmode ){
	// 	gluPickMatrix(mousex, mousey, pickw, pickh, viewport);
	// }
	// gluPerspective(FOV, WinX/(float)WinY, nearplane, farplane);
	// glMatrixMode(GL_MODELVIEW);
	// glLoadIdentity( );
	// SetCamera();
	mCamera->SetProjection(width(),height());

	// Draw the axes if required. Use thick lines
	if ( showaxes ) {
		glLineWidth(3.0);
		glEnable(GL_LINE_STIPPLE);
		glLineStipple(2,0xAAAA);
		glBegin(GL_LINES);
		glColor3f(0.5,0.25,0.25);                     // X Axis - Red
		glVertex3f(0,0,0); glVertex3f(-10,0,0);
		glColor3f(0.25,0.5,0.25);                     // Z Axis - Green
		glVertex3f(0,0,0); glVertex3f(0,0,-10);
		glColor3f(0.25,0.25,0.5);                     // Y Axis - Blue
		glVertex3f(0,0,0); glVertex3f(0,-10,0);
		glEnd();
		glDisable(GL_LINE_STIPPLE);
		glBegin(GL_LINES);
		glColor3f(0.6,0.25,0.25);                     // X Axis - Red
		glVertex3f(0,0,0); glVertex3f(10,0,0);
		glColor3f(0.25,0.6,0.25);                     // Z Axis - Green
		glVertex3f(0,0,0); glVertex3f(0,0,10);
		glColor3f(0.25,0.25,0.6);                     // Y Axis - Blue
		glVertex3f(0,0,0); glVertex3f(0,10,0);
		glEnd();
		glLineWidth(3.0);
	}	
	glDepthRange(0,1);
	
	if ( renderer ) {
		if (renderObject){
		  renderer->render(object);
		}
	}
	// Adjust the depthrange so selected items are shown clearly
	glDepthRange(0,1-0.0005-0.0005);
	drawSelected();
	glDepthRange(0,1);
	
	GLdouble model[4][4], proj[4][4];
	GLint view[4];
	
	#ifndef Q_WS_QWS
	glGetDoublev(GL_MODELVIEW_MATRIX, &model[0][0]);
	glGetDoublev(GL_PROJECTION_MATRIX, &proj[0][0]);
	glGetIntegerv(GL_VIEWPORT, &view[0]);
	#endif
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f,(GLfloat)width()/(GLfloat)height(),0.1f,100.0f);
	
	glPopAttrib();
  glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// glTranslated(0.0, 0.0, -50.0);	
  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
	
	drawSelectionWindow(&painter);	
	//drawBrush(&painter);
	drawHUD(&painter);
	drawSelectedIDs(&painter, &model[0][0], &proj[0][0], &view[0]);
	drawIDs(&painter, &model[0][0], &proj[0][0], &view[0]); // draw vertex, edge and face ids
	
	
	//try out some code to put an axis in the bottom left corner of the screen  
	glViewport(10.0,10.0,50.0,50.0);
	
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	
	glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
	gluPerspective(10.0, 1.0, 1.0, 100);
	// gluOrtho(-10.0, 10.0, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity( );
	Vector3d t = normalized(mCamera->getEye() - mCamera->getCenter())*10.0;
	gluLookAt(t[0], t[1], t[2],
						//mCamera->getEye()[0],mCamera->getEye()[1],mCamera->getEye()[2],
						// mCamera->getCenter()[0],mCamera->getCenter()[1],mCamera->getCenter()[2],
						0.0,0.0,0.0,
						mCamera->getUp()[0],mCamera->getUp()[1],mCamera->getUp()[2]);
						// 0.0,1.0,0.0);
	glDisable(GL_BLEND);
	glLineWidth(1.5);
	glBegin(GL_LINES);
	glColor3f(1.0,0.25,0.25);                     // X Axis - Red
	glVertex3f(0,0,0); glVertex3f(1,0,0);
	glColor3f(0.25,1.0,0.25);                     // Z Axis - Green
	glVertex3f(0,0,0); glVertex3f(0,0,1);
	glColor3f(0.25,0.25,1.0);                     // Y Axis - Blue
	glVertex3f(0,0,0); glVertex3f(0,1,0);
	glEnd();
	glLineWidth(3.0);
	glEnable(GL_BLEND);																			// Enable Blending
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f,(GLfloat)width()/(GLfloat)height(),0.1f,100.0f);
	
	glPopAttrib();
  glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// glTranslated(0.0, 0.0, -50.0);	
  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
	
	painter.end();
}

void GLWidget::resizeGL( int width, int height ){
	// setupViewport(width,height);
	// drawText(this->size().width(),this->size().height());	
	if (height==0)	height=1; 							//Making Height Equal One
	glViewport( 0, 0, (GLint)width, (GLint)height );
	
	// viewport.resize(this->size().width(),this->size().height());
}

void GLWidget::setupViewport(int width, int height){	
	// mScene->resize(width,height);
  // setup viewport, projection etc.:

	// glViewport(0, 0, width, height);
	// // glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	// // glLoadIdentity();												// Reset The Projection Matrix
	// // // Calculate The Aspect Ratio Of The Window
	// // gluPerspective(60.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);
	// glMatrixMode(GL_MODELVIEW);						// Select The Modelview Matrix
}

void GLWidget::drawText(int width, int height ){	
}

/**
 * \brief draw a selection window when in the proper mode
 *	by dave - experimental
 */
void GLWidget::drawSelectionWindow(QPainter *painter){
	if (mShowSelectionWindow){
		QBrush brush = QBrush(QColor(0,0,0,255));
		QPen pen = QPen(brush,1.0);
		painter->setPen(pen);
		painter->setBrush(QBrush(QColor(0,0,0,50)));//Qt::NoBrush);
		//get the mouse position from global coordinate system
		int x = mapFromGlobal(QCursor::pos()).x();
		int y = mapFromGlobal(QCursor::pos()).y();
		// std::cout << "y = " << y << "\t\tYY = " << mSelectionWindowStartY <<" \n";
		painter->drawRect(mSelectionWindowStartX,height()-mSelectionWindowStartY, x-mSelectionWindowStartX, y-(height()-mSelectionWindowStartY));
		// painter->drawRect(1,0, x, y);
	}
}

void GLWidget::drawBrush(QPainter *painter){
	if (mShowBrush){
		QBrush brush = QBrush(QColor(255,0,0,127));
		QPen pen = QPen(brush,4.0);
		painter->setPen(pen);
		painter->setBrush(Qt::NoBrush);
		//get the mouse position from global coordinate system
		int x = mapFromGlobal(QCursor::pos()).x();
		int y = mapFromGlobal(QCursor::pos()).y();
		painter->drawEllipse(x - mBrushSize/2, y - mBrushSize/2, mBrushSize, mBrushSize);
		painter->drawLine(x-10,y,x+10,y);
		painter->drawLine(x,y-10,x,y+10);
	}
}

//the Heads up display should show the current object's 
//number of vertices, faces, edges, the genus
//number of selected vertices, edges, faces, face vertices, and eventually objects
//other data that could be shown will be added later
void GLWidget::drawHUD(QPainter *painter){	
	if (mShowHUD){
		
		if (mSelectionMaskString == "Faces"){
		//show info about a selected face	
			if (numSelectedFaces() == 1) {
				DLFLFacePtr fp = object->sel_fptr_array[0];
			}
		}
		if (mSelectionMaskString == "Edges"){
		//show info about a selected edge	
			if (numSelectedEdges() == 1) {
				DLFLEdgePtr ep = object->sel_eptr_array[0];
			}			
		}
		if (mSelectionMaskString == "Vertices"){
		//show info about a selected vertex	
			if (numSelectedVertices() == 1) {
				DLFLVertexPtr vp = object->sel_vptr_array[0];
			}
		}
		if (mSelectionMaskString == "Corners"){
		//show info about a selected corner	
			if (numSelectedCorners() == 1) {
				DLFLFaceVertexPtr fvp = object->sel_fvptr_array[0];
				// std::cout << fvp << "\n";
			}
		}
		
		QString s1 = "Vertices: " + QString("%1").arg((uint)object->num_vertices()) +
		 						"\nEdges: " + QString("%1").arg((uint)object->num_edges()) +
								"\nFaces: " + QString("%1").arg((uint)object->num_faces()) +
								"\nMaterials: " + QString("%1").arg((uint)object->num_materials()) +
								"\nGenus: " + QString("%1").arg(object->genus());

		QString s2 = "Sel. Vertices:" + QString("%1").arg(numSelectedVertices()) +
		 						"\nSel. Edges: " + QString("%1").arg(numSelectedEdges()) +
								"\nSel. Faces: " + QString("%1").arg(numSelectedFaces()) +
								"\nSel. Corners: " + QString("%1").arg(numSelectedCorners());

		QString s3 = 	"Mode: " + mModeString + 
                        "\nRemeshing Mode: " + mRemeshingSchemeString + 
                        "\nExtrusion Mode: " + mExtrusionModeString + 
                        "\nSelection Mode: " + mSelectionMaskString +
                        "\nRendering Mode: " + mRenderingModeString +
                        "\nModeling Mode: " + mModelingModeString;
									
		
		
		// QString s4 = ""
		QFont font("Arial", 11);
		QFontMetrics fm(font);
		// painter->setFont(font);

		QRect r1(fm.boundingRect(s1));
		// std::cout<<r1.width() << "\n";
		QRect r2(fm.boundingRect(s2));
		QRect r3(fm.boundingRect(s3));

		painter->setPen(Qt::NoPen);
		QBrush brush = QBrush(QColor(0,0,0,127));
		painter->setBrush(brush);
		QRectF rectangle(0.0, height()-r1.height()*7, width(), height());
		// painter->drawRoundRect(QRect(3.0,3.0,rectangle.width(),rectangle.height()),25,25);
		painter->drawRect(rectangle);
		painter->setPen(Qt::white);
		painter->drawText(rectangle.left()+65, 										rectangle.top()+5,	r3.width(),	rectangle.height(),Qt::AlignLeft, s3);
		painter->drawText(/*fm.width(s3)*/280, 										rectangle.top()+5, 	r1.width(), rectangle.height(),Qt::AlignLeft, s1);
		painter->drawText(/*fm.width(s3)+fm.width(s1)*/460, 			rectangle.top()+5, 	r2.width(),	rectangle.height(),Qt::AlignLeft, s2);
	}
}

void GLWidget::drawIDs( QPainter *painter, const GLdouble *model, const GLdouble *proj, const GLint	*view) {
	glDisable(GL_DEPTH_TEST);
	GLdouble win_x = 0, win_y = 0, win_z = 0;	
	double min_dist=100000000.0, max_dist=-100000000.0, x,y,z,d;
	int count, min_alpha = 25, max_alpha = 255;
	// Vector3d coord = viewport.camera.getPos(); //use this to find the dist from the camera
	Vector3d coord = mCamera->getEye(); //use this to find the dist from the camera
	QBrush brush;
	
	Vector3d offset = object->position;
	
	/* Draw Vertex IDs */
	if( mShowVertexIDs ) {
		DLFLVertexPtrArray vparray;
		object->getVertices(vparray);
		double vlsqr_array[vparray.size()];
		count = 0;
		DLFLVertexPtrArray::iterator it;
		for( it = vparray.begin(); it != vparray.end(); it++) {
			Vector3d dist = (*it)->coords - coord;
			vlsqr_array[count] = dist.lengthsqr();
			max_dist = (vlsqr_array[count] > max_dist ) ? vlsqr_array[count] : max_dist;
			min_dist = (vlsqr_array[count] < min_dist ) ? vlsqr_array[count] : min_dist;
			count++;
		}
		count = 0;
		for( it = vparray.begin(); it != vparray.end(); it++) {
			Vector3d point = (*it)->coords;
			point = object->tr.applyTo(point);
			//point += object->position;
			point.get(x,y,z);		
			QString id = QString::number((*it)->getID() );
			if(max_dist == min_dist)
				d = min_alpha;
			else
				d = (vlsqr_array[count]-min_dist)*(max_alpha-min_alpha)/(max_dist - min_dist) + min_alpha;
			gluProject(x, y, z, model, proj, view, &win_x, &win_y, &win_z);
			win_y = height() - win_y; // y is inverted
			painter->setPen(Qt::NoPen);
			brush = QBrush(QColor(mVertexIDBgColor.red(),mVertexIDBgColor.green(),mVertexIDBgColor.blue(),min_alpha+max_alpha-d));
			painter->setBrush(brush);
			QRectF rectangle(win_x, win_y, 35, 20);
			painter->drawRoundRect(rectangle,6,6);
			painter->setPen(QColor(255,255,255,min_alpha+max_alpha-d));
			painter->drawText(rectangle, Qt::AlignCenter,id);
			count++;
		}
	}

	/* Draw Edge IDs */
	if( mShowEdgeIDs ) {
		DLFLEdgePtrArray eparray;
		object->getEdges(eparray);
		double elsqr_array[eparray.size()];
		count = 0;
		DLFLEdgePtrArray::iterator it;
		for( it = eparray.begin(); it != eparray.end(); it++) {
			Vector3d dist = (*it)->getMidPoint() - coord;
			elsqr_array[count] = dist.lengthsqr();
			max_dist = (elsqr_array[count] > max_dist ) ? elsqr_array[count] : max_dist;
			min_dist = (elsqr_array[count] < min_dist ) ? elsqr_array[count] : min_dist;
			count++;
		}
		count=0;
		for( it = eparray.begin(); it != eparray.end(); it++) {
			QString id = QString::number( (*it)->getID() );
			Vector3d point = (*it)->getMidPoint();
			point = object->tr.applyTo(point);
			point.get(x,y,z);
			if(max_dist == min_dist)
				d = min_alpha;
			else
				d = (elsqr_array[count]-min_dist)*(max_alpha-min_alpha)/(max_dist - min_dist) + min_alpha;
			gluProject(x, y, z, model, proj, view, &win_x, &win_y, &win_z);
			win_y = height() - win_y; // y is inverted
			painter->setPen(Qt::NoPen);
			// std::cout<< min_alpha << " " << max_alpha << " "<< d << std::endl;
			brush = QBrush(QColor(mEdgeIDBgColor.red(),mEdgeIDBgColor.green(),mEdgeIDBgColor.blue(),min_alpha+max_alpha-d));
			painter->setBrush(brush);
			QRectF rectangle(win_x, win_y, 35, 20);
			painter->drawRoundRect(rectangle,6,6);
			painter->setPen(QColor(255,255,255,min_alpha+max_alpha-d));
			painter->drawText(rectangle, Qt::AlignCenter,id);
			count++;
		}
	}
	
	/* Draw Face IDs */
	if( mShowFaceIDs ) {
		DLFLFacePtrArray fparray;
		object->getFaces(fparray);
		double flsqr_array[fparray.size()];
		count = 0;
		DLFLFacePtrArray::iterator it;
		for( it = fparray.begin(); it != fparray.end(); it++) {
			Vector3d dist = (*it)->geomCentroid() - coord;
			flsqr_array[count] = dist.lengthsqr();
			max_dist = (flsqr_array[count] > max_dist ) ? flsqr_array[count] : max_dist;
			min_dist = (flsqr_array[count] < min_dist ) ? flsqr_array[count] : min_dist;
			count++;
		}
		count=0;
		for( it = fparray.begin(); it != fparray.end(); it++) {
			QString id = QString::number( (*it)->getID() );
			Vector3d point = (*it)->geomCentroid();// + (*it)->getNormal();
			point = object->tr.applyTo(point);
			point.get(x,y,z);
			if(max_dist == min_dist)
				d = min_alpha;
			else
				d = (flsqr_array[count]-min_dist)*(max_alpha-min_alpha)/(max_dist - min_dist) + min_alpha;
			gluProject(x, y, z, model, proj, view, &win_x, &win_y, &win_z);
			win_y = height() - win_y; // y is inverted
			painter->setPen(Qt::NoPen);
			brush = QBrush(QColor(mFaceIDBgColor.red(),mFaceIDBgColor.green(),mFaceIDBgColor.blue(),min_alpha+max_alpha-d));
			painter->setBrush(brush);
			QRectF rectangle(win_x, win_y, 35, 20);
			painter->drawRoundRect(rectangle,6,6);
			painter->setPen(QColor(255,255,255,min_alpha+max_alpha-d));
			painter->drawText(rectangle, Qt::AlignCenter,id);
			count++;
		}
	}

	glPopMatrix( );
	glEnable(GL_DEPTH_TEST);
}

void GLWidget::drawSelectedIDs( QPainter *painter, const GLdouble *model, const GLdouble *proj, const GLint	*view) {
	if (mShowSelectedIDs){
		glDisable(GL_DEPTH_TEST);
		
		glPushMatrix( );
		double mat[16];
		object->tr.fillArrayColumnMajor(mat);
		glMultMatrixd(mat);
	
		double x,y,z;
		QBrush brush;
		QRectF rectangle;
		QString id;
		GLdouble win_x = 0, win_y = 0, win_z = 0;
	
		if( !mShowVertexIDs ) {
			if ( !object->sel_vptr_array.empty() ){
				DLFLVertexPtrArray::iterator first, last;
				first = object->sel_vptr_array.begin(); last = object->sel_vptr_array.end();
				while ( first != last ){
					QString id = QString::number( (*first)->getID() );
					double x,y,z;
					Vector3d point = (*first)->coords;// + (*it)->getNormal();
					point = object->tr.applyTo(point);
					point.get(x,y,z);
					win_x = 0, win_y = 0, win_z = 0;
					gluProject(x, y, z, model, proj, view, &win_x, &win_y, &win_z);
					win_y = height() - win_y; // y is inverted
					painter->setPen(Qt::NoPen);
					brush = QBrush(QColor(mVertexIDBgColor));
					painter->setBrush(brush);
					rectangle = QRectF(win_x, win_y, 40, 20);
					painter->drawRoundRect(rectangle,6,6);
					painter->setPen(Qt::white);
					painter->drawText(rectangle, Qt::AlignCenter,id);
					++first;
				}
			}
		}
	
		if( !mShowEdgeIDs ) {
			if ( !object->sel_eptr_array.empty() ){
				DLFLEdgePtrArray::iterator first, last;
				first = object->sel_eptr_array.begin(); last = object->sel_eptr_array.end();
				while ( first != last ){
					QString id = QString::number( (*first)->getID() );
					Vector3d point = (*first)->getMidPoint(true);
					point = object->tr.applyTo(point);
					point.get(x,y,z);
					win_x = 0, win_y = 0, win_z = 0;
					gluProject(x, y, z, model, proj, view, &win_x, &win_y, &win_z);
					win_y = height() - win_y; // y is inverted
					painter->setPen(Qt::NoPen);
					QBrush brush = QBrush(QColor(mEdgeIDBgColor));
					painter->setBrush(brush);
					rectangle = QRectF(win_x, win_y, 40, 20);
					painter->drawRoundRect(rectangle,6,6);
					painter->setPen(Qt::white);
					painter->drawText(rectangle, Qt::AlignCenter,id);
					++first;
				}
			}
		}

		if( !mShowFaceIDs ) {
			if ( !object->sel_fptr_array.empty() ){
				DLFLFacePtrArray::iterator first, last;
				first = object->sel_fptr_array.begin(); last = object->sel_fptr_array.end();
				while ( first != last )	{
					QString id = QString::number( (*first)->getID() );
					double x,y,z; 
					Vector3d point = (*first)->geomCentroid();// + (*it)->getNormal();
					point = object->tr.applyTo(point);
					point.get(x,y,z);
					win_x = 0, win_y = 0, win_z = 0;
					gluProject(x, y, z, model, proj, view, &win_x, &win_y, &win_z);
					win_y = height() - win_y; // y is inverted
					painter->setPen(Qt::NoPen);
					brush = QBrush(QColor(mFaceIDBgColor));
					painter->setBrush(brush);
					rectangle = QRectF(win_x, win_y, 40, 20);
					painter->drawRoundRect(rectangle,6,6);
					painter->setPen(Qt::white);
					painter->drawText(rectangle, Qt::AlignCenter,id);
					++first;
				}
			}
		}

		if( !mShowFaceVertexIDs ) {
			if ( !object->sel_fvptr_array.empty() ) {
				DLFLFaceVertexPtrArray::iterator first, last;
				first = object->sel_fvptr_array.begin(); last = object->sel_fvptr_array.end();
				while ( first != last ){
					QString id = QString::number( (*first)->vertex->getID() );
					double x,y,z; 
					Vector3d point = (*first)->vertex->coords;
					point = object->tr.applyTo(point);
					point.get(x,y,z);
					win_x = 0, win_y = 0, win_z = 0;
					gluProject(x, y, z, model, proj, view, &win_x, &win_y, &win_z);
					win_y = height() - win_y; // y is inverted
					painter->setPen(Qt::NoPen);
					brush = QBrush(QColor(mVertexIDBgColor));
					painter->setBrush(brush);
					rectangle = QRectF(win_x, win_y, 40, 20);
					painter->drawRoundRect(rectangle,6,6);
					painter->setPen(Qt::white);
					painter->drawText(rectangle, Qt::AlignCenter,id);
					++first;
				}
			}
		} 
		glPopMatrix( );
		glEnable(GL_DEPTH_TEST);
	}
}

// void GLWidget::toggleFullScreen( ) {
// 	std::cout<<"toggle fullscreen mode\n";
// 	// if( !mIsFullScreen ) {   
// 		setWindowState(windowState() ^ Qt::WindowFullScreen);
// 		// setWindowState(Qt::WindowFullScreen);
// 		// move(0,20);
// 		// resize( QApplication::desktop()->size() );
// 		// resizeGL( QApplication::desktop()->size().width(), QApplication::desktop()->size().height() );
// 		// setFocusPolicy( Qt::StrongFocus );
// 		// setWindowFlags( Qt::FramelessWindowHint );
// 		// show();
// 	// } else {
// 	// 	// setWindowFlags( Qt::Widget );
// 	// 	resize( 700, 800 );
// 	// 	show();
// 	// }
// 	// mIsFullScreen != mIsFullScreen;
// }

// Subroutine for selecting a Vertex
DLFLVertexPtr GLWidget::selectVertex(int mx, int my, int w, int h) {
	GLuint selectBuf[8192];
	uint closest;
	GLuint dist;
	long hits, index;
	DLFLVertexPtr sel(NULL);

	glSelectBuffer(8192,selectBuf);
	glRenderMode(GL_SELECT);

	glInitNames(); glPushName(0);

	GLint vp[4];
	glGetIntegerv(GL_VIEWPORT, vp);
	// viewport.camera.enterSelectionMode(mx,my,30,30,vp); // Reduced sensitivity for picking points
	mCamera->enterSelectionMode(mx,my,w,h,vp); // Reduced sensitivity for picking points

	// Make sure earlier matrices are preserved, since multiple windows
	// seem to be sharing the same matrix stacks
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	// viewport.reshape();
	// viewport.apply_transform();
	// glViewport(0,0,width(),height());
	mCamera->SetProjection(width(),height());
	// viewport.apply_transform();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderVerticesForSelect(object);
	glFlush();

	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	mCamera->leaveSelectionMode();

	hits = glRenderMode(GL_RENDER);
	if ( hits > 0 ){
		closest = 0; dist = 0xffffffff;
		while ( hits ){
			index = (hits-1)*4;
			if ( selectBuf[index+1] < dist ){
				dist = selectBuf[index+1];
				closest = selectBuf[index+3];
			}
			hits--;
		}
		// closest now has the id of the selected vertex
		sel = DLFLObject::vparray[closest];
	}
	return sel;
}

// Subroutine for selecting a Vertex
DLFLVertexPtrArray GLWidget::selectVertices(int mx, int my, int w, int h) {
	GLuint selectBuf[8192];
	long hits, index;
	DLFLVertexPtrArray vparray;

	glSelectBuffer(8192,selectBuf);
	glRenderMode(GL_SELECT);

	glInitNames(); glPushName(0);

	GLint vp[4];
	glGetIntegerv(GL_VIEWPORT, vp);
	mCamera->enterSelectionMode(mx,my,w,h,vp); // Reduced sensitivity for picking points

	// Make sure earlier matrices are preserved, since multiple windows
	// seem to be sharing the same matrix stacks
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	// viewport.reshape();
	// viewport.apply_transform();
	// glViewport(0,0,width(),height());
	mCamera->SetProjection(width(),height());
	// viewport.apply_transform();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderVerticesForSelect(object);
	glFlush();

	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	mCamera->leaveSelectionMode();

	hits = glRenderMode(GL_RENDER);
	// std::cout <<  "hits = " << hits << "\n";
	if ( hits > 0 ){
		while ( hits ){
			index = (hits-1)*4;
			// if(DLFLObject::vparray[selectBuf[index+3]])
				vparray.push_back(DLFLObject::vparray[selectBuf[index+3]]);
			hits--;
		}
		return vparray;
	}
	vparray.clear();
	return vparray;
}

// Subroutine for selecting an Edge
DLFLEdgePtr GLWidget::selectEdge(int mx, int my,int w, int h) {
	GLuint selectBuf[8192];
	uint closest;
	GLuint dist;
	long hits, index;
	DLFLEdgePtr sel(NULL);

	glSelectBuffer(8192,selectBuf);
	glRenderMode(GL_SELECT);

	glInitNames(); glPushName(0);

	GLint vp[4];
	glGetIntegerv(GL_VIEWPORT, vp);
	mCamera->enterSelectionMode(mx,my,w,h,vp);

	// Make sure earlier matrices are preserved, since multiple windows
	// seem to be sharing the same matrix stacks
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	// viewport.reshape();
	// viewport.apply_transform();
	mCamera->SetProjection(width(),height());
	// viewport.apply_transform();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderEdgesForSelect(object);
	glFlush();

	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	mCamera->leaveSelectionMode();

	hits = glRenderMode(GL_RENDER);
	if ( hits > 0 ){
		closest = 0; dist = 0xffffffff;
		while ( hits ){
			index = (hits-1)*4;
			if ( selectBuf[index+1] < dist ){
				dist = selectBuf[index+1];
				closest = selectBuf[index+3];
			}
			hits--;
		}
		// closest now has the id of the selected edge
		sel = DLFLObject::eparray[closest];
	}
	return sel;
}

// Subroutine for selecting an Edge
DLFLEdgePtrArray GLWidget::selectEdges(int mx, int my,int w, int h) {
	GLuint selectBuf[8192];
	long hits, index;
	DLFLEdgePtr sel(NULL);
	DLFLEdgePtrArray eparray;

	glSelectBuffer(8192,selectBuf);
	glRenderMode(GL_SELECT);

	glInitNames(); glPushName(0);

	GLint vp[4];
	glGetIntegerv(GL_VIEWPORT, vp);
	mCamera->enterSelectionMode(mx,my,w,h,vp);

	// Make sure earlier matrices are preserved, since multiple windows
	// seem to be sharing the same matrix stacks
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	mCamera->SetProjection(width(),height());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderEdgesForSelect(object);
	glFlush();

	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	mCamera->leaveSelectionMode();

	hits = glRenderMode(GL_RENDER);
	if ( hits > 0 ){
		while ( hits ){
			index = (hits-1)*4;
			// if(DLFLObject::eparray[selectBuf[index+3]])
				eparray.push_back(DLFLObject::eparray[selectBuf[index+3]]);
			hits--;
		}
		return eparray;
	}
	eparray.clear();
	return eparray;
}

// Subroutine for selecting a Face
DLFLFacePtr GLWidget::selectFace(int mx, int my, int w, int h) {
	GLuint selectBuf[8192];
	uint closest;
	GLuint dist;
	long hits, index;
	DLFLFacePtr sel(NULL);

	glSelectBuffer(8192,selectBuf);
	glRenderMode(GL_SELECT);

	glInitNames(); glPushName(0);

	GLint vp[4];
	glGetIntegerv(GL_VIEWPORT, vp);
	mCamera->enterSelectionMode(mx,my,w,h,vp);

	// Make sure earlier matrices are preserved, since multiple windows
	// seem to be sharing the same matrix stacks
	// glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	// viewport.reshape();
	// viewport.apply_transform();
	mCamera->SetProjection(width(),height());
	// viewport.apply_transform();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderFacesForSelect(object);
	glFlush();

	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	mCamera->leaveSelectionMode();

	hits = glRenderMode(GL_RENDER);
	if ( hits > 0 ){
		closest = 0; dist = 0xffffffff;
		while ( hits ){
			index = (hits-1)*4;
			if ( selectBuf[index+1] < dist ){
				dist = selectBuf[index+1];
				closest = selectBuf[index+3];
			}
			hits--;
		}
		// closest now has the id of the selected face
		sel = DLFLObject::fparray[closest];
	}	
	return sel;
}

// Subroutine for selecting multiple faces at once
DLFLFacePtrArray GLWidget::selectFaces(int mx, int my, int w, int h) {
	// glEnable(GL_CULL_FACE);
	GLuint selectBuf[8192];
	long hits, index;
	DLFLFacePtr sel(NULL);
	DLFLFacePtrArray fparray;
	fparray.clear();

	glSelectBuffer(8192,selectBuf);
	glRenderMode(GL_SELECT);

	glInitNames(); glPushName(0);

	GLint vp[4];
	glGetIntegerv(GL_VIEWPORT, vp);
	mCamera->enterSelectionMode(mx,my,w,h,vp);

	// Make sure earlier matrices are preserved, since multiple windows
	// seem to be sharing the same matrix stacks
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	mCamera->SetProjection(width(),height());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderFacesForSelect(object);
	glFlush();

	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	mCamera->leaveSelectionMode();

	hits = glRenderMode(GL_RENDER);
	// std::cout << hits << " = hits\n";
	if ( hits > 0 ){
		while ( hits ){
			index = (hits-1)*4;			
			// if(DLFLObject::fparray[selectBuf[index+3]])
			fparray.push_back(DLFLObject::fparray[selectBuf[index+3]]);
			hits--;
		}	
		// glDisable(GL_CULL_FACE);
		return fparray;		
	}	
	// glDisable(GL_CULL_FACE);
	fparray.clear();
	return fparray;
}


// Subroutine for selecting multiple faces at once
// DLFLFacePtrArray GLWidget::deselectFaces(int mx, int my) {
DLFLFacePtr GLWidget::deselectFaces(int mx, int my, int w, int h) {
	glEnable(GL_CULL_FACE);
	GLuint selectBuf[8192];
	uint closest;
	GLuint dist;
	long hits, index;
	DLFLFacePtr sel(NULL);
	DLFLFacePtrArray fparray;

	glSelectBuffer(8192,selectBuf);
	glRenderMode(GL_SELECT);

	glInitNames(); glPushName(0);

	GLint vp[4];
	glGetIntegerv(GL_VIEWPORT, vp);
	mCamera->enterSelectionMode(mx,my,mBrushSize,mBrushSize,vp);

	// Make sure earlier matrices are preserved, since multiple windows
	// seem to be sharing the same matrix stacks
	// glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	// viewport.reshape();
	// viewport.apply_transform();
	mCamera->SetProjection(width(),height());
	// viewport.apply_transform();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderFacesForSelect(object);
	glFlush();

	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	mCamera->leaveSelectionMode();

	hits = glRenderMode(GL_RENDER);
	if ( hits > 0 ){
		closest = 0; dist = 0xffffffff;
		while ( hits ){
			index = (hits-1)*4;
			if ( selectBuf[index+1] < dist ){
				dist = selectBuf[index+1];
				closest = selectBuf[index+3];
			}
			
			//if (DLFLObject::fparray[selectBuf[index+3]].normalCentroid()*camera.getPos()){
			// if(isSelected(DLFLObject::fparray[selectBuf[index+3]]))
				// fparray.push_back(DLFLObject::fparray[selectBuf[index+3]]);
			//}
			hits--;
		}
		// closest now has the id of the selected face
		sel = DLFLObject::fparray[closest];
	}	
	glDisable(GL_CULL_FACE);
	// return fparray;
	return sel;
}

// Subroutine for selecting a FaceVertex (Corner) within a Face
DLFLFaceVertexPtr GLWidget::selectFaceVertex(DLFLFacePtr fp, int mx, int my, int w, int h) {
	GLuint selectBuf[8192];
	uint closest;
	GLuint dist;
	long hits, index;
	DLFLFaceVertexPtr sel(NULL);

	glSelectBuffer(8192,selectBuf);
	glRenderMode(GL_SELECT);

	glInitNames(); glPushName(0);

	GLint vp[4];
	glGetIntegerv(GL_VIEWPORT, vp);
	mCamera->enterSelectionMode(mx,my,w,h,vp);
	// Make sure earlier matrices are preserved, since multiple windows
	// seem to be sharing the same matrix stacks
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	// viewport.reshape();
	// viewport.apply_transform();
	mCamera->SetProjection(width(),height());
	// viewport.apply_transform();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderFaceVerticesForSelect(fp);
	glFlush();

	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	mCamera->leaveSelectionMode();

	hits = glRenderMode(GL_RENDER);
	if ( hits > 0 ){
		closest = 0; dist = 0xffffffff;
		while ( hits ){
			index = (hits-1)*4;
			if ( selectBuf[index+1] < dist ){
				dist = selectBuf[index+1];
				closest = selectBuf[index+3];
			}
			hits--;
		}
		// closest now has the id of the selected face vertex
		sel = DLFLObject::fvparray[closest];
	}
	return sel;
}

// Draw the selected items
void GLWidget::drawSelected(void) {

  if ( !object->sel_vptr_array.empty() ) {
    glPointSize(mSelectedVertexThickness);
    //glBegin(GL_POINTS);
    glColor4f(mSelectedVertexColor.redF(),mSelectedVertexColor.greenF(),mSelectedVertexColor.blueF(),mSelectedVertexColor.alphaF());
    DLFLVertexPtrArray::iterator first, last;
    first = object->sel_vptr_array.begin(); last = object->sel_vptr_array.end();
    while ( first != last ){
      GeometryRenderer::instance()->renderVertex(*first);
      ///(*first)->render(); 
      ++first;
    }
    //glEnd();
    glPointSize(1.0);
  }

	if ( !object->sel_eptr_array.empty() ){
		glLineWidth(mSelectedEdgeThickness);
		glColor4f(mSelectedEdgeColor.redF(),mSelectedEdgeColor.greenF(),mSelectedEdgeColor.blueF(),mSelectedEdgeColor.alphaF());
		DLFLEdgePtrArray::iterator first, last;
		first = object->sel_eptr_array.begin(); last = object->sel_eptr_array.end();
		while ( first != last ){
		  glBegin(GL_LINES); {
		    GeometryRenderer::instance()->renderEdge(*first);
		  } glEnd();
		  ///(*first)->render(); 
		  ++first;
		}
		glLineWidth(3.0);
	}

	if ( !object->sel_fptr_array.empty() ){
	  glLineWidth(mSelectedEdgeThickness);
	  glColor4f(mSelectedFaceColor.redF(),mSelectedFaceColor.greenF(),mSelectedFaceColor.blueF(),mSelectedFaceColor.alphaF());
	  DLFLFacePtrArray::iterator first, last;
	  first = object->sel_fptr_array.begin(); last = object->sel_fptr_array.end();
	  while ( first != last )	{
	    GeometryRenderer::instance()->renderFace(*first,false);
	    ///(*first)->render_FVN(); 
	    ++first;
	  }
	  glLineWidth(3.0);
	}

	if ( !object->sel_fvptr_array.empty() ) {
		glPointSize(mSelectedVertexThickness);
		glColor4f(mSelectedVertexColor.redF(),mSelectedVertexColor.greenF(),mSelectedVertexColor.blueF(),mSelectedVertexColor.alphaF());
		glBegin(GL_POINTS);
		DLFLFaceVertexPtrArray::iterator first, last;
		first = object->sel_fvptr_array.begin(); last = object->sel_fvptr_array.end();
		while ( first != last ){
		  GeometryRenderer::instance()->renderFaceVertex(*first,false);
		  ///(*first)->render(); 
		  ++first;
		}
		glEnd();
		glPointSize(1.5);
	}
}

void GLWidget::wheelEvent(QWheelEvent *event) {

	// int x = event->x(), y = event->y();
	// int numDegrees = event->delta() / 8;
	// int numSteps = numDegrees / 15;
	// double z;
	mCamera->HandleMouseWheel(event->delta(), width(),height());
	repaint();
}
void GLWidget::mousePressEvent(QMouseEvent *event) {
	
	if ( QApplication::keyboardModifiers() == Qt::AltModifier || 
       //event->buttons() == Qt::MidButton ||
			(event->buttons() == Qt::LeftButton && QApplication::keyboardModifiers() == (Qt::ShiftModifier | Qt::AltModifier)) )
        {
            mCamera->HandleMouseEvent(event->button(), event->type(), event->x(), event->y());
            repaint();	
        }	
	else event->ignore();
}

// this has been modified for the QT interface, so it handles focus automatically
void GLWidget::mouseMoveEvent(QMouseEvent *event) {	
	if (event->buttons() == Qt::MidButton ||
        event->buttons() == Qt::LeftButton && QApplication::keyboardModifiers() == Qt::AltModifier || 
		event->buttons() == Qt::RightButton && QApplication::keyboardModifiers() == Qt::AltModifier || 
		event->buttons() == Qt::LeftButton && QApplication::keyboardModifiers() == (Qt::ShiftModifier | Qt::AltModifier) ||
		event->buttons() == Qt::MidButton  && QApplication::keyboardModifiers() == (Qt::AltModifier))
        {
            // 
            mCamera->HandleMouseMotion(event->x(),event->y(), width(), height() );
            repaint();	
        } else event->ignore();
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event) {
    //
	if (QApplication::keyboardModifiers() == Qt::AltModifier || 
        event->buttons() == Qt::MidButton ||
        event->buttons() == Qt::LeftButton && QApplication::keyboardModifiers() == (Qt::ShiftModifier | Qt::AltModifier) 
       ) {
		mCamera->HandleMouseEvent(event->button(), event->type(), event->x(), event->y());
		repaint();	
	}	
	else event->ignore();
}

//drag and drop - dave 08/31/2008
 void GLWidget::dragEnterEvent(QDragEnterEvent *event) {
    //if (event->mimeData()->hasFormat("text/plain"))  
    //event->acceptProposedAction();
    event->ignore();
}

void GLWidget::dropEvent(QDropEvent *event) {

    //QMessageBox::about(this, tr("Drop Event"), QFileInfo(event->mimeData()->urls()[0].toLocalFile()).absoluteFilePath());
    //QMessageBox::about(this, tr("Drop Event"), QString(event->mimeData()->data("text/uri-list")));
    //mParent->dropEvent(event);
    //event->acceptProposedAction();
    event->ignore();
}

// Global operations (don't require selection)
void GLWidget::recomputeNormals(void)     // Recompute normals and lighting
{
  object->computeNormals();
  computeLighting( object, &plight);
}

void GLWidget::recomputeLighting(void)                // Recompute lighting
{
  computeLighting( object, &plight);
}

void GLWidget::computeLighting( DLFLFacePtr fp, LightPtr lightptr) {
  if ( fp->front() ) {
    double Ka = fp->material()->Ka;
    double Kd = fp->material()->Kd;
    double Ks = fp->material()->Ks;

		RGBColor basecolor = fp->material()->color;
		RGBColor fvcolor;
		Vector3d normal, pos;

    DLFLFaceVertexPtr current = fp->front();
    normal = current->getNormal();
    pos = current->getVertexCoords();
		
  	fvcolor = lightptr->illuminate(pos,normal)*Kd;
    fvcolor += (1.0-Kd)*basecolor;		
    current->color = fvcolor;

    current = current->next();
    while ( current != fp->front() ) {
      normal = current->getNormal();
      pos = current->getVertexCoords();

    	fvcolor = lightptr->illuminate(pos,normal)*Kd;
	    fvcolor += (1.0-Kd)*basecolor;
    	current->color = fvcolor;

			// current->color = RGBColor(((double)rand() / ((`)(RAND_MAX)+(double)(1)) ),
			// 													((double)rand() / ((double)(RAND_MAX)+(double)(1)) ),
			// 													((double)rand() / ((double)(RAND_MAX)+(double)(1)) )
			// 													);
      current = current->next();
    }
  }
}

void GLWidget::computeLighting(DLFLObjectPtr obj, LightPtr lightptr) 
{
  DLFLFacePtrList::iterator first, last;
  DLFLFacePtr faceptr;
  first = obj->beginFace(); last = obj->endFace();
  while ( first != last ) {
    faceptr = (*first);
    computeLighting(faceptr,lightptr);
    ++first;
  }
}

void GLWidget::setWarmLightColor(QColor c){
	plight.warmcolor.set(c.redF(),c.greenF(),c.blueF());
	recomputeLighting();
	redraw();
}

void GLWidget::setCoolLightColor(QColor c){
	plight.coolcolor.set(c.redF(),c.greenF(),c.blueF());
	recomputeLighting();
	redraw();
}

void GLWidget::setLightIntensity(double i){
	plight.intensity = i;
	recomputeLighting();
	redraw();
}

void GLWidget::setRenderColor(QColor c){
	mRenderColor = c;
	GeometryRenderer *gr = GeometryRenderer::instance();
	gr->renderColor[0] = c.redF();
	gr->renderColor[1] = c.greenF();
	gr->renderColor[2] = c.blueF();
	gr->renderColor[3] = c.alphaF();
	redraw();
}

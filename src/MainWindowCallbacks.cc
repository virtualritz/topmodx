/*** ***/
/* $Id: MainWindowCallbacks.cc,v 4.13 2004/01/20 22:18:36 vinod Exp $ */

// Definitions for callback functions in the MainWindow class
// All these are static methods
#include <queue>
#include "MainWindow.h"

void MainWindow::load_texture() {
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Open Texture File..."),
		mTextureSaveDirectory,
		tr("All Supported Files (*.jpg *.png);;JPEG Files (*.jpg);;PNG Files (*.png);;All Files (*)"),
		0, QFileDialog::DontUseSheet);

	if (!fileName.isEmpty()){
		// undoPush();
	  mTextureSaveDirectory = QFileInfo(fileName).absoluteDir().absolutePath();
	  //mPreferencesDialog->setTextureSaveDirectory(mTextureSaveDirectory);

		QByteArray ba = fileName.toLatin1();
		const char *texfile = ba.data();
		if (texfile != NULL){
			textured->setTexture(texfile);
			texturedlit->setTexture(texfile);
			// getActive()->valid(0); // To ensure new texture is loaded into OpenGL
			redraw();
		}
	}
}

//use a specific renderer...
void MainWindow::useWireframeRenderer() {
	setRenderer(wired);
	redraw();
}

void MainWindow::useNormalRenderer() {
	setRenderer(normal);
	redraw();
}

void MainWindow::useLightedRenderer() {
	active->recomputeNormals();
	setRenderer(lit);
	redraw();
}

void MainWindow::useTexturedRenderer() {
	setRenderer(textured);
	redraw();
}

void MainWindow::useTexturedLitRenderer() {
	setRenderer(texturedlit);
	redraw();
}

void MainWindow::useColorableRenderer() {
	setRenderer(colorable);
	redraw();
}



void MainWindow::setSingleClickExtrude(int value){
	mSingleClickExtrude = (bool)value;
}
// Selection Menu.
void MainWindow::select_vertex() {
	setMode(MainWindow::SelectVertex);
}

void MainWindow::edit_vertex() {
	setMode(MainWindow::EditVertex);
}

void MainWindow::select_face() {
	// cout << "select_face called\n";
	setMode(MainWindow::SelectFace);
}

void MainWindow::select_face_loop() {
	setMode(MainWindow::SelectFaceLoop);
}

void MainWindow::select_edge_ring() {
	setMode(MainWindow::SelectEdgeRing);
}

void MainWindow::select_multiple_faces() {
	setMode(MainWindow::MultiSelectFace);
}

void MainWindow::select_multiple() {
	switch (selectionmask){
		case MaskVertices:
		setMode(MainWindow::MultiSelectVertex);
		break;
		case MaskEdges:
		setMode(MainWindow::MultiSelectEdge);
		break;
		case MaskFaces://face stuff
		setMode(MainWindow::MultiSelectFace);
		break;
		case MaskCorners:
		break;
		default:
		break;
	};
}

void MainWindow::select_multiple_edges() {
	setMode(MainWindow::MultiSelectEdge);
}

void MainWindow::select_multiple_vertices() {
	setMode(MainWindow::MultiSelectVertex);
}

void MainWindow::select_similar_faces() {
	// setMode(MainWindow::SelectSimilarFaces);
}

void MainWindow::select_similar() {
	// switch(selectionmask){
	// 	case MaskFaces:
	setMode(MainWindow::SelectSimilar);
	// 	break;
	// 	case MaskEdges:
	// 	setMode(MainWindow::SelectSimilarEdges);
	// 	break;
	// 	case MaskVertices:
	// 	setMode(MainWindow::SelectSimilarVertices);
	// 	break;
	// 	default:
	// 	break;
	// };
}

void MainWindow::select_faces_by_area() {
	setMode(MainWindow::SelectFacesByArea);
}

void MainWindow::select_faces_by_color() {
	setMode(MainWindow::SelectFacesByColor);
}

void MainWindow::selection_window() {
	setMode(MainWindow::SelectionWindow);
}

void MainWindow::select_checkerboard_faces() {
	setMode(MainWindow::SelectCheckerboard);
}

void MainWindow::select_edge() {
	setMode(MainWindow::SelectEdge);
}

void MainWindow::select_edge_loop() {
	setMode(MainWindow::SelectEdgeLoop);
}

void MainWindow::select_corner() {
	setMode(MainWindow::SelectCorner);
}

void MainWindow::selectionMaskVertices() {
	// setSelectionMask(MainWindow::MaskVertices);
	setMode(MainWindow::SelectVertex);
}

void MainWindow::selectionMaskFaces() {
	// cout << "selectionMaskFaces called\n";

	// setSelectionMask(MainWindow::MaskFaces);
	setMode(MainWindow::SelectFace);
}

void MainWindow::selectionMaskEdges() {
	// setSelectionMask(MainWindow::MaskEdges);
	setMode(MainWindow::SelectEdge);

}

void MainWindow::selectionMaskCorners() {
	// setSelectionMask(MainWindow::MaskCorners);
	setMode(MainWindow::SelectCorner);

}

void MainWindow::selectAll(){
	switch (selectionmask){
		case MaskVertices:
		active->selectAllVertices();
		break;
		case MaskEdges:
		active->selectAllEdges();
		break;
		case MaskFaces:
		active->selectAllFaces();
		break;
		case MaskCorners:
		// active->selectAllCorners();
		case MaskObject:
		break;
		default:
		// active->selectAllVertices();
		break;
	};
}

void MainWindow::selectInverse(){
	switch (selectionmask){
		case MaskVertices:
		active->selectInverseVertices();
		break;
		case MaskEdges:
		active->selectInverseEdges();
		break;
		case MaskFaces:
		active->selectInverseFaces();
		break;
		case MaskCorners:
		active->selectInverseFaceVertices();
		case MaskObject:
		break;
		default:
		// active->selectInverseVertices();
		break;
	};
}
void MainWindow::exit_selection_mode() {
	setMode(MainWindow::NormalMode);
	redraw();
}

void MainWindow::clear_selected(){
	MainWindow::clearSelected();
	redraw();
}

// Basics.
// Extrusions.
void MainWindow::changeExtrudeLength(double value) {
	MainWindow::extrude_dist = value;
}

void MainWindow::changeExtrudeRotation(double value) {
	MainWindow::extrude_rot = (int)value;
}

void MainWindow::changeExtrudeScale(double value) {
	MainWindow::extrude_scale = value;
}

void MainWindow::changeNumExtrusions(double value) {
	MainWindow::num_extrusions = (int)value;
}

void MainWindow::changeScherkCollinsPinch(double value) {
	MainWindow::scherk_collins_pinch = value;
}
void MainWindow::changeScherkCollinsPinchCenter(double value) {
	MainWindow::scherk_collins_pinch_center = value;
}
void MainWindow::changeScherkCollinsPinchWidth(double value) {
	MainWindow::scherk_collins_pinch_width = value;
}

void MainWindow::changeScherkCollinsHoleNumSegments(double value) {
  scherk_collins_hole_num_segs = (int)value;
}

void MainWindow::changeScherkCollinsHoleInitSkip(double value) {
  scherk_collins_hole_init_skip = (int)value;
}

void MainWindow::changeScherkCollinsHoleSkip(double value) {
  scherk_collins_hole_skip = (int)value;
}

void MainWindow::changeScherkCollinsHoleTwist(double value) {
  scherk_collins_hole_twist = (int)value;
}

void MainWindow::changeScherkCollinsHoleSegSkip(double value) {
  scherk_collins_hole_seg_skip = (int)value;
}

void MainWindow::toggleScherkCollins(int state) {
	scherk_collins = bool(state);
}
void MainWindow::toggleTriangulateNewFaces(int state) {
	MainWindow::triangulate_new_faces = bool(state);
}



void MainWindow::clearMaterials(){
	undoPush();
	object.clearMaterials();
	active->recomputeNormals();
	redraw();
}


// Geometric transformations
void MainWindow::translatex(double x) {
	Vector3d oldtr = object.position;
	object.position[0] = x;
	object.tr.transform[0][3] = x;
	redraw();
}

void MainWindow::translatey(double y) {
	object.position[1] = y;
	object.tr.transform[1][3] = y;
	redraw();
}

void MainWindow::translatez(double z) {
	object.position[2] = z;
	object.tr.transform[2][3] = z;
	redraw();
}

void MainWindow::scalex(double x) {
	object.scale_factor[0] = x;
	object.tr.transform[0][0] = x;
	redraw();
}

void MainWindow::scaley(double y) {
	object.scale_factor[1] = y;
	object.tr.transform[1][1] = y;
	redraw();
}

void MainWindow::scalez(double z) {
	object.scale_factor[2] = z;
	object.tr.transform[2][2] = z;
	redraw();
}

void MainWindow::freezeTransforms() {
	object.freezeTransformations();
	object.position.reset();
	object.scale_factor.set(1,1,1);
	object.rotation.reset();
	object.tr.reset();
	active->recomputeLighting();
	redraw();
}


void MainWindow::edgeCleanup(void) // Cleanup redundant edges
{
	undoPush();
	setModified(true);
	DLFL::edgeCleanup(&object);
	active->recomputeNormals();
	MainWindow::clearSelected();
	redraw();
}
void MainWindow::deleteEdge(DLFLEdgePtr edgeptr){
  // Fenghui's simple profiler for DeleteEdge operation.
  std::clock_t start = std::clock();
  std::clock_t op = std::clock();
  std::clock_t recompute_patches = std::clock();
  std::clock_t recompute_normals = std::clock();

  // Obtain the vertex pointers for this edge
  DLFLVertexPtr vp1, vp2;
  edgeptr->getVertexPointers(vp1, vp2);

  DLFL::deleteEdge( &object, edgeptr, true);
  
    // Compute Normals only for the face effected
    map<DLFLVertexPtr, DLFLVertexPtrList::iterator> vertex_idx = object.getVertexIdx();
    // Make sure it is not a point sphere
    if (vertex_idx.find(vp1) != vertex_idx.end()) {
      vp1->updateNormal();
    }
    // Make sure it is not a point sphere
    if (vertex_idx.find(vp2) != vertex_idx.end()) {
      vp2->updateNormal();
    }

}
void MainWindow::deleteSelected(){
	DLFLEdgePtrArray septrarr;
	DLFLFacePtrArray sfptrarr;
	DLFLVertexPtrArray svptrarr;
	DLFLFaceVertexPtrArray sfvptrarr;

	vector<DLFLFaceVertexPtr>::iterator fvt;
	vector<DLFLVertexPtr>::iterator vit;
	vector<DLFLEdgePtr>::iterator eit;
	vector<DLFLFacePtr>::iterator fit;

	// undoPush();
	// setModified(true);

	switch (selectionmask){
		case MaskEdges:
			septrarr = active->getSelectedEdges();
			if ( septrarr.size() > 0 && septrarr[0] ) {
				// undoPush();
				setModified(true);
				vector<DLFLEdgePtr>::iterator eit;
				for(eit = septrarr.begin(); eit != septrarr.end(); eit++){
          deleteEdge(*eit);
				}
			}
			active->clearSelectedEdges();

			redraw();
		  break;
		case MaskVertices:
			svptrarr = active->getSelectedVertices();
			if ( svptrarr[0] ) {
				undoPush();
				setModified(true);
				for(vit = svptrarr.begin(); vit != svptrarr.end(); vit++){
					(*vit)->getEdges(septrarr);
					vector<DLFLEdgePtr>::iterator eit;
					for(eit = septrarr.begin(); eit != septrarr.end(); eit++)
						//DLFL::deleteEdge( &object, *eit, true);
						deleteEdge(*eit);
					}
			}
			active->clearSelectedVertices();
			redraw();
      break;
		case MaskFaces:

      break;
		case MaskCorners:
      break;
		case MaskObject://someday...
      break;
		default:
      break;
	};
}

void MainWindow::selectEdgesFromFaces(){
	DLFLEdgePtrArray septrarr;
	DLFLFacePtrArray sfptrarr;
	vector<DLFLFacePtr>::iterator fit;
	vector<DLFLEdgePtr>::iterator eit;
	//loop through selected faces, get corresponding edges, select them
	sfptrarr = active->getSelectedFaces();
	if ( sfptrarr.size() > 0 && sfptrarr[0] ) {
		for(fit = sfptrarr.begin(); fit != sfptrarr.end(); fit++){
			(*fit)->getEdges(septrarr);
			vector<DLFLEdgePtr>::iterator eit;
			for(eit = septrarr.begin(); eit != septrarr.end(); eit++){
				if (!active->isSelected(*eit)){
					active->setSelectedEdge(num_sel_edges,*eit);
					num_sel_edges++;
				}
			}
		}
  		active->recomputeNormals();
	}
	setMode(MainWindow::SelectEdge);
	active->clearSelectedFaces();
	redraw();
}

void MainWindow::selectEdgesFromVertices(){
	DLFLEdgePtrArray septrarr;
	DLFLVertexPtrArray svptrarr;
	vector<DLFLVertexPtr>::iterator vit;
	vector<DLFLEdgePtr>::iterator eit;
	//loop through selected vertices, get corresponding edges, select them
	svptrarr = active->getSelectedVertices();
	if ( svptrarr.size() > 0 && svptrarr[0] ) {
		for(vit = svptrarr.begin(); vit != svptrarr.end(); vit++){
			(*vit)->getEdges(septrarr);
			for(eit = septrarr.begin(); eit != septrarr.end(); eit++){
				if (!active->isSelected(*eit)){
					active->setSelectedEdge(num_sel_edges,*eit);
					num_sel_edges++;
				}
			}
		}
  		active->recomputeNormals();
	}
	setMode(MainWindow::SelectEdge);
	active->clearSelectedVertices();
	redraw();
}

void MainWindow::selectFacesFromEdges(){
	DLFLEdgePtrArray septrarr;
	vector<DLFLEdgePtr>::iterator eit;
	DLFLFacePtr fptr1, fptr2;
	//loop through selected faces, get corresponding vertices, select them
	septrarr = active->getSelectedEdges();
	if ( septrarr.size() > 0 && septrarr[0] ) {
		for(eit = septrarr.begin(); eit != septrarr.end(); eit++){
			(*eit)->getFacePointers(fptr1,fptr2);
			if (!active->isSelected(fptr1)){
				active->setSelectedFace(num_sel_faces,fptr1);
				num_sel_faces++;
			}
			if (!active->isSelected(fptr2)){
				active->setSelectedFace(num_sel_faces,fptr2);
				num_sel_faces++;
			}
		}
  		active->recomputeNormals();
	}
	setMode(MainWindow::SelectFace);
	active->clearSelectedEdges();
	redraw();
}

void MainWindow::selectFacesFromVertices(){
	DLFLVertexPtrArray svptrarr;
	vector<DLFLVertexPtr>::iterator vit;
	DLFLFacePtrArray sfptrarr;
	vector<DLFLFacePtr>::iterator fit;
	//loop through selected faces, get corresponding edges, select them
	svptrarr = active->getSelectedVertices();
	if ( svptrarr.size() > 0 && svptrarr[0] ) {
		for(vit = svptrarr.begin(); vit != svptrarr.end(); vit++){
			(*vit)->getFaces(sfptrarr);
			for(fit = sfptrarr.begin(); fit != sfptrarr.end(); fit++){
				if (!active->isSelected(*fit)){
					active->setSelectedFace(num_sel_faces,*fit);
					num_sel_faces++;
				}
			}
		}
  		active->recomputeNormals();
	}
	setMode(MainWindow::SelectFace);
	active->clearSelectedVertices();
	redraw();
}

void MainWindow::selectVerticesFromFaces(){
	DLFLFacePtrArray sfptrarr;
	vector<DLFLFacePtr>::iterator fit;
	DLFLFaceVertexPtrArray sfvptrarr;
	vector<DLFLFaceVertexPtr>::iterator fvit;
	DLFLVertexPtr vptr;
	//loop through selected faces, get corresponding vertices, select them
	sfptrarr = active->getSelectedFaces();
	if ( sfptrarr.size() > 0 && sfptrarr[0] ) {
		for(fit = sfptrarr.begin(); fit != sfptrarr.end(); fit++){
			(*fit)->getCorners(sfvptrarr);
			for(fvit = sfvptrarr.begin(); fvit != sfvptrarr.end(); fvit++){
				vptr = (*fvit)->getVertexPtr();
				if (!active->isSelected(vptr)){
					active->setSelectedVertex(num_sel_verts,vptr);
					num_sel_verts++;
				}
			}
		}
  		active->recomputeNormals();
	}
	setMode(MainWindow::SelectVertex);
	active->clearSelectedFaces();
	redraw();
}

void MainWindow::selectVerticesFromEdges(){
	DLFLEdgePtrArray septrarr;
	vector<DLFLEdgePtr>::iterator eit;
	DLFLVertexPtr vptr1,vptr2;
	//loop through selected faces, get corresponding vertices, select them
	septrarr = active->getSelectedEdges();
	// std::cout<< septrarr[0] << " \t\t" << septrarr.size() <<"\n";
	if ( septrarr.size() > 0 && septrarr[0]) {
		for(eit = septrarr.begin(); eit != septrarr.end(); eit++){
			(*eit)->getVertexPointers(vptr1,vptr2);
			if (!active->isSelected(vptr1)){
				active->setSelectedVertex(num_sel_verts,vptr1);
				num_sel_verts++;
			}
			if (!active->isSelected(vptr2)){
				active->setSelectedVertex(num_sel_verts,vptr2);
				num_sel_verts++;
			}
		}
  		active->recomputeNormals();
	}
	setMode(MainWindow::SelectVertex);
	active->clearSelectedEdges();
	redraw();
}

void MainWindow::selectVertex(DLFLVertexPtr vp){
  active->setSelectedVertex(num_sel_verts,vp);
  num_sel_verts++;
}

void MainWindow::selectComponent(){
	DLFLEdgePtrArray septrarr;
	DLFLVertexPtrArray svptrarr;
	DLFLFaceVertexPtrArray sfvptrarr;
	DLFLFacePtrArray sfptrarr;
	vector<DLFLVertexPtr>::iterator vit;
	vector<DLFLEdgePtr>::iterator eit;
	vector<DLFLFacePtr>::iterator fit;
	vector<DLFLFaceVertexPtr>::iterator fvit;

	DLFLVertexPtr vptr1,vptr2;
	DLFLFacePtr fptr1,fptr2;
	DLFLEdgePtrArray eptrarray;
	vector<DLFLEdgePtr>::iterator eit2;

	switch (selectionmask){
		case MaskVertices:
		//loop through selected vertices, get corresponding edges
		svptrarr = active->getSelectedVertices();
		if ( svptrarr.size() > 0 && svptrarr[0] ) {
      std::queue<DLFLVertexPtr> Q;
			for(vit = svptrarr.begin(); vit != svptrarr.end(); vit++){
        Q.push(*vit);
      }
      while (!Q.empty()) {
        DLFLVertexPtr u = Q.front();
        Q.pop();
        u->getEdges(septrarr);
				//loop through edges, select all vertices connected to these edges
				for(eit = septrarr.begin(); eit != septrarr.end(); eit++){
					DLFLVertexPtr vp1, vp2;
					//get the two vertices for each edge, select them if they aren't already selected
					(*eit)->getVertexPointers(vp1,vp2);
					if (!active->isSelected(vp1)){
						active->setSelectedVertex(num_sel_verts,vp1);
            Q.push(vp1);
						num_sel_verts++;
					}
					if (!active->isSelected(vp2)){
						active->setSelectedVertex(num_sel_verts,vp2);
            Q.push(vp2);
						num_sel_verts++;
					}
				}
			}
		}
		redraw();
		break;
		case MaskEdges:
		//loop through selected edges, get vertices, then get those edges
		septrarr = active->getSelectedEdges();
		if ( septrarr.size() > 0 && septrarr[0]) {
      std::queue<DLFLEdgePtr> Q;
			for(eit = septrarr.begin(); eit != septrarr.end(); eit++){
        Q.push(*eit);
      }
      while (!Q.empty()) {
        DLFLEdgePtr e = Q.front();
        Q.pop();
				//get the 2 vertices for the current edge
        e->getVertexPointers(vptr1,vptr2);
				//get the edges for vertex 1
				vptr1->getEdges(eptrarray);
				for (eit2 = eptrarray.begin(); eit2 != eptrarray.end(); eit2++){
					if (!active->isSelected(*eit2)){
						active->setSelectedEdge(num_sel_edges,*eit2);
            Q.push(*eit2);
						num_sel_edges++;
					}
				}
				//get edges for vertex 2
				vptr2->getEdges(eptrarray);
				for (eit2 = eptrarray.begin(); eit2 != eptrarray.end(); eit2++){
					if (!active->isSelected(*eit2)){
						active->setSelectedEdge(num_sel_edges,*eit2);
            Q.push(*eit2);
						num_sel_edges++;
					}
				}
			}
		}
		redraw();
		break;
		case MaskFaces:
		//loop through selected faces
		sfptrarr = active->getSelectedFaces();
		if ( sfptrarr.size() > 0 && sfptrarr[0] ) {
      std::queue<DLFLFacePtr> Q;
			for(fit = sfptrarr.begin(); fit != sfptrarr.end(); fit++){
        Q.push(*fit);
      }
      while (!Q.empty()) {
        DLFLFacePtr f = Q.front();
        Q.pop();
				//get the edges for the current face
				f->getEdges(eptrarray);
				for(eit = eptrarray.begin(); eit != eptrarray.end(); eit++){
					//get the 2 faces for the current edge, select them if they aren't already selected
					(*eit)->getFacePointers(fptr1,fptr2);
					if (!active->isSelected(fptr1)){
						active->setSelectedFace(num_sel_faces,fptr1);
            Q.push(fptr1);
						num_sel_faces++;
					}
					if (!active->isSelected(fptr2)){
						active->setSelectedFace(num_sel_faces,fptr2);
            Q.push(fptr2);
						num_sel_faces++;
					}
				}
			}
		}
		redraw();
		break;
		default:
		break;
	};
}

void MainWindow::growSelection(){
	DLFLEdgePtrArray septrarr;
	DLFLVertexPtrArray svptrarr;
	DLFLFaceVertexPtrArray sfvptrarr;
	DLFLFacePtrArray sfptrarr;
	vector<DLFLVertexPtr>::iterator vit;
	vector<DLFLEdgePtr>::iterator eit;
	vector<DLFLFacePtr>::iterator fit;
	vector<DLFLFaceVertexPtr>::iterator fvit;

	DLFLVertexPtr vptr1,vptr2;
	DLFLFacePtr fptr1,fptr2;
	DLFLEdgePtrArray eptrarray;
	vector<DLFLEdgePtr>::iterator eit2;

	switch (selectionmask){
		case MaskVertices:
		//loop through selected vertices, get corresponding edges
		svptrarr = active->getSelectedVertices();
		if ( svptrarr.size() > 0 && svptrarr[0] ) {
			for(vit = svptrarr.begin(); vit != svptrarr.end(); vit++){
				(*vit)->getEdges(septrarr);
				//loop through edges, select all vertices connected to these edges
				for(eit = septrarr.begin(); eit != septrarr.end(); eit++){
					DLFLVertexPtr vp1, vp2;
					//get the two vertices for each edge, select them if they aren't already selected
					(*eit)->getVertexPointers(vp1,vp2);
					if (!active->isSelected(vp1)){
						active->setSelectedVertex(num_sel_verts,vp1);
						num_sel_verts++;
					}
					if (!active->isSelected(vp2)){
						active->setSelectedVertex(num_sel_verts,vp2);
						num_sel_verts++;
					}
				}
			}
		}
		redraw();
		break;
		case MaskEdges:
		//loop through selected edges, get vertices, then get those edges
		septrarr = active->getSelectedEdges();
		if ( septrarr.size() > 0 && septrarr[0]) {
			for(eit = septrarr.begin(); eit != septrarr.end(); eit++){
				//get the 2 vertices for the current edge
				(*eit)->getVertexPointers(vptr1,vptr2);
				//get the edges for vertex 1
				vptr1->getEdges(eptrarray);
				for (eit2 = eptrarray.begin(); eit2 != eptrarray.end(); eit2++){
					if (!active->isSelected(*eit2)){
						active->setSelectedEdge(num_sel_edges,*eit2);
						num_sel_edges++;
					}
				}
				//get edges for vertex 2
				vptr2->getEdges(eptrarray);
				for (eit2 = eptrarray.begin(); eit2 != eptrarray.end(); eit2++){
					if (!active->isSelected(*eit2)){
						active->setSelectedEdge(num_sel_edges,*eit2);
						num_sel_edges++;
					}
				}
			}
		}
		redraw();
		break;
		case MaskFaces:
		//loop through selected faces
		sfptrarr = active->getSelectedFaces();
		if ( sfptrarr.size() > 0 && sfptrarr[0] ) {
			for(fit = sfptrarr.begin(); fit != sfptrarr.end(); fit++){
				//get the edges for the current face
				(*fit)->getEdges(eptrarray);
				for(eit = eptrarray.begin(); eit != eptrarray.end(); eit++){
					//get the 2 faces for the current edge, select them if they aren't already selected
					(*eit)->getFacePointers(fptr1,fptr2);
					if (!active->isSelected(fptr1)){
						active->setSelectedFace(num_sel_faces,fptr1);
						num_sel_faces++;
					}
					if (!active->isSelected(fptr2)){
						active->setSelectedFace(num_sel_faces,fptr2);
						num_sel_faces++;
					}
				}
			}
		}
		redraw();
		break;
		case MaskCorners:

		break;
		case MaskObject:
		break;
		default:
		break;
	};
}

void MainWindow::shrinkSelection(){
	DLFLEdgePtrArray septrarr;
	DLFLVertexPtrArray svptrarr;
	DLFLFaceVertexPtrArray sfvptrarr;
	DLFLFacePtrArray sfptrarr;
	vector<DLFLVertexPtr>::iterator vit;
	vector<DLFLEdgePtr>::iterator eit;
	vector<DLFLFacePtr>::iterator fit;
	vector<DLFLFaceVertexPtr>::iterator fvit;
	int i = 0;

	DLFLVertexPtr vptr1,vptr2;
	DLFLFacePtr fptr1,fptr2;
	DLFLEdgePtrArray eptrarray;
	vector<DLFLEdgePtr>::iterator eit2;

	switch (selectionmask){
		case MaskVertices:
		//loop through selected vertices, get corresponding edges
		svptrarr = active->getSelectedVertices();
		if ( svptrarr.size() > 0 && svptrarr[0] ) {
			bool deselectvertices[svptrarr.size()];
			for(vit = svptrarr.begin(); vit != svptrarr.end(); vit++,i++){
				deselectvertices[i] = false;
				(*vit)->getEdges(septrarr);
				//loop through edges, select all vertices connected to these edges
				for(eit = septrarr.begin(); eit != septrarr.end(); eit++){
					DLFLVertexPtr vp1, vp2;
					//get the two vertices for each edge, select them if they aren't already selected
					(*eit)->getVertexPointers(vp1,vp2);
					if (!active->isSelected(vp1) || !active->isSelected(vp2))
						deselectvertices[i] = true;
				}
			}
			//loop back through verts, now deselect the flagged ones
			i = 0;
			for(vit = svptrarr.begin(); vit != svptrarr.end(); vit++, i++){
				//if it's flagged, deselect it
				if (deselectvertices[i])
					active->clearSelectedVertex(*vit);
			}
		}
		redraw();
		break;
		case MaskEdges:
		//loop through selected edges, get vertices, then get those edges
		septrarr = active->getSelectedEdges();
		if ( septrarr.size() > 0 && septrarr[0]) {
			bool deselectedges[septrarr.size()];
			for(eit = septrarr.begin(); eit != septrarr.end(); eit++,i++){
				//get the 2 vertices for the current edge
				(*eit)->getVertexPointers(vptr1,vptr2);
				//get the edges for vertex 1
				vptr1->getEdges(eptrarray);
				deselectedges[i] = false;
				for (eit2 = eptrarray.begin(); eit2 != eptrarray.end(); eit2++){
					if (!active->isSelected(*eit2))
						deselectedges[i] = true;
				}
				//get edges for vertex 2
				vptr2->getEdges(eptrarray);
				for (eit2 = eptrarray.begin(); eit2 != eptrarray.end(); eit2++){
					if (!active->isSelected(*eit2))
						deselectedges[i] = true;
				}
			}
			//loop back through edges, now deselect the flagged ones
			i = 0;
			for(eit = septrarr.begin(); eit != septrarr.end(); eit++,i++){
				//if it's flagged, deselect it
				if (deselectedges[i])
					active->clearSelectedEdge(*eit);
			}
		}
		redraw();		break;
		case MaskFaces:
		//loop through selected faces
		sfptrarr = active->getSelectedFaces();
		if ( sfptrarr.size() > 0 && sfptrarr[0] ) {
			bool deselectfaces[sfptrarr.size()];
			for(fit = sfptrarr.begin(); fit != sfptrarr.end(); fit++, i++){
				//get the edges for the current face
				(*fit)->getEdges(eptrarray);
				//by default don't deselect this face
				deselectfaces[i] = false;
				for(eit = eptrarray.begin(); eit != eptrarray.end(); eit++){
					//get the 2 faces for the current edge, check if both of them are selected, flag the current face
					(*eit)->getFacePointers(fptr1,fptr2);
					if (!active->isSelected(fptr1) || !active->isSelected(fptr2))
						deselectfaces[i] = true;
				}
			}
			//loop back through faces, now deselect the flagged ones
			i = 0;
			for(fit = sfptrarr.begin(); fit != sfptrarr.end(); fit++,i++){
				//if it's flagged, deselect it
				if (deselectfaces[i])
					active->clearSelectedFace(*fit);
			}
		}
		redraw();
		break;
		case MaskCorners:
		// active->selectAllCorners();
		case MaskObject:
		break;
		default:
		break;
	};
}
void MainWindow::reorderSelectedFaces(){

}

void MainWindow::toggleFullScreen(){
	// go back into normal screen mode
	if (windowState() == Qt::WindowFullScreen && !mToolsToolBar->isVisible()) {
		setWindowState(Qt::WindowNoState);
		mEditToolBar->setVisible(true);
		//mSelectionMaskToolBar->toggleViewAction();
		mPrimitivesToolBar->setVisible(true);
		mToolsToolBar->setVisible(true);
		mStatusBar->show();
	}
	// go to full screen mode 2
	else if (windowState() == Qt::WindowFullScreen) {
		// setWindowState(windowState() ^ Qt::WindowFullScreen);
		mStatusBar->hide();
		mEditToolBar->setVisible(false);
		mPrimitivesToolBar->setVisible(false);
		mToolsToolBar->setVisible(false);

	}
	//go into full screen mode 1
	else {
		setWindowState(windowState() ^ Qt::WindowFullScreen);
	}


}

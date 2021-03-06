/*** ***/

#ifndef _DLFLEXTRUDE_H_
#define _DLFLEXTRUDE_H_

#include <DLFLCoreExt.h>
#include <DLFLObject.h>

namespace DLFL {

  DLFLFacePtrArray duplicateFace(DLFLObjectPtr obj, DLFLFacePtr fptr, double offset, double rot, double sf);
  DLFLFacePtrArray duplicateFace(DLFLObjectPtr obj, DLFLFacePtr fptr, const Vector3d& dir, double offset, double rot, double sf);

  DLFLFacePtr duplicateFacePlanarOffset(DLFLObjectPtr obj, DLFLFacePtr fptr, double offset, double rot, double thickness, bool fractionalthickness);
  DLFLFacePtr duplicateFacePlanarOffset(DLFLObjectPtr obj, DLFLFacePtr fptr, const Vector3d& dir, double offset, double rot, double thickness, bool fractionalthickness);

  /* API
  uint extrudeFace(DLFLObjectPtr obj, uint faceID, double d, int num, double rot, double sf = 1.0);
  uint extrudeFaceDS(DLFLObjectPtr obj, uint faceID, double d, int num, double twist = 0.0, double sf = 1.0);
  uint extrudeDualFace(DLFLObjectPtr obj, uint faceID, double d, int num, double rot=0.0, double sf=1.0, bool mesh=false);
  uint extrudeFaceDodeca(DLFLObjectPtr obj, uint faceID, double d, int num, double rot=0.0, double sf = 1.0, bool hexagonalize=false);
  uint extrudeFaceIcosa(DLFLObjectPtr obj, uint faceID, double d, int num, double rot=0.0,  double sf = 1.0);
  void stellateFace(DLFLObjectPtr obj, uint faceID, double d);
  void doubleStellateFace(DLFLObjectPtr obj, uint faceID, double d);
  end API */

  DLFLFacePtr extrudeFace(DLFLObjectPtr obj, DLFLFacePtr fptr, double d);
  DLFLFacePtr extrudeFace(DLFLObjectPtr obj, DLFLFacePtr fptr, double d, int num);
  DLFLFacePtr extrudeFace(DLFLObjectPtr obj, DLFLFacePtr fptr, double d, double rot, double sf = 1.0);
  DLFLFacePtr extrudeFace(DLFLObjectPtr obj, DLFLFacePtr fptr, double d, int num, double rot, double sf = 1.0);
  // Extrude face for triangulated new faces/Scherk Collins surface.
  DLFLFacePtr extrudeFaceScherkCollins(DLFLObjectPtr obj, DLFLFacePtr fptr, double d, int num,
      double rot = 0.0, double sf = 1.0, bool triangulate_new_faces = false,
      bool scherk_collins = false, double pinch = 1.0, double pinch_center = 0.5,
      double pinch_width = 1.0);
  DLFLFacePtr extrudeFace(DLFLObjectPtr obj, DLFLFacePtr fptr, double d, const Vector3d& dir);
  DLFLFacePtr extrudeFace(DLFLObjectPtr obj, DLFLFacePtr fptr, double d, const Vector3d& dir, int num);
  DLFLFacePtr extrudeFace(DLFLObjectPtr obj, DLFLFacePtr fptr, double d, const Vector3d& dir, double rot, double sf = 1.0);
  DLFLFacePtr extrudeFace(DLFLObjectPtr obj, DLFLFacePtr fptr, double d, const Vector3d& dir, int num, double rot, double sf = 1.0);

  DLFLFacePtr extrudeFacePlanarOffset(DLFLObjectPtr obj, DLFLFacePtr fptr, double d, double rot, double thickness, bool fractionalthickness);
  DLFLFacePtr extrudeFacePlanarOffset(DLFLObjectPtr obj, DLFLFacePtr fptr, double d, const Vector3d& dir, double rot, double thickness, bool fractionalthickness);

  DLFLFacePtr extrudeFaceDS(DLFLObjectPtr obj, DLFLFacePtr fptr, double d, double twist = 0.0, double sf = 1.0);
  DLFLFacePtr extrudeFaceDS(DLFLObjectPtr obj, DLFLFacePtr fptr, double d, int num,
      double twist = 0.0, double sf = 1.0);

  DLFLFacePtr extrudeFaceDS(DLFLObjectPtr obj, DLFLFacePtr fptr, double d, const Vector3d& dir, double twist = 0.0, double sf = 1.0);
  DLFLFacePtr extrudeFaceDS(DLFLObjectPtr obj, DLFLFacePtr fptr, double d, const Vector3d& dir, int num, double twist = 0.0, double sf = 1.0);

  DLFLFacePtr extrudeDualFace(DLFLObjectPtr obj, DLFLFacePtr fptr, double d, double rot=0.0, double sf=1.0, bool mesh=false);
  DLFLFacePtr extrudeDualFace(DLFLObjectPtr obj, DLFLFacePtr fptr, double d, int num, double rot=0.0, double sf=1.0, bool mesh=false);
  DLFLFacePtr extrudeDualFace(DLFLObjectPtr obj, DLFLFacePtr fptr, double d, const Vector3d& dir, double rot=0.0, double sf=1.0, bool mesh=false);
  DLFLFacePtr extrudeDualFace(DLFLObjectPtr obj, DLFLFacePtr fptr, double d, const Vector3d& dir, int num, double rot=0.0, double sf=1.0, bool mesh=false);
    
  void stellateFace(DLFLObjectPtr obj, DLFLFacePtr fptr, double d);
  void stellateFace(DLFLObjectPtr obj, DLFLFacePtr fptr, double d, const Vector3d& dir);

  void doubleStellateFace(DLFLObjectPtr obj, DLFLFacePtr fptr, double d);

  DLFLFacePtr extrudeHexTileFace(DLFLObjectPtr obj, DLFLFacePtr fptr, double d, double rot=0.0, double sf = 1.0);

  DLFLFacePtr extrudeFaceDodeca(DLFLObjectPtr obj, DLFLFacePtr fptr, double d, int num, double rot=0.0, double sf = 1.0, bool hexagonalize=false);
  DLFLFacePtr extrudeFaceDodeca(DLFLObjectPtr obj, DLFLFacePtr fptr, double d, double rot=0.0, double sf = 1.0);
	
	DLFLFacePtr extrudeFaceDodeca(DLFLObjectPtr obj, DLFLFacePtr fptr, double angle, int num, double ex_dist1, double ex_dist2, double ex_dist3, bool hexagonalize);
	DLFLFacePtr extrudeFaceDodeca(DLFLObjectPtr obj, DLFLFacePtr fptr, double angle, double ex_dist1, double ex_dist2, double ex_dist3);
	DLFLFacePtr extrudeDodeca_Symmetric(DLFLObjectPtr obj, DLFLFacePtr fptr, double d, double rot, double sf, int modfactor);

	DLFLFacePtr extrudeFaceCubOcta(DLFLObjectPtr obj, DLFLFacePtr fptr, double angle, int num, double ex_dist1, double ex_dist2, double ex_dist3);
	DLFLFacePtr extrudeFaceCubOcta(DLFLObjectPtr obj, DLFLFacePtr fptr, double angle, double ex_dist1, double ex_dist2, double ex_dist3);
	DLFLFacePtr extrudeFaceSmallRhombiCubOcta(DLFLObjectPtr obj, DLFLFacePtr fptr, double angle, int num, double ex_dist1, double ex_dist2, double ex_dist3);
	DLFLFacePtr extrudeFaceSmallRhombiCubOcta(DLFLObjectPtr obj, DLFLFacePtr fptr, double angle, double ex_dist1, double ex_dist2, double ex_dist3);
	
	Vector3d GetRingPosition(DLFLVertexPtrList :: iterator vl_ring, int position, int numfaces);
	DLFLVertexPtr GetRingVertex(DLFLVertexPtrList :: iterator vl_ring, int position, int numfaces);
	
	DLFLFacePtr extrudeFaceIcosa(DLFLObjectPtr obj, DLFLFacePtr fptr, double angle, int num, double ex_dist1, double ex_dist2, double ex_dist3);
	DLFLFacePtr extrudeFaceIcosa(DLFLObjectPtr obj, DLFLFacePtr fptr, double angle, double ex_dist1, double ex_dist2, double ex_dist3);
	
  // DLFLFacePtr extrudeFaceIcosa(DLFLObjectPtr obj, DLFLFacePtr fptr, double d, int num, double rot=0.0,  double sf = 1.0);
  // DLFLFacePtr extrudeFaceIcosa(DLFLObjectPtr obj, DLFLFacePtr fptr, double d, double rot, double sf = 1.0);

  void extrudeFace(DLFLObjectPtr obj, DLFLFacePtr fptr);

	void extrudeFaceDome(DLFLObjectPtr obj, DLFLFacePtr fptr, double length, double rot=0.0, double sf=1.0);

} // end namespace DLFL

#endif // _DLFLEXTRUDE_H_

#include "DLFLLighting.h"

void computeLighting( DLFLFacePtr fp, LightPtr lightptr) {
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

			// current->color = RGBColor(((double)rand() / ((double)(RAND_MAX)+(double)(1)) ),
			// 													((double)rand() / ((double)(RAND_MAX)+(double)(1)) ),
			// 													((double)rand() / ((double)(RAND_MAX)+(double)(1)) )
			// 													);
      current = current->next();
    }
  }
}

void computeLighting(DLFLObjectPtr obj, LightPtr lightptr) 
{
  DLFLFacePtrList::iterator first, last;
  DLFLFacePtr faceptr;
  first = obj->beginFace(); last = obj->endFace();
  while ( first != last ) {
    faceptr = (*first);
    computeLighting(faceptr,lightptr, usegpu);
    ++first;
  }
}


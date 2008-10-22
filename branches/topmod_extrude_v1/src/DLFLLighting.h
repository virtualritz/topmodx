#ifndef _DLFL_LIGHTING_HH_
#define _DLFL_LIGHTING_HH_

// Subroutines for lighting computations in DLFL

#include <QApplication>
#include <QProgressDialog>

#include <DLFLCommon.h>
#include <DLFLObject.h>
#include <DLFLCore.h>
#include <DLFLCoreExt.h>
#include <Light.h>

//
;
void computeLighting( DLFLFacePtr fp, LightPtr lightptr);
void computeLighting( DLFLObjectPtr obj, LightPtr lightptr);

#endif /* #ifndef _DLFL_LIGHTING_HH_ */


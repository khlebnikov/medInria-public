/*=========================================================================

 medInria

 Copyright (c) INRIA 2013. All rights reserved.
 See LICENSE.txt for details.
 
  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

=========================================================================*/

#pragma once

#include <dtkCore/dtkAbstractProcess.h>

#include <itkImage.h>

#include "msegPluginExport.h"

class medProcessPaintSegmPrivate;

//! Process that creates a segmented image.
class MEDVIEWSEGMENTATIONPLUGIN_EXPORT medProcessPaintSegm : public dtkAbstractProcess
{
    Q_OBJECT;

public:
    typedef itk::Image<unsigned char,3> SegmType;

             medProcessPaintSegm();
    virtual ~medProcessPaintSegm();

    // Create function, using new.
    static dtkAbstractProcess *create();

    //! Implement dtkAbstractObject
    virtual QString description() const;
    virtual QString identifier() const;

    static bool registered();

    static QString s_identifier();

    static QString MaskImageTypeIdentifier();
    // Input channels
    enum { ImageChannel = 0, MaskChannel = 1};

    //! Override dtkAbstractProcess
    virtual void setInput(dtkAbstractData *data, int channel);
    virtual  int update();
    virtual void *data();
    dtkAbstractData * output();

protected:
    void setOutputMetadata(const dtkAbstractData * inputData, dtkAbstractData * outputData);

private:
    medProcessPaintSegmPrivate *d;
};




/*=========================================================================

  Program:   vtkINRIA3D
  Module:    $Id: vtkDiffXMLWriter.cxx 1298 2009-10-22 12:58:07Z filus $
  Language:  C++
  Author:    $Author: filus $
  Date:      $Date: 2009-10-22 14:58:07 +0200 (Thu, 22 Oct 2009) $
  Version:   $Revision: 1298 $

  Copyright (c) 2007 INRIA - Asclepios Project. All rights reserved.
  See Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

  =========================================================================*/
#include "vtkDiffXMLWriter.h"

#include <vtksys/SystemTools.hxx>
#include <vtksys/ios/sstream>
#include <vtkstd/string>
#include <vtkstd/vector>
#include "vtkSmartPointer.h"
#include <string>
#include "vtkDataManager.h"
#include "vtkMetaDataSetSequence.h"
#include "vtkDataSet.h"
#include "vtkObjectFactory.h"
#include "vtkMetaSurfaceMesh.h"
#include <vtkPolyData.h>
#include <vtkDataArrayCollection.h>
#include <vtkCellArray.h>
#include <vtkActor.h>
#include <vtkProperty.h>
//----------------------------------------------------------------------------
vtkStandardNewMacro(vtkDiffXMLWriter);
vtkCxxRevisionMacro(vtkDiffXMLWriter, "$Revision: 1298 $");

//----------------------------------------------------------------------------
vtkDiffXMLWriter::vtkDiffXMLWriter()
{

  this->Input = 0;
  this->FileName = "";
}

//----------------------------------------------------------------------------
vtkDiffXMLWriter::~vtkDiffXMLWriter()
{
}


//----------------------------------------------------------------------------
void vtkDiffXMLWriter::PrintSelf(ostream& os, vtkIndent indent)
{
}

//----------------------------------------------------------------------------
void vtkDiffXMLWriter::SetInput (vtkDataManager* manager)
{
  this->Input = manager;
}

//----------------------------------------------------------------------------
vtkDataManager* vtkDiffXMLWriter::GetInput (void)
{
  return this->Input;
}


//----------------------------------------------------------------------------
void vtkDiffXMLWriter::Update(void)
{
  std::cout<<"writing DIFF XML type"<<std::endl;
  
  std::ostringstream os;
  
  std::vector<vtkMetaDataSet*> datasetlist = this->Input->GetMetaDataSetList();
  
  os<<"<?xml version=\"1.0\"?>\n<DIF>\n\t<DIFBody>\n\t\t<Volumes number=\""<<datasetlist.size()<<"\">\n\t\t\t";
  vtkMetaSurfaceMesh* metasurface = 0;
  vtkDataArrayCollection* arrays = vtkDataArrayCollection::New();
  for (unsigned int j=0; j<datasetlist.size(); j++)
  {
    
    vtkMetaDataSet* metadata = datasetlist[j];
    std::string filepath = metadata->GetFilePath();
    
    int val = metadata->GetType();
			
    switch (val)
    {
	case vtkMetaDataSet::VTK_META_IMAGE_DATA :
	  break;
	  
	case vtkMetaDataSet::VTK_META_SURFACE_MESH :
	  metasurface = vtkMetaSurfaceMesh::SafeDownCast(metadata);
	  
	  metadata->GetColorArrayCollection (arrays);
	  
	  os<<"<Volume name=\""<<metadata->GetName()<<"\" color=\"";
	  
	  // TODO: Color required to be in Hexadecimal values, but when asked from vtk object it is returned as RGB values, Thus conversion required here.
	  
	  //double *color; color = metadata->GetActor(0)->GetProperty()->GetColor();
	  //					
	  //					//printf("color %x",color[0]);
	  //					
	  //					
	  //					double dv;
	  //					char *sv;
	  //					int i;
	  //					
	  //					dv=0.1;
	  //					sv=(char *) &dv;
	  //					printf("sv -> ");
	  //					for (i=0;i<sizeof (double);++i)
	  //						printf("%x ",sv[i]);
	  //					printf("\n");
	  
	  os<<"\">\n\t\t\t\t<Vertices number=\""<<metasurface->GetPolyData()->GetNumberOfPoints()<<"\">\n";
	  double point[3];
	  for(vtkIdType i=0;i<metasurface->GetPolyData()->GetNumberOfPoints();i++)
	  {
	    metasurface->GetPolyData()->GetPoint(i,point);
	    os<<"\t\t\t\t\t"<<point[0]<<" "<<point[1]<<" "<<point[2]<<"\n";
	  }
	  os<<"</Vertices>";
	  os<<"\n";
	  
	  os<<"\t\t\t\t<Polygons number=\""<<metasurface->GetPolyData()->GetPolys()->GetNumberOfCells()<<"\">\n";
	  vtkIdList* pointids = vtkIdList::New();
	  
	  for(unsigned int i=0;i<metasurface->GetPolyData()->GetPolys()->GetNumberOfCells();++i)
	  {
	    metasurface->GetPolyData()->GetCellPoints(i, pointids);
	    if (pointids->GetNumberOfIds() != 3)
	    {
	      vtkWarningMacro(<<"warning : wrong type of cells !"<<endl);
	      pointids->Delete();
							
	      return;
	    }
	    os<<"\t\t\t\t\t"<<(pointids->GetId(0)+1)<<" "<<(pointids->GetId(1)+1)<<" "<<(pointids->GetId(2)+1)<<"\n";
	  }

	  pointsids->Delete();
	  
	  os<<"</Polygons>";
	  os<<"\n\t\t\t</Volume>";
	  
	  break;
	  
	case vtkMetaDataSet::VTK_META_VOLUME_MESH :
	  break;
	default :
	  break;
    }
  }

  arrays->Delete();
  
  os<<"\n\t\t</Volumes>";
  
  os<<"\n\t<DIFBody>\n<DIF>\n";
  
  // open the file:
  std::ofstream buffer (this->FileName.c_str());
  if( buffer.fail() )
  {
    vtkErrorMacro(<<"Cannot write in file !"<<endl);
    buffer.close();
  }  
	
  buffer << os.str().c_str();
  buffer.close();
}


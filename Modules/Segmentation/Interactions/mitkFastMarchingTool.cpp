/*===================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center,
Division of Medical and Biological Informatics.
All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without
even the implied warranty of MERCHANTABILITY or FITNESS FOR
A PARTICULAR PURPOSE.

See LICENSE.txt or http://www.mitk.org for details.

===================================================================*/

#include "mitkFastMarchingTool.h"
#include "mitkToolManager.h"


#include "mitkBaseRenderer.h"
#include "mitkRenderingManager.h"
#include "mitkApplicationCursor.h"

//#include "mitkFastMarchingTool.xpm"
#include "mitkInteractionConst.h"

#include "itkOrImageFilter.h"
#include "mitkImageTimeSelector.h"



namespace mitk {
  MITK_TOOL_MACRO(Segmentation_EXPORT, FastMarchingTool, "FastMarching2D tool");
}


mitk::FastMarchingTool::FastMarchingTool()
:FeedbackContourTool("PressMoveReleaseAndPointSetting"),
m_NeedUpdate(true),
m_CurrentTimeStep(0),
m_LowerThreshold(0),
m_UpperThreshold(200),
m_StoppingValue(100),
m_Sigma(1.0),
m_Alpha(-0.5),
m_Beta(3.0)
{
  CONNECT_ACTION( AcADDPOINTRMB, OnAddPoint );
  CONNECT_ACTION( AcADDPOINT, OnAddPoint );
  CONNECT_ACTION( AcREMOVEPOINT, OnDelete );

  m_ReferenceImageSliceAsITK = InternalImageType::New();

  m_ProgressCommand = mitk::ToolCommand::New();

  m_ThresholdFilter = ThresholdingFilterType::New();
  m_ThresholdFilter->SetLowerThreshold( m_LowerThreshold );
  m_ThresholdFilter->SetUpperThreshold( m_UpperThreshold );
  m_ThresholdFilter->SetOutsideValue( 0 );
  m_ThresholdFilter->SetInsideValue( 1.0 );

  m_SmoothFilter = SmoothingFilterType::New();
  m_SmoothFilter->AddObserver( itk::ProgressEvent(), m_ProgressCommand);
  m_SmoothFilter->SetTimeStep( 0.05 );
  m_SmoothFilter->SetNumberOfIterations( 2 );
  m_SmoothFilter->SetConductanceParameter( 9.0 );

  m_GradientMagnitudeFilter = GradientFilterType::New();
  m_GradientMagnitudeFilter->AddObserver( itk::ProgressEvent(), m_ProgressCommand);
  m_GradientMagnitudeFilter->SetSigma( m_Sigma );

  m_SigmoidFilter = SigmoidFilterType::New();
  m_SigmoidFilter->AddObserver( itk::ProgressEvent(), m_ProgressCommand);
  m_SigmoidFilter->SetAlpha( m_Alpha );
  m_SigmoidFilter->SetBeta( m_Beta );
  m_SigmoidFilter->SetOutputMinimum( 0.0 );
  m_SigmoidFilter->SetOutputMaximum( 1.0 );

  m_FastMarchingFilter = FastMarchingFilterType::New();
  m_FastMarchingFilter->AddObserver( itk::ProgressEvent(), m_ProgressCommand);
  m_FastMarchingFilter->SetStoppingValue( m_StoppingValue );

  m_SeedContainer = NodeContainer::New();
  m_SeedContainer->Initialize();
  m_FastMarchingFilter->SetTrialPoints( m_SeedContainer );

  //set up pipeline
  m_SmoothFilter->SetInput( m_ReferenceImageSliceAsITK );
  m_GradientMagnitudeFilter->SetInput( m_SmoothFilter->GetOutput() );
  m_SigmoidFilter->SetInput( m_GradientMagnitudeFilter->GetOutput() );
  m_FastMarchingFilter->SetInput( m_SigmoidFilter->GetOutput() );
  m_ThresholdFilter->SetInput( m_FastMarchingFilter->GetOutput() );
}

mitk::FastMarchingTool::~FastMarchingTool()
{
}


float mitk::FastMarchingTool::CanHandleEvent( StateEvent const *stateEvent) const
{
  float returnValue = Superclass::CanHandleEvent(stateEvent);

  //we can handle delete
  if(stateEvent->GetId() == 12 )
  {
    returnValue = 1.0;
  }

  return returnValue;
}


const char** mitk::FastMarchingTool::GetXPM() const
{
  return NULL;//mitkFastMarchingTool_xpm;
}

std::string mitk::FastMarchingTool::GetIconPath() const
{
  return ":/Segmentation/FastMarching_48x48.png";
}

std::string mitk::FastMarchingTool::GetCursorIconPath() const
{
  return ":/Segmentation/FastMarching_Cursor_48x48.png";
}

const char* mitk::FastMarchingTool::GetName() const
{
  return "FastMarching2D";
}

void mitk::FastMarchingTool::SetUpperThreshold(double value)
{
  m_UpperThreshold = value / 10.0;
  m_ThresholdFilter->SetUpperThreshold( m_UpperThreshold );
  m_NeedUpdate = true;
}

void mitk::FastMarchingTool::SetLowerThreshold(double value)
{
  m_LowerThreshold = value / 10.0;
  m_ThresholdFilter->SetLowerThreshold( m_LowerThreshold );
  m_NeedUpdate = true;
}

void mitk::FastMarchingTool::SetBeta(double value)
{
  if (m_Beta != value)
  {
      m_Beta = value;
      m_SigmoidFilter->SetBeta( m_Beta );
      m_NeedUpdate = true;
  }
}

void mitk::FastMarchingTool::SetSigma(double value)
{
  if (m_Sigma != value)
  {
      m_Sigma = value;
      m_GradientMagnitudeFilter->SetSigma( m_Sigma );
      m_NeedUpdate = true;
  }
}

void mitk::FastMarchingTool::SetAlpha(double value)
{
  if (m_Alpha != value)
  {
      m_Alpha = value;
      m_SigmoidFilter->SetAlpha( m_Alpha );
      m_NeedUpdate = true;
  }
}

void mitk::FastMarchingTool::SetStoppingValue(double value)
{
  if (m_StoppingValue != value)
  {
      m_StoppingValue = value;
      m_FastMarchingFilter->SetStoppingValue( m_StoppingValue );
      m_NeedUpdate = true;
  }
}

void mitk::FastMarchingTool::Activated()
{
  Superclass::Activated();

  m_ResultImageNode = mitk::DataNode::New();
  m_ResultImageNode->SetName("FastMarching_Preview");
  m_ResultImageNode->SetBoolProperty("helper object", true);
  m_ResultImageNode->SetColor(0.0, 1.0, 0.0);
  m_ResultImageNode->SetVisibility(true);
  m_ToolManager->GetDataStorage()->Add( this->m_ResultImageNode, m_ToolManager->GetReferenceData(0));

  m_SeedsAsPointSet = mitk::PointSet::New();
  m_SeedsAsPointSetNode = mitk::DataNode::New();
  m_SeedsAsPointSetNode->SetData(m_SeedsAsPointSet);
  m_SeedsAsPointSetNode->SetName("Seeds_Preview");
  m_SeedsAsPointSetNode->SetBoolProperty("helper object", true);
  m_SeedsAsPointSetNode->SetColor(0.0, 1.0, 0.0);
  m_SeedsAsPointSetNode->SetVisibility(true);
  m_ToolManager->GetDataStorage()->Add( this->m_SeedsAsPointSetNode, m_ToolManager->GetReferenceData(0));

  this->Initialize();
}

void mitk::FastMarchingTool::Deactivated()
{
  Superclass::Deactivated();
  m_ToolManager->GetDataStorage()->Remove( this->m_ResultImageNode );
  m_ToolManager->GetDataStorage()->Remove( this->m_SeedsAsPointSetNode );
  this->ClearSeeds();
  this->m_SmoothFilter->RemoveAllObservers();
  this->m_SigmoidFilter->RemoveAllObservers();
  this->m_GradientMagnitudeFilter->RemoveAllObservers();
  this->m_FastMarchingFilter->RemoveAllObservers();
  m_ResultImageNode = NULL;
  mitk::RenderingManager::GetInstance()->RequestUpdateAll();
}

void mitk::FastMarchingTool::Initialize()
{
  m_ReferenceImage = dynamic_cast<mitk::Image*>(m_ToolManager->GetReferenceData(0)->GetData());
  if(m_ReferenceImage->GetTimeSlicedGeometry()->GetTimeSteps() > 1)
  {
    mitk::ImageTimeSelector::Pointer timeSelector = ImageTimeSelector::New();
    timeSelector->SetInput( m_ReferenceImage );
    timeSelector->SetTimeNr( m_CurrentTimeStep );
    timeSelector->UpdateLargestPossibleRegion();
    m_ReferenceImage = timeSelector->GetOutput();
  }
//  CastToItkImage(m_ReferenceImage, m_ReferenceImageAsITK);
//  m_SmoothFilter->SetInput( m_ReferenceImageAsITK );
  m_NeedUpdate = true;
}

void mitk::FastMarchingTool::ConfirmSegmentation()
{
  // combine preview image with current working segmentation
  if (dynamic_cast<mitk::Image*>(m_ResultImageNode->GetData()))
  {
    //logical or combination of preview and segmentation slice
    OutputImageType::Pointer workingImageSliceInITK = OutputImageType::New();

    mitk::Image::Pointer workingImageSlice;
    mitk::Image::Pointer workingImage = dynamic_cast<mitk::Image*>(this->m_ToolManager->GetWorkingData(0)->GetData());
    if(workingImage->GetTimeSlicedGeometry()->GetTimeSteps() > 1)
    {
      mitk::ImageTimeSelector::Pointer timeSelector = mitk::ImageTimeSelector::New();
      timeSelector->SetInput( workingImage );
      timeSelector->SetTimeNr( m_CurrentTimeStep );
      timeSelector->UpdateLargestPossibleRegion();
      // todo: make GetAffectedWorkingSlice dependant of current time step
      workingImageSlice = GetAffectedWorkingSlice( m_PositionEvent );
      CastToItkImage( workingImageSlice, workingImageSliceInITK );
    }
    else
    {
      workingImageSlice = GetAffectedWorkingSlice( m_PositionEvent );
      CastToItkImage( workingImageSlice, workingImageSliceInITK );
    }

    typedef itk::OrImageFilter<OutputImageType, OutputImageType> OrImageFilterType;
    OrImageFilterType::Pointer orFilter = OrImageFilterType::New();

    orFilter->SetInput(0, m_ThresholdFilter->GetOutput());
    orFilter->SetInput(1, workingImageSliceInITK);
    orFilter->Update();

    mitk::Image::Pointer segmentationResult = mitk::Image::New();

    mitk::CastToMitkImage(orFilter->GetOutput(), segmentationResult);
    segmentationResult->GetGeometry()->SetOrigin(workingImageSlice->GetGeometry()->GetOrigin());
    segmentationResult->GetGeometry()->SetIndexToWorldTransform(workingImageSlice->GetGeometry()->GetIndexToWorldTransform());

    //write to segmentation volume and hide preview image
    // again, current time step is not considered
    this->WriteBackSegmentationResult(m_PositionEvent, segmentationResult );
    this->m_ResultImageNode->SetVisibility(false);
    this->ClearSeeds();
//    workingImage->Modified();
  }

  mitk::RenderingManager::GetInstance()->RequestUpdateAll();
}


bool mitk::FastMarchingTool::OnAddPoint(Action* action, const StateEvent* stateEvent)
{
  // Add a new seed point for FastMarching algorithm
  const PositionEvent* p = dynamic_cast<const PositionEvent*>(stateEvent->GetEvent());
  if (!p) return false;

  m_PositionEvent = new PositionEvent(p->GetSender(), p->GetType(), p->GetButton(), p->GetButtonState(), p->GetKey(), p->GetDisplayPosition(), p->GetWorldPosition());

  m_ReferenceImageSlice = GetAffectedReferenceSlice( m_PositionEvent );

  CastToItkImage(m_ReferenceImageSlice, m_ReferenceImageSliceAsITK);
  m_SmoothFilter->SetInput( m_ReferenceImageSliceAsITK );
/*
  //if click happpened in another renderwindow or slice then reset pipeline and preview
  if( (m_LastEventSender != m_PositionEvent->GetSender()) || (m_LastEventSlice != m_PositionEvent->GetSender()->GetSlice()) )
  {
//    this->ResetFastMarching(m_PositionEvent);
      this->Reset
  }
*/
  m_LastEventSender = m_PositionEvent->GetSender();
  m_LastEventSlice = m_LastEventSender->GetSlice();

  mitk::Point3D clickInIndex;

  m_ReferenceImageSlice->GetGeometry()->WorldToIndex(m_PositionEvent->GetWorldPosition(), clickInIndex);
  itk::Index<2> seedPosition;
  seedPosition[0] = clickInIndex[0];
  seedPosition[1] = clickInIndex[1];
//  seedPosition[2] = clickInIndex[2];

  NodeType node;
  const double seedValue = 0.0;
  node.SetValue( seedValue );
  node.SetIndex( seedPosition );
  this->m_SeedContainer->InsertElement(this->m_SeedContainer->Size(), node);
  m_FastMarchingFilter->Modified();

  m_SeedsAsPointSet->InsertPoint(m_SeedsAsPointSet->GetSize(), m_PositionEvent->GetWorldPosition());

  mitk::RenderingManager::GetInstance()->RequestUpdateAll();

  m_NeedUpdate = true;

  this->Update();

  return true;
}


bool mitk::FastMarchingTool::OnDelete(Action* action, const StateEvent* stateEvent)
{
  // delete last seed point
  if(!(this->m_SeedContainer->empty()))
  {
    //delete last element of seeds container
    this->m_SeedContainer->pop_back();
    m_FastMarchingFilter->Modified();

    //delete last point in pointset - somehow ugly
    m_SeedsAsPointSet->GetPointSet()->GetPoints()->DeleteIndex(m_SeedsAsPointSet->GetSize() - 1);

    mitk::RenderingManager::GetInstance()->RequestUpdateAll();

    m_NeedUpdate = true;

    this->Update();
  }
  return true;
}


void mitk::FastMarchingTool::Update()
{
  // update FastMarching pipeline and show result
  if (m_NeedUpdate)
  {
    m_ProgressCommand->AddStepsToDo(20);
    CurrentlyBusy.Send(true);
    try
    {
      m_ThresholdFilter->Update();
    }
    catch( itk::ExceptionObject & excep )
    {
     MITK_ERROR << "Exception caught: " << excep.GetDescription();

     m_ProgressCommand->SetRemainingProgress(100);
     CurrentlyBusy.Send(false);

     std::string msg = excep.GetDescription();
     ErrorMessage.Send(msg);

     return;
    }
    m_ProgressCommand->SetRemainingProgress(100);
    CurrentlyBusy.Send(false);

    //make output visible
    mitk::Image::Pointer result = mitk::Image::New();
    CastToMitkImage( m_ThresholdFilter->GetOutput(), result);
    result->GetGeometry()->SetOrigin(m_ReferenceImageSlice->GetGeometry()->GetOrigin() );
    result->GetGeometry()->SetIndexToWorldTransform(m_ReferenceImageSlice->GetGeometry()->GetIndexToWorldTransform() );
    m_ResultImageNode->SetData(result);
    m_ResultImageNode->SetVisibility(true);
    mitk::RenderingManager::GetInstance()->RequestUpdateAll();
  }
}


void mitk::FastMarchingTool::ClearSeeds()
{
  // clear seeds for FastMarching as well as the PointSet for visualization
  this->m_SeedContainer->Initialize();
  this->m_SeedsAsPointSet->Clear();

  m_FastMarchingFilter->Modified();

  this->m_NeedUpdate = true;
}


void mitk::FastMarchingTool::Reset()
{
  //clear all seeds and preview empty result
  this->ClearSeeds();

  m_ResultImageNode->SetVisibility(false);

  mitk::RenderingManager::GetInstance()->RequestUpdateAll();
}

void mitk::FastMarchingTool::SetCurrentTimeStep(int t)
{
  if( m_CurrentTimeStep != t )
  {
    m_CurrentTimeStep = t;

    this->Initialize();
  }
}

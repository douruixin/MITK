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
#ifndef itkGibbsTrackingFilter_h
#define itkGibbsTrackingFilter_h

// MITK
#include <mitkSphereInterpolator.h>

// ITK
#include <itkProcessObject.h>
#include <itkImage.h>
#include <itkDiffusionTensor3D.h>
#include <itkMersenneTwisterRandomVariateGenerator.h>

// VTK
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkCellArray.h>
#include <vtkPoints.h>
#include <vtkPolyLine.h>

namespace itk{

template< class ItkQBallImageType >
class GibbsTrackingFilter : public ProcessObject
{
public:
    typedef GibbsTrackingFilter Self;
    typedef ProcessObject Superclass;
    typedef SmartPointer< Self > Pointer;
    typedef SmartPointer< const Self > ConstPointer;

    itkNewMacro(Self)
    itkTypeMacro( GibbsTrackingFilter, ProcessObject )

    typedef Image< DiffusionTensor3D<float>, 3 >    ItkTensorImage;
    typedef typename ItkQBallImageType::Pointer     ItkQBallImageTypePointer;
    typedef Image< float, 3 >                       ItkFloatImageType;
    typedef vtkSmartPointer< vtkPolyData >          FiberPolyDataType;

    // parameter setter
    itkSetMacro( StartTemperature, float )
    itkSetMacro( EndTemperature, float )
    itkSetMacro( Iterations, unsigned long )
    itkSetMacro( ParticleWeight, float )
    itkSetMacro( ParticleWidth, float )
    itkSetMacro( ParticleLength, float )
    itkSetMacro( ConnectionPotential, float )
    itkSetMacro( InexBalance, float )
    itkSetMacro( ParticlePotential, float )
    itkSetMacro( MinFiberLength, int )
    itkSetMacro( AbortTracking, bool )
    itkSetMacro( CurvatureThreshold, float)
    itkSetMacro( DuplicateImage, bool )
    itkSetMacro( RandomSeed, int )
    itkSetMacro( LoadParameterFile, std::string )
    itkSetMacro( SaveParameterFile, std::string )
    itkSetMacro( LutPath, std::string )

    // getter
    itkGetMacro( ParticleWeight, float )
    itkGetMacro( ParticleWidth, float )
    itkGetMacro( ParticleLength, float )
    itkGetMacro( CurrentStep, unsigned long )
    itkGetMacro( NumParticles, int )
    itkGetMacro( NumConnections, int )
    itkGetMacro( NumAcceptedFibers, int )
    itkGetMacro( ProposalAcceptance, float )
    itkGetMacro( Steps, unsigned int)

    // input data
    itkSetMacro(QBallImage, typename ItkQBallImageType::Pointer)
    itkSetMacro(MaskImage, ItkFloatImageType::Pointer)
    itkSetMacro(TensorImage, ItkTensorImage::Pointer)

    void GenerateData();

    virtual void Update(){
        this->GenerateData();
    }

    FiberPolyDataType GetFiberBundle();

protected:

    GibbsTrackingFilter();
    virtual ~GibbsTrackingFilter();
    void EstimateParticleWeight();
    void PrepareMaskImage();
    bool LoadParameters();
    bool SaveParameters();

    // Input Images
    typename ItkQBallImageType::Pointer m_QBallImage;
    typename ItkFloatImageType::Pointer m_MaskImage;
    typename ItkTensorImage::Pointer    m_TensorImage;

    // Tracking parameters
    float           m_StartTemperature;     // Start temperature
    float           m_EndTemperature;       // End temperature
    unsigned long   m_Iterations;           // Total number of iterations
    unsigned long   m_CurrentStep;          // current tracking step
    float           m_ParticleWeight;       // w (unitless)
    float           m_ParticleWidth;        // sigma  (mm)
    float           m_ParticleLength;       // l (mm)
    float           m_ConnectionPotential;  // gross L (chemisches potential, default 10)
    float           m_InexBalance;          // gewichtung zwischen den lambdas; -5 ... 5 -> nur intern ... nur extern,default 0
    float           m_ParticlePotential;    // default 0.2
    int             m_MinFiberLength;       // discard all fibers shortan than the specified length in mm
    bool            m_AbortTracking;        // set flag to abort tracking
    int             m_NumAcceptedFibers;    // number of reconstructed fibers generated by the FiberBuilder
    volatile bool   m_BuildFibers;          // set flag to generate fibers from particle grid
    unsigned int    m_Steps;                // number of temperature decrease steps
    float           m_ProposalAcceptance;   // proposal acceptance rate (0-1)
    float           m_CurvatureThreshold;   // curvature threshold in radians (1 -> no curvature is accepted, -1 all curvature angles are accepted)
    bool            m_DuplicateImage;       // generates a working copy of the qball image so that the original image won't be changed by the mean subtraction
    int             m_NumParticles;         // current number of particles in grid
    int             m_NumConnections;       // current number of connections between particles in grid
    int             m_RandomSeed;           // seed value for random generator (-1 for standard seeding)
    std::string     m_LoadParameterFile;    // filename of parameter file (reader)
    std::string     m_SaveParameterFile;    // filename of parameter file (writer)
    std::string     m_LutPath;              // path to lookuptables used by the sphere interpolator

    FiberPolyDataType m_FiberPolyData;      // container for reconstructed fibers

    //Constant values
    static const int m_ParticleGridCellCapacity = 1024;
};
}

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkGibbsTrackingFilter.cpp"
#endif

#endif

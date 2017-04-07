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


#ifndef MITK_PHOTOACOUSTICS_BEAMFORMING_DAS_FILTER
#define MITK_PHOTOACOUSTICS_BEAMFORMING_DAS_FILTER

#include "mitkImageToImageFilter.h"
#include <functional>

namespace mitk {

  //##Documentation
  //## @brief
  //## @ingroup Process
  class BeamformingDASFilter : public ImageToImageFilter
  {
  public:
    mitkClassMacro(BeamformingDASFilter, ImageToImageFilter);

    itkFactorylessNewMacro(Self)
      itkCloneMacro(Self)

    struct beamformingSettings
    {
      double Pitch = 0.0003; // [m]
      float SpeedOfSound = 1540; // [m/s]
      unsigned int SamplesPerLine = 2048;
      unsigned int ReconstructionLines = 128;
      double RecordTime = 0.00006; // [s]
      unsigned int TransducerElements = 128;

      enum DelayCalc {Linear, QuadApprox, Spherical};
      DelayCalc DelayCalculationMethod = QuadApprox;

      enum Apodization {Hamm, Hann, Box};
      Apodization Apod = Hann;

      double Angle = 10;
      bool Photoacoustic = true;
      double BPHighPass = 50;
      double BPLowPass = 50;
      double BPFalloff = 0.2;
      bool UseBP = false;
    };

    void Configure(beamformingSettings settings);

    void SetProgressHandle(std::function<void(int, std::string)> progressHandle);

  protected:

    BeamformingDASFilter();

    ~BeamformingDASFilter();

    virtual void GenerateInputRequestedRegion() override;

    virtual void GenerateOutputInformation() override;

    virtual void GenerateData() override;

    //##Description
    //## @brief Time when Header was last initialized
    itk::TimeStamp m_TimeOfHeaderInitialization;

    std::function<void(int, std::string)> m_ProgressHandle;

    double* VonHannFunction(int samples);
    double* HammFunction(int samples);
    double* BoxFunction(int samples);

    void DASLinearLine(double* input, double* output, double inputDim[2], double outputDim[2], const unsigned short& line, double* apodisation, const unsigned short& apodArraySize);
    void DASQuadraticLine(double* input, double* output, double inputDim[2], double outputDim[2], const unsigned short& line, double* apodisation, const unsigned short& apodArraySize);
    void DASSphericalLine(double* input, double* output, double inputDim[2], double outputDim[2], const unsigned short& line, double* apodisation, const unsigned short& apodArraySize);

    mitk::Image::Pointer BandpassFilter(mitk::Image::Pointer data);
    itk::Image<double, 3U>::Pointer BPFunction(mitk::Image::Pointer reference, int width, int center);

    double* m_OutputData;
    double* m_InputData;
    double* m_InputDataPuffer;

    beamformingSettings m_Conf;
  };

} // namespace mitk

#endif MITK_PHOTOACOUSTICS_BEAMFORMING_DAS_FILTER

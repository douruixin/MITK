SET(H_FILES
  Algorithms/itkImportMitkImageContainer.h
  Algorithms/itkImportMitkImageContainer.txx
  Algorithms/itkLocalVariationImageFilter.h
  Algorithms/itkLocalVariationImageFilter.txx
  Algorithms/itkMITKScalarImageToHistogramGenerator.h
  Algorithms/itkMITKScalarImageToHistogramGenerator.txx
  Algorithms/itkTotalVariationDenoisingImageFilter.h
  Algorithms/itkTotalVariationDenoisingImageFilter.txx
  Algorithms/itkTotalVariationSingleIterationImageFilter.h
  Algorithms/itkTotalVariationSingleIterationImageFilter.txx

  Algorithms/mitkImageAccessByItk.h
  Algorithms/mitkImageCast.h
  Algorithms/mitkImageToItk.h
  Algorithms/mitkImageToItk.txx
  Algorithms/mitkInstantiateAccessFunctions.h
  Algorithms/mitkITKImageImport.h
  Algorithms/mitkITKImageImport.txx
  Algorithms/mitkPixelTypeList.h

  # Preprocessor macros taken from Boost
  Algorithms/mitkPPArithmeticDec.h
  Algorithms/mitkPPArgCount.h
  Algorithms/mitkPPCat.h
  Algorithms/mitkPPConfig.h
  Algorithms/mitkPPControlExprIIf.h
  Algorithms/mitkPPControlIf.h
  Algorithms/mitkPPControlIIf.h
  Algorithms/mitkPPDebugError.h
  Algorithms/mitkPPDetailAutoRec.h
  Algorithms/mitkPPDetailDMCAutoRec.h
  Algorithms/mitkPPExpand.h
  Algorithms/mitkPPFacilitiesEmpty.h
  Algorithms/mitkPPFacilitiesExpand.h
  Algorithms/mitkPPLogicalBool.h
  Algorithms/mitkPPRepetitionDetailDMCFor.h
  Algorithms/mitkPPRepetitionDetailEDGFor.h
  Algorithms/mitkPPRepetitionDetailFor.h
  Algorithms/mitkPPRepetitionDetailMSVCFor.h
  Algorithms/mitkPPRepetitionFor.h
  Algorithms/mitkPPSeqElem.h
  Algorithms/mitkPPSeqForEach.h
  Algorithms/mitkPPSeqForEachProduct.h
  Algorithms/mitkPPSeq.h
  Algorithms/mitkPPSeqEnum.h
  Algorithms/mitkPPSeqSize.h
  Algorithms/mitkPPSeqToTuple.h
  Algorithms/mitkPPStringize.h
  Algorithms/mitkPPTupleEat.h
  Algorithms/mitkPPTupleElem.h
  Algorithms/mitkPPTupleRem.h
  Algorithms/mitkClippedSurfaceBoundsCalculator.h

  IO/mitkPixelTypeTraits.h

  DataManagement/mitkCommon.h
  Interactions/mitkEventMapperAddOn.h

  Service/mitkAny.h
  Service/mitkGetModuleContext.h
  Service/mitkItkHashMap.h
  Service/mitkItkHashSet.h
  Service/mitkItkHashTable.h
  Service/mitkModuleAbstractTracked.h
  Service/mitkModuleAbstractTracked.tpp
  Service/mitkModuleActivator.h
  Service/mitkServiceFactory.h
  Service/mitkServiceTracker.h
  Service/mitkServiceTracker.tpp
  Service/mitkServiceTrackerCustomizer.h
  Service/mitkServiceTrackerPrivate.h
  Service/mitkServiceTrackerPrivate.tpp
  Service/mitkServiceUtils.h
  Service/mitkSharedData.h
  Service/mitkStaticInit.h
  Service/mitkTrackedService.h
  Service/mitkTrackedService.tpp
  Service/mitkTrackedServiceListener.h
)

SET(CPP_FILES
  Algorithms/mitkBaseDataSource.cpp
  Algorithms/mitkBaseProcess.cpp
  Algorithms/mitkCoreObjectFactoryBase.cpp
  Algorithms/mitkCoreObjectFactory.cpp
  Algorithms/mitkDataNodeFactory.cpp
  Algorithms/mitkDataNodeSource.cpp
  Algorithms/mitkGeometry2DDataToSurfaceFilter.cpp
  Algorithms/mitkHistogramGenerator.cpp
  Algorithms/mitkImageCaster.cpp
  Algorithms/mitkImageCastPart1.cpp
  Algorithms/mitkImageCastPart2.cpp
  Algorithms/mitkImageCastPart3.cpp
  Algorithms/mitkImageCastPart4.cpp
  Algorithms/mitkImageChannelSelector.cpp
  Algorithms/mitkImageSliceSelector.cpp
  Algorithms/mitkImageSource.cpp
  Algorithms/mitkImageTimeSelector.cpp
  Algorithms/mitkImageToImageFilter.cpp
  Algorithms/mitkPointSetSource.cpp
  Algorithms/mitkPointSetToPointSetFilter.cpp
  Algorithms/mitkRGBToRGBACastImageFilter.cpp
  Algorithms/mitkSubImageSelector.cpp
  Algorithms/mitkSurfaceSource.cpp
  Algorithms/mitkSurfaceToSurfaceFilter.cpp
  Algorithms/mitkUIDGenerator.cpp
  Algorithms/mitkVolumeCalculator.cpp
  Algorithms/mitkClippedSurfaceBoundsCalculator.cpp
  Controllers/mitkBaseController.cpp
  Controllers/mitkCallbackFromGUIThread.cpp
  Controllers/mitkCameraController.cpp
  Controllers/mitkCameraRotationController.cpp
  Controllers/mitkFocusManager.cpp
  Controllers/mitkLimitedLinearUndo.cpp
  Controllers/mitkOperationEvent.cpp
  Controllers/mitkProgressBar.cpp
  Controllers/mitkRenderingManager.cpp
  Controllers/mitkSliceNavigationController.cpp
  Controllers/mitkSlicesCoordinator.cpp
  Controllers/mitkSlicesRotator.cpp
  Controllers/mitkSlicesSwiveller.cpp
  Controllers/mitkStatusBar.cpp
  Controllers/mitkStepper.cpp
  Controllers/mitkTestManager.cpp
  Controllers/mitkUndoController.cpp
  Controllers/mitkVerboseLimitedLinearUndo.cpp
  Controllers/mitkVtkInteractorCameraController.cpp
  Controllers/mitkVtkLayerController.cpp
  DataManagement/mitkAbstractTransformGeometry.cpp
  DataManagement/mitkAnnotationProperty.cpp
  DataManagement/mitkApplicationCursor.cpp
  DataManagement/mitkBaseData.cpp
  DataManagement/mitkBaseProperty.cpp
  DataManagement/mitkClippingProperty.cpp
  DataManagement/mitkChannelDescriptor.cpp
  DataManagement/mitkColorProperty.cpp
  DataManagement/mitkDataStorage.cpp
  #DataManagement/mitkDataTree.cpp
  DataManagement/mitkDataNode.cpp
  #DataManagement/mitkDataTreeStorage.cpp
  DataManagement/mitkDisplayGeometry.cpp
  DataManagement/mitkEnumerationProperty.cpp
  DataManagement/mitkGeometry2D.cpp
  DataManagement/mitkGeometry2DData.cpp
  DataManagement/mitkGeometry3D.cpp
  DataManagement/mitkGeometryData.cpp
  DataManagement/mitkGroupTagProperty.cpp
  DataManagement/mitkImage.cpp
  DataManagement/mitkImageDataItem.cpp
  DataManagement/mitkImageDescriptor.cpp
  DataManagement/mitkLandmarkBasedCurvedGeometry.cpp
  DataManagement/mitkLandmarkProjectorBasedCurvedGeometry.cpp
  DataManagement/mitkLandmarkProjector.cpp
  DataManagement/mitkLevelWindow.cpp
  DataManagement/mitkLevelWindowManager.cpp
  DataManagement/mitkLevelWindowPreset.cpp
  DataManagement/mitkLevelWindowProperty.cpp
  DataManagement/mitkLookupTable.cpp
  DataManagement/mitkLookupTables.cpp # specializations of GenericLookupTable
  DataManagement/mitkMemoryUtilities.cpp
  DataManagement/mitkModalityProperty.cpp
  DataManagement/mitkModeOperation.cpp
  DataManagement/mitkNodePredicateAnd.cpp
  DataManagement/mitkNodePredicateBase.cpp
  DataManagement/mitkNodePredicateCompositeBase.cpp
  DataManagement/mitkNodePredicateData.cpp
  DataManagement/mitkNodePredicateDataType.cpp
  DataManagement/mitkNodePredicateDimension.cpp
  DataManagement/mitkNodePredicateFirstLevel.cpp
  DataManagement/mitkNodePredicateNot.cpp
  DataManagement/mitkNodePredicateOr.cpp
  DataManagement/mitkNodePredicateProperty.cpp
  DataManagement/mitkNodePredicateSource.cpp
  DataManagement/mitkPlaneOrientationProperty.cpp
  DataManagement/mitkPlaneGeometry.cpp
  DataManagement/mitkPlaneOperation.cpp
  DataManagement/mitkPointOperation.cpp
  DataManagement/mitkPointSet.cpp
  DataManagement/mitkProperties.cpp
  DataManagement/mitkPropertyList.cpp
  DataManagement/mitkRotationOperation.cpp
  DataManagement/mitkSlicedData.cpp
  DataManagement/mitkSlicedGeometry3D.cpp
  DataManagement/mitkSmartPointerProperty.cpp
  DataManagement/mitkStandaloneDataStorage.cpp
  DataManagement/mitkStateTransitionOperation.cpp
  DataManagement/mitkStringProperty.cpp
  DataManagement/mitkSurface.cpp
  DataManagement/mitkSurfaceOperation.cpp
  DataManagement/mitkThinPlateSplineCurvedGeometry.cpp
  DataManagement/mitkTimeSlicedGeometry.cpp
  DataManagement/mitkTransferFunction.cpp
  DataManagement/mitkTransferFunctionInitializer.cpp
  DataManagement/mitkVector.cpp
  DataManagement/mitkVtkInterpolationProperty.cpp
  DataManagement/mitkVtkRepresentationProperty.cpp
  DataManagement/mitkVtkResliceInterpolationProperty.cpp
  DataManagement/mitkVtkScalarModeProperty.cpp
  DataManagement/mitkVtkVolumeRenderingProperty.cpp
  DataManagement/mitkWeakPointerProperty.cpp
  DataManagement/mitkShaderProperty.cpp
  DataManagement/mitkResliceMethodProperty.cpp
  DataManagement/mitkMaterial.cpp
  Interactions/mitkAction.cpp
  Interactions/mitkAffineInteractor.cpp
  Interactions/mitkCoordinateSupplier.cpp
  Interactions/mitkDisplayCoordinateOperation.cpp
  Interactions/mitkDisplayInteractor.cpp
  Interactions/mitkDisplayPositionEvent.cpp
  Interactions/mitkDisplayVectorInteractor.cpp
  Interactions/mitkDisplayVectorInteractorLevelWindow.cpp
  Interactions/mitkDisplayVectorInteractorScroll.cpp
  Interactions/mitkEvent.cpp
  Interactions/mitkEventDescription.cpp
  Interactions/mitkEventMapper.cpp
  Interactions/mitkGlobalInteraction.cpp
  Interactions/mitkInteractor.cpp
  Interactions/mitkMouseMovePointSetInteractor.cpp
  Interactions/mitkMoveSurfaceInteractor.cpp
  Interactions/mitkNodeDepententPointSetInteractor.cpp
  Interactions/mitkPointSetInteractor.cpp
  Interactions/mitkPositionEvent.cpp
  Interactions/mitkPositionTracker.cpp
  Interactions/mitkState.cpp
  Interactions/mitkStateEvent.cpp
  Interactions/mitkStateMachine.cpp
  Interactions/mitkStateMachineFactory.cpp
  Interactions/mitkTransition.cpp
  Interactions/mitkWheelEvent.cpp
  Interactions/mitkKeyEvent.cpp
  Interactions/mitkVtkEventAdapter.cpp
  Interactions/mitkCrosshairPositionEvent.cpp
  IO/mitkBaseDataIOFactory.cpp
  IO/mitkDicomSeriesReader.cpp
  IO/mitkFileReader.cpp
  IO/mitkFileSeriesReader.cpp
  IO/mitkFileWriter.cpp
  #IO/mitkIpPicGet.c
  IO/mitkImageGenerator.cpp
  IO/mitkImageWriter.cpp
  IO/mitkImageWriterFactory.cpp
  IO/mitkItkImageFileIOFactory.cpp
  IO/mitkItkImageFileReader.cpp
  IO/mitkItkPictureWrite.cpp
  IO/mitkLookupTableProperty.cpp
  IO/mitkOperation.cpp
  #IO/mitkPicFileIOFactory.cpp
  #IO/mitkPicFileReader.cpp
  #IO/mitkPicFileWriter.cpp
  #IO/mitkPicHelper.cpp
  #IO/mitkPicVolumeTimeSeriesIOFactory.cpp
  #IO/mitkPicVolumeTimeSeriesReader.cpp
  IO/mitkPixelType.cpp
  IO/mitkPointSetIOFactory.cpp
  IO/mitkPointSetReader.cpp
  IO/mitkPointSetWriter.cpp
  IO/mitkPointSetWriterFactory.cpp
  IO/mitkRawImageFileReader.cpp
  IO/mitkStandardFileLocations.cpp
  IO/mitkSTLFileIOFactory.cpp
  IO/mitkSTLFileReader.cpp
  IO/mitkSurfaceVtkWriter.cpp
  IO/mitkSurfaceVtkWriterFactory.cpp
  IO/mitkVtiFileIOFactory.cpp
  IO/mitkVtiFileReader.cpp
  IO/mitkVtkImageIOFactory.cpp
  IO/mitkVtkImageReader.cpp
  IO/mitkVtkSurfaceIOFactory.cpp
  IO/mitkVtkSurfaceReader.cpp
  IO/vtkPointSetXMLParser.cpp
  IO/mitkLog.cpp
  Rendering/mitkBaseRenderer.cpp
  Rendering/mitkVtkMapper2D.cpp
  Rendering/mitkVtkMapper3D.cpp
  Rendering/mitkRenderWindowFrame.cpp
  Rendering/mitkGeometry2DDataMapper2D.cpp
  Rendering/mitkGeometry2DDataVtkMapper3D.cpp
  Rendering/mitkGLMapper2D.cpp
  Rendering/mitkGradientBackground.cpp
  Rendering/mitkManufacturerLogo.cpp
  Rendering/mitkMapper2D.cpp
  Rendering/mitkMapper3D.cpp
  Rendering/mitkMapper.cpp
  Rendering/mitkPointSetGLMapper2D.cpp
  Rendering/mitkPointSetVtkMapper3D.cpp
  Rendering/mitkPolyDataGLMapper2D.cpp
  Rendering/mitkSurfaceGLMapper2D.cpp
  Rendering/mitkSurfaceVtkMapper3D.cpp
  Rendering/mitkVolumeDataVtkMapper3D.cpp
  Rendering/mitkVtkPropRenderer.cpp
  Rendering/mitkVtkWidgetRendering.cpp
  Rendering/vtkMitkRectangleProp.cpp
  Rendering/vtkMitkRenderProp.cpp
  Rendering/mitkVtkEventProvider.cpp
  Rendering/mitkRenderWindow.cpp
  Rendering/mitkRenderWindowBase.cpp
  Rendering/mitkShaderRepository.cpp
  Rendering/mitkImageVtkMapper2D.cpp
  Rendering/vtkMitkThickSlicesFilter.cpp
  Rendering/vtkMitkApplyLevelWindowToRGBFilter.cpp
  Service/mitkAtomicInt.cpp
  Service/mitkCoreActivator.cpp
  Service/mitkCoreModuleContext.cpp
  Service/mitkModule.cpp
  Service/mitkModuleContext.cpp
  Service/mitkModuleEvent.cpp
  Service/mitkModuleInfo.cpp
  Service/mitkModulePrivate.cpp
  Service/mitkModuleRegistry.cpp
  Service/mitkModuleUtils.cpp
  Service/mitkModuleVersion.cpp
  Service/mitkLDAPExpr.cpp
  Service/mitkLDAPFilter.cpp
  Service/mitkServiceEvent.cpp
  Service/mitkServiceException.cpp
  Service/mitkServiceListenerEntry.cpp
  Service/mitkServiceListeners.cpp
  Service/mitkServiceProperties.cpp
  Service/mitkServiceReference.cpp
  Service/mitkServiceReferencePrivate.cpp
  Service/mitkServiceRegistration.cpp
  Service/mitkServiceRegistrationPrivate.cpp
  Service/mitkServiceRegistry.cpp
)


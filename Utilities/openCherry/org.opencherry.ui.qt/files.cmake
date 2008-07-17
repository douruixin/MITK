SET(CPP_FILES
  manifest.cpp
  cherryLogView.cpp
  cherryQtEditorPart.cpp
  cherryQtLogView.cpp
  cherryQtUIPlugin.cpp
  cherryQtViewPart.cpp
  cherryQtWorkbenchPageTweaklet.cpp
  cherryQtWorkbenchTweaklet.cpp
  #cherryQtWorkbenchWindow.cpp
  cherryQtSimpleWorkbenchWindow.cpp
  
  # application
  application/cherryQtActionBarAdvisor.cpp
  application/cherryQtWorkbenchAdvisor.cpp
)

SET(INTERNAL_CPP_FILES
  cherryQtEditorPane.cpp
  cherryQtErrorView.cpp
  cherryQtShowViewAction.cpp
  cherryQtViewPane.cpp
  cherryQtPlatformLogModel.cpp
  cherryQtShowViewDialog.cpp
  cherryQtSimpleEditorAreaHelper.cpp
)

SET(MOC_H_FILES
  cherryQtSimpleWorkbenchWindow.h
  internal/cherryQtShowViewAction.h
  internal/cherryQtViewPane.h
)

SET(UI_FILES
  internal/cherryQtShowViewDialog.ui
  cherryQtLogView.ui
)

foreach(file ${INTERNAL_CPP_FILES})
  SET(CPP_FILES ${CPP_FILES} internal/${file})
endforeach(file ${INTERNAL_CPP_FILES})
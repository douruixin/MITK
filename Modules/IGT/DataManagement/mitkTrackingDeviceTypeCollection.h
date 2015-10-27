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

#ifndef TRACKINGDEVICETYPECOLLECTION_H_INCLUDED
#define TRACKINGDEVICETYPECOLLECTION_H_INCLUDED

#include <MitkIGTExports.h>

#include "mitkTrackingTypes.h"
#include "mitkTrackingDeviceTypeInformation.h"

// Microservices
#include <mitkServiceInterface.h>
#include <usServiceRegistration.h>

namespace mitk {
  /**Documentation
  * \brief
  *
  * \ingroup IGT
  */
  class MITKIGT_EXPORT TrackingDeviceTypeCollection
  {
    public:

      TrackingDeviceTypeCollection();
      ~TrackingDeviceTypeCollection();

      /**
      *\brief Registers this object as a Microservice, making it available to every module and/or plugin.
      * To unregister, call UnregisterMicroservice().
      */
      virtual void RegisterAsMicroservice();

      /**
      *\brief Registers this object as a Microservice, making it available to every module and/or plugin.
      */
      virtual void UnRegisterMicroservice();

      /**
      *\brief Returns the id that this device is registered with. The id will only be valid, if the
      * NavigationDataSource has been registered using RegisterAsMicroservice().
      */
      std::string GetMicroserviceID();

      /**
      *\brief These Constants are used in conjunction with Microservices
      */
      static const std::string US_INTERFACE_NAME;
      static const std::string US_PROPKEY_DEVICENAME;
      static const std::string US_PROPKEY_ID;
      static const std::string US_PROPKEY_ISACTIVE; //NOT IMPLEMENTED YET!

      void RegisterTrackingDeviceType(TrackingDeviceTypeInformation* typeInformation);

      TrackingDeviceTypeInformation* GetTrackingDeviceTypeInformation(TrackingDeviceType type);

    private:

      us::ServiceRegistration<TrackingDeviceTypeCollection> m_ServiceRegistration;

      std::vector<TrackingDeviceTypeInformation*> m_TypeInformations;

      std::string m_Name;

  };
} // namespace mitk
MITK_DECLARE_SERVICE_INTERFACE(mitk::TrackingDeviceTypeCollection, "org.mitk.services.TrackingDeviceTypeCollection")
#endif //TRACKINGDEVICETYPECOLLECTION_H_INCLUDED

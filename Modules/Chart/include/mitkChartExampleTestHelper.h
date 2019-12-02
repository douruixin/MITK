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

#ifndef MITK_CHART_EXAMPLE_TEST_HELPER_H
#define MITK_CHART_EXAMPLE_TEST_HELPER_H

#include <MitkChartExports.h>

// mitk core
#include <QmitkChartxyData.h>
#include <QmitkChartWidget.h>

// std includes
#include <map>
#include <memory>
#include <vector>
#include <string>

namespace mitk
{
    class MITKCHART_EXPORT ChartExampleTestHelper
    {

    public:
        //////////////////////////////////////////////////////////////////////////
        // ACCESS TO DATA SETS
        //////////////////////////////////////////////////////////////////////////

        std::unique_ptr<QmitkChartxyData> GetDataOne();
        std::unique_ptr<QmitkChartxyData> GetDataTwo();
        std::unique_ptr<QmitkChartxyData> GetDataThree();
        std::unique_ptr<QmitkChartxyData> GetDataFour();
        std::unique_ptr<QmitkChartxyData> GetDataFive();

        //////////////////////////////////////////////////////////////////////////
        // INSTANCE OF CLASS TO BE TESTED
        //////////////////////////////////////////////////////////////////////////

        QmitkChartWidget qmitkChartWidget;

        //////////////////////////////////////////////////////////////////////////
        // AUXILIARY FUNCTIONS
        //////////////////////////////////////////////////////////////////////////

        QmitkChartWidget::ChartType ReturnChartTypeByString(std::string chartTypeString);
        QmitkChartWidget::ChartColor ReturnChartColorByString(std::string chartColorString);
        QmitkChartWidget::LineStyle ReturnChartStyleByString(std::string chartStyleString);

        void Add(int dataSet);
        std::map<double, double> ToStdMap(QVariantList xData, QVariantList yData);
        void ClearMemory();

    }; // end ChartExampleTestHelper
} // end mitk

#endif
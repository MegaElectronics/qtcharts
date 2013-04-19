/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qpolarchart.h"
#include "qabstractaxis.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \enum QPolarChart::PolarOrientation

   This type is used to signify the polar orientation of an axis.

    \value PolarOrientationRadial
    \value PolarOrientationAngular
*/

/*!
 \class QPolarChart
 \brief QtCommercial chart API.

 QPolarChart is a specialization of QChart to show a polar chart.

 Polar charts support line, spline, area, and scatter series, and all axis types
 supported by those series.

 \note When setting ticks to an angular QValueAxis, keep in mind that the first and last tick
 are co-located at 0/360 degree angle.

 \note If the angular distance between two consecutive points in a series is more than 180 degrees,
 any line connecting the two points becomes meaningless, so choose the axis ranges accordingly
 when displaying line, spline, or area series.

 \note Polar charts do not support multiple axes of same orientation.

 \sa QChart
 */

/*!
 Constructs a polar chart as a child of a \a parent.
 Parameter \a wFlags is passed to the QChart constructor.
 */
QPolarChart::QPolarChart(QGraphicsItem *parent, Qt::WindowFlags wFlags)
    : QChart(QChart::ChartTypePolar, parent, wFlags)
{
}

/*!
 Destroys the object and it's children, like series and axis objects added to it.
 */
QPolarChart::~QPolarChart()
{
}

/*!
 Returns the axes added for the \a series with \a polarOrientation. If no series is provided, then any axis with the
 specified polar orientation is returned.
 \sa addAxis()
 */
QList<QAbstractAxis *> QPolarChart::axes(PolarOrientations polarOrientation, QAbstractSeries *series) const
{
    Qt::Orientations orientation(0);
    if (polarOrientation.testFlag(PolarOrientationAngular))
        orientation |= Qt::Horizontal;
    if (polarOrientation.testFlag(PolarOrientationRadial))
        orientation |= Qt::Vertical;

    return QChart::axes(orientation, series);
}

/*!
  This convenience method adds \a axis to the polar chart with \a polarOrientation.
  The chart takes the ownership of the axis.

  \note Axes can be added to a polar chart also with QChart::addAxis() instead of this method.
  The specified alignment determines the polar orientation: horizontal alignments indicate angular
  axis and vertical alignments indicate radial axis.
  \sa QChart::removeAxis(), QChart::createDefaultAxes(), QAbstractSeries::attachAxis(), QChart::addAxis()
*/
void QPolarChart::addAxis(QAbstractAxis *axis, PolarOrientation polarOrientation)
{
    if (!axis || axis->type() == QAbstractAxis::AxisTypeBarCategory) {
        qWarning("QAbstractAxis::AxisTypeBarCategory is not a supported axis type for polar charts.");
    } else {
        Qt::Alignment alignment = Qt::AlignLeft;
        if (polarOrientation == PolarOrientationAngular)
            alignment = Qt::AlignBottom;
        QChart::addAxis(axis, alignment);
    }
}

/*!
  Angular axes of a polar chart report horizontal orientation and radial axes report
  vertical orientation.
  This function is a convenience function for converting the orientation of an \a axis to
  corresponding polar orientation. If the \a axis is NULL or not added to a polar chart,
  the return value is meaningless.
*/
QPolarChart::PolarOrientation QPolarChart::axisPolarOrientation(QAbstractAxis *axis)
{
    if (axis && axis->orientation() == Qt::Horizontal)
        return PolarOrientationAngular;
    else
        return PolarOrientationRadial;
}

#include "moc_qpolarchart.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
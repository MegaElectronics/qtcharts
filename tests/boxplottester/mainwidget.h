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

#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "qchartglobal.h"
#include "qchart.h"
#include "qchartview.h"
#include <QWidget>
#include <QBoxPlotSeries>

class QGridLayout;

QTCOMMERCIALCHART_USE_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = 0);

signals:

private:
    void initThemeCombo(QGridLayout *grid);
    void initCheckboxes(QGridLayout *grid);

private slots:
    void addSeries();
    void removeSeries();
    void addBox();
    void animationToggled(bool enabled);
    void legendToggled(bool enabled);
    void titleToggled(bool enabled);
    void changeChartTheme(int themeIndex);

private:
    QChart *m_chart;
    QChartView *m_chartView;
    QGridLayout *m_scatterLayout;
    int rowPos;
    int nSeries;
    QBoxPlotSeries *m_series[10];
};

#endif // MAINWIDGET_H
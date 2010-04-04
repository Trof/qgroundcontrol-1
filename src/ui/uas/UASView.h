/*=====================================================================

PIXHAWK Micro Air Vehicle Flying Robotics Toolkit

(c) 2009 PIXHAWK PROJECT  <http://pixhawk.ethz.ch>

This file is part of the PIXHAWK project

    PIXHAWK is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    PIXHAWK is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with PIXHAWK. If not, see <http://www.gnu.org/licenses/>.

======================================================================*/

/**
 * @file
 *   @brief Definition of one airstrip
 *
 *   @author Lorenz Meier <mavteam@student.ethz.ch>
 *
 */

#ifndef UASVIEW_H
#define UASVIEW_H

#include <QtGui/QWidget>
#include <QString>
#include <QTimer>
#include <QMouseEvent>
#include <UASInterface.h>

namespace Ui {
    class UASView;
}

class UASView : public QWidget {
    Q_OBJECT
public:
    UASView(UASInterface* uas, QWidget *parent = 0);
    ~UASView();

public slots:
    void receiveHeartbeat(UASInterface* uas);
    void updateThrust(UASInterface* uas, double thrust);
    void updateBattery(UASInterface* uas, double voltage, double percent, int seconds);
    void updateLocalPosition(UASInterface*, double x, double y, double z, quint64 usec);
    void updateGlobalPosition(UASInterface*, double lon, double lat, double alt, quint64 usec);
    void updateSpeed(UASInterface*, double x, double y, double z, quint64 usec);
    void updateState(UASInterface*, QString uasState, QString stateDescription);
    /** @brief Update the MAV mode */
    void updateMode(int sysId, QString status, QString description);
    void updateLoad(UASInterface* uas, double load);
    void receiveValue(int uasid, QString id, double value, quint64 time);
    void refresh();
    /** @brief Receive new waypoint information */
    void setWaypoint(int uasId, int id, double x, double y, double z, double yaw, bool autocontinue, bool current);
    /** @brief Set waypoint as current target */
    void selectWaypoint(int uasId, int id);
    /** @brief Set the current system type */
    void setSystemType(UASInterface* uas, unsigned int systemType);

protected:
    void changeEvent(QEvent *e);
    QTimer* refreshTimer;
    QColor heartbeatColor;
    quint64 startTime;
    int timeRemaining;
    double chargeLevel;
    UASInterface* uas;
    double load;
    QString state;
    QString stateDesc;
    QString mode;
    double thrust;

    void mouseDoubleClickEvent (QMouseEvent * event);
    /** @brief Mouse enters the widget */
    void enterEvent(QEvent* event);
    /** @brief Mouse leaves the widget */
    void leaveEvent(QEvent* event);

private:
    Ui::UASView *m_ui;

signals:
    void uasInFocus(UASInterface* uas);
    void uasOutFocus(UASInterface* uas);
};

#endif // UASVIEW_H
#ifndef SUBJECT_H
#define SUBJECT_H

#include <QMainWindow>
#include <QTime>
#include <iostream>

class Subject
{
private:
    QString name;
    QString location;
    QTime startTime;
    QTime endTime;

    bool mon;
    bool tue;
    bool wed;
    bool thu;
    bool fri;

public:
    Subject();
    Subject(const QString &name, const QString &location, const QTime &startTime,
            const QTime &endTime, bool mon, bool tue, bool wed, bool thu, bool fri);

    QString getName() const { return name; }
    QString getLocation() const { return location; }
    QTime getStartTime() const { return startTime; }
    QTime getEndTime() const { return endTime; }

    bool getMon() const { return mon; }
    bool getTue() const { return tue; }
    bool getWed() const { return wed; }
    bool getThu() const { return thu; }
    bool getFri() const { return fri; }

    void setName(const QString& name) { this->name = name; }
    void setLocation(const QString& location) { this->location = location; }
    void setStartTime(const QTime& startTime) { this->startTime = startTime; }
    void setEndTime(const QTime& endTime) { this->endTime = endTime; }

    void setMon(bool mon) { this->mon = mon; };
    void setTue(bool tue) { this->tue = tue; };
    void setWed(bool wed) { this->wed = wed; };
    void setThu(bool thu) { this->thu = thu; };
    void setFri(bool fri) { this->fri = fri; };
};

#endif // SUBJECT_H

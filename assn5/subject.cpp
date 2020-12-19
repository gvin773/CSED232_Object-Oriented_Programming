#include "subject.h"

Subject::Subject()
{

}

Subject::Subject(const QString &name, const QString &location, const QTime &startTime,
        const QTime &endTime, bool mon, bool tue, bool wed, bool thu, bool fri)
    : name(name), location(location), startTime(startTime), endTime(endTime),
      mon(mon), tue(tue), wed(wed), thu(thu), fri(fri)
{

}

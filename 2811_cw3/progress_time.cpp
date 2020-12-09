#include "progress_time.h"

using namespace std;

void ProgressTime::SetDurationTime(qint64 duration)
{
    _duration = int(duration / 1000);
    char t[1024] = {0};     //storge time
    int min = (_duration) / 60;
    int sec = (_duration) % 60;

    if (min > 999)
    {
        sprintf(t, "%04d:%02d", min, sec);
    }
    else if (min > 99)
    {
        sprintf(t, "%03d:%02d", min, sec);
    }
    else
    {
        sprintf(t, "%02d:%02d", min, sec);
    }

    setText(t);
}

void ProgressTime::SetCurrentTime(qint64 current)
{
    _current = int(current / 1000);
    char t[1024] = {0};     //storge time
    int min = (_current) / 60;
    int sec = (_current) % 60;

    if (min > 999)
    {
        sprintf(t, "%04d:%02d", min, sec);
    }
    else if (min > 99)
    {
        sprintf(t, "%03d:%02d", min, sec);
    }
    else
    {
        sprintf(t, "%02d:%02d", min, sec);
    }

    setText(t);
}

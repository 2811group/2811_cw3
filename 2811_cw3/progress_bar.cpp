#include "progress_bar.h"

void ProgressBar::SetDuration(qint64 duration)
{
    setRange(0, int(duration));
}

void ProgressBar::SetPosition(qint64 postion)
{
    setValue(int(postion));
}


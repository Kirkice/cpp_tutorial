#include <iostream>
#include "log.h"

int main() {
    Log mlog;
    mlog.Init();
    mlog.Debug("Log!Log!Log!Log!Log!Log!Log!Log!Log!Log!Log!Log!");
    mlog.DebugWarn("Warn!Warn!Warn!Warn!Warn!Warn!Warn!Warn!Warn!");
    mlog.DebugError("Error!Error!Error!Error!Error!Error!Error!Error!");
    return 0;
}

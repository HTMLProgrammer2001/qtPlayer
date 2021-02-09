#include "globals.h"

QString Globals::dbName = "audio.db";
QString Globals::user = "test";
QString Globals::passwd = "12345678";

QEvent::Type Globals::eventType = static_cast<QEvent::Type>(QEvent::User + 1);

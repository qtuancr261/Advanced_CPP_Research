#include "fonefomular.h"

FOneFomular::FOneFomular()
{
    setGoStrategy(new GoByDriveStrategy{});
}

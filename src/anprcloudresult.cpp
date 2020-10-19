#include "anprcloudresult.h"

using namespace anprcloud;

ANPRCloudResult::ANPRCloudResult()
{

}

bool ANPRCloudResult::hasVehicle()
{
    return m_vehicles.size()>0;
}

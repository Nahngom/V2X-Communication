#include "veins_inet/VeinsInetRSUApplication.h"

#include "inet/common/ModuleAccess.h"
#include "inet/common/packet/Packet.h"
#include "inet/common/TagBase_m.h"
#include "inet/common/TimeTag_m.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/networklayer/common/L3AddressTag_m.h"
#include "inet/transportlayer/contract/udp/UdpControlInfo_m.h"

#include "veins_inet/VeinsInetSampleMessage_m.h"
#include "veins_inet/VeinsInetRSUApplication.h"

using namespace inet;

Define_Module(VeinsInetRSUApplication);

VeinsInetRSUApplication::VeinsInetRSUApplication()
{
}


bool VeinsInetRSUApplication::startApplication() {

    return true;
}

bool VeinsInetRSUApplication::stopApplication() {
    return true;
}

void VeinsInetRSUApplication::processPacket(std::shared_ptr<inet::Packet> pk) {
    throw cRuntimeError("processPacket called 0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");

    EV_INFO << "RSU received a packet: ---------------------------------RSU" << pk->getName() << endl;

}
void VeinsInetRSUApplication::handleStartOperation(inet::LifecycleOperation* operation) {
    // Startup behavior for the RSU (can be empty)
}

void VeinsInetRSUApplication::handleStopOperation(inet::LifecycleOperation* operation) {
    // Cleanup or shutdown logic (optional)
}

void VeinsInetRSUApplication::handleCrashOperation(inet::LifecycleOperation* operation) {
    // Crash handling logic (optional)
}
VeinsInetRSUApplication::~VeinsInetRSUApplication() {
    // Cleanup code if needed (or leave empty)
}

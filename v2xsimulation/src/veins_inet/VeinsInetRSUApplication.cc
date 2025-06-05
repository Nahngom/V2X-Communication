#include "veins_inet/VeinsInetRSUApplication.h"

#include "inet/common/ModuleAccess.h"
#include "inet/common/packet/Packet.h"
#include "inet/common/TagBase_m.h"
#include "inet/common/TimeTag_m.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/networklayer/common/L3AddressTag_m.h"
#include "inet/transportlayer/contract/udp/UdpControlInfo_m.h"

#include "veins_inet/VeinsInetSampleMessage_m.h"

using namespace inet;
Define_Module(VeinsInetRSUApplication);

VeinsInetRSUApplication::VeinsInetRSUApplication()
{
}


bool VeinsInetRSUApplication::startApplication() {
    EV_INFO << "RSU application started on " << getParentModule()->getFullName() << endl;
    return true;
}

bool VeinsInetRSUApplication::stopApplication() {
    return true;
}

void VeinsInetRSUApplication::processPacket(std::shared_ptr<inet::Packet> pk) {
    EV_INFO << "RSU received a packet: " << pk->getName() << endl;

    auto payload = pk->peekData<VeinsInetSampleMessage>();

    auto packet = createPacket("rsu_relay");
    packet->insertAtBack(payload);
    sendPacket(std::move(packet));
}


#include "veins_inet/VeinsInetRSUApplicationBase.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/packet/Packet.h"
#include "inet/common/TagBase_m.h"
#include "inet/common/TimeTag_m.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/networklayer/common/L3AddressTag_m.h"
#include "inet/transportlayer/contract/udp/UdpControlInfo_m.h"
#include "inet/common/lifecycle/ModuleOperations.h"
#include "inet/common/packet/chunk/ByteCountChunk.h"
namespace veins {

using namespace inet;

Define_Module(VeinsInetRSUApplicationBase);

VeinsInetRSUApplicationBase::VeinsInetRSUApplicationBase()
{
}
bool VeinsInetRSUApplicationBase::startApplication()
{
    return true;
}

bool VeinsInetRSUApplicationBase::stopApplication()
{
    return true;
}
int VeinsInetRSUApplicationBase::numInitStages() const
{
    return inet::NUM_INIT_STAGES;
}
void VeinsInetRSUApplicationBase::processPacket(std::shared_ptr<inet::Packet> pk) {
    EV_INFO << "RSU received packet, forwarding to vehicles...\n";

        auto packetName = "accidentForward";
        auto payload = makeShared<ByteCountChunk>(B(100));  // create dummy payload
        auto forwardPk = new Packet(packetName);
        forwardPk->insertAtBack(payload);

        // Set destination as multicast to reach all vehicles
        inet::L3Address destAddr = inet::L3AddressResolver().resolve("224.0.0.1");

        socket.sendTo(forwardPk, destAddr, 1234);  // port should match vehicle receiver
}

void VeinsInetRSUApplicationBase::initialize(int stage)
{
    ApplicationBase::initialize(stage);

    if (stage == INITSTAGE_LOCAL) {
    }
}
void VeinsInetRSUApplicationBase::handleMessageWhenUp(cMessage* msg) {
    if (msg->isSelfMessage()) {
        // handle timers here if needed
    } else if (auto pk = dynamic_cast<inet::Packet*>(msg)) {
        emit(packetReceivedSignal, pk);
        processPacket(std::shared_ptr<inet::Packet>(pk));  // call child logic
    } else {
        delete msg;  // unexpected
    }
}

void VeinsInetRSUApplicationBase::finish() {
    ApplicationBase::finish();
}

void VeinsInetRSUApplicationBase::handleStartOperation(LifecycleOperation* operation) {
    //throw cRuntimeError("processPacket called 0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    // Resolve multicast group address (e.g., for V2X)
        L3AddressResolver().tryResolve("224.0.0.1", destAddress);
        ASSERT(!destAddress.isUnspecified());

        // Set output gate (required even if not sending)
        socket.setOutputGate(gate("socketOut"));

        // Bind to local UDP port to listen

        //if(check) throw cRuntimeError("processPacket called 0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
        // Join multicast group on specified interface
        const char* interface = par("interface");
        IInterfaceTable* ift = getModuleFromPar<IInterfaceTable>(par("interfaceTableModule"), this);

    #if INET_VERSION >= 0x0402
        InterfaceEntry* ie = ift->findInterfaceByName(interface);
    #else
        InterfaceEntry* ie = ift->getInterfaceByName(interface);
    #endif
        ASSERT(ie);

        socket.setMulticastOutputInterface(ie->getInterfaceId());  // still needed for group subscription

        MulticastGroupList mgl = ift->collectMulticastGroups();
        socket.joinLocalMulticastGroups(mgl);  // subscribe to all configured multicast groups

        // Set this module to handle incoming messages
        socket.setCallback(this);
        socket.bind(par("localPort"));
        // Do NOT call sendTo() anywhere => receive-only mode


        EV_INFO << "RSU binding to port: " << par("localPort").intValue() << "\n";
        EV_INFO << "RSU joining multicast group: " << destAddress << " on interface: " << interface << "\n";

}
void VeinsInetRSUApplicationBase::socketDataArrived(UdpSocket* socket, Packet* packet) {
    //throw cRuntimeError("processPacket called 0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    processPacket(std::shared_ptr<inet::Packet>(packet));
}

void VeinsInetRSUApplicationBase::handleStopOperation(LifecycleOperation* operation) {
    // Optional shutdown logic
}

void VeinsInetRSUApplicationBase::handleCrashOperation(LifecycleOperation* operation) {
    // Optional crash logic
}
void VeinsInetRSUApplicationBase::socketErrorArrived(UdpSocket* socket, Indication* indication) {

    EV_WARN << "UDP socket error received: " << indication->getName() << endl;
    delete indication;  // clean up
}

void VeinsInetRSUApplicationBase::socketClosed(UdpSocket* socket) {

    EV_WARN << "UDP socket closed" << endl;
}

VeinsInetRSUApplicationBase::~VeinsInetRSUApplicationBase() {} // Destructor
} // namespace veins

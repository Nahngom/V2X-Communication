//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 
//
//#ifndef VEINS_INET_VEINSINETRSUAPPLICATIONBASE_H_
//#define VEINS_INET_VEINSINETRSUAPPLICATIONBASE_H_
//
//class VeinsInetRSUApplicationBase {
//};
//
//#endif /* VEINS_INET_VEINSINETRSUAPPLICATIONBASE_H_ */
//#ifndef VEINS_INET_VEINSINETRSUAPPLICATIONBASE_H_
//#define VEINS_INET_VEINSINETRSUAPPLICATIONBASE_H_
#pragma once

#include "veins_inet/veins_inet.h"
#include "inet/common/INETDefs.h"
#include "inet/applications/base/ApplicationBase.h"
#include "inet/common/packet/Packet.h"
#include "veins/modules/utility/TimerManager.h"
#include "inet/transportlayer/contract/udp/UdpSocket.h"
namespace veins {

class VEINS_INET_API VeinsInetRSUApplicationBase : public inet::ApplicationBase, public inet::UdpSocket::ICallback {
protected:
    inet::UdpSocket socket;  // Add this line
    inet::L3Address destAddress;
  protected:
    //inet::UdpSocket socket;
    const int portNumber = 9001;
  public:
      virtual void handleStartOperation(inet::LifecycleOperation* operation) override;
      virtual void handleStopOperation(inet::LifecycleOperation* operation) override;
      virtual void handleCrashOperation(inet::LifecycleOperation* operation) override;
  protected:
    // OMNeT++ signals
    simsignal_t packetReceivedSignal = registerSignal("packetReceived");

    // Required: called when the module starts
    virtual void initialize(int stage) override;
    virtual int numInitStages() const override;

    // Required: main packet handling logic (to be implemented in derived class)
    virtual void processPacket(std::shared_ptr<inet::Packet> pk);

    // Optional: override if needed
    virtual void handleMessageWhenUp(cMessage *msg) override;

    // Optional: when module shuts down
    virtual void finish() override;
    ///


    virtual void socketDataArrived(inet::UdpSocket* socket, inet::Packet* packet) override;

    virtual void socketErrorArrived(inet::UdpSocket* socket, inet::Indication* indication) override;
    virtual void socketClosed(inet::UdpSocket* socket) override;


    ///
    // Default application startup/shutdown hooks
    virtual bool startApplication();
    virtual bool stopApplication();
  public:
      VeinsInetRSUApplicationBase();
      virtual ~VeinsInetRSUApplicationBase();
};

} // namespace veins

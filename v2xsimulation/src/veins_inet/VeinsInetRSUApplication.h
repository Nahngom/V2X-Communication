#pragma once
#include "veins_inet/veins_inet.h"
#include "veins_inet/VeinsInetApplicationBase.h"  // You need this!


class VEINS_INET_API VeinsInetRSUApplication : public veins::VeinsInetApplicationBase {
  protected:
    virtual bool startApplication() override;
    virtual void processPacket(std::shared_ptr<inet::Packet> pk) override;
    virtual bool stopApplication() override;
  public:
      VeinsInetRSUApplication();
      virtual ~VeinsInetRSUApplication() = default;
};

//#ifndef VEINS_INET_VEINSINETRSUAPPLICATION_H_
//#define VEINS_INET_VEINSINETRSUAPPLICATION_H_
#pragma once
#include "veins_inet/veins_inet.h"
#include "veins_inet/VeinsInetRSUApplicationBase.h"  // You need this!


class VEINS_INET_API VeinsInetRSUApplication : public veins::VeinsInetRSUApplicationBase {
  protected:
    virtual bool startApplication();
    virtual void processPacket(std::shared_ptr<inet::Packet> pk) override;
    virtual bool stopApplication();

  public:
      virtual void handleStartOperation(inet::LifecycleOperation* operation) override;
      virtual void handleStopOperation(inet::LifecycleOperation* operation) override;
      virtual void handleCrashOperation(inet::LifecycleOperation* operation) override;

  public:
      VeinsInetRSUApplication();
      virtual ~VeinsInetRSUApplication();
};

package v2xsimulation.veins_inet;

import v2xsimulation.veins_inet.VeinsInetApplicationBase;
//
// RSU application that processes incoming messages and relays them.
//
simple VeinsInetRSUApplication extends VeinsInetApplicationBase
{
    parameters:
        string inter; // e.g. "wlan0"
        @display("i=block/app");
        @class(VeinsInetRSUApplication);
}

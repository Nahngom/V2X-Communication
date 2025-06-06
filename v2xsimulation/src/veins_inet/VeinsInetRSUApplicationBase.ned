package v2xsimulation.veins_inet;

import inet.applications.contract.IApp;

simple VeinsInetRSUApplicationBase like IApp
{
    parameters:
        int localPort;
        string interfaceTableModule;   // To access NIC interfaces
        string interface = default("wlan0");  // NIC name used for communication

        @display("i=block/app");
        @class(veins::VeinsInetRSUApplicationBase);  // C++ class

        @signal[packetReceived](type=inet::Packet);  // Only receiving
        @statistic[packetReceived](title="packets received";
                                    source=packetReceived;
                                    record=count, "sum(packetBytes)", "vector(packetBytes)";
                                    interpolationmode=none);
    gates:
        input socketIn @labels(UdpControlInfo/up);
        output socketOut @labels(UdpControlInfo/down);
}

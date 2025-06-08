package v2xsimulation.veins_inet;

import inet.node.inet.AdhocHost;
import inet.mobility.static.StationaryMobility;
import inet.networklayer.configurator.ipv4.HostAutoConfigurator;


//
// Stationary RSU that talks to vehicles using 802.11p
//
module VeinsInetRSU extends AdhocHost
{
    parameters:
        @display("i=block/tower");
        mobility.typename = "StationaryMobility";  // RSU doesn't move
}


package v2xsimulation.simulations.veins_inet;

import inet.physicallayer.ieee80211.packetlevel.Ieee80211DimensionalRadioMedium;
import v2xsimulation.veins_inet.VeinsInetCar;
import v2xsimulation.veins_inet.VeinsInetManager;
import inet.visualizer.integrated.IntegratedVisualizer;
import inet.environment.common.PhysicalEnvironment;
import org.car2x.veins.visualizer.roads.RoadsCanvasVisualizer;
import org.car2x.veins.visualizer.roads.RoadsOsgVisualizer;
import v2xsimulation.veins_inet.VeinsInetRSU;
network Scenario
{
    @display("bgb=319,384");
    submodules:
        radioMedium: Ieee80211DimensionalRadioMedium {
            @display("p=64,224");
        }
        manager: VeinsInetManager {
            @display("p=192,320");
        }
        visualizer: IntegratedVisualizer {
            @display("p=64,320");
        }
        physicalEnvironment: PhysicalEnvironment {
            @display("p=192,224");
        }
        roadsCanvasVisualizer: RoadsCanvasVisualizer {
            @display("p=64,416");
        }
        roadsOsgVisualizer: RoadsOsgVisualizer {
            @display("p=192,416");
        }
        node[0]: VeinsInetCar;
        
        rsu1: VeinsInetRSU {
          @display("p=290,515");
    }
    rsu2: VeinsInetRSU {
        @display("p=140,900");
    }
        
}

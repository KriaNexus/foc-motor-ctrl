<table class="sphinxhide">
 <tr>
   <td align="center"><img src="../../media/xilinx-logo.png" width="30%"/><h1> Kria&trade; KD240 Drives Starter Kit <br>FOC Motor Control Application Tutorial</h1>
   </td>
 </tr>
 <tr>
 <td align="center"><h1>Known Issues and Debug Help</h1>

 </td>
 </tr>
</table>

# Known Issues and Limitations

* QEI reported speed is showing glitches. The QEI library computation of the speed has a known issue and will be addressed with a QEI library update.
* Motor lower speed mode control capability is approximately 250 rpms.
* Default motor tuning values are provided for the KD240 Motor Accessory Kit based the Anaheim motor with the plastic disk visual load. This load disk primarily acts as an inertial load and thus if you are connecting other loads to your motor, you should plan on conducting your own tuning process and defining custom tuning defaults based on your load testing.
* Open-loop control mode is intended as a test mode and thus does not implement any software based ramp control. You will see fault protections triggered if immediately trying to set open-loop mode control with a Vq voltage > ~10V. If using an open-loop, you are responsible for incrementally stepping up the Vq command to your desired voltage setting. Typical use cases of open-loop mode have Vd set to 0V.
* DC link current reading is limited to reading analog values > ~0.5A due to a limitation in the KD240 hardware. You should not assume the DC link current feedback is accurate until it is > ~0.5A.
* If the bokeh server is stopped while the motor is running, the motor will not stop. The motor should be stopped through the GUI by switching to Off mode before stopping the bokeh server.

# Debugging Motor Control Application

If the motor control application is not functioning as intended, follow these debugging steps to diagnose and resolve issues.

1. **Check Wire Connections**
    * Ensure that wire connections matches the configuration shown in the application deployment page.
    * Verify that the 24V DC supply is connected and the wall power is up.
    * Check DS9 LED, which represents the DC link; it should be in a high state.
    * Confirm that the Quadrature Encoder Interface (QEI) encoder from the motor is properly connected to the board.

2. **Read DC Link Voltage**
    * If the application repeatedly fails to start with system faults, measure the DC link voltage by reading data from the ADC interface (ADC-HUB voltage channel 6).
    * Use the command `iio_attr -c xilinx_adc_hub voltage6` to check the voltage reading and should read around 24V.

      ```bash
      iio_attr -c xilinx_adc_hub voltage6
      dev 'xilinx_adc_hub', channel 'voltage6' (input), attr 'input', value '25.116806030'
      ```

        A reading significantly lower or higher than the tolerance range of the power supply could indicate a hardware failure on the board.

3. **Debug PL Interfaces**
   * If unexpected behavior occurs, start probing different blocks of the programmable logic (PL) interfaces for debugging.
   * Utilize the IIO utilities or the IIO driver sysfs for the specific hardware interface.
   * For detailed information on debugging hardware interfaces, refer to the [Device and  Channel Attributes](./sw_arch.md#device-and-channel-attributes) section.

4. **Gate Drive Mode**
   * Ensure that the software application is set to a valid mode that turns the Gate Drive ON, except for the off mode.
   * Monitor DS10 LED: it should go high in modes other than off.

5. **Observe Errors and Messages from the Application**
   * Keep an eye on the serial console for error messages or other relevant information.
   * Review the `dmesg` logs, which provide valuable information from the respective hardware drivers. These logs can be a helpful source of diagnostic information.

6. **Network Connection**
   * If the application does not respond to changes from the GUI, verify the network connection by pinging the host address.
   * Sometimes, a web socket disconnection message may appear, indicating a communication issue. If you encounter such disconnection issues, try killing the Bokeh server and relaunching the server and the dashboard.

   Sample Disconnection Message:

   ```bash
   2023-09-13 18:47:32,361 WebSocket connection closed: code=None, reason=None
   ``````

# CAN Bus Issue

When experiencing intermittent communication issues during experiments with the KD240-KR260 board setup for ROS2 CANopen application, the motor may not respond to control commands. In such cases, use the commands below to reset the CAN interface on the KR260 board, then rerun the control commands. Also, ensure that all cables are of good quality and securely connected, as poor connections can lead to communication issues. If you are using a Pmod CAN connector, consider swapping it with a different Pmod connector if problems persist. 

Additionally, if the CANopen setup is left running for an extended period, the TX queue of the CAN interface might fill-up resulting in the interface hang, especially on the KR260 board.
There are no indications for this situation other than the KR260 and KD240 not receiving CAN messages. 

To resolve this issue, reset the Pmod CAN interface using the following commands on KR260 board:

```bash
sudo ip link set can0 down
sudo ip link set can0 up
```
If this issue occurs frequently, consider increasing the TX queue length on KR260 with `sudo ip link set can0 txqueuelen 20000`.

# System Crash During Application Reload

There is a known issue of system crash during the reload of the kd240-motor-ctrl-qei application. While the initial load and unload process works correctly, subsequent attempts to load the application result in a system crash. To prevent this, it is recommended to remove all the HLS modules before unloading the application firmware. This ensures that the next reload of the application does not cause a crash.

To remove the HLS modules before unloading the firmware, use the following commands:

```bash
sudo rmmod $(lsmod | grep hls_ | awk '{print $1}') # Unloads all HLS modules
sudo lsmod # Verify that HLS modules have been removed
```
> **Note**: Ensure that the HLS modules are not in use before executing the `xmutil unload` command.

<!---

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License.

You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0.

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License.

-->

<p class="sphinxhide" align="center">Copyright&copy; 2023 Advanced Micro Devices, Inc</p>

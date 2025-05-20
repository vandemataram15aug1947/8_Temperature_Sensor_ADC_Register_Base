# 🌡️ 8_Temperature_Sensor_ADC_Register_Base

This project demonstrates how to interface an **analog temperature sensor** with the **TMS320F28379D microcontroller** using **ADC register-level programming** (without driverlib or API functions). The goal is to understand the direct register configurations required to read analog values, convert them via the ADC, and process temperature data from a sensor such as **LM35**, **TMP36**, or any other linear-output analog sensor.

---

## 📘 Overview

This lab focuses on:

- Initializing the ADC module using register-level access (no high-level APIs)
- Sampling analog temperature sensor values connected to an ADC pin (e.g., `ADCINA0`)
- Converting raw ADC values to temperature (in °C)
- Viewing results through breakpoints, watch window, or DAC/serial interface

This project is intended for embedded systems learners working with **bare-metal control** on **TI’s F2837xD** series DSPs.

---

## 🛠️ Tools Used

- **Code Composer Studio (CCS)** – for code development and debugging
- **TMS320F28379D** – Texas Instruments C2000 Delfino microcontroller
- **Temperature Sensor** – LM35 / TMP36 / or similar analog output sensor
- **Oscilloscope / Debug Probe** – for observing signal and output
- **Digital Multimeter (DMM)** *(optional)* – to verify sensor voltage

---

## 🔧 Project Features

- ✅ **Direct register-based ADC initialization**  
- ✅ **Polling-based ADC result acquisition**  
- ✅ **Simple formula for voltage-to-temperature conversion**  
- ✅ **Can be extended to ISR-based acquisition or real-time control**

---

## 📁 Folder Structure

```
8_Temperature_Sensor_ADC_Register_Base/
├── device/ # Device support files
├── targetConfigs/ # Target configuration files
├── CPU1_RAM/ # RAM build configuration
├── .cproject / .project # Eclipse project descriptor files
├── 2837xD_RAM_lnk_cpu1.cmd # Linker command file for RAM
├── F2837xD_CodeStartBranch.asm # Entry point for code
├── F2837xD_usDelay.asm # Delay function using cycle count
├── F2837xD_GlobalVariableDefs.c # Global peripheral variables
├── F2837xD_DefaultISR.c # Default ISR definitions
├── F2837xD_PieCtrl.c # PIE interrupt controller setup
├── F2837xD_PieVect.c # PIE vector table setup
├── F2837xD_SysCtrl.c # System clock & PLL configuration
├── F2837xD_Gpio.c # GPIO setup (if needed for indicator)
├── ADC_Temperature.c # 🔥 Main logic: ADC register config and temperature calc
└── README.md # 📄 Project documentation (this file)
```


---

## 🧠 Register-Level ADC Setup

The ADC is configured by writing directly to the following registers:

- `AdcaRegs.ADCCTL1` – Enable ADC, clock settings
- `AdcaRegs.ADCCTL2` – Clock prescaler, resolution, mode
- `AdcaRegs.ADCSOCxCTL` – SOC trigger source and channel select
- `AdcaRegs.ADCINTSELxNSEL` – Interrupt source setup
- `AdcaRegs.ADCSOCFRC1` – Software trigger to force conversion
- `AdcaResultRegs.ADCRESULTx` – Holds the conversion result

---

## 📏 Sensor Calculation Example

For a typical LM35 sensor:

- Output: **10 mV/°C**
- ADC full scale: **3.0V (assuming)**, 12-bit resolution = 4096 steps
- Voltage per step = 3.0 / 4096 = 0.000732V (0.732 mV)
- Temperature (°C) = `ADC_Result * 0.732 / 10`

**Simplified Formula:**

```c
Temperature_C = (float)ADC_Result * 0.0732;
```

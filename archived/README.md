# Archived projects

Full project history via git subtree.

## 2024-2025 Project - Not Rocket Science

| Folder | Source repo | What it is |
|---|---|---|
| fc-firmware | NRS-FC | STM32F4 SRAD flight computer. Reached board bring-up only. |
| ham | HAM | STM32 HAL wrapper used by NRS-FC. Not platform-independent. |
| pdu-report | NRS-PDU | Power distribution unit report (LaTeX). |
| ground-station | NRS-Groundstation | Stub. |
| fc-verification | NRS-Flight-Computer-Verification | Verification/test examples. |
| wiring | nrs-wiring | drawio wiring diagrams and generated HTML guide. |

## 2025-2026 Project - Ratatoskr

| Folder | Source repo | What it is |
|---|---|---|
| fc-notta | Ratatoskr-FC-Notta | Teensy 4.1 + FreeRTOS SRAD flight computer. Task architecture, filters, mocks and tests. State machine never implemented. |
| cats-vega-configs | Ratatoskr-CATS-Vega-configurations | The COTS flight computer configurations that actually flew. |
| gs-adapter-firmware | Ratatoskr-GS-adapter-firmware | 2.4 GHz SX1280 USB-LoRa bridge with FEM and thermal throttling. |
| gs-nidhoggr | Ratatoskr-GS-Nidhoggr | Qt/QML ground station application with MAVLink emulator, flight state view and CSV logging. |
| proto | mavlink (fork) | Horizon MAVLink dialect: ROCKET_STATE_TYPE, FLIGHT_STATES, PAYLOAD_TEMPERATURE, COSMIC_RADIATION. |
| teensy-prototype-lab | teensy-flight-computer-prototype-LAB | Early Teensy prototype. README only. |

# Elephant Anklet Monitoring Device

## Project Description
The Elephant Anklet Monitoring Device is designed to track the 9-axis motion of elephants, implementing both gyro and compass data. The device stores the collected data on an SD card, allowing for detailed analysis of the movement patterns.

## Features
- Tracks 9-axis motion (accelerometer, gyroscope, and magnetometer)
- Implements gyro and compass data
- Stores data on an SD card for easy access and analysis
- Autonomous operation after initial setup

## Installation Instructions

### Prerequisites
- STM32CubeIDE
- STM32 development board
- USB cable for connecting the development board to your computer

### Step-by-Step Installation

1. **Download and Install STM32CubeIDE**:
   - Visit the [STM32CubeIDE download page](https://www.st.com/en/development-tools/stm32cubeide.html).
   - Download the installer suitable for your operating system (Windows, macOS, Linux).
   - Run the installer and follow the on-screen instructions to complete the installation.

2. **Clone the Project Repository**:
   - Open your terminal or command prompt.
   - Clone the project repository using the following command:
     ```sh
     git clone https://github.com/yourusername/Elephant-Anklet-Monitoring-Device.git
     ```

3. **Open the Project in STM32CubeIDE**:
   - Launch STM32CubeIDE.
   - Select `File` > `Open Projects from File System...`.
   - Navigate to the cloned project directory and select it to import the project.

4. **Build the Project**:
   - In STM32CubeIDE, navigate to the `Project Explorer` view.
   - Right-click on the project and select `Build Project`.
   - Ensure there are no build errors before proceeding.

5. **Flash the Code to the Development Board**:
   - Connect your STM32 development board to your computer via USB.
   - In STM32CubeIDE, click on the `Run` menu and select `Debug As` > `STM32 Cortex-M C/C++ Application`.
   - Follow the prompts to flash the code onto the development board.
   - Once flashing is complete, press the reset button on the development board to start the program.

## Usage

1. **Connect the Device**:
   - Plug the development board into a power source via USB.
   
2. **Operate the Device**:
   - After flashing the code and pressing the reset button, the device will operate autonomously, collecting and storing data on the SD card.

## Contributing
We welcome contributions to the Elephant Anklet Monitoring Device project. To contribute:

1. Fork the repository.
2. Create a new branch (`git checkout -b feature/YourFeature`).
3. Commit your changes (`git commit -am 'Add new feature'`).
4. Push to the branch (`git push origin feature/YourFeature`).
5. Open a pull request.

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Contact
For further inquiries or support, please contact us at [email@example.com](mailto:email@example.com).


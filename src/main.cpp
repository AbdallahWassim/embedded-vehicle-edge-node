#include <iostream>
#include <thread>
#include <chrono>
#include "ThreadSafeQueue.hpp"

// Création d'une queue partagée pour stocker des entiers (ex: Vitesse véhicule)
ThreadSafeQueue<int> vehicleDataQueue;

void vCanRxTask() {
    int simulatedSpeed = 0;
    while (true) {
        simulatedSpeed += 5;
        if (simulatedSpeed > 150) simulatedSpeed = 0;

        std::cout << "[CAN RX] Sending speed: " << simulatedSpeed << " km/h" << std::endl;
        vehicleDataQueue.push(simulatedSpeed);

        std::this_thread::sleep_for(std::chrono::milliseconds(800));
    }
}

void vProcessingTask() {
    int receivedSpeed = 0;
    while (true) {
        // Cette ligne bloque jusqu'à ce que la Queue reçoive quelque chose
        if (vehicleDataQueue.pop(receivedSpeed)) {
            std::cout << "[PROCESSING] Analyzing speed: " << receivedSpeed << " km/h - Status: ";
            if (receivedSpeed > 120) std::cout << "CRITICAL (Overspeed!)" << std::endl;
            else std::cout << "OK" << std::endl;
        }
    }
}

int main() {
    std::cout << "[SYSTEM] Booting Embedded Edge Node with ThreadSafe Communication..." << std::endl;

    std::thread canTask(vCanRxTask);
    std::thread procTask(vProcessingTask);

    canTask.join();
    procTask.join();

    return 0;
}
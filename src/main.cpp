#include <iostream>
#include <thread>
#include "ThreadSafeQueue.hpp"
#include "CanReceiver.hpp"

ThreadSafeQueue<int> vehicleDataQueue;

void vCanRxTask() {
    CanReceiver canBus("vcan0");
    struct can_frame frame;

    while (true) {
        // La tâche se met en pause ici jusqu'à recevoir une trame CAN
        if (canBus.readFrame(frame)) {
            // On filtre : on ne s'intéresse qu'à la trame ID 0x100 (ex: Trame Moteur)
            if (frame.can_id == 0x100) {
                int speed = frame.data[0]; // On suppose que la donnée 0 est la vitesse
                std::cout << "[CAN RX] Real Frame ID 0x100 received! Extracted speed: " << speed << " km/h" << std::endl;
                vehicleDataQueue.push(speed);
            }
        }
    }
}

void vProcessingTask() {
    int receivedSpeed = 0;
    while (true) {
        if (vehicleDataQueue.pop(receivedSpeed)) {
            std::cout << "[PROCESSING] Analyzing speed: " << receivedSpeed << " km/h - Status: ";
            if (receivedSpeed > 120) std::cout << "CRITICAL (Overspeed!)" << std::endl;
            else std::cout << "OK" << std::endl;
        }
    }
}

int main() {
    std::cout << "[SYSTEM] Booting Embedded Edge Node with SocketCAN..." << std::endl;

    std::thread canTask(vCanRxTask);
    std::thread procTask(vProcessingTask);

    canTask.join();
    procTask.join();

    return 0;
}
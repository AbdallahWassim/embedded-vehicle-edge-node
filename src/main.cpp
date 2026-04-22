#include <iostream>
#include <thread>
#include "ThreadSafeQueue.hpp"
#include "CanReceiver.hpp"
#include "DataFilter.hpp"

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
                int voltage = frame.data[1] ;
                int current = frame.data[2] ;

                std::cout << "[CAN RX] Real Frame ID 0x100 received! Extracted speed: " << speed << " km/h" << std::endl;
                std::cout << "[CAN RX] Voltage: " << voltage << " V, Current: " << current << " A" << std::endl;
                vehicleDataQueue.push(speed);
                vehicleDataQueue.push(voltage);
                vehicleDataQueue.push(current) ;
            }
        }
    }
}

void vProcessingTask() {
    int receivedSpeed = 0;
    int receivedVoltage = 0 ;
    int receivedCurrent = 0 ;

    MovingAverageFilter speedFilter(5); // Filtre pour la vitesse (moyenne des 5 dernières valeurs)
    while (true) {
        if (vehicleDataQueue.pop(receivedSpeed)) {
            int smoothedSpeed = speedFilter.process(receivedSpeed);
            std::cout << "[PROCESSING] Analyzing speed: " << smoothedSpeed << " km/h - Status: ";
            if (smoothedSpeed > 120) std::cout << "CRITICAL (Overspeed!)" << std::endl;
            else std::cout << "OK" << std::endl;
        }
        if (vehicleDataQueue.pop(receivedVoltage)) {
            int smoothedVoltage = speedFilter.process(receivedVoltage);
            std::cout << "[PROCESSING] Analyzing voltage: " << smoothedVoltage << " V - Status: ";
            if (smoothedVoltage < 11) std::cout << "WARNING (Low Voltage!)" << std::endl;
            else std::cout << "OK" << std::endl;
        }
        if (vehicleDataQueue.pop(receivedCurrent)) {
            int smoothedCurrent = speedFilter.process(receivedCurrent);
            std::cout << "[PROCESSING] Analyzing current: " << smoothedCurrent << " A - Status: ";
            if (smoothedCurrent > 50) std::cout << "WARNING (High Current!)" << std::endl;
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
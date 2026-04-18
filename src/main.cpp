#include <iostream>
#include <thread>
#include <chrono>

// Tâche 1 : Simule l'interruption/réception du bus CAN (Haute fréquence)
void vCanRxTask() {
    while (true) {
        std::cout << "[CAN RX TASK] Polling CAN bus for new frames..." << std::endl;
        // Simule un délai RTOS (vTaskDelay) de 500ms
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

// Tâche 2 : Simule le traitement des données capteurs (Basse fréquence)
void vProcessingTask() {
    while (true) {
        std::cout << "[PROCESSING TASK] Computing sensor data..." << std::endl;
        // Simule un délai RTOS (vTaskDelay) de 1000ms
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

int main() {
    std::cout << "[SYSTEM] Booting Embedded Edge Node Simulator..." << std::endl;

    // Lancement des tâches (Équivalent de xTaskCreate en FreeRTOS)
    std::thread canTask(vCanRxTask);
    std::thread procTask(vProcessingTask);

    // Empêche le programme principal de se terminer (Équivalent de vTaskStartScheduler)
    canTask.join();
    procTask.join();

    return 0;
}
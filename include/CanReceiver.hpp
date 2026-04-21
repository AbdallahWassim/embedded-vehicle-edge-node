#ifndef CAN_RECEIVER_HPP
#define CAN_RECEIVER_HPP

#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>

class CanReceiver {
private:
    int m_socket;

public:
    CanReceiver(const std::string& interfaceName) {
        // 1. Créer le socket CAN
        m_socket = socket(PF_CAN, SOCK_RAW, CAN_RAW);
        if (m_socket < 0) {
            std::cerr << "[ERROR] Cannot open CAN socket!" << std::endl;
            return;
        }

        // 2. Trouver l'interface (ex: vcan0)
        struct ifreq ifr;
        std::strcpy(ifr.ifr_name, interfaceName.c_str());
        ioctl(m_socket, SIOCGIFINDEX, &ifr);

        // 3. Lier le socket à l'interface
        struct sockaddr_can addr;
        addr.can_family  = AF_CAN;
        addr.can_ifindex = ifr.ifr_ifindex;

        if (bind(m_socket, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
            std::cerr << "[ERROR] Cannot bind to CAN interface!" << std::endl;
            return;
        }
        std::cout << "[SYSTEM] SocketCAN bound successfully to " << interfaceName << std::endl;
    }

    ~CanReceiver() {
        if (m_socket >= 0) close(m_socket);
    }

    // Fonction bloquante qui lit une trame
    bool readFrame(struct can_frame& frame) {
        int nbytes = read(m_socket, &frame, sizeof(struct can_frame));
        return (nbytes == sizeof(struct can_frame));
    }
};

#endif
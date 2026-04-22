#ifndef DATA_FILTER_HPP 
#define DATA_FILTER_HPP 

#include <vector>

class MovingAverageFilter {
    private :
        std::vector<int> m_window ;
        size_t m_windowSize ; 
        size_t m_index ;
        int m_sum ;


    public : 
    // constructor to initialize the size of window (ex: the last 5 valeurs) 
    
    MovingAverageFilter(size_t size) : m_window(size, 0), m_windowSize(size), m_index(0), m_sum(0) {} 
    
    // function to add a new value and get the current average
    int process(int newValue) {
        // Remove the oldest value from the sum
        m_sum -= m_window[m_index];
        // Add the new value to the window and sum
        m_window[m_index] = newValue;
        m_sum += newValue;
        // Move the index forward
        m_index = (m_index + 1) % m_windowSize;
        // Return the average
        return m_sum / m_windowSize;
    }

};

#endif 
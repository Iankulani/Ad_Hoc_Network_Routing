#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

// Define the maximum number of routing entries
#define MAX_ROUTES 10

// Define a Node struct
typedef struct Node {
    char mac_address[18];  // MAC address as a string (xx:xx:xx:xx:xx:xx)
    char routing_table[MAX_ROUTES][18]; // Simple routing table (direct routes)
    int route_count; // Count of routes in the routing table
} Node;

// Function to simulate delay (like time.sleep() in Python)
void delay(int seconds) {
    sleep(seconds);
}

// Function to add a route to the node's routing table
void add_route(Node *node, const char *destination_mac) {
    if (node->route_count < MAX_ROUTES) {
        strcpy(node->routing_table[node->route_count], destination_mac);
        node->route_count++;
        printf("Route added: %s\n", destination_mac);
    } else {
        printf("Routing table full! Cannot add more routes.\n");
    }
}

// Function to send packet from source to destination node
void send_packet(Node *source_node, const char *destination_mac, const char *packet_data) {
    int route_found = 0;

    // Search for the route in the source node's routing table
    for (int i = 0; i < source_node->route_count; i++) {
        if (strcmp(source_node->routing_table[i], destination_mac) == 0) {
            route_found = 1;
            printf("Sending packet to %s via next hop %s\n", destination_mac, destination_mac);
            delay(1);  // Simulate packet transfer delay
            printf("Packet delivered to %s: %s\n", destination_mac, packet_data);
            break;
        }
    }

    if (!route_found) {
        printf("Route not found for %s. Broadcasting for route discovery...\n", destination_mac);
        route_discovery(source_node, destination_mac, packet_data);
    }
}

// Function to initiate route discovery and simulate adding the route
void route_discovery(Node *source_node, const char *destination_mac, const char *packet_data) {
    printf("Node %s initiating route discovery for %s...\n", source_node->mac_address, destination_mac);
    delay(2);  // Simulate route discovery process
    printf("Route discovered! Adding route to routing table.\n");
    add_route(source_node, destination_mac);  // Direct route for simplicity
    printf("Route to %s is %s\n", destination_mac, destination_mac);
    send_packet(source_node, destination_mac, packet_data);
}

// Function to get MAC address input from user
void get_mac_address_input(char *mac_address) {
    printf("Enter MAC Address of the node:");
    scanf("%s", mac_address);
}

int main() {
    char source_mac[18], destination_mac[18];
    Node source_node, destination_node;
    
    // Initialize source node
    printf("Welcome to the Ad Hoc Network Routing Simulation!\n");

    // Get MAC addresses for nodes
    get_mac_address_input(source_mac);
    get_mac_address_input(destination_mac);

    // Set source and destination MAC addresses
    strcpy(source_node.mac_address, source_mac);
    strcpy(destination_node.mac_address, destination_mac);
    
    // Initialize routing table for source node (no routes initially)
    source_node.route_count = 0;

    // Add a direct route to the destination (simplified routing)
    add_route(&source_node, destination_mac);

    // Simulate sending a packet from source node to destination node
    const char *packet_data = "Hello, this is a test packet!";
    send_packet(&source_node, destination_mac, packet_data);

    return 0;
}

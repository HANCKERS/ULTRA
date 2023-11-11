#include <iostream>
#include <vector>
#include <unordered_set>

void printDirectJourneys(const GTFS::Data& data, const std::string& sourceStopId, const std::string& destinationStopId) {
    std::cout << "Direct journeys:" << std::endl;

    // Iterate through stop times to find direct journeys
    for (const auto& stopTime : data.stopTimes) {
        if (stopTime.stopId == sourceStopId && stopTime.tripId == destinationStopId) {
            // Found a direct journey
            const auto& trip = data.trips[data.tripIds().at(stopTime.tripId)];
            const auto& route = data.routes[data.routeIds().at(trip.routeId)];
            std::cout << "R1(" << sourceStopId << " > " << destinationStopId << ") - Route: " << route.name << ", Trip: " << trip.name << std::endl;
        }
    }
}

void printJourneysWithOneTransfer(const GTFS::Data& data, const std::string& sourceStopId, const std::string& destinationStopId) {
    std::cout << "Journeys with one transfer:" << std::endl;

    // Find all stops reachable from the source stop with one transfer
    std::unordered_set<std::string> reachableStops;
    for (const auto& transfer : data.transfers) {
        if (transfer.fromStopId == sourceStopId) {
            reachableStops.insert(transfer.toStopId);
        }
    }

    // Iterate through stop times to find journeys with one transfer
    for (const auto& stopTime : data.stopTimes) {
        if (reachableStops.count(stopTime.stopId) > 0) {
            for (const auto& transfer : data.transfers) {
                if (transfer.fromStopId == stopTime.stopId && transfer.toStopId == destinationStopId) {
                    // Found a journey with one transfer
                    const auto& trip1 = data.trips[data.tripIds().at(stopTime.tripId)];
                    const auto& route1 = data.routes[data.routeIds().at(trip1.routeId)];

                    const auto& trip2 = data.trips[data.tripIds().at(transfer.tripId)];
                    const auto& route2 = data.routes[data.routeIds().at(trip2.routeId)];

                    std::cout << "R2(" << sourceStopId << " > " << stopTime.stopId << ") - Route: " << route1.name << ", Trip: " << trip1.name
                              << " - R3(" << stopTime.stopId << " > " << destinationStopId << ") - Route: " << route2.name << ", Trip: " << trip2.name << std::endl;
                }
            }
        }
    }
}

int main(int argc, char* argv[]) {
\

    // Print direct journeys
    printDirectJourneys(gtfsData, sourceStopId, destinationStopId);

    // Print journeys with one transfer
    printJourneysWithOneTransfer(gtfsData, sourceStopId, destinationStopId);

    return 0;
}

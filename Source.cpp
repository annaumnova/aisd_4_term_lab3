#include"BellmanFord.h"

int main() {
    
    //information about flights
    List<GraphCities> cities;
    List<std::string> str;

    //parse the information
    parse(&cities, &str);

    //Bellman-Ford algorithm
    bellmanFord(&cities, &str, "Moscow", "Vladivostok");
    bellmanFord(&cities, &str, "Moscow", "Khabarovsk");
    bellmanFord(&cities, &str, "St.Petersburg", "Vladivostok");
    bellmanFord(&cities, &str, "Moscow", "St.Petersburg");
    bellmanFord(&cities, &str, "Vladivostok", "Vladivostok");
    bellmanFord(&cities, &str, "Vladivostok", "Khabarovsk");
    bellmanFord(&cities, &str, "St.Petersburg", "Khabarovsk");

	return 0;
}
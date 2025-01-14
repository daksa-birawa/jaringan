#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <thread>
#include <chrono>

using namespace std;

// Struktur untuk menyimpan statistik ruangan
struct Room {
    string name;
    int requests = 0;
    double total_response_time = 0.0;
    int active_connections = 0;
    double throughput = 0.0;
};

// Fungsi untuk mensimulasikan waktu respon acak
double generateResponseTime(double max_response_time) {
    return static_cast<double>(rand()) / RAND_MAX * max_response_time;
}

// Fungsi utama simulasi Round Robin
void roundRobinSimulation(vector<Room>& rooms, int total_requests, double max_response_time) {
    int num_rooms = rooms.size();
    int current_room = 0;

    for (int request_id = 1; request_id <= total_requests; ++request_id) {
        Room& room = rooms[current_room];

        // Simulasikan waktu respon
        double response_time = generateResponseTime(max_response_time);
        room.requests++;
        room.total_response_time += response_time;
        room.active_connections++;
        room.throughput += 1.0 / response_time;

        // Output simulasi
        cout << "Request " << request_id << " dialokasikan ke " << room.name << endl;
        cout << "  Response Time: " << fixed << setprecision(2) << response_time << " detik" << endl;

        // Simulasikan waktu proses
        this_thread::sleep_for(chrono::milliseconds(100)); // Delay 100ms untuk simulasi

        // Selesaikan koneksi
        room.active_connections--;

        // Pindahkan ke ruangan berikutnya
        current_room = (current_room + 1) % num_rooms;
    }
}

int main() {
    // Inisialisasi data
     vector<Room> rooms = {
        {"Room 1"}, {"Room 2"}, {"Room 3"}, {"Room 4"}
    };

    const int total_requests = 20;
    const double max_response_time = 2.0; // Dalam detik


    srand(time(0)); // Inisialisasi random seed

    // Jalankan simulasi
    cout << "Simulasi Round Robin dimulai...\n\n";
    roundRobinSimulation(rooms, total_requests, max_response_time);

    // Tampilkan hasil akhir
    cout << "\nStatistik Akhir:\n";
    for (const auto& room : rooms) {
        double avg_response_time = (room.requests > 0) ? room.total_response_time / room.requests : 0.0;
        cout << room.name << ":\n";
        cout << "  Total Requests: " << room.requests << endl;
        cout << "  Rata-rata Response Time: " << fixed << setprecision(2) << avg_response_time << " detik" << endl;
        cout << "  Throughput: " << fixed << setprecision(2) << room.throughput << " requests per second" << endl;
        cout << "  Active Connections: " << room.active_connections << endl;
    }

    return 0;
}
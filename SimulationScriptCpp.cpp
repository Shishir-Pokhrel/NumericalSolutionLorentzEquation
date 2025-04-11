#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <iomanip> // For setprecision

// Lorenz system parameters
const double s = 10.0;     // Prandtl number
const double r = 28.0;     // Rayleigh number
const double b = 8.0/3.0;  // Geometric factor

struct State {
    double x, y, z;
};

struct SimulationResult {
    std::vector<double> x, y, z, t;
};

void lorenzSystem(const State& current, State& derivatives) {
    derivatives.x = -s * (current.x - current.y);
    derivatives.y = -current.x * current.z + r * current.x - current.y;
    derivatives.z = current.x * current.y - b * current.z;
}

SimulationResult eulerIntegration(State initialState, double tMin, double tMax, double h = 0.001) {
    SimulationResult result;
    int n = static_cast<int>((tMax - tMin) / h) + 1;
    
    result.x.reserve(n);
    result.y.reserve(n);
    result.z.reserve(n);
    result.t.reserve(n);
    
    result.x.push_back(initialState.x);
    result.y.push_back(initialState.y);
    result.z.push_back(initialState.z);
    result.t.push_back(tMin);
    
    for (int i = 1; i < n; ++i) {
        State current{result.x[i-1], result.y[i-1], result.z[i-1]};
        State derivatives;
        lorenzSystem(current, derivatives);
        
        result.x.push_back(current.x + h * derivatives.x);
        result.y.push_back(current.y + h * derivatives.y);
        result.z.push_back(current.z + h * derivatives.z);
        result.t.push_back(tMin + i * h);
    }
    
    return result;
}

void writeToFile(const SimulationResult& result, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
    
    // Set high precision for all values
    outFile << std::scientific << std::setprecision(15);
    
    for (size_t i = 0; i < result.t.size(); ++i) {
        outFile << result.t[i] << " " 
                << result.x[i] << " " 
                << result.y[i] << " " 
                << result.z[i] << "\n";
    }
    outFile.close();
}

void generateGnuplotScript(const std::string& dataFile, const std::string& plotTitle) {
    std::ofstream script("plot_results.gp");
    
    script << "set terminal pngcairo enhanced size 1200,800\n";
    script << "set output 'lorenz_plot.png'\n";
    script << "set multiplot layout 2,2 title '" << plotTitle << "'\n\n";
    
    // Time series plot
    script << "set title 'Time Series'\n";
    script << "set xlabel 't'\n";
    script << "plot '" << dataFile << "' using 1:2 with lines title 'x(t)', \\\n";
    script << "     '" << dataFile << "' using 1:3 with lines title 'y(t)', \\\n";
    script << "     '" << dataFile << "' using 1:4 with lines title 'z(t)'\n\n";
    
    // 3D plot
    script << "set title '3D Trajectory'\n";
    script << "set view 60,30\n";
    script << "set xlabel 'x'\n";
    script << "set ylabel 'y'\n";
    script << "set zlabel 'z'\n";
    script << "splot '" << dataFile << "' using 2:3:4 with lines notitle\n\n";
    
    // 2D projections
    script << "set title 'x-z Projection'\n";
    script << "set xlabel 'x'\n";
    script << "set ylabel 'z'\n";
    script << "plot '" << dataFile << "' using 2:4 with lines title 'x-z'\n\n";
    
    script << "set title 'y-z Projection'\n";
    script << "set xlabel 'y'\n";
    script << "set ylabel 'z'\n";
    script << "plot '" << dataFile << "' using 3:4 with lines title 'y-z'\n\n";
    
    script << "unset multiplot\n";
    script.close();
}

int main() {
    State initialState{10.0, 10.0, 10.0};
    double tMin = 0.0, tMax = 30.0, tMid = 15.0;
    double h = 0.001;
    
    // Full simulation
    auto fullResult = eulerIntegration(initialState, tMin, tMax, h);
    writeToFile(fullResult, "full_simulation.dat");
    generateGnuplotScript("full_simulation.dat", "Lorenz System (t=0 to 30)");
    
    std::cout << "Simulation complete. Files created:\n";
    std::cout << " - full_simulation.dat (data file)\n";
    std::cout << " - plot_results.gp (gnuplot script)\n\n";
    std::cout << "Run 'gnuplot plot_results.gp' to generate 'lorenz_plot.png'\n";
    
    return 0;
}

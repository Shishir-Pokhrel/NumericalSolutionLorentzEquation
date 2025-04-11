This repository has the following: 
  Simulation scripts for solution of atmospheric dynamics equations in 
    - Matlab SimulationScriptMATLAB.m
    - Python SimulationScriptPYTHON.py
    - C++ script SimulationScriptCpp.cpp

The matlab script and python script can be run respectively on Matlab and python. 

To run the C++ script, 
  - Compile the script using
        g++ -std=c++11 SimulationScriptCpp.cpp -o lorenz
  - Run 
        ./lorentz
  - Generate plot results using
        gnuplot plot_results.gp
    

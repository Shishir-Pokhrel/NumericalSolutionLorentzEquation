clc; clear all; close all;

%% Parameters and Initial Conditions
h = 0.001;          % Step size
x0 = 10; y0 = 10; z0 = 10;  % Initial conditions
tmin = 0; tmax = 30; tmid = 15;  % Time parameters

% Lorenz system parameters
s = 10;     % Prandtl number
r = 28;     % Rayleigh number
b = 8/3;    % Geometric factor

%% Full Simulation (t = 0 to 30)
[x, y, z, t] = Euler(x0, y0, z0, tmin, tmax);

% Plot time series
figure;
plot(t, x, t, y, t, z); 
legend('x(t)', 'y(t)', 'z(t)');
xlabel('t'); 
title('Explicit Euler for time t = 0 to t=30');

% Plot 3D trajectory
figure;
plot3(x, y, z, 'k'); 
xlabel('x'); ylabel('y'); zlabel('z');
title('3D plot for t = 0 to t=30');

% Plot 2D projections
figure;
subplot(2,1,1);
plot(x, z, 'k'); 
xlabel('x'); ylabel('z');
title('x-z projection');

subplot(2,1,2);
plot(y, z, 'k'); 
xlabel('y'); ylabel('z');
title('y-z projection');

%% Split Simulation (t = 0-15 and 15-30)
% First half (t = 0 to 15)
[x1, y1, z1, t1] = Euler(x0, y0, z0, tmin, tmid);

figure;
plot(t1, x1, t1, y1, t1, z1); 
legend('x(t)', 'y(t)', 'z(t)');
xlabel('t'); 
title('Euler''s method, t = 0 to 15');

% Second half (t = 15 to 30) using final state of first half as initial condition
nk = numel(x1);
[x2, y2, z2, t2] = Euler(x1(nk), y1(nk), z1(nk), tmid, tmax);

figure;
plot(t2, x2, t2, y2, t2, z2);
legend('x(t)', 'y(t)', 'z(t)');
xlabel('t'); 
title('Euler''s method, t = 15 to 30');

%% Euler Integration Function
function [x, y, z, t] = Euler(x0, y0, z0, tmin, tmax)
    h = 0.001; 
    t = tmin:h:tmax; 
    n = length(t);
    
    % Initialize arrays
    x = zeros(1, n); 
    y = zeros(1, n); 
    z = zeros(1, n);
    
    % Set initial conditions
    x(1) = x0; 
    y(1) = y0; 
    z(1) = z0;
    
    % Euler integration
    for i = 1:n-1
        [dx, dy, dz] = LorenzSystem(x(i), y(i), z(i));
        x(i+1) = x(i) + h * dx;
        y(i+1) = y(i) + h * dy;
        z(i+1) = z(i) + h * dz;
    end   
end

%% Lorenz System Equations
function [dx, dy, dz] = LorenzSystem(x, y, z)
    s = 10;     % Prandtl number
    r = 28;     % Rayleigh number
    b = 8/3;    % Geometric factor
    
    dx = -s * (x - y);
    dy = -x * z + r * x - y;
    dz = x * y - b * z;
end

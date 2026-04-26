clc; clear;

n = 20;
t = linspace(0, 1, n);

% Planned path (smooth curve)
lat_path = 17 + 0.2*t;
lon_path = 78 + 0.1*sin(2*pi*t);

% Actual path (follows + curved deviation)
lat_actual = lat_path;
lon_actual = lon_path;

% Introduce curved deviation (middle region)
idx = 8:14;
lat_actual(idx) = lat_actual(idx) + 0.05*sin(linspace(0, pi, length(idx)));
lon_actual(idx) = lon_actual(idx) + 0.05*cos(linspace(0, pi, length(idx)));

% Plot
figure;
plot(lat_path, lon_path, 'g-o', 'LineWidth', 2); hold on;
plot(lat_actual, lon_actual, 'r-x', 'LineWidth', 2);
legend('Planned Path', 'Actual Path');
xlabel('Latitude'); ylabel('Longitude');
title('Hiking Path with Deviation');
grid on;

% ----------- FORMATTED OUTPUT FOR WOKWI -----------

fprintf('\nPATH = {\n');
for i = 1:n
    fprintf('  {%.5f, %.5f},\n', lat_path(i), lon_path(i));
end
fprintf('};\n');

fprintf('\nACTUAL = {\n');
for i = 1:n
    fprintf('  {%.5f, %.5f},\n', lat_actual(i), lon_actual(i));
end
fprintf('};\n');

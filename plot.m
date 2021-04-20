data = load('output.txt');

t = data(:, 1);
theta = data(:, 2);
omega = data(:, 3);

figure;
hold on;
title('Pendulum Angular Displacement and Rate vs Time');
yyaxis left;
plot(t, theta);
ylabel('\theta(t) [rad]');
ylim([min([theta; omega]), max([theta; omega])]);

yyaxis right;
plot(t, omega);
ylabel('\omega(t) [rad/s]');
ylim([min([theta; omega]), max([theta; omega])]);

xlabel('Time [s]');
legend('Angular displacement, \theta(t)', 'Angular rate, \omega(t)');
grid on;
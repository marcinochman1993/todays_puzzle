close all;

T = 0.05;
f = 1/T;
fs = 8*f;
Ts = 1/fs;
A = 2;
N = 10000;
t = 0:Ts:Ts*N;

y = A*sin(2*pi*f*t);
Y = fft(y);

f_vec = fs*(0:N)/N;


plot(f_vec, abs(Y))
grid on;
xlabel('f [Hz]')
ylabel('|y(f)|')
xlim([0 fs/2])
title('Spectrum of original signal');

% move fs/2
figure()
mixing_sequence = ones(1, N+1);
mixing_sequence(:, 1:2:end) = -1;

shifted_y = y.*mixing_sequence;
shifted_Y = fft(shifted_y);
plot(f_vec, abs(shifted_Y))
xlabel('f [Hz]')
ylabel('|y(f)|')
title('Spectrum of shifted signal fs/2');
xlim([0 fs/2])
grid on;


clear all;
close all;
%fréquence pistolet
F = 5.5;



T=2;
Te=1/M;
M=32;
Ts= Te/100;
Tsim=T-Te;



sim('SimulinkCarre');

z=linspace(0,(1/T)*M-1,M);
%for i = 1 : (size(Sin_Ech.Data)/2)+1
%    Sin_Ech.data(i)=0;
%end


plot(z*(1/T),fft(Sin_Ech.data), '*');
figure;


figure;

plot(Sin_Cont);
hold on;
plot(Sin_Ech,'*');

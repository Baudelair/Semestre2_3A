clear all;
close all;
%fréquence pistolet
F0 = 85000;
F1 =  85005.9;
F2 =  90000;
F3 =  94986.8;
F4 =  100000;
F5 =  115015.9;
F6 =  120000;


T=1/5000;
Te=1/320000;
M=T/Te;
Ts= Te/100;
Tsim=T-Te;



sim('SimulinkCarre');

z=linspace(0,M-1,M);
%for i = 1 : (size(Sin_Ech.Data)/2)+1
%    Sin_Ech.data(i)=0;
%end


plot(z*(1/T),abs(fft(Sin_Ech.data(2*M:3*M),M)), '*');
figure;

sys=tf(1,[1.7483*10^-23,7.6663*10^-18,1.162*10^-11,3.0332*10^-6,1]);
bode(sys);
figure;

plot(Sin_Cont);
hold on;
plot(Sin_Ech,'*');

clc; clear all; close all; 

L1 = 9.626;
L2 = 23.5;
L3 = 18.475;
L4 = 9;
phi = 90;

x = -15;
y = 10;
z = 5;

%Theta 1
th1 = atan2d(y,x);

%Theta 3
r = sqrt(x^2+y^2);
Z = z + L4 - L1;
th3_1 =  acosd((r^2+Z^2 - L2^2 - L3^2)/(2*L2*L3));
th3_2 = -acosd((r^2+Z^2 - L2^2 - L3^2)/(2*L2*L3));

%Theta 2
th2_1 = atan2d(Z,r) - atan2d((L3*sind(th3_1)),(L2+L3*cosd(th3_1)));
th2_2 = atan2d(Z,r) - atan2d((L3*sind(th3_2)),(L2+L3*cosd(th3_2)));

%Theta 4
th4_1 = phi - th2_1 - th3_1;
th4_2 = phi - th2_2 - th3_2;

